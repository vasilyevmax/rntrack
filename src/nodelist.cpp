/*
 *  RNtrack - FTN message tracker/router
 *
 *  nodelist.cpp - Work with nodelists
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id$
 */

#ifndef __GNUC__
#include <io.h>
#include <direct.h>
#ifdef _MSC_VER
#include "dirent/dirent.h"
#endif
#else
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#endif                  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "constant.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "age.hpp"
#include "utils.hpp"

char *NodelistPath;

static bool NodelistTurnOff = FALSE;
static int NodelistLineNum = 0;

static char mErrReadIndex[] = "Error reading index file.";
static char mNdlChanged[] = "Some nodelists have changed. Recompilation is necessary.";
static char mIndNFound[] = "Index file not found. Create new index file.";
static char mErrNdlMustFull[] = "Error: You must define default Zone for Regional and Network versions of nodelist.";
static char mErrNdlFormat[] = "Incorrect nodelist format.";

#define ErrReadIndex   Log.Level(LOGE) << mErrReadIndex << EOL
#define IndexChanged   Log.Level(LOGI) << mNdlChanged << EOL
#define IndexNotFound  Log.Level(LOGI) << mIndNFound << EOL


typedef struct _Ntr {
   dword Number;
   dword Attrib;
   struct _Ntr  *Next;
   struct _Ntr  *Sub;
} Ntr;

void ErrNdlFormat(char *m) {
   Log.Level(LOGE) << "Error in line " << NodelistLineNum << ", " << mErrNdlFormat << EOL;
   Log.Level(LOGE) << m << EOL;
   NodelistTurnOff = TRUE;
}

int FindNodelist(char *Mask, char *Name) {
int maxext;
DIR *dd;
struct dirent *ff;
char NDir[512], Path[512], Fname[512];
char *tmt = NULL;
FILE *ft;

   *Name = '\0';
   Path[1] = '\0';
   maxext = (-1);

   GetFilePath(Path,Mask);
   if (NodelistPath != NULL && *Path != PATHDELIMC
#ifndef __unix__
       && Path[1] != ':'
#endif
   ) {
      strcpy(NDir,NodelistPath);
      strcat(NDir,Path);
      strcpy(Path,NDir);
   }
   GetFileName(Fname,Mask);
   if (strchr(Fname,'*') || strchr(Fname,'?')) {
      if ((dd = opendir(dirslashbug(Path))) != 0) {
         while((ff = readdir(dd)) != NULL) {
            if (fsCompareName(ff->d_name,Fname) != 0 && (tmt = strrchr(ff->d_name,'.')) != NULL) {
           tmt++;
               if (StrIsNum(tmt) && atoi(tmt) > maxext) {
                  maxext = atoi(tmt);
          strcpy(Name,Path);
          strcat(Name,ff->d_name);
               }
            }
         }
         closedir(dd);
      } else {
         yyerror("Nodelist not found.");
         return (-1);
      }
   } else {
      strcpy(Name,Path);
      strcat(Name,Fname);
   }
   if (*Name == '\0') {
      yyerror("Nodelist not found.");
      return (-1);
   }
   if ((ft = fopen(Name,"rt")) == NULL) {
      yyerror("Unable to open Nodelist.");
      return (-1);
   } else {
      fclose (ft);
   }
   return (0);
}

// ------------------- Compile and write one nodelist  --------------------

static FILE *nh;
static int  CurrentNet = -1;
static int  CurrentZone = -1;
static Ntr  **CurrentHub = NULL;
static Ntr  *_pNodeList = NULL;
static bool PointListMode = FALSE;
static Ntr *BossNode = NULL;

bool OpenNodelist(char *FName) {
   nh = fopen(FName,"rt");
   if (nh == NULL) {
      Log.Level(LOGE) << "Unable to open nodelist '" << FName << "'" << EOL;
      return FALSE;
   }
   return TRUE;
}

bool CloseNodelist(void) {
   return (fclose (nh) == 0);
}

int ReadNdlLine (char *Buff, int Count) {
char *tmt;
   Buff[0] = ';';
   while (Buff[0] == ';') {
      NodelistLineNum++;
      if (fgets(Buff, Count, nh) == NULL) {
         Buff[0] = '\0';
         return (-1);
      }
      tmt = strchr(Buff,'\n');
      if (tmt != NULL) *tmt = '\0';
      tmt = strchr(Buff,'\r');
      if (tmt != NULL) *tmt = '\0';
      tmt = strchr(Buff,(char)0x1a);
      if (tmt != NULL) *tmt = '\0';
      if (strlen(Buff) == 0) {
         Buff[0] = ';';
      }
   }
   return(strlen(Buff));
}

Ntr *ExistByNumber(Ntr *Addr, unsigned int Number) {
Ntr *tmt;
   tmt = Addr;
   while (tmt != NULL) {
      if ((tmt->Number & 0xffff) == (Number & 0xffff)) {
         return tmt;
      }
      tmt = tmt->Next;
   }
   return NULL;
}

