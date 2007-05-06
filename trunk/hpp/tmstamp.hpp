/*
 *  RNtrack - FTN message tracker/router
 *
 *  tmstamp.hpp - Check time of execution ScanDir's
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

#ifndef _TMSTAMP_HPP_
#define _TMSTAMP_HPP_

#ifdef HAVE_CONFIG_H
# include "aconfig.h"
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#elif HAVE_SYS_TIME_H
#include <sys/time.h>
#endif

#include "scandir.hpp"

class ScanDir;

class tTimes {
public:
   time_t _STime;
   time_t _ETime;
   tTimes() { _STime = 0; _ETime = 0; };
   ~tTimes() { return; };
   void Print(void);
};

time_t TimeOfBeginOfDay(int Day);
int GetLastTime(char *FName);
int InTime(IndBiList<tTimes>::ElemPtr tmt);

#endif
