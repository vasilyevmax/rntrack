/*
 *  RNtrack - FTN message tracker/router
 *
 *  filebox.cpp - Filebox routines
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

#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <ctype.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "fidoaddr.hpp"
#include "scandir.hpp"
#include "mytypes.hpp"

// --------------------------------------------------------------------

class tFilebox {
public:
   FA _Addr;
   char _Path[101];
   tFilebox() { _Addr.Clean(); memset(_Path,0,100); };
   ~tFilebox() { return; };
};

IndBiList<tFilebox> Filebox;

// --------------------------------------------------------------------

char *dec232_tbl = "0123456789abcdefghijklmnopqrstuv";

char *dec232(short n, short digits)
{
  static char buf[20];
  int i,b;
  buf[0]='\0';

  for (i=0;i<digits;i++)
  {
    b = n & 31;
    buf[digits-i-1]=dec232_tbl[b];
    n>>=5;
  }
  buf [digits]=0;
  return buf;
}

// --------------------------------------------------------------------

int SetUseFileBoxes(void) {
   if (UseFileBoxes) {
      yyerror("UseFileBoxes already set.");
      return (-1);
   }
   if (FileBoxDir != NULL)
   {
    UseFileBoxes = TRUE;
   }
   else
   {
    yyerror("You must define FileBoxDir before UseFileBoxes.");
    return (-1);
   }
   return (0);
}

// --------------------------------------------------------------------


void AddFilebox(FA &Addr, char *P) {
tFilebox *a;

   a = new tFilebox;
   a->_Addr = Addr;
   RSTRLCPY(a->_Path,P,100);
   a->_Path[100] = '\0';
   Filebox.AddToEnd(a);
}

char *GetFilebox(FA const &Addr) {
IndBiList<tFilebox>::ElemPtr tmt;

   for (tmt = Filebox.GetFirst(); tmt != NULL; tmt++) {
      if (tmt->_Addr == Addr) {
         return tmt->_Path;
      }
   }   
   return NULL;
}

int SetFilebox(FA &f, char *tmt) {
char FPath[101];

//   Log.Level(LOGD) << "DEBUG0" <<EOL;

   if (strlen(tmt) == 0) {
      yyerror("Missed parameter: Path.");
      return (-1);
   }

   if (strlen(tmt) > 100) {
      yyerror("Path should be no more 100 characters.");
      return (-1);
   }

   if (!f.Valid()) {
      yyerror("Invalid address.");
      return (-1);
   }
   
   if (f.Masked()) {
      yyerror("You can't use mask in our address.");
      return (-1);
   }
   
   RSTRLCPY(FPath,tmt,100);
   AddFilebox(f,FPath);
   return(0);
}

void DestroyFilebox(void) {
   Filebox.Clear();
}

char *MakeFileboxName(FA &f, PKTMode m)
{
 static char Buff[BUFF_SIZE];
 char *tmt;
 Buff[0]='\0';
 
 if ((tmt=GetFilebox(f))!=NULL)
 {
  RSTRLCPY(Buff,tmt,100);
 }
 else
 {
  RSTRLCPY(Buff,FileBoxDir,BUFF_SIZE);
  if (FileBoxType == FILEBOXBRAKE) 
  {
   if (Buff[strlen(Buff)-1] != PATHDELIMC) {
    RSTRLCAT(Buff,PATHDELIMS,BUFF_SIZE);
   }    
   tmt=GetDomain(f);
   if (tmt) {
    RSTRLCAT(Buff,tmt,BUFF_SIZE);
   }    
   else {
    RSTRLCAT(Buff,"fidonet",BUFF_SIZE);
   }    
   RSTRLCAT(Buff,".",BUFF_SIZE);
  }
  if (FileBoxType == FILEBOXLONG || FileBoxType == FILEBOXTMLONG || FileBoxType == FILEBOXBRAKE)
  {
   if ((Buff[strlen(Buff)-1] != PATHDELIMC) && FileBoxType != FILEBOXBRAKE) {
    RSTRLCAT(Buff,PATHDELIMS,BUFF_SIZE);
   }    
   sprintf(Buff+strlen(Buff),"%u.%u.%u.%u",
         (word)(f.Zone() & 0xffff),
	 (word)(f.Net() & 0xffff),
	 (word)(f.Node() & 0xffff),
	 (word)(f.Point() & 0xffff)); 
  }
  if (FileBoxType == FILEBOXTMLONG && m == F_HOLD)
   RSTRLCAT(Buff,".h",BUFF_SIZE);
  if (FileBoxType == FILEBOXTMSHORT)
  {
   RSTRLCAT(Buff,dec232((word)(f.Zone() & 0xffff),2),BUFF_SIZE);
   RSTRLCAT(Buff,dec232((word)(f.Net() & 0xffff),3),BUFF_SIZE);
   RSTRLCAT(Buff,dec232((word)(f.Node() & 0xffff),3),BUFF_SIZE);
   RSTRLCAT(Buff,".",BUFF_SIZE);
   RSTRLCAT(Buff,dec232((word)(f.Point() & 0xffff),2),BUFF_SIZE);
   if (m == F_HOLD)
    RSTRLCAT(Buff,"h",BUFF_SIZE);
  }
  if (FileBoxType == FILEBOXBRAKE)
  {
   RSTRLCAT(Buff,".",BUFF_SIZE);
   switch(m)
   {
    case F_HOLD: RSTRLCAT(Buff,"hold",BUFF_SIZE); break;
    case F_DIRECT: RSTRLCAT(Buff,"direct",BUFF_SIZE); break;
    case F_CRASH: RSTRLCAT(Buff,"crash",BUFF_SIZE); break;
    case F_IMMEDIATE: RSTRLCAT(Buff,"immediate",BUFF_SIZE); break;
    default: RSTRLCAT(Buff,"normal",BUFF_SIZE); break;
   }
  }
 }
 return Buff;
}

// --------------------------------------------------------------------

int SetFileBoxDir(char *tmt) {
char Buf[BUFF_SIZE];

   if (strlen(tmt) == 0) {
      yyerror("Missed parameter: FileBox path.");
      return (-1);
   }
   if (!DirExists(tmt)) {
      yyerror("Directory not found.");
      return (-1);
   }
   RSTRLCPY(Buf,tmt,BUFF_SIZE);
   if (Buf[strlen(Buf)-1] != PATHDELIMC) {
      RSTRLCAT(Buf,PATHDELIMS,BUFF_SIZE);
   }                                                                                                            
   FileBoxDir = strdup(Buf);
   return 0;
}

int SetFileBoxType(fileboxType fbtype)
{
 static int flag = FALSE;

 if (flag) 
 {
  yyerror("FileBoxType: already defined.");
  return(-1);
 }
 flag = TRUE;

 FileBoxType = fbtype;
 return 0;
}


// ---------------------------- END --------------------------------------
