/*
 *  RNtrack - FTN message tracker/router
 *
 *  rntrack.cpp - Main module
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

#include <locale.h>
#ifndef UNIX
#include <io.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#if !defined (UNIX) && !defined(__DJGPP__)
#include <sys/utime.h>
#else
#include <sys/types.h>
#include <utime.h>
#include <errno.h>
#include <unistd.h>
#endif
#ifdef __SUN__
#include <time.h>
#endif
#include "constant.hpp"
#include "vars.hpp"
#include "help.hpp"
#include "getopt.hpp"
#include "configure.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "scandir.hpp"
#include "aka.hpp"
#include "passwd.hpp"
#include "parsetpl.hpp"
#include "tmstamp.hpp"
#include "script.hpp"
#include <smapi/msgapi.h>

static struct utimbuf ut;
static struct _minf mnf;

// --------------------------------------------------------------------
//                         Signals catch functions
// --------------------------------------------------------------------
void AbrtHndl(int Sign) {
FILE *fh;

   printf("Internal Error!!! Please, read report.err in documentation.\n");
   printf("---------------------------------------\n");
   printf("%s RNtrack %s\n",Date(),ProgVersion);
   printf("Check point: %ld\n",(long int)CHP);
   printf("Signal: %u\n",Sign);
   printf("---------------------------------------\n");
   fh = fopen("RNtrack.err","a+t");
   if (fh != NULL) {
      fprintf(fh,"Internal Error!!! Please, read report.err in documentation.\n");   
      fprintf(fh,"---------------------------------------\n");
      fprintf(fh,"%s RNtrack %s\n",Date(),ProgVersion);
      fprintf(fh,"Check point: %ld\n",(long int)CHP);
      fprintf(fh,"Signal: %u\n",Sign);
      fprintf(fh,"---------------------------------------\n");
   }
   fclose(fh);
   ReleaseSemaphore();
   exit(-1);
}

// --------------------------------------------------------------------
//                            Init all subsystems.
// --------------------------------------------------------------------
int InitSystem(void) {

#ifndef _DEBUG
   CHP = 99100;
   signal(SIGSEGV,&AbrtHndl);
   signal(SIGILL,&AbrtHndl);
#endif

/*   if (sizeof(int) != 4 || sizeof(long) != 4) {
      fprintf(stderr,"RNtrack compiled for wrong platform.\nPlease, call to author.\n");
      if (sizeof(long) == 8 && sizeof(void *) == 8 && sizeof(int) == 4) {
          fprintf(stderr,"Continue at your own risk! This software is not 64-bit ready yet!\n");
      } else {
          return FALSE;
      }
   }*/
   CHP = 99101;
   tzset();
   CHP = 99102;
   Log.LogLevel(2);
   memset(&mnf, '\0', sizeof (mnf));
   CHP = 99103;
   mnf.req_version = 1;
   MsgOpenApi(&mnf);
   CHP = 99104;


   if (InitScriptSystem() != TRUE) {
      Log.Level(LOGE) << "Unable to start script system" << EOL;
	  return FALSE;
   }
   if (ConfigFile == NULL) {
      ConfigFile = strdup(DefaultConfig);
   }
   CHP = 99105;

   if (ParseConfig(ConfigFile) != 0) {
      CHP = 9910501;
      return FALSE;
   }

   CHP = 99106;
   if (!MyAddr.Valid()) {
      Log.Level(LOGE) << "Error. Own Address is not defined." << EOL;
      return FALSE;
   }
   if (ForceINTL) {
      UseOwnZone = TRUE;
   }

   if (!Ndl.Load()) {
      return FALSE;
   }

   if (!InitOutbound()) {
      return FALSE;
   }

   if (!SetSemaphore()) {
      return FALSE;
   }

   InitScriptValues();

   switch (DoSomeWordRc("BeforeWork")) {
      case SS_ERROR: return FALSE;
      default: break;
   }

   return TRUE;
}

// --------------------------------------------------------------------
//                         Shutdown all subsystems.
// --------------------------------------------------------------------
void DoneSystem(void) {
int i;

//   ScanDirs.clearAndDestroy();
   DoSomeWord("AfterWork");
   CHP = 99200;
   DestroyAka();
   CHP = 99201;
   DestroyPasswd();
   CHP = 99202;
   StopScriptSystem();
   if (Log.Opened() && LogLevel != 0) {
      CHP = 99203;
      Log.Level(LOGE) << "--- RNtrack " << ProgVersion << " stopped." << EOL;
      Log.Close();
   }
   CHP = 99204;
   if (TimeStampFile != NULL) {
      CHP = 99205;
      if (utime(TimeStampFile,&ut) != 0) {
         CHP = 99206;
         i = errno;
         Log.Level(LOGE) << "Unable to set modification time for file '" << TimeStampFile << "'. Errno: " << i << EOL;
         CHP = 99207;
      }
      CHP = 99208;
   }
   ReleaseSemaphore();
   CHP = 99209;
}

// --------------------------------------------------------------------
//                              M A I N
// --------------------------------------------------------------------
int main (int argc, char *argv[]) {
int Option;
int DoScan;
char *tmpCf;

   setlocale(LC_CTYPE, "");
   CHP = 99000;
   ut.actime = time(NULL);
   ut.modtime = time(NULL);
   Hello();

   DoScan = FALSE;
   CHP = 99001;

   tmpCf = getenv("RNTRACKCONFIG");
   
   if (tmpCf)
    ConfigFile = strdup(tmpCf);
   
   while ((Option = ParseCmdArgs(argc, argv, "c:uh?t")) != EOF) {
      switch (Option) {
         case 'u' : UnpackNeed = TRUE;
                    break;
         case 'c' : /* Kill all mail */
                    ConfigFile = strdup(optionArg);
                    break;
         case 't' : DoScan = TRUE;
                    break;
         case '?' :
         case 'h' : Help(); exit(0);
      } /* switch */
   } /* while */

// ---
   atexit(&DoneSystem);

   CHP = 99002;
   if (!InitSystem()) {
      return (-1);
   }
   CHP = 99003;
   if (DoScan) {
      LastTime = 0;
   }
// ---

   if (UnpackNeed) {
      if (!DoRepack()) {
         return (-1);
      }
   }

   if (LogLevel >= 5) {
      PrintScanDirs();
   }

   DoScanDirs();

   return (0);
}

// ---------------------------- END --------------------------------------
