/*
 *  RNtrack - FTN message tracker/router
 *
 *  badpkt.cpp - Work with bad packets
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
#include "configure.hpp"
#include "scandir.hpp"
#include "mytypes.hpp"
#include "outbound.hpp"

// --------------------------------------------------------------------

int SetBadPktMode(tBadMsgMode bpmode, char * bpath)
{
    static int BadPktAlready = FALSE;

    if(BadPktAlready)
    {
        yyerror("BadPackets: already defined.");
        return -1;
    }

    BadPktAlready = TRUE;
    BadPktMode    = bpmode;

    if(bpath != NULL)
    {
        if(!DirExists(bpath))
        {
            yyerror("Unable to open bad PKT directory.");
            return -1;
        }

        BadPktDir = strdup(bpath);
    }

    return 0;
}

// --------------------------------------------------------------------

int BadPkt(char * PktName)
{
    char Buff[BUFF_SIZE];

    Buff[0] = '\0';

    if(BadPktMode == SKIP)
    {
        Log.Level(LOGE) << "   PKT '" << PktName << "' skipped." << EOL;
    }
    else if(BadPktMode == MOVE)
    {
        RSTRLCPY(Buff, MakeAPktName(BadPktDir), BUFF_SIZE);

        if(FileMove(Buff, PktName))
        {
            Log.Level(LOGE) << "   PKT '" << PktName << "' moved to '" <<
                               Buff << "'." << EOL;
        }
        else
        {
            Log.Level(LOGE) << "   Can't move PKT '" << PktName << "' to '" <<
                               Buff << "'." << EOL;
            return -1;
        }
    }
    else if(BadPktMode == REMOVE)
    {
        if(!unlink(PktName))
        {
            Log.Level(LOGE) << "   PKT '" << PktName << "' removed." << EOL;
        }
        else
        {
            Log.Level(LOGE) << "   Can't remove PKT '" << PktName << "'." <<
                               EOL;
            return -1;
        }
    }

    return 0;
} // BadPkt

// ---------------------------- END --------------------------------------
