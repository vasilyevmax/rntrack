/*
 *  RNtrack - FTN message tracker/router
 *
 *  configure.hpp - Configuration routines
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: configure.hpp,v 1.3 2005/03/22 19:10:35 ph0enix Exp $
 */
    
#ifndef _CONFIGURE_HPP_
#define _CONFIGURE_HPP_

typedef enum {LEX_START, LEX_PARSE, LEX_DIGIT, LEX_COMMENT, LEX_STRING,
              LEX_CRLF, LEX_END, LEX_TOKEN, LEX_ERROR, LEX_COMMLINE} tLexState;


int ParseConfig(char *CfgFile);
#undef yyerror
int yyerror(char *s);
int yylex(void);

extern int avail;

int SetMyAddr(FA &f);
int SetLogFile(char *tmt);
int SetTimeStampFile(char *tmt);
int SetLogLevel(int tmt);
int SetCreateMissingBase(void);
int SetForceINTL(void);
int SetNoLogIgnore(void);
int SetSetViaAlways(void);
int SetMaxAttach(int tmt);
int SetMaxMsgSize(int tmt);
int SetMaxPktSize(int tmt);
int SetLoopStr(char *tmt);
int SetOrigin(char *tmt);
int SetSysopName(char *tmt);
int SetTearline(char *tmt);
int SetNewVia(void);
int SetUseOwnZone(void);
int SetUseASO(void);
int SetUseBrake(void);
int SetAgeFromVia(void);
int SetSoftCheckInNodelists(void);
int SetAPktDir(char *tmt);
int SetCheckPoints(CheckPointsT pmode);
int SetNodelistPath(char *tmt);
int SetIndexFile(char *tmt);
int SetUTC(int i);
int SetInclude(char *tmt);
int SetSemaphoreName(char *File, unsigned int SemTime);
int SetTrafficLogTemplate(char *tmt);
int SetIgnoreBSY(void);
int SetIgnoreAttachPath(void);
int LoadScriptFile(char *Fname);
int SetStripPathInPkt(void);
#endif
