/*
 *  RNtrack - FTN message tracker/router
 *
 *  attach.hpp - Work with attaches
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: attach.hpp,v 1.1.1.1 2005/01/14 19:18:07 ph0enix Exp $
 */

#ifndef _ATTACH_HPP_
#define _ATTACH_HPP_
#include "time.h"
#include "fidoaddr.hpp"

int SetFileInbound(char *tmt);
int SetSkipHiddenFiles(void);
int PrintAttach(cMSG &m);
int DeleteAttach(cMSG &m);
int ChangePath(cMSG &m,char *Path);
int ToLowerPath(cMSG &m);
int ToUpperPath(cMSG &m);
int MoveAttach(cMSG &m,char *Path);
int CopyAttach(cMSG &m,char *Path);
int AttachExists(cMSG &m);
int AddAttachToLo(cMSG &m);
int AddFboxAttachToLo(cMSG &m, char *path);
int DelAttachFromLo(cMSG &m);
int GetAttSize(cMSG &m);

#endif

