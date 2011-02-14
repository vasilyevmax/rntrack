/*
 *  RNtrack - FTN message tracker/router
 *
 *  pktbase.cpp - Work with *.PKT base
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
#else
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#endif                                                                                                          

#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <assert.h>
#include <errno.h>

#include "constant.hpp"
#include "vars.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "pktbase.hpp"
#include "badpkt.hpp"
#include "passwd.hpp"
#include "aka.hpp"
#include "configure.hpp"
#include <smapi/msgapi.h>
#include <smapi/progprot.h>
#include "tpkt.hpp"
#ifdef _AIX_CONV
#include "aix_conv.hpp"
#endif
// ---------------------------

typedef struct {
   word FromNode;
   word ToNode;
   word FromNet;
   word ToNet;
   word Attr;
   word Cost;
   char               DateTime[20];
} tPMSG;                                                                                                        

PKTBASE::PKTBASE() {
   DirName = NULL;
   PktName = NULL;
   fNoCheckPwd = FALSE;
   fh = NULL;
   MsgMask = NULL;
   MsgNum = 0;
   MaxMsgNum = 0;
   dp = NULL;
   fForWrite = FALSE;
   fCreated = FALSE;
}

PKTBASE::~PKTBASE() {
   Clear();
}
// ---------------------------

void PKTBASE::AddToMask(unsigned int Num) {
   if (Num > MaxMsgNum) {
      MsgMask = (char *) realloc(MsgMask,Num+1);
      CheckMem(MsgMask);
      MaxMsgNum++;
      while (MaxMsgNum != Num) {
         MsgMask[MaxMsgNum++] = 1;
      }
   }
   MsgMask[Num] = 1;
}

// ---------------------------

bool PKTBASE::CopyHeader(FILE *tf) {
tPKTH PKTH;

   if (fread(&PKTH,sizeof(tPKTH),1,fh) != 1) {
      Log.Level(LOGE) << "   Error reading PKT header '" << PktName << "'." << EOL;
      return FALSE;
   }

// Removed by UFM. At this point transformation of pkt header is not necessary.
//#ifdef _AIX_CONV
//    AIXConvPKTH(PKTH);
//#endif

   if (fwrite(&PKTH,sizeof(tPKTH),1,tf) != 1) {
      Log.Level(LOGE) << "   Error writing PKT header." << EOL;
      return FALSE;
   }
   return TRUE;
}

// ---------------------------

bool PKTBASE::CopyTail(FILE *tf) {
char Buffer[10240];
int rc;

   while(!feof(fh)) {
      if ((rc = fread(Buffer,1,10240,fh)) != 10240) {
         if (!feof(fh)) {
            Log.Level(LOGE) << "   Error reading tail of PKT." << EOL;
            return FALSE;
         }
      }

      if (fwrite(Buffer,1,rc,tf) != (unsigned) rc) {
         Log.Level(LOGE) << "   Error writing tail of PKT." << EOL;
         return FALSE;
      }
   }
   return TRUE;
}
// ---------------------------

#define READBLOCKLEN  4096

bool PKTBASE::CopyOneMessage(FILE *tf) {
char *Buff;
int I,i;

   Buff = (char *)malloc(sizeof(tPMSG)+256);
   CheckMem(Buff);
   if (LogLevel >= 5) {
      Log.Level(LOGD) << "...Current file position " << (int) ftell(fh) << EOL;
   }
   I = 0;
   if (fread(&I,2,1,fh) != 1) {
      free(Buff);
      Log.Level(LOGE) << "   Error: Unable to read packed message header." << EOL;
      return FALSE;
   }

   Log.Level(LOGD) << "...Message signature: " << I << EOL;
   if (I != 2) {
      Log.Level(LOGE) << "   Error: Missing 0200 at the beginning of the message." << EOL;
      free(Buff);
      return FALSE;
   }
   if (!ReadHeader(fh,Buff)) {
      free(Buff);
      Log.Level(LOGE) << "   Error: Unable to read packed message header." << EOL;
      return FALSE;
   }

   I = sizeof(tPMSG);
   for (i = 0; i < 3; i++) {
      do {
         if (fread(Buff+I,1,1,fh) != 1) {
            return FALSE;
         }
         I++;
      } while(Buff[I-1] != '\0');
   }
   do {
      Buff = (char *)realloc(Buff,I + READBLOCKLEN + 2);
      CheckMem(Buff);
      memset(Buff+I,0,READBLOCKLEN + 1);
      for (i = 0; i < READBLOCKLEN; i++) {
         if (fread(Buff+I,1,1,fh) != 1) {
            Log.Level(LOGE) << "   Error reading body of the message." << EOL;
            free(Buff);
            return FALSE;
         }
         I++; 
         if (Buff[I-1] == '\0') break;
      }
   } while(Buff[I-1] != '\0');
   if (tf != NULL) {
      i = 2;
      if (fwrite(&i,2,1,tf) != 1) {
         Log.Level(LOGE) << "   Error writing copy of the signature." << EOL;
         free(Buff);
         return FALSE;
      }
      if (fwrite(Buff,I,1,tf) != 1) {
         Log.Level(LOGE) << "   Error writing copy of the message." << EOL;
         free(Buff);
         return FALSE;
      }
   }
   free(Buff);
   return TRUE;
}

// ---------------------------

bool PKTBASE::CopyMessages(FILE *tf) {
uint Num;

   for(Num = 1; Num <= MaxMsgNum; Num++) {
      if (MsgMask[Num] == 0) {
         if (!CopyOneMessage(NULL)) return FALSE;
      } else {
         if (!CopyOneMessage(tf)) return FALSE;
      }
   }
   return TRUE;
}
// ---------------------------

bool PKTBASE::_Close(void) {
uint Num;
char TempName[BUFF_SIZE];
char *tmt;
FILE *tf;

   Log.Level(LOGD) << "_Close PKT '" << PktName << "'" << EOL;
   Log.Level(LOGD) << "MaxMsgNum: " << MaxMsgNum << EOL;
   if (fh == NULL) {
      MsgNum = 0;
      MaxMsgNum = 0;
      Log.Level(LOGD) << "...Handle is NULL. Do nothing." << EOL;
      return TRUE;
   }

   Log.Level(LOGD) << "...Handle is not NULL" << EOL;

   if (MaxMsgNum == 0) {
      if (!fCreated) {
         fclose(fh);
         fh = NULL;
         if (BadPktMode == EXIT)
          return FALSE;
         BadPkt(PktName);
         MsgNum = 0;
         return TRUE;
      } else {
         fclose(fh);
         fh = NULL;
         unlink(PktName);
         MsgNum = 0;
         MaxMsgNum = 0;
         return TRUE;
      }
   }
   if (LogLevel >= 5) {
      Log.Level(LOGD) << "...MaxMsgNum <> 0" << EOL;
      for(Num = 1; Num <= MaxMsgNum; Num++) {
         Log.Level(LOGD) << " " << (int) MsgMask[Num];
      }
      Log.Level(LOGD) << EOL;
   }

   for(Num = 1; Num <= MaxMsgNum; Num++) {
      if (MsgMask[Num] != 0) break;
   }
   if (Num > MaxMsgNum) {
      fclose(fh);
      fh = NULL;
      unlink(PktName);
      MsgNum = 0;
      MaxMsgNum = 0;
      return TRUE;
   }
   Log.Level(LOGD) << "...not deleted messages exist in the PKT" << EOL;
   for(Num = 1; Num <= MaxMsgNum; Num++) {
      if (MsgMask[Num] == 0) break;
   }

   if (Num > MaxMsgNum ) {
      fclose(fh);
      MsgNum = 0;
      MaxMsgNum = 0;
      fh = NULL;
      return TRUE;
   }

   Log.Level(LOGD) << "..._deleted_ messages exist in the PKT" << EOL;
   if (fseek(fh,0L,SEEK_SET) != 0) {
      fclose(fh);
      fh = NULL;
      MsgNum = 0;
      MaxMsgNum = 0;
      Log.Level(LOGE) << "   Unable to seek to the beginning of the PKT file." << EOL;
      if (BadPktMode == EXIT)
       return FALSE;
      BadPkt(PktName);
      MsgNum = 0;
      return TRUE;      
   }

   Log.Level(LOGD) << "...the seek to the beginning is completed" << EOL;
   RSTRLCPY(TempName,PktName,BUFF_SIZE);
   tmt = strrchr(TempName,PATHDELIMC);
   if (tmt == NULL) {
#ifndef __unix__
      tmt = strchr(TempName,':');
      if (tmt != NULL) {
         tmt++;
      } else {
#endif      
         tmt = TempName;
#ifndef __unix__     
      }
#endif      
   } else {
      tmt++;
   }
   *tmt = '\0';
   RSTRLCAT(TempName,"TPKT.FTR",BUFF_SIZE);

   Log.Level(LOGD) << "...Temporary file: '" << TempName << "'" << EOL;
   tf = fopen(TempName,"w+b");
   if (tf == NULL) {
      Log.Level(LOGE) << "   Unable to create temporary file." << EOL;
      fclose(fh);
      fh = NULL;
      MsgNum = 0;
      MaxMsgNum = 0;
      return FALSE;
   }

   Log.Level(LOGD) << "...Temporary file created." << EOL;
   if (!CopyHeader(tf)) {
      fclose(fh);
      fclose(tf);
      fh = NULL;
      unlink(TempName);
      MsgNum = 0;
      MaxMsgNum = 0;
      return FALSE;
   }

   Log.Level(LOGD) << "...Copying header of PKT completed." << EOL;
   if (!CopyMessages(tf)) {
      Log.Level(LOGD) << "ERROR: can't copy messages." << EOL;
      fclose(fh);
      fclose(tf);
      fh = NULL;
      unlink(TempName);
      MsgNum = 0;
      MaxMsgNum = 0;
      return FALSE;
   }

   Log.Level(LOGD) << "...Copying messages completed." << EOL;
   if (!CopyTail(tf)) {
      fclose(fh);
      fclose(tf);
      fh = NULL;
      unlink(TempName);
      MsgNum = 0;
      MaxMsgNum = 0;
      return FALSE;
   }

   Log.Level(LOGD) << "...Copying tail completed." << EOL;
   MsgNum = 0;
   MaxMsgNum = 0;
   fclose(fh);
   fclose(tf);
   fh = NULL;
   Log.Level(LOGD) << "...Handles closed." << EOL;

   unlink(PktName);
   if (rename(TempName,PktName) != 0) {
      Log.Level(LOGE) << "   Unable to rename temporary file to PKT." << EOL;
      if (BadPktMode == EXIT)
       return FALSE;
       BadPkt(TempName);
       return TRUE;
   }
   return TRUE;
}

// ---------------------------

void PKTBASE::Clear(void) {
   _Close();
   fNoCheckPwd = FALSE;
   fForWrite = FALSE;
   fCreated = FALSE;
   if (dp != NULL) {
      closedir(dp);
      dp = NULL;
   }
   if (DirName != NULL) {
      free(DirName);
      DirName = NULL;
   }
   if (PktName != NULL) {
      free(PktName);
      PktName = NULL; 
   }
   if (MsgMask != NULL) {
      free(MsgMask);
      MsgMask = NULL;
   }
}

// ---------------------------

bool PKTBASE::Set(char *Dir, int BaseType) {
char *tmt;
char *Buff;
struct stat dd;

   Clear();
   if (*Dir != '#') return FALSE;
   if (BaseType == BASE_OUT) {
//      CfgError("You can't save to or rewrite in *.PKT base.");
      return FALSE;
   }

   if (*(Dir+1) == '#') {
      fNoCheckPwd = TRUE;
      Dir++;
   }

   Buff = strdup(Dir+1);
   CheckMem(Buff);
   tmt = strrchr(Buff,'!');
   if (tmt == NULL) {
      tmt = "*";
   } else {
      *tmt = '\0';
      tmt++;
   }
   Log.Level(LOGD) << "PKTBASE FTN Mask: '" << tmt << "'" << EOL;
   FMask.Parse(tmt);
   if (!FMask.PKTValid()) {
      free(Buff);
      return FALSE;
   }
   if (stat(dirslashbug(Buff),&dd) != 0 && BaseType != BASE_OUT) {
      free(Buff);
      return FALSE;
   }
   if (S_ISDIR(dd.st_mode) && BaseType != BASE_OUT) {
      DirName = strdup(Buff);
      CheckMem(DirName);
      if (DirName[strlen(DirName)] == PATHDELIMC) {
         DirName[strlen(DirName)] = '\0';
      }
      Log.Level(LOGD) << "PKTBASE DirName: '" << DirName << "'" << EOL;
   } else if (S_ISREG(dd.st_mode) && BaseType != BASE_OUT) {
      PktName = strdup(Buff);
      CheckMem(PktName);
      Log.Level(LOGD) << "PKTBASE PktName: '" << PktName << "'" << EOL;
   } else if (BaseType == BASE_OUT) {
      PktName = strdup(Buff);
      CheckMem(PktName);
      Log.Level(LOGD) << "PKTBASE_OUT PktName: '" << PktName << "'" << EOL;
   } else {
      Log.Level(LOGD) << "No one type" << EOL;
      free(Buff);
      return FALSE;
   }
   if (BaseType == BASE_OUT) {
      fForWrite = TRUE;
   }
   free(Buff);
   return TRUE;
}

// ---------------------------

bool PKTBASE::Next(void) {
int SIGN;
char Buff[1024];
struct dirent *de;

   Log.Level(LOGD) << "----- PKTBASE::Next() -----" << EOL;
   SIGN = 0;
   MsgNum++;
   if (fh != NULL) {
      Log.Level(LOGD) << "PKTBASE::Next(). fh != NULL" << EOL;
      if (fread(&SIGN,2,1,fh) != 1) {
         Log.Level(LOGE) << "   Error: Unable to read signature from PKT '" << PktName << "'" << EOL;
         fclose (fh);
         fh = NULL;
     if (BadPktMode == EXIT)
          return FALSE;
         BadPkt(PktName);
         return TRUE;
      }
   }
#ifdef _AIX_CONV
    SIGN=RotateInt(SIGN);
#endif
   Log.Level(LOGD) << "PKTBASE::Next(). SIGN == " << SIGN << EOL;
   if (SIGN == 0) {
      if (!_Close()) {
         return FALSE;
      }

      if (dp == NULL) return FALSE;

      Log.Level(LOGD) << "PKTBASE::Next(). dp != NULL"  << EOL;
      Buff[0] = '\0';
      while ((de = readdir(dp)) != NULL) {
         Log.Level(LOGD) << "PKTBASE::Next(). de->d_name == '" << de->d_name << "'" << EOL;
         if (fsCompareName(de->d_name,"*.[Pp][Kk][Tt]") != 0) {
        sprintf(Buff,"%s"PATHDELIMS"%s",DirName,de->d_name);
        break;
     }
      }
      if (Buff[0] == '\0') {
         Log.Level(LOGD) << "No more files from ReadDir in Next." << EOL;
         closedir(dp);
         dp = NULL;
         return FALSE;
      }

      Log.Level(LOGD) << "New PKT == '" << Buff << "'" << EOL;
      if (PktName != NULL) {
         free(PktName);
      }
      PktName = strdup(Buff);
      if (!_Open()) return FALSE;
      MsgNum = 0;
      return (Next());
   } else if (SIGN != 2) {
      Log.Level(LOGE) << "   Error: Wrong signature in PKT '" << PktName << "'" << EOL;
      fclose (fh);
      fh = NULL;
      if (BadPktMode == EXIT)
       return FALSE;
      BadPkt(PktName);
      MsgNum = 0;
      return TRUE;
   }
   return TRUE;
}

// ---------------------------

bool PKTBASE::_Open(void) {
tPKTH PKTH;
FA f;
char Buff[4096];
char *tmt;
s_stat tmp_stat;

   if (PktName == NULL) {
      return TRUE;
   }
   
   if (MaxPktSize != 0)
   {
    if (!stat(PktName,&tmp_stat))
    {
     if ((uint)tmp_stat.st_size > MaxPktSize)
     {
      Log.Level(LOGE) << "   Error: size of PKT '" << PktName << "' is " << (uint)tmp_stat.st_size << " (" << MaxPktSize << " allowed)." << EOL;
      if (BadPktMode == EXIT)
       return FALSE;
      BadPkt(PktName);
      return TRUE;
     }
    } 
   }

   Log.Level(LOGD) << "_Open PKT '" << PktName << "'" << EOL;
   if (!_Close()) return FALSE;
   fh = fopen(PktName,"r+b");
#ifdef __unix__
   if (errno == EACCES) {
      Log.Level(LOGE) << "   Error _open PKT '" << PktName << "' - permission denied." << EOL;
      return TRUE;
   }
#endif
   if (fh == NULL && !fForWrite) {
      Log.Level(LOGE) << "   Error _open PKT '" << PktName << "'." << EOL;
      return TRUE;
   }
   if (fh == NULL && fForWrite) {
      Log.Level(LOGE) << "   Error _open PKT '" << PktName << "'." << EOL;
      return TRUE;
   }
   if (fread(&PKTH,sizeof(tPKTH),1,fh) != 1) {
      Log.Level(LOGE) << "   Error reading PKT header." << EOL;
      fclose(fh);
      fh = NULL;
      if (BadPktMode == EXIT)
       return FALSE;
      BadPkt(PktName);
      MsgNum = 0;
      return TRUE;
   }
#ifdef _AIX_CONV
   AIXConvPKTH(PKTH);
#endif
   if (PKTH.c0002 != 2 || ((PKTH.c0001 != 0 && PKTH.c0100 != 0) && (PKTH.c0001 != 1 && PKTH.c0100 != 256))) {
      Log.Level(LOGD) << "   " << (uint) PKTH.c0002 << " " << (uint) PKTH.c0001 << " " << (uint) PKTH.c0100 << EOL;
      Log.Level(LOGE) << "   Error: destroyed header or unknown PKT format in PKT '" << PktName << "'" << EOL;
      fclose(fh);
      fh = NULL;
      if (BadPktMode == EXIT)
       return FALSE;
      BadPkt(PktName);
      MsgNum = 0;
      return TRUE;
   }
   f.Zone(PKTH.FromZone);
   if (PKTH.FromNet == 0xffff) {
      f.Net(PKTH.AuxNet);
      f.Point(PKTH.FromPoint);
   } else {
      f.Net(PKTH.FromNet);
      f.Point(PKTH.FromPoint);
   }
   f.Node(PKTH.FromNode);
   Log.Level(LOGD) << "PKT from: " << f << EOL;

   if (f != FMask) {
      fclose(fh);
      fh = NULL;
      Log.Level(LOGW) << "Sender of PKT '" << PktName << "' does not match with " << FMask << EOL;
      return TRUE;
   }
   if (!fNoCheckPwd) {
      tmt = GetPasswd(f);
      if (tmt == NULL) tmt = "\0";
      memset(Buff,0,9);
      RSTRLCPY(Buff,PKTH.Passwd,8);
      if (stricmp(Buff,tmt) != 0) {
         Log.Level(LOGW) << "Wrong password in PKT '" << PktName << "'" << EOL;
         Log.Level(LOGW) << "Should be '" << tmt << "'. In PKT '" << Buff << "'" << EOL;
         fclose(fh);
         fh = NULL;
     if (BadPktMode == EXIT)
          return FALSE;
         BadPkt(PktName);
         MsgNum = 0;
         return TRUE;      
      }
   }

   MsgNum = 0;
   return TRUE;
}

// ---------------------------

bool PKTBASE::Rewind(void) {

   Log.Level(LOGD) << "------ Rewind for *.PKT --------" << EOL;
   if (!_Close()) return FALSE;
   Log.Level(LOGD) << "------ _Close OK. --------" << EOL;
   if (dp != NULL) {
      closedir(dp);
      dp = NULL;
   }
   Log.Level(LOGD) << "PKTBASE::Rewind(). DirName == '" << (DirName == NULL ? "(NULL)" : DirName) << "'" << EOL;
   if (DirName != NULL) {
      dp = opendir(dirslashbug(DirName));
      if (dp == NULL) {
         Log.Level(LOGD) << "Null from OpenDir." << EOL;
         return FALSE;
      }
   }
   if (!_Open()) return FALSE;
   if (!Next()) return FALSE;
   return TRUE;
}

// ---------------------------

bool PKTBASE::Renumber(void) {
   return TRUE;
}

// ---------------------------

bool PKTBASE::DeleteMsg(void) {
   MsgMask[MsgNum] = 0;
   return TRUE;
}

// ---------------------------

char *PKTBASE::ReadToMem(void) {
   return NULL;
}

// ---------------------------

char *PKTBASE::MessageName(void) {
static char Buff[2048];

   RSTRLCPY(Buff,"#",2048);
   RSTRLCAT(Buff,PktName,2048);
   sprintf(Buff+strlen(Buff),":%u",MsgNum);
   return Buff;
}

// ---------------------------

bool PKTBASE::WriteFromMem(char *Buff) {
   CHP = 537;
   CHP = 538;
   if (Buff != NULL) *Buff = *Buff;
   return FALSE;
}

// ---------------------------
// MHM fix: HTML2FIDO v 1.1.33 is known to produce non-FTSC0001 compliant
// messages (where the date occupies less than 20 characters). We fix it here.

bool PKTBASE::ReadHeader(FILE *tf, char *Buff) {
int i, c;

   if (fread(Buff,sizeof(tPMSG)-20,1,tf) != 1) {
      return FALSE;
   }
   Buff+=sizeof(tPMSG)-20;
   RSTRLCPY(Buff, "14 Dec 90  12:00:00",20); // Innocent date
   for (i=0; i < 20; i++) {
      c = fgetc(tf);
      if (c==EOF)
         return FALSE;
      if (c=='\0')
         break;
      *Buff++ = c;
   }
   return TRUE;
}

// ---------------------------

bool PKTBASE::ReadMsg(cMSG &m) {
tPMSG p;
char *Buff;
uint i, I;

   CHP = 639;
   m.Clear();
   if (fh == NULL) {
      return FALSE;
   }

   CHP = 640;
   if (!ReadHeader(fh,(char *)&p)) {
      if (feof(fh) != 0) {
         Log.Level(LOGE) << "   Warning: New message, but EOF found in PKT '" << PktName << "'." << EOL;
         return FALSE;
      }
      Log.Level(LOGE) << "   Error: Unable to read message header from PKT '" << PktName << "'." << EOL;
      return FALSE;
   }
   p.DateTime[19] = '\0';
   CHP = 641;
#ifdef _AIX_CONV
   p.FromNode=RotateShort(p.FromNode);
   p.ToNode=RotateShort(p.ToNode);
   p.FromNet=RotateShort(p.FromNet);
   p.ToNet=RotateShort(p.ToNet);
   p.Cost=RotateShort(p.Cost);
   p.Attr=RotateShort(p.Attr);
#endif
   m._FromAddr.Node(p.FromNode);
   m._ToAddr.Node(p.ToNode);
   m._FromAddr.Net(p.FromNet);
   m._ToAddr.Net(p.ToNet);
   m._Cost = p.Cost;
   m._Time = ToTime(p.DateTime);
   
   SetMsgAttr(p.Attr,m);
   CHP = 642;
   for(i = 0; i < 36; i++) {
      if (fread(m._ToName+i,1,1,fh) != 1) {
         Log.Level(LOGE) << "   Error: Unable to read message header (ToName) from PKT '" << PktName << "'" << EOL;
         return FALSE;
      }
      if (m._ToName[i] == '\0') break;
   }
   CHP = 643;

   for(i = 0; i < 36; i++) {
      if (fread(m._FromName+i,1,1,fh) != 1) {
         Log.Level(LOGE) << "   Error: Unable to read message header (FromName) from PKT '" << PktName << "'" << EOL;
         return FALSE;
      }
      if (m._FromName[i] == '\0') break;
   }
   CHP = 644;

   for(i = 0; i < 72; i++) {
      if (fread(m._Subject+i,1,1,fh) != 1) {
         Log.Level(LOGE) << "   Error: Unable to read message header (Subject) from PKT '" << PktName << "'" << EOL;
         return FALSE;
      }
      if (m._Subject[i] == '\0') break;
   }

   CHP = 645;
   I = 0;
   Buff = NULL;
   do {
      CHP = 6451;
      Buff = (char *)realloc(Buff,I + READBLOCKLEN + 2);
      CHP = 6452;
      CheckMem(Buff);
      CHP = 6453;
      memset(Buff+I,0,READBLOCKLEN + 1);
      CHP = 6454;
      for (i = 0; i < READBLOCKLEN; i++) {
         CHP = 6455;
         if (fread(Buff+I,1,1,fh) != 1) {
            Log.Level(LOGE) << "   Error reading body of message." << EOL;
            free(Buff);
            return FALSE;
         }
         CHP = 6456;
         I++; 
         if (Buff[I-1] == '\0') break;
         CHP = 6457;
      }
   } while(Buff[I-1] != '\0');
   
/*   if (MaxMsgSize != 0)
   {
    if (I > MaxMsgSize)
    {
     Log.Level(LOGE) << "   Error: size of MSG body from '" << PktName << "' is " << I << " (" << MaxMsgSize << " allowed)." << EOL;
     free(Buff);      
     return FALSE;
    }
   }
  */ 
   CHP = 646;
   m.ParseMem(Buff);
   CHP = 647;
   free(Buff);
   CHP = 648;
   AddToMask(MsgNum);
   CHP = 649;
   return TRUE;
}

