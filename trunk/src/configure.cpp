/*
 *  RNtrack - FTN message tracker/router
 *
 *  configure.cpp - Configuration routines
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

#ifdef HAVE_UNISTD_H
    #include <unistd.h>
#endif
#ifdef HAVE_IO_H
    #include <io.h>
#endif

#ifdef HAVE_STRING_H
    #include <string.h>
#endif
#ifdef HAVE_STDLIB_H
    #include <stdlib.h>
#endif
#include <ctype.h>

/*--------------------------------------------------------------------*/
/*                 Library function (re)definitions                   */
/*--------------------------------------------------------------------*/

#if !defined (stricmp) && !defined (HAVE_STRICMP) && defined (HAVE_STRCASECMP)
    #define stricmp(s1, s2) strcasecmp(s1, s2)
#endif

/*--------------------------------------------------------------------*/
/*                        Program include files                       */
/*--------------------------------------------------------------------*/

#include "constant.hpp"
#include "vars.hpp"
#include "log.hpp"
#include "configure.hpp"
#include "scandir.hpp"
#include "cfg.hpp"
#if defined (__PERL_VERSION__)
    #include "script.hpp"
#endif

/*--------------------------------------------------------------------*/
/*                         Global definitions                         */
/*--------------------------------------------------------------------*/
int yyparse(void);

/*--------------------------------------------------------------------*/
/*                          Global variables                          */
/*--------------------------------------------------------------------*/

static FILE * fh;           // Configuration file handler
int nxtch;                  // Next character. Used by Lex
int LineNumber;             // Current Line number
int CharNumber;             // Position in the current line

char * chpool;              // Pool for String's & Token's
int avail = 0;              // Current position in Pool.
int DetectError;            // Detected error in config file
bool NoTokensF = FALSE;     // Special state of lexx. No tokens!
char * CurrentLine;         // Current translated line
FA cffa;
FA cffa1;
FA cffa2;

/*--------------------------------------------------------------------*/
/*                          Predefined tokens                         */
/*--------------------------------------------------------------------*/

