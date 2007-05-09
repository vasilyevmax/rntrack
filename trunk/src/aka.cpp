/*
 *  RNtrack - FTN message tracker/router
 *
 *  aka.cpp - Aka routines
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
#include "fidoaddr.hpp"
#include "scandir.hpp"
#include "mytypes.hpp"
#include "a_list.hpp"
#include "log.hpp"

// --------------------------------------------------------------------

class tAka {
public:
   FA _Addr;
   FA _Mask;
   tAka() { _Addr.Clean(); _Mask.Clean(); };
   ~tAka() { return; };
};

IndBiList<tAka> Aka;
// --------------------------------------------------------------------

void AddAka(FA &Addr, FA &Mask) {
tAka *a;

   Log.Level(LOGD) << "AddAka: " << Addr << " " << Mask << EOL;
   a = new tAka;
   a->_Addr = Addr;
   a->_Mask = Mask;
   Aka.AddToEnd(a);
}

FA &GetMyAka(FA const &Addr) {
IndBiList<tAka>::ElemPtr tmt;

   for (tmt = Aka.GetFirst(); tmt != NULL; tmt++) {
      if (tmt->_Mask == Addr) {
         return tmt->_Addr;
      }
   }
   return MyAddr;
}

int IsMyAka(FA const &Addr) {
IndBiList<tAka>::ElemPtr tmt;

   for (tmt = Aka.GetFirst(); tmt != NULL; tmt++) {
      if (tmt->_Addr == Addr) {
         return TRUE;
      }
   }
   return (MyAddr == Addr);
}

int SetAka(FA &f, FA &m) {

   if (!f.Valid()) {
      yyerror("Invalid our addres.");
      return (-1);
   }
   if (f.Masked()) {
      yyerror("Our AKA Address should do not be a mask.");
      return (-1);
   }

   if (!m.Valid()) {
      yyerror("Invalid address.");
      return (-1);
   }
   AddAka(f,m);
   return(0);
}

void DestroyAka(void) {
   Aka.Clear();
}

// ---------------------------- END --------------------------------------
