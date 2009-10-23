/*
 *  RNtrack - FTN message tracker/router
 *
 *  tmstamp.cpp - Check time of execution ScanDir's
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
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "scandir.hpp"
#include "age.hpp"
#include "mytypes.hpp"
#include "tmstamp.hpp"
#include "wildmat.hpp"

// --------------------------------------------------------------------
time_t LastTime = 0;
// --------------------------------------------------------------------

void tTimes::Print(void){

   Log.Level(LOGD) << "#" << FromTime(_STime);
   if (_ETime != 0) {
      Log.Level(LOGD) << "-" << FromTime(_ETime);
   }
   Log.Level(LOGD) << "#";
}
// --------------------------------------------------------------------

time_t TimeOfBeginOfDay(int Day) {
time_t t;
struct tm *tmbuf;

   t = time(NULL);
   tmbuf = localtime(&t);
   tmbuf->tm_sec = 0;
   tmbuf->tm_min = 0;
   tmbuf->tm_hour = 0;
   t = mktime(tmbuf);
   if (Day == -1) {
      return t;
   }
   Day -= tmbuf->tm_wday;
//   if (Day < 0) {
//      Day += 7;
//   }
   t += Day * (24*60*60);
   return t;
}

// --------------------------------------------------------------------

int GetLastTime(char *FName) {
struct stat _fstat;

   if (access(FName,F_OK) != 0) {
      LastTime = 0;
      return TRUE;
   }
   if (stat(FName,&_fstat) != 0) {
      Log.Level(LOGE) << "Unable to get time from file '" << FName << '"' << EOL;
      return FALSE;
   }
   LastTime = _fstat.st_mtime;
   return TRUE;
}

// --------------------------------------------------------------------

int InTime(IndBiList<tTimes>::ElemPtr tmt) {
time_t CTime;
time_t ETime, STime;

   if (tmt == NULL) {
      return TRUE;
   }
   CTime = time(NULL);
   for (;tmt != NULL; tmt++) {                                                             
      ETime = tmt->_ETime;
      STime = tmt->_STime;
      Log.Level(LOGD) << "CTime == " << (int) CTime << " STime == " << (int) STime 
                      << " ETime == " << (int) ETime << " LastTime == " << (int) LastTime << EOL;
      if (ETime != 0) {
         if (CTime >= STime && CTime <= ETime) return TRUE;
      } else {
         if (LastTime <= STime && CTime >= STime) return TRUE;
      }
   }
   return FALSE;
}

// ---------------------------- END --------------------------------------
