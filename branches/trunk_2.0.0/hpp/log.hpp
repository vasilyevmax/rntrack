/*
 *  RNtrack - FTN message tracker/router
 *
 *  log.hpp - Work with log file
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

#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <stdio.h>
#include "mytypes.hpp"

#define EOL '\n'

class LogStream
{
    FILE * fh;
    uint _LogLevel;
    uint cLogLevel;
    int NewLine;
private:
    void ShowLine(const char * format, ...)
#ifdef __GNUC__
    __attribute__ ((format(printf, 2, 3)))
#endif
    ;

public:
    LogStream();
    ~LogStream();
    int Open(char * FName);

    int Opened(void)
    {
        return fh != NULL;
    }
    int Close(void);

    void LogLevel(uint);
    LogStream & Level(uint);
    LogStream & operator <<(const char * p);
    LogStream & operator <<(char p);
    LogStream & operator <<(int i);
    LogStream & operator <<(unsigned int i);
    LogStream & operator <<(sword i);    // smapi takes care for this, and
#ifdef HAS_INT64
    LogStream & operator <<(long t);
    LogStream & operator <<(unsigned long t);
    LogStream & operator <<(long long t);
    LogStream & operator <<(unsigned long long t);
#else
    LogStream & operator <<(time_t t);
    LogStream & operator <<(word i);     // word/sword is always a 16 bit int,
    LogStream & operator <<(dword i);    // dword is always 32 bit, even on a 64 bit host
#endif
};

char * Date(void);

#endif