static struct
{
    const char * kw;
    int ltp;
}
kwtable[] =
{
    {"Action:", _ACTION},
    {"Mask:", _MASK},
    {"*Mask:", _SMASK},
    {"+Mask:", _PMASK},
    {"Route", _ROUTE},
    {"RouteFilebox", _ROUTEFBOX},
    {"RouteHub", _ROUTEHUB},
    {"Hold", _HOLD},
    {"Direct", _DIRECT},
    {"Crash", _CRASH},
    {"Normal", _NORMAL},
    {"Immediate", _IMMEDIATE},
    {"AddNote", _ADDNOTE},
    {"Copy", _COPY},
    {"Rewrite", _REWRITE},
    {"Ignore", _IGNORE},
    {"Display", _DISPLAY},
    {"DelFile", _DELFILE},
    {"NewMsg", _NEWMSG},
    {"WriteFile", _WRITEFILE},
    {"AppendToFile", _APPENDTOFILE},
    {"Call", _CALL},
    {"Poll", _POLL},
    {"Script", _ASCRIPT},
    {"DeleteAttach", _DELETEATTACH},
    {"ChangePath", _CHANGEPATH},
    {"ToLowerPath", _TOLOWERPATH},
    {"ToUpperPath", _TOUPPERPATH},
    {"AddKludge", _ADDKLUDGE},
    {"MoveAttach", _MOVEATTACH},
    {"MoveAttachFilebox", _MOVEATTACHFBOX},
    {"CopyAttach", _COPYATTACH},
    {"CopyAttachFilebox", _COPYATTACHFBOX},
    {"Split", _SPLIT},
    {"Recode", _RECODE},
    {"LogFile:", _LOGFILE},
    {"TimeStampFile:", _TIMESTAMPFILE},
    {"LogLevel:", _LOGLEVEL},
    {"Nodelist:", _NODELIST},
    {"IndexFile:", _INDEXFILE},
    {"NodelistPath:", _NODELISTPATH},
    {"Address:", _ADDRESS},
    {"SysopName:", _SYSOPNAME},
    {"UseOwnZone", _USEOWNZONE},
    {"ForceINTL", _FORCEINTL},
    {"LoopStr:", _LOOPSTR},
    {"ScanDir:", _SCANDIR},
    {"BodyMask:", _BODYMASK},
    {"*BodyMask:", _SBODYMASK},
    {"+BodyMask:", _PBODYMASK},
    {"KludgeMask:", _KLUDGEMASK},
    {"*KludgeMask:", _SKLUDGEMASK},
    {"+KludgeMask:", _PKLUDGEMASK},
    {"ScriptMask:", _SCRIPTMASK},
    {"*ScriptMask:", _SSCRIPTMASK},
    {"+ScriptMask:", _PSCRIPTMASK},
    {"MaxAge:", _MAXAGE},
    {"BadMessages:", _BADMESSAGES},
    {"BadPackets:", _BADPACKETS},
    {"NoLogIgnore", _NOLOGIGNORE},
    {"Aka:", _AKA},
    {"SkipHiddenFiles", _SKIPHIDDENFILES},
    {"FileInbound:", _FILEINBOUND},
    {"Outbound:", _OUTBOUND},
    {"FileBoxDir:", _FILEBOXDIR},
    {"FileBoxType:", _FILEBOXTYPE},
    {"AddToNullPkt", _ADDTONULLPKT},
    {"TempMail:", _TEMPMAIL},
    {"TrafficLog:", _TRAFFICLOG},
    {"Password:", _PASSWORD},
    {"Domain:", _DOMAIN},
    {"FileBox:", _FILEBOX},
    {"UseFileBoxes", _USEFILEBOXES},
    {"UTC:", _UTC},
    {"Origin:", _ORIGIN},
    {"Tearline:", _TEARLINE},
    {"Include:", _INCLUDE},
    {"APktDir:", _APKTDIR},
    {"CreateMissingBase", _CREATEMISSINGBASE},
    {"MaxAttachSize:", _MAXATTACHSIZE},
    {"MaxMsgSize:", _MAXMSGSIZE},
    {"MaxPktSize:", _MAXPKTSIZE},
    {"KillRoutedMessage:", _KILLROUTEDMESSAGE},
    {"MaxNodelistAge:", _MAXNODELISTAGE},
    {"UseNewVia", _USENEWVIA},
    {"SetViaAlways", _SETVIAALWAYS},
    {"SoftCheckInNodelists", _SOFTCHECKINNODELIST},
    {"CheckPoints:", _CHECKPOINTS},
    {"TrafficLogTemplate:", _TRAFFICLOGTEMPLATE},
    {"Skip", _SKIP},
    {"Delete", _DELETE},
    {"Exit", _EXIT},
    {"Move", _MOVE},
    {"Long", _LONG},
    {"Tmlong", _TMLONG},
    {"Tmshort", _TMSHORT},
    {"Brake", _BRAKE},
    {"@BeforeRoute", _BEFOREROUTE},
    {"@AfterRoute", _AFTERROUTE},
    {"Renumber", _RENUMBER},
    {"Unpack", _UNPACK},
    {"Daily", _DAILY},
    {"Weekly", _WEEKLY},
    {"Flag", _FLAG},
    {"Never", _NEVER},
    {"Hard", _HARD},
    {"Soft", _SOFT},
    {"Always", _ALWAYS},
    {"Semaphore:", _SEMAPHORE},
    {"UseASO", _USEASO},
    {"UseBrake", _USEBRAKE},
    {"ScriptFile:", _SCRIPTFILE},
    {"IgnoreBSY", _IGNOREBSY},
    {"IgnoreAttachPath", _IGNOREATTACHPATH},
    {"Fresh", _FRESH},
    {"ScriptBefore", _BEFORESCRIPT},
    {"ScriptAfter", _AFTERSCRIPT},
    {"AgeFromVia", _AGEFROMVIA},
    {NULL, LEXERR},
};

// --------------------------------------------------------------------

int SetMyAddr(FA & f)
{
    if((MyAddr.Zone() & FA_NOTDEF) == 0)
    {
        yyerror("Address already defined.");
        return -1;
    }

    MyAddr = f;

    if(!MyAddr.Valid())
    {
        yyerror("Invalid FTN Address.");
        return -1;
    }

    if(MyAddr.Masked())
    {
        yyerror("You can't use mask in our address.");
        return -1;
    }

    return 0;
}

