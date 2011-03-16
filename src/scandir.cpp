/*
 *  RNtrack - FTN message tracker/router
 *
 *  scandir.cpp - ScanDir class
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

#ifndef __GNUC__
  #include <io.h>
  #include <direct.h>
#else
  #include <unistd.h>
  #include <sys/types.h>
  #include <dirent.h>
  #include <sys/stat.h>
  #include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "string.hpp"
#include <assert.h>
#include <errno.h>
#include <ctype.h>

#include "constant.hpp"
#include "vars.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "age.hpp"
#include "scandir.hpp"
#include "attach.hpp"
#include "aka.hpp"
#include "wildmat.hpp"
#include "script.hpp"
#include <smapi/msgapi.h>
#include <smapi/progprot.h>

// ---------------------------------------------------------
// ---------------------------------------------------------

Action::Action()
{
    _Act = ACT_ERROR;
    _TplName = NULL;
    _OutDir  = NULL;
    _Base    = NULL;
    _Mask    = NULL;
    _Tpl = NULL;
    _Times.Clear();
    sd = NULL;
    _f.Clean();
}

// --------------------------------------------------------------------

Action::~Action()
{
    CHP = 1;
    _Times.Clear();

    if(_TplName != NULL)
    {
        free(_TplName);
    }

    if(_OutDir != NULL)
    {
        free(_OutDir);
    }

    if(_Base != NULL)
    {
        delete _Base;
    }

    if(_Mask != NULL)
    {
        delete _Mask;
    }

    if(_Tpl != NULL)
    {
        delete _Tpl;
    }
}

// --------------------------------------------------------------------

#include "scd_do.cpp"

// --------------------------------------------------------------------

void Action::Print(void)
{
    char * tmt2;
    char Buff[1024];

    IndBiList<tTimes>::ElemPtr tmt;

    if(LogLevel < 5)
    {
        return;
    }

    CHP = 22;

    switch(_Act)
    {
        case ACT_ERROR:
            tmt2 = "Error!";
            break;

        case ACT_IGNORE:
            tmt2 = "Ignore";
            break;

        default:
            tmt2 = "Unknown";
            break;
    }
    sprintf(Buff, "Action: %s", tmt2);
    Log.Level(LOGD) << Buff << EOL;
    Log.Level(LOGD) << "--" << EOL;

    if(_Times.IsEmpty())
    {
        Log.Level(LOGD) << "Always";
    }
    else
    {
        for(tmt = _Times.GetFirst(); tmt != NULL; tmt++)
        {
            tmt->Print();
            Log.Level(LOGD) << " ";
        }
    }

    Log.Level(LOGD) << EOL;
    Log.Level(LOGD) << "--" << EOL;
} // Print

// ---------------------------------------------------------
// ---------------------------------------------------------

void DoList::AddAction(Action & a)
{
    CHP = 30;
    Actions.AddToEnd(&a);
}

// ---------------------------------------------------------

void DoList::AddMask(Mask & m)
{
    CHP = 31;
    Masks.AddToEnd(&m);
}

// ---------------------------------------------------------

DoList::DoList()
{
    CHP = 32;
}

// ---------------------------------------------------------

DoList::~DoList()
{
    CHP = 33;
    Actions.Clear();
    Masks.Clear();
}

// ---------------------------------------------------------

int DoList::Do(MSGBASE & b, cMSG & m)
{
    IndBiList<Action>::ElemPtr tmt;

    CHP = 34;

    for(tmt = Actions.GetFirst(); tmt != NULL; tmt++)
    {
        if(InTime(tmt->_Times.GetFirst()))
        {
            tmt->Do(b, m);
/*			if(!tmt->Do(b, m))
			{
				return FALSE;
			} */
        }
    }
    return TRUE;
}

// ---------------------------------------------------------

MaskType DoList::InMask(cMSG & m)
{
    IndBiList<Mask>::ElemPtr tmt;
    int SkipFlag;

    CHP = 35;
    SkipFlag = FALSE;
    tmt = Masks.GetFirst();

    while(tmt != NULL)
    {
        if(*tmt == m)
        {
            SkipFlag = (tmt->_Type == MASK_SKIP ? TRUE : FALSE);
            tmt++;

            while(tmt != NULL && tmt->_Type == MASK_ADD && *tmt == m)
            {
                tmt++;
            }

            if(tmt == NULL || tmt->_Type != MASK_ADD)
            {
                return SkipFlag ? MASK_SKIP : MASK_NORMAL;
            }

            while(tmt != NULL && tmt->_Type == MASK_ADD)
            {
                tmt++;
            }
        }
        else
        {
            tmt++;

            while(tmt != NULL && tmt->_Type == MASK_ADD)
            {
                tmt++;
            }
        }
    }
    return MASK_ERROR;
} // InMask