Ntr *GetCurrentZone(void) {
   return(ExistByNumber(_pNodeList,CurrentZone));
}

Ntr *GetCurrentNet(void) {
Ntr *tmt;
   if ((tmt = GetCurrentZone()) != NULL) {
      if (tmt->Sub != NULL) {
         return (ExistByNumber(tmt->Sub,CurrentNet));
      } else {
        return NULL;
      }
   } else {
      return NULL;
   }
}

bool DelDupNode(unsigned int Node) {
// Remove a node from the list if it is already present there but check
// whether it is a hub. If it is a hub then do not remove it. If the node
// is also a hub now then we set the current hub pointer to the hub.
// Return TRUE  if the node was successfully removed 
//              or it was absent in the list
//        FALSE if the node was in the list as a hub and it is a hub now.
Ntr *tr;
   tr = GetCurrentNet();
   assert(tr != NULL);
   tr = tr->Sub;
   while (tr != NULL) {
      if ((tr->Number & 0xffff) == (Node & 0xffff)) {
         if ((tr->Number & A_MASK) != A_HUB) {
            tr->Number = (unsigned int)-1;
            return TRUE;
         } else if (((tr->Number & A_MASK) == A_HUB) && ((Node & A_MASK) == A_HUB)) {
//            Log.Level(LOGD) << "Two nodes? " << tr->Number << " " << Node << EOL;
//            Log.Level(LOGD) << "Net: " << CurrentZone << ":" << CurrentNet << EOL;
            CurrentHub = &(tr->Next);
            return FALSE;
         }
      }
      tr = tr->Next;
   }
   return TRUE;
}

void AddElemToList(Ntr **Addr, unsigned int Number) {
Ntr *tmt;
   tmt = (Ntr *) malloc(sizeof(Ntr));
   CheckMem((char *)tmt);
   memset(tmt,0,sizeof(Ntr));
   tmt->Number = Number;
   while ((*Addr) != 0) {
      Addr = &((*Addr)->Next);
   }
   *Addr = tmt;
}

void AddNetToList(void) {
Ntr *tr;
   tr = GetCurrentZone();
   assert(tr != NULL);
   AddElemToList(&(tr->Sub),CurrentNet);
}

void AddZoneToList(void) {
   AddElemToList(&_pNodeList,CurrentZone);
   AddNetToList();
}

void _SetCurrentZone(unsigned int Zone) {
   CurrentZone = Zone;
   CurrentNet = Zone;
   CurrentHub = NULL;
   if (GetCurrentZone() == 0) {
      AddZoneToList();
   }
}

void _AddNode(unsigned int Node) {
// Add a node to the list. If it is absent there then just prepend it
// to the CurrentHub list. If there is no CurrentHub list then we add
// the node as usual. If the node is already present in the list
// then do nothing.
Ntr *tr, *tmt;

   if (DelDupNode(Node) == TRUE) {
      if (CurrentHub != NULL) {
         tmt = (Ntr *) malloc(sizeof(Ntr));
         CheckMem((char *)tmt);
         memset(tmt,0,sizeof(Ntr));
         tmt->Number = Node;
         tr = (*CurrentHub)->Next;
         (*CurrentHub)->Next = tmt;
         tmt->Next = tr;
      } else {
         tr = GetCurrentNet();
         assert(tr != NULL);
         AddElemToList(&(tr->Sub),Node);
      }
   }
}

void _SetCurrentNet(unsigned int Net) {
   CurrentNet = Net;
   CurrentHub = NULL;
   if (GetCurrentNet() == NULL) {
      AddNetToList();
   }
}

bool _SetCurrentBoss(char *tmt) {
FA f;
Ntr *tp;

   BossNode = NULL;
   f.Parse(tmt);
   if (f.Masked()) return FALSE;
   if ((f.Point() & 0xffff) != 0) return FALSE;
   tp = ExistByNumber(_pNodeList,f.Zone());
   if (tp == NULL) return TRUE;
   if (tp->Sub == NULL) return TRUE;
   tp = ExistByNumber(tp->Sub,f.Net());
   if (tp == NULL) return TRUE;
   if (tp->Sub == NULL) return TRUE;
   tp = ExistByNumber(tp->Sub,f.Node());
   if (tp == NULL) return TRUE;
   BossNode = tp;
   return TRUE;
}

void _AddPoint(int pnt) {

   if (BossNode != NULL) {
      AddElemToList(&(BossNode->Sub),pnt);
   }
}

