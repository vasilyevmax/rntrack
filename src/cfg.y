
%{

/*
 *  RNtrack - FTN message tracker/router
 *
 *  cfg.(y|hpp|cpp) - Config file parser
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: cfg.y,v 1.6 2005/06/22 22:18:14 ph0enix Exp $
 */

#define YYDEBUG 0
/* #define YYERROR_VERBOSE */
#ifdef HAVE_CONFIG_H
# include "aconfig.h"
#endif

#include <stdlib.h>
#ifdef HAVE_MALLOC_H
   #include <malloc.h>
#endif
#include "msg.hpp"
#include "outbound.hpp"
#include "fidoaddr.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "constant.hpp"
#include "log.hpp"
#include "aka.hpp"
#include "age.hpp"
#include "scandir.hpp"
#include "attach.hpp"
#include "badpkt.hpp"
#include "badmsg.hpp"
#include "domain.hpp"
#include "filebox.hpp"
#include "passwd.hpp"
#include "nodelist.hpp"
#include "script.hpp"

#undef YYSTYPE               /* Perl also uses bison? damn! */

extern int DetectError;
extern int NoTokensF;

extern FA   cffa;
extern FA   cffa1;
extern FA   cffa2;

static int brf = FALSE, arf = FALSE, renumberf = FALSE, unpackf = FALSE, freshf = FALSE;
static ScanDir *wsd = NULL;
static char *FileName = NULL;
static char *BPktDir = NULL;
static char *ScriptBefore = NULL;
static char *ScriptAfter = NULL;
static tTimes *tt;
static IndBiList<tTimes> *_TTimes;
static MSGBASE *mbase;
static Mask *msk = NULL;
static int MaskMode;
static int rc;
static int FlagMode = 0;
static Action *act = NULL;

static void CheckETTime(void) {
time_t tmt;
   if (tt->_ETime != 0 && tt->_ETime < tt->_STime) {
      tmt = tt->_ETime;
      tt->_ETime = (23*60*60)+(59*60)+59;
      tt->_ETime += TimeOfBeginOfDay(-1);
      _TTimes->AddToEnd(tt);
      tt = new tTimes;
      tt->_STime = TimeOfBeginOfDay(-1);
      tt->_ETime = tmt;
   }
}

static int PrepareMask(Mask &m) {
ScanDir *sd;
char ErrMess[128];

   CHP = 23700;
   sd = ScanDirs.GetLast();
   if (sd == NULL) {
      strcpy(ErrMess,"'");
      strcat(ErrMess,m.MaskName());
      strcat(ErrMess,":' without 'ScanDir:'");
      yyerror(ErrMess);
      return -1;
   }
   m.sd = sd;
   return 0;
}

static void AddReadyMask(Mask &m) {
ScanDir *sd;

   switch (PrevMask) {
      case 0: // first mask.
      case 1: // after action.
         LastDo = new DoList();
         sd = ScanDirs.GetLast();
         sd->_DoLists.AddToEnd(LastDo);
         PrevMask = 2;
         break;
      case 2: // after MASK.
         break;
   }
   LastDo->AddMask(m);
}


static int CheckMaskMode(char *f) {
char Buff[128];
   if (MaskMode != 0) {
      strcpy(Buff,"You can use '");
      strcat(Buff,f);
      strcat(Buff,"' flag only in 'Mask:'.");
      yyerror(Buff);
      return -1;
   }
   return 0;
}


static int ctoi(char *s) {
   char *foo;
   int res = 0;

   res = strtoul(s, &foo, 0);
   if (*foo)	/* parse error */
      return 0;
   return res;
}



%}

%union {
   int          in;
   char         *ch;
   long         ln;
   KillModeT    kmode;
   CheckPointsT pmode;
   tBadMsgMode  bmode;
   tBadMsgMode  bpmode;
   fileboxType	fbtype;
   time_t       t;
   PKTMode      pktmode;
};



%token _LOGFILE            _LOGLEVEL    _NODELIST    _INDEXFILE    _NODELISTPATH
       _ADDRESS            _SYSOPNAME   _USEOWNZONE  _FORCEINTL    _LOOPSTR
       _SCANDIR            _MASK        _SMASK       _PMASK        _BODYMASK
       _SBODYMASK          _PBODYMASK   _KLUDGEMASK  _SKLUDGEMASK  _PKLUDGEMASK
       _ACTION             _MAXAGE      _BADMESSAGES _NOLOGIGNORE  _AKA
       _SKIPHIDDENFILES    _FILEINBOUND _OUTBOUND    _ADDTONULLPKT _TEMPMAIL
       _TRAFFICLOG         _PASSWORD    _UTC         _ORIGIN       _TEARLINE
       _INCLUDE            _APKTDIR     _CHECKPOINTS _SETVIAALWAYS _FRESH
       _CREATEMISSINGBASE  _USENEWVIA   _SCRIPTMASK  _SSCRIPTMASK  _PSCRIPTMASK
       _MAXATTACHSIZE      _SEMAPHORE   _SCRIPTFILE  _USEASO _USEBRAKE _FILEBOXDIR
       _KILLROUTEDMESSAGE  _IGNOREBSY   _AFTERSCRIPT _BEFORESCRIPT _AGEFROMVIA
       _MAXNODELISTAGE _USEFILEBOXES _FILEBOXTYPE _LONG _TMLONG _TMSHORT _BRAKE
       _SOFTCHECKINNODELIST _BADPACKETS _IGNOREATTACHPATH _MAXPKTSIZE _MAXMSGSIZE
       _TIMESTAMPFILE _DOMAIN _FILEBOX
       _TRAFFICLOGTEMPLATE
		 _STRIPPATHINPKT

       _CRLF        _SKIP _DELETE _EXIT _MOVE __EOF
       _STRING      _BEFOREROUTE _AFTERROUTE
       _DIGIT_
       _RENUMBER    _UNPACK _DAILY _WEEKLY _FLAG
       _NEVER _HARD _SOFT _ALWAYS
