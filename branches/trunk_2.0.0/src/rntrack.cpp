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
#include "smapi/msgapi.h"

#ifdef HAVE_CONFIG_H
    #include "aconfig.h"
#endif

#ifdef TIME_WITH_SYS_TIME_H
    #include <time.h>
    #include <sys/time.h>
#elif defined (HAVE_TIME_H)
    #include <time.h>
#elif defined (HAVE_SYS_TIME_H)
    #include <sys/time.h>
#endif
#include <locale.h>
#ifdef HAVE_IO_H
    #include <io.h>
#endif
#ifdef HAVE_STRING_H
    #include <string.h>
#endif
#ifdef HAS_SYS_UTIME_H
    #include <sys/utime.h>
#elif defined (HAVE_UTIME_H)
    #include <utime.h>
#endif
#ifdef HAVE_SYS_TYPES_H
    #include <sys/types.h>
#elif defined (HAVE_TYPES_H)
    #include <types.h>
#endif
#ifdef HAVE_UNISTD_H
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

static struct utimbuf ut;
static struct _minf mnf;

unsigned RevisionLO; // software revision number, minor part
unsigned RevisionHI; // software revision number, major part

// --------------------------------------------------------------------
//                         Signals catch functions
// --------------------------------------------------------------------
void AbrtHndl(int Sign)
{
    FILE * fh;

    printf("Internal Error!!! Please, read report.err in documentation.\n");
    printf("---------------------------------------\n");
    printf("%s " PACKAGE_NAME " %s\n", Date(), ProgVersion);
    printf("Check point: %ld\n", (long int)CHP);
    printf("Signal: %u\n", Sign);
    printf("---------------------------------------\n");
    fh = fopen("RNtrack.err", "a+t");

    if(fh != NULL)
    {
        fprintf(
            fh,
            "Internal Error!!! Please, read report.err in documentation.\n");
        fprintf(fh, "---------------------------------------\n");
        fprintf(fh, "%s " PACKAGE_NAME " %s\n", Date(), ProgVersion);
        fprintf(fh, "Check point: %ld\n", (long int)CHP);
        fprintf(fh, "Signal: %u\n", Sign);
        fprintf(fh, "---------------------------------------\n");
    }

    fclose(fh);
    ReleaseSemaphore();
    exit(-1);
} // AbrtHndl

// --------------------------------------------------------------------
//                            Init all subsystems.
// --------------------------------------------------------------------
int InitSystem(void)
{
#ifndef _DEBUG
    CHP = 99100;
    signal(SIGSEGV, &AbrtHndl);
    signal(SIGILL, &AbrtHndl);
#endif

/*  if(sizeof(int) != 4 || sizeof(long) != 4)
    {
        fprintf(stderr,
        "RNtrack was compiled for a wrong platform.\nPlease, inform the packager.\n"                                                                    );
    
        if(sizeof(long) == 8 && sizeof(void *) == 8 && sizeof(int) == 4)
        {
            fprintf(stderr,
                "Continue at your own risk! This software is not 64-bit ready yet!\n"                                                                    );
        }
        else
        {
            return FALSE;
        }
    } */
    
    CHP = 99101;
    tzset();
    CHP = 99102;
    Log.LogLevel(2);
    memset(&mnf, '\0', sizeof(mnf));
    CHP = 99103;
    mnf.req_version = 1;
    MsgOpenApi(&mnf);
    CHP = 99104;


    if(!InitScriptSystem())
    {
        Log.Level(LOGE) << "Unable to start script system" << EOL;
        return FALSE;
    }

    if(ConfigFile == NULL)
    {
        ConfigFile = strdup(DefaultConfig);
    }

    CHP = 99105;

    if(ParseConfig((const char *)ConfigFile) != 0)
    {
        CHP = 9910501;
        return FALSE;
    }

    CHP = 99106;

    if(!MyAddr.Valid())
    {
        Log.Level(LOGE) << "Error. Own Address is not defined." << EOL;
        return FALSE;
    }

    if(ForceINTL)
    {
        UseOwnZone = TRUE;
    }

    if(!Ndl.Load())
    {
        return FALSE;
    }

    if(!InitOutbound())
    {
        return FALSE;
    }

    if(!SetSemaphore())
    {
        return FALSE;
    }

    InitScriptValues();

    char * tmp = (char *)"BeforeWork";
    switch(DoSomeWordRc(tmp))
    {
        case SS_ERROR:
            return FALSE;

        default:
            break;
    }

    {
        char * rev1 = strdup(VERSION);

        if(rev1)
        {
            char * rev2 = strtok(rev1, ".");
            RevisionLO = atoi(rev2);
            RevisionHI = atoi(rev1);
            free(rev1);
        }
    }
    return TRUE;
} // InitSystem

