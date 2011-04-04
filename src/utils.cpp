/** @file utils.cpp
 *  @brief Common routines
 */
/*
 *  RNtrack - FTN message tracker/router
 *
 *  utils.cpp - Common routines
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

#ifndef __unix__
    #include <process.h>
#endif
#ifndef __GNUC__
    #include <io.h>
    #include <direct.h>
#else
    #include <limits.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <errno.h>
#endif
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __EMX__
    #include <sys/nls.h>
#endif
#include <ctype.h>
#if defined (__FreeBSD__) || defined (__OpenBSD__) || defined (__NetBSD__) || \
    defined (__OSX__)
    #include <stdlib.h>
#else
    #include <malloc.h>
#endif
#include "log.hpp"
#include "mytypes.hpp"
#include "constant.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include <smapi/compiler.h>
#include "wildmat.hpp"

#ifdef __WATCOMC__
    #include <dos.h>
    #undef far
#endif

#ifdef __OS2__
    #include <os2.h>
#endif

#ifdef __NT__
    #undef byte
    #undef EXPENTRY
    #include <windows.h>
#endif

extern LogStream Log;

void CheckMem(char * ptr)
{
    if(ptr == NULL)
    {
        Log.Level(100) << "Internal Error. Out of memory." << EOL;
        exit(-1);
    }
}

int DirExists(char * ptr)
{
    struct stat dd;

    if(stat(dirslashbug(ptr), &dd) != 0)
    {
        Log.Level(105) << "DirExists: stat return -1. Errno: " << errno << EOL;
        return FALSE;
    }

    if(S_ISDIR(dd.st_mode))
    {
        return TRUE;
    }

    Log.Level(105) << "DirExists: dd.st_mode:" << dd.st_mode << EOL;
    return FALSE;
}

int StrIsNum(char * Str)
{
    while(*Str != '\0')
    {
        if(isdigit((uchar) * Str) == 0)
        {
            return FALSE;
        }

        Str++;
    }
    return TRUE;
}

int StrIsXNum(char * Str)
{
    while(*Str != '\0')
    {
        if(isxdigit(*Str) == 0)
        {
            return FALSE;
        }

        Str++;
    }
    return TRUE;
}

int FileCopy(char * Dst, char * Src)
{
#if defined (__OS2__) && !defined (__WATCOMC__)
    return DosCopy((uchar *)Src, (uchar *)Dst, 1) == 0;
#elif defined (__NT__)
    return CopyFile(Src, Dst, FALSE);
#else
    FILE * inf;
    FILE * ouf;
    char Buff[4096];
    size_t i;

    inf = fopen(Src, "r");

    if(inf == NULL)
    {
        return FALSE;
    }

    ouf = fopen(Dst, "w+");

    if(ouf == NULL)
    {
        fclose(inf);
        return FALSE;
    }

    clearerr(inf);
    clearerr(ouf);

    while(feof(inf) == 0)
    {
        i = fread(Buff, 1, 4096, inf);

        if(ferror(inf) != 0)
        {
            fclose(inf);
            fclose(ouf);
            unlink(Dst);
            return FALSE;
        }

        if(fwrite(Buff, 1, i, ouf) != i || ferror(ouf) != 0)
        {
            fclose(inf);
            fclose(ouf);
            unlink(Dst);
            return FALSE;
        }
    }
    fclose(inf);
    fclose(ouf);
    return TRUE;
#endif // if defined (__OS2__) && !defined (__WATCOMC__)
} // FileCopy

int FileMove(char * Dst, char * Src)
{
    if(!FileCopy(Dst, Src))
    {
        return FALSE;
    }

    if(unlink(Src) != 0)
    {
        return FALSE;
    }

    return TRUE;
}

FILE * fcopen(const char * Name, const char * Mode)
{
// Open file and create path if need.
    char * tmt;
    char Buff[1024];

    umask(0);
    strcpy(Buff, Name);
    tmt = strrchr(Buff, PATHDELIMC);

    if(tmt != NULL)
    {
        *tmt = '\0';
        tmt  = Buff;

        while((tmt = strchr(tmt, PATHDELIMC)) != NULL)
        {
            *tmt = '\0';
            mymkdir(Buff);
            *tmt = PATHDELIMC;
            tmt++;
        }
        strcpy(Buff, Name);
        *strrchr(Buff, PATHDELIMC) = '\0';
        mymkdir(Buff);
    }

    return fopen(Name, Mode);
} // fcopen

int ExecP(char * Name)
{
// hmm...
#if 0
    char Buff[4096];
    char * argv[200];
    char * tmt, * tmt2;
    int i;
    memset(argv, 0, sizeof(argv));
    strcpy(Buff, Name);
    tmt = Buff;
    i   = 0;

    do
    {
        tmt2 = strchr(tmt, ' ');

        if(tmt2 != NULL)
        {
            *tmt2   = '\0';
            argv[i] = tmt;
            tmt = tmt2 + 1;

            while(isspace((uchar) * tmt))
            {
                tmt++;
            }
            i++;
        }
    }
    while(tmt2 != NULL);
    argv[i] = tmt;
    i = spawnvp(P_WAIT, argv[0], argv);
    return i;

#endif // if 0
    return system(Name);
} // ExecP

char * GetFilePath(char * Path, char * Name)
{
    char * tmt;

    *Path = '\0';

    if(strlen(Name) == 0)
    {
        return NULL;
    }

    strcpy(Path, Name);

    if(Path[strlen(Path) - 1] == PATHDELIMC)
    {
        return Path;
    }

    tmt = strrchr(Path, PATHDELIMC);

    if(tmt != NULL)
    {
        tmt++;
        *tmt = '\0';
    }

#ifndef __unix__

    if(strcmp(Path, Name) == 0)
    {
        tmt = strchr(Path, ':');

        if(tmt != NULL)
        {
            tmt++;
            *tmt = '\0';
        }
    }

#endif

    if(strcmp(Path, Name) == 0)
    {
        *Path = '\0';
        return NULL;
    }

    return Path;
} // GetFilePath

char * GetFileName(char * FName, char * Name)
{
    char * tmt;

    *FName = '\0';

    if(strlen(Name) == 0)
    {
        return NULL;
    }

    if(Name[strlen(Name) - 1] == PATHDELIMC)
    {
        return NULL;
    }

    tmt = strrchr(Name, PATHDELIMC);

    if(tmt != NULL)
    {
        tmt++;
        strcpy(FName, tmt);
    }

#ifndef __unix__

    if(strlen(FName) == 0)
    {
        tmt = strchr(Name, ':');

        if(tmt != NULL)
        {
            tmt++;
            strcpy(FName, tmt);
        }
    }

#endif

    if(strlen(FName) == 0)
    {
        strcpy(FName, Name);
    }

    return FName;
} // GetFileName

void nls_strupr(char * s)
{
#ifdef __NT__
    char * s2 = strdup(s);

    if(s2)
    {
        int slen = strlen(s);

        OemToChar(s2, s);
        LCMapString(LOCALE_SYSTEM_DEFAULT, LCMAP_UPPERCASE, s, slen, s2,
                    slen + 1);
        CharToOem(s2, s);
        free(s2);
    }
#else
    while(*s)
    {
  #ifdef __EMX__
        *s = _nls_toupper((uchar) * s);
  #else
        *s = toupper((uchar) * s);
  #endif
        s++;
    }
#endif
} // nls_strupr

#ifdef __unix__
unsigned int filelength(int fh)
{
    struct stat bstat;

    if(fstat(fh, &bstat) != 0)
    {
        return 0;
    }

    return bstat.st_size;
}
#endif

//  ------------------------------------------------------------------
//  Returns current timezone offset based on TZ environment variable.
//  ------------------------------------------------------------------

int tzoffset()
{
    struct tm * a;
    int tz;
    time_t t;

    t   = time(NULL);
    a   = localtime(&t);
    tz  = a->tm_hour * 100 + a->tm_min;
    a   = gmtime(&t);
    tz -= a->tm_hour * 100 + a->tm_min;

    if(tz < -12 * 100)
    {
        tz += 24 * 100;
    }
    else if(tz > 12 * 100)
    {
        tz -= 24 * 100;
    }

    tz = tz / 100;
    return tz;
}

// #ifndef __unix__
#ifndef MAX_PATH
    #ifdef PATH_MAX
        #define MAX_PATH PATH_MAX
    #else
        #define MAX_PATH 1025
    #endif
#endif
// #endif

const char * dirslashbug(const char * dirname)
{
    static char newname[MAX_PATH];
    int len;

//   len = GetFullPathName(dirname, MAX_PATH, newname, &p);
//   if ((len > 3) && (newname[len-1] == PATHDELIMC)) {
    strcpy(newname, dirname);
    len = strlen(newname);

    if((len > 1) && (newname[len - 1] == PATHDELIMC))
    {
        newname[len - 1] = '\0';
    }

    return newname;
}

/** @brief get the first WORD (unsigned short) of a DWORD (unsigned int)
 *  @param[in] Dword
 *  @return the first WORD
 */
