/*
 *  RNtrack - FTN message tracker/router
 *
 *  sqbase.cpp - Work with Squish and JAM bases
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
#include <assert.h>
#include <errno.h>

#include "msgapi.h"
#include "constant.hpp"
#include "vars.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "sqbase.hpp"
#include "aka.hpp"
#include "unused.h"


static time_t dosftime(struct _stamp & time)
{
    struct tm mytime;

    memset(&mytime, 0, sizeof(struct tm)); /* added by VRP 20000731 */
    mytime.tm_mday = time.date.da;
    mytime.tm_mon  = time.date.mo - 1;
    mytime.tm_year = time.date.yr + 80;
    mytime.tm_hour = time.time.hh;
    mytime.tm_min  = time.time.mm;
    mytime.tm_sec  = time.time.ss * 2;

    return mktime(&mytime);
}

static void dosttime(struct _stamp & time, time_t t)
{
    struct tm * mytime;

    mytime = localtime(&t);
    time.date.da = mytime->tm_mday;
    time.date.mo = mytime->tm_mon + 1;
    time.date.yr = mytime->tm_year - 80;
    time.time.hh = mytime->tm_hour;
    time.time.mm = mytime->tm_min;
    time.time.ss = mytime->tm_sec / 2;
}

SQUISH::SQUISH()
{
    CHP = 515;
    DirName   = NULL;
    MsgNum    = 0;
    tMsgNum   = 0;
    MaxNum    = 0;
    Area      = NULL;
    PrevIsDel = FALSE;
}

SQUISH::SQUISH(char _bType)
{
    CHP = 515;
    DirName   = NULL;
    MsgNum    = 0;
    tMsgNum   = 0;
    MaxNum    = 0;
    Area      = NULL;
    PrevIsDel = FALSE;
    bType     = _bType;
}

SQUISH::~SQUISH()
{
    Clear();
    CHP = 516;
}

// ---------------------------

void SQUISH::Clear(void)
{
    CHP = 51700;

    if(DirName != NULL)
    {
        CHP = 51701;
        free(DirName);
        CHP = 51702;
        DirName = NULL;
    }

    CHP = 51703;

    if(Area != NULL)
    {
        CHP = 51704;
        MsgCloseArea(Area);
        CHP  = 51705;
        Area = NULL;
    }

    MsgNum    = 0;
    tMsgNum   = 0;
    MaxNum    = 0;
    PrevIsDel = FALSE;
    CHP = 51706;
} // Clear

// ---------------------------

bool SQUISH::Open(void)
{
    int TypeOfBase;

    if(bType == '$')
    {
        TypeOfBase = (MSGTYPE_SQUISH | MSGTYPE_NOTH);
    }
    else
    {
        TypeOfBase = (MSGTYPE_JAM);
    }

    CHP  = 51710;
    Area = MsgOpenArea((byte *)DirName + 1, MSGAREA_NORMAL, TypeOfBase);

    if(Area == NULL)
    {
        Log.Level(LOGE) << "SQUISH.Open: Unable to open message base '" <<
                        DirName <<
                        "', code: " << (uint)msgapierr <<
                        ", errno: " << errno << EOL;
        return FALSE;
    }

    return TRUE;
} // Open

// ---------------------------

bool SQUISH::Close(void)
{
    CHP = 51720;

    if(Area != NULL)
    {
        MsgCloseArea(Area);
        Area = NULL;
    }

    return TRUE;
}

// ---------------------------

bool SQUISH::Set(char * Dir, int BaseType)
{
    int TypeOfBase;

    CHP = 518;
    unused(BaseType);
    CHP = 51801;
    Clear();
    CHP = 51802;

    if(*Dir != '$' && *Dir != '@')
    {
        return FALSE;
    }

    if(bType == '$')
    {
        TypeOfBase = (MSGTYPE_SQUISH | MSGTYPE_NOTH);
    }
    else
    {
        TypeOfBase = (MSGTYPE_JAM);
    }

    CHP = 51803;
    msgapierr = 0;

    if(CreateMissingBase)
    {
        CHP  = 51804;
        Area = MsgOpenArea((byte *)Dir + 1, MSGAREA_CRIFNEC, TypeOfBase);
        CHP  = 51805;

        if(Area == NULL)
        {
            Log.Level(LOGD) << "SQUISH.Set: Unable to create message base '" <<
                            Dir << "', code: " << (uint)msgapierr <<
                            ", errno: " << errno << EOL;
        }
    }
    else
    {
        CHP  = 51806;
        Area = MsgOpenArea((byte *)Dir + 1, MSGAREA_NORMAL, TypeOfBase);
        CHP  = 51807;

        if(Area == NULL)
        {
            Log.Level(LOGD) << "SQUISH.Set: Unable to open message base '" <<
                            Dir << "', code: " << (uint)msgapierr <<
                            ", errno: " << errno << EOL;
        }
    }

    if(Area == NULL)
    {
        return FALSE;
    }

    CHP = 51808;
    MsgCloseArea(Area);
    CHP  = 51809;
    Area = NULL;

    if(MsgValidate(TypeOfBase, (byte *)Dir + 1) != 1)
    {
        return FALSE;
    }

    CHP = 51810;
    DirName = strdup(Dir);
    CHP = 51811;
    CheckMem(DirName);
    CHP = 51812;
    return TRUE;
} // Set

