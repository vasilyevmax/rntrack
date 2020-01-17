/*
 *  RNtrack - FTN message tracker/router
 *
 *  msgbase.cpp - Message bases. root class and MSG base format.
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

#include "constant.hpp"
#ifndef __GNUC__
  #include <io.h>
  #include <direct.h>
#else
  #include <sys/types.h>
  #include <dirent.h>
  #include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "compiler.h"
#include "vars.hpp"
#include "log.hpp"
#include "configure.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "msg.hpp"
#include "msgbase.hpp"
#include "sqbase.hpp"
#include "pktbase.hpp"
#include "aka.hpp"
#include "msgapi.h"
#include "progprot.h"

#ifdef _AIX_CONV
  #include "aix_conv.hpp"
#endif

// ---------------------------

typedef struct
{
    char FromName[36];
    char ToName[36];
    char Subject[72];
    char DateTime[20];
    unsigned short int TimesRead;
    unsigned short int DestNode;
    unsigned short int OrigNode;
    unsigned short int Cost;
    unsigned short int OrigNet;
    unsigned short int DestNet;
    char Reserved[8];
    unsigned short int ReplyTo;
    unsigned short int Attr;
    unsigned short int NextReply;
} MsgHeader;

#define H_Private     0x0001
#define H_Crash       0x0002
#define H_Received    0x0004
#define H_Send        0x0008
#define H_FileAttach  0x0010
#define H_Transit     0x0020
#define H_Orphan      0x0040
#define H_KillSend    0x0080
#define H_Local       0x0100
#define H_Hold        0x0200
#define H_NU1         0x0400
#define H_FileRequest 0x0800
#define H_RRQ         0x1000
#define H_IRR         0x2000
#define H_ARQ         0x4000
#define H_FURQ        0x8000


// ---------------------------

void SetMsgAttr(cMSG & m, unsigned short int & Attr)
{
    Attr = 0;

    if(m.fPrivate == 1)
    {
        Attr = Attr | H_Private;
    }

    if(m.fCrash == 1)
    {
        Attr = Attr | H_Crash;
    }

    if(m.fReceived == 1)
    {
        Attr = Attr | H_Received;
    }

    if(m.fSend == 1)
    {
        Attr = Attr | H_Send;
    }

    if(m.fFileAttach == 1)
    {
        Attr = Attr | H_FileAttach;
    }

    if(m.fTransit == 1)
    {
        Attr = Attr | H_Transit;
    }

    if(m.fOrphan == 1)
    {
        Attr = Attr | H_Orphan;
    }

    if(m.fKillSend == 1)
    {
        Attr = Attr | H_KillSend;
    }

    if(m.fLocal == 1)
    {
        Attr = Attr | H_Local;
    }

    if(m.fHold == 1)
    {
        Attr = Attr | H_Hold;
    }

    if(m.fFileRequest == 1)
    {
        Attr = Attr | H_FileRequest;
    }

    if(m.fRRQ == 1)
    {
        Attr = Attr | H_RRQ;
    }

    if(m.fIRR == 1)
    {
        Attr = Attr | H_IRR;
    }

    if(m.fARQ == 1)
    {
        Attr = Attr | H_ARQ;
    }

    if(m.fFURQ == 1)
    {
        Attr = Attr | H_FURQ;
    }
} // SetMsgAttr

void SetMsgAttr(unsigned short int & Attr, cMSG & m)
{
    if(Attr & H_Private)
    {
        m.fPrivate = 1;
    }

    if(Attr & H_Crash)
    {
        m.fCrash = 1;
    }

    if(Attr & H_Received)
    {
        m.fReceived = 1;
    }

    if(Attr & H_Send)
    {
        m.fSend = 1;
    }

    if(Attr & H_FileAttach)
    {
        m.fFileAttach = 1;
    }

    if(Attr & H_Transit)
    {
        m.fTransit = 1;
    }

    if(Attr & H_Orphan)
    {
        m.fOrphan = 1;
    }

    if(Attr & H_KillSend)
    {
        m.fKillSend = 1;
    }

    if(Attr & H_Local)
    {
        m.fLocal = 1;
    }

    if(Attr & H_Hold)
    {
        m.fHold = 1;
    }

    if(Attr & H_FileRequest)
    {
        m.fFileRequest = 1;
    }

    if(Attr & H_RRQ)
    {
        m.fRRQ = 1;
    }

    if(Attr & H_IRR)
    {
        m.fIRR = 1;
    }

    if(Attr & H_ARQ)
    {
        m.fARQ = 1;
    }

    if(Attr & H_FURQ)
    {
        m.fFURQ = 1;
    }
} // SetMsgAttr

// ---------------------------

void AddKluToChain(char * & cl, const char * Kn, const char * Kb)
{
    char * buff;
    int olen;

    buff = (char *)malloc(60000);
    CheckMem(buff);

    if(Kb == NULL)
    {
        sprintf(buff, "%s\r", Kn);
    }
    else if(Kn == NULL)
    {
        sprintf(buff, "%s\r", Kb);
    }
    else
    {
        sprintf(buff, "%s %s\r", Kn, Kb);
    }

    olen = 0;

    if(cl != NULL)
    {
        olen = (int)strlen(cl);
        cl   = (char *)realloc(cl, olen + strlen(buff) + 1);
        CheckMem(cl);
        strcat(cl, buff);
    }
    else
    {
        cl = (char *)realloc(cl, strlen(buff) + 1);
        CheckMem(cl);
        strcpy(cl, buff);
    }

    free(buff);
} // AddKluToChain

void PrepKluChain(char * & Ctrl, cMSG & m, bool IsKludge)
{
    IndBiList<Kludge>::ElemPtr Klu;

    CHP = 201;
    Klu = m._Klu.GetFirst();
    CHP = 205;

    while(Klu != NULL)
    {
        if(Klu->Name() != NULL && strlen(Klu->Name()) != 0)
        {
            if((stricmp(Klu->Name(), "SEEN-BY:")    == 0) ||
               (strcmp(Klu->Name(), "---")          == 0) ||
               (stricmp(Klu->Name(), "\1VIA")       == 0) ||
               (stricmp(Klu->Name(), "\1Recd")      == 0) ||
               (stricmp(Klu->Name(), "\1Forwarded") == 0) ||
               (stricmp(Klu->Name(), " * Origin:")  == 0) ||
               (stricmp(Klu->Name(), "\1PATH:")     == 0))
            {
                if(IsKludge != TRUE)
                {
                    AddKluToChain(Ctrl, Klu->Name(), Klu->Body());
                }
            }
            else
            {
                if(IsKludge == TRUE)
                {
                    AddKluToChain(Ctrl, Klu->Name(), Klu->Body());
                }
            }
        }
        else if(Klu->Body() != NULL)
        {
            if(IsKludge == TRUE)
            {
                AddKluToChain(Ctrl, Klu->Name(), Klu->Body());
            }
        }

        Klu++;
    }
    CHP = 206;
} // PrepKluChain

bool WriteMsgBody(cMSG & m, FILE * fh)
{
    char * Buff;
    unsigned int FSize;
    char * Ctrl;

    CHP  = 203;
    Buff = (char *)malloc(40960);
    CheckMem(Buff);
    CHP = 204;

#ifdef __OS2__
// A very strange situation...
// Without this code the program _strongly_ freezes in OS/2.
//   fprintf(stderr," \b");fflush(stderr);
#endif

    Ctrl = NULL;
    CHP  = 205;
    m.Normalise();
    CHP = 206;
    PrepKluChain(Ctrl, m, TRUE);
    CHP = 207;

    if(Ctrl != NULL)
    {
        if(fwrite(Ctrl, strlen(Ctrl), 1, fh) != 1)
        {
            free(Ctrl);
            free(Buff);
            fclose(fh);
            return FALSE;
        }

        free(Ctrl);
        Ctrl = NULL;
    }

    if(!m.fEmpty)
    {
        FSize = (unsigned int)strlen(m.Body());

        if(fwrite(m.Body(), FSize, 1, fh) != 1)
        {
            free(Buff);
            fclose(fh);
            return FALSE;
        }

        if(*(m.Body() + FSize - 1) != '\r')
        {
            if(fwrite("\r", 1, 1, fh) != 1)
            {
                free(Buff);
                fclose(fh);
                return FALSE;
            }
        }
    }

    CHP = 208;
    PrepKluChain(Ctrl, m, FALSE);

    if(Ctrl != NULL)
    {
        CHP = 20801;

        if(fwrite(Ctrl, strlen(Ctrl), 1, fh) != 1)
        {
            free(Ctrl);
            free(Buff);
            fclose(fh);
            return FALSE;
        }

        free(Ctrl);
        Ctrl = NULL;
    }

    CHP = 209;
    free(Buff);

    CHP = 210;

    if(fwrite("\0", 1, 1, fh) != 1)
    {
        fclose(fh);
        return FALSE;
    }

    CHP = 211;
    return TRUE;
} // WriteMsgBody

// ---------------------------

// ---------------------------

MSGBASE::~MSGBASE(){}

MSGASMSG::MSGASMSG()
{
    CHP     = 215;
    DirName = NULL;
    MsgNum  = 0;
    MaxNum  = 0;
    MsgMask = NULL;
}

MSGASMSG::~MSGASMSG()
{
    CHP = 216;
    Clear();
}

// ---------------------------

void MSGASMSG::AddToMask(unsigned int Num)
{
    if(Num > MaxNum)
    {
        MsgMask = (char *)realloc(MsgMask, Num + 1);
        CheckMem(MsgMask);
        MaxNum++;

        while(MaxNum != Num)
        {
            MsgMask[MaxNum++] = 0;
        }
    }

    MsgMask[Num] = 1;
}

// ---------------------------

void MSGASMSG::Clear(void)
{
    CHP = 217;

    if(DirName != NULL)
    {
        free(DirName);
        DirName = NULL;
    }

    if(MsgMask != NULL)
    {
        free(MsgMask);
        MsgMask = NULL;
    }

    MsgNum = 0;
    MaxNum = 0;
}

// ---------------------------

bool MSGASMSG::Set(char * Dir, int BaseType)
{
    char Buff[1024];

    BaseType++;
    CHP = 218;
    Clear();

    if(!CreateMissingBase && !DirExists(Dir))
    {
        Log.Level(LOGD) << "MSGASMSG.Set: Message base directory '" << Dir <<
                           "' is not exist." << EOL;
        return FALSE;
    }

    DirName = (char *)malloc(strlen(Dir) + 2);
    CheckMem(DirName);
    strcpy(DirName, Dir);

    if(DirName[strlen(DirName) - 1] != PATHDELIMC)
    {
        strcat(DirName, PATHDELIMS);
    }

    strcpy(Buff, DirName);
    strcat(Buff, "0.ftr");
    fcopen(Buff, "rb");

    if(!DirExists(Dir))
    {
        return FALSE;
    }

    return TRUE;
} // Set

// ---------------------------

bool MSGASMSG::Next(void)
{
    CHP = 219;

    if(DirName == NULL)
    {
        return FALSE;
    }

    if(MsgNum == 0)
    {
        return FALSE;
    }

    if(MaxNum == 0)
    {
        return FALSE;
    }

    CHP = 220;
    MsgNum++;

    while(MsgNum <= MaxNum)
    {
        if(MsgMask[MsgNum] != 0)
        {
            return TRUE;
        }

        MsgNum++;
    }
    CHP    = 221;
    MsgNum = 0;
    return FALSE;
} // Next

// ---------------------------

bool MSGASMSG::Rewind(void)
{
    char bb[512];
    DIR * ff;
    struct dirent * pp;

    if(DirName == NULL)
    {
        return FALSE;
    }

    if(MsgMask != NULL)
    {
        free(MsgMask);
        MsgMask = NULL;
    }

    MsgNum = 0;
    MaxNum = 0;

    Log.Level(LOGD) << "Do Rewind for dir '" << DirName << "'" << EOL;
    ff = opendir(dirslashbug(DirName));

    if(ff == NULL)
    {
        Log.Level(LOGD) << "Error in opendir. ERRNO == " << errno << EOL;
        return FALSE;
    }

    while((pp = readdir(ff)) != NULL)
    {
// WARNING!!!!!!!!!!! i'm not sure about d_type in all operation systems
//      if ((pp->d_type & 0x1a) == 0) {
        if(fsCompareName(pp->d_name, "*" MsgExtension) != 0)
        {
            strcpy(bb, pp->d_name);
            Log.Level(LOGD) << "File '" << bb << "' matched with mask." << EOL;
            *strchr(bb, '.') = '\0';

            if(StrIsNum(bb))
            {
                Log.Level(LOGD) << bb << " is a number. Add to list." << EOL;
                AddToMask(atoi(bb));
            }
        }
    }
    closedir(ff);

    Log.Level(LOGD) << "------------------" << EOL;
    Log.Level(LOGD) << "Max message number is: " << MaxNum << EOL;
    MsgNum = 1;

    if(MaxNum == 0)
    {
        return FALSE;
    }

    while(MsgNum <= MaxNum)
    {
        if(MsgMask[MsgNum] == 1)
        {
            Log.Level(LOGD) << "First message number is: " << MsgNum << EOL;
            Log.Level(LOGD) << "------------------" << EOL;
            return TRUE;
        }

        MsgNum++;
    }

    MsgNum = 1;
    Log.Level(LOGD) << "Messages not found. Set first number to 1" << EOL;
    Log.Level(LOGD) << "------------------" << EOL;
    return FALSE;
} // Rewind

// ---------------------------

bool MSGASMSG::Renumber(void)
{
    unsigned int Num, NewNum;
    char Buff[1024];
    char Buff2[1024];

    Log.Level(LOGD) << EOL;
    Log.Level(LOGD) << "Do Renumber for base '" << DirName << "'" << EOL;
    Log.Level(LOGD) << "----------------------------------------" << EOL;

    if(Rewind() == FALSE)
    {
        Log.Level(LOGD) << "Base is Empty?" << EOL;
        return TRUE;
    }

    Num = 1;

    while(Num <= MaxNum)
    {
        if(MsgMask[Num] == 0)
        {
            Num++;
        }
        else
        {
            NewNum = 1;

            while(NewNum <= MaxNum)
            {
                if(MsgMask[NewNum] == 1)
                {
                    NewNum++;
                }
                else
                {
                    if(NewNum < Num)
                    {
                        sprintf(Buff, "%s%u" MsgExtension, DirName, Num);
                        sprintf(Buff2, "%s%u" MsgExtension, DirName, NewNum);
                        Log.Level(LOGD) << "Rename '" << Buff << "' to '" <<
                                           Buff2 << "'" << EOL;

                        if(rename(Buff, Buff2) != 0)
                        {
                            Log.Level(LOGE) << "Unable to rename '" << Buff <<
                                               "' to '" << Buff2 << "'" << EOL;
                            return FALSE;
                        }

                        MsgMask[NewNum] = 1;
                        MsgMask[Num]    = 0;
                        break;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            Num++;
        }
    }
    return TRUE;
} // Renumber

// ---------------------------

bool MSGASMSG::DeleteMsg(void)
{
    char Buff[1024];

    if(MsgMask[MsgNum] == 0)
    {
        return TRUE;
    }

    sprintf(Buff, "%s%u" MsgExtension, DirName, MsgNum);
    int error = unlink(Buff);

    if(!error)
    {
        MsgMask[MsgNum] = 0;
        Log.Level(LOGD) << "Message " << Buff << " is deleted" << EOL;
    }

    return !error;
}

// ---------------------------

char * MSGASMSG::ReadToMem(void)
{
    FILE * fh;
    char * Buff;
    unsigned long FSize;

    Buff = (char *)malloc(4096);
    CheckMem(Buff);
    sprintf(Buff, "%s%u" MsgExtension, DirName, MsgNum);
    fh = fopen(Buff, "rb");
    free(Buff);

    if(fh == NULL)
    {
        return NULL;
    }

    if(fseek(fh, 0, SEEK_END) != 0)
    {
        fclose(fh);
        return NULL;
    }

    FSize = ftell(fh);

    if(fseek(fh, 0, SEEK_SET) != 0)
    {
        fclose(fh);
        return NULL;
    }

    Buff = (char *)malloc(FSize + sizeof(FSize));
    CheckMem(Buff);
    *(unsigned long *)Buff = FSize;

    if(FSize != 0)
    {
        if(fread(Buff + sizeof(FSize), FSize, 1, fh) != 1)
        {
            free(Buff);
            fclose(fh);
            return NULL;
        }
    }

    fclose(fh);
    return Buff;
} // ReadToMem

// ---------------------------

char * MSGASMSG::MessageName(void)
{
    static char Buff[2048];

    sprintf(Buff, "%s%u" MsgExtension, DirName, MsgNum);
    return Buff;
}

// ---------------------------

bool MSGASMSG::WriteFromMem(char * Buff)
{
    FILE * fh;
    unsigned long FSize;
    unsigned int Num;
    char * b;
    char tmt[1024];

    Num = MaxNum;

    do
    {
        Num++;
        sprintf(tmt, "%s%u" MsgExtension, DirName, Num);
    }
    while(access(tmt, F_OK) == 0);
    AddToMask(Num);

    b = (char *)malloc(4096);
    CheckMem(b);
    sprintf(b, "%s%u" MsgExtension, DirName, Num);
    fh = fopen(b, "wb");
    free(b);

    if(fh == NULL)
    {
        return FALSE;
    }

    FSize = *(unsigned long *)Buff;

    if(FSize != 0)
    {
        if(fwrite(Buff + sizeof(FSize), FSize, 1, fh) != 1)
        {
            fclose(fh);
            return FALSE;
        }
    }

    fclose(fh);
    return TRUE;
} // WriteFromMem

// ---------------------------

bool MSGASMSG::ReadMsg(cMSG & m)
{
    MsgHeader Hdr;
    FILE * fh;
    char * Buff;
    unsigned long FSize;
    int i;

//s_stat tmp_stat;

    CHP  = 222;
    Buff = (char *)malloc(4096);
    CheckMem(Buff);
    sprintf(Buff, "%s%u" MsgExtension, DirName, MsgNum);

/*   if (MaxMsgSize != 0)
   {
    if (!stat(Buff,&tmp_stat))
    {
     if ((uint)tmp_stat.st_size > MaxMsgSize)
     {
      Log.Level(LOGE) << "   Error: size of MSG '" << Buff << "' is " <<
                         (uint)tmp_stat.st_size << " (" << MaxMsgSize << "
                            allowed)." << EOL;
      free(Buff);
      return FALSE;
     }
    }
   }*/

    fh = fopen(Buff, "rb");
    i  = errno;

    if(fh == NULL)
    {
        if(i != EACCES)
        {
            Log.Level(LOGE) << "Unable to open message '" << Buff <<
                               "', Errno: " << i << EOL;
        }

        free(Buff);
        return FALSE;
    }

    free(Buff);

    CHP = 223;

    if(fread(&Hdr, sizeof(Hdr), 1, fh) != 1)
    {
        i = errno;
        Log.Level(LOGE) << "Unable to read message header, Errno: " << i <<
                           EOL;
        fclose(fh);
        return FALSE;
    }

    m.Clear();
    CHP = 224;
