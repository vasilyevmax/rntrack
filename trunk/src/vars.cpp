/*
 *  RNtrack - FTN message tracker/router
 *
 *  vars.cpp - Global variables initiaization
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

#include "vars.hpp"

char *ConfigFile = NULL;
LogStream Log;
int LogLevel = -1;
char *LogFileName = NULL;
NodeLists Ndl;
FA MyAddr;
char *SysopName = NULL;
int UseOwnZone = FALSE;
char *LoopStr = NULL;
int ForceINTL = FALSE;
char *CurrLinePos = NULL;
char *LastCfgLine = NULL;
uint MaxAge = 0;
uint LastCfgLineNum = 0;
tBadMsgMode BadMsgMode = EXIT;
tBadMsgMode BadPktMode = SKIP;
MSGBASE *BadMsgBase = NULL;
int LogIgnore = TRUE;
int SkipHiddenFiles = FALSE;
char *FileInbound = NULL;
int AddToNullPkt = FALSE;
char *Outbound = NULL;
char *FileBoxDir = NULL;
char *TrafficLog = NULL;
MSGBASE *TempMail = NULL;
int UTC = 99;
sdword CHP = 0;
int UnpackNeed = FALSE;
char *Origin = NULL;
char *Tearline = NULL;
int CreateMissingBase = FALSE;
char *APktDir = NULL;
unsigned int MaxAttachSize= 0;
unsigned int MaxMsgSize=0;
unsigned int MaxPktSize=0;
KillModeT KillMode = KILL_ALWAYS;
time_t MaxNodelistAge = (time_t)-1;
ScanDir *BeforeRoute = NULL;
ScanDir *AfterRoute = NULL;
int NewVIAType = FALSE;
int SetViaAlways = FALSE;
int SoftCheckInNodelists = FALSE;
CheckPointsT CheckPoints = CHECKPNT_NEVER;
fileboxType FileBoxType = FILEBOXLONG;
DoList *LastDo = NULL;
int PrevMask = 0;
char *TimeStampFile = NULL;
char *Semaphore = NULL;
char *BadPktDir = NULL;
unsigned int  SemaphoreTime = 0;
char *TrafficLogTpl = NULL;
int UseASO = FALSE;
int UseBrake = FALSE;
int UseFileBoxes = FALSE;
int IgnoreBSY = FALSE;
int IgnoreAttachPath = FALSE;
int StripPathInPKT = FALSE;
int AgeFromVia = FALSE;
