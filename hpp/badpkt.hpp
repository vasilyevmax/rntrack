/*
 *  RNtrack - FTN message tracker/router
 *
 *  badpkt.hpp - Work with bad packets
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id: badpkt.hpp,v 1.1.1.1 2005/01/14 19:18:07 ph0enix Exp $
 */

#ifndef _BADPKT_HPP_
#define _BADPKT_HPP_

int SetBadPktMode(tBadMsgMode bpmode, char *bpath);
int BadPkt(char *PktName);

#endif

