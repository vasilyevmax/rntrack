/*
 *  RNtrack - FTN message tracker/router
 *
 *  mask.cpp - Work with masks (Mask, BodyMask, KludgeMask, ScriptMask...)
 *  Check points 23*
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
#ifdef HAVE_CONFIG_H
    #include "aconfig.h"
#endif

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>

#include "constant.hpp"
#include "mask.hpp"
#include "vars.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "msg.hpp"
#include "age.hpp"
#include "scandir.hpp"
#include "attach.hpp"
#include "aka.hpp"
#include "wildmat.hpp"
#include "script.hpp"

/*--------------------------------------------------------------------*/
/*                         Common functions                           */
/*                         CHP = 231*                                 */
/*--------------------------------------------------------------------*/

static int SoftCmp(const char * Str, char * Mask)
{
// compare string with mask
    int NotFlag;
    int rc;
    char * Str1;
    char * Mask1, * m;

    CHP = 23100;
    NotFlag = FALSE;

    if(strcmp(Mask, "*") == 0)
    {
        return TRUE;
    }

    if(Str == NULL)
    {
        return FALSE;
    }

    Str1 = strdup(Str);
    nls_strupr(Str1);
    Mask1 = strdup(Mask);
    nls_strupr(Mask1);
    m = Mask1;

    if(*Mask1 == '!')
    {
        NotFlag = TRUE;
        Mask1++;
    }

    if(*Mask1 == '~')
    {
        Mask1++;
        rc = (strstr(Str1, Mask1) != NULL);
//printf("-----1>Str == '%s' Mask == '%s' rc == %d\n",Str1,Mask1,rc);
        free(Str1);
        free(m);
        return NotFlag != rc;
    }
    else
    {
        rc = (wildmat(Str1, Mask1) != 0);
//  printf("-----2>Str == '%s' Mask == '%s' rc == %d\n",Str1,Mask1,rc);
        free(Str1);
        free(m);
        return NotFlag != rc;
    }
} // SoftCmp

static int SoftKluCmp(cMSG & m, char * StrName, char * StrBody)
{
// compare message kludges with mask
    IndBiList<Kludge>::ElemPtr Klu;
    int rc;
    int Comp;

    CHP = 23101;
    rc  = 0;

    Klu = m._Klu.GetFirst();
    CHP = 23102;

    while(Klu != NULL)
    {
        CHP  = 23103;
        Comp = FALSE;

        if(StrName == NULL)
        {
            CHP = 23104;

            if(Klu->Name() == NULL || strlen(Klu->Name()) == 0)
            {
                Comp = TRUE;
            }
        }
        else
        {
            CHP = 23105;

            if(SoftCmp(Klu->Name(), StrName))
            {
                Comp = TRUE;
            }
        }

        CHP = 23106;

        if(Comp)
        {
            CHP = 23107;

            if(StrBody == NULL)
            {
                CHP = 23108;

                if(Klu->Body() == NULL || strlen(Klu->Body()) == 0)
                {
                    rc++;
                }
            }
            else
            {
                CHP = 23109;

                if(SoftCmp((const char *)Klu->Body(), StrBody))
                {
                    rc++;
                }
            }

            CHP = 23110;
        }

        CHP = 23111;
        Klu++;
    }


    CHP = 23122;
    return rc;
} // SoftKluCmp

int EquFA(FA const & m, FA const & f)
{
    bool NotFlag;

    CHP = 23123;
    NotFlag = FALSE;

    if(m.Zone() & FA_NOTMASK)
    {
        NotFlag = TRUE;
    }

    if(m.Zone() & FA_OURMASK)
    {
        return IsMyAka(f) != (int)NotFlag;
    }

    if(m.Point() & FA_SUBMASK)
    {
        return Ndl.InSubHubs(f, m) != NotFlag;
    }

    if(m.Zone() & FA_LSTMASK)
    {
        return (Ndl.ExistInNodelist(f) != (unsigned int)-1) != NotFlag;
    }

    if(m.Zone() & FA_PVTMASK)
    {
        return ((Ndl.GetFlags(f) & A_MASK) == A_PVT) != NotFlag;
    }

    if(m.Zone() & FA_HOLDMASK)
    {
        return ((Ndl.GetFlags(f) & A_MASK) == A_HOLD) != NotFlag;
    }

    if(m.Zone() & FA_DOWNMASK)
    {
        return ((Ndl.GetFlags(f) & A_MASK) == A_DOWN) != NotFlag;
    }

    if(m.Zone() & FA_HUBMASK)
    {
        return ((Ndl.GetFlags(f) & A_MASK) == A_HUB) != NotFlag;
    }

    return f == m;
} // EquFA