unsigned short & FirstWord(const unsigned int & Dword)
{
    struct SplitDWORD {unsigned short first; unsigned short second;};
    SplitDWORD * p = (SplitDWORD *)&Dword;
    return p->first;
}

int fsCompareName(const char * Name, const char * Mask)
{
#ifdef __unix__
    return wildmat(Name, Mask);
#else
    char NewName[MAX_PATH];
    char NewMask[MAX_PATH];
    strcpy(NewName, Name);
    strcpy(NewMask, Mask);
    strupr(NewName);
    strupr(NewMask);
    return wildmat(NewName, NewMask);
#endif
}

#if defined (__WATCOMC__) && defined (MSDOS)
    extern "C" 
    {
    // special function. Replaces located in SMAPI.
        void pascal far flush_handle2_(int fh){}
    }
#endif

int SetSemaphore(void)
{
    unsigned int SemTime;
    FILE * fh;

    SemTime = SemaphoreTime;

    if(Semaphore == NULL)
    {
        return TRUE;
    }

    do
    {
        if(access(Semaphore, F_OK) != 0)
        {
            break;
        }

        if(SemTime == SemaphoreTime)
        {
            Log.Level(101) << "Detected semaphore file '" << Semaphore <<
                              "'." << EOL;
        }

        sleep(1);
        SemTime--;
    }
    while(SemTime != 0);

    if(SemTime != SemaphoreTime)
    {
        if(access(Semaphore, F_OK) != 0)
        {
            Log.Level(101) << "Semaphore file '" << Semaphore <<
                              "' now released." << EOL;
        }
        else
        {
            Log.Level(101) << "Semaphore file '" << Semaphore <<
                              "' now ignored by time." << EOL;
        }
    }

    unlink(Semaphore);
    fh = fopen(Semaphore, "wb");

    if(fh == NULL)
    {
        Log.Level(100) << "Unable to create semaphore file '" << Semaphore <<
                          "'." << EOL;
        return FALSE;
    }

    fclose(fh);
    return TRUE;
} // SetSemaphore

int ReleaseSemaphore(void)
{
    if(Semaphore == NULL)
    {
        return TRUE;
    }

    unlink(Semaphore);
    return TRUE;
}

extern "C" 
{
    void ShowLogLine(char * msg)
    {
        Log.Level(102) << msg;
    }
}