// ---------------------------------------------------------

void DoList::Print(void)
{
    IndBiList<Mask>::ElemPtr tmt;
    IndBiList<Action>::ElemPtr dtmt;

    if(LogLevel < 5)
    {
        return;
    }

    CHP = 36;

    for(tmt = Masks.GetFirst(); tmt != NULL; tmt++)
    {
        tmt->Print();
        Log.Level(LOGD) << EOL;
    }

    for(dtmt = Actions.GetFirst(); dtmt != NULL; dtmt++)
    {
        dtmt->Print();
    }
}

// ---------------------------------------------------------
// ---------------------------------------------------------

ScanDir::ScanDir()
{
    CHP            = 37;
    _Renumber      = FALSE;
    _Unpack        = FALSE;
    _Fresh         = FALSE;
    _MaxAge        = 0;
    _MaxAttachSize = 0;
    _MaxMsgSize    = 0;
    _MaxPktSize    = 0;
    _LoopStr       = NULL;
    _FlagFile      = NULL;
    _FileInbound   = NULL;
    _ScriptBefore  = NULL;
    _ScriptAfter   = NULL;
    _Base          = NULL;
}

// ---------------------------------------------------------

ScanDir::~ScanDir()
{
    CHP = 38;
    _DoLists.Clear();
    _Times.Clear();

    if(_LoopStr != NULL)
    {
        free(_LoopStr);
        _LoopStr = NULL;
    }

    if(_FileInbound != NULL)
    {
        free(_FileInbound);
        _FileInbound = NULL;
    }

    if(_FlagFile != NULL)
    {
        free(_FlagFile);
        _FlagFile = NULL;
    }

    if(_Base != NULL)
    {
        delete _Base;
        _Base = NULL;
    }

    if(_ScriptBefore != NULL)
    {
        free(_ScriptBefore);
        _ScriptBefore = NULL;
    }

    if(_ScriptAfter != NULL)
    {
        free(_ScriptAfter);
        _ScriptAfter = NULL;
    }
}

// ---------------------------------------------------------

int ScanDir::Flagged(void)
{
    if(_FlagFile == NULL)
    {
        return TRUE;
    }

    if(_FlagFile[0] == '!')
    {
        return access(&_FlagFile[1], F_OK) != 0;
    }
    else
    {
        if(_FlagFile[0] == '#')
        {
            return access(&_FlagFile[1], F_OK) == 0;
        }
        else
        {
            return access(_FlagFile, F_OK) == 0;
        }
    }
}

// ---------------------------------------------------------

// Alwais return TRUE !!! Fix it!
bool ScanDir::Execute(MSGBASE & b, cMSG & m)
{
    IndBiList<DoList>::ElemPtr tmt;
    MaskType tmtm;
    CHP = 67;
    PrepareMsgForScript(m);

    for(tmt = _DoLists.GetFirst(); tmt != NULL; tmt++)
    {
        CHP = 68;

        if((tmtm = tmt->InMask(m)) != MASK_ERROR)
        {
            CHP = 69;
            tmt->Do(b, m);
/*			if(!tmt->Do(b, m))
			{
				CHP = 70;
				return FALSE;
			} */
            CHP = 71;

            if(tmtm != MASK_SKIP)
            {
                break;
            }
        }

        CHP = 72;
    }
    return TRUE;
} // Execute

// ---------------------------------------------------------