// ---------------------------

bool PKTBASE::WriteOneMsg(unsigned int Num, cMSG &m) {
   if (&m != NULL)Num++;

   return FALSE;
}

// ---------------------------

bool PKTBASE::WriteMsg(cMSG &m) {
   return WriteOneMsg(MsgNum,m);
}

// ---------------------------

bool PKTBASE::WriteNewMsg(cMSG &m) {
   return WriteOneMsg(MsgNum,m);
}

// ---------------------------

void PKTBASE::Print(void) {
}

// ---------------------------

bool PKTBASE::CheckOut(void) {
struct stat dd;

   yyerror("You can't save to or rewrite in *.PKT base.");
   return FALSE;

   fForWrite = TRUE;
   if (PktName == NULL) {
      yyerror("Base can't be a directory.");
      return FALSE;
   }
   if (stat(dirslashbug(PktName),&dd) == 0) {
      if (S_ISDIR(dd.st_mode)) {
         yyerror("Base can't be a directory.");
         return FALSE;
      }
   }
   if (!FMask.Valid() || FMask.Masked()) {
      yyerror("Address should be full and without any masks.");
      return FALSE;
   }
   return FALSE;
}

// ---------------------------

char *PKTBASE::BaseName(void) {
static char Buff[BUFF_SIZE];
   RSTRLCPY(Buff,"#",BUFF_SIZE);
   if (fNoCheckPwd) RSTRLCAT(Buff,"#",BUFF_SIZE);
   if (DirName != NULL) {
      RSTRLCAT(Buff,DirName,BUFF_SIZE);
   } else {
      RSTRLCAT(Buff,PktName,BUFF_SIZE);
   }
   RSTRLCAT(Buff,"!",BUFF_SIZE);
   RSTRLCAT(Buff,FMask.ToStr(),BUFF_SIZE);
   return Buff;
}