bool ParseNodeLine(char *tmt) {
unsigned int tmp;

// DumpNdl();
// fprintf(stderr,"%s\n",tmt);
//   printf("'%s'\n",tmt);
   switch(*tmt) {
      case 'B': // Boss record. Pointlist?
      case 'b':
         PointListMode = TRUE;
         if (_SetCurrentBoss(tmt+5) != TRUE) {
            ErrNdlFormat("Bad BOSS record");
            return FALSE;
         }
         break;
      case 'Z': // Zone record
         PointListMode = FALSE;
         _SetCurrentZone(atoi(tmt+5));
         break;
      case 'R': // Region record
         PointListMode = FALSE;
         if (CurrentZone == 0) {
            Log.Level(LOGE) << mErrNdlMustFull << EOL;
            return FALSE;
         }
         tmp = atoi(tmt+7);
         tmp |= A_REGION;
         _SetCurrentNet(tmp);  // Region is a strange type of net.
         break;
      case 'H': // Host, Hub, or Hold record
         switch(*(tmt+2)) {
            case 's': // Host
               PointListMode = FALSE;
               if (CurrentZone == 0) {
                  Log.Level(LOGE) << mErrNdlMustFull << EOL;
                  return FALSE;
               }
               _SetCurrentNet(atoi(tmt+5));
               break;
            case 'b': // Hub
               if (PointListMode == TRUE) {
                  ErrNdlFormat("HUB record in pointlist!");
                  return FALSE;
               }
               if (CurrentZone == 0) {
                  ErrNdlFormat("HUB record without Zone record!");
                  return FALSE;
               }
               tmp = atoi(tmt+4);
               tmp |= A_HUB;
               _AddNode(tmp);
               break;
            case 'l': // Hold
               if (PointListMode == TRUE) {
                  ErrNdlFormat("Node or point with HOLD flag!");
                  return FALSE;
               }
               if (CurrentZone == 0) {
                  ErrNdlFormat("HOLD record without Zone record!");
                  return FALSE;
               }
               tmp = atoi(tmt+5);
               tmp |= A_HOLD;
               _AddNode(tmp);
               break;
            default: 
               ErrNdlFormat("Unknown format!");
               return FALSE;
         }
         break;
      case ',': // Simple node
         if (PointListMode == TRUE) {
            _AddPoint(atoi(tmt+1));
         } else {
            if (CurrentZone == 0) {
               ErrNdlFormat("Node record without Zone record!");
               return FALSE;
            }
            if (CurrentNet == 0) {
               ErrNdlFormat("Node record without Host/Region record!");
               return FALSE;
            }
            _AddNode(atoi(tmt+1));
         }
         break;
      case 'D': // Down
         if (PointListMode == TRUE) {
            ErrNdlFormat("DOWN record in pointlist!");
            return FALSE;
         }
         if (CurrentZone == 0) {
            ErrNdlFormat("Node Down record without Zone record!");
            return FALSE;
         }
         if (CurrentNet == 0) {
            ErrNdlFormat("Node Down record without Host/Region record!");
            return FALSE;
         }
         tmp = atoi(tmt+5);
         tmp |= A_DOWN;
         _AddNode(tmp);
         break;
      case 'P': // Pvt or Point
      case 'p': 
         switch(*(tmt+1)) {
            case 'v': // Pvt
               if (PointListMode == TRUE) {
                  ErrNdlFormat("PVT record in pointlist!");
                  return FALSE;
               }
               if (CurrentZone == 0) {
                  ErrNdlFormat("Node Pvt record without Zone record!");
                  return FALSE;
               }
               if (CurrentNet == 0) {
                  ErrNdlFormat("Node Pvt record without Host record!");
                  return FALSE;
               }
               tmp = atoi(tmt+4);
               tmp |= A_PVT;
               _AddNode(tmp);
               break;
            case 'o': // Point
               if (PointListMode == FALSE) {
                  ErrNdlFormat("POINT record not in pointlist!");
                  return FALSE;
               }
               tmp = atoi(tmt+6);
               _AddPoint(tmp);
               break;
            default: 
               ErrNdlFormat("Unknown format!");
               return FALSE;
         }
         break;
      default: // No one? Hmm...
         ErrNdlFormat("Unknown format!");
         return FALSE;
   }
   return TRUE;
}

bool ParseOneNodelist (NodeListElem *Elem) {
char Buff[512];
   Log.Level(LOGI) << "Compile nodelist '" << Elem->Name << "'";
   if (Elem->StartZone != 0) {
      _SetCurrentZone(Elem->StartZone); // Set address to Zone:Zone/0; 1st line of the nodelist should be "Host" or "Region"
      Log.Level(LOGI) << ", start zone number is " << Elem->StartZone << EOL;
   } else {
      CurrentZone = 0;
   }
   CurrentNet = 0;
   Log.Level(LOGI) << " ..." << EOL;

   if (!OpenNodelist(Elem->Name)) {
      return FALSE;
   }

   NodelistLineNum = 0;
   while(ReadNdlLine(Buff,510) > 0) {
      if (!ParseNodeLine(Buff)) {
         CloseNodelist();
         return FALSE;
      }
   }
   CloseNodelist();
   Log.Level(LOGI) << "Done" << EOL;
   return TRUE;
}

