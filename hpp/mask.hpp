/*
 *  RNtrack - FTN message tracker/router
 *
 *  mask.hpp - Work with masks
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

#ifndef _MASK_HPP_
#define _MASK_HPP_

#include "msg.hpp"

typedef enum {MASK_ADD, MASK_SKIP, MASK_NORMAL, MASK_ERROR} MaskType;

class ScanDir;

class Mask
{
public:

    MaskType _Type;
    ScanDir * sd;

    virtual ~Mask();
    virtual void Print(void) const;
    virtual int operator ==(cMSG & m) const   = 0;
    virtual const char * MaskName(void) const = 0;
};

class BodyMask : public Mask
{
public:
    char * _Body;
    uint _Lines;
    uint _Bytes;
    BodyMask();
    ~BodyMask();
    void Print(void) const;
    int operator ==(cMSG & m) const;

    const char * MaskName(void) const
    {
        return "BodyMask";
    }
};


class ScriptMask : public Mask
{
public:
    char * _ScriptName;
    ScriptMask();
    ~ScriptMask();
    void Print(void) const;
    int operator ==(cMSG & m) const;

    const char * MaskName(void) const
    {
        return "ScriptMask";
    }
};


class KludgeMask : public Mask
{
public:
    char * _KludgeName;
    char * _KludgeBody;
    uint _Times;
    KludgeMask();
    ~KludgeMask();
    void Print(void) const;
    int operator ==(cMSG & m) const;

    const char * MaskName(void) const
    {
        return "KludgeMask";
    }
};

class NormalMask : public Mask
{
public:

    FA _FromAddr;
    FA _ToAddr;
    char * _FromName;
    char * _ToName;
    char * _Subject;
    uint Loops;
// ----- bit field attributes of message ----
    uint fMaxAge : 2;        // Max Age.
    uint fMaxAttach : 2;     // Max Attach Size
    uint fEchomail : 2;      // Message is echomail.
    uint fScanned : 2;       // Scanned
    uint fLok : 2;           // Locked
    uint fAS : 2;            // Archive/Sent
    uint fLoop : 2;          // Loop check
    uint fPrivate : 2;       // Private.
    uint fCrash : 2;         // Crash.
    uint fReceived : 2;      // Received
    uint fSent : 2;          // Sent
    uint fFileAttach : 2;    // File attach
    uint fTransit : 2;       // Transit
    uint fOrphan : 2;        // Orphan
    uint fKillSent : 2;      // Kill/Sent
    uint fLocal : 2;         // Local
    uint fHold : 2;          // Hold
    uint fFileRequest : 2;   // File Request
    uint fRRQ : 2;           // RRQ
    uint fIRR : 2;           // IRR
    uint fARQ : 2;           // ARQ
    uint fFURQ : 2;          // FURQ
    uint fDIR : 2;           // DIR
    uint fIMM : 2;           // IMM
    uint fCFM : 2;           // CFM
    uint fEmpty : 2;         // Empty message (not have Body)
    uint fTFS : 2;           // TFS
    uint fKFS : 2;           // KFS
    uint fAttExists : 2;     // All attached files is exists
    uint fMaxMsg : 2;        // Max Message Size

    NormalMask();
    ~NormalMask();
    void Print(void) const;
    int operator ==(cMSG & m) const;

    const char * MaskName(void) const
    {
        return "Mask";
    }
};

#endif
