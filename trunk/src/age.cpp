/*
 *  RNtrack - FTN message tracker/router
 *
 *  age.cpp - Message age routines
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
#include <string.h>
#include <ctype.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "scandir.hpp"
#include "age.hpp"
#include "mytypes.hpp"

// --------------------------------------------------------------------
// --------------------------------------------------------------------

int AgeIsOver(time_t D, uint MAge) {
   return (AgeIs(D) > (int) MAge);
}

int AgeIs(time_t D) {
time_t t;

   t = time(NULL);
   if (D == 0) return 0;
   if (t < D) return 0;
   return ((t - D) / (60 * 60 * 24));
}
// --------------------------------------------------------------------

int SetMaxAge(int tmt) {
IndBiList<ScanDir>::ElemPtr sd;

   sd = ScanDirs.GetLast();
   if (sd == NULL) {
      if (MaxAge != 0) {
         yyerror("Global MaxAge already defined.");
         return (-1);
      }
   } else {
      if (sd->_MaxAge != 0) {
         yyerror("MaxAge for this ScanDir already defined.");
         return (-1);
      }
   }
   if (tmt < 1 || tmt > 65535) {
      yyerror("Parameter must be a number between 1 and 65535.");
      return (-1);
   }
   if (sd != NULL) {
      sd->_MaxAge = tmt;
   } else {
      MaxAge = tmt;
   }
   return 0;
}



// ---------------------------- END --------------------------------------
