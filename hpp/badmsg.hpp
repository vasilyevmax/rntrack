/*
 *  RNtrack - FTN message tracker/router
 *
 *  badmsg.hpp - Work with bad messages
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

#ifndef _BADMSG_HPP_
#define _BADMSG_HPP_

#include "msgbase.hpp"

typedef enum {SKIP, EXIT, MOVE, REMOVE} tBadMsgMode;
int SetBadMode(tBadMsgMode bmode, char * bname);
void DoBadMsg(MSGBASE & b);

#endif