/*--------------------------------------------------------------------*/
/*                         Classes                                    */
/*--------------------------------------------------------------------*/


/*--------------------------------------------------------------------*/
/*                         Mask class                                 */
/*--------------------------------------------------------------------*/

Mask::~Mask() {}

void Mask::Print(void) const
{
    switch(_Type)
    {
    case MASK_ADD:
        Log << "+";
        break;

    case MASK_SKIP:
        Log << "*";
        break;

    case MASK_NORMAL:
        break;

    case MASK_ERROR:
        Log << "--==(InternalError)==--";
        break;
    }
}

/*--------------------------------------------------------------------*/
/*                         BodyMask class                             */
/*                         CHP = 230*                                 */
/*--------------------------------------------------------------------*/

BodyMask::BodyMask()
{
    CHP    = 23000;
    _Body  = NULL;
    _Type  = MASK_ERROR;
    _Lines = 0;
    _Bytes = 0;
    sd     = NULL;
}

BodyMask::~BodyMask()
{
    CHP = 23001;

    if(_Body != NULL)
    {
        free(_Body);
    }

    _Body  = NULL;
    _Type  = MASK_ERROR;
    _Lines = 0;
    _Bytes = 0;
    sd     = NULL;
}

void BodyMask::Print(void) const
{
    Mask::Print();
    Log << "BodyMask: \"" << _Body << "\" ";

    if(_Lines != (uint) - 1)
    {
        if((_Lines & 0x08000000) != 0)
        {
            Log << "!";
        }

        Log << (_Lines & 0x00ffffff);
    }
    else
    {
        Log << "*";
    }

    Log << " ";

    if(_Bytes != (uint) - 1)
    {
        if((_Bytes & 0x08000000) != 0)
        {
            Log << "!";
        }

        Log << (_Bytes & 0x00ffffff);
    }
    else
    {
        Log << "*";
    }
} // Print

int BodyMask::operator ==(cMSG & m) const
{
    CHP = 23010;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "Compare message with mask '";
        Print();
        Log.Level(LOGD) << "'" << EOL;
    }

    if(!SoftCmp((const char *)m.Body(), _Body))
    {
        return FALSE;
    }

    if(_Lines != (unsigned int)-1)
    {
        if(_Lines & 0x08000000)
        {
            if(m.Lines() >= (_Lines & 0x07ffffff))
            {
                return FALSE;
            }
        }
        else
        {
            if(m.Lines() < (_Lines & 0x07ffffff))
            {
                return FALSE;
            }
        }
    }

    if(_Bytes != (unsigned int)-1)
    {
        if(_Bytes & 0x08000000)
        {
            if(m.Bytes() >= (_Bytes & 0x07ffffff))
            {
                return FALSE;
            }
        }
        else
        {
            if(m.Bytes() < (_Bytes & 0x07ffffff))
            {
                return FALSE;
            }
        }
    }

    CHP = 23011;
    Log.Level(LOGD) << "Message is equal to mask." << EOL;

    return TRUE;
} // ==

/*--------------------------------------------------------------------*/
/*                         KludgeMask class                           */
/*                         CHP = 232*                                 */
/*--------------------------------------------------------------------*/

KludgeMask::KludgeMask()
{
    CHP = 23200;
    _KludgeName = NULL;
    _KludgeBody = NULL;
    _Type = MASK_ERROR;
    _Times      = 0;
    sd = NULL;
}

KludgeMask::~KludgeMask()
{
    CHP = 23201;

    if(_KludgeName != NULL)
    {
        free(_KludgeName);
    }

    _KludgeName = NULL;

    if(_KludgeBody != NULL)
    {
        free(_KludgeBody);
    }

    _KludgeBody = NULL;
    _Type = MASK_ERROR;
    _Times      = 0;
    sd = NULL;
}

void KludgeMask::Print(void) const
{
    Mask::Print();
    Log << "KludgeMask: \"" << _KludgeName << "\" \"" << _KludgeBody << "\" ";

    if(_Times != (uint) - 1)
    {
        if((_Times & 0x08000000) != 0)
        {
            Log << "!";
        }

        Log << (_Times & 0x00ffffff);
    }
    else
    {
        Log << "*";
    }
}