// --------------------------------------------------------------------

int SetSemaphoreName(char * File, unsigned int SemTime)
{
    if(Semaphore != NULL)
    {
        yyerror("Semaphore is already set");
        return -1;
    }

    if(strlen(File) == 0)
    {
        yyerror("Missing parameter: Semaphore file name.");
        return -1;
    }

    Semaphore = strdup(File);
    SemaphoreTime = SemTime;
    return 0;
}

// --------------------------------------------------------------------

int SetTimeStampFile(char * tmt)
{
    FILE * fh;

    if(TimeStampFile != NULL)
    {
        yyerror("Timestamp file already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Timestamp file name.");
        return -1;
    }

    if(access(tmt, W_OK) != 0)  /* attempt to create file */
    {
        fh = fopen(tmt, "a");

        if(fh == NULL)
        {
            yyerror("Unable to create Timestamp file");
            return -1;
        }
        else
        {
            fclose(fh);
        }
    }

    TimeStampFile = strdup(tmt);

    if(!GetLastTime(TimeStampFile))
    {
        return -1;
    }

    return 0;
} // SetTimeStampFile

// --------------------------------------------------------------------

int SetLogFile(char * tmt)
{
    if(LogFileName != NULL)
    {
        yyerror("Log file already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Log file name.");
        return -1;
    }

    LogFileName = strdup(tmt);

    if(Log.Open(LogFileName) != 0)
    {
        return -1;
    }

    if(LogLevel != 0)
    {
        Log.Level(LOGE) << "--- RNtrack " << ProgVersion << " started." << EOL;
    }

    return 0;
} // SetLogFile

// --------------------------------------------------------------------

int SetTrafficLogTemplate(char * tmt)
{
    if(TrafficLogTpl != NULL)
    {
        yyerror("Template for Traffic log already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: File name of Template for traffic Log.");
        return -1;
    }

    TrafficLogTpl = strdup(tmt);

    return 0;
}

// --------------------------------------------------------------------

int SetLogLevel(int tmt)
{
    if(LogLevel != -1)
    {
        yyerror("LogLevel already set.");
        return -1;
    }

    if(tmt < 0 || tmt > 65535)
    {
        yyerror("Parameter must be a number between 0 and 65535.");
        return -1;
    }

    Log.LogLevel(tmt);
    LogLevel = tmt;
    return 0;
}

// ---------------------------------------------------------------------

int LoadScriptFile(char * fname)
{
#if defined (__PERL_VERSION__)

    if(strlen(fname) == 0)
    {
        yyerror("Missing parameter: Script file name.");
        return -1;
    }

    if(access(fname, R_OK) != 0)
    {
        yyerror("Script file not found.");
        return -1;
    }

    if(_LoadScriptFile(fname) != 0)
    {
        return -1;
    }

    return 0;

#else
    yyerror("RNtrack compiled without script system support. Sorry.");
    fname = fname;
    return -1;

#endif /* defined(__PERL_VERSION__) */
} // LoadScriptFile

