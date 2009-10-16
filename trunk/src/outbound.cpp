/*
 *  RNtrack - FTN message tracker/router
 *
 *  outbound.cpp - Work with outbound
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <ctype.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "parsetpl.hpp"
#include "fidoaddr.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "pktbase.hpp"
#include "attach.hpp"
#include "aka.hpp"
#include "passwd.hpp"
#include "outbound.hpp"
#include "filebox.hpp"
#include "mytypes.hpp"
#include <smapi/msgapi.h>
#include <smapi/progprot.h>
#include "tpkt.hpp"

#ifdef _AIX_CONV
#include "aix_conv.hpp"
#endif

#if defined(__sun__) || defined(__OSX__)
#define strftim strftime
#endif

// --------------------------------------------------------------------
typedef struct {
   word c0002;
   word FromNode;
   word ToNode;
   word FromNet;
   word ToNet;
   word Attr;
   word Cost;
   char               DateTime[20];
} tPMSG;                                                                                                        
char *LoFile = NULL;
// --------------------------------------------------------------------

void LogTraffic(cMSG &m, FA &ToAddr) {
FILE *fh;
char Buff[128];
time_t t;
Template *tpl;

   if (TrafficLog == NULL) {
      return;
   }
   if (TrafficLogTpl == NULL) {
      fh = fopen(TrafficLog,"a+t");
      if (fh == NULL) {
         Log.Level(LOGE) << "Unable to open file '" << TrafficLog << "'" << EOL;
         return;
      }
      t = time(NULL);
      strftime(Buff,128,"-------------------- Packed on %b %d %Y %H:%M:%S --------------------\n",localtime(&t));
      fputs(Buff,fh);
      fprintf(fh,"From : %s, %s\n",m._FromName,m._FromAddr.ToStr());
      fprintf(fh,"To   : %s, %s\n",m._ToName,m._ToAddr.ToStr());
      fprintf(fh,"Subj : %s\n",m._Subject);
      fprintf(fh,"Date : %s\n",FromTime(m._Time));
      fprintf(fh,"Size : %d\n",(int)(m.Body() != NULL ? strlen(m.Body()) : 0));
      fprintf(fh,"Via  : %s\n",ToAddr.ToStr());
      fputs("------------------------------------------------------------------------\n",fh);
      fclose(fh);
   } else {
      tpl = new Template();
      if (tpl->Set(TrafficLogTpl) != TRUE) {
         Log.Level(LOGE) << "Unable to open traffic log template file '" << TrafficLogTpl << "'." << EOL;
         return;
      }
      tpl->SetMsg(m);
      if (tpl->Parse()) {
         tpl->Save(TrafficLog,2);
      }
      tpl->Clean();
      delete tpl;
   }
}

// --------------------------------------------------------------------
char *MakePktName(FA &f, char *PathPrefix) {
static char Buff[BUFF_SIZE];
char *tmt;
   RSTRLCPY(Buff,PathPrefix,BUFF_SIZE);
   if (UseASO || UseBrake) {
      if (Buff[strlen(Buff)-1] != PATHDELIMC) {
         RSTRLCAT(Buff,PATHDELIMS,BUFF_SIZE);
      }
      if (UseBrake)
      {
       tmt=GetDomain(f);
       if (tmt) {
        RSTRLCAT(Buff,tmt,BUFF_SIZE);
       }    
       else {
        RSTRLCAT(Buff,"fidonet",BUFF_SIZE);
       }    
       RSTRLCAT(Buff,".",BUFF_SIZE);
      }
      sprintf(Buff+strlen(Buff),"%u.%u.%u.%u",
         (word)(f.Zone() & 0xffff),
     (word)(f.Net() & 0xffff),
     (word)(f.Node() & 0xffff),
     (word)(f.Point() & 0xffff));
   } else {
      if (Buff[strlen(Buff)-1] == PATHDELIMC) {
         Buff[strlen(Buff)-1] = '\0';
      }
      if ((MyAddr.Zone() & 0xffff) != (f.Zone() & 0xffff)) {
         sprintf(Buff+strlen(Buff),".%03x",(word)(f.Zone() & 0xffff));
      }
      RSTRLCAT(Buff,PATHDELIMS,BUFF_SIZE);
      sprintf(Buff+strlen(Buff),"%04x%04x",(word)(f.Net() & 0xffff),(word)(f.Node() & 0xffff));
      if ((f.Point() & 0xffff) != 0) {
         RSTRLCAT(Buff,PntExtension""PATHDELIMS"0000",BUFF_SIZE);
         sprintf(Buff+strlen(Buff),"%04x",(word)(f.Point() & 0xffff));
      }
   }
   return Buff;
}

// --------------------------------------------------------------------
void AddOutExt(PKTMode m, char *Buff, int outmode)
{
 if (UseBrake)
 {
  switch (m) {
     case F_DIRECT: RSTRLCAT(Buff,".direct",BUFF_SIZE); break;
     case F_CRASH:  RSTRLCAT(Buff,".crash",BUFF_SIZE); break;
     case F_HOLD:   RSTRLCAT(Buff,".hold",BUFF_SIZE); break;
     case F_NORMAL: RSTRLCAT(Buff,".normal",BUFF_SIZE); break;
     case F_IMMEDIATE: RSTRLCAT(Buff,".immediate",BUFF_SIZE); break;
     case F_ATTACH: break;
  }
  if (outmode == 1) {
   RSTRLCAT(Buff,".mail",BUFF_SIZE);
  } 
  else {
   RSTRLCAT(Buff,".list",BUFF_SIZE);
  }
 }
 else
 {
  if (outmode == 1)
  {
   switch (m) {
      case F_DIRECT: RSTRLCAT(Buff,".dut",BUFF_SIZE); break;
      case F_CRASH:  RSTRLCAT(Buff,".cut",BUFF_SIZE); break;
      case F_HOLD:   RSTRLCAT(Buff,".hut",BUFF_SIZE); break;
      case F_NORMAL: RSTRLCAT(Buff,".out",BUFF_SIZE); break;
      case F_IMMEDIATE: RSTRLCAT(Buff,".iut",BUFF_SIZE); break;
      case F_ATTACH: break;
   }  
  }
  else
  {
   switch (m) {
      case F_DIRECT: RSTRLCAT(Buff,".dlo",BUFF_SIZE); break;
      case F_CRASH:  RSTRLCAT(Buff,".clo",BUFF_SIZE); break;
      case F_HOLD:   RSTRLCAT(Buff,".hlo",BUFF_SIZE); break;
      case F_NORMAL: RSTRLCAT(Buff,".flo",BUFF_SIZE); break;
      case F_IMMEDIATE: RSTRLCAT(Buff,".ilo",BUFF_SIZE); break;
      case F_ATTACH: break;
   }
  }    
 }    
}
// --------------------------------------------------------------------

char *MakeAPktName(char *PathPrefix) {
static char Buff[BUFF_SIZE];
char *tmt;
   RSTRLCPY(Buff,PathPrefix,BUFF_SIZE);
   if (Buff[strlen(Buff)-1] == PATHDELIMC) {
      Buff[strlen(Buff)-1] = '\0';
   }
   tmt = Buff+strlen(Buff);
   do {
      sprintf(tmt,PATHDELIMS"%08lx"PktExtension,MsgID());
   } while (access(Buff,F_OK) == 0);
   return Buff;
}

// --------------------------------------------------------------------

int AddToLo(char *Txt) {
int ind;
size_t size;
   ind = 0;
   while (LoFile[ind] != 0) {
      
      if (stricmp(&LoFile[ind],Txt) == 0) {
         return TRUE;
      }
      while (LoFile[ind]) ind++;
      ind++;
   }
   size=ind + 1 + strlen(Txt) + 1;
   LoFile = (char *) realloc(LoFile,size);
   CheckMem(LoFile);
   RSTRLCPY(LoFile+ind,Txt,size);
   ind += strlen(Txt);
   LoFile[ind++] = '\0';
   LoFile[ind] = '\0';
   return TRUE;
}

int DelFromLo(char *Txt) {
int ind;
int rc;
   if (LogLevel >= 5) {
      Log.Level(LOGD) << "Delete " << Txt << " from ?lo" << EOL;
   }
   ind = 0;
   while (LoFile[ind] != 0) {
      if (LoFile[ind] == '^' || LoFile[ind] == '#') {
         rc = stricmp(&LoFile[ind+1],Txt);
      } else {
         rc = stricmp(&LoFile[ind],Txt);
      }
      if (rc == 0) {
         LoFile[ind] = '~';
      }
      while(LoFile[ind] != '\0') {
         ind++;
      }
      ind++;
   }
   if (LogLevel >= 5) {
      Log.Level(LOGD) << "Done" << EOL;
   }
   return TRUE;
}

int ReadLoFile(char *Name) {
char TmtName[BUFF_SIZE];
char *tmt2;
int ind;
#if 0
fpos_t LoSize;
#endif
FILE *fh;

   RSTRLCPY(TmtName,Name,BUFF_SIZE);
   if (!UseBrake)
   {
    tmt2 = TmtName + strlen(TmtName) - 2;
    tmt2[0] = 'l';
    tmt2[1] = 'o';
   }
   
   LoFile = (char *) malloc(2);
   CheckMem(LoFile);
   memset(LoFile,0,2);
   ind = 0;
   if (access(TmtName,F_OK) != 0) {
      return TRUE;
   }
   fh = fopen(TmtName,"rt");
   if (fh == NULL) {
      free(LoFile);
      LoFile = NULL;
      return FALSE;
   }

#if 0
   if (fseek(fh,0L,SEEK_END) != 0) {
      free(LoFile);
      LoFile = NULL;
      fclose(fh);
      return FALSE;
   }
   if (fgetpos(fh,&LoSize) != 0) {
      free(LoFile);
      LoFile = NULL;
      fclose(fh);
      return FALSE;
   }
   if (fseek(fh,0L,SEEK_SET) != 0) {
      free(LoFile);
      LoFile = NULL;
      fclose(fh);
      return FALSE;
   }
#endif
   while (fgets(TmtName,1023,fh) != NULL) {
      if ((tmt2 = strchr(TmtName,'\n')) != NULL) {
         *tmt2 = '\0';
      }
      AddToLo(TmtName);
   }
   if (!feof(fh)) {
      free(LoFile);
      LoFile = NULL;
      fclose(fh);
      return FALSE;
   }
   fclose(fh);
   return TRUE;
}


int ReadLoFile(FA &f, PKTMode m) {
char TmtName[BUFF_SIZE];
   RSTRLCPY(TmtName,MakePktName(f,Outbound),BUFF_SIZE);
   AddOutExt(m,TmtName,0);
   return ReadLoFile(TmtName);
}

int SaveLoFile(char *Name) {
char TmtName[BUFF_SIZE];
char *tmt2;
int ind;
FILE *fh;

   if (LoFile[0] == '\0') {
      free (LoFile);
      LoFile = NULL;
      return TRUE;
   }
   RSTRLCPY(TmtName,Name,BUFF_SIZE);
   if (!UseBrake)
   {
    tmt2 = TmtName + strlen(TmtName) - 2;
    tmt2[0] = 'l';
    tmt2[1] = 'o';
   }
   fh = fcopen(TmtName,"wt");
   if (fh == NULL) {
      free(LoFile);
      LoFile = NULL;
      return FALSE;
   }

   ind = 0;
   while (LoFile[ind] != 0) {
      if (LoFile[ind] != '~') {
         fprintf(fh,"%s\n",&LoFile[ind]);
      }
      while(LoFile[ind] != '\0') ind++;
      ind++;
   }
   free(LoFile);
   if (ftell(fh) == 0) {
      fclose(fh);
      unlink(TmtName);
   } else {
      fclose(fh);
   }
   LoFile = NULL;
   return TRUE;
}

int SaveLoFile(FA &f, PKTMode m) {
char TmtName[BUFF_SIZE];
   RSTRLCPY(TmtName,MakePktName(f,Outbound),BUFF_SIZE);
   AddOutExt(m,TmtName,0);    
   return SaveLoFile(TmtName);
}

// --------------------------------------------------------------------
// --------------------------------------------------------------------

PKT::PKT() {
   BsyFile = NULL;
   fh = NULL;
   Addr.Clean();
}

PKT::~PKT() {
   Clean();
}

// --------------------------------------------------------------------

int PKT::Clean(void) {
   if (fh != NULL) {
      fclose(fh);
      fh = NULL;
   }
   DelBsy();
   Addr.Clean();
   return TRUE;
}

// --------------------------------------------------------------------

void PKT::DelBsy(void) {
   if (IgnoreBSY) return;
   if (BsyFile != NULL) {
      unlink(BsyFile);
      free(BsyFile);
      BsyFile = NULL;
   }
}

// --------------------------------------------------------------------

int PKT::Set(FA &f) {
   Clean();
   if (!f.Valid() || f.Masked()) {
      return FALSE;
   }
   Addr = f;
   return TRUE;
}

// --------------------------------------------------------------------

int PKT::Bsy(void) {
char TmtName[BUFF_SIZE];
char BsyName[BUFF_SIZE];
FILE *fh;
int bfh;

   if (IgnoreBSY) return TRUE;
   
   if (BsyFile != NULL) {
      return TRUE;
   }
   RSTRLCPY(TmtName,MakePktName(Addr,Outbound),BUFF_SIZE);
   RSTRLCPY(BsyName,TmtName,BUFF_SIZE);
   RSTRLCAT(TmtName,".ftr",BUFF_SIZE);
   if (UseBrake) {
    RSTRLCAT(BsyName,".busy",BUFF_SIZE);
   }    
   else {
    RSTRLCAT(BsyName,BsyExtension,BUFF_SIZE);
   }    

// Create temp file name. Just for make directory, if need...
   fh = fcopen(TmtName,"wb");
   if (fh == NULL) return FALSE;
   fclose (fh);
   unlink(TmtName);

   bfh = open(BsyName,O_CREAT | O_EXCL | O_RDWR,S_IREAD | S_IWRITE);
   if (bfh == -1) {
      return FALSE;
   }
   close(bfh);
   BsyFile = strdup(BsyName);
   return TRUE;
}

// --------------------------------------------------------------------
static char _PKTName[BUFF_SIZE];

PKTrc PKT::Open(PKTMode m, char *pktFileName) {
long PktSize;

   if (!Addr.Valid()) {
      return PKTERROR;
   }
   Mode = m;
   if (!Bsy()) {
      return BSY;
   }
   
   RSTRLCPY(_PKTName,pktFileName,BUFF_SIZE);
   
   if (access(_PKTName,F_OK) != 0) {
      fh = fcopen(_PKTName,"w+b");
      if (fh == NULL) {
         DelBsy();
         return PKTERROR;
      }
      return NEWPKT;
   } else {
      fh = fcopen(_PKTName,"r+b");
   }
   if (fh == NULL) {
      DelBsy();
      return PKTERROR;
   }

   if (fseek(fh,0L,SEEK_END) != 0) {
      DelBsy();
      fclose(fh);
      return PKTERROR;
   }
   if ((PktSize = ftell(fh)) == -1) {
      DelBsy();
      fclose(fh);
      return PKTERROR;
   }
   if (PktSize == 0 && Mode == F_ATTACH) {
      return NEWPKT;
   }

   if (PktSize == 0) {
      if (!AddToNullPkt) {
         DelBsy();
         fclose(fh);
         return NULLPKT;
      } else {
         return NEWPKT;
      }
   }
   if (PktSize < (long) (sizeof(tPKTH) + 2)) {
      DelBsy();
      fclose(fh);
      return BADPKT;
   }
   if (fseek(fh,0,SEEK_SET) != 0) {
      DelBsy();
      fclose(fh);
      return PKTERROR;
   }
   return PKTOK;
}

PKTrc PKT::AddMsg(cMSG &m, PKTMode mod, int Dest) {
PKTrc rc;
int NewPkt;
tPKTH p;
tPMSG pm;
struct tm *tp;
char *tmt;
time_t ltime;
char Buff[BUFF_SIZE];

   if (!Bsy()) {
      return BSY;
   }
   if (m.fFileAttach && (APktDir != NULL || UseFileBoxes == TRUE || Dest == 1)) {
      if (!ReadLoFile(Addr,mod)) {
         Clean();
         return ATTERROR;
      }

      if (UseFileBoxes == TRUE || Dest == 1)
      {
       RSTRLCPY(Buff,MakeFileboxName(Addr,mod),BUFF_SIZE);
       if (!DirExists(Buff))
        mymkdir(Buff);       
       if (m.fKFS)
       {
        if (!MoveAttach(m,Buff))
            return ATTERROR;
       }
       else
       {
        if (!CopyAttach(m,Buff))
            return ATTERROR;
       }
       AddFboxAttachToLo(m,Buff);       
      }
      else
      {
       RSTRLCPY(Buff,APktDir,BUFF_SIZE);
       AddAttachToLo(m);
      }

      rc = Open(F_ATTACH,MakeAPktName(Buff));

      switch (rc) {
         case PKTOK:
         case NEWPKT:
              break;
         default: Clean(); return (rc);
      }
      NewPkt = TRUE;
      Mode = mod;
   } else if (Dest == 1) {
      NewPkt = TRUE;
      RSTRLCPY(Buff,MakeFileboxName(Addr,mod),BUFF_SIZE);
      if (!DirExists(Buff))
       mymkdir(Buff);
      rc = Open(F_ATTACH,MakeAPktName(Buff));
      
      switch (rc) {
         case PKTOK: break;
         case NEWPKT: NewPkt = TRUE; break;
         default: Clean(); return (rc);
      }
   } else {
      NewPkt = FALSE;

      RSTRLCPY(Buff,MakePktName(Addr,Outbound),BUFF_SIZE);
      AddOutExt(mod,Buff,1);

      rc = Open(mod,Buff);

      switch (rc) {
          case PKTOK: break;
          case NEWPKT: NewPkt = TRUE; break;
          default: Clean(); return (rc);
      }
   }

   memset(&p,0,sizeof(tPKTH));
   p.FromZone = GetMyAka(Addr).Zone();
   p.FromZone2 = GetMyAka(Addr).Zone();
   p.FromNet = GetMyAka(Addr).Net();
   p.FromNode = GetMyAka(Addr).Node();
// FSC-0048
//   if (GetMyAka(Addr).Point() & 0xffff) {
//      p.FromPoint = GetMyAka(Addr).Point() & 0xffff;
//      p.AuxNet = p.FromNet;
//      p.FromNet = -1;
//   }
   p.FromPoint = GetMyAka(Addr).Point() & 0xffff;

   if ((tmt = GetPasswd(Addr)) != NULL) {
      RSTRLCPY(p.Passwd,tmt,8);
   }

   p.ToZone = Addr.Zone();
   p.ToZone2 = Addr.Zone();
   p.ToNet = Addr.Net();
   p.ToNode = Addr.Node();
   p.ToPoint = Addr.Point();
   p.c0002 = 2;
   p.c0001 = 1;
   p.c0100 = 256;
   p.ProductCodeL = ProductLO;
   p.ProductCodeH = ProductHI;
   p.Baud = 2400;
   p.RevisionH = RevisionHI;
   p.RevisionL = RevisionLO;
   ltime = time(NULL);
   tp = localtime(&ltime);
   p.Year = tp->tm_year + 1900;
   p.Month = tp->tm_mon;
   p.Day = tp->tm_mday;
   p.Hour = tp->tm_hour;
   p.Minute = tp->tm_min;
   p.Second = tp->tm_sec;
#ifdef _AIX_CONV
   AIXConvPKTH(p);
#endif

   if (fwrite(&p,sizeof(tPKTH),1,fh) != 1) {
      Clean();
      return PKTERROR;
   }
   if (!NewPkt) {
      if (fseek(fh,-2,SEEK_END) != 0) {
         Clean();
         return PKTERROR;
      }
   }
   memset(&pm,0,sizeof(tPMSG));
   pm.c0002 = 2;
   pm.FromNode = m._FromAddr.Node();
   pm.ToNode = m._ToAddr.Node();
   pm.FromNet = m._FromAddr.Net();
   pm.ToNet = m._ToAddr.Net();
   pm.Cost  = m._Cost;
   RSTRLCPY(pm.DateTime,FromTime(m._Time),20);
   SetMsgAttr(m,pm.Attr);
#ifdef _AIX_CONV
    pm.ToNode=RotateShort(pm.ToNode);
    pm.FromNode=RotateShort(pm.FromNode);
    pm.ToNet=RotateShort(pm.ToNet);
    pm.FromNet=RotateShort(pm.FromNet);
    pm.Attr=RotateShort(pm.Attr);
    pm.Cost=RotateShort(pm.Cost);
    pm.c0002=RotateShort(pm.c0002);
#endif
   if (fwrite(&pm,sizeof(tPMSG),1,fh) != 1) {
      Clean();
      return PKTERROR;
   }

   if (strlen(m._ToName) != 0) {
      if (fwrite(m._ToName,strlen(m._ToName),1,fh) != 1) {
         Clean();
         return PKTERROR;
      }
   }
   if (fwrite("\0",1,1,fh) != 1) {
      Clean();
      return PKTERROR;
   }

   if (strlen(m._FromName) != 0) {
      if (fwrite(m._FromName,strlen(m._FromName),1,fh) != 1) {
         Clean();
         return PKTERROR;
      }
   }
   if (fwrite("\0",1,1,fh) != 1) {
      Clean();
      return PKTERROR;
   }

   if (strlen(m._Subject) != 0) {
   
      if (fwrite(m._Subject,strlen(m._Subject),1,fh) != 1) {
         Clean();
         return PKTERROR;
      }
   }
   if (fwrite("\0",1,1,fh) != 1) {
      Clean();
      return PKTERROR;
   }
   if (!WriteMsgBody(m,fh)) {
      Clean();
      return PKTERROR;
   }
   if (fwrite("\0\0",2,1,fh) != 1) {
      Clean();
      return PKTERROR;
   }
   fclose (fh);
   fh = NULL;

   if (m.fFileAttach && (APktDir != NULL || UseFileBoxes == TRUE || Dest == 1)) {
      memmove(_PKTName+1,_PKTName,strlen(_PKTName)+1);
      _PKTName[0] = '^';
      AddToLo(_PKTName);
      if (!SaveLoFile(Addr,Mode)) {
         Clean();
         return ATTERROR;
      }
   }

   if (m.fFileAttach && APktDir == NULL && UseFileBoxes != TRUE && Dest != 1) {
      if (!ReadLoFile(Addr,Mode)) {
         Clean();
         return ATTERROR;
      }
      AddAttachToLo(m);
      if (!SaveLoFile(Addr,Mode)) {
         Clean();
         return ATTERROR;
      }
   }


 Clean();
 return PKTOK;

}

// --------------------------------------------------------------------

PKTrc PKT::Poll(PKTMode mod) {
char TmtName[BUFF_SIZE];
int i;

   RSTRLCPY(TmtName,MakePktName(Addr,Outbound),BUFF_SIZE);
   AddOutExt(mod,TmtName,0);
   
   if (!Bsy()) {
      return BSY;
   }
   fh = fcopen(TmtName,"ab");
   i = errno;
   if (fh == NULL) {
      Clean();
      Log.Level(LOGD) << "PKT.Poll: Unbale to create/open '" << TmtName << "', Errno: " << i << EOL;
      return PKTERROR;
   }
   fclose(fh);
   Clean();
   return PKTOK;
}
// --------------------------------------------------------------------
// --------------------------------------------------------------------


int UnpackOneMsg(char *&tmt) {
cMSG m;
tPMSG *p;
int LoOpened;
   m.Clear();
   p =(tPMSG *)tmt;
   tmt += sizeof(tPMSG);
   if (p->c0002 != 2) {
      Log.Level(LOGE) << "   Error: Destroyed packet." << EOL;
      return FALSE;
   }
   m._FromAddr.Node(p->FromNode);
   m._ToAddr.Node(p->ToNode);
   m._FromAddr.Net(p->FromNet);
   m._ToAddr.Net(p->ToNet);
   m._Cost = p->Cost;
   m._Time = ToTime(p->DateTime);
   SetMsgAttr(p->Attr,m);
   RSTRLCPY(m._ToName,tmt,36);
   while (*tmt++ != '\0');
   RSTRLCPY(m._FromName,tmt,36);
   while (*tmt++ != '\0');
   RSTRLCPY(m._Subject,tmt,72);
   while (*tmt++ != '\0');
   
   m.ParseMem(tmt);
   m.DelLastOurVia();
   if (!TempMail->WriteNewMsg(m)) {
      Log.Level(LOGE) << "   Unable to write message to base " << TempMail->BaseName() << EOL;
      return FALSE;
   }
   if (m.fFileAttach) {
      LoOpened = FALSE;
      if (LoFile != NULL) LoOpened = TRUE;
      if (!LoOpened && !ReadLoFile(_PKTName)) {
         return FALSE;
      }
      DelAttachFromLo(m);
      if (!LoOpened && !SaveLoFile(_PKTName)) {
         return FALSE;
      }
   }
      
   while (*tmt != '\0') tmt++;
   tmt++;
   return TRUE;
}

int DoRepackFile(char *Name) {
char *tmt,*tmt2;
FILE *fh;
long PktSize;

   fh = fcopen(Name,"rb");
   if (fh == NULL) {
      Log.Level(LOGE) << "Unable to open " << Name << EOL;
      return TRUE;
   }

   if (fseek(fh,0,SEEK_END) != 0) {
      Log.Level(LOGE) << "Error reading " << Name << EOL;
      fclose(fh);
      return TRUE;
   }

   if ((PktSize = ftell(fh)) == 0) {
      Log.Level(LOGW) << "Packet " << Name << " have null size. Skipped." << EOL;
      fclose(fh);
      return TRUE;
   }

   if (PktSize < (long) (sizeof(tPKTH) + 2)) {
      Log.Level(LOGE) << "Packet " << Name << " is wrong." << EOL;
      fclose(fh);
      return TRUE;
   }
   if (fseek(fh,0,SEEK_SET) != 0) {
      Log.Level(LOGE) << "Error reading " << Name << EOL;
      fclose(fh);
      return TRUE;
   }

   Log.Level(LOGI) << "Unpack " << Name << EOL;

   tmt = (char *) malloc(PktSize);
   CheckMem(tmt);
   tmt2 = tmt;
   if (fread(tmt,PktSize,1,fh) != 1) {
      free (tmt2);
      Log.Level(LOGE) << "Error reading " << Name << EOL;
      fclose(fh);
      return TRUE;
   }
   fclose(fh);
   tmt += sizeof(tPKTH);
   while (*tmt == '\2') {
      if (!UnpackOneMsg(tmt)) {
         free (tmt2);
         return TRUE;
      }
   }
   unlink(Name);
   free (tmt2);
   return TRUE;
}

static int _FileInAPKT(char *FName) {
char Buff[BUFF_SIZE];
char *tmt;

   Log.Level(LOGD) << "_FileInAPKT: Check '" << FName << "' in APKT dir?" << EOL;
   RSTRLCPY(Buff,FName,BUFF_SIZE);
   tmt = strrchr(Buff,PATHDELIMC);
   if (tmt != NULL) *tmt = '\0';
   if (stricmp(Buff,APktDir) != 0) return FALSE;
   Log.Level(LOGD) << "_FileInAPKT: Check '" << FName << "' is a PKT?" << EOL;
   if (tmt != NULL) *tmt = PATHDELIMC;
   tmt = strrchr(Buff,'.');
   if (tmt == NULL || fsCompareName(tmt,".[Pp][Kk][Tt]") != 0) {
      return FALSE;
   }
   Log.Level(LOGD) << "_FileInAPKT: Ok. '" << FName << "' is a PKT." << EOL;
   return TRUE;
}

int DoRepackAPKT(char *Name) {
int ind;

   Log.Level(LOGD) << "Unpack APkt " << Name << EOL;
   if (APktDir == NULL) return TRUE;
   if (!ReadLoFile(Name)) {
      Log.Level(LOGE) << "Unable to read ?lo file" << EOL;
      Log.Level(LOGD) << "Name == " << Name << EOL;
      return TRUE;
   }

   ind = 0;
   while (LoFile[ind] != 0) {
      if (LoFile[ind] != '~') {
         if (LoFile[ind] == '^' || LoFile[ind] == '#') ind++;
         if (_FileInAPKT(&LoFile[ind])) {
            if (!DoRepackFile(&LoFile[ind])) {
               free(LoFile);
               return TRUE;
            }
            DelFromLo(&LoFile[ind]);
         }
      }
      while(LoFile[ind] != '\0') ind++;
      ind++;
   }
   if (!SaveLoFile(Name)) {
      Log.Level(LOGE) << "Unable to save ?lo file" << EOL;
      Log.Level(LOGD) << "Name == " << Name << EOL;
      return TRUE;
   }
   return TRUE;
}

int DoRepackBundle(char *Name) {
char Buff[BUFF_SIZE];
char TmtName[BUFF_SIZE];
char *tmt;
FILE *fh;
int bfh;

   Log.Level(LOGD) << "DoRepackBundle.Name == " << Name << EOL;
   RSTRLCPY(Buff,Name,BUFF_SIZE);
   tmt = strrchr(Buff,'.');
   if (tmt == NULL) {
      return TRUE;
   }
   *tmt = '\0';
   tmt++;
   if (strchr("fcdohFCDOH",*tmt) == NULL) {
      return TRUE;
   }
   RSTRLCPY(_PKTName,Name,BUFF_SIZE);
   RSTRLCPY(TmtName,Buff,BUFF_SIZE);
   RSTRLCAT(TmtName,".ftr",BUFF_SIZE);
   if (UseBrake) {
    RSTRLCAT(Buff,".busy",BUFF_SIZE);
   }    
   else {
    RSTRLCAT(Buff,BsyExtension,BUFF_SIZE);
   }    
   fh = fcopen(TmtName,"wb");
   if (fh == NULL) {
      Log.Level(LOGW) << "Unable to create temp file '" << Name << "'" << EOL;
      return TRUE;
   }
   fclose (fh);
   unlink(TmtName);
   bfh = open(Buff,O_CREAT | O_EXCL | O_RDWR,S_IREAD | S_IWRITE);
   if (bfh == -1) {
      Log.Level(LOGW) << "Packet " << Name << " is locked." << EOL;
      return TRUE;
   }
   close(bfh);
   if (toupper((uchar)Name[strlen(Name)-1]) == 'T') {
      if (!DoRepackFile(Name)) {
         unlink(Buff);
         return TRUE;
      }
   }

   if (!DoRepackAPKT(Name)) {
      unlink(Buff);
      return TRUE;
   }
   unlink(Buff);
   return TRUE;
}

int DoRepackDir(char *Name);

int DoRepackPoints(char *Dir) {
char fdir[BUFF_SIZE];
DIR *dd;
struct dirent *ff;
struct stat statb;

   dd = opendir(dirslashbug(Dir));
   if (dd == NULL) {
      return TRUE;
   }
   while ((ff = readdir(dd)) != NULL) {
      if (fsCompareName(ff->d_name,"*.[pP][nN][tT]") != 0) {
         RSTRLCPY(fdir,Dir,BUFF_SIZE);
         RSTRLCAT(fdir,ff->d_name,BUFF_SIZE);
     RSTRLCAT(fdir,PATHDELIMS,BUFF_SIZE);
         if (stat(dirslashbug(fdir),&statb) == 0 && S_ISDIR(statb.st_mode)) {
            DoRepackDir(fdir);
         }
      }
   }
   closedir(dd);
   return TRUE;
}


int DoRepackDir(char *Name) {
char fdir[BUFF_SIZE];
char *tmt;
DIR *dd;
struct dirent *ff;
struct stat statb;

   Log.Level(LOGD) << "DoRepackDir: " << Name << EOL;
   if (strlen(Name) == 0) return TRUE;
   RSTRLCPY(fdir,Name,BUFF_SIZE);
   if (fdir[strlen(fdir)-1] == PATHDELIMC) fdir[strlen(fdir)-1] = '\0';
   tmt = strrchr(fdir,'.');
   if (tmt != NULL) {
      if (strrchr(tmt,PATHDELIMC) != NULL) {
         tmt = NULL;
      } else {
         tmt = tmt - fdir + Name;
      }
   }

   if (tmt != NULL) {
      tmt++;
      RSTRLCPY(fdir,tmt,BUFF_SIZE);
      fdir[3] = '\0';
      if (fdir[2] == PATHDELIMC) fdir[2] = '\0';
      if (fdir[1] == PATHDELIMC) fdir[1] = '\0';
      if (!StrIsXNum(fdir) && stricmp(fdir,"pnt") != 0) {
         return TRUE;
      }
   }
   if (tmt == NULL || stricmp(tmt,"pnt"PATHDELIMS) != 0) {
      DoRepackPoints(Name);
   }
   Log.Level(LOGD) << "Unpack dir " << Name << " by mask *.?ut" << EOL;
   dd = opendir(dirslashbug(Name));
   if (dd != NULL) {
      while ((ff = readdir(dd)) != NULL) {
         if(fsCompareName(ff->d_name,"*.?[Uu][Tt]") != 0) {
            RSTRLCPY(fdir,Name,BUFF_SIZE);
            RSTRLCAT(fdir,ff->d_name,BUFF_SIZE);
            if (stat(fdir,&statb) == 0 && S_ISREG(statb.st_mode)) {
               DoRepackBundle(fdir);
            }
     }
      }
      closedir(dd);
   }

   if (APktDir == NULL) return TRUE;

   Log.Level(LOGD) << "Unpack dir " << Name << " by mask *.?lo"  << EOL;
   dd = opendir(dirslashbug(Name));
   if (dd == NULL) {
      return TRUE;
   }

   while ((ff = readdir(dd)) != NULL) {
      if (fsCompareName(ff->d_name,"*.?[Ll][Oo]") != 0) {
         RSTRLCPY(fdir,Name,BUFF_SIZE);
         RSTRLCAT(fdir,ff->d_name,BUFF_SIZE);
         if (stat(fdir,&statb) == 0 && S_ISREG(statb.st_mode)) {
            DoRepackBundle(fdir);
         }
      }
   }
   closedir(dd);

   return TRUE;
}

int DoRepack(void) {
char Buff[BUFF_SIZE];
char fname[BUFF_SIZE];
char fdir[BUFF_SIZE];
DIR *dd;
struct dirent *ff;
struct stat statb;
int rc;

   Log.Level(LOGD) << "--==( DoRepack )==--" << EOL;
   Log.Level(LOGD) << "DoRepack started. Outbound directory: '" << Outbound << "'." << EOL;
   TempMail->Rewind();
   RSTRLCPY(Buff,Outbound,BUFF_SIZE);
   if (Buff[strlen(Buff)-1] == PATHDELIMC) {
      Buff[strlen(Buff)-1] = '\0';
   }
   GetFilePath(fdir,Buff);
   GetFileName(fname,Buff);
   RSTRLCAT(fname,".*",BUFF_SIZE);
   rc = stat(dirslashbug(Outbound),&statb);
   if ( rc == 0 && S_ISDIR(statb.st_mode)) {
      DoRepackDir(Outbound);
   } else {
      Log.Level(LOGD) << "DoRepack: Outbound is not a directory???" << EOL;
      Log.Level(LOGD) << "          rc == " << rc << EOL;
      Log.Level(LOGD) << "          statb.st_mode == " << statb.st_mode << EOL;
   }

   dd = opendir(dirslashbug(fdir));
   if (dd == NULL) {
      Log.Level(LOGD) << "DoRepack: Unable to open '" << fdir << "', exit." << EOL;
      Log.Level(LOGD) << "--==( End DoRepack )==--" << EOL;
      return TRUE;
   }
   while ((ff = readdir(dd)) != NULL) {
      if (fsCompareName(ff->d_name,fname) != 0) {
         RSTRLCPY(Buff,fdir,BUFF_SIZE);
         RSTRLCAT(Buff,ff->d_name,BUFF_SIZE);
         RSTRLCAT(Buff,PATHDELIMS,BUFF_SIZE);
         if (stat(dirslashbug(Buff),&statb) == 0 && S_ISDIR(statb.st_mode)) {
            DoRepackDir(Buff);
         }
      }
   }
   closedir(dd);

   Log.Level(LOGD) << "--==( End DoRepack )==--" << EOL;
   return TRUE;
}

// --------------------------------------------------------------------
// --------------------------------------------------------------------

int SetAddToNullPkt(void){
   if (AddToNullPkt) {
      yyerror("AddToNullPkt is already set.");
      return (-1);
   }
   AddToNullPkt = TRUE;
   return (0);
}

int SetOutbound(char *tmt){
 size_t size;

   if (Outbound != NULL) {
      yyerror("Outbound directory already defined.");
      return (-1);
   }
   if (strlen(tmt) == 0) {
      yyerror("Missing parameter: Outbound directory name.");
      return (-1);
   }
   if (APktDir != NULL && stricmp(APktDir,tmt) == 0) {
      yyerror("APKT directory and Outbound directory should be different.");
      return (-1);
   }
   size=strlen(tmt)+2;
   Outbound = (char *) malloc(size);
   CheckMem(Outbound);
   RSTRLCPY(Outbound,tmt,size);
   if (Outbound[strlen(Outbound)-1] != PATHDELIMC) {
      RSTRLCAT(Outbound,PATHDELIMS,size);
   }
   return 0;
}

int SetTrafficLog(char *tmt){

   if (TrafficLog != NULL) {
      yyerror("Traffic log already defined.");
      return (-1);
   }
   if (strlen(tmt) == 0) {
      yyerror("Missing parameter: Traffic log file name.");
      return (-1);
   }
   TrafficLog = strdup(tmt);
   return 0;
}

int SetTempMail(char *tmt){

   if (TempMail != NULL) {
      yyerror("Directory for TempMail already defined.");
      return (-1);
   }
   if (strlen(tmt) == 0) {
      yyerror("Missing parameter: TempMail base name.");
      return (-1);
   }
   TempMail = MakeBase(tmt);
   if (TempMail == NULL) {
      return (-1);
   }
   if (!TempMail->Set(tmt,BASE_OUT)) {
      yyerror("Unable to open TempMail base.");
      return (-1);
   }
   if (!TempMail->CheckOut()) return (-1);

   return 0;
}

int SetKillRoutedMessages(KillModeT kmode){
   KillMode = kmode;
   return 0;
}

int InitOutbound(void) {
   if (UnpackNeed) {
      if (Outbound == NULL) {
         Log.Level(LOGE) << "Outbound directory not specified." << EOL;
         return FALSE;
      }
      if (TempMail == NULL) {
         Log.Level(LOGE) << "TempMail base not specified." << EOL;
         return FALSE;
      }
   }
   return TRUE;
}
// ---------------------------- END --------------------------------------