#ifdef _AIX_CONV
    Hdr.TimesRead = RotateShort(Hdr.TimesRead);
    Hdr.DestNode  = RotateShort(Hdr.DestNode);
    Hdr.OrigNode  = RotateShort(Hdr.OrigNode);
    Hdr.Cost    = RotateShort(Hdr.Cost);
    Hdr.OrigNet = RotateShort(Hdr.OrigNet);
    Hdr.DestNet = RotateShort(Hdr.DestNet);
    Hdr.ReplyTo = RotateShort(Hdr.ReplyTo);
    Hdr.Attr    = RotateShort(Hdr.Attr);
#endif
    m._FromAddr.Node(Hdr.OrigNode);
    m._FromAddr.Net(Hdr.OrigNet);
    m._ToAddr.Node(Hdr.DestNode);
    m._ToAddr.Net(Hdr.DestNet);

    strncpy(m._Subject, Hdr.Subject, 72);
    strncpy(m._FromName, Hdr.FromName, 36);
    strncpy(m._ToName, Hdr.ToName, 36);
    m._Time      = ToTime(Hdr.DateTime);
    m._Cost      = Hdr.Cost;
    m._ReplyTo   = Hdr.ReplyTo;
    m._TimesRead = Hdr.TimesRead;
    m._NextReply = Hdr.NextReply;
    memcpy(m._Reserved, Hdr.Reserved, 8);
    SetMsgAttr(Hdr.Attr, m);