// ------------------------------------------------------
// Flush compiled nodelist to disk
// ------------------------------------------------------

#if 0
void PrintNtr(Ntr *tmt, char *Buff) {
int len;
Ntr *tmt2;
   len = strlen(Buff);
   tmt2= tmt;
   while (tmt != NULL) {
      sprintf(Buff+len,"%d ",tmt->Number & 0xffff);
      PrintNtr(tmt->Sub,Buff);
      tmt = tmt->Next;
   }
   if (tmt2 == NULL) printf("%s\n",Buff);
}
#endif

int ElementsInList (Ntr *Addr) {
Ntr *tmt;
int Elems;

   tmt = Addr;
   Elems = 0;
   while (tmt != NULL) {
      if (tmt->Number != (unsigned int)-1) {
         Elems++;
      }
      tmt = tmt->Next;
   }
   return Elems;
}

bool SaveElements(FILE *fh, Ntr *Addr) {
Ntr *tmt;
   tmt = Addr;
   while (tmt != NULL) {
      if (tmt->Number != (unsigned int)-1) {
          if (fwrite(&tmt->Number,sizeof(int),1,fh) != 1) {
             Log.Level(LOGE) << "Unable to write body of Elems" << EOL;
             return FALSE;
          }
      }
      tmt = tmt->Next;
   }
   return TRUE;
}

bool FlushElements(FILE *fh, Ntr *tmt) {
int Elems;

   Elems = ElementsInList(tmt);
   if (fwrite(&Elems,sizeof(Elems),1,fh) != 1) {
      Log.Level(LOGE) << "Unable to write Elems" << EOL;
      return FALSE;
   }
   if (!SaveElements(fh,tmt)) return FALSE;
   return TRUE;
}

bool FlushSubElements(FILE *fh, Ntr *tmt) {
   if (FlushElements(fh,tmt) == FALSE) return FALSE;
   while (tmt != NULL) {
      if (tmt->Number != (unsigned int)-1) {
         if (FlushSubElements(fh,tmt->Sub) == FALSE) return FALSE;
      }
      tmt = tmt->Next;
   }
   return TRUE;
}

bool FlushElementsTree(FILE *fh) {
   return (FlushSubElements(fh, _pNodeList));
}

// ------------------------------------------------------
// Free parser memory
// ------------------------------------------------------

void FreeSubElements(Ntr *tmt) {
Ntr *tmt2;

   if (tmt == NULL) return;
   while (tmt != NULL) {
      FreeSubElements(tmt->Sub);
      tmt2 = tmt->Next;
      free(tmt);
      tmt = tmt2;
   }
}

void FreeParserMem(void) {
   FreeSubElements(_pNodeList);
   _pNodeList = NULL;
}

// ------------------------------------------------------

bool FlushNodelist (FILE *fh) {
#if 0
char Buff[1024];
   PrintNtr(_pNodeList,Buff);
#endif
   if (FlushElementsTree(fh) == FALSE) return FALSE;
   FreeParserMem();
   return TRUE;
}



// ------------------------- class NodeLists -----------------------

NodeLists::NodeLists() {
   NList = NULL;
   Lists = 0;
   StartZone = 0;
   IndexName = strdup(DefaultIndex);
}

NodeLists::~NodeLists() {
   if (NList != NULL) {
      free(NList);
      NList= NULL;
   }
   Lists = 0;
   if (IndexName != NULL) {
      free(IndexName);
      IndexName = NULL;
   }
}

#if 0
void PrintNch(Nch *tmt, char *Buff) {
int i;
int len;
   len = strlen(Buff);
   i = 0;
   while (tmt[i].Number != -1) {
      sprintf(Buff+len,"%d ",tmt[i].Number & 0xffff);
      PrintNch(tmt[i].Sub,Buff);
      i++;
   }
   if (tmt[0].Number == -1) printf("%s\n",Buff);
}
#endif

void NodeLists::Print(void) {
#if 0
int tmc;
char Buff[1024];
NodeListElem *tmt;
   printf("Index file: '%s'\n",IndexName);
   printf("Total nodelists: '%d'\n",Lists);
   tmt = NList;
   tmc = Lists;
   while (tmc != 0) {
      printf("Nodelist name: '%s'\n",tmt->Name);
      printf("Nodelist Date: '%d'\n",tmt->Time);
      tmc--;
      tmt++;
   }
   Buff[0] = '\0';
   PrintNch(Index,Buff);
#endif
}

void NodeLists::IndexFile(char *File) {
   if (IndexName != NULL) {
      free(IndexName);
      IndexName = NULL;
   }
   IndexName = strdup(File);
}

