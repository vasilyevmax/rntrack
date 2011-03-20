/*
 *  RNtrack - FTN message tracker/router
 *
 *  outbound.hpp - Work with outbound
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

#ifndef _OUTBOUND_HPP_
#define _OUTBOUND_HPP_

#include <stdio.h>
#include "fidoaddr.hpp"
#include "domain.hpp"

#ifdef _AIX_CONV
    #include "aix_conv.hpp"
#endif

#include "vars.hpp"

int SetAddToNullPkt(void);
int SetOutbound(char * tmt);
int SetTrafficLog(char * tmt);
int SetTempMail(char * tmt);
int SetKillRoutedMessages(KillModeT kmode);

typedef enum {F_DIRECT, F_CRASH, F_HOLD, F_NORMAL, F_ATTACH,
              F_IMMEDIATE} PKTMode;

typedef enum {BSY, NULLPKT, PKTERROR, ATTERROR, PKTOK, NEWPKT, BADPKT} PKTrc;

int ReadLoFile(FA & f, PKTMode m);
int SaveLoFile(FA & f, PKTMode m);

class PKT
{
public:
    char * BsyFile;
    FA Addr;
    PKTMode Mode;
    FILE * fh;

    PKT();
    ~PKT();
    int Set(FA & f);
    PKTrc Open(PKTMode m, char * pktFileName);
    PKTrc AddMsg(cMSG & m, PKTMode mod, int Dest);
    PKTrc Poll(PKTMode mod);
    int Clean(void);
    int Bsy(void);
    void DelBsy(void);
};

void LogTraffic(cMSG & m, FA & ToAddr);
int AddToLo(char * Txt);
int DelFromLo(char * Txt);
int InitOutbound(void);
int DoRepack(void);
char * MakeAPktName(char * path);
void AddOutExt(PKTMode m, char * Buff, int outmode);

#endif