//   if (LogLevel >= 5) {
//      Log.Level(LOGD) << "MSGASMSG::ReadMsg. Message after parsing header: "
// << EOL;
//      m.Print();
//   }

    CHP = 225;

// Now, read body...
    if(fseek(fh, 0L, SEEK_END) != 0)
    {
        i = errno;
        Log.Level(LOGE) << "Unable to seek to end of message, Errno: " << i <<
                           EOL;
        fclose(fh);
        return FALSE;
    }

    FSize = ftell(fh) - sizeof(Hdr);

    if(FSize == 0)
    {
        if(UseOwnZone)
        {
            m._FromAddr.Zone(FA_ANYMASK);
            m._FromAddr.Zone(GetMyAka(m._FromAddr).Zone());
            m._ToAddr.Zone(FA_ANYMASK);
            m._ToAddr.Zone(GetMyAka(m._ToAddr).Zone());
        }

        fclose(fh);
        return TRUE;
    }

    CHP = 226;

    if(fseek(fh, sizeof(Hdr), SEEK_SET) != 0)
    {
        i = errno;
        Log.Level(LOGE) <<
        "Unable to seek to beginning of message, Errno: " << i << EOL;
        fclose(fh);
        return FALSE;
    }

    CHP  = 227;
    Buff = (char *)malloc(FSize + 1);
    CheckMem(Buff);
    memset(Buff, 0, FSize + 1);

    CHP = 228;

    if(fread(Buff, FSize, 1, fh) != 1)
    {
        i = errno;
        Log.Level(LOGE) << "Unable to read message body, Errno: " << i << EOL;
        free(Buff);
        fclose(fh);
        return FALSE;
    }

    m.ParseMem(Buff);
    CHP = 236;
    free(Buff);
    fclose(fh);
    CHP = 237;
    return TRUE;
} // ReadMsg