/* Actions */
       _ADDNOTE _COPY  _REWRITE _IGNORE _DISPLAY _DELFILE _NEWMSG _WRITEFILE
       _APPENDTOFILE _CALL _ROUTE _ROUTEFBOX _ROUTEHUB _POLL _DELETEATTACH _CHANGEPATH _MOVEATTACH
       _ASCRIPT _TOLOWERPATH _TOUPPERPATH _COPYATTACHFBOX _MOVEATTACHFBOX
       _COPYATTACH _SPLIT _RECODE _ADDKLUDGE _HOLD _CRASH _DIRECT _NORMAL _IMMEDIATE
	LEXERR

%start  Conf

%%

Conf     :   /* empty */
         |   Conf ConfLine
         ;


ConfLine :  Action _CRLF
         |  IncludeF _CRLF ={
            if (SetInclude($<ch>1) != 0) {
               YYABORT;
            }
         }
         |  TimeStampFile _CRLF
         |  Address _CRLF
         |  _ADDTONULLPKT _CRLF
            = {
               if (SetAddToNullPkt() != 0) {
                  YYABORT;
               }
            }
         |  Aka _CRLF
         |  APktDir _CRLF
         |  BodyMask _CRLF
         |  SBodyMask _CRLF
         |  PBodyMask _CRLF
         |  CheckPoints _CRLF
         |  _CREATEMISSINGBASE _CRLF
            = {
               if (SetCreateMissingBase() != 0) {
                  YYABORT;
               }
            }
         |  FileInbound _CRLF
         |  _FORCEINTL  _CRLF
            = {
               if (SetForceINTL() != 0) {
                  YYABORT;
               }
            }
         |  Origin _CRLF
         |  IndexFile _CRLF
         |  KillRoutedMessage _CRLF
         |  KludgeMask _CRLF
         |  SKludgeMask _CRLF
         |  PKludgeMask _CRLF
         |  LogFile _CRLF
         |  LogLevel _CRLF
         |  LoopStr _CRLF
         |  Mask _CRLF
         |  SMask _CRLF
         |  PMask _CRLF
         |  MaxAge _CRLF
         |  MaxAttachSize _CRLF
	 |  MaxMsgSize _CRLF
	 |  MaxPktSize _CRLF
         |  MaxNodelistAge _CRLF
         |  Nodelist _CRLF
         |  NodelistPath _CRLF
         |  _NOLOGIGNORE _CRLF
            = {
               if (SetNoLogIgnore() != 0) {
                  YYABORT;
               }
            }
         |  Outbound _CRLF
         |  Password _CRLF
	 |  Domain _CRLF
	 |  FileBox _CRLF
         |  ScriptMask _CRLF
         |  SScriptMask _CRLF
         |  PScriptMask _CRLF
         |  _IGNOREBSY _CRLF
            = {
               if (SetIgnoreBSY() != 0) {
                  YYABORT;
               }
            }
         |  _IGNOREATTACHPATH _CRLF
            = {
               if (SetIgnoreAttachPath() != 0) {
                  YYABORT;
               }
            }
         |  _SETVIAALWAYS _CRLF
            = {
               if (SetSetViaAlways() != 0) {
                  YYABORT;
               }
            }
         |  _SKIPHIDDENFILES _CRLF
            = {
               if (SetSkipHiddenFiles() != 0) {
                  YYABORT;
               }
            }
         |  _SOFTCHECKINNODELIST _CRLF
            = {
               if (SetSoftCheckInNodelists() != 0) {
                  YYABORT;
               }
            }
         |  SysopName _CRLF
         |  TearLine _CRLF
         |  _USENEWVIA _CRLF
            = {
               if (SetNewVia() != 0) {
                  YYABORT;
               }
            }
         |  _USEOWNZONE _CRLF
            = {
               if (SetUseOwnZone() != 0) {
                  YYABORT;
               }
            }
         |  _USEASO _CRLF
	         = {
	            if (SetUseASO() != 0) {
                  YYABORT;
	            }
	         }
	 | _USEBRAKE _CRLF
	         = {
		    if (SetUseBrake() != 0) {
		  YYABORT;
		    }
		 }
	 |  _USEFILEBOXES _CRLF
	         = {
	            if (SetUseFileBoxes() != 0) {
                  YYABORT;
	            }
	         }
         | _STRIPPATHINPKT _CRLF
			   = {
				   if (SetStripPathInPkt() != 0) {
					   YYABORT;
               }
            }
         |  _AGEFROMVIA _CRLF
            = {
               if (SetAgeFromVia() != 0) {
                  YYABORT;
               }
            }
         |  Utc _CRLF
         |  TempMail _CRLF
         |  TrafficLog _CRLF
         |  BadMessages _CRLF
         |  BadPackets _CRLF
         |  ScanDir _CRLF
         |  Semaphore _CRLF
         |  TrafficLogTemplate _CRLF
         |  ScriptFile _CRLF
	 |  FileBoxDir _CRLF
	 |  FileBoxType _CRLF
         |   error _CRLF ={ YYABORT; }
         = { DetectError = TRUE;
         }
         | _CRLF
         = {
            avail = 0;
         }
         ;

ScriptFile : _SCRIPTFILE _STRING ={
               if (LoadScriptFile($<ch>2) != 0) {
                  YYABORT;
               }
             }
           ;

FileBoxDir : _FILEBOXDIR _STRING ={
               if (SetFileBoxDir($<ch>2) != 0) {
                  YYABORT;
               }
             }
           ;

FileBoxType: _FILEBOXTYPE FBOXTYPE
              ={
                if (SetFileBoxType($<fbtype>2) != 0) {
		  YYABORT;
                }
              }
            ;
FBOXTYPE  : _LONG ={ $<fbtype>$ = FILEBOXLONG}
            | _TMLONG ={ $<fbtype>$ = FILEBOXTMLONG }
            | _TMSHORT ={ $<fbtype>$ = FILEBOXTMSHORT }
	    | _BRAKE = { $<fbtype>$ = FILEBOXBRAKE }
            ;


TrafficLogTemplate : _TRAFFICLOGTEMPLATE _STRING ={
                      if (SetTrafficLogTemplate($<ch>2) != 0) {
                         YYABORT;
                      }
                   }
                   ;

Semaphore : _SEMAPHORE _DIGIT_ _STRING ={
             if (SetSemaphoreName($<ch>3, $<ln>2) != 0) {
                YYABORT;
             }
          }
          ;


