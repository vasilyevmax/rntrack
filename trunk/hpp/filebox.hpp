/*
 *  RNtrack - FTN message tracker/router
 *
 *  filebox.hpp - Filebox routines
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

#ifndef _FILEBOX_HPP_
#define _FILEBOX_HPP_
#include "fidoaddr.hpp"

int SetUseFileBoxes(void);
char *GetFilebox(FA const &Addr);
int SetFilebox(FA &f, char *tmt);
void DestroyFilebox(void);
int SetFileBoxDir(char *tmt);
int SetFileBoxType(fileboxType fbtype);
char *MakeFileboxName(FA &f, PKTMode m);

#endif

