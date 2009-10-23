/*
 *  RNtrack - FTN message tracker/router
 *
 *  utils.hpp - Common routines
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

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#ifdef HAVE_CONFIG_H
# include "constant.hpp"
#else
# include <smapi/compiler.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

//#if defined(__WATCOMC__) && (defined(__OS2__) || defined(MSDOS))
/* Why it's not implemented in smapi/compiler.h? */
//#define strcasecmp stricmp
//#define strncasecmp strnicmp
//#endif

#if !defined(HAVE_STRICMP) && defined(HAVE_STRCASECMP) && !defined(stricmp)
# define stricmp(s1,s2) strcasecmp(s1,s2)
# define HAVE_STRICMP
#endif

#ifndef O_BINARY
#define O_BINARY 0
#endif

void CheckMem(char *ptr);
int StrIsNum(char *Str);
int StrIsXNum(char *Str);
int DirExists(char *ptr);
int FileCopy(char *Dst, char *Src);
int FileMove(char *Dst, char *Src);
FILE *fcopen(char *Name, char *Mode);
int ExecP(char *Name);
int SetSemaphore(void);
int ReleaseSemaphore(void);

#ifdef __unix__
unsigned int filelength(int fh);
#endif
int tzoffset(void);
char *GetFilePath(char *Path, char *Name);
char *GetFileName(char *FName, char *Name);
void nls_strupr(char *s);
const char *dirslashbug(const char *dirname);

int fsCompareName(char *Name, char *Mask);

#if defined(__WATCOMC__) && defined(MSDOS)
#ifdef __cplusplus
extern "C" {
#endif
   void pascal far flush_handle2_(int fh);
#ifdef __cplusplus
}
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
   void ShowLogLine(char *msg);
#ifdef __cplusplus
}
#endif

#endif /* _UTILS_HPP_ */

