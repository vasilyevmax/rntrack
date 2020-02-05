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
    #include "constant.hpp"
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

#define  BASE_IN   0x0001
#define  BASE_OUT  0x0002
#define  BASE_ECHO 0x0004

class MSGBASE
{
public:
// MSGBASE();
    virtual bool Rewind(void)                = 0;
    virtual bool Set(char * c, int BaseType) = 0;
    virtual bool Next(void)                  = 0;
    virtual bool ReadMsg(cMSG & m)           = 0;
    virtual bool WriteMsg(cMSG & m)          = 0;
    virtual bool DeleteMsg(void)             = 0;
    virtual bool WriteNewMsg(cMSG & m)       = 0;
    virtual void Clear(void)                 = 0;
    virtual void Print(void)                 = 0;
    virtual char * ReadToMem(void)           = 0;
    virtual bool WriteFromMem(char * Buff)   = 0;
    virtual char * MessageName(void)         = 0;
    virtual char * BaseName(void)            = 0;
    virtual bool Renumber(void)              = 0;
    virtual bool CheckOut(void)              = 0;
    virtual bool CheckIn(void)               = 0;
    virtual bool Open(void)                  = 0;
    virtual bool Close(void)                 = 0;

    virtual ~MSGBASE();
};


class MSGASMSG : public MSGBASE
{
    char * DirName;
    unsigned int MsgNum;
    unsigned int MaxNum;
    char * MsgMask;
// private:
public:
    void AddToMask(unsigned int Num);
    bool WriteOneMsg(unsigned int Num, cMSG & m);

    MSGASMSG();
    ~MSGASMSG();
    void Print(void);
    bool Set(char * c, int BaseType);
    void Clear(void);
    bool Next(void);
    bool Rewind(void);
    bool DeleteMsg(void);
    bool ReadMsg(cMSG & m);
    bool WriteMsg(cMSG & m);
    bool WriteNewMsg(cMSG & m);
    char * ReadToMem(void);
    bool WriteFromMem(char * Buff);
    char * MessageName(void);

    char * BaseName(void)
    {
        return DirName;
    }
    bool Renumber(void);

    bool CheckOut(void)
    {
        return TRUE;
    }
    bool CheckIn(void)
    {
        return TRUE;
    }
    bool Open(void)
    {
        return TRUE;
    }
    bool Close(void)
    {
        return TRUE;
    }
};

MSGBASE * MakeBase(char * BName);
void SetMsgAttr(cMSG & m, unsigned short int & Attr);
void SetMsgAttr(unsigned short int & Attr, cMSG & m);
bool WriteMsgBody(cMSG & m, FILE * fh);
void PrepKluChain(char * & cl, cMSG & m, bool IsKludge);
void AddKluToChain(char * & cl, const char * Kn, const char * Kb);

#endif