// ---------------------------

bool SQUISH::Next(void)
{
    HMSG fh;

    Log.Level(LOGD) << "(1) SQUISH.Next: MsgNum == " << MsgNum <<
                    " tMsgNum == " << tMsgNum << EOL;
    CHP = 519;

    if(Area == NULL)
    {
        return FALSE;
    }

    CHP = 520;

    if(PrevIsDel == FALSE)
    {
        MsgNum++;
    }
    else
    {
        PrevIsDel = FALSE;
    }

    tMsgNum++;

    CHP = 520001;

    while(MsgNum <= MsgGetHighMsg(Area))
    {
        Log.Level(LOGD) << "(W) SQUISH.Next: MsgNum == " << MsgNum <<
                        " tMsgNum == " << tMsgNum << EOL;
        CHP = 520002;
        fh  = MsgOpenMsg(Area, MOPEN_READ, MsgNum);
        CHP = 520003;

        if(fh != NULL)
        {
            CHP = 520004;
            MsgCloseMsg(fh);
            CHP = 520005;
            return TRUE;
        }

        CHP = 520006;

        if(msgapierr != 0 && msgapierr != MERR_NOENT)
        {
            return TRUE;
        }

        CHP = 520007;
        MsgNum++;
        CHP = 520008;
    }

    CHP = 521;
    return FALSE;
} // Next

// ---------------------------

bool SQUISH::Rewind(void)
{
    if(Area == NULL)
    {
//      Log.Level(LOGD) << "Base not opened!!! " << EOL;
        CHP = 524;
        return FALSE;
    }

    CHP = 522;
    Log.Level(LOGD) << "-------- Rewind base --------" << EOL;
    Log.Level(LOGD) << "Base name: " << DirName << EOL;
    CHP = 523;
    CHP = 525;
    Log.Level(LOGD) << "High message number: " << (int)MsgGetHighMsg(Area) <<
                    EOL;

    if(MsgGetHighMsg(Area) == 0)
    {
        CHP = 526;
        return FALSE;
    }

    MsgNum    = 0;
    tMsgNum   = 0;
    PrevIsDel = FALSE;
    CHP = 527;
    return Next();
} // Rewind

// ---------------------------

bool SQUISH::Renumber(void)
{
    CHP = 528;
    return TRUE;
}

// ---------------------------

bool SQUISH::DeleteMsg(void)
{
    CHP = 530;

    if(MsgKillMsg(Area, MsgNum) != 0)
    {
        CHP = 531;
        Log.Level(LOGD) << "SQUISH.DeleteMsg: Unable to delete message '" <<
                        MessageName() <<
                        "', code: " << (uint)msgapierr <<
                        ", errno: " << errno << EOL;
        return FALSE;
    }

//   if (bType == '$') { // Squish base. No need to move to the next message
    PrevIsDel = TRUE;
//   }
    CHP = 532;
    return TRUE;
}

// ---------------------------

char * SQUISH::ReadToMem(void)
{
    CHP = 533;
    CHP = 534;
    return NULL;
}

// ---------------------------

char * SQUISH::MessageName(void)
{
    static char Buff[2048];

    CHP = 535;
    sprintf(Buff, "%s#%u(%u)", DirName, tMsgNum, MsgNum);
    CHP = 536;
    return Buff;
}

// ---------------------------

bool SQUISH::WriteFromMem(char * Buff)
{
    CHP  = 537;
    CHP  = 538;
    unused(Buff);
    return FALSE;
}

// ---------------------------