int KludgeMask::operator ==(cMSG & m) const
{
    uint cLoops;

    CHP = 23210;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "Compare message with mask '";
        Print();
        Log.Level(LOGD) << "'" << EOL;
    }

    if((cLoops = SoftKluCmp(m, _KludgeName, _KludgeBody)) == 0)
    {
        return FALSE;
    }

    Log.Level(LOGD) << "Matches " << cLoops << " times." << EOL;

    if(_Times != (unsigned int)-1)
    {
        if(_Times & 0x08000000)
        {
            if(cLoops >= (_Times & 0x07ffffff))
            {
                return FALSE;
            }
        }
        else
        {
            if(cLoops < (_Times & 0x07ffffff))
            {
                return FALSE;
            }
        }
    }

    CHP = 23211;
    Log.Level(LOGD) << "Message is equal to mask." << EOL;
    return TRUE;
} // ==

/*--------------------------------------------------------------------*/
/*                         NormalMask class                           */
/*                         CHP = 233*                                 */
/*--------------------------------------------------------------------*/

NormalMask::NormalMask()
{
    CHP = 23300;
    _FromName = NULL;
    _ToName   = NULL;
    _Subject  = NULL;
    Loops     = (unsigned int)-1;
    fPrivate  = fCrash      = fReceived    = fSend       = fFileAttach =
                fTransit    = fOrphan      = fKillSend   = fLocal      =
                fHold       = fFileRequest = fRRQ        = fIRR        =
                fARQ        = fFURQ        = fDIR        = fIMM        =
                fCFM        = fTFS         = fKFS        = fEmpty      =
                fMaxAge     = fLoop        = fAttExists  = fEchomail   =
                fScanned    = fMaxAttach   = fMaxMsg     = fLok        =
                fAS         = 0;
    _Type = MASK_ERROR;
    sd    = NULL;
}

NormalMask::~NormalMask()
{
    CHP = 23301;

    if(_FromName != NULL)
    {
        free(_FromName);
    }

    _FromName = NULL;

    if(_ToName != NULL)
    {
        free(_ToName);
    }

    _ToName = NULL;

    if(_Subject != NULL)
    {
        free(_Subject);
    }

    _Subject = NULL;
    _Type    = MASK_ERROR;
    sd = NULL;
}