bool NodeLists::CompileNeed(void) {
FILE *fh;
unsigned int tmp;
NodeListElem Elem;

// 1 - does index file exist?
   if (access(IndexName,F_OK) != 0) {
      IndexNotFound;
      return TRUE;
   }

// 2 - can we open it?
   fh = fopen(IndexName,"r+b");
   if (fh == NULL) {
      Log.Level(LOGE) << "Unable to open index file." << EOL;
      return TRUE;
   }

// 3 - can we read the signature from it?
   if (fread(&tmp,sizeof(tmp),1,fh) != 1) {
      ErrReadIndex;
      fclose(fh);
      return TRUE;
   }

// 4 - is signature correct?
   if (tmp != NdlSign) {
      Log.Level(LOGE) << "Index file from the old version of RNtrack. Recompilation is necessary." << EOL;
      fclose(fh);
      return TRUE;
   }

// 5 - can we read nodelist count?
   if (fread(&tmp,sizeof(tmp),1,fh) != 1) {
      ErrReadIndex;
      fclose(fh);
      return TRUE;
   }

// 6 - is the count of nodelists the same?
   if (tmp != (unsigned int) Lists) {
      IndexChanged;
      fclose(fh);
      return TRUE;
   }

// 7 - have nodelists not changed?
   for (unsigned int i = 0; i < tmp; i++) {
      if (fread(&Elem,sizeof(Elem),1,fh) != 1) {
         ErrReadIndex;
         fclose(fh);
         return TRUE;
      }
      if ((MaxNodelistAge != (time_t)-1) && (NodelistTurnOff != TRUE)) {
         if ((time(NULL) - (NList+i)->Time) > MaxNodelistAge) {
            Log.Level(LOGW) << "Nodelist '" << (NList+i)->Name << "' too old." << EOL;
            Log.Level(LOGI) << "Checking existance in nodelists turned off." << EOL;
            NodelistTurnOff = TRUE;
            Log.Level(LOGD) << "Time  : " << (int) (time(NULL)) << EOL;
            Log.Level(LOGD) << "NTime : " << (int) (NList+i)->Time << EOL;
            Log.Level(LOGD) << "Age   : " << (int) (time(NULL) - (NList+i)->Time) << EOL;
            Log.Level(LOGD) << "MaxAge: " << (int) MaxNodelistAge << EOL;
         }
      }
      if (memcmp(&Elem,NList+i,sizeof(Elem)) != 0) {
         Log.Level(LOGD) << "NodeLists::CompileNeed. memcmp failed. Nodelist changed." << EOL;
         Log.Level(LOGD) << "--Information should be:" << EOL;
         Log.Level(LOGD) << "NName : " << (NList+i)->Name << EOL;
         Log.Level(LOGD) << "NTime : " << (int) (NList+i)->Time << EOL;
         Log.Level(LOGD) << "Zone  : " << (int) (NList+i)->StartZone << EOL;
         Log.Level(LOGD) << "--Information in index file:" << EOL;
         Log.Level(LOGD) << "NName : " << Elem.Name << EOL;
         Log.Level(LOGD) << "NTime : " << Elem.Time << EOL;
         Log.Level(LOGD) << "Zone  : " << Elem.StartZone << EOL;
         IndexChanged;
         fclose(fh);
         return TRUE;
      }
   }
   fclose (fh);
   return FALSE;
}

char *NodeLists::Names(char *Buff) {
NodeListElem *Elem;
int i;
char *tmt;

   Buff[0] = '\0';
   for (Elem = NList, i=0; i < Lists; Elem++, i++) {
      tmt = strrchr(Elem->Name,PATHDELIMC);
      if (tmt != NULL) {
         tmt++;
      } else {
         tmt = Elem->Name;
      }
      strcat(Buff,tmt);
      if (i+1 < Lists) strcat(Buff,", ");
   }
   return Buff;
}

