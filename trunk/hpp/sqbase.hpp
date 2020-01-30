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
#include "msgapi.h"
#include "mytypes.hpp"


class SQUISH : public MSGBASE
{
    HAREA Area;
    char * DirName;
    unsigned int MsgNum;
    unsigned int tMsgNum;
    unsigned int MaxNum;
    bool PrevIsDel;
    char bType;
// private:
public:
    bool WriteOneMsg(unsigned int Num, cMSG & m);

    SQUISH();
    SQUISH(char _bType);
    ~SQUISH();
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
    bool Open(void);
    bool Close(void);
};

#endif