// ---------------------------

bool MSGASMSG::WriteOneMsg(unsigned int Num, cMSG & m)
{
    MsgHeader Hdr;
    FILE * fh;
    char * Buff;


    CHP  = 23701;
    Buff = (char *)malloc(40960);
    CHP  = 23702;
    CheckMem(Buff);
    CHP = 23703;
    sprintf(Buff, "%s%u" MsgExtension, DirName, Num);
    CHP = 23704;
    fh  = fopen(Buff, "wb");
    CHP = 23705;

    if(fh == NULL)
    {
        free(Buff);
        return FALSE;
    }

    CHP = 23706;
    free(Buff);

    CHP = 23707;
    Hdr.OrigNode = (unsigned short)(m._FromAddr.Node());
    Hdr.OrigNet  = (unsigned short)(m._FromAddr.Net());
    Hdr.DestNode = (unsigned short)(m._ToAddr.Node());
    Hdr.DestNet  = (unsigned short)(m._ToAddr.Net());
    strncpy(Hdr.Subject, m._Subject, 72);
    strncpy(Hdr.FromName, m._FromName, 36);
    strncpy(Hdr.ToName, m._ToName, 36);
    strncpy(Hdr.DateTime, FromTime(m._Time), 20);
    Hdr.Cost      = m._Cost;
    Hdr.ReplyTo   = m._ReplyTo;
    Hdr.TimesRead = m._TimesRead;
    Hdr.NextReply = m._NextReply;
    memcpy(Hdr.Reserved, m._Reserved, 8);
    CHP = 23708;

    SetMsgAttr(m, Hdr.Attr);

    CHP = 23709;
#ifdef _AIX_CONV
    Hdr.TimesRead = RotateShort(Hdr.TimesRead);
    Hdr.DestNode  = RotateShort(Hdr.DestNode);
    Hdr.OrigNode  = RotateShort(Hdr.OrigNode);
    Hdr.Cost    = RotateShort(Hdr.Cost);
    Hdr.OrigNet = RotateShort(Hdr.OrigNet);
    Hdr.DestNet = RotateShort(Hdr.DestNet);
    Hdr.ReplyTo = RotateShort(Hdr.ReplyTo);
    Hdr.Attr    = RotateShort(Hdr.Attr);
#endif

    if(fwrite(&Hdr, sizeof(Hdr), 1, fh) != 1)
    {
        fclose(fh);
        return FALSE;
    }

    CHP = 23710;

    if(!WriteMsgBody(m, fh))
    {
        fclose(fh);
        return FALSE;
    }

    CHP = 23711;
    fclose(fh);
    CHP = 23712;
    AddToMask(Num);
    return TRUE;
} // WriteOneMsg

