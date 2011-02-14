/*
 *  RNtrack - FTN message tracker/router
 *
 *  pktbase.hpp - Work with *.PKT base
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

#ifndef _PKTBASE_HPP_
#define _PKTBASE_HPP_

#if defined(__MSVC__)
#include "dirent/dirent.h"
#endif
#include "a_list.hpp"
#include "utils.hpp"
#include "fidoaddr.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "mytypes.hpp"


class PKTBASE: public MSGBASE {
   FA           FMask;
   char         *DirName;
   char         *PktName;
   char         *MsgMask;
   unsigned int MsgNum;
   unsigned int MaxMsgNum;
   int          fNoCheckPwd;
   FILE         *fh;
   DIR          *dp;
   int          fForWrite;
   int          fCreated;

   bool _Close(void);
   bool _Open(void);
   void AddToMask(unsigned int Num);
   bool CopyHeader(FILE *tf);
   bool CopyTail(FILE *tf);
   bool CopyMessages(FILE *tf);
   bool CopyOneMessage(FILE *tf);
   bool ReadHeader(FILE *tf, char *Buff);
public:
  bool WriteOneMsg(unsigned int Num, cMSG &m);
   PKTBASE();
   ~PKTBASE();
   void Print(void);
   bool Set(char *c, int BaseType);
   void Clear(void);
   bool Next(void);
   bool Rewind(void);
   bool DeleteMsg(void);
   bool ReadMsg(cMSG &m);
   bool WriteMsg(cMSG &m);
   bool WriteNewMsg(cMSG &m);
   char *ReadToMem(void);
   bool WriteFromMem(char *Buff);
   //  { return FALSE; };
   char *MessageName(void);
   char *BaseName(void);
   bool  Renumber(void);
   bool CheckOut(void);
   bool CheckIn(void) { return TRUE; };
   bool Open(void) { return TRUE; };
   bool Close(void) { return _Close(); };
};

#endif