bool NodeLists::Compile(void) {
FILE *fh;
char *tmt;
int tmp;
int i;
// 1  - Write new _empty_ header.
   fh = fopen(IndexName,"wb");
   if (fh == NULL) {
      Log.Level(LOGE) << "Unable to create index file." << EOL;
      return FALSE;
   }
   tmt = (char *) malloc(sizeof(NdlSign) + sizeof(int) + sizeof(NodeListElem)*Lists);
   CheckMem(tmt);
   memset(tmt,'\0',sizeof(NdlSign) + sizeof(int) + sizeof(NodeListElem)*Lists);
   if (fwrite(tmt,sizeof(NdlSign) + sizeof(int) + sizeof(NodeListElem)*Lists,1,fh) != 1) {
      Log.Level(LOGE) << "Unable to write temporary header to index file." << EOL;
      fclose(fh);
      free(tmt);
      return FALSE;
   }
   free(tmt);

// 2  - Write compiled nodelists.

   for (i = 0; i < Lists; i++) {
      if (!ParseOneNodelist(NList + i)) {
         fclose (fh);
         return FALSE;
      }
   }
   if (!FlushNodelist(fh)) {
      fclose(fh);
      return FALSE;
   }

// 3  - Write new, true header.

   if (fseek(fh,0,SEEK_SET) != 0) {
      Log.Level(LOGE) << "Unable to set pointer to the beginning of the index file." << EOL;
      fclose(fh);
      return FALSE;
   }
   tmp = NdlSign;
   if (fwrite(&tmp,sizeof(tmp),1,fh) != 1) {
      Log.Level(LOGE) << "Unable to write a signature to the index file." << EOL;
      fclose(fh);
      return FALSE;
   }
   if (fwrite(&Lists,sizeof(Lists),1,fh) != 1) {
      Log.Level(LOGE) << "Unable to write a Nodelist counter to the index file." << EOL;
      fclose(fh);
      return FALSE;
   }
   for (i=0; i < Lists; i++) {
      if ((MaxNodelistAge != (time_t)-1) && (NodelistTurnOff != TRUE)) {
         if ((time(NULL) - (NList+i)->Time) > MaxNodelistAge) {
            Log.Level(LOGW) << "Nodelist '" << (NList+i)->Name << "' too old." << EOL;
            Log.Level(LOGI) << "Checking of existence in nodelists is turned off." << EOL;
            NodelistTurnOff = TRUE;
            Log.Level(LOGD) << "Age   : " << (int) (time(NULL) - (NList+i)->Time) << EOL;
            Log.Level(LOGD) << "MaxAge: " << (int) MaxNodelistAge << EOL;
         }
      }
      if (fwrite(NList+i,sizeof(NodeListElem),1,fh) != 1) {
         Log.Level(LOGE) << "Unable to write a Nodelist information to the index file." << EOL;
         fclose(fh);
         return FALSE;
      }
   }
   fclose(fh);
   return TRUE;
}
#ifdef _DEBUG

void IPrint(Nch *Ind) {
   if (Ind != NULL) {
      fprintf(stderr,"---%p>",Ind);
      while (Ind->Number != -1) {
         fprintf(stderr," %u",Ind->Number);
         Ind++;
      }
      fprintf(stderr,"\n");
   }
}
#endif
bool NodeLists::LoadOneIndex(FILE *fh, Nch *&Ind) {
unsigned int tmp;
Nch *tmt;
unsigned int i;

   if (fread(&tmp,sizeof(tmp),1,fh) != 1) return FALSE;
   tmt = (Nch *) malloc((tmp+1)*sizeof(Nch));
   CheckMem((char *)tmt);
   memset(tmt,0,(tmp+1)*sizeof(Nch));
   tmt[tmp].Number = (unsigned int) -1;
   for (i = 0; i < tmp; i++) {
      if (fread(&tmt[i].Number,sizeof(int),1,fh) != 1) return FALSE;
   }
   Ind = tmt;
   for (i = 0; i < tmp; i++) {
      if (LoadOneIndex(fh,Ind[i].Sub) == FALSE) return FALSE;
   }
   return TRUE;
}

bool NodeLists::Load(void) {
FILE *fh;
   if (!Enabled() || NodelistTurnOff)
   {
      return TRUE;
   }
   if (CompileNeed())
   {
      if (!Compile())
      {
         if(NodelistTurnOff)
         {
            Log.Level(LOGN) << "Nodelists are not used." << EOL;
            return TRUE;
         }
         return FALSE;
      }
   }
   else
   {
      if(NodelistTurnOff)
      {
         Log.Level(LOGN) << "Nodelists are not used." << EOL;
         return TRUE;
      }
   }
   fh = fopen(IndexName,"rb");
   if (fh == NULL) {
      Log.Level(LOGE) << "Unable to open index file." << EOL;
      return FALSE;
   }
   if (fseek(fh,sizeof(NdlSign) + sizeof(int) + sizeof(NodeListElem)*Lists,SEEK_SET) != 0) {
      Log.Level(LOGE) << "Unable to seek in index file." << EOL;
      return FALSE;
   }
   if (!LoadOneIndex(fh,Index)) {
      Log.Level(LOGE) << "Unable to load index file." << EOL;
      return FALSE;
   }
   fclose(fh);
   return TRUE;
}

Nch *NodeLists::Srch(Nch *Addr, unsigned int Number) {
   if (Addr == NULL) return NULL;
   while (Addr->Number != (unsigned int)-1) {
      if ((Addr->Number & 0xffff) == (Number & 0xffff)) {
         return Addr;
      }
      Addr++;
   }
   return NULL;
}