// ---------------------------------------------------------------------
int SetCreateMissingBase(void)
{
    if(CreateMissingBase)
    {
        yyerror("CreateMissingBase already set.");
        return -1;
    }

    CreateMissingBase = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetForceINTL(void)
{
    if(ForceINTL)
    {
        yyerror("ForceINTL already set.");
        return -1;
    }

    ForceINTL = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetAgeFromVia(void)
{
    if(AgeFromVia)
    {
        yyerror("AgeFromVia already set.");
        return -1;
    }

    AgeFromVia = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetNoLogIgnore(void)
{
    if(!LogIgnore)
    {
        yyerror("NoLogIgnore already set.");
        return -1;
    }

    LogIgnore = FALSE;
    return 0;
}

// --------------------------------------------------------------------

int SetSetViaAlways(void)
{
    if(SetViaAlways)
    {
        yyerror("SetViaAlways already set.");
        return -1;
    }

    SetViaAlways = 1;
    return 0;
}

// --------------------------------------------------------------------

int SetIgnoreBSY(void)
{
    if(IgnoreBSY)
    {
        yyerror("IgnoreBSY already set.");
        return -1;
    }

    IgnoreBSY = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetIgnoreAttachPath(void)
{
    if(IgnoreAttachPath)
    {
        yyerror("IgnoreAttachPath already set.");
        return -1;
    }

    IgnoreAttachPath = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetStripPathInPkt(void)
{
    if(StripPathInPKT)
    {
        yyerror("StripPathInPKT already set.");
        return -1;
    }

    StripPathInPKT = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetMaxAttach(int tmt)
{
    IndBiList<ScanDir>::ElemPtr sd;

    sd = ScanDirs.GetLast();

    if(sd == NULL)
    {
        if(MaxAttachSize != 0)
        {
            yyerror("Global MaxAttachSize already defined.");
            return -1;
        }
    }
    else
    {
        if(sd->_MaxAttachSize != 0)
        {
            yyerror("MaxAttachSize for this ScanDir already defined.");
            return -1;
        }
    }

    if(tmt < 1)
    {
        yyerror("Parameter must be a number greater than 0.");
        return -1;
    }

    if(sd != NULL)
    {
        sd->_MaxAttachSize = tmt;
    }
    else
    {
        MaxAttachSize = tmt;
    }

    return 0;
} // SetMaxAttach

// --------------------------------------------------------------------

int SetMaxMsgSize(int tmt)
{
    IndBiList<ScanDir>::ElemPtr sd;

    sd = ScanDirs.GetLast();

    if(sd == NULL)
    {
        if(MaxMsgSize != 0)
        {
            yyerror("Global MaxMsgSize already defined.");
            return -1;
        }
    }
    else
    {
        if(sd->_MaxMsgSize != 0)
        {
            yyerror("MaxMsgSize for this ScanDir already defined.");
            return -1;
        }
    }

    if(tmt < 0)
    {
        yyerror("Parameter can't be a negative number.");
        return -1;
    }

    if(sd != NULL)
    {
        sd->_MaxMsgSize = tmt;
    }
    else
    {
        MaxMsgSize = tmt;
    }

    return 0;
} // SetMaxMsgSize

// --------------------------------------------------------------------

int SetMaxPktSize(int tmt)
{
    IndBiList<ScanDir>::ElemPtr sd;

    sd = ScanDirs.GetLast();

    if(sd == NULL)
    {
        if(MaxPktSize != 0)
        {
            yyerror("Global MaxPktSize already defined.");
            return -1;
        }
    }
    else
    {
        if(sd->_MaxPktSize != 0)
        {
            yyerror("MaxPktSize for this ScanDir already defined.");
            return -1;
        }
    }

    if(tmt < 0)
    {
        yyerror("Parameter can't be a negative number.");
        return -1;
    }

    if(sd != NULL)
    {
        sd->_MaxPktSize = tmt;
    }
    else
    {
        MaxPktSize = tmt;
    }

    return 0;
} // SetMaxPktSize

// --------------------------------------------------------------------

int SetLoopStr(char * tmt)
{
    IndBiList<ScanDir>::ElemPtr sd;

    sd = ScanDirs.GetLast();

    if(sd == NULL)
    {
        if(LoopStr != NULL)
        {
            yyerror("Loop string already defined.");
            return -1;
        }
    }
    else
    {
        if(sd->_LoopStr != 0)
        {
            yyerror("Loop string for this ScanDir already defined.");
            return -1;
        }
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Loop string.");
        return -1;
    }

    if(sd != NULL)
    {
        sd->_LoopStr = strdup(tmt);
    }
    else
    {
        LoopStr = strdup(tmt);
    }

    return 0;
} // SetLoopStr

// --------------------------------------------------------------------

int SetOrigin(char * tmt)
{
    if(Origin != NULL)
    {
        yyerror("Origin already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Origin string.");
        return -1;
    }

    if(strlen(tmt) > 70)
    {
        yyerror("Origin string too long. Max Origin length is 70 characters.");
        return -1;
    }

    Origin = strdup(tmt);
    return 0;
}

// --------------------------------------------------------------------

int SetSysopName(char * tmt)
{
    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Sysop name.");
        return -1;
    }

    if(SysopName != NULL)
    {
        yyerror("Sysop name already defined.");
        return -1;
    }

    SysopName = strdup(tmt);
    return 0;
}

// --------------------------------------------------------------------

int SetTearline(char * tmt)
{
    if(Tearline != NULL)
    {
        yyerror("Tearline already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Tearline string.");
        return -1;
    }

    if(strlen(tmt) > 70)
    {
        yyerror(
            "Tearline string too long. Max Tearline length is 70 characters.");
        return -1;
    }

    Tearline = strdup(tmt);
    return 0;
}

// --------------------------------------------------------------------

int SetNewVia(void)
{
    if(NewVIAType)
    {
        yyerror("NewVIA mode already set.");
        return -1;
    }

    NewVIAType = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetUseOwnZone(void)
{
    if(UseOwnZone)
    {
        yyerror("UseOwnZone already set.");
        return -1;
    }

    UseOwnZone = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetUseASO(void)
{
    if(UseBrake)
    {
        yyerror("Can't use Amiga outbound because UseBrake already defined.");
        return -1;
    }

    if(UseASO)
    {
        yyerror("UseASO already set.");
        return -1;
    }

    UseASO = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetUseBrake(void)
{
    if(UseASO)
    {
        yyerror(
            "Can't use The Brake! outbound because UseASO already defined.");
        return -1;
    }

    if(UseBrake)
    {
        yyerror("UseBrake already set.");
        return -1;
    }

    UseBrake = TRUE;
    return 0;
}

// --------------------------------------------------------------------


int SetSoftCheckInNodelists(void)
{
    if(SoftCheckInNodelists)
    {
        yyerror("SoftCheckInNodelists already set.");
        return -1;
    }

    SoftCheckInNodelists = TRUE;
    return 0;
}

// --------------------------------------------------------------------

int SetAPktDir(char * tmt)
{
    char Buff[1024];
    char Buff2[1024];

    if(APktDir != NULL)
    {
        yyerror("APktDir already defined.");
        return -1;
    }

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: directory name.");
        return -1;
    }

    if(!DirExists(tmt))
    {
        yyerror("Directory not exists.");
        return -1;
    }

    if(Outbound != NULL)
    {
        strcpy(Buff, Outbound);

        if(Buff[strlen(Buff) - 1] == PATHDELIMC)
        {
            Buff[strlen(Buff) - 1] = '\0';
        }

        strcpy(Buff2, tmt);

        if(Buff2[strlen(Buff2) - 1] == PATHDELIMC)
        {
            Buff2[strlen(Buff2) - 1] = '\0';
        }

        if(stricmp(Buff, Buff2) == 0)
        {
            yyerror(
                "APKT directory and Outbound directory should be in different place.");
            return -1;
        }
    }

    APktDir = strdup(tmt);
    return 0;
} // SetAPktDir

int SetCheckPoints(CheckPointsT pmode)
{
    CheckPoints = pmode;
    return 0;
}

// --------------------------------------------------------------------

int SetNodelistPath(char * tmt)
{
    char Buf[1024];

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Nodelists path.");
        return -1;
    }

    if(!DirExists(tmt))
    {
        yyerror("Directory not found.");
        return -1;
    }

    strcpy(Buf, tmt);

    if(Buf[strlen(Buf) - 1] != PATHDELIMC)
    {
        strcat(Buf, PATHDELIMS);
    }

    NodelistPath = strdup(Buf);
    return 0;
}

// --------------------------------------------------------------------

int SetIndexFile(char * tmt)
{
    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Index file name.");
        return -1;
    }

    Ndl.IndexFile(tmt);
    return 0;
}

// --------------------------------------------------------------------

int SetUTC(int i)
{
    if(UTC != 99)
    {
        yyerror("UTC offset already defined.");
        return -1;
    }

    if(i < -12 || i > 12)
    {
        yyerror("UTC offset must be a number between -12 and +12.");
        return -1;
    }

    UTC = i;
    return 0;
}

/*--------------------------------------------------------------------*/
/*    P a r s e C o n f i g                                           */
/*                                                                    */
/*    Read and parse configuration file                               */
/*--------------------------------------------------------------------*/

// extern int yydebug;

int ParseConfig(const char * CfgFile)
{
    int rc;

//  Open configuration File
//  yydebug = 1;
    CHP = 1003;

    if(access(CfgFile, R_OK) != 0)
    {
        Log.Level(LOGE) << "Configuration file '" << CfgFile <<
                           "' not found." << EOL;
        return -1;
    }

    CHP = 1004;
    fh  = fopen(CfgFile, "rt");

    if(fh == 0)
    {
        Log.Level(LOGE) << "Unable to open configuration file '" << CfgFile <<
                           "'." << EOL;
        return -1;
    }

//  Initialise variables

    LineNumber = 0;
    CharNumber = 0;
    avail = 0;

    CHP    = 1005;
    chpool = (char *)malloc(MAXCFGLINE);
    CurrentLine = (char *)malloc(MAXCFGLINE);
    CHP = 1006;
    CheckMem(chpool);
    CheckMem(CurrentLine);
    CHP = 1007;

//  Parse

    rc = yyparse();

//  Done?

//  if(!feof(fh))
//  {
//      Log.Level(LOGE) << "Error(s) in configuration file '" << CfgFile <<
//                         "'." << EOL;
//      rc = -1;
//  }
    free(CurrentLine);
    CurrentLine = NULL;
    free(chpool);
    chpool = NULL;
    fclose(fh);
    return rc;
} // ParseConfig

/*--------------------------------------------------------------------*/
/*    y y e r r o r                                                   */
/*                                                                    */
/*    Show error message from lexical analiser                        */
/*--------------------------------------------------------------------*/

static int Pos = 0;

int yyerror(const char * s)
{
    int i;

    Log.Level(LOGE) << "\nError in '" << ConfigFile << "' Line: " <<
                       LineNumber << EOL;
    Log.Level(LOGE) << CurrentLine << EOL;

    for(i = 0; i < Pos; i++)
    {
        Log.Level(LOGE) << " ";
    }
    Log.Level(LOGE) << "^ ";

    if(stricmp(s, "parse error") == 0)
    {
        Log.Level(LOGE) << "Syntax error. Please, refer to documentation." <<
                           EOL;
    }
    else
    {
        Log.Level(LOGE) << s << EOL;
    }

    return 0;
}

/*--------------------------------------------------------------------*/
/*    S e a r c h T o k e n                                           */
/*                                                                    */
/*    Search token in table and return its number                     */
/*--------------------------------------------------------------------*/

int SearchToken(char * s)
{
    int i;
    int l;
    char * Buff;

    l = strlen(s);

    if(l == 0)
    {
        return LEXERR;
    }

    Buff = (char *)malloc(l + 1);
    CheckMem(Buff);
    strcpy(Buff, s);

    for(i = 0; i < l; i++)
    {
        if(Buff[i] != '\0' && strchr(DELIMETERS, Buff[i]) != NULL)
        {
            Buff[i] = '\0';
            break;
        }
    }

    if(strlen(Buff) == 0)
    {
        free(Buff);
        return LEXERR;
    }

    for(i = 0; kwtable[i].kw != NULL; i++)
    {
        if(!stricmp(Buff, kwtable[i].kw))
        {
            break;
        }
    }

//    if (LogLevel >= 5)
//    {
    if(kwtable[i].kw != NULL)
    {
        Pos += strlen(Buff);
//          Log.Level(LOGD) << "Found token: '" << kwtable[i].kw << "'." << EOL;
    }
    else
    {
//          Log.Level(LOGD) << "token: '" << Buff << "' not found." << EOL;
    }

//    }
    free(Buff);
    return kwtable[i].ltp;
} // SearchToken

/*--------------------------------------------------------------------*/
/*    T o k e n N a m e                                               */
/*                                                                    */
/*    Search token in table by number and return its name             */
/*--------------------------------------------------------------------*/

const char * TokenName(int s)
{
    int i;

    for(i = 0; kwtable[i].kw != NULL; i++)
    {
        if(kwtable[i].ltp == s)
        {
            break;
        }
    }
    return kwtable[i].kw;
}

/*--------------------------------------------------------------------*/
/*    T a k e C h a r                                                 */
/*                                                                    */
/*    Get one char from stream with buffering                         */
/*    Look forward, and if get a token then return the token.         */
/*                                                                    */
/*    NoTokenF: TRUE   Disable tokenise stream.                       */
/*              FALSE  Enable tokenise stream.                        */
/*--------------------------------------------------------------------*/

static tLexState LexStat = LEX_START;
static int NeedLoad = TRUE;

int TakeChar(void)
{
    int rctk;
    char * tmt;


    if(NeedLoad)
    {
        if(fgets(CurrentLine, MAXCFGLINE, fh) == NULL)
        {
            NeedLoad = TRUE;
            return __EOF;
        }

        LineNumber++;
        NeedLoad   = FALSE;
        Pos        = 0;
        CharNumber = 0;
        avail      = 0;
        tmt        = strrchr(CurrentLine, '\n');

        if(tmt != NULL)
        {
            *tmt = '\0';
        }

        tmt = strrchr(CurrentLine, '\r');

        if(tmt != NULL)
        {
            *tmt = '\0';
        }
    }

    if(CurrentLine[Pos] == '\0')
    {
        NeedLoad = TRUE;
        return _CRLF;
    }

    if(LexStat == LEX_START && NoTokensF != TRUE)
    {
        rctk = SearchToken(&CurrentLine[Pos]);
    }
    else
    {
        rctk = LEXERR;
    }

    if(rctk == LEXERR)
    {
        return CurrentLine[Pos++];
    }
    else
    {
        return rctk;
    }
} // TakeChar

// --------------------------------------------------------------------

void AddEnv(char * Buf, char * env)
{
    char * tmt;

    tmt = getenv(env);

    if(tmt != NULL)
    {
        strcat(Buf, tmt);
    }
    else if(StrIsXNum(env))
    {
        tmt    = Buf + strlen(Buf);
        *tmt++ = char(strtol(env, NULL, 16));
        *tmt   = '\0';
    }
    else
    {
//      strcat(Buf,env);
    }
}

/*--------------------------------------------------------------------*/
/*    P r e p a r e S t r i n g                                       */
/*                                                                    */
/*    Translate in string all '%blabla%' as environment variabless    */
/*    and'%01%' as hexadecimal characters.                            */
/*--------------------------------------------------------------------*/

char * PrepareString(char * tmt)
{
    char * tmt2, * c;
    static char Buff[MAXCFGLINE];

    Buff[0] = '\0';
    tmt2    = Buff;

    while(*tmt != '\0')
    {
        if(*tmt == '%')
        {
            tmt++;

            if(*tmt == '%')
            {
                *tmt2++ = *tmt++;
                *tmt2   = '\0';
                continue;
            }

            if((c = strchr(tmt, '%')) != NULL)
            {
                *c = '\0';
                AddEnv(tmt2, tmt);
                *c    = '%';
                tmt   = c + 1;
                tmt2 += strlen(tmt2);
            }
            else
            {
                *tmt2++ = '%';
                *tmt2++ = *tmt++;
                *tmt2   = '\0';
                continue;
            }
        }
        else
        {
            *tmt2++ = *tmt++;
            *tmt2   = '\0';
        }
    }
    return Buff;
} // PrepareString

/*--------------------------------------------------------------------*/
/*    y y l e x                                                       */
/*                                                                    */
/*    Lexical analiser                                                */
/*--------------------------------------------------------------------*/


int yylex(void)
{
    char * p;

    p = NULL;

    if(DetectError)
    {
        LexStat = LEX_ERROR;
    }

    while(1)
    {
        switch(LexStat)
        {
            case LEX_START:
                nxtch   = TakeChar();
                LexStat = LEX_PARSE;
                break;

            case LEX_PARSE:

                if(nxtch > 256)
                {
                    if(nxtch == __EOF)
                    {
                        LexStat = LEX_END;
                        break;
                    }
                    else if(nxtch == _CRLF)
                    {
                        LexStat = LEX_CRLF;
                        break;
                    }
                    else
                    {
                        LexStat = LEX_START;
                        return nxtch;
                    }

//     printf("NxtCh == '%s'(%d)\n",TokenName(nxtch),nxtch);
//                } else {
//     printf("NxtCh == '%c'(%d)\n",nxtch,nxtch);
                }

                if(strchr(DELIMETERS, nxtch) != NULL)
                {
                    LexStat = LEX_START;
                    break;
                }
                else if(isdigit(nxtch))
                {
                    yylval.ln = 0;
                    LexStat   = LEX_DIGIT;
                    break;
                }
                else if(nxtch == '(')
                {
                    LexStat = LEX_COMMENT;
                    break;
                }
                else if(nxtch == '\\')
                {
                    LexStat = LEX_COMMLINE;
                    break;
                }
                else if(nxtch == '"')
                {
                    p = &chpool[avail];
                    LexStat = LEX_STRING;
                    break;
                }
                else
                {
                    LexStat = LEX_START;
                    return nxtch;
                }

            case LEX_DIGIT:

                if(isdigit(nxtch) && nxtch < 256)
                {
                    yylval.ln = (yylval.ln * 10) + nxtch - '0';
                    nxtch = TakeChar();
                    break;
                }
                else
                {
                    LexStat = LEX_PARSE;
                    return _DIGIT_;
                }

            case LEX_COMMENT:
                nxtch = TakeChar();

                if(nxtch == __EOF)
                {
                    LexStat = LEX_PARSE;
                }

                if(nxtch == ')')
                {
                    LexStat = LEX_START;
                }

                break;

            case LEX_COMMLINE:
                nxtch = TakeChar();

                if(nxtch == __EOF || nxtch == _CRLF)
                {
                    LexStat = LEX_PARSE;
                }

                break;

            case LEX_ERROR:

                if(nxtch == _CRLF || nxtch == __EOF)
                {
                    NoTokensF = FALSE;
                    LexStat   = LEX_PARSE;
                }
                else
                {
                    nxtch = TakeChar();
                }

                break;

            case LEX_STRING:

                if(avail + 3 > MAXCFGLINE)
                {
                    Log.Level(LOGE) <<
                    "Internal error #1. Please, contact with author!" << EOL;
                    exit(-1);
                }

                nxtch = TakeChar();

                if(nxtch == _CRLF || nxtch == __EOF)
                {
                    LexStat = LEX_PARSE;
                    return LEXERR;
                }
                else if(nxtch == '"')
                {
                    chpool[avail] = '\0';
                    avail -= strlen(p);
                    strcpy(p, PrepareString(p));
                    avail += (strlen(p) + 1);
                    yylval.ch = p;
                    LexStat   = LEX_START;
                    return _STRING;
                }
                else
                {
                    chpool[avail++] = nxtch;
                    break;
                }

            case LEX_CRLF:
                DetectError = FALSE;
                LexStat = LEX_START;
                return _CRLF;

            case LEX_END:
                return 0;

            default:
                Log.Level(LOGE) << "Wrong state of LexStateMachine!" << EOL;
                exit(-1);
        } // switch
    }
    Log.Level(LOGE) << "Exit from LEXX!" << EOL;
    exit(-1);
    return 0;
} // yylex

/*--------------------------------------------------------------------*/
/*                       Nested include file                          */
/*--------------------------------------------------------------------*/
extern int yychar;

int SetInclude(const char * tmt)
{
    int sLineNumber;
    char * schpool;
    char * sCurrentLine;

    FILE * sFh;
    char * sConfigFile;

    if(strlen(tmt) == 0)
    {
        yyerror("Missing parameter: Include file name.");
        return -1;
    }

    if(access(tmt, R_OK) != 0)
    {
        yyerror("File does not exist.");
        return -1;
    }

    sLineNumber  = LineNumber;
    sFh = fh;
    sConfigFile  = ConfigFile;
    ConfigFile   = strdup(tmt);
    CheckMem(ConfigFile);
    schpool      = chpool;
    sCurrentLine = CurrentLine;

    if(ParseConfig(tmt) != 0)
    {
        return -1;
    }

    LexStat     = LEX_START;
    chpool      = schpool;
    CurrentLine = sCurrentLine;
    LineNumber  = sLineNumber;
    nxtch = _CRLF;
    yychar      = _CRLF;
    fh = sFh;
    free(ConfigFile);
    ConfigFile  = sConfigFile;
    NeedLoad    = TRUE;
    return 0;
} // SetInclude
