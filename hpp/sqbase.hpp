/*
 *  RNtrack - FTN message tracker/router
 *
 *  sqbase.hpp - Work with Squish and JAM bases
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

#ifndef _SQBASE_HPP_
#define _SQBASE_HPP_

#include "a_list.hpp"
#include "utils.hpp"
#include "fidoaddr.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include <smapi/msgapi.h>
#include "mytypes.hpp"


class SQUISH: public MSGBASE {
   HAREA Area;
   char *DirName;
   unsigned int MsgNum;
   unsigned int tMsgNum;
   unsigned int MaxNum;
   int PrevIsDel;
   char bType;
// private:
public:
   int WriteOneMsg(unsigned int Num, cMSG &m);
   SQUISH();
   SQUISH(char _bType);
   ~SQUISH();
   void Print(void);
   int  Set(char *c, int BaseType);
   void Clear(void);
   int  Next(void);
   int  Rewind(void);
   int  DeleteMsg(void);
   int  ReadMsg(cMSG &m);
   int  WriteMsg(cMSG &m);
   int  WriteNewMsg(cMSG &m);
   char *ReadToMem(void);
   int  WriteFromMem(char *Buff);
   char *MessageName(void);
   char *BaseName(void) { return DirName; };
   int  Renumber(void);
   int  CheckOut(void) { return TRUE; };
   int  CheckIn(void) { return TRUE; };
   int  Open(void);
   int  Close(void);
};

#endif

