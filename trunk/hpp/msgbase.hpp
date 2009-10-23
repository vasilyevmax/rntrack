/*
 *  RNtrack - FTN message tracker/router
 *
 *  msgbase.hpp - Message bases. root class and MSG base format.
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

#ifndef _MSGBASE_HPP_
#define _MSGBASE_HPP_

#ifdef HAVE_CONFIG_H
# include "constant.hpp"
#endif

#ifdef HAVE_TIME_H
#include <time.h>
#elif HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#include "a_list.hpp"
#include "utils.hpp"
#include "fidoaddr.hpp"
#include "msg.hpp"
#include "mytypes.hpp"

#define  BASE_IN 0x0001
#define  BASE_OUT 0x0002
#define  BASE_ECHO 0x0004

class MSGBASE {
public:
//   MSGBASE();
   virtual int Rewind(void) = 0;
   virtual int Set(char *c, int BaseType) = 0;
   virtual int Next(void) = 0;
   virtual int ReadMsg(cMSG &m) = 0;
   virtual int WriteMsg(cMSG &m) = 0;
   virtual int DeleteMsg(void) = 0;
   virtual int WriteNewMsg(cMSG &m) = 0;
   virtual void Clear(void) = 0;
   virtual void Print(void) = 0;
   virtual char *ReadToMem(void) = 0;
   virtual int WriteFromMem(char *Buff) = 0;
   virtual char *MessageName(void) = 0;
   virtual char *BaseName(void) = 0;
   virtual int  Renumber(void) = 0;
   virtual int  CheckOut(void) = 0;
   virtual int  CheckIn(void) = 0;
   virtual int  Open(void) = 0;
   virtual int  Close(void) = 0;
   virtual ~MSGBASE();
};


class MSGASMSG: public MSGBASE {
   char *DirName;
   unsigned int MsgNum;
   unsigned int MaxNum;
   char         *MsgMask;
// private:
public:
   void AddToMask(unsigned int Num);
   int WriteOneMsg(unsigned int Num, cMSG &m);
   MSGASMSG();
   ~MSGASMSG();
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
   char *MessageName(void);
   char *BaseName(void) { return DirName; };
   int  Renumber(void);
   int CheckOut(void) { return TRUE; };
   int CheckIn(void) { return TRUE; };
   int Open(void) { return TRUE; };
   int Close(void) { return TRUE; };
};

MSGBASE *MakeBase(char *BName);
void SetMsgAttr(cMSG &m,unsigned short int &Attr);
void SetMsgAttr(unsigned short int &Attr,cMSG &m);
int WriteMsgBody(cMSG &m,FILE *fh);
void PrepKluChain(char *&cl, cMSG &m, int IsKludge);
void AddKluToChain(char *&cl, char *Kn, char *Kb);


#endif
