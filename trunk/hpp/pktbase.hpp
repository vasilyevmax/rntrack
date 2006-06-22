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
 *  $Id: pktbase.hpp,v 1.1.1.1 2005/01/14 19:17:59 ph0enix Exp $
 */

#ifndef _PKTBASE_HPP_
#define _PKTBASE_HPP_

#include <time.h>
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
   
   int _Close(void);
   int _Open(void);
   void AddToMask(unsigned int Num);
   int CopyHeader(FILE *tf);
   int CopyTail(FILE *tf);
   int CopyMessages(FILE *tf);
   int CopyOneMessage(FILE *tf);
   int PKTBASE::ReadHeader(FILE *tf, char *Buff);
public:
   int WriteOneMsg(unsigned int Num, cMSG &m);
   PKTBASE();
   ~PKTBASE();
   void Print(void);
   int Set(char *c, int BaseType);
   void Clear(void);
   int Next(void);
   int Rewind(void);
   int DeleteMsg(void);
   int ReadMsg(cMSG &m);
   int WriteMsg(cMSG &m);
   int WriteNewMsg(cMSG &m);
   char *ReadToMem(void);
   int WriteFromMem(char *Buff);
   //  { return FALSE; };
   char *MessageName(void);
   char *BaseName(void);
   int  Renumber(void);
   int CheckOut(void);
   int CheckIn(void) { return TRUE; };
   int Open(void) { return TRUE; };
   int Close(void) { return _Close(); };
};

#endif

