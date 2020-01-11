/*
 *  RNtrack - FTN message tracker/router
 *
 *  scandir.hpp - ScanDir class
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

#ifndef _SCANDIR_HPP_
#define _SCANDIR_HPP_

#include "a_list.hpp"
#include "utils.hpp"
#include "fidoaddr.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "outbound.hpp"
#include "mytypes.hpp"
#include "parsetpl.hpp"
#include "tmstamp.hpp"
#include "mask.hpp"
#include "filebox.hpp"

typedef enum
{
    ACT_ERROR, ACT_MOVE, ACT_COPY, ACT_DELETE, ACT_REWRITE, ACT_NEWMSG,
    ACT_IGNORE, ACT_DISPLAY, ACT_ROUTE, ACT_FLAG, ACT_WRITEFILE, ACT_CALL,
    ACT_DELETEATTACH, ACT_CHANGEPATH, ACT_MOVEATTACH, ACT_SPLIT, ACT_ADDFILE,
    ACT_ADDNOTE, ACT_DELFILE, ACT_POLL, ACT_COPYATTACH, ACT_RECODE, ACT_SCRIPT,
    ACT_ROUTEFBOX, ACT_TOLOWERPATH, ACT_TOUPPERPATH, ACT_COPYATTACHFBOX,
    ACT_MOVEATTACHFBOX, ACT_ROUTEHUB, ACT_ADDKLUDGE
} tAct;

class Action
{
public:
    IndBiList<tTimes> _Times;
    FA _f;
    tAct _Act;
    char * _TplName;
    PKTMode _Flav;
    Template * _Tpl;
    char * _OutDir;
    MSGBASE * _Base;
    Mask * _Mask;
    int _Lines;
    ScanDir * sd;
    ScanDir * Before;
    ScanDir * After;
    Action();
    ~Action();
    void Print(void);
    bool Do(MSGBASE & b, cMSG & m);
};

class DoList
{
    IndBiList<Mask> Masks;
    IndBiList<Action> Actions;
public:
    DoList();
    ~DoList();
    void AddAction(Action & Act);
    void AddMask(Mask & Msk);
    void Print(void);
    int Do(MSGBASE & b, cMSG & m);
    MaskType InMask(cMSG & m);
};

class ScanDir
{
public:
    IndBiList<DoList> _DoLists;
    IndBiList<tTimes> _Times;
    MSGBASE * _Base;
    int _Renumber;
    int _Unpack;
    int _Fresh;
    uint _MaxAge;
    uint _MaxAttachSize;
    uint _MaxMsgSize;
    uint _MaxPktSize;
    char * _LoopStr;
    char * _FlagFile;
    char * _FileInbound;
    char * _ScriptBefore;
    char * _ScriptAfter;
    ScanDir();
    ~ScanDir();
    void SetBase(MSGBASE * B)
    {
        _Base = B;
    }
    MSGBASE * Base(void)
    {
        return _Base;
    }
    void Print(void);
    int Do(void);
    int DoWithRoute(MSGBASE & b, cMSG & m);
    bool Execute(MSGBASE & b, cMSG & m);
    int Flagged(void);

    inline uint MaxAge(void)
    {
        if(_MaxAge == 0)
        {
            return ::MaxAge;
        }
        else
        {
            return _MaxAge;
        }
    }
    inline uint MaxAttachSize(void)
    {
        if(_MaxAttachSize == 0)
        {
            return ::MaxAttachSize;
        }
        else
        {
            return _MaxAttachSize;
        }
    }
    inline uint MaxMsgSize(void)
    {
        if(_MaxMsgSize == 0)
        {
            return ::MaxMsgSize;
        }
        else
        {
            return _MaxMsgSize;
        }
    }
    inline uint MaxPktSize(void)
    {
        if(_MaxPktSize == 0)
        {
            return ::MaxPktSize;
        }
        else
        {
            return _MaxPktSize;
        }
    }
    inline char * LoopStr(void)
    {
        if(_LoopStr == NULL)
        {
            return ::LoopStr;
        }
        else
        {
            return _LoopStr;
        }
    }
    inline char * FileInbound(void)
    {
        if(_FileInbound == NULL)
        {
            return ::FileInbound;
        }
        else
        {
            return _FileInbound;
        }
    }
};

extern IndBiList<ScanDir> ScanDirs;

int AddScanDir(void);
void PrintScanDirs(void);
void DoScanDirs(void);
int AddAction(void);

#endif

