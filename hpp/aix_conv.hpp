/*
 *  RNtrack - FTN message tracker/router
 *
 *  aix_conv.hpp - AIX byte order transform
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: aix_conv.hpp,v 1.1.1.1 2005/01/14 19:18:05 ph0enix Exp $
 */

#ifndef _AIX_CONV_HPP_
#define _AIX_CONV_HPP_
#endif

#include "tpkt.hpp"

int AIXConvPKTH (tPKTH &PKTH);
short int RotateShort (short int s);
int RotateInt (int i);