int ScanDir::Do(void)
{
    cMSG m;
    MSGBASE * s;

    CHP = 39;

    if(_Base == NULL)
    {
        return TRUE;
    }

    if(_Base->Open() != TRUE)
    {
        return FALSE;
    }

    if(!Flagged())
    {
        Log.Level(LOGN) << "Skip base '" << _Base->BaseName() <<
                           "' by Flag." << EOL;
        _Base->Close();
        return TRUE;
    }

    if(!InTime(_Times.GetFirst()))
    {
        Log.Level(LOGN) << "Skip base '" << _Base->BaseName() <<
                           "' by Time." << EOL;
        _Base->Close();
        return TRUE;
    }

    Log.Level(LOGD) << EOL;
    Log.Level(LOGN) << "Scanning message base " << _Base->BaseName() << EOL;
    Log.Level(LOGD) << "--------------------------------------" << EOL;

    if(_ScriptBefore != NULL)
    {
        switch(DoSomeWordRc(_ScriptBefore))
        {
            case SS_OK: // do nothing, all is OK
            case SS_NOTDEF:
                break;          // the same

            case SS_ERROR:
                _Base->Close();
                Log.Level(LOGE) << "Stop ScanDir: by script '" <<
                                   _ScriptBefore << "' error." << EOL;
                return FALSE;

            case SS_FALSE:
                _Base->Close();
                Log.Level(LOGI) << "Leave RNtrack: by script '" <<
                                   _ScriptBefore << "' return." << EOL;
                return TRUE;

            default:
                break;
        }
    }

    if(_Unpack)
    {
        s = TempMail;
        Log.Level(LOGI) << "Unpack outbound to " << _Base->BaseName() << EOL;
        TempMail = _Base;

        if(!DoRepack())
        {
            Log.Level(LOGE) << "Unable unpack outbound" << EOL;
            TempMail = s;
            _Base->Close();
//          DoSomeWord("ErrorInScandir");
            return FALSE;
        }

        TempMail = s;
    }

    if(!_Base->Rewind())
    {
        Log.Level(LOGD) << "Base is empty." << EOL;
        goto DoneOK;
    }

    CHP = 64;

    if(!_DoLists.IsEmpty())
    {
        do
        {
            Log.Level(LOGD) << EOL;
            Log.Level(LOGD) << "Current message: " << _Base->MessageName() <<
                               EOL;

            if(!_Base->ReadMsg(m))
            {
                if(errno == EACCES)
                {
                    Log.Level(LOGE) << "Message " << _Base->MessageName() <<
                                       " Locked by another process." << EOL;
                    errno = 0;
                }
                else
                {
                    CHP = 65;

                    if(errno == ENOENT)
                    {
                        _Base->Close();
                    }
                    else
                    {
                        DoBadMsg(*_Base);
                        CHP = 66;
                    }
                }
            }
            else
            {
                if(LogLevel >= 5)
                {
                    m.Print();
                }

                if(Execute(*_Base, m) != TRUE)
                {
                    _Base->Close();
                    return FALSE;
                }

                CHP = 73;
            }

            CHP = 74;
        }
        while(_Base->Next());
        Log.Level(LOGD) << "No more messages." << EOL;
    }
    else
    {
        Log.Level(LOGD) << "No masks in scandir." << EOL;
    }

    if(_FlagFile != NULL && _FlagFile[0] == '#')
    {
        unlink(&_FlagFile[1]);
    }

    if(_Renumber)
    {
        Log.Level(LOGI) << "Renumber message base " << _Base->BaseName() <<
                           EOL;

        if(!_Base->Renumber())
        {
            _Base->Close();
            return FALSE;
        }
    }

DoneOK:

    if(_ScriptAfter != NULL)
    {
        switch(DoSomeWordRc(_ScriptAfter))
        {
            case SS_OK: // do nothing, all is OK
            case SS_NOTDEF:
                break;          // the same

            case SS_ERROR:
                _Base->Close();
                Log.Level(LOGE) << "Stop ScanDir: by script '" <<
                                   _ScriptAfter << "' error." << EOL;
                return FALSE;

            case SS_FALSE:
                _Base->Close();
                Log.Level(LOGI) << "Leave ScanDir: by script '" <<
                                   _ScriptAfter << "' return." << EOL;
                return TRUE;

            default:
                break;
        }
    }

    _Base->Close();
    CHP = 75;
    return TRUE;
} // Do

// ---------------------------------------------------------