unsigned int NodeLists::FindHub(FA const &f) {
Nch *tmt;
unsigned int currHub=0;
// If nodelists are switched off or it is necesary to say that a node exists
// then return A_HOST for any address.
// In other parts of this program compare return value of this
// function only with (-1).

   if (NodelistTurnOff)
    return 0;

  if (ExistInNodelist(f) != (unsigned int)-1)
  {
   tmt = Srch(Index,f.Zone() & 0xffff);
   if (tmt == NULL) 
    return 0;

   tmt = tmt->Sub;
   tmt = Srch(tmt,f.Net() & 0xffff);
   if (tmt == NULL)
    return 0;
   if (f.Node() == 0)
    return 0;
   tmt = tmt->Sub;
   while ((tmt->Number & 0xffff) != (f.Node() & 0xffff))
   {
    if ((tmt->Number & A_MASK) == A_HUB)
     currHub=tmt->Number;
    if ( ( ((tmt+1)->Number & 0xffff) == (f.Node() & 0xffff)) && (((tmt+1)->Number & A_MASK) == A_HUB ))
     currHub=(tmt+1)->Number;
    tmt++;
   }
  }
  if (currHub != 0) 
   currHub = currHub & 0xffff;
  return currHub;  
}

unsigned int NodeLists::ExistInNodelist(FA const &f) {
Nch *tmt;
// If nodelists are switched off or it is necesary to say that a node exists
// then return A_HOST for any address.
// In other parts of this program compare return value of this
// function only with (-1).

   if (NodelistTurnOff) {
      return (A_HOST);
   }
   tmt = Srch(Index,f.Zone() & 0xffff);
   if (tmt == NULL) return ((SoftCheckInNodelists == FALSE) ? (unsigned int)-1 : A_HOST);

   tmt = tmt->Sub;
   tmt = Srch(tmt,f.Net() & 0xffff);
   if (tmt == NULL) return ((SoftCheckInNodelists == FALSE) ? (unsigned int)-1 : A_HOST);
   if (f.Node() == 0) {
      return A_HOST;
   }
   tmt = tmt->Sub;
   tmt = Srch(tmt,f.Node() & 0xffff);
   if (tmt == NULL) {
      return (unsigned int)-1;
   }
   if ((f.Point() & 0xffff) != 0) {
      switch (CheckPoints) {
         case CHECKPNT_HARD:
            if (Srch(tmt->Sub,f.Point() & 0xffff) == NULL) {
               return (unsigned int)-1;
            }
            break;
         case CHECKPNT_SOFT:
            if (tmt->Sub == NULL) break;
            if (tmt->Sub->Number == (unsigned int)-1) break;
            if (Srch(tmt->Sub,f.Point() & 0xffff) == NULL) return (unsigned int)-1;
            break;
         case CHECKPNT_NEVER:
            break;
      }
   }
   return tmt->Number;
}

unsigned int NodeLists::GetFlags(FA const &f) {
Nch *tmt;
   if (NodelistTurnOff) {
      return (A_NONE);
   }
   tmt = Srch(Index,f.Zone() & 0xffff);
   if (tmt == NULL) return A_NONODE;

   tmt = tmt->Sub;
   tmt = Srch(tmt,f.Net() & 0xffff);
   if (tmt == NULL) return A_NONODE;
   if (f.Node() == 0) {
      return A_HOST;
   }
   tmt = tmt->Sub;
   tmt = Srch(tmt,f.Node() & 0xffff);
   if (tmt == NULL) {
      return A_NONODE;
   }
   return tmt->Number;
}

void SayNodelistFlags(FA const &f) {
unsigned int i;
   i = Ndl.GetFlags(f);
   if (i == A_NONODE) {
      Log.Level(LOGD) << "NONODE";
      return;
   }
   i &= A_MASK;
   if (i == A_DOWN) Log.Level(LOGD) << "DOWN";
   if (i == A_HOLD) Log.Level(LOGD) << "HOLD";
   if (i == A_HUB) Log.Level(LOGD) << "HUB";
   if (i == A_HOST) Log.Level(LOGD) << "HOST";
   if (i == A_PVT) Log.Level(LOGD) << "PVT";
   if (i == A_REGION) Log.Level(LOGD) << "REGION";
}

