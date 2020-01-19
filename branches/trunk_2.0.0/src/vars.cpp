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

#include "compiler.h"
#include "vars.hpp"

char * ConfigFile  = NULL;
LogStream Log;
int LogLevel       = -1;
char * LogFileName = NULL;
NodeLists Ndl;
FA MyAddr;
char * SysopName   = NULL;
bool UseOwnZone    = FALSE;
char * LoopStr     = NULL;
bool ForceINTL     = FALSE;
char * LastCfgLine = NULL;
uint MaxAge = 0;
uint LastCfgLineNum    = 0;
tBadMsgMode BadMsgMode = EXIT;
tBadMsgMode BadPktMode = SKIP;
MSGBASE * BadMsgBase   = NULL;
bool LogIgnore = TRUE;
bool SkipHiddenFiles   = FALSE;
char * FileInbound     = NULL;
bool AddToNullPkt      = FALSE;
char * Outbound = NULL;
char * FileBoxDir      = NULL;
char * TrafficLog      = NULL;
MSGBASE * TempMail     = NULL;
int UTC         = 99;
sdword CHP      = 0;
bool UnpackNeed = FALSE;
char * Origin   = NULL;
char * Tearline = NULL;
bool CreateMissingBase = FALSE;
char * APktDir  = NULL;
unsigned int MaxAttachSize = 0;
unsigned int MaxMsgSize    = 0;
unsigned int MaxPktSize    = 0;
KillModeT KillMode = KILL_ALWAYS;
time_t MaxNodelistAge      = (time_t)-1;
ScanDir * BeforeRoute      = NULL;
ScanDir * AfterRoute = NULL;
bool NewVIAType      = FALSE;
int SetViaAlways = 0; // type 'bool' and constants 'FALSE' and 'TRUE' can not
// be used in embedded perl. We use type int and values 0
// and any positive number
bool SoftCheckInNodelists  = FALSE;
CheckPointsT CheckPoints   = CHECKPNT_NEVER;
fileboxType FileBoxType    = FILEBOXLONG;
DoList * LastDo = NULL;
int PrevMask = 0;
char * TimeStampFile       = NULL;
char * Semaphore = NULL;
char * BadPktDir = NULL;
unsigned int SemaphoreTime = 0;
char * TrafficLogTpl       = NULL;
bool UseASO           = FALSE;
bool UseBrake         = FALSE;
bool UseFileBoxes     = FALSE;
bool IgnoreBSY        = FALSE;
bool IgnoreAttachPath = FALSE;
bool StripPathInPKT   = FALSE;
bool AgeFromVia       = FALSE;

