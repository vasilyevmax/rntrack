/*
 *  RNtrack - FTN message tracker/router
 *
 *  attach.cpp - Work with attaches
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

#ifdef HAVE_CONFIG_H
# include "aconfig.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_IO_H
#include <io.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_DOS_H
#include <dos.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <ctype.h>
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#include <errno.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "fidoaddr.hpp"
#include "scandir.hpp"
#include "attach.hpp"
#include "outbound.hpp"
#include "mytypes.hpp"
#include "msg.hpp"

#ifdef __WATCOMC__
#undef far
#endif

#ifdef __NT__
#undef byte
#undef EXPENTRY
#include <windows.h>
#endif

// --------------------------------------------------------------------
static char NewPath[BUFF_SIZE];
static char NewSubj[73];
static int  AttSize;
static char FboxPath[BUFF_SIZE];
// --------------------------------------------------------------------

static char *BaseName(char *name) {
static char Buff[BUFF_SIZE];
char Buff1[BUFF_SIZE];
char *tmt;
   Buff[0]='\0';
   RSTRLCPY(Buff1,name,BUFF_SIZE);
   if ((tmt = strrchr(Buff1,PATHDELIMC)) != NULL) {
      tmt++;
      RSTRLCPY(Buff1,tmt,BUFF_SIZE);
   }
   if ((tmt = strrchr(Buff1,':')) != NULL) {
      tmt++;
      RSTRLCPY(Buff1,tmt,BUFF_SIZE);
   }
   if ((tmt = strrchr(Buff1,'/')) != NULL) {
      tmt++;
      RSTRLCPY(Buff1,tmt,BUFF_SIZE);
   }
   if ((tmt = strrchr(Buff1,'\\')) != NULL) {
      tmt++;
      RSTRLCPY(Buff1,tmt,BUFF_SIZE);
   }
   RSTRLCAT(Buff,Buff1,BUFF_SIZE);
   return Buff;

}

static char *FullName(char *name) {
static char Buff[BUFF_SIZE];
   if (FileInbound != NULL) {
      RSTRLCPY(Buff,FileInbound,BUFF_SIZE);
   } else {
      Buff[0] = '\0';
   }
   if ((strchr(name,PATHDELIMC) == NULL
#ifndef __unix__
   && strchr(name,':') == NULL
#endif
   ) || (IgnoreAttachPath != FALSE)) {
      RSTRLCAT(Buff,BaseName(name),BUFF_SIZE);
   } else {
      RSTRLCPY(Buff,name,BUFF_SIZE);
   }
   return Buff;
}


int _PrintAttach(char *Buff) {
   Log.Level(LOGI) << "Attached '" << FullName(Buff) << "'" << EOL;
   return TRUE;
}

int _AttToSize(char *Buff) {
int i;
int fh;
char *tmt;

   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
#endif
   fh = open(tmt,O_RDONLY | O_BINARY);
#ifdef __NT__
   CharToOem(tmt,tmt);
#endif
   i = errno;
   if (fh == -1) {
      if (i != ENOENT) {
         Log.Level(LOGE) << "   Unable to open file: '" << tmt << "', Errno: " << i << EOL;
         return FALSE;
      } else {
         return TRUE;
      }
   }

   i = filelength(fh);
   if (i == -1) {
      i = errno;
      close(fh);
      Log.Level(LOGE) << "   Unable to get size of file: '" << tmt << "', Errno: " << i << EOL;
      return FALSE;
   }
   close(fh);
   AttSize += i;
   return TRUE;
}

int _AddToLo(char *Buff) {
char tmt[BUFF_SIZE];
   tmt[0] = NewPath[0];
   tmt[1] = '\0';

   RSTRLCAT(tmt,FullName(Buff),BUFF_SIZE);

   AddToLo(tmt);
   return TRUE;
}

int _AddToFboxLo(char *Buff) {
char tmt[BUFF_SIZE];
   tmt[0] = NewPath[0];
   tmt[1] = '\0';

   if (FboxPath[0] != '\0')
   {
    RSTRLCAT(tmt,FboxPath,BUFF_SIZE);
    if (tmt[strlen(tmt)-1]!=PATHDELIMC) {
     RSTRLCAT(tmt,PATHDELIMS,BUFF_SIZE);
    }
    RSTRLCAT(tmt,BaseName(Buff),BUFF_SIZE);
   }
   else {
    RSTRLCAT(tmt,FullName(Buff),BUFF_SIZE);
   }

   AddToLo(tmt);
   return TRUE;
}

int _DelFromLo(char *Buff) {
   DelFromLo(FullName(Buff));
   return TRUE;
}

int _ChangePath(char *Buff) {
   RSTRLCAT(NewSubj,NewPath,72);
   RSTRLCAT(NewSubj,BaseName(Buff),72);
   RSTRLCAT(NewSubj," ",72);
   return TRUE;
}

int _ToLowerPath(char *Buff) {
char Buff1[BUFF_SIZE];
   RSTRLCPY(Buff1,Buff,BUFF_SIZE);
   for (unsigned int i=0;i<strlen(Buff1);i++)
    Buff1[i]=tolower(Buff1[i]);
   RSTRLCAT(NewSubj,Buff1,72);
   RSTRLCAT(NewSubj," ",72);
   return TRUE;
}

int _ToUpperPath(char *Buff) {
char Buff1[BUFF_SIZE];
   RSTRLCPY(Buff1,Buff,BUFF_SIZE);
   for (unsigned int i=0;i<strlen(Buff1);i++)
    Buff1[i]=toupper(Buff1[i]);
   RSTRLCAT(NewSubj,Buff1,72);
   RSTRLCAT(NewSubj," ",72);
   return TRUE;
}

int _DeleteAttach(char *Buff) {
char *tmt;
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
#endif
   if (access(tmt,F_OK) != 0) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGI) << "   File not found: '" << tmt << "'" << EOL;
      return TRUE;
   }
   if (unlink(tmt) != 0) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGE) << "   Unable to delete: '" << tmt << "'" << EOL;
      return FALSE;
   }
#ifdef __NT__
   CharToOem(tmt,tmt);
#endif
   Log.Level(LOGI) << "   Delete: '" << tmt << "'" << EOL;
   return TRUE;
}

int _AttachExists(char *Buff) {
struct stat dd;
char *tmt;
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
#endif
   if (stat(tmt,&dd) != 0) return FALSE;
   if (!S_ISREG(dd.st_mode)) return FALSE;
#ifdef __MINGW32__
   if (SkipHiddenFiles) {
      struct _finddata_t fd;
      int h = _findfirst(tmt, &fd);
      if (h != -1) {
         _findclose(h);
         if (!strcmp(fd.name, tmt) && (fd.attrib|_A_HIDDEN)) return FALSE;
      }
   }
#elif defined(__DJGPP__)
   if (SkipHiddenFiles) {
      unsigned int attrs;
      _dos_getfileattr(tmt, &attrs);
      if (attrs|_A_HIDDEN) return FALSE;
   }
#elif !defined(__unix__)
   if (SkipHiddenFiles && (dd.st_attr & 2)) return FALSE;
#endif
   return TRUE;
}

int _MoveAttach(char *Buff) {
char *tmt;
char B[BUFF_SIZE];
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
#endif
   if (access(tmt,F_OK) != 0) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGI) << "   File not found: '" << tmt << "'" << EOL;
      return TRUE;
   }
   RSTRLCPY(B,NewPath,BUFF_SIZE);
   RSTRLCAT(B,BaseName(Buff),BUFF_SIZE);
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
   OemToChar(B,B);
#endif
   if (!FileMove(B,tmt)) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGE) << "   Unable to move file '" << tmt << "' to " << NewPath << EOL;
      return FALSE;
   }
#ifdef __NT__
   CharToOem(tmt,tmt);
#endif
   Log.Level(LOGI) << "   Move: '" << tmt << "' ==> " << NewPath << EOL;
   return TRUE;
}

int _CopyAttach(char *Buff) {
char *tmt;
char B[BUFF_SIZE];
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
#endif
   if (access(tmt,F_OK) != 0) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGI) << "   File not found: '" << tmt << "'" << EOL;
      return TRUE;
   }
   RSTRLCPY(B,NewPath,BUFF_SIZE);
   RSTRLCAT(B,BaseName(Buff),BUFF_SIZE);
   tmt = FullName(Buff);
#ifdef __NT__
   OemToChar(tmt,tmt);
   OemToChar(B,B);
#endif
   if (!FileCopy(B,tmt)) {
#ifdef __NT__
      CharToOem(tmt,tmt);
#endif
      Log.Level(LOGE) << "   Unable to copy file '" << tmt << "' to " << NewPath << EOL;
      return FALSE;
   }
#ifdef __NT__
   CharToOem(tmt,tmt);
#endif
   Log.Level(LOGI) << "   Copy: '" << tmt << "' ==> " << NewPath << EOL;
   return TRUE;
}

// --------------------------------------------------------------------
#if defined(__unix__) || defined(__EMX__)

typedef int (*faff)(char *b);

int ForAllFiles(faff Action,cMSG &m) {
#else
int ForAllFiles(int (*Action)(char *Fname),cMSG &m) {
#endif
// For all Files attached to message do Action.
// return Action value.
// Action - int Action(char *FName);
char Buff[73];
char *tmt;
   if (m._Subject == NULL) {
      return FALSE;
   }
   if (strlen(m._Subject) == 0) {
      return FALSE;
   }
   memset(Buff,0,73);
   RSTRLCPY(Buff,m._Subject,72);
   tmt = Buff;
   while (*tmt == ' ') tmt++;
   if (*tmt == '\0') return FALSE;
   while (*tmt != '\0') {
      while (*tmt == ' ') tmt++;
      if (*tmt == '\0') break;
      int i;
      i = FALSE;
      if (strchr(tmt,' ') != NULL) {
         i = TRUE;
         *strchr(tmt,' ') = '\0';
      }
      if (!Action(tmt)) return FALSE;
      while (*tmt != '\0') tmt++;
      if (i) tmt++;
   }
   return TRUE;
}

// --------------------------------------------------------------------

int PrintAttach(cMSG &m) {
   return ForAllFiles(&_PrintAttach,m);
}

int AddAttachToLo(cMSG &m) {
   NewPath[0] = '\0';
   if (m.fTFS) {
      NewPath[0] = '#';
   }
   if (m.fKFS) {
      NewPath[0] = '^';
   }
   return ForAllFiles(&_AddToLo,m);
}

int AddFboxAttachToLo(cMSG &m, char *path) {
   NewPath[0] = '\0';
   if (m.fTFS) {
      NewPath[0] = '#';
   }
   if (m.fKFS) {
      NewPath[0] = '^';
   }
   RSTRLCPY(FboxPath,path,BUFF_SIZE);
   return ForAllFiles(&_AddToFboxLo,m);
}

int DelAttachFromLo(cMSG &m) {
   return ForAllFiles(&_DelFromLo,m);
}

int DeleteAttach(cMSG &m) {
   return ForAllFiles(&_DeleteAttach,m);
}

int ChangePath(cMSG &m,char *Path) {
int rc;
   RSTRLCPY(NewPath,Path,BUFF_SIZE);
   memset(NewSubj,0,73);
   if (strlen(NewPath) != 0 && NewPath[strlen(NewPath)-1] != PATHDELIMC) {
      RSTRLCAT(NewPath,PATHDELIMS,BUFF_SIZE);
   }

   rc = ForAllFiles(&_ChangePath,m);
   if (!rc) {
      return FALSE;
   }

   if (NewSubj[0] != '\0') {
      NewSubj[strlen(NewSubj)-1]='\0';
   }

   if (strlen(NewSubj) > 71) {
      Log.Level(LOGE) << "New subject too long. '" << NewSubj << "'" << EOL;
      return FALSE;
   }
   RSTRLCPY(m._Subject,NewSubj,72);
   return TRUE;
}


int ToLowerPath(cMSG &m) {
int rc;

   memset(NewSubj,0,73);
   rc = ForAllFiles(&_ToLowerPath,m);
   if (!rc) {
      return FALSE;
   }

   if (NewSubj[0] != '\0') {
      NewSubj[strlen(NewSubj)-1]='\0';
   }

   if (strlen(NewSubj) > 71) {
      Log.Level(LOGE) << "New subject too long. '" << NewSubj << "'" << EOL;
      return FALSE;
   }
   RSTRLCPY(m._Subject,NewSubj,72);
   return TRUE;
}

int ToUpperPath(cMSG &m) {
int rc;

   memset(NewSubj,0,73);
   rc = ForAllFiles(&_ToUpperPath,m);
   if (!rc) {
      return FALSE;
   }

   if (NewSubj[0] != '\0') {
      NewSubj[strlen(NewSubj)-1]='\0';
   }

   if (strlen(NewSubj) > 71) {
      Log.Level(LOGE) << "New subject too long. '" << NewSubj << "'" << EOL;
      return FALSE;
   }
   RSTRLCPY(m._Subject,NewSubj,72);
   return TRUE;
}

int GetAttSize(cMSG &m) {
int rc;
   AttSize = 0;
   rc = ForAllFiles(&_AttToSize,m);
   if (!rc) {
      return -1;
   }
   return AttSize;
}

int MoveAttach(cMSG &m,char *Path) {
int rc;
   RSTRLCPY(NewPath,Path,BUFF_SIZE);
   memset(NewSubj,0,73);
   if (strlen(NewPath) != 0 && NewPath[strlen(NewPath)-1] != PATHDELIMC) {
      RSTRLCAT(NewPath,PATHDELIMS,BUFF_SIZE);
   }

   rc = ForAllFiles(&_ChangePath,m);
   if (!rc) {
      return FALSE;
   }

   if (NewSubj[0] != '\0') {
      NewSubj[strlen(NewSubj)-1]='\0';
   }

   if (strlen(NewSubj) > 71) {
      Log.Level(LOGE) << "New subject too long. '" << NewSubj << "'" << EOL;
      return FALSE;
   }
   rc = ForAllFiles(&_MoveAttach,m);
   if (!rc) {
      return FALSE;
   }

//   strncpy(m._Subject,NewSubj,72);
   return TRUE;
}

int CopyAttach(cMSG &m,char *Path) {
int rc;
   RSTRLCPY(NewPath,Path,BUFF_SIZE);
   if (strlen(NewPath) != 0 && NewPath[strlen(NewPath)-1] != PATHDELIMC) {
      RSTRLCAT(NewPath,PATHDELIMS,BUFF_SIZE);
   }

   rc = ForAllFiles(&_CopyAttach,m);
   if (!rc) {
      return FALSE;
   }

   return TRUE;
}

int AttachExists(cMSG &m) {
   return ForAllFiles(&_AttachExists,m);
}

// --------------------------------------------------------------------
int SetFileInbound(char *tmt) {
IndBiList<ScanDir>::ElemPtr sd;
size_t size;

   sd = ScanDirs.GetLast();

   if (sd == NULL) {
      if (FileInbound != NULL) {
         yyerror("File inbound directory already defined.");
         return (-1);
      }
   } else {
      if (sd->_FileInbound != NULL) {
         yyerror("File inbound directory for this scandir already defined.");
         return (-1);
      }
   }
   if (strlen(tmt) == 0) {
      yyerror("Missing parameter: Inbound directory name.");
      return (-1);
   }
   if (!DirExists(tmt)) {
      yyerror("Unable to open file inbound directory.");
      return (-1);
   }

   size=strlen(tmt) + 2;

   if (sd == NULL) {
      FileInbound = (char *) malloc(size);
      CheckMem(FileInbound);
      RSTRLCPY(FileInbound,tmt,size);
      if (FileInbound[strlen(FileInbound)-1] != PATHDELIMC) {
         RSTRLCAT(FileInbound,PATHDELIMS,size);
      }
   } else {
      sd->_FileInbound = (char *) malloc(size);
      CheckMem(sd->_FileInbound);
      RSTRLCPY(sd->_FileInbound,tmt,size);
      if (FileInbound[strlen(sd->_FileInbound)-1] != PATHDELIMC) {
         RSTRLCAT(sd->_FileInbound,PATHDELIMS,size);
      }
   }
   return 0;
}

int SetSkipHiddenFiles(void) {
   if (SkipHiddenFiles) {
      yyerror("SkipHiddenFiles already set.");
      return (-1);
   }
   SkipHiddenFiles = TRUE;
   return (0);
}

// ---------------------------- END --------------------------------------