void NormalMask::Print(void) const
{
    char fa1[40], fa2[40];

    CHP = 23302;
    Mask::Print();
    strcpy(fa1, _FromAddr.ToStr());
    strcpy(fa2, _ToAddr.ToStr());
    Log << "Mask: \"" << _FromName << "\" " << fa1 <<
                " \"" << _ToName << "\" " << fa2 <<
                " \"" << _Subject << '"';
    fa1[0] = '\0';

    if(fMaxAge == 1)
    {
        strcat(fa1, "+g");
    }

    if(fMaxAge == 2)
    {
        strcat(fa1, "-g");
    }

    if(fAttExists == 1)
    {
        strcat(fa1, "+x");
    }

    if(fAttExists == 2)
    {
        strcat(fa1, "-x");
    }

    if(fPrivate == 1)
    {
        strcat(fa1, "+p");
    }

    if(fPrivate == 2)
    {
        strcat(fa1, "-p");
    }

    if(fCrash == 1)
    {
        strcat(fa1, "+c");
    }

    if(fCrash == 2)
    {
        strcat(fa1, "-c");
    }

    if(fReceived == 1)
    {
        strcat(fa1, "+r");
    }

    if(fReceived == 2)
    {
        strcat(fa1, "-r");
    }

    if(fSend == 1)
    {
        strcat(fa1, "+s");
    }

    if(fSend == 2)
    {
        strcat(fa1, "-s");
    }

    if(fFileAttach == 1)
    {
        strcat(fa1, "+a");
    }

    if(fFileAttach == 2)
    {
        strcat(fa1, "-a");
    }

    if(fTransit == 1)
    {
        strcat(fa1, "+i");
    }

    if(fTransit == 2)
    {
        strcat(fa1, "-i");
    }

    if(fOrphan == 1)
    {
        strcat(fa1, "+o");
    }

    if(fOrphan == 2)
    {
        strcat(fa1, "-o");
    }

    if(fKillSend == 1)
    {
        strcat(fa1, "+k");
    }

    if(fKillSend == 2)
    {
        strcat(fa1, "-k");
    }

    if(fLocal == 1)
    {
        strcat(fa1, "+l");
    }

    if(fLocal == 2)
    {
        strcat(fa1, "-l");
    }

    if(fHold == 1)
    {
        strcat(fa1, "+h");
    }

    if(fHold == 2)
    {
        strcat(fa1, "-h");
    }

    if(fFileRequest == 1)
    {
        strcat(fa1, "+f");
    }

    if(fFileRequest == 2)
    {
        strcat(fa1, "-f");
    }

    if(fRRQ == 1)
    {
        strcat(fa1, "+q");
    }

    if(fRRQ == 2)
    {
        strcat(fa1, "-q");
    }

    if(fIRR == 1)
    {
        strcat(fa1, "+y");
    }

    if(fIRR == 2)
    {
        strcat(fa1, "-y");
    }

    if(fARQ == 1)
    {
        strcat(fa1, "+b");
    }

    if(fARQ == 2)
    {
        strcat(fa1, "-b");
    }

    if(fFURQ == 1)
    {
        strcat(fa1, "+u");
    }

    if(fFURQ == 2)
    {
        strcat(fa1, "-u");
    }

    if(fDIR == 1)
    {
        strcat(fa1, "+d");
    }

    if(fDIR == 2)
    {
        strcat(fa1, "-d");
    }

    if(fIMM == 1)
    {
        strcat(fa1, "+m");
    }

    if(fIMM == 2)
    {
        strcat(fa1, "-m");
    }

    if(fEmpty == 1)
    {
        strcat(fa1, "+e");
    }

    if(fEmpty == 2)
    {
        strcat(fa1, "-e");
    }

    if(fTFS == 1)
    {
        strcat(fa1, "+t");
    }

    if(fTFS == 2)
    {
        strcat(fa1, "-t");
    }

    if(fKFS == 1)
    {
        strcat(fa1, "+j");
    }

    if(fKFS == 2)
    {
        strcat(fa1, "-j");
    }

    if(fCFM == 1)
    {
        strcat(fa1, "+n");
    }

    if(fCFM == 2)
    {
        strcat(fa1, "-n");
    }

    if(fEchomail == 1)
    {
        strcat(fa1, "+E");
    }

    if(fEchomail == 2)
    {
        strcat(fa1, "-E");
    }

    if(fMaxAttach == 1)
    {
        strcat(fa1, "+A");
    }

    if(fMaxAttach == 2)
    {
        strcat(fa1, "-A");
    }

    if(fMaxMsg == 1)
    {
        strcat(fa1, "+M");
    }

    if(fMaxMsg == 2)
    {
        strcat(fa1, "-M");
    }

    if(fScanned == 1)
    {
        strcat(fa1, "+v");
    }

    if(fScanned == 2)
    {
        strcat(fa1, "-v");
    }

    if(fLok == 1)
    {
        strcat(fa1, "+L");
    }

    if(fLok == 2)
    {
        strcat(fa1, "-L");
    }

    if(fAS == 1)
    {
        strcat(fa1, "+S");
    }

    if(fAS == 2)
    {
        strcat(fa1, "-S");
    }

    if(fLoop != 0)
    {
        if(fLoop == 1)
        {
            strcat(fa1, "+");
        }

        if(fLoop == 2)
        {
            strcat(fa1, "-");
        }

        sprintf(fa2, "%d", Loops);
        strcat(fa1, fa2);
    }

    if(fa1[0] == '\0')
    {
        strcat(fa1, "*");
    }

    Log << " " << fa1;
} // Print