// --------------------------------------------------------------------
//                         Shutdown all subsystems.
// --------------------------------------------------------------------
void DoneSystem(void)
{
    int i;

//   ScanDirs.clearAndDestroy();
    char * tmp = (char *)"AfterWork";
    DoSomeWord(tmp);
    CHP = 99200;
    DestroyAka();
    CHP = 99201;
    DestroyPasswd();
    CHP = 99202;

    if(!StopScriptSystem())
    {
        if(Log.Opened())
        {
            CHP = 99203;
            Log.Level(LOGE) <<
            "Error at deinitialisation scripts subsystem." << EOL;
        }
    }

    if(LogLevel != 0 && Log.Opened())
    {
        CHP = 99204;
        Log.Level(LOGE) << "--- RNtrack " << ProgVersion << " stopped." << EOL;
        Log.Close();
    }

    CHP = 99205;

    if(TimeStampFile != NULL)
    {
        CHP = 99206;

        if(utime(TimeStampFile, &ut) != 0)
        {
            CHP = 99207;
            i   = errno;
            Log.Level(LOGE) << "Unable to set modification time for file '" <<
                               TimeStampFile << "'. Errno: " << i << EOL;
            CHP = 99208;
        }

        CHP = 99209;
    }

    ReleaseSemaphore();
    CHP = 99210;
} // DoneSystem

// --------------------------------------------------------------------
//                              M A I N
// --------------------------------------------------------------------
int main(int argc, char * argv[])
{
    int Option;
    int DoScan;
    char * tmpCf;

    setlocale(LC_CTYPE, "");
    CHP = 99000;
    ut.actime  = time(NULL);
    ut.modtime = time(NULL);

    DoScan = FALSE;
    CHP    = 99001;

    tmpCf = getenv("RNTRACKCONFIG");

    if(tmpCf)
    {
        ConfigFile = strdup(tmpCf);
    }

    while((Option = ParseCmdArgs(argc, argv, "c:uh?tv")) != EOF)
    {
        switch(Option)
        {
            case 'u':
                UnpackNeed = TRUE;
                break;

            case 'c': /* Kill all mail */
                ConfigFile = strdup(optionArg);
                break;

            case 't':
                DoScan = TRUE;
                break;

            case '?':
                Help();
                exit(1);

            case 'h':
                Hello();
                Help();
                exit(0);

            case 'v':
                Hello();
                exit(0);
        } /* switch */
    } /* while */

// ---

    CHP = 99002;

    if(!InitSystem())
    {
        return -1;
    }

    CHP = 99003;
    atexit(&DoneSystem);

    if(DoScan)
    {
        LastTime = 0;
    }

// ---

    CHP = 99004;

    if(UnpackNeed)
    {
        if(!DoRepack())
        {
            return -1;
        }
    }

    if(LogLevel >= 5)
    {
        PrintScanDirs();
    }

    CHP = 99005;
    DoScanDirs();

    return 0;
} // main

// ---------------------------- END --------------------------------------
