/*
 *  RNtrack - FTN message tracker/router
 *
 *  domain.cpp - Domain routines
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

class tDomain {
public:
   FA _Mask;
   char _Domain[11];
   tDomain() { _Mask.Clean(); memset(_Domain,0,10); };
   ~tDomain() { return; };
};

IndBiList<tDomain> Domain;
// --------------------------------------------------------------------

void AddDomain(FA &Addr, char *P) {
tDomain *a;

   a = new tDomain;
   a->_Mask = Addr;
   RSTRLCPY(a->_Domain,P,10);
   a->_Domain[10] = '\0';
   Domain.AddToEnd(a);
}

char *GetDomain(FA const &Addr) {
IndBiList<tDomain>::ElemPtr tmt;

   for (tmt = Domain.GetFirst(); tmt != NULL; tmt++) {
      if (tmt->_Mask == Addr) {
         return tmt->_Domain;
      }
   }   
   return NULL;
}

int SetDomain(FA &f, char *tmt) {
char Dom[11];

   if (strlen(tmt) == 0) {
      yyerror("Missed parameter: Domain.");
      return (-1);
   }

   if (strlen(tmt) > 10) {
      yyerror("Domain should be no more 10 characters.");
      return (-1);
   }

   if (!f.Valid()) {
      yyerror("Invalid addres.");
      return (-1);
   }
   RSTRLCPY(Dom,tmt,10);
   AddDomain(f,Dom);
   return(0);
}

void DestroyDomain(void) {
   Domain.Clear();
}

// ---------------------------- END --------------------------------------