bool SQUISH::ReadMsg(cMSG & m)
{
    HMSG fh;
    XMSG rm;
    char * Ctrl;
    char * Body;
    int CtrlLen;
    int BodyLen;
    char * tmt, * tmt2;

    CHP = 539;
    Log.Level(LOGD) << "MSGAPI::ReadMsg CHP == " << CHP << EOL;
    fh = MsgOpenMsg(Area, MOPEN_READ, MsgNum);
    // if (fh == NULL) fh = SpecialOpen();
    CHP = 540;
    Log.Level(LOGD) << "MSGAPI::ReadMsg CHP == " << CHP << EOL;

    if(fh == NULL)
    {
        Log.Level(LOGD) << "MSGAPI:MsgOpenMsg: Unable to open message '" <<
                        MessageName() <<
                        "', code: " << (uint)msgapierr <<
                        ", errno: " << errno << EOL;
        errno = 0;
        CHP   = 541;
        return FALSE;
    }

    CHP = 542;
    Log.Level(LOGD) << "MSGAPI::ReadMsg CHP == " << CHP << EOL;
    m.Clear();
    CHP = 543;
    Log.Level(LOGD) << "MSGAPI::ReadMsg CHP == " << CHP << EOL;
    CtrlLen = MsgGetCtrlLen(fh);
    CHP = 544;
    Log.Level(LOGD) << "MSGAPI::ReadMsg CHP == " << CHP << EOL;
    BodyLen = MsgGetTextLen(fh);
    CHP = 545;
    Log.Level(LOGD) << "MSGAPI::ReadMsg BodyLen == " << BodyLen << EOL;
    Ctrl = (char *)malloc(CtrlLen + 1);
    CheckMem(Ctrl);
    CHP = 546;
    memset(Ctrl, 0, CtrlLen + 1);
    CHP  = 547;
    Body = (char *)malloc(BodyLen + 1);
    CheckMem(Body);
    CHP = 548;
    memset(Body, 0, BodyLen + 1);
    CHP = 549;

    if(MsgReadMsg(fh, &rm, 0, BodyLen, (byte *)Body, CtrlLen,
                  (byte *)Ctrl) == (unsigned int)-1)
    {
        CHP   = 550;
        errno = 0;
        free(Ctrl);
        free(Body);
        MsgCloseMsg(fh);
        return FALSE;
    }

    Log.Level(LOGD) << "MSGAPI::ReadMsg Body == " << Body << EOL;
    CHP = 551;
    ConvertControlInfo((byte *)Ctrl, &rm.orig, &rm.dest);
    CHP = 552;
    RSTRLCPY(m._FromName, (char *)rm.from, 36);
    RSTRLCPY(m._ToName, (char *)rm.to, 36);
    RSTRLCPY(m._Subject, (char *)rm.subj, 72);
    m._Time = dosftime(rm.date_written);
    //   m._Time = sToTime((char *)rm.__ftsc_date);
    m._FromAddr.Zone(rm.orig.zone);
    m._FromAddr.Net(rm.orig.net);
    m._FromAddr.Node(rm.orig.node);
    m._FromAddr.Point(rm.orig.point);
    m._ToAddr.Zone(rm.dest.zone);
    m._ToAddr.Net(rm.dest.net);
    m._ToAddr.Node(rm.dest.node);
    m._ToAddr.Point(rm.dest.point);

    if(rm.orig.zone == 0 && UseOwnZone)
    {
        m._FromAddr.Zone(FA_ANYMASK);
        m._FromAddr.Zone(GetMyAka(m._FromAddr).Zone());
    }

    if(rm.dest.zone == 0 && UseOwnZone)
    {
        m._ToAddr.Zone(FA_ANYMASK);
        m._ToAddr.Zone(GetMyAka(m._ToAddr).Zone());
    }

    if(m._ToAddr.Net() == 0 && m._ToAddr.Node() == 0)
    {
        m._ToAddr = GetMyAka(m._FromAddr);
    }

    Log.Level(LOGD) << "MSGAPI::ReadMsg FromAddr == " << m._FromAddr << EOL;
    Log.Level(LOGD) << "MSGAPI::ReadMsg ToAddr   == " << m._ToAddr << EOL;
    SetMsgAttr(FirstWord((const unsigned int &)rm.attr), m);

    if(rm.attr & MSGSCANNED)
    {
        m.fScanned = 1;
    }

    if(rm.attr & MSGLOCKED)
    {
        m.fLok = 1;
    }

    m._ReplyTo = rm.replyto;
    CHP = 553;

    tmt = Ctrl;

    while(*tmt != '\0')
    {
        tmt2 = strchr(tmt + 1, '\1');

        if(tmt2 != NULL)
        {
            *tmt2 = '\0';
        }

        m.AddKludge((const char * &)tmt);

        if(tmt2 != NULL)
        {
            *tmt2 = '\1';
        }
        else
        {
            break;
        }
    }
    CHP = 554;
    tmt = Body;
    m.ParseMem(tmt);
    CHP = 555;
    MsgCloseMsg(fh);
    CHP = 556;
    free(Ctrl);
    free(Body);
    CHP = 557;
    return TRUE;
} // ReadMsg

// ---------------------------

