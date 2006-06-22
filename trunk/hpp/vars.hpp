/*
 *  RNtrack - FTN message tracker/router
 *
 *  vars.hpp - Global variables definitions
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: vars.hpp,v 1.4 2005/03/22 19:10:36 ph0enix Exp $
 */

#ifndef _VARS_HPP_
#define _VARS_HPP_
#include <time.h>
#include "log.hpp"
#include "nodelist.hpp"
#include "badmsg.hpp"
#include "msgbase.hpp"
#include "mytypes.hpp"

typedef enum { KILL_NEVER, KILL_ALWAYS, KILL_FLAG } KillModeT;
typedef enum { CHECKPNT_NEVER, CHECKPNT_HARD, CHECKPNT_SOFT } CheckPointsT;
typedef enum { FILEBOXLONG, FILEBOXTMLONG, FILEBOXTMSHORT, FILEBOXBRAKE } fileboxType;

extern KillModeT KillMode;

extern char *ConfigFile;
extern LogStream Log;
extern int LogLevel;
extern char *LogFileName;
extern NodeLists Ndl;
extern FA MyAddr;
extern char *SysopName;
extern int UseOwnZone;
extern char *LoopStr;
extern int ForceINTL;
extern unsigned int MaxAge;

extern int UseASO;
extern int UseBrake;
extern int UseFileBoxes;

extern char *CurrLinePos;
extern char *LastCfgLine;
extern uint LastCfgLineNum;

extern tBadMsgMode BadMsgMode;
extern tBadMsgMode BadPktMode;
extern MSGBASE *BadMsgBase;

extern int LogIgnore;

extern int SkipHiddenFiles;
extern char *FileInbound;

extern int AddToNullPkt;
extern char *Outbound;
extern char *FileBoxDir;
extern char *TrafficLog;
extern MSGBASE *TempMail;
extern int UTC;
extern sdword CHP;
extern int UnpackNeed;

extern char *Origin;
extern char *Tearline;

extern time_t LastTime;
extern int CreateMissingBase;
extern char *APktDir;
extern unsigned int MaxAttachSize;
extern unsigned int MaxMsgSize;
extern unsigned int MaxPktSize;
extern time_t MaxNodelistAge;

class ScanDir;

extern ScanDir *BeforeRoute;
extern ScanDir *AfterRoute;

extern int NewVIAType;
extern int SetViaAlways;
extern int SoftCheckInNodelists;
extern CheckPointsT CheckPoints;
extern fileboxType FileBoxType;
class DoList;
extern DoList *LastDo;
extern int PrevMask;
extern char *TimeStampFile;
extern char *BadPktDir;
extern char *Semaphore;
extern unsigned int  SemaphoreTime;
extern char *TrafficLogTpl;
extern int IgnoreBSY;
extern int IgnoreAttachPath;
extern int StripPathInPKT;
extern int AgeFromVia;
#endif