int NormalMask::operator ==(cMSG & m) const
{
    uint cMaxAge;
    uint cLoops;
    uint cMaxAttachSize;
    uint cMaxMsgSize;
    char * tmt2;

    CHP = 23310;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "Compare message with mask '";
        Print();
        Log.Level(LOGD) << "'" << EOL;
    }

    if(!EquFA(_ToAddr, m._ToAddr))
    {
        return FALSE;
    }

    if(!EquFA(_FromAddr, m._FromAddr))
    {
        return FALSE;
    }

    if(!SoftCmp((const char *)m._FromName, _FromName))
    {
        return FALSE;
    }

    if(!SoftCmp((const char *)m._ToName, _ToName))
    {
        return FALSE;
    }

    if(!SoftCmp((const char *)m._Subject, _Subject))
    {
        return FALSE;
    }

    if((fPrivate - m.fPrivate) == 1)
    {
        return FALSE;
    }

    if((fCrash - m.fCrash) == 1)
    {
        return FALSE;
    }

    if((fReceived - m.fReceived) == 1)
    {
        return FALSE;
    }

    if((fSend - m.fSend) == 1)
    {
        return FALSE;
    }

    if((fFileAttach - m.fFileAttach) == 1)
    {
        return FALSE;
    }

    if((fTransit - m.fTransit) == 1)
    {
        return FALSE;
    }

    if((fOrphan - m.fOrphan) == 1)
    {
        return FALSE;
    }

    if((fKillSend - m.fKillSend) == 1)
    {
        return FALSE;
    }

    if((fLocal - m.fLocal) == 1)
    {
        return FALSE;
    }

    if((fHold - m.fHold) == 1)
    {
        return FALSE;
    }

    if((fFileRequest - m.fFileRequest) == 1)
    {
        return FALSE;
    }

    if((fRRQ - m.fRRQ) == 1)
    {
        return FALSE;
    }

    if((fIRR - m.fIRR) == 1)
    {
        return FALSE;
    }

    if((fARQ - m.fARQ) == 1)
    {
        return FALSE;
    }

    if((fFURQ - m.fFURQ) == 1)
    {
        return FALSE;
    }

    if((fDIR - m.fDIR) == 1)
    {
        return FALSE;
    }

    if((fIMM - m.fIMM) == 1)
    {
        return FALSE;
    }

    if((fCFM - m.fCFM) == 1)
    {
        return FALSE;
    }

    if((fTFS - m.fTFS) == 1)
    {
        return FALSE;
    }

    if((fKFS - m.fKFS) == 1)
    {
        return FALSE;
    }

    if((fEchomail - m.fEchomail) == 1)
    {
        return FALSE;
    }

    if((fScanned - m.fScanned) == 1)
    {
        return FALSE;
    }

    if((fLok - m.fLok) == 1)
    {
        return FALSE;
    }

    if((fAS - m.fAS) == 1)
    {
        return FALSE;
    }

    if((fEmpty - m.fEmpty) == 1)
    {
        return FALSE;
    }

    if(fLoop != 0)
    {
        cLoops = m.LoopCount(sd->LoopStr());

        if(fLoop == 1 && (cLoops < Loops))
        {
            return FALSE;
        }

        if(fLoop == 2 && (cLoops >= Loops))
        {
            return FALSE;
        }
    }

    cMaxAge = sd->MaxAge();

    if(fMaxAge == 1 && !AgeIsOver(m._Time, cMaxAge))
    {
        return FALSE;
    }

    if(fMaxAge == 2 && AgeIsOver(m._Time, cMaxAge))
    {
        return FALSE;
    }

    if(fAttExists != 0 || fMaxAttach != 0)
    {
        if(!m.fFileAttach)
        {
            return FALSE;
        }

        tmt2 = FileInbound;

        if(sd->_FileInbound != NULL)
        {
            FileInbound = sd->_FileInbound;
        }

        if(fAttExists == 1 && !AttachExists(m))
        {
            FileInbound = tmt2;
            return FALSE;
        }

        if(fAttExists == 2 && AttachExists(m))
        {
            FileInbound = tmt2;
            return FALSE;
        }

        cMaxAttachSize = m.AttachSize();
        FileInbound    = tmt2;

        if(fMaxAttach == 1 && (cMaxAttachSize <= sd->MaxAttachSize()))
        {
            return FALSE;
        }

        if(fMaxAttach == 2 && (cMaxAttachSize > sd->MaxAttachSize()))
        {
            return FALSE;
        }
    }

    CHP = 23311;
    cMaxMsgSize = m.Bytes();

    if(fMaxMsg == 1 && (cMaxMsgSize <= sd->MaxMsgSize()))
    {
        return FALSE;
    }

    if(fMaxMsg == 2 && (cMaxMsgSize > sd->MaxMsgSize()))
    {
        return FALSE;
    }

    CHP = 23312;
    Log.Level(LOGD) << "Message is equal to mask." << EOL;
    return TRUE;
} // ==

/*--------------------------------------------------------------------*/
/*                         ScriptMask class                           */
/*                         CHP = 234*                                 */
/*--------------------------------------------------------------------*/

ScriptMask::ScriptMask()
{
    CHP = 23400;
    _ScriptName = NULL;
    _Type = MASK_ERROR;
    sd    = NULL;
}

ScriptMask::~ScriptMask()
{
    CHP = 23401;

    if(_ScriptName != NULL)
    {
        free(_ScriptName);
    }

    _ScriptName = NULL;
    _Type = MASK_ERROR;
    sd    = NULL;
}

void ScriptMask::Print(void) const
{
    Mask::Print();
    Log << "ScriptMask: \"" << _ScriptName << "\"";
}

int ScriptMask::operator ==(cMSG & m) const
{
    m   = m;
    CHP = 23410;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "Compare message with mask '";
        Print();
        Log.Level(LOGD) << "'" << EOL;
    }

    CHP = 23411;

    switch(DoSomeWordRc(_ScriptName))
    {
    case SS_OK:
        Log.Level(LOGD) << "Message is equal to mask." << EOL;
        return TRUE;

    case SS_NOTDEF:
    case SS_FALSE:
    case SS_ERROR:
    default:
        Log.Level(LOGD) << "Message is not equal to mask." << EOL;
        return FALSE;
    }
} // ==
