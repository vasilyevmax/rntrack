/*
 *  RNtrack - FTN message tracker/router
 *
 *  msg.hpp - Work with messages
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

#ifndef _MSG_HPP_
#define _MSG_HPP_

#ifdef HAVE_CONFIG_H
    #include "constant.hpp"
    #undef BYTEORDER
#endif

#ifdef HAVE_TIME_H
    #include <time.h>
#elif HAVE_SYS_TIME_H
    #include <sys/time.h>
#endif

#include "a_list.hpp"
#include "utils.hpp"
#include "fidoaddr.hpp"
#include "mytypes.hpp"

#if 0
    char * FromTime(time_t tmt);
    time_t ToTime(char * txt);

    extern char months[][4];
#endif

class Kludge
{
    char * _Name;            // name of Kludhe;
    char * _Body;            // Body of Kludge

public:

    Kludge()
    {
        _Name = NULL;
        _Body = NULL;
    }
    Kludge(char * N, char * B);
    Kludge(char * Txt);
    void Set(char * N, char * B);
    void Clear(void);

    ~Kludge();
    int operator ==(const Kludge & k) const;

    char * Name(void)
    {
        return _Name;
    }
    char * Body(void)
    {
        return _Body;
    }
    void Recode(char * RecodeTable);
    void Print(void);
    int Save(FILE * fh);
//  friend void Kludges::Add(char * Txt);
};

class cMSG
{
public:

    char * _Body;            // Body of message
    FA _FromAddr;            // From Address
    FA _ToAddr;              // ToAddress
    char _Subject[72];       // Subject of message
    char _FromName[36];      // From name
    char _ToName[36];        // To Name
    IndBiList<Kludge> _Klu;  // Kludges
    time_t _Time;            // Date and time
    unsigned int _Cost;      // Cost
    unsigned int _TimesRead;
    unsigned int _ReplyTo;
    unsigned int _NextReply;
    char _Reserved[8];
    char _AreaName[128];     // Are name for Echomail flag
    char _RoutedVia[128];    // routed via information.

// ----- bit field attributes of message ----

    uint fEchomail    : 1;   // Message is echomail.
    uint fNoZone      : 1;   // Message not have Zone.
    uint fChanged     : 1;   // Message is changed.
    uint fPrivate     : 1;   // Private.
    uint fCrash       : 1;   // Crash.
    uint fReceived    : 1;   // Received
    uint fSend        : 1;   // Send
    uint fFileAttach  : 1;   // File attach
    uint fTransit     : 1;   // Transit
    uint fOrphan      : 1;   // Orphan
    uint fKillSend    : 1;   // Kill/Send
    uint fLocal       : 1;   // Local
    uint fHold        : 1;   // Hold
    uint fFileRequest : 1;   // File Request
    uint fRRQ         : 1;   // RRQ
    uint fIRR         : 1;   // IRR
    uint fARQ         : 1;   // ARQ
    uint fFURQ        : 1;   // FURQ
    uint fDIR         : 1;   // DIR
    uint fIMM         : 1;   // IMM
    uint fCFM         : 1;   // CFM
    uint fEmpty       : 1;   // Empty message (not have Body)
    uint fTFS         : 1;   // TFS
    uint fKFS         : 1;   // KFS
    uint fScanned     : 1;   // Message is scanned (Squish only)
    uint fLok         : 1;   // Message is Locked
    uint fAS          : 1;   // Archive/Sent

    cMSG();
    ~cMSG();
    void SetBody(char * Buff, unsigned int Len);

    char * Body(void)
    {
        return _Body;
    }
    void Body(char * b)
    {
        _Body = b;
    }
    void Clear(void);
    void AddKludge(char * & Txt);
    void AddOurVia(void);
    void DelLastOurVia(void);
    void Print(void);
    void ParseMem(char * Buff);
    char * FlagsToStr(char * str);
    char * SomeFlagsToStr(char * str);
    void Normalise(void);
    unsigned int Lines(void);
    unsigned int Bytes(void);
    unsigned int LoopCount(char * LoopStr);
    unsigned int AttachSize(void);
    void Recode(char * RecodeTable);
    cMSG & operator =(const cMSG & m);
};

unsigned long MsgID(void);
time_t ToTime(char * txt);
char * FromTime(time_t tmt);

#endif
