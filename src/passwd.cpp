/*
 *  RNtrack - FTN message tracker/router
 *
 *  passwd.cpp - Password routines
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: passwd.cpp,v 1.4 2005/07/30 20:11:14 ph0enix Exp $
 */

#ifdef __MINGW32__
#ifndef _STAT_DEFINED
#define _STAT_DEFINED 1
#endif
#endif
#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <ctype.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "fidoaddr.hpp"
#include "scandir.hpp"
#include "mytypes.hpp"

// --------------------------------------------------------------------

class tPasswd {
public:
   FA _Addr;
   char _Passwd[9];
   tPasswd() { _Addr.Clean(); memset(_Passwd,0,8); };
   ~tPasswd() { return; };
};

IndBiList<tPasswd> Passwd;
// --------------------------------------------------------------------

void AddPasswd(FA &Addr, char *P) {
tPasswd *a;

   a = new tPasswd;
   a->_Addr = Addr;
   RSTRLCPY(a->_Passwd,P,8);
   a->_Passwd[8] = '\0';
   Passwd.AddToEnd(a);
}

char *GetPasswd(FA const &Addr) {
IndBiList<tPasswd>::ElemPtr tmt;

   for (tmt = Passwd.GetFirst(); tmt != NULL; tmt++) {
      if (tmt->_Addr == Addr) {
         return tmt->_Passwd;
      }
   }   
   return NULL;
}

int SetPasswd(FA &f, char *tmt) {
char Pwd[9];

   if (strlen(tmt) == 0) {
      yyerror("Missed parameter: Password.");
      return (-1);
   }

   if (strlen(tmt) > 8) {
      yyerror("Password should be no more 8 characters.");
      return (-1);
   }

   if (!f.Valid()) {
      yyerror("Invalid addres.");
      return (-1);
   }
   RSTRLCPY(Pwd,tmt,8);
   nls_strupr(Pwd);
   AddPasswd(f,Pwd);
   return(0);
}

void DestroyPasswd(void) {
   Passwd.Clear();
}

// ---------------------------- END --------------------------------------
