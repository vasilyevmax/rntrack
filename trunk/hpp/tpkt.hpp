/*
 *  RNtrack - FTN message tracker/router
 *
 *  tpkt.hpp - PKT format definition
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: tpkt.hpp,v 1.1.1.1 2005/01/14 19:18:08 ph0enix Exp $
 */

#ifndef _TPKT_HPP_
#define _TPKT_HPP_

#include "mytypes.hpp"

// --------------------------------------------------------------------
// --------------------------------------------------------------------

typedef struct {
   word FromNode;     // 0   00
   word ToNode;       // 2   02
   word Year;         // 4   04 
   word Month;        // 6   06
   word Day;          // 8   08
   word Hour;         // 10  0A
   word Minute;       // 12  0C
   word Second;       // 14  1F  
   word Baud;         // 16  10
   word c0002;        // 18  12
   word FromNet;      // 20  14 
   word ToNet;        // 22  16
   byte ProductCodeL; // 24  18
   byte RevisionH;    // 25  19
   char Passwd[8];    // 26  1A
   word FromZone;     // 34  22
   word ToZone;       // 36  24
   word AuxNet;       // 38  26
   word c0100;        // 40  28
   byte ProductCodeH; // 42  29
   byte RevisionL;    // 43  2A
   word c0001;        // 40  2B
   word FromZone2;    // 42  2A
   word ToZone2;
   word FromPoint;
   word ToPoint;
   byte Reserved[4];
} tPKTH;

#endif