IncludeF : _INCLUDE _STRING ={ $<ch>$ = $<ch>2; }
         ;

Aka      : _AKA ={ cffa.Clean(); } faddress = { cffa1 = cffa; cffa.Clean(); } faddress
            = {
               if (SetAka(cffa1, cffa) != 0) {
                  YYABORT;
               }
               cffa.Clean();
               cffa1.Clean();
            }
         ;

TimeStampFile : _TIMESTAMPFILE _STRING
            = {
               if (SetTimeStampFile($<ch>2) != 0) {
                  YYABORT;
               }
            }
              ;

APktDir  : _APKTDIR _STRING
            = {
               if (SetAPktDir($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

Address  : _ADDRESS ={ cffa.Clean(); } faddress
            = {
               if (SetMyAddr(cffa) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
         ;

CheckPoints : _CHECKPOINTS ChkPntMode = { SetCheckPoints($<pmode>2); }
            ;

ChkPntMode  : _NEVER ={ $<pmode>$ = CHECKPNT_NEVER; }
            | _HARD  ={ $<pmode>$ = CHECKPNT_HARD; }
            | _SOFT  ={ $<pmode>$ = CHECKPNT_SOFT; }
            ;

KillRoutedMessage : _KILLROUTEDMESSAGE KillRMode = { SetKillRoutedMessages($<kmode>2); }
                  ;

KillRMode         : _ALWAYS = { $<kmode>$ = KILL_ALWAYS; }
                  | _NEVER  = { $<kmode>$ = KILL_NEVER; }
                  | _FLAG   = { $<kmode>$ = KILL_FLAG; }
                  ;

SysopName: _SYSOPNAME _STRING
            = {
               if (SetSysopName($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

TearLine : _TEARLINE _STRING
            = {
               if (SetTearline($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

LogFile  : _LOGFILE _STRING
            = {
               if (SetLogFile($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

LogLevel : _LOGLEVEL _DIGIT_
            = {
               if (SetLogLevel($<ln>2) != 0) {
                  YYABORT;
               }
            }
         ;

Origin   : _ORIGIN _STRING
            = {
               if (SetOrigin($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

Nodelist : _NODELIST _STRING NdlZone
            = {
               if (SetNodelist($<ch>2,$<ln>3) != 0) {
                  YYABORT;
               }
            }
         ;

NdlZone  : ={ $<ln>$ = -3; }
         | _DIGIT_  ={ $<ln>$ = $<ln>1; }
         ;

NodelistPath : _NODELISTPATH _STRING
            = {
               if (SetNodelistPath($<ch>2) != 0) {
                  YYABORT;
               }
            }
             ;

IndexFile: _INDEXFILE _STRING
            = {
               if (SetIndexFile($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

LoopStr  : _LOOPSTR _STRING
            = {
               if (SetLoopStr($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

MaxAttachSize : _MAXATTACHSIZE _DIGIT_
            = {
               if (SetMaxAttach($<ln>2) != 0) {
                  YYABORT;
               }
            }
              ;

MaxNodelistAge : _MAXNODELISTAGE _DIGIT_
            = {
               if (SetMaxNodelistAge($<ln>2) != 0) {
                  YYABORT;
               }
            }
               ;

Outbound : _OUTBOUND _STRING
            = {
               if (SetOutbound($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

TempMail : _TEMPMAIL _STRING
            = {
               if (SetTempMail($<ch>2) != 0) {
                  YYABORT;
               }
            }
         ;

TrafficLog : _TRAFFICLOG _STRING
            = {
               if (SetTrafficLog($<ch>2) != 0) {
                  YYABORT;
               }
            }
           ;

FileInbound : _FILEINBOUND _STRING
            = {
               if (SetFileInbound($<ch>2) != 0) {
                  YYABORT;
               }
            }
            ;

MaxAge      : _MAXAGE _DIGIT_
            = {
               if (SetMaxAge($<ln>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;

MaxMsgSize   : _MAXMSGSIZE _DIGIT_
            = {
               if (SetMaxMsgSize($<ln>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;

MaxPktSize   : _MAXPKTSIZE _DIGIT_
            = {
               if (SetMaxPktSize($<ln>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;

Password    : _PASSWORD _STRING
            = {
               if (strlen($<ch>2) > 8){
                  yyerror("Password too long. Max password length is a 8 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }
              faddress
            = {
               if (SetPasswd(cffa, $<ch>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;

Domain    : _DOMAIN _STRING
            = {
               if (strlen($<ch>2) > 10){
                  yyerror("Domain too long. Max domain length is a 10 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }
              faddress
            = {
               if (SetDomain(cffa, $<ch>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;

FileBox    : _FILEBOX _STRING
            = {
               if (strlen($<ch>2) > 100){
                  yyerror("Path too long. Max path length is a 100 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }
              faddress
            = {
               if (SetFilebox(cffa, $<ch>2) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }
            ;


BadMessages : _BADMESSAGES BadMsgMode
              ={
                if (SetBadMode($<bmode>2,FileName) != 0) {
                  YYABORT;
                }
                FileName = NULL;
              }
            ;
BadMsgMode  : _SKIP ={ $<bmode>$ = SKIP; FileName = NULL;}
            | _EXIT ={ $<bmode>$ = EXIT; FileName = NULL;}
            | _DELETE ={ $<bmode>$ = REMOVE; FileName = NULL;}
            | _MOVE _STRING ={ $<bmode>$ = MOVE; FileName = $<ch>2;}
            ;

BadPackets  : _BADPACKETS BadPktMode
              ={
                if (SetBadPktMode($<bpmode>2,BPktDir) != 0) {
                  YYABORT;
                }
		BPktDir = NULL;
              }
            ;
BadPktMode  : _SKIP ={ $<bpmode>$ = SKIP; BPktDir = NULL;}
            | _EXIT ={ $<bpmode>$ = EXIT; BPktDir = NULL;}
            | _DELETE ={ $<bpmode>$ = REMOVE; BPktDir = NULL;}
            | _MOVE _STRING ={ $<bpmode>$ = MOVE; BPktDir = $<ch>2;}
            ;

Utc         : _UTC UtcOffs
              ={
                if (SetUTC($<ln>2) != 0) {
                  YYABORT;
                }
              }
            ;

UtcOffs     : _DIGIT_ ={ $<ln>$ = $<ln>1; }
            | '+' _DIGIT_ ={ $<ln>$ = $<ln>2; }
            | '-' _DIGIT_ ={ $<ln>$ = -$<ln>2; }
            ;

/* ScanDir --------- */

ScanDir  : _SCANDIR
           = {
              wsd = new ScanDir();
              CheckMem((char *)wsd);
              renumberf = FALSE;
              unpackf = FALSE;
              freshf = FALSE;
              arf = FALSE;
              brf = FALSE;
              _TTimes = &wsd->_Times;
              mbase = NULL;
              PrevMask = 0;
              ScriptBefore = NULL;
              ScriptAfter = NULL;
              FileName = NULL;
           }
           SDType
           = {
              wsd->SetBase(mbase);
              wsd->_Renumber = renumberf;
              wsd->_Unpack = unpackf;
              wsd->_Fresh = freshf;
              wsd->_FlagFile = FileName;
              wsd->_ScriptBefore = ScriptBefore;
              wsd->_ScriptAfter = ScriptAfter;
              ScanDirs.AddToEnd(wsd);
              if (brf) BeforeRoute = wsd;
              if (arf) AfterRoute = wsd;
           }
         ;

SDType  : BeforeAfter Flag
        | _STRING
          = {
             mbase = MakeBase($<ch>1);
             if (mbase == NULL) {
                YYABORT;
             }
             if (!mbase->Set($<ch>1,BASE_IN)) {
                delete mbase;
                mbase = NULL;
                yyerror("Unable to open message base.");
                YYABORT;
             }
             if (!mbase->CheckIn()) {
                delete mbase;
                YYABORT;
             }
          }
          AddSdParam Flag
        ;

BeforeAfter : _BEFOREROUTE = { brf = TRUE; }
            | _AFTERROUTE = { arf = TRUE; }
            ;

AddSdParam  :
            | AddSdParam SdParam
            ;

SdParam     : _RENUMBER
               = {
                  if (renumberf == TRUE) {
                     yyerror("Renumber for this base already set.");
                     YYABORT;
                  } else {
                    renumberf = TRUE;
                  }
               }
            | _BEFORESCRIPT _STRING
               = {
                  if (ScriptWordExists($<ch>2) == FALSE) {
                     yyerror("Script function not found.");
                     YYABORT;
                  }
                  ScriptBefore = strdup($<ch>2);
               }
            | _AFTERSCRIPT  _STRING
               = {
                  if (ScriptWordExists($<ch>2) == FALSE) {
                     yyerror("Script function not found.");
                     YYABORT;
                  }
                  ScriptAfter = strdup($<ch>2);
               }
            | _FRESH
               = {
                  if (freshf == TRUE) {
                     yyerror("Fresh scripts for this base already set.");
                     YYABORT;
                  } else {
                     freshf = TRUE;
                  }
               }
            | _UNPACK
               = {
                  if (unpackf == TRUE) {
                     yyerror("Unpack for this base already set.");
                     YYABORT;
                  } else {
                     unpackf = TRUE;
                  }
                  if (Outbound == NULL) {
                     yyerror("Outbound directory not specified.");
                     YYABORT;
                  }
               }
            | STime
               = {
                  if (TimeStampFile == NULL) {
                     yyerror("You can't set scanning time without Timestamp File.");
                     YYABORT;
                  }

               }
            ;

STime       : _DAILY
               = {
                  tt = new tTimes;
                  tt->_STime = TimeOfBeginOfDay(-1);
                  tt->_ETime = 0;
               }
              DaySTime
               = {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                  }
               }
            | _WEEKLY
               = {
                  tt = new tTimes;
                  tt->_STime = TimeOfBeginOfDay(0);
                  tt->_ETime = 0;
               }
              WeekSTime
               = {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                  }
               }
            ;

DaySTime    :
            | DaySTime DaySSTime
               = {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                     tt = new tTimes;
                  }
               }
            ;

DaySSTime   : Time
               = {
                  tt->_STime = $<t>1 + TimeOfBeginOfDay(-1);
               }
            | Time '-' Time
               = {
                  tt->_STime = $<t>1 + TimeOfBeginOfDay(-1);
                  tt->_ETime = $<t>3 + TimeOfBeginOfDay(-1) + 59;
               }
            | AnyP '.' Time ={
                  time_t i_time;
                  time_t b_time;
                  if ($<t>3 == (time_t) 0) {
                     yyerror("Time of pereodical event should be between 00:01 and 23:59");
                     YYABORT;
                  }
                  tt->_STime = TimeOfBeginOfDay(-1);
                  b_time = tt->_STime;
                  do {
                     i_time = tt->_STime;
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                     tt = new tTimes;
                     tt->_ETime = 0;
                     tt->_STime = i_time + $<t>3;
                  } while (tt->_STime < (b_time + (23*60*60)+(59*60)+60));
                  tt->_STime = 0;
            }
            ;

AnyP        : 'p'
            | 'P'
            ;

Time        : _DIGIT_
              = {
                 if ($<ln>1 < 0 || $<ln>1 > 23) {
                    yyerror("Hour should be between 00 and 23");
                    YYABORT;
                 } else {
                    $<t>$ = (time_t) ($<ln>1 * 60);
                 }
              }
              ':' _DIGIT_
              = {
                 if ($<ln>4 < 0 || $<ln>4 > 59 || $<t>2 == (time_t) -1) {
                    $<t>$ = (time_t)-1;
                    yyerror("Minutes should be between 00 and 59");
                    YYABORT;
                 } else {
                    $<t>$ = $<t>2 + (time_t) $<ln>4;
                    $<t>$ *= 60;
                 }
              }
            ;

WeekSTime   :
            | WeekSTime WeekSSTime
               = {
                  CheckETTime();
                  _TTimes->AddToEnd(tt);
                  tt = new tTimes;
               }
            ;

WeekSSTime  : _DIGIT_
              = {
                 if ($<ln>1 < 0 || $<ln>1 > 6) {
                    yyerror("Day of week should be between 0 and 6");
                    YYABORT;
                 } else {
                    tt->_STime = TimeOfBeginOfDay($<ln>1);
                 }
              }
            | _DIGIT_ '-' _DIGIT_
              = {
                 if ($<ln>1 < 0 || $<ln>1 > 6 || $<ln>3 < 0 || $<ln>3 > 6) {
                    yyerror("Day of week should be between 0 and 6");
                    YYABORT;
                 } else {
                    tt->_STime = TimeOfBeginOfDay($<ln>1);
                    tt->_ETime = TimeOfBeginOfDay($<ln>3) + (23*60*60)+(59*60)+59;
                 }
              }
            ;

Flag        : = { FileName = NULL; }
            | AFlag = { FileName = strdup($<ch>1); }
            ;

/* -------------- */

Mask        : _MASK ={ MaskMode = 0; } MParam ={
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(NormalMask *)msk);
            }
            ;

SMask       : _SMASK ={ MaskMode = 0; } MParam ={
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(NormalMask *)msk);
            }
            ;

PMask       : _PMASK ={ MaskMode = 0; } MParam ={
               msk->_Type = MASK_ADD;
               AddReadyMask(*(NormalMask *)msk);
            }
            ;

MParam      : ={
               msk = new NormalMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }
            SyName ={
               ((NormalMask *)msk)->_FromName = strdup($<ch>2);
               cffa.Clean();
            }
            faddress ={
               ((NormalMask *)msk)->_FromAddr = cffa;
               if (MaskMode == 0) {
                  rc = ((NormalMask *)msk)->_FromAddr.MaskValid();
               } else {
                  rc = ((NormalMask *)msk)->_FromAddr.ActValid();
               }
               if (!rc) {
                  yyerror("Invalid 'From' Address.");
                  YYABORT;
               }
            }
            SyName  ={
               ((NormalMask *)msk)->_ToName = strdup($<ch>6);
               cffa.Clean();
            }
            faddress ={
               ((NormalMask *)msk)->_ToAddr = cffa;
               if (MaskMode == 0) {
                  rc = ((NormalMask *)msk)->_ToAddr.MaskValid();
               } else {
                  rc = ((NormalMask *)msk)->_ToAddr.ActValid();
               }
               if (!rc) {
                  yyerror("Invalid 'To' Address.");
                  YYABORT;
               }
               if ((((NormalMask *)msk)->_ToAddr.Zone() & (FA_LSTMASK|FA_HOLDMASK|FA_DOWNMASK|FA_PVTMASK|FA_HUBMASK)) && (!Ndl.Enabled())) {
                  yyerror("You can't use '#','H','D','U' or 'P' mask without nodelist.");
                  YYABORT;
               }
               if ((((NormalMask *)msk)->_ToAddr.Point() & FA_SUBMASK) && (!Ndl.Enabled())) {
                  yyerror("You can't use '&' mask without nodelist.");
                  YYABORT;
               }
            }
            MString ={
               ((NormalMask *)msk)->_Subject = strdup($<ch>10);
               NoTokensF = TRUE;
            }
            MsgAttr ={
               NoTokensF = FALSE;
            }
            ;

SyName      : _STRING
            | '$' ={ $<ch>$ = "$"; }
            | '*' ={ $<ch>$ = "*"; }
            | '%' ={ $<ch>$ = "%"; }
            ;

MString     : _STRING
            | '*' ={ $<ch>$ = "*"; }
            ;

MDigit      : MNot _DIGIT_ ={
               if ($<ln>2 > 65535) {
                  yyerror("Parameter shoul be less that 65535");
                  YYABORT;
               }
               $<ln>$ = $<ln>1 | $<ln>2;
            }
            | '*' ={ $<ln>$ = -1; }
            ;

MNot        : ={ $<ln>$ = 0; }
            | '!' ={ $<ln>$ = 0x08000000; }
            ;

MsgAttr     : '*'
            | ={ FlagMode = 1; } MsgFAttr
            ;
MsgFAttr    : FlagsMode
            | MsgFAttr FlagsMode
            ;

FlagsMode   : FlagsChar
            | '+' ={ FlagMode = 1; } FlagsChar
            | '-' ={ FlagMode = 2; } FlagsChar
            ;

FlagsChar   : 'a' ={ ((NormalMask *)msk)->fFileAttach = (FlagMode == 2) ? 2 : 1; }
            | 'A' ={ /* Check MaxAttach size*/
               if (CheckMaskMode("A") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxAttachSize == 0 && MaxAttachSize == 0) {
                  yyerror("Not one (global or local) MaxAttachSize is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxAttach = (FlagMode == 2) ? 2 : 1;
            }
            | 'M' ={ /* Check MaxMsg size*/
               if (CheckMaskMode("M") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxMsgSize == 0 && MaxMsgSize == 0) {
                  yyerror("Not one (global or local) MaxMsgSize is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxMsg = (FlagMode == 2) ? 2 : 1;
            }
            | 'b' ={ ((NormalMask *)msk)->fARQ = (FlagMode == 2) ? 2 : 1; }
            | 'c' ={ ((NormalMask *)msk)->fCrash = (FlagMode == 2) ? 2 : 1; }
            | 'd' ={ ((NormalMask *)msk)->fDIR = (FlagMode == 2) ? 2 : 1; }
            | 'e' ={ /* Empty message */
               if (CheckMaskMode("e") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fEmpty = (FlagMode == 2) ? 2 : 1;
            }
            | 'E' ={ /* Check echomail */
               if (CheckMaskMode("E") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fEchomail = (FlagMode == 2) ? 2 : 1;
            }
            | 'f' ={ ((NormalMask *)msk)->fFileRequest = (FlagMode == 2) ? 2 : 1; }
            | 'g' ={ /* Check age */
               if (CheckMaskMode("g") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxAge == 0 && MaxAge == 0) {
                  yyerror("Not one (global or local) MaxAge is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxAge = (FlagMode == 2) ? 2 : 1;
            }
            | 'h' ={ ((NormalMask *)msk)->fHold = (FlagMode == 2) ? 2 : 1; }
            | 'i' ={ ((NormalMask *)msk)->fTransit = (FlagMode == 2) ? 2 : 1; }
            | 'j' ={ ((NormalMask *)msk)->fKFS = (FlagMode == 2) ? 2 : 1; }
            | 'k' ={ ((NormalMask *)msk)->fKillSend = (FlagMode == 2) ? 2 : 1; }
            | 'l' ={ ((NormalMask *)msk)->fLocal = (FlagMode == 2) ? 2 : 1; }
            | 'L' ={ ((NormalMask *)msk)->fLok = (FlagMode == 2) ? 2 : 1; }
            | 'm' ={ ((NormalMask *)msk)->fIMM = (FlagMode == 2) ? 2 : 1; }
            | 'n' ={ ((NormalMask *)msk)->fCFM = (FlagMode == 2) ? 2 : 1; }
            | 'o' ={ ((NormalMask *)msk)->fOrphan = (FlagMode == 2) ? 2 : 1; }
            | 'p' ={ ((NormalMask *)msk)->fPrivate = (FlagMode == 2) ? 2 : 1; }
            | 'q' ={ ((NormalMask *)msk)->fRRQ = (FlagMode == 2) ? 2 : 1; }
            | 'r' ={ ((NormalMask *)msk)->fReceived = (FlagMode == 2) ? 2 : 1; }
            | 's' ={ ((NormalMask *)msk)->fSend = (FlagMode == 2) ? 2 : 1; }
            | 'S' ={ ((NormalMask *)msk)->fAS = (FlagMode == 2) ? 2 : 1; }
            | 't' ={ ((NormalMask *)msk)->fTFS = (FlagMode == 2) ? 2 : 1; }
            | 'u' ={ ((NormalMask *)msk)->fFURQ = (FlagMode == 2) ? 2 : 1; }
            | 'v' ={ ((NormalMask *)msk)->fScanned = (FlagMode == 2) ? 2 : 1; }
            | 'x' ={ /* Check existing attach */
               if (CheckMaskMode("x") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fAttExists = (FlagMode == 2) ? 2 : 1;
            }
            | 'y' ={ ((NormalMask *)msk)->fIRR = (FlagMode == 2) ? 2 : 1; }
            | _DIGIT_ = {
               if (CheckMaskMode("loop flag") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fLoop = (FlagMode == 2) ? 2 : 1;
               if (((NormalMask *)msk)->Loops != (unsigned int)-1) {
                  yyerror("Only one loop count should be in mask.");
                  YYABORT;
               }
               ((NormalMask *)msk)->Loops = $<ln>1;
            }
            ;

/* -------------- */

KludgeMask  : _KLUDGEMASK KMParam ={
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(KludgeMask *)msk);
            }
            ;

SKludgeMask : _SKLUDGEMASK KMParam ={
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(KludgeMask *)msk);
            }
            ;

PKludgeMask : _PKLUDGEMASK KMParam ={
               msk->_Type = MASK_ADD;
               AddReadyMask(*(KludgeMask *)msk);
            }
            ;

KMParam     : ={
               msk = new KludgeMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }
            MString MString MDigit ={
               ((KludgeMask *)msk)-> _KludgeName = strdup($<ch>2);
               ((KludgeMask *)msk)-> _KludgeBody = strdup($<ch>3);
               ((KludgeMask *)msk)-> _Times = $<ln>4;
            }
            ;

/* -------------- */

BodyMask    : _BODYMASK BMParam ={
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(BodyMask *)msk);
            }
            ;

SBodyMask   : _SBODYMASK BMParam ={
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(BodyMask *)msk);
            }
            ;

PBodyMask   : _PBODYMASK BMParam ={
               msk->_Type = MASK_ADD;
               AddReadyMask(*(BodyMask *)msk);
            }
            ;

BMParam     : ={
               msk = new BodyMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }
            MString MDigit MDigit ={
               ((BodyMask *)msk)-> _Body = strdup($<ch>2);
               ((BodyMask *)msk)-> _Lines = $<ln>3;
               ((BodyMask *)msk)-> _Bytes = $<ln>4;
            }
            ;


/* -------------- */

ScriptMask  : _SCRIPTMASK SCRMParam ={
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(ScriptMask *)msk);
            }
            ;

SScriptMask : _SSCRIPTMASK SCRMParam ={
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(ScriptMask *)msk);
            }
            ;

PScriptMask : _PSCRIPTMASK SCRMParam ={
               msk->_Type = MASK_ADD;
               AddReadyMask(*(ScriptMask *)msk);
            }
            ;

SCRMParam   : ={
               msk = new ScriptMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }
            _STRING ={
               ((ScriptMask *)msk)->_ScriptName = strdup($<ch>2);
               if (ScriptWordExists($<ch>2) != TRUE) {
                  yyerror("Subroutine not found in scripts.");
                  YYABORT;
               }
            }
            ;

/* -------------- */

Action : _ACTION ={
          if (PrevMask == 0) {
             yyerror("Action without Mask.");
             YYABORT;
          }
          wsd = ScanDirs.GetLast();
          PrevMask = 1;
          act = new Action();
          act->sd = wsd;
          act->Before = BeforeRoute;
          act->After = AfterRoute;
         _TTimes = &act->_Times;
       }
       ActionCmd ={
          LastDo->AddAction(*act);
       }
       MayBeActTime
       ;

MayBeActTime  :
              | '[' STime ']'
              ;

ActionCmd : AAddNote
          | _DELETE ={ act->_Act = ACT_DELETE; }
          | AMove
          | ACopy
          | ARewrite
          | _IGNORE ={ act->_Act = ACT_IGNORE; }
          | ADisplay
          | AAFlag
          | ADelFile
          | ANewMsg
          | AWriteFile
          | AAppendToFile
          | ACall
          | ARoute
	  | ARouteFbox
	  | ARouteHub
          | APoll
          | _DELETEATTACH ={ act->_Act = ACT_DELETEATTACH; }
          | AChangePath
	  | AToLowerPath
	  | AToUpperPath
          | AMoveAttach
	  | AMoveAttachFbox
          | ACopyAttach
	  | ACopyAttachFbox
          | ASplit
          | ARecode
          | AScript
	  | AAddKludge
          ;

AAddNote : _ADDNOTE _STRING ={
            act->_Act = ACT_ADDNOTE;
            act->_Tpl = new Template();
            if (!act->_Tpl->Set($<ch>2)) {
               yyerror("Template file is not accesible.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               YYABORT;
            }
            act->_Tpl->sd = ScanDirs.GetLast();
         }
         ;

AMove    : _MOVE _STRING ={
            act->_Act = ACT_MOVE;
            act->_Base = MakeBase($<ch>2);
            if (act->_Base == NULL) {
               YYABORT;
            }
            if (!act->_Base->Set($<ch>2,BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
         }
         ;

ACopy    : _COPY _STRING ={
            act->_Act = ACT_COPY;
            act->_Base = MakeBase($<ch>2);
            if (act->_Base == NULL) {
               YYABORT;
            }
            if (!act->_Base->Set($<ch>2,BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
         }
         ;

ARewrite : _REWRITE ={
              MaskMode = 1;
              act->_Act = ACT_REWRITE;
           }
           MParam ={
              act->_Mask = msk;
           }
         ;

ADisplay : _DISPLAY _STRING ={
            act->_Act = ACT_DISPLAY;
            act->_TplName = strdup($<ch>2);
         }
         ;

AScript  : _ASCRIPT _STRING ={
            act->_Act = ACT_SCRIPT;
            if (ScriptWordExists($<ch>2) == FALSE) {
               yyerror("Script function not found.");
               YYABORT;
            }
            act->_TplName = strdup($<ch>2);
         }
         ;

AAFlag   : AFlag ={
            act->_Act = ACT_FLAG;
            act->_OutDir = strdup($<ch>1);
         }
         ;

AFlag    : _FLAG _STRING = { $<ch>$ = $<ch>2; }
         ;

ADelFile : _DELFILE _STRING ={
            act->_Act = ACT_DELFILE;
            act->_OutDir = strdup($<ch>2);
         }
         ;

ANewMsg  : _NEWMSG  ={
            MaskMode = 1;
            act->_Act = ACT_NEWMSG;
         }
         _STRING _STRING MParam ={
            act->_Tpl = new Template();
            if (!act->_Tpl->Set($<ch>3)) {
               yyerror("Template file is not accesible.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               YYABORT;
            }
            act->_Tpl->sd =  ScanDirs.GetLast();
            act->_Base = MakeBase($<ch>4);
            if (act->_Base == NULL || !act->_Base->Set($<ch>4,BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
            act->_Mask = msk;

         }
         ;

AWriteFile : _WRITEFILE _STRING _STRING ={
              act->_Act = ACT_WRITEFILE;
              act->_Tpl = new Template();
              if (!act->_Tpl->Set($<ch>2)) {
                 yyerror("Template file is not accesible.");
                 delete act->_Tpl;
                 act->_Tpl = NULL;
                 YYABORT;
              }
              act->_Tpl->sd =  ScanDirs.GetLast();
              act->_OutDir = strdup($<ch>3);
           }
           ;

AAppendToFile : _APPENDTOFILE _STRING _STRING ={
                   act->_Act = ACT_ADDFILE;
                   act->_Tpl = new Template();
                   if (!act->_Tpl->Set($<ch>2)) {
                      yyerror("Template file is not accesible.");
                      delete act->_Tpl;
                      act->_Tpl = NULL;
                      YYABORT;
                   }
                   act->_Tpl->sd =  ScanDirs.GetLast();
                   act->_OutDir = strdup($<ch>3);
              }
              ;

ACall : _CALL _STRING _STRING _STRING ={
           act->_Act = ACT_CALL;
           act->_Tpl = new Template();
           if (!act->_Tpl->Set($<ch>2)) {
              yyerror("Template file is not accesible.");
              delete act->_Tpl;
              act->_Tpl = NULL;
              YYABORT;
           }
           act->_Tpl->sd =  ScanDirs.GetLast();
           act->_OutDir = strdup($<ch>3);
           act->_TplName = strdup($<ch>4);
      }
      | _CALL _STRING ={
           act->_Act = ACT_CALL;
           act->_TplName = strdup($<ch>2);
      }
      ;

ARoute : _ROUTE RouMode ={ cffa.Clean(); } faddress ={
          act->_Act = ACT_ROUTE;
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action Route in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = $<pktmode>2;
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid routing address.");
             YYABORT;
          }
       }
       ;

ARouteFbox : _ROUTEFBOX RouMode ={ cffa.Clean(); } faddress ={
          act->_Act = ACT_ROUTEFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: RouteFilebox.");
	   YYABORT;
	  }
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action RouteFilebox in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = $<pktmode>2;
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid routing address.");
             YYABORT;
          }
       }
       ;

ARouteHub : _ROUTEHUB RouMode ={ cffa.Clean(); } ={
          act->_Act = ACT_ROUTEHUB;
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action RouteHub in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = $<pktmode>2;
       }
       ;


ACopyAttachFbox : _COPYATTACHFBOX RouMode ={ cffa.Clean(); } faddress ={
          act->_Act = ACT_COPYATTACHFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: CopyAttachFilebox.");
	   YYABORT;
	  }
          act->_Flav = $<pktmode>2;
          act->_f = cffa;
       }
       ;

AMoveAttachFbox : _MOVEATTACHFBOX RouMode ={ cffa.Clean(); } faddress ={
          act->_Act = ACT_MOVEATTACHFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: MoveAttachFilebox.");
	   YYABORT;
	  }
          act->_Flav = $<pktmode>2;
          act->_f = cffa;
       }
       ;

RouMode : _HOLD   ={ $<pktmode>$ = F_HOLD; }
        | _CRASH  ={ $<pktmode>$ = F_CRASH; }
        | _DIRECT ={ $<pktmode>$ = F_DIRECT; }
        | _NORMAL ={ $<pktmode>$ = F_NORMAL; }
	| _IMMEDIATE={ $<pktmode>$ = F_IMMEDIATE; }
        ;

APoll : _POLL RouMode ={ cffa.Clean(); } faddress ={
          act->_Act = ACT_POLL;
          act->_Flav = $<pktmode>2;
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid poll address.");
             YYABORT;
          }
       }
      ;

AChangePath : _CHANGEPATH _STRING ={
               act->_Act = ACT_CHANGEPATH;
               if (strlen($<ch>2) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup($<ch>2);
            }
            ;

AToLowerPath : _TOLOWERPATH ={
               act->_Act = ACT_TOLOWERPATH;
            }
            ;


AToUpperPath : _TOUPPERPATH ={
               act->_Act = ACT_TOUPPERPATH;
            }
            ;

AAddKludge : _ADDKLUDGE _STRING _STRING ={
               act->_Act = ACT_ADDKLUDGE;
	       act->_OutDir = strdup($<ch>2);
	       act->_TplName = strdup($<ch>3);
            }
            ;


AMoveAttach : _MOVEATTACH _STRING ={
               act->_Act = ACT_MOVEATTACH;
               if (!DirExists($<ch>2)) {
	         Log.Level(LOGE) << "Target directory '" << $<ch>2 << "' not found." << EOL;
               }
               if (strlen($<ch>2) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup($<ch>2);
            }
            ;

ACopyAttach : _COPYATTACH _STRING ={
               act->_Act = ACT_COPYATTACH;
               if (!DirExists($<ch>2)) {
	         Log.Level(LOGE) << "Target directory '" << $<ch>2 << "' not found." << EOL;
               }
               if (strlen($<ch>2) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup($<ch>2);
            }
            ;

ASplit      : _SPLIT _DIGIT_ ={
               act->_Act = ACT_SPLIT;
               if ($<ln>2 < 1 || $<ln>2 > 65535) {
                  yyerror("Parameter 'Lines' should be positive integer between 1 and 65535");
                  YYABORT;
               }
               act->_Lines = $<ln>2;
            }
            ;

ARecode     : _RECODE _STRING ={
               FILE *fp = NULL;
               char buf[512],*p,*q;
               int in,on,count;
               int line = 0;

                  act->_Act = ACT_RECODE;
                  fp = fopen($<ch>2,"r");
                  if (fp == NULL) {
                     yyerror("Unable to open file");
                     YYABORT;
                  }
                  act->_TplName = (char *)malloc(256);
                  CheckMem(act->_TplName);
                  for (count = 0; count < 256; count++) act->_TplName[count] = (char) count;
                  count = 0;
                  line = 0;

                  while (fgets((char*)buf,sizeof(buf),fp)) {
                     line++;
                     p = strtok((char*)buf," \t\n#");
                     q = strtok(NULL," \t\n#");
                     if (p != NULL && q != NULL) {
                        in = ctoi((char *)p);
                        if (in > 255) {
                           sprintf(buf, "%s: Error in line %d.", $<ch>2, line);
                           yyerror(buf);
                           fclose(fp);
                           free(act->_TplName);
                           YYABORT;
                        }
                        on=ctoi((char *)q);
                        if (in != 0 && on != 0) {
                           if (count++ < 256 ) {
                              act->_TplName[in]=on;
                           } else {
                              sprintf(buf,"Char map table \"%s\" is big",$<ch>2);
                              yyerror(buf);
                              fclose(fp);
                              free(act->_TplName);
                              YYABORT;
                           }
                        }
                     } /* if */
                  } /* While */
                  fclose(fp);
            }
            ;


/* -------------- */

faddress : FullFtnAddr
         | '!' FullFtnAddr = { cffa.Zone(cffa.Zone() | FA_NOTMASK); }
         ;

FullFtnAddr : nodeaddr
            | pointaddr
            | '*'
               = {
                  cffa.Zone(FA_ANYMASK);
                  cffa.Net(FA_ANYMASK);
                  cffa.Node(FA_ANYMASK);
                  cffa.Point(FA_ANYMASK);
               }
            | '#'
               = {
                  cffa.Zone(FA_LSTMASK);
                  cffa.Net(FA_LSTMASK);
                  cffa.Node(FA_LSTMASK);
                  cffa.Point(FA_LSTMASK);
               }
            | 'H'
               = {
                  cffa.Zone(FA_HOLDMASK);
                  cffa.Net(FA_HOLDMASK);
                  cffa.Node(FA_HOLDMASK);
                  cffa.Point(FA_HOLDMASK);
               }
            | 'U'
               = {
                  cffa.Zone(FA_HUBMASK);
                  cffa.Net(FA_HUBMASK);
                  cffa.Node(FA_HUBMASK);
                  cffa.Point(FA_HUBMASK);
               }
            | 'D'
               = {
                  cffa.Zone(FA_DOWNMASK);
                  cffa.Net(FA_DOWNMASK);
                  cffa.Node(FA_DOWNMASK);
                  cffa.Point(FA_DOWNMASK);
               }
            | 'P'
               = {
                  cffa.Zone(FA_PVTMASK);
                  cffa.Net(FA_PVTMASK);
                  cffa.Node(FA_PVTMASK);
                  cffa.Point(FA_PVTMASK);
               }
            | '@'
               = {
                  cffa.Zone(FA_OURMASK);
                  cffa.Net(FA_OURMASK);
                  cffa.Node(FA_OURMASK);
                  cffa.Point(FA_OURMASK);
               }
            | '$'
               = {
                  cffa.Zone(FA_FROMMASK);
                  cffa.Net(FA_FROMMASK);
                  cffa.Node(FA_FROMMASK);
                  cffa.Point(FA_FROMMASK);
               }
            | '%'
               = {
                  cffa.Zone(FA_TOMASK);
                  cffa.Net(FA_TOMASK);
                  cffa.Node(FA_TOMASK);
                  cffa.Point(FA_TOMASK);
               }
            | '%' '.' _DIGIT_
               = {
                  if ($<ln>3 != 0) {
                     yyerror("parse error");
                     YYABORT;
                  }
                  cffa.Zone(FA_TOMASK);
                  cffa.Net(FA_TOMASK);
                  cffa.Node(FA_TOMASK);
                  cffa.Point(0);
               }
            ;

pointaddr: nodeaddr '.' PntAddr
         ;

PntAddr  : dw   = { cffa.Point($<ln>1); }
         | '&'  = { cffa.Point(FA_SUBMASK); }
         ;

nodeaddr : dw ':' dw '/' dw
            = {
               cffa.Zone($<ln>1);
               cffa.Net($<ln>3);
               cffa.Node($<ln>5);
               cffa.Point(0);
            }
         ;

dw       : _DIGIT_ = { $<ln>$ = $<ln>1; }
         | '*' = { $<ln>$ = FA_ANYMASK; }
         ;


%%