bool SQUISH::WriteOneMsg(unsigned int Num, cMSG & m)
{
    HMSG fh;
    char * Ctrl;
    int CtrlLen;
    char * Body;
    int BodyLen;
    XMSG rm;
    char * tmt, * tmt2;

    CHP = 558;
    fh  = MsgOpenMsg(Area, MOPEN_CREATE, Num);
    CHP = 559;

    if(fh == NULL)
    {
        CHP = 560;
        return FALSE;
    }

    CHP = 560;
    memset(&rm, 0, sizeof(XMSG));
    RSTRLCPY((char *)rm.from, m._FromName, 36);
    RSTRLCPY((char *)rm.to, m._ToName, 36);
    RSTRLCPY((char *)rm.subj, m._Subject, 72);
    RSTRLCPY((char *)rm.__ftsc_date, FromTime(m._Time), 20);
    CHP = 561;
    dosttime(rm.date_written, m._Time);
    dosttime(rm.date_arrived, time(NULL));
    rm.orig.zone  = (unsigned short)(m._FromAddr.Zone());
    rm.orig.net   = (unsigned short)(m._FromAddr.Net());
    rm.orig.node  = (unsigned short)(m._FromAddr.Node());
    rm.orig.point = (unsigned short)(m._FromAddr.Point());
    rm.dest.zone  = (unsigned short)(m._ToAddr.Zone());
    rm.dest.net   = (unsigned short)(m._ToAddr.Net());
    rm.dest.node  = (unsigned short)(m._ToAddr.Node());
    rm.dest.point = (unsigned short)(m._ToAddr.Point());
    unsigned short attr;
    SetMsgAttr(m, (unsigned short &)attr);
    rm.attr = (unsigned long)attr;

    if(m.fScanned)
    {
        rm.attr |= MSGSCANNED;
    }

    if(m.fLok)
    {
        rm.attr |= MSGLOCKED;
    }

    rm.replyto = m._ReplyTo;
    CHP = 561;

    Ctrl = NULL;
    CHP  = 562;
    m.Normalise();
    PrepKluChain(Ctrl, m, TRUE);
    CHP = 563;
    tmt = tmt2 = Ctrl;

    if(Ctrl != NULL)
    {
        CHP = 564;

        do
        {
            if(*tmt2 == '\r')
            {
                tmt2++;
            }

            *tmt = *tmt2;
            tmt++;
            tmt2++;
        }
        while(*(tmt - 1) != '\0');
        CtrlLen = (int)strlen(Ctrl);
    }
    else
    {
        CHP = 565;
        CtrlLen = 0;
    }

    Body = NULL;
    CHP  = 566;

    if(!m.fEmpty && m.Body() != NULL)
    {
        char c;
        CHP  = 567;
        Body = strdup(m.Body());
        CheckMem(Body);
        CHP = 568;

        if((c = Body[strlen(Body) - 1]) != '\r' && c != '\n')
        {
            CHP = 569;
            Log.Level(LOGD) << "MSGAPI::WriteOneMsg: last char == '" <<
                            (int)c << "'(" << c << ") " << EOL;
            Log.Level(LOGD) << "MSGAPI::WriteOneMsg: Append newline. " << EOL;
            AddKluToChain(Body, "\0", NULL);
            CHP = 570;
        }
    }

    CHP = 571;
    CHP = 572;
    PrepKluChain(Body, m, FALSE);

    if(Body != NULL)
    {
        CHP = 578;
        BodyLen = (int)strlen(Body);
    }
    else
    {
        CHP = 579;
        BodyLen = 0;
    }

    CHP = 580;
    Log.Level(LOGD) << "BodyLen: " << BodyLen << EOL;

    if(MsgWriteMsg(fh, 0, &rm,
                   (byte *)(Body == NULL ? " " : Body), BodyLen + 1,
                   BodyLen + 1, CtrlLen + 1,
                   (byte *)Ctrl) != 0)
    {
        CHP = 581;

        if(Ctrl != NULL)
        {
            free(Ctrl);
        }

        if(Body != NULL)
        {
            free(Body);
        }

        return FALSE;
    }

    CHP = 582;
    MsgCloseMsg(fh);
    CHP = 583;

// printf("--> '%s'\n",Ctrl);
    if(Ctrl != NULL)
    {
        free(Ctrl);
    }

    CHP = 584;

    if(Body != NULL)
    {
        free(Body);
    }

    CHP = 585;
    return TRUE;
} // WriteOneMsg

// ---------------------------

bool SQUISH::WriteMsg(cMSG & m)
{
    return WriteOneMsg(MsgNum, m);
}

// ---------------------------

bool SQUISH::WriteNewMsg(cMSG & m)
{
    int Num;

    Num = 0;
    return WriteOneMsg(Num, m);
}

// ---------------------------

void SQUISH::Print(void)
{
#ifdef _DEBUG
    printf("---------------- MSGASMSG -------------------\n");

    if(DirName != NULL)
    {
        printf("Directory == '%s'\n", DirName);
    }

    printf("Current Msg number == '%u'\n", tMsgNum);
#endif
}