bool NodeLists::InSubHubs(FA const &Addr, FA const &Mask) {
Nch *tmt;
bool Existing;
// If the node used as a mask is in the nodelist and it is a hub or host
// then check if the Addr belongs to the "subhub" list of nodes linked in
// the nodelist to the hub or to the host. Otherwise check a point.
// And there is a mess with regions. Blast them thrice together with
// those who developed Fidonet standards.

   Existing = (ExistInNodelist(Addr) == (unsigned int) -1 ? FALSE : TRUE);
// Node is equal Mask?
   if ((Addr.Zone() & 0xffff) == (Mask.Zone() & 0xffff) &&
       (Addr.Net() & 0xffff) == (Mask.Net() & 0xffff) &&
       (Addr.Node() & 0xffff) == (Mask.Node() & 0xffff)) {
      if ((Addr.Point() & 0xffff) != 0) {
         return (Existing);
      }
      return TRUE;
   }
   if (Existing == FALSE) return FALSE;

// Is the node in the same zone?
   if ((Addr.Zone() & 0xffff) != (Mask.Zone() & 0xffff)) return FALSE;

// Search the zone of mask.
   tmt = Srch(Index,Mask.Zone() & 0xffff);
   if (tmt == NULL) {
//      Log.Level(LOGD) << "Zone " << (Mask.Zone() & 0xffff) << " missing" << EOL;
      return FALSE;
   }
   tmt = tmt->Sub;
   if (tmt == NULL) {
//      Log.Level(LOGD) << "Zone " << (Mask.Zone() & 0xffff) << " Empty" << EOL;
      return FALSE;
   }

// Search the Net of mask.
   tmt = Srch(tmt,Mask.Net() & 0xffff);
   if (tmt == NULL) {
//      Log.Level(LOGD) << "Net " << (Mask.Zone() & 0xffff) << ":" << (Mask.Net() & 0xffff) << " missing" << EOL;
      return FALSE;
   }
   if ((tmt->Number & A_MASK) == A_REGION) {
      if ((Mask.Node() & 0xffff) == 0) {
         // Mask to region. Search net.
         while (tmt->Number != (unsigned int) -1) {
            if ((tmt->Number & 0xffff) == (Addr.Net() & 0xffff)) {
               // The net is found. Search node.
               tmt = tmt->Sub;
               if (tmt == NULL) return FALSE;
               if ((Addr.Node() & 0xffff) == 0) return TRUE;
               if (Srch(tmt,Addr.Node() & 0xffff) == NULL) {
                  return FALSE;
               } else {
                  return TRUE;
               }
            }
            tmt++;
            if ((tmt->Number & A_MASK) == A_REGION) {
               // Next region began but net was not found...
               return FALSE;
            }
         }
         return FALSE;
      }
   }
   if ((Addr.Net() & 0xffff) != (Mask.Net() & 0xffff)) {
//      Log.Level(LOGD) << "Node " << Addr << " not equal to mask " << Mask << " and mask is not a regional mask." << EOL;
      return FALSE;
   }
   tmt = tmt->Sub;
   if (tmt == NULL) {
//      Log.Level(LOGD) << "Node " << Addr << " not equal to mask " << Mask << " and no nodes in mask net." << EOL;
      return FALSE;
   }
   // If the mask is a HOST then the beginning has already been found.
   // Otherwise continue the search.
   if ((Mask.Node() & 0xffff) != 0) {
      tmt = Srch(tmt,Mask.Node() & 0xffff);
      if (tmt == NULL) return FALSE;
      // if Mask is not a hub - leave.
      if ((tmt->Number & A_MASK) != A_HUB) return FALSE;
      tmt++;
   }
   // Ok. We have the beginning of the list.
   // Search the node down to a hub or to the end of the list.
   while (tmt->Number != (unsigned int) -1 && (tmt->Number & A_MASK) != A_HUB) {
      if ((tmt->Number & 0xffff) == (Addr.Node() & 0xffff)) {
         return Existing;
      }
      tmt++;
   }
   return FALSE;
}

int NodeLists::AddNodelist(char *tmt, int TempZone) {
char Buff[512];
struct stat NdlStat;
NodeListElem *Elem;

   memset(Buff,0,512);
   if (strlen(tmt) == 0) {
      yyerror("Missing parameter: nodelist name or mask.");
      return (-1);
   }
   if ((TempZone <= 0) && (TempZone != -3)) {
      yyerror("Zone number must be between 1 and 65535");
      return (-1);
   }
   if (TempZone != -3) {
      StartZone = TempZone;
   } else {
      StartZone = 0;
   }

   if (FindNodelist(tmt,Buff) != 0) {
      return (-1);
   }
   if (stat(Buff,&NdlStat) != 0) {
      Log.Level(LOGE) << "Unable to get information about nodelist '" << Buff << "'." << EOL;
      return (-1);
   }
   Elem = (NodeListElem *) malloc(sizeof(NodeListElem)+100);
   CheckMem((char *)Elem);
   memcpy(Elem->Name,Buff,512);
   Elem->Time = NdlStat.st_mtime;
   Elem->StartZone = StartZone;
   Log.Level(LOGD) << "NTime : " << (int) Elem->Time << EOL;
   if (NList == NULL) {
      NList = Elem;
      Lists = 1;
   } else {
      tmt = (char *) realloc(NList, (Lists + 1) * sizeof(NodeListElem));
      CheckMem((char *)tmt);
      NList = (NodeListElem *)tmt;
      memcpy(NList + Lists,Elem,sizeof(NodeListElem));
      Lists++;
      free(Elem);
   }
   return (0);
}

// --------------------------------------------------------------------

int SetMaxNodelistAge(int tmt) {

   if (MaxNodelistAge != (time_t)-1) {
      yyerror("Max nodelists age already set.");
      return(-1);
   }
   if (tmt < 1) {
      yyerror("Parameter must be a number greater than 0.");
      return (-1);
   }
   MaxNodelistAge = tmt * 24 * 60 * 60;
   return 0;
}

// --------------------------------------------------------------------

int SetNodelist(char *tmt, int TempZone) {
   return Ndl.AddNodelist(tmt,TempZone);
}