int ScanDir::DoWithRoute(MSGBASE & b, cMSG & m)
{
    CHP = 390001;

    if(_Base != NULL)
    {
        Log.Level(LOGE) <<
        "Internal error. ScanDir::DoWithRoute _Base != NULL" << EOL;
        return FALSE;
    }

    Log.Level(LOGD) << EOL;
    Log.Level(LOGD) << "----- ScanDir::DoWithRoute -----" << EOL;

    if(!Flagged())
    {
        Log.Level(LOGI) << "Skip this base by flag state." << EOL;
        return TRUE;
    }

    CHP   = 390010;
    _Base = &b;

    if(!_DoLists.IsEmpty())
    {
        Log.Level(LOGD) << EOL;

        if(LogLevel >= 5)
        {
            m.Print();
        }

        CHP = 390020;

        if(Execute(*_Base, m) != TRUE)
        {
            _Base = NULL;
            return FALSE;
        }

        CHP = 390030;
    }
    else
    {
        Log.Level(LOGD) << "No masks in scandir." << EOL;
    }

    _Base = NULL;

    if(_FlagFile != NULL && _FlagFile[0] == '#')
    {
        unlink(&_FlagFile[1]);
    }

    CHP = 390040;
    return TRUE;
} // DoWithRoute

// ---------------------------------------------------------

void ScanDir::Print(void)
{
    IndBiList<tTimes>::ElemPtr tmt;
    IndBiList<DoList>::ElemPtr dtmt;

    if(LogLevel < 5)
    {
        return;
    }

    Log.Level(LOGD) << "------------------------------------" << EOL;
    Log.Level(LOGD) << "ScanDir.Print()" << EOL;
    Log.Level(LOGD) << "Base: '" <<
                       ((_Base != NULL) ? _Base->BaseName() : "--NONE--") << "'" << EOL;
    Log.Level(LOGD) << "Renumber: " << ((_Renumber) ? "YES" : "NO") << EOL;
    Log.Level(LOGD) << "Unpack: " << ((_Unpack) ? "YES" : "NO") << EOL;
    Log.Level(LOGD) << "Fresh: " << ((_Fresh) ? "YES" : "NO") << EOL;
    Log.Level(LOGD) << "MaxAge: " << _MaxAge << EOL;
    Log.Level(LOGD) << "MaxAttachSize: " << _MaxAttachSize << EOL;
    Log.Level(LOGD) << "MaxPktSize: " << _MaxPktSize << EOL;
    Log.Level(LOGD) << "MaxMsgSize: " << _MaxMsgSize << EOL;
    Log.Level(LOGD) << "LoopStr: '" <<
                       ((LoopStr() != NULL) ? LoopStr() : "--NONE--") << 
                       "'" << EOL;
    Log.Level(LOGD) << "FileInbound: '" <<
                       ((_FileInbound != NULL) ? _FileInbound : "--NONE--") << 
                       "'" << EOL;
    Log.Level(LOGD) << "FlagFile: '" <<
                       ((_FlagFile != NULL) ? _FlagFile : "--NONE--") << 
                       "'" << EOL;
    Log.Level(LOGD) << "ScriptBefore: '" <<
                       ((_ScriptBefore != NULL) ? _ScriptBefore : "--NONE--") << 
                       "'" << EOL;
    Log.Level(LOGD) << "ScriptAfter: '" <<
                       ((_ScriptAfter != NULL) ? _ScriptAfter : "--NONE--") << 
                       "'" << EOL;
    Log.Level(LOGD) << "Times: ";

    if(_Times.IsEmpty())
    {
        Log.Level(LOGD) << "Always";
    }
    else
    {
        for(tmt = _Times.GetFirst(); tmt != NULL; tmt++)
        {
            tmt->Print();
            Log.Level(LOGD) << " ";
        }
    }

    Log.Level(LOGD) << EOL;
    Log.Level(LOGD) << "--" << EOL;

    if(_DoLists.IsEmpty())
    {
        Log.Level(LOGD) << "ScanDir without masks and actions" << EOL;
    }
    else
    {
        for(dtmt = _DoLists.GetFirst(); dtmt != NULL; dtmt++)
        {
            dtmt->Print();
        }
    }

    Log.Level(LOGD) << "------------------------------------" << EOL;
} // Print

// ---------------------------------------------------------

IndBiList<ScanDir> ScanDirs;

void PrintScanDirs(void)
{
    IndBiList<ScanDir>::ElemPtr tmt;

    CHP = 41;

    for(tmt = ScanDirs.GetFirst(); tmt != NULL; tmt++)
    {
        tmt->Print();
    }
}

void DoScanDirs(void)
{
    IndBiList<ScanDir>::ElemPtr tmt;

    CHP = 42;

    for(tmt = ScanDirs.GetFirst(); tmt != NULL; tmt++)
    {
        CHP = 43;
        tmt->Do();
        CHP = 44;
    }
}

// --------------------------------------------------------------------