// ---------------------------

bool MSGASMSG::WriteMsg(cMSG & m)
{
    return WriteOneMsg(MsgNum, m);
}

// ---------------------------

bool MSGASMSG::WriteNewMsg(cMSG & m)
{
    unsigned int Num;
    char Buff[1024];

    Num = MaxNum;

    do
    {
        Num++;
        sprintf(Buff, "%s%u" MsgExtension, DirName, Num);
    }
    while(access(Buff, F_OK) == 0);
    AddToMask(Num);
    return WriteOneMsg(Num, m);
}

// ---------------------------

void MSGASMSG::Print(void)
{
#if 0

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "---------------- MSGASMSG -------------------" <<
                           EOL;

        if(DirName != NULL)
        {
            Log.Level(LOGD) << "Directory == '" << DirName << "'" << EOL;
        }

        Log.Level(LOGD) << "Current Msg number == '" << MsgNum << "'" << EOL;
    }

#endif
}

// ---------------------------

MSGBASE * MakeBase(char * BName)
{
    MSGBASE * tmt;

// Make message base from name.
// First character of base name can be:
// $ -- Squish style area
// @ -- JAM style area
// # -- PKT style area
// Without these characters it is a MSG style area

    if(*BName == '$')
    {
        tmt = new SQUISH('$');
    }
    else if(*BName == '#')
    {
        tmt = new PKTBASE();
    }
    else if(*BName == '@')
    {
        tmt = new SQUISH('@');
    }
    else
    {
        tmt = new MSGASMSG();
    }

    if(tmt == NULL)
    {
        yyerror("Internal Error. Out of memory.");
        return NULL;
    }

    return tmt;
} // MakeBase
