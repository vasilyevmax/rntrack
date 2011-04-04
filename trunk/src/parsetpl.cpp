/*
 *  RNtrack - FTN message tracker/router
 *
 *  parsetpl.cpp - Work with template files
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
#include <string.h>
#include <ctype.h>
#include "constant.hpp"
#include "help.hpp"
#include "utils.hpp"
#include "vars.hpp"
#include "scandir.hpp"
#include "badmsg.hpp"
#include "aka.hpp"
#include "age.hpp"
#include "parsetpl.hpp"
#include "mytypes.hpp"

#if defined (__sun__) || defined (__OSX__)
    #define strftim strftime
#endif

// --------------------------------------------------------------------
//                         Local function prototypes
// --------------------------------------------------------------------

int SetLogFile(void);
int SetLogLevel(void);
int SetNodelist(void);
int CommentLine(void);
int SetIndexFile(void);
int SetNodelistPath(void);
int SetMyAddr(void);
int SetSysopName(void);
int SetUseOwnZone(void);
int SetForceINTL(void);
int SetLoopStr(void);
int SetNoLogIgnore(void);

// --------------------------------------------------------------------
//                                Local variables
// --------------------------------------------------------------------

static int AddSysop(Template * Tpl);
static int AddMaxAge(Template * Tpl);
static int AddMyAddr(Template * Tpl);
static int AddMsgDate(Template * Tpl);
static int AddMsgAge(Template * Tpl);
static int AddFromName(Template * Tpl);
static int AddToName(Template * Tpl);
static int AddSubject(Template * Tpl);
static int AddFromAddr(Template * Tpl);
static int AddFromZone(Template * Tpl);
static int AddFromNet(Template * Tpl);
static int AddFromNode(Template * Tpl);
static int AddFromPoint(Template * Tpl);
static int AddToAddr(Template * Tpl);
static int AddToZone(Template * Tpl);
static int AddToNet(Template * Tpl);
static int AddToNode(Template * Tpl);
static int AddToPoint(Template * Tpl);
static int AddMsgFlags(Template * Tpl);
static int AddMsgHeader(Template * Tpl);
static int AddDate(Template * Tpl);
static int AddMsgBody(Template * Tpl);
static int AddMsgKludges(Template * Tpl);
static int AddMsgVias(Template * Tpl);
static int AddNodelists(Template * Tpl);
static int AddMsgOrigin(Template * Tpl);
static int AddMsgTearline(Template * Tpl);
static int AddMsgNOrigin(Template * Tpl);
static int AddMsgNTearline(Template * Tpl);
static int AddOrigin(Template * Tpl);
static int AddTearline(Template * Tpl);
static int AddMsgLoops(Template * Tpl);
static int AddMsgAttachSize(Template * Tpl);
static int AddMaxAttachSize(Template * Tpl);
static int AddAreaName(Template * Tpl);
static int AddSize(Template * Tpl);
static int AddLines(Template * Tpl);
static int AddRoutedVia(Template * Tpl);
static int AddMsgId(Template * Tpl);
static int AddMsgReply(Template * Tpl);
static int AddNewMsgId(Template * Tpl);
static int AddProgVersion(Template * Tpl);

#ifdef __unix__
    static int AddFPid(Template * Tpl);
#endif

static int AddInetFromAddr(Template * Tpl);
static int AddInetToAddr(Template * Tpl);

typedef struct
{
    const char * Token;
    int (* Func)(Template * Tpl);
} TplTok;

static TplTok TemplTokens[] =
{
    {"Nodelists", &AddNodelists},
    {"ToName", &AddToName},
    {"FromName", &AddFromName},
    {"Subject", &AddSubject},
    {"MsgHeader", &AddMsgHeader},
    {"MsgKludges", &AddMsgKludges},
    {"MsgVias", &AddMsgVias},
    {"MsgAttr", &AddMsgFlags},
    {"Sysop", &AddSysop},
    {"FromAddr", &AddFromAddr},
    {"FromZone", &AddFromZone},
    {"FromNet", &AddFromNet},
    {"FromNode", &AddFromNode},
    {"FromPoint", &AddFromPoint},
    {"ToAddr", &AddToAddr},
    {"ToZone", &AddToZone},
    {"ToNet", &AddToNet},
    {"ToNode", &AddToNode},
    {"ToPoint", &AddToPoint},
    {"MyAddr", &AddMyAddr},
    {"MsgBody", &AddMsgBody},
    {"MsgDate", &AddMsgDate},
    {"Date", &AddDate},
    {"MsgAge", &AddMsgAge},
//   {"MaxAge",&AddMaxAge}, //fixme
    {"MsgOrigin", &AddMsgOrigin},
    {"MsgTearline", &AddMsgTearline},
    {"MsgNOrigin", &AddMsgNOrigin},
    {"MsgNTearline", &AddMsgNTearline},
    {"MsgAttachSize", &AddMsgAttachSize},
//   {"MaxAttachSize",&AddMaxAttachSize}, //fixme
    {"Origin", &AddOrigin},
    {"Tearline", &AddTearline},
//   {"MsgLoops",&AddMsgLoops}, //fixme
    {"MsgAreaName", &AddAreaName},
    {"MsgSize", &AddSize},
    {"MsgLines", &AddLines},
    {"MsgRoutedVia", &AddRoutedVia},
    {"MsgID", &AddMsgId},
    {"MsgReply", &AddMsgReply},
    {"Version", &AddProgVersion},
#ifdef __unix__
    {"Pid", &AddFPid},
#endif
    {"InetFromAddr", &AddInetFromAddr},
    {"InetToAddr", &AddInetToAddr},
//   {"NewMsgId",&AddNewMsgId},
    {0, 0}
};
// --------------------------------------------------------------------

static int AddNodelists(Template * Tpl)
{
    char Buff[4096];

    CHP = 77001;
    Ndl.Names(Buff);
    CHP = 77002;
    Tpl->AddStr(Buff);
    CHP = 77003;
    return TRUE;
}

static int AddOrigin(Template * Tpl)
{
    CHP = 77004;
    Tpl->AddStr(" * Origin: ");
    CHP = 77005;

    if(Origin != NULL)
    {
        Tpl->AddStr(Origin);
    }

    CHP = 77006;
    Tpl->AddStr(" (");
    Tpl->AddStr(Tpl->To->_FromAddr.ToStr());
    Tpl->AddStr(")");
    CHP = 77007;
    return TRUE;
}

static int AddTearline(Template * Tpl)
{
    CHP = 77008;
    Tpl->AddStr("--- ");
    CHP = 77009;

    if(Tearline == NULL)
    {
        CHP = 77010;
        Tpl->AddStr("RNtrack "ProgVersion);
        CHP = 77011;
    }
    else
    {
        CHP = 77012;
        Tpl->AddStr(Tearline);
        CHP = 77013;
    }

    CHP = 77014;
    return TRUE;
}

static int AddMsgOrigin(Template * Tpl)
{
    IndBiList<Kludge>::ElemPtr Klu;
    CHP = 77015;
    Klu = Tpl->From->_Klu.GetFirst();
    CHP = 77016;

    while(Klu != NULL)
    {
        if(Klu->Name() != NULL)
        {
            if(stricmp(Klu->Name(), " * Origin:") == 0)
            {
                Tpl->AddStr(" + Origin: ");
                Tpl->AddStr(Klu->Body());
                return TRUE;
            }
        }

        Klu++;
    }

    CHP = 77026;
    return TRUE;
}

static int AddMsgTearline(Template * Tpl)
{
    IndBiList<Kludge>::ElemPtr Klu;

    CHP = 77037;
    Klu = Tpl->From->_Klu.GetFirst();

    while(Klu != NULL)
    {
        if(Klu->Name() != NULL)
        {
            if(strcmp(Klu->Name(), "---") == 0)
            {
                Tpl->AddStr("-+-");

                if(Klu->Body() != NULL)
                {
                    Tpl->AddStr(" ");
                    Tpl->AddStr(Klu->Body());
                }

                return TRUE;
            }
        }

        Klu++;
    }

    CHP = 77047;
    return TRUE;
} // AddMsgTearline

static int AddMsgNOrigin(Template * Tpl)
{
    uint i;

    CHP = 77058;
    i   = Tpl->BodySize;
    CHP = 77059;
    AddMsgOrigin(Tpl);
    CHP = 77060;

    if(i == Tpl->BodySize)
    {
        CHP = 77061;
        Tpl->AddStr(" * Origin: Default RNtrack origin. (");
        Tpl->AddStr(Tpl->From->_FromAddr.ToStr());
        Tpl->AddStr(")");
        CHP = 77062;
    }
    else
    {
        CHP = 77063;
        Tpl->Body[i + 1] = '*';
    }

    CHP = 77064;
    return TRUE;
} // AddMsgNOrigin

static int AddMsgNTearline(Template * Tpl)
{
    uint i;

    CHP = 77065;
    i   = Tpl->BodySize;
    CHP = 77066;
    AddMsgTearline(Tpl);
    CHP = 77067;

    if(i == Tpl->BodySize)
    {
        CHP = 77068;
        Tpl->AddStr("--- RNtrack "ProgVersion);
    }
    else
    {
        CHP = 77069;
        Tpl->Body[i + 1] = '-';
    }

    CHP = 77070;
    return TRUE;
}

static int AddSysop(Template * Tpl)
{
    CHP = 77071;
    Tpl->AddStr(SysopName);
    return TRUE;
}

static int AddProgVersion(Template * Tpl)
{
    Tpl->AddStr(ProgVersion);
    return TRUE;
}

#ifdef __unix__
static int AddFPid(Template * Tpl)
{
    Tpl->AddInt((unsigned)getpid());
    return TRUE;
}

#endif

static int AddMaxAge(Template * Tpl)
{
    char Buff[128];

    CHP = 77072;

    if(Tpl->sd->_MaxAge != 0)
    {
        CHP = 77073;
        sprintf(Buff, "%u", Tpl->sd->_MaxAge);
    }
    else if(MaxAge != 0)
    {
        CHP = 77074;
        sprintf(Buff, "%u", MaxAge);
    }
    else
    {
        CHP = 77075;
        strcpy(Buff, "NA");
    }

    CHP = 77076;
    Tpl->AddStr(Buff);
    CHP = 77077;
    return TRUE;
} // AddMaxAge

static int AddMaxAttachSize(Template * Tpl)
{
    char Buff[128];

    CHP = 77078;

    if(Tpl->sd->MaxAttachSize() != 0)
    {
        sprintf(Buff, "%u", Tpl->sd->MaxAttachSize());
    }
    else
    {
        strcpy(Buff, "NA");
    }

    CHP = 77079;
    Tpl->AddStr(Buff);
    CHP = 77080;
    return TRUE;
}

static int AddMsgAttachSize(Template * Tpl)
{
    char Buff[512];

    CHP = 77081;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%d", Tpl->From->AttachSize());
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77082;
    Tpl->AddStr(Buff);
    CHP = 77083;
    return TRUE;
}

static int AddMsgFlags(Template * Tpl)
{
    char Buff[512];

    CHP = 77084;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->FlagsToStr(Buff));
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77085;
    Tpl->AddStr(Buff);
    CHP = 77086;
    return TRUE;
}

static int AddAreaName(Template * Tpl)
{
    char Buff[512];

    CHP = 77087;

    if(Tpl->From != NULL && Tpl->From->fEchomail)
    {
        sprintf(Buff, "%s", Tpl->From->_AreaName);
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77088;
    Tpl->AddStr(Buff);
    CHP = 77089;
    return TRUE;
}

static int AddSize(Template * Tpl)
{
    char Buff[512];
    unsigned int sz;

    CHP = 77700;
    sz  = 0;

    if(Tpl->From != NULL)
    {
        sz = Tpl->From->Bytes();
    }

    sprintf(Buff, "%d", sz);
    CHP = 77701;
    Tpl->AddStr(Buff);
    CHP = 77702;
    return TRUE;
}

static int AddLines(Template * Tpl)
{
    char Buff[512];
    unsigned int sz;

    CHP = 77710;
    sz  = 0;

    if(Tpl->From != NULL)
    {
        sz = Tpl->From->Lines();
    }

    sprintf(Buff, "%d", sz);
    CHP = 77711;
    Tpl->AddStr(Buff);
    CHP = 77712;
    return TRUE;
}

static int AddMyAddr(Template * Tpl)
{
    char Buff[128];
    FA f;

    CHP = 77090;

    if(Tpl->To != NULL)
    {
        f = GetMyAka(Tpl->To->_ToAddr);
        strcpy(Buff, f.ToStr());
    }
    else
    {
        strcpy(Buff, MyAddr.ToStr());
    }

    CHP = 77091;
    Tpl->AddStr(Buff);
    CHP = 77092;
    return TRUE;
}

static int AddMsgDate(Template * Tpl)
{
    char Buff[128];

    CHP = 77093;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", FromTime(Tpl->From->_Time));
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77094;
    Tpl->AddStr(Buff);
    CHP = 77095;
    return TRUE;
}

static int AddDate(Template * Tpl)
{
    char Buff[128];
    time_t t;

    CHP = 77096;
    t   = time(NULL);
#ifdef SYSLOG_LOG_FORMAT
    strftime(Buff, 128, "%b %d %H:%M:%S", localtime(&t));
#else
    strftime(Buff, 128, "%d %b %Y %H:%M:%S", localtime(&t));
#endif
    CHP = 77097;
    Tpl->AddStr(Buff);
    CHP = 77098;
    return TRUE;
}

static int AddMsgAge(Template * Tpl)
{
    char Buff[128];

    CHP = 77099;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%d", AgeIs(Tpl->From->_Time));
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77100;
    Tpl->AddStr(Buff);
    CHP = 77101;
    return TRUE;
}

static int AddMsgLoops(Template * Tpl)
{
    char Buff[128];

    CHP = 77102;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%d", Tpl->From->LoopCount(Tpl->sd->LoopStr()));
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77103;
    Tpl->AddStr(Buff);
    CHP = 77104;
    return TRUE;
}

static int AddFromName(Template * Tpl)
{
    char Buff[128];

    CHP = 77105;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_FromName);
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77106;
    Tpl->AddStr(Buff);
    CHP = 77107;
    return TRUE;
}

static int AddToName(Template * Tpl)
{
    char Buff[128];

    CHP = 77108;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_ToName);
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77109;
    Tpl->AddStr(Buff);
    CHP = 77110;
    return TRUE;
}

static int AddSubject(Template * Tpl)
{
    char Buff[128];

    CHP = 77111;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_Subject);
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77112;
    Tpl->AddStr(Buff);
    CHP = 77113;
    return TRUE;
}

static int AddFromAddr(Template * Tpl)
{
    char Buff[128];

    CHP = 77114;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_FromAddr.ToStr());
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77115;
    Tpl->AddStr(Buff);
    CHP = 77116;
    return TRUE;
}

static int AddFromZone(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_FromAddr.Zone(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddFromNet(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_FromAddr.Net(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddInetFromAddr(Template * Tpl)
{
    char Buff[128];

    Buff[0] = '\0';

    if(Tpl->From != NULL)
    {
        if((0 < Tpl->From->_FromAddr.Point()) &&
           (Tpl->From->_FromAddr.Point() <= 65535))
        {
            sprintf(Buff + strlen(Buff), "p%u.",
                    (unsigned int)Tpl->From->_FromAddr.Point());
        }

        sprintf(Buff + strlen(Buff), "f%u.", 
                (unsigned int)Tpl->From->_FromAddr.Node());
        sprintf(Buff + strlen(Buff), "n%u.", 
                (unsigned int)Tpl->From->_FromAddr.Net());
        sprintf(Buff + strlen(Buff), "z%u", 
                (unsigned int)Tpl->From->_FromAddr.Zone());
        Tpl->AddStr(Buff);
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
} // AddInetFromAddr

static int AddInetToAddr(Template * Tpl)
{
    char Buff[128];

    Buff[0] = '\0';

    if(Tpl->From != NULL)
    {
        if((0 < Tpl->From->_ToAddr.Point()) &&
           (Tpl->From->_ToAddr.Point() <= 65535))
        {
            sprintf(Buff + strlen(
                        Buff), "p%u.",
                    (unsigned int)Tpl->From->_FromAddr.Point());
        }

        sprintf(Buff + strlen(Buff), "f%u.", 
                (unsigned int)Tpl->From->_ToAddr.Node());
        sprintf(Buff + strlen(Buff), "n%u.", 
                (unsigned int)Tpl->From->_ToAddr.Net());
        sprintf(Buff + strlen(Buff), "z%u", 
                (unsigned int)Tpl->From->_ToAddr.Zone());
        Tpl->AddStr(Buff);
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
} // AddInetToAddr

static int AddFromNode(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_FromAddr.Node(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddFromPoint(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        if(Tpl->From->_FromAddr.Point() & FA_NOTDEF)
        {
            Tpl->AddInt(0);
        }
        else
        {
            Tpl->AddStr(fatoa(Tpl->From->_FromAddr.Point(), Buff));
        }
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddToAddr(Template * Tpl)
{
    char Buff[128];

    CHP = 77117;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_ToAddr.ToStr());
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77118;
    Tpl->AddStr(Buff);
    CHP = 77119;
    return TRUE;
}

static int AddToZone(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_ToAddr.Zone(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddToNet(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_ToAddr.Net(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddToNode(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        Tpl->AddStr(fatoa(Tpl->From->_ToAddr.Node(), Buff));
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddToPoint(Template * Tpl)
{
    char Buff[20];

    if(Tpl->From != NULL)
    {
        if(Tpl->From->_ToAddr.Point() & FA_NOTDEF)
        {
            Tpl->AddInt(0);
        }
        else
        {
            Tpl->AddStr(fatoa(Tpl->From->_ToAddr.Point(), Buff));
        }
    }
    else
    {
        Tpl->AddInt(-1);
    }

    return TRUE;
}

static int AddMsgHeader(Template * Tpl)
{
    char Buff[128];

    CHP = 77120;

    if(Tpl->From == NULL)
    {
        strcpy(Buff, "Unknown");
        Tpl->AddStr(Buff);
        return TRUE;
    }

    CHP = 77121;
    Tpl->AddStr("From: ");
    AddFromName(Tpl);
    Tpl->AddStr(" (");
    AddFromAddr(Tpl);
    Tpl->AddStr(")\n");
    Tpl->AddStr("To  : ");
    AddToName(Tpl);
    Tpl->AddStr(" (");
    AddToAddr(Tpl);
    Tpl->AddStr(")\n");
    Tpl->AddStr("Subj: ");
    AddSubject(Tpl);
    Tpl->AddStr("\n");
    Tpl->AddStr("Date: ");
    AddMsgDate(Tpl);
    Tpl->AddStr("\n");
    Tpl->AddStr("Attr: ");
    AddMsgFlags(Tpl);
    CHP = 77129;
    return TRUE;
} // AddMsgHeader

static int AddMsgBody(Template * Tpl)
{
    char Buff[128];
    char * c;
    char LastChr;

    CHP = 77130;

    if(Tpl->From == NULL)
    {
        strcpy(Buff, "Unknown");
        Tpl->AddStr(Buff);
        return TRUE;
    }

    CHP = 77132;
    c   = Tpl->From->_Body;

    if(c == NULL)
    {
        return TRUE;
    }

    CHP = 77134;
// Copy the body of the message and strip 0x0A characters. Fucked shit,
// does anybody besides me read these standards?
    LastChr = '\0';

    while(*c != '\0')
    {
        if(*c == '\r')
        {
            if(LastChr != '\n' && *(c + 1) != '\n')
            {
                Tpl->AddChar('\r');
            }
        }
        else
        {
            Tpl->AddChar(*c);
        }

        LastChr = *c;
        c++;
    }
    CHP = 77136;

//   Tpl->Normalise();
    if(Tpl->BodySize != 0 &&
       (Tpl->Body[Tpl->BodySize - 1] == '\n' ||
        Tpl->Body[Tpl->BodySize - 1] == '\r'))
    {
        (Tpl->BodySize)--;
    }

    return TRUE;
} // AddMsgBody

static void AddInvalidatedKlu(Template * Tpl, Kludge * Klu)
{
    if(Klu->Name() != NULL && strlen(Klu->Name()) != 0)
    {
        if(*Klu->Name() == '\1')
        {
            Tpl->AddChar('@');
            Tpl->AddStr(Klu->Name() + 1);
        }
        else if(stricmp(Klu->Name(), "SEEN-BY:") == 0)
        {
            Tpl->AddStr("SEEN+BY:");
        }
        else if(stricmp(Klu->Name(), "---") == 0)
        {
            Tpl->AddStr("-+-");
        }
        else if(stricmp(Klu->Name(), " * Origin:") == 0)
        {
            Tpl->AddStr("+ Origin:");
        }
        else
        {
            Tpl->AddStr(Klu->Name());
        }
    }

    Tpl->AddChar(' ');

    if(Klu->Body() != NULL && strlen(Klu->Body()) != 0)
    {
        Tpl->AddStr(Klu->Body());
    }
} // AddInvalidatedKlu

static int AddMsgKlu(Template * Tpl, IndBiList<Kludge>::ElemPtr Klu,
                     bool IsKludge)
{
    bool FirstKlu;

    CHP = 77140;
    FirstKlu = TRUE;

    while(Klu != NULL)
    {
        if(Klu->Name() != NULL && strlen(Klu->Name()) != 0)
        {
            if((stricmp(Klu->Name(), "---")        == 0) ||
               (stricmp(Klu->Name(), " * Origin:") == 0))
            {
                Klu++;
                continue;
            }

            if((stricmp(Klu->Name(), "SEEN-BY:")    == 0) ||
               (stricmp(Klu->Name(), "\1VIA")       == 0) ||
               (stricmp(Klu->Name(), "\1Recd")      == 0) ||
               (stricmp(Klu->Name(), "\1Forwarded") == 0) ||
               (stricmp(Klu->Name(), "\1PATH:")     == 0))
            {
                if(IsKludge != TRUE)
                {
                    if(FirstKlu != TRUE)
                    {
                        Tpl->AddChar('\n');
                    }

                    AddInvalidatedKlu(Tpl, Klu);
                    FirstKlu = FALSE;
                }
                else
                {
                    Klu++;
                    continue;
                }
            }
            else
            {
                if(IsKludge == TRUE)
                {
                    if(FirstKlu != TRUE)
                    {
                        Tpl->AddChar('\n');
                    }

                    AddInvalidatedKlu(Tpl, Klu);
                    FirstKlu = FALSE;
                }
                else
                {
                    Klu++;
                    continue;
                }
            }
        }

        Klu++;
    }
    CHP = 77160;
    return TRUE;
} // AddMsgKlu

static int AddMsgKludges(Template * Tpl)
{
    CHP = 77161;
    return AddMsgKlu(Tpl, Tpl->From->_Klu.GetFirst(), TRUE);
}

static int AddMsgVias(Template * Tpl)
{
    CHP = 77161;
    return AddMsgKlu(Tpl, Tpl->From->_Klu.GetFirst(), FALSE);
}

static int AddRoutedVia(Template * Tpl)
{
    char Buff[512];

    CHP = 77163;

    if(Tpl->From != NULL)
    {
        sprintf(Buff, "%s", Tpl->From->_RoutedVia);
    }
    else
    {
        strcpy(Buff, "Unknown");
    }

    CHP = 77164;
    Tpl->AddStr(Buff);
    CHP = 77165;
    return TRUE;
}

static int AddSomeKludge(Template * Tpl, const char * Klud)
{
    IndBiList<Kludge>::ElemPtr Klu;

    CHP = 77166;
    Klu = Tpl->From->_Klu.GetFirst();
    CHP = 77167;

    while(Klu != NULL)
    {
        if(Klu->Name() != NULL)
        {
            if(stricmp(Klu->Name(), Klud) == 0)
            {
                Tpl->AddStr(Klu->Body() != NULL ? Klu->Body() : "Unknown");
                return TRUE;
            }
        }

        Klu++;
    }
    Tpl->AddStr("Unknown");
    CHP = 77169;
    return TRUE;
}

char * StrAsTpl(cMSG & m, char * s)
{
    char * tmt;
    Template * tpl;

    tpl = new Template();
    tpl->SetMsg(m);
    tpl->LastTplLine = strdup(s);
    tpl->ParseOneLine();
    tmt = strdup(tpl->Body);
    delete tpl;
    return tmt;
}

static int AddMsgId(Template * Tpl)
{
    return AddSomeKludge(Tpl, "\1MSGID:");
}

static int AddMsgReply(Template * Tpl)
{
    return AddSomeKludge(Tpl, "\1REPLY:");
}

static int AddNewMsgId(Template * Tpl)
{
    char Buff[50];

    sprintf(Buff, "%08lx", MsgID());
    Tpl->AddStr(Buff);
    return TRUE;
}

// --------------------------------------------------------------------

Template::Template()
{
    CHP = 77170;
    TplName = NULL;
    LastTplLine = NULL;
    fh   = NULL;
    Body = NULL;
    BodySize    = 0;
    MaxBodySize = 0;
    From  = NULL;
    To    = NULL;
    FName = NULL;
}

Template::~Template()
{
    CHP = 77180;

    if(TplName != NULL)
    {
        free(TplName);
    }

    if(LastTplLine != NULL)
    {
        free(LastTplLine);
    }

    if(Body != NULL)
    {
        free(Body);
    }

    if(fh != NULL)
    {
        fclose(fh);
    }

    if(FName != NULL)
    {
        free(FName);
    }
}

bool Template::Set(char * c)
{
    CHP = 77190;

    if(access(c, R_OK) != 0)
    {
        Log.Level(LOGD) << "Template.Set: File '" << c <<
                           "' does not exist or is not readable." << EOL;
        return FALSE;
    }

    TplName = strdup(c);
    return TRUE;
}

// --------------------------------------------------------------------

int Template::GetOneLine(void)
{
    CHP = 77200;

    if(fgets(LastTplLine, MAXCFGLINE, fh) == NULL)
    {
        return FALSE;
    }

    CHP = 77201;
// Strip end of line
//   tmt = strrchr(LastTplLine,'\n');
//   if (tmt != NULL) *tmt = '\0';
//   tmt = strrchr(LastTplLine,'\r');
//   if (tmt != NULL) *tmt = '\0';
    return TRUE;
}

// --------------------------------------------------------------------

void Template::AddStr(const char * c)
{
    CHP = 77202;

    while(*c)
    {
        AddChar(*c);
        c++;
    }
    CHP = 77203;
}

void Template::AddInt(int i)
{
    char Buff[128];

    sprintf(Buff, "%d", i);
    AddStr(Buff);
}

void Template::AddChar(char c)
{
    CHP = 77204;

    if(Body == NULL)
    {
        MaxBodySize = TPLADD;
        Body = (char *)malloc(TPLADD);
        CheckMem(Body);
    }

    CHP = 77206;

    if(BodySize == MaxBodySize)
    {
        MaxBodySize += TPLADD;
        Body = (char *)realloc(Body, MaxBodySize);
        CheckMem(Body);
    }

    CHP = 77208;
    Body[BodySize] = c;

    if(c != '\0')
    {
        BodySize++;
    }

    CHP = 77210;
} // AddChar

int Template::AddTok(char * T)
{
    TplTok * Tok;

    CHP = 77211;
    Tok = TemplTokens;

    while(Tok->Token != 0)
    {
        if(stricmp(Tok->Token, T) == 0)
        {
            return Tok->Func(this);
        }

        Tok++;
    }
    CHP = 77221;

    if(Tok->Token == 0)
    {
        AddChar('@');
        AddStr(T);
    }

    CHP = 77224;
    return TRUE;
} // AddTok

int Template::ParseOneLine(void)
{
// get string from Template file.
// parse @f as template word
    char * tmt, * tmt2;
    char Tok[MAXCFGLINE];

    CHP = 77225;
    tmt = LastTplLine;

    while(*tmt != '\0')
    {
        if(*tmt == '@')
        {
            tmt++;

            if(*tmt == '@')
            {
                AddChar(*tmt++);
                continue;
            }

            tmt2 = Tok;

            while(isalpha((uchar) * tmt))
            {
                *tmt2++ = *tmt++;
            }
            *tmt2 = '\0';

            if(!AddTok(Tok))
            {
                return FALSE;
            }
        }
        else
        {
            AddChar(*tmt++);
        }
    }
    CHP = 77245;
    AddChar('\0');
    CHP = 77246;
    return TRUE;
} // ParseOneLine

// --------------------------------------------------------------------

void Template::Normalise(void)
{
    char * tmt;

    CHP = 77247;
    AddChar('\0');
    CHP = 77248;

// First - replace all \r to \n

    while((tmt = strchr(Body, '\r')) != NULL)
    {
        *tmt = '\n';
    }

    CHP = 77250;
}

// --------------------------------------------------------------------

int Template::Parse(void)
{
    CHP = 77260;

    if(TplName == NULL)
    {
        Log.Level(LOGE) << "Template file not set" << EOL;
        return FALSE;
    }

    CHP = 77264;

    if(access(TplName, R_OK) != 0)
    {
        Log.Level(LOGE) << "Template file '" << TplName <<
                           "' does not exist." << EOL;
        return FALSE;
    }

    CHP = 77268;
    fh  = fopen(TplName, "rt");

    if(fh == 0)
    {
        Log.Level(LOGE) << "Unable to open template file '" << TplName <<
                           "'" << EOL;
        return FALSE;
    }

    CHP = 77272;
    LastTplLine = (char *)malloc(MAXCFGLINE);
    CheckMem(LastTplLine);

    while(GetOneLine())
    {
        if(!ParseOneLine())
        {
            fclose(fh);
            fh = NULL;
            return FALSE;
        }
    }
    CHP = 77276;

    if(!feof(fh))
    {
        Log.Level(LOGE) << "Error reading template file '" << TplName <<
                           "'" << EOL;
        fclose(fh);
        fh = NULL;
        return FALSE;
    }

    CHP = 77280;
    fclose(fh);
    fh  = NULL;
    CHP = 77284;
    Normalise();
    CHP = 77288;
    return TRUE;
} // Parse

// --------------------------------------------------------------------
int Template::Save(char * Name, int Mode)
{
    CHP = 77292;

    if(Mode == 1)
    {
        CHP = 77293;
        fh  = fopen(Name, "w+t");

        if(fh == NULL)
        {
            Log.Level(LOGE) << "Unable to create file '" << Name << "'" << EOL;
            return FALSE;
        }
    }
    else
    {
        CHP = 77297;
        fh  = fopen(Name, "a+t");

        if(fh == NULL)
        {
            Log.Level(LOGE) << "Unable to append to file '" << Name << "'" <<
                               EOL;
            return FALSE;
        }
    }

    CHP = 77301;

    if(fputs(Body, fh) == EOF)
    {
        Log.Level(LOGE) << "Unable to write to file '" << Name << "'" << EOL;
        fclose(fh);
        fh = NULL;
        return FALSE;
    }

    CHP = 77304;
    fclose(fh);
    fh  = NULL;
    CHP = 77308;
    return TRUE;
} // Save

int Template::Save(cMSG & m)
{
    char * tmt;

    CHP = 77312;
    m.SetBody(Body, strlen(Body));
    CHP = 77314;

    while((tmt = strchr(m.Body(), '\n')) != NULL)
    {
        *tmt = '\r';
    }
    CHP = 77316;
    return TRUE;
}

// --------------------------------------------------------------------
void Template::Clean(void)
{
    if(Body != NULL)
    {
        free(Body);
        Body = NULL;
        BodySize    = 0;
        MaxBodySize = 0;
    }
}

// ---------------------------- END --------------------------------------
