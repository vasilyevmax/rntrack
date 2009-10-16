/*
 *  RNtrack - FTN message tracker/router
 *
 *  badmsg.cpp - Work with bad messages
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
#include "mytypes.hpp"

// --------------------------------------------------------------------
// --------------------------------------------------------------------

int SetBadMode(tBadMsgMode bmode, char *bname) {
static int BadAlready = FALSE;

   if (BadAlready) {
      yyerror("BadMessages: already defined.");
      return(-1);
   }
   BadAlready = TRUE;
   BadMsgMode = bmode;
   if (bname != NULL) {
      if (strlen(bname) == 0) {
         yyerror("Missind message base name.");
         return (-1);
      }
      if (*bname == '$' || *bname == '#' || *bname == '@') {
         yyerror("You can use only MSG base as a base for bad mail.");
         return (-1);
      }

      BadMsgBase = MakeBase(bname);
      if (BadMsgBase == NULL) return (-1);
      if (!BadMsgBase->CheckOut()) {
         delete BadMsgBase;
         return (-1);
      }
      if (!BadMsgBase->Set(bname,BASE_OUT)) {
         delete BadMsgBase;
         yyerror("Invalid message base name.");
         return (-1);
      }
      BadMsgBase->Rewind();
   }

   return (0);
}

void DoBadMsg(MSGBASE &b) {
char *Buff;
   switch(BadMsgMode) {
      case REMOVE:
         Log.Level(LOGE) << "Delete bad message " << b.MessageName() << EOL;
         b.DeleteMsg();
         break;
      case EXIT:
         Log.Level(LOGE) << "Message " << b.MessageName() << " is bad. Exit." << EOL;
         exit(-1);
      case SKIP:
         Log.Level(LOGE) << "Skip bad message " << b.MessageName() << EOL;
         break;
      case MOVE:
         Buff = b.ReadToMem();
         if (Buff == NULL) {
            Log.Level(LOGE) << "Skip bad message " << b.MessageName() << EOL;
            break;
         } else {
            Log.Level(LOGE) << "Move bad message " << b.MessageName()
                            << " to " << BadMsgBase->BaseName() << EOL;
         }
         if (!BadMsgBase->WriteFromMem(Buff)) {
            free(Buff);
            break;
         }
         free(Buff);
         b.DeleteMsg();
         break;
   }
}

// ---------------------------- END --------------------------------------
