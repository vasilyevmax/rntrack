/*
 *  RNtrack - FTN message tracker/router
 *
 *  scripts.hpp - Work with scripts
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

#ifndef _SCRIPT_HPP_
#define _SCRIPT_HPP_
#include "msg.hpp"
#include "sqbase.hpp"

typedef enum { 
   SS_NOTDEF, SS_OK, SS_ERROR, SS_FALSE
} ScrRet;

int _LoadScriptFile(char *fname);
void PrepareMsgForScript(cMSG &sm);
int ScriptWordExists(char *word);
int InitScriptSystem(void);
void InitScriptValues(void);
int StopScriptSystem(void);
ScrRet DoSomeWord(char *word);
ScrRet DoSomeWordRc(char *word);
ScrRet DoThisWord(char *word);
ScrRet DoThisWordRc(char *word);

/* definitions for error codes */
#define FTR_OUTOFRANGE	 -400

#endif
