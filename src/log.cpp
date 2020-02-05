/*
 *  RNtrack - FTN message tracker/router
 *
 *  log.cpp - Work with log file
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
/*--------------------------------------------------------------------*/
/*                  Autoconf-generated include files                  */
/*--------------------------------------------------------------------*/

#ifdef HAVE_CONFIG_H
    #include "aconfig.h"
#endif

/*--------------------------------------------------------------------*/
/*                        System include files                        */
/*--------------------------------------------------------------------*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef HAVE_IO_H
    #include <io.h>
#endif
#include <string.h>
#include <assert.h>
#ifdef HAVE_UNISTD_H
    #include <unistd.h>
#endif

/*--------------------------------------------------------------------*/
/*                         Local include files                        */
/*--------------------------------------------------------------------*/
#include "compiler.h"
#include "mytypes.hpp"
#include "log.hpp"

/*--------------------------------------------------------------------*/
/*                         Global definitions                         */
/*--------------------------------------------------------------------*/
// #define DEBUG_LOG 1

/*--------------------------------------------------------------------*/
/*                      Functions prototypes                          */
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*    T i m e                                                         */
/*                                                                    */
/*    Print current time                                              */
/*--------------------------------------------------------------------*/
char * CurrTime(void)
{
    time_t td;
    struct tm * ts;
    static char Buff[60];

    time(&td);
    ts = localtime(&td);
    strftime(Buff, 60, "%X  ", ts);
    return Buff;
}

/*--------------------------------------------------------------------*/
/*    D a t e                                                         */
/*                                                                    */
/*    Print current date                                              */
/*--------------------------------------------------------------------*/
char * Date(void)
{
    time_t td;
    struct tm * ts;
    static char Buff[60];

    time(&td);
    ts = localtime(&td);
#ifdef SYSLOG_LOG_FORMAT
    strftime(Buff, 60, "%b %d %H:%M:%S", ts);
#else
    strftime(Buff, 60, "%Y-%m-%d %H:%M:%S", ts);
#endif
    return Buff;
}

/*--------------------------------------------------------------------*/
/*                       Class LogStream                              */
/*--------------------------------------------------------------------*/

LogStream::LogStream()
{
    fh      = NULL;
    NewLine = -1;
}

LogStream::~LogStream()
{
    Close();
}

int LogStream::Open(char * FName)
{
    if(strlen(FName) == 0)
    {
        fprintf(stderr, "Log file is not specified\n");
        return FALSE;
    }

    Close();
    fh = fopen(FName, "a+t");

    if(fh == NULL)
    {
        fprintf(stderr, "Unable to open log file '%s'\n", FName);
        return FALSE;
    }

    NewLine = -1;
    return 0;
}

int LogStream::Close(void)
{
    if(fh != NULL)
    {
        int tmt;
        fflush(fh);
        tmt = fclose(fh);
        fh  = NULL;
        return tmt;
    }
    else
    {
        return FALSE;
    }
}

void LogStream::LogLevel(uint Lvl)
{
    _LogLevel = Lvl;
}

LogStream & LogStream::Level(uint Lvl)
{
    cLogLevel = Lvl;
    return *this;
}

void LogStream::ShowLine(const char * format, ...)
{
    FILE * CurrFh;
    char * tmt, * tmt2;
    char * Buff;
    bool ToFile, ToScreen;
    va_list ll;

    ToFile   = TRUE;
    ToScreen = FALSE;

    if(fh == NULL)
    {
        CurrFh = stdout;
    }
    else
    {
        CurrFh = fh;
    }

    if(cLogLevel < 100 && cLogLevel > _LogLevel)
    {
        return;
    }

    if(cLogLevel >= 200 && cLogLevel - 200 > _LogLevel)
    {
        return;
    }

    if(cLogLevel >= 100 && cLogLevel < 200 && cLogLevel - 100 > _LogLevel)
    {
        return;
    }

    if(cLogLevel >= 100)
    {
        ToScreen = TRUE;
    }

    if(cLogLevel >= 200)
    {
        ToFile = FALSE;
    }

    if(ToScreen)
    {
        va_start(ll, format);
        vprintf(format, ll);
        va_end(ll);
        fflush(stdout);
    }

    if(ToFile && CurrFh != stdout)
    {
        Buff = (char *)malloc(20480);
        assert(Buff != NULL);
        tmt = Buff;
        va_start(ll, format);
        vsprintf(Buff, format, ll);
        va_end(ll);
        tmt2 = tmt;

        if(NewLine != 0)
        {
#if defined (__unix__) && defined (LOG_SHOW_PID)
            fprintf(CurrFh, "%s [%u] ", Date(), getpid());
#else
            fprintf(CurrFh, "%s ", Date());
#endif
            NewLine = 0;
        }

        while(*tmt != '\0')
        {
            tmt2 = tmt;

            if(NewLine != 0)
            {
#if defined (__unix__) && defined (LOG_SHOW_PID)
                fprintf(CurrFh, "%s [%u] ", Date(), getpid());
#else
                fprintf(CurrFh, "%s ", Date());
#endif
                NewLine = 0;
            }

            while(*tmt != '\n' && *tmt != '\0')
            {
                tmt++;
            }

            if(*tmt == '\0')
            {
                if(tmt2 != tmt)
                {
                    fputs(tmt2, CurrFh);
                }

                break;
            }

            if(*tmt == '\n')
            {
                NewLine = -1;
                *tmt    = '\0';

                if(tmt2 != tmt)
                {
                    fputs(tmt2, CurrFh);
                }

                *tmt = '\n';
                fputs("\n", CurrFh);
                tmt++;
            }
        }
        fflush(CurrFh);
        free(Buff);
    }
} // ShowLine

LogStream & LogStream::operator <<(const char * p)
{
    ShowLine("%s", p);
    return *this;
}

LogStream & LogStream::operator <<(char p)
{
    ShowLine("%c", p);
    return *this;
}

LogStream & LogStream::operator <<(sword i)
{
    ShowLine("%d", (int)i);
    return *this;
}

LogStream & LogStream::operator <<(int i)
{
    ShowLine("%d", i);
    return *this;
}

#ifdef HAS_INT64
LogStream & LogStream::operator <<(long t)
{
    ShowLine("%ld", t);
    return *this;
}

LogStream & LogStream::operator <<(unsigned long t)
{
    ShowLine("%ld", t);
    return *this;
}

LogStream & LogStream::operator <<(long long t)
{
    ShowLine("%lld", t);
    return *this;
}

LogStream & LogStream::operator <<(unsigned long long t)
{
    ShowLine("%lld", t);
    return *this;
}
#else
LogStream & LogStream::operator <<(time_t t)
{
    ShowLine("%ld", (long)t);
    return *this;
}

LogStream & LogStream::operator <<(word i)
{
    ShowLine("%u", (unsigned)i);
    return *this;
}

LogStream & LogStream::operator <<(dword i)
{
    ShowLine("%lu", (unsigned long)i);
    return *this;
}
#endif

LogStream & LogStream::operator <<(unsigned int i)
{
    ShowLine("%u", (unsigned int)i);
    return *this;
}
