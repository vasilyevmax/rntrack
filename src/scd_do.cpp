/*
 *  RNtrack - FTN message tracker/router
 *
 *  scd_do.cpp - Part of scandir.cpp
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

#ifndef __SCD_DO_CPP__
#define __SCD_DO_CPP__


FA & MakeFromAddr(cMSG & m, FA & s)
{
    static FA t;

    CHP = 2;
    t   = s;

    if(s.Zone() & FA_ANYMASK)
    {
        t.Zone(m._FromAddr.Zone());
    }
    else
    {
        t.Zone(s.Zone());
    }

    if(s.Net() & FA_ANYMASK)
    {
        t.Net(m._FromAddr.Net());
    }
    else
    {
        t.Net(s.Net());
    }

    if(s.Node() & FA_ANYMASK)
    {
        t.Node(m._FromAddr.Node());
    }
    else
    {
        t.Node(s.Node());
    }

    if(s.Point() & FA_ANYMASK)
    {
        t.Point(m._FromAddr.Point());
    }
    else
    {
        t.Point(s.Point());
    }

    if(s.Zone() & FA_TOMASK)
    {
        t = m._ToAddr;
    }

    if(s.Zone() & FA_FROMMASK)
    {
        t = m._FromAddr;
    }

    if(s.Zone() & FA_OURMASK)
    {
        t = GetMyAka(m._ToAddr);
    }

    return t;
} // MakeFromAddr

FA & MakeToAddr(cMSG & m, FA & s)
{
    static FA t;

    CHP = 3;
    t   = s;

    if(s.Zone() & FA_ANYMASK)
    {
        t.Zone(m._ToAddr.Zone());
    }
    else
    {
        t.Zone(s.Zone());
    }

    if(s.Net() & FA_ANYMASK)
    {
        t.Net(m._ToAddr.Net());
    }
    else
    {
        t.Net(s.Net());
    }

    if(s.Node() & FA_ANYMASK)
    {
        t.Node(m._ToAddr.Node());
    }
    else
    {
        t.Node(s.Node());
    }

    if(s.Point() & FA_ANYMASK)
    {
        t.Point(m._ToAddr.Point());
    }
    else
    {
        t.Point(s.Point());
    }

    if(s.Zone() & FA_FROMMASK)
    {
        t = m._FromAddr;
    }

    if(s.Zone() & FA_TOMASK)
    {
        t = m._ToAddr;
    }

    if(s.Zone() & FA_OURMASK)
    {
        t = GetMyAka(m._FromAddr);
    }

    return t;
} // MakeToAddr

void MakeToName(cMSG & m, char * s, char * t)
{
    CHP = 4;

    if(s != NULL && strcmp(s, "*") == 0)
    {
        RSTRLCPY(t, m._ToName, 36);
        return;
    }

    if(s != NULL && strcmp(s, FROMMASK_CHAR) == 0)
    {
        RSTRLCPY(t, m._FromName, 36);
        return;
    }

    if(s != NULL && strcmp(s, TOMASK_CHAR) == 0)
    {
        RSTRLCPY(t, m._ToName, 36);
        return;
    }

    if(s != NULL)
    {
        RSTRLCPY(t, s, 36);
        return;
    }
} // MakeToName

void MakeFromName(cMSG & m, char * s, char * t)
{
    CHP = 5;

    if(s != NULL && strcmp(s, "*") == 0)
    {
        RSTRLCPY(t, m._FromName, 36);
        return;
    }

    if(s != NULL && strcmp(s, FROMMASK_CHAR) == 0)
    {
        RSTRLCPY(t, m._FromName, 36);
        return;
    }

    if(s != NULL && strcmp(s, TOMASK_CHAR) == 0)
    {
        RSTRLCPY(t, m._ToName, 36);
        return;
    }

    if(s != NULL)
    {
        RSTRLCPY(t, s, 36);
        return;
    }
} // MakeFromName

void PrepareMsg(cMSG & s, cMSG & d, NormalMask * _Mask)
{
    FA tf;
    FA tt;
    char sf[36];
    char st[36];
    char * tmt;

    CHP = 6;
    MakeFromName(s, _Mask->_FromName, sf);
    MakeToName(s, _Mask->_ToName, st);
    RSTRLCPY(d._FromName, sf, 36);
    RSTRLCPY(d._ToName, st, 36);
    RSTRLCPY(d._Subject, s._Subject, 72);
    tf = MakeFromAddr(s, _Mask->_FromAddr);
    tt = MakeToAddr(s, _Mask->_ToAddr);

    if(s._FromAddr != tf)          // If we change the source address
    {
        d.fChanged = 1;            // we need to change MSGID.
    }

    d._FromAddr = tf;
    d._ToAddr   = tt;

    if(&s == &d)
    {
        d.fPrivate  = (_Mask->fPrivate != 0) ? _Mask->fPrivate : s.fPrivate;
        d.fCrash    = (_Mask->fCrash != 0) ? _Mask->fCrash : s.fCrash;
        d.fReceived = (_Mask->fReceived != 0) ? _Mask->fReceived : s.fReceived;
        d.fSent = (_Mask->fSent != 0) ? _Mask->fSent : s.fSent;
        d.fFileAttach =
            (_Mask->fFileAttach != 0) ? _Mask->fFileAttach : s.fFileAttach;
        d.fTransit  = (_Mask->fTransit != 0) ? _Mask->fTransit : s.fTransit;
        d.fOrphan   = (_Mask->fOrphan != 0) ? _Mask->fOrphan : s.fOrphan;
        d.fKillSent = (_Mask->fKillSent != 0) ? _Mask->fKillSent : s.fKillSent;
        d.fLocal    = (_Mask->fLocal != 0) ? _Mask->fLocal : s.fLocal;
        d.fHold = (_Mask->fHold != 0) ? _Mask->fHold : s.fHold;
        d.fFileRequest =
            (_Mask->fFileRequest != 0) ? _Mask->fFileRequest : s.fFileRequest;
        d.fRRQ     = (_Mask->fRRQ != 0) ? _Mask->fRRQ : s.fRRQ;
        d.fIRR     = (_Mask->fIRR != 0) ? _Mask->fIRR : s.fIRR;
        d.fARQ     = (_Mask->fARQ != 0) ? _Mask->fARQ : s.fARQ;
        d.fFURQ    = (_Mask->fFURQ != 0) ? _Mask->fFURQ : s.fFURQ;
        d.fDIR     = (_Mask->fDIR != 0) ? _Mask->fDIR : s.fDIR;
        d.fIMM     = (_Mask->fIMM != 0) ? _Mask->fIMM : s.fIMM;
        d.fCFM     = (_Mask->fCFM != 0) ? _Mask->fCFM : s.fCFM;
        d.fTFS     = (_Mask->fTFS != 0) ? _Mask->fTFS : s.fTFS;
        d.fKFS     = (_Mask->fKFS != 0) ? _Mask->fKFS : s.fKFS;
        d.fScanned = (_Mask->fScanned != 0) ? _Mask->fScanned : s.fScanned;
        d.fLok     = (_Mask->fLok != 0) ? _Mask->fLok : s.fLok;
        d.fAS = (_Mask->fAS != 0) ? _Mask->fAS : s.fAS;
    }
    else
    {
        d.fPrivate  = (_Mask->fPrivate != 0) ? _Mask->fPrivate : 0;
        d.fCrash    = (_Mask->fCrash != 0) ? _Mask->fCrash : 0;
        d.fReceived = (_Mask->fReceived != 0) ? _Mask->fReceived : 0;
        d.fSent = (_Mask->fSent != 0) ? _Mask->fSent : 0;
        d.fFileAttach = (_Mask->fFileAttach != 0) ? _Mask->fFileAttach : 0;
        d.fTransit    = (_Mask->fTransit != 0) ? _Mask->fTransit : 0;
        d.fOrphan   = (_Mask->fOrphan != 0) ? _Mask->fOrphan : 0;
        d.fKillSent = (_Mask->fKillSent != 0) ? _Mask->fKillSent : 0;
        d.fLocal    = (_Mask->fLocal != 0) ? _Mask->fLocal : 0;
        d.fHold = (_Mask->fHold != 0) ? _Mask->fHold : 0;
        d.fFileRequest = (_Mask->fFileRequest != 0) ? _Mask->fFileRequest : 0;
        d.fRRQ     = (_Mask->fRRQ != 0) ? _Mask->fRRQ : 0;
        d.fIRR     = (_Mask->fIRR != 0) ? _Mask->fIRR : 0;
        d.fARQ     = (_Mask->fARQ != 0) ? _Mask->fARQ : 0;
        d.fFURQ    = (_Mask->fFURQ != 0) ? _Mask->fFURQ : 0;
        d.fDIR     = (_Mask->fDIR != 0) ? _Mask->fDIR : 0;
        d.fIMM     = (_Mask->fIMM != 0) ? _Mask->fIMM : 0;
        d.fCFM     = (_Mask->fCFM != 0) ? _Mask->fCFM : 0;
        d.fTFS     = (_Mask->fTFS != 0) ? _Mask->fTFS : 0;
        d.fKFS     = (_Mask->fKFS != 0) ? _Mask->fKFS : 0;
        d.fScanned = (_Mask->fScanned != 0) ? _Mask->fScanned : 0;
        d.fLok     = (_Mask->fLok != 0) ? _Mask->fLok : 0;
        d.fAS = (_Mask->fAS != 0) ? _Mask->fAS : 0;
    }

    if(_Mask->_Subject != NULL && strcmp(_Mask->_Subject, "*") != 0)
    {
        tmt = StrAsTpl(d, _Mask->_Subject);
        RSTRLCPY(d._Subject, tmt, 72);
        free(tmt);
    }

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) <<
                        "----------------------- Destin message -----------------" << EOL;
        d.Print();
        Log.Level(LOGD) <<
                        "----------------------- Source message -----------------" << EOL;
        s.Print();
    }
} // PrepareMsg

bool Action::Do(MSGBASE & b, cMSG & m)
{
    char * tmt;
    char * tmt2;
    cMSG * d;
    FILE * fh;
    PKT p;
    FA f;
    PKTrc rc;
    int rcc;
    char Buff[BUFF_SIZE];
    size_t size;

    CHP = 7;

    switch(_Act)
    {
    case ACT_IGNORE:
        CHP = 8;

        if(LogIgnore)
        {
            Log.Level(LOGN) << "Ignore msg " << b.MessageName() << EOL;
        }

        break;

    case ACT_DELETE:
        CHP = 9;
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be deleted" << EOL;
            return FALSE;
        }
        Log.Level(LOGI) << "Delete msg " << tmt << EOL;

        if(!b.DeleteMsg())
        {
            Log.Level(LOGE) << "Error deleting message " << tmt << EOL;
            return FALSE;
        }

        break;

    case ACT_FLAG:
        CHP = 10;
        Log.Level(LOGI) << "Create file " << _OutDir << EOL;
        fh = fcopen(_OutDir, "wb");

        if(fh == NULL)
        {
            Log.Level(LOGE) << "Error creating file " << _OutDir << EOL;
            return FALSE;
        }

        fclose(fh);
        break;

    case ACT_DELFILE:
        CHP = 10;
        Log.Level(LOGI) << "Delete file " << _OutDir << EOL;
        unlink(_OutDir);
        break;

    case ACT_DELETEATTACH:
        CHP = 11;

        if(m.fFileAttach)
        {
            m.Normalise();
            tmt = b.MessageName();
            Log.Level(LOGI) << "Delete files attached to " << tmt << EOL;
            tmt2 = FileInbound;

            if(sd->_FileInbound != NULL)
            {
                FileInbound = sd->_FileInbound;
            }

            if(!DeleteAttach(m))
            {
                FileInbound = tmt2;
                return FALSE;
            }

            FileInbound = tmt2;
        }

        break;

    case ACT_CHANGEPATH:
    case ACT_TOLOWERPATH:
    case ACT_TOUPPERPATH:
        CHP = 12;

        if(m.fFileAttach)
        {
            if(m.fLok == 1)
            {
                Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
                return FALSE;
            }
            m.Normalise();
            tmt = b.MessageName();

            if(_Act == ACT_CHANGEPATH)
            {
                if(strlen(_OutDir) == 0)
                {
                    Log.Level(LOGI) <<
                                    "Strip path to attached files in " << tmt << EOL;
                }
                else
                {
                    Log.Level(LOGI) <<
                                    "Change path to attached files in " << tmt <<
                                    " to " <<
                                    _OutDir << EOL;
                }
            }

            tmt2 = FileInbound;

            if(sd->_FileInbound != NULL)
            {
                FileInbound = sd->_FileInbound;
            }

            if(_Act == ACT_TOLOWERPATH)
            {
                Log.Level(LOGI) << "Convert path of attached files in " <<
                                tmt << " to lower case" << EOL;

                if(!ToLowerPath(m))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }
            }
            else if(_Act == ACT_TOUPPERPATH)
            {
                Log.Level(LOGI) << "Convert path of attached files in " <<
                                tmt << " to upper case" << EOL;

                if(!ToUpperPath(m))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }
            }
            else
            {
                if(!ChangePath(m, _OutDir))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }
            }

            FileInbound = tmt2;

//              m.fChanged = 1;
            if(SetViaAlways)
            {
                m.AddOurVia();
            }

            if(!b.WriteMsg(m))
            {
                Log.Level(LOGE) <<
                                "Error writing message with new subject " <<
                                tmt << EOL;
                return FALSE;
            }
        }

        break;

    case ACT_MOVEATTACH:
    case ACT_MOVEATTACHFBOX:
        CHP = 13;

        if(m.fFileAttach)
        {
            if(m.fLok == 1)
            {
                Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
                return FALSE;
            }
            m.Normalise();
            tmt  = b.MessageName();
            tmt2 = FileInbound;

            if(sd->_FileInbound != NULL)
            {
                FileInbound = sd->_FileInbound;
            }

            if(_Act == ACT_MOVEATTACHFBOX)
            {
                RSTRLCPY(Buff, MakeFileboxName(_f, _Flav), BUFF_SIZE);
                Log.Level(LOGI) << "Move attached files in " << tmt <<
                                " to " << Buff << EOL;
                mymkdir(Buff);

                if(!MoveAttach(m, Buff))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }

                if(!ReadLoFile(_f, _Flav))
                {
                    return FALSE;
                }

                AddFboxAttachToLo(m, Buff);

                if(!SaveLoFile(_f, _Flav))
                {
                    return FALSE;
                }
            }
            else
            {
                Log.Level(LOGI) << "Move attached files in " << tmt <<
                                " to " << _OutDir << EOL;

                if(!MoveAttach(m, _OutDir))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }
            }

            FileInbound = tmt2;

//              m.fChanged = 1;
            if(SetViaAlways)
            {
                m.AddOurVia();
            }

            if(!b.WriteMsg(m))
            {
                Log.Level(LOGE) <<
                                "Error writing message with new subject " <<
                                tmt << EOL;
                return FALSE;
            }
        }

        break;

    case ACT_COPYATTACH:
    case ACT_COPYATTACHFBOX:
        CHP = 13;

        if(m.fFileAttach)
        {
            m.Normalise();
            tmt  = b.MessageName();
            tmt2 = FileInbound;

            if(sd->_FileInbound != NULL)
            {
                FileInbound = sd->_FileInbound;
            }

            if(_Act == ACT_COPYATTACHFBOX)
            {
                RSTRLCPY(Buff, MakeFileboxName(_f, _Flav), BUFF_SIZE);
                Log.Level(LOGI) << "Copy attached files in " << tmt <<
                                " to " << Buff << EOL;

                mymkdir(Buff);

                if(!CopyAttach(m, Buff))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }

                if(!ReadLoFile(_f, _Flav))
                {
                    return FALSE;
                }

                AddFboxAttachToLo(m, Buff);

                if(!SaveLoFile(_f, _Flav))
                {
                    return FALSE;
                }
            }
            else
            {
                Log.Level(LOGI) << "Copy attached files in " << tmt <<
                                " to " << _OutDir << EOL;

                if(!CopyAttach(m, _OutDir))
                {
                    FileInbound = tmt2;
                    return FALSE;
                }
            }

            FileInbound = tmt2;
        }

        break;

    case ACT_COPY:
        CHP = 14;
        m.Normalise();

        if(SetViaAlways)
        {
            m.AddOurVia();
        }

        CHP = 1401;
        tmt = b.MessageName();
        CHP = 1402;
        Log.Level(LOGI) << "Copy msg " << tmt << " to " <<
                        _Base->BaseName() << EOL;

        if(_Base->Open() != TRUE)
        {
            Log.Level(LOGE) << "Error opening base '" <<
                            _Base->BaseName() << "'" << EOL;
            return FALSE;
        }

        CHP = 1403;

        if(!_Base->WriteNewMsg(m))
        {
            CHP = 1404;
            Log.Level(LOGE) << "Error writing message " << tmt <<
                            " to " << _Base->BaseName() << EOL;
            _Base->Close();
            return FALSE;
        }

        CHP = 1405;
        _Base->Close();
        CHP = 1406;
        break;

    case ACT_MOVE:
        CHP = 15;
        m.Normalise();
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }

        CHP = 1501;
        if(SetViaAlways)
        {
            m.AddOurVia();
        }

        CHP = 1502;
        Log.Level(LOGI) << "Move msg " << tmt << " to " <<
                        _Base->BaseName() << EOL;

        if(_Base->Open() != TRUE)
        {
            Log.Level(LOGE) << "Error opening base '" <<
                            _Base->BaseName() << "'" << EOL;
            return FALSE;
        }

        CHP = 1503;

        if(!_Base->WriteNewMsg(m))
        {
            CHP = 1504;
            Log.Level(LOGE) << "Error writing message " << tmt <<
                            " to " << _Base->BaseName() << EOL;
            _Base->Close();
            return FALSE;
        }

        CHP = 1505;

        if(!b.DeleteMsg())
        {
            CHP = 1506;
            Log.Level(LOGE) << "Error deleting message " << tmt << EOL;
            _Base->Close();
            return FALSE;
        }

        CHP = 1506;
        _Base->Close();
        CHP = 1507;
        break;

    case ACT_WRITEFILE:
        CHP = 16;
        m.Normalise();
        _Tpl->Clean();
        _Tpl->SetMsg(m);
        Log.Level(LOGI) << "Create file " << _OutDir << EOL;

        if(!_Tpl->Parse())
        {
            return FALSE;
        }

        if(!_Tpl->Save(_OutDir, 1))
        {
            return FALSE;
        }

        _Tpl->Clean();
        break;

    case ACT_ADDFILE:
        CHP = 16001;
        m.Normalise();
        _Tpl->Clean();
        _Tpl->SetMsg(m);
        Log.Level(LOGI) << "Append to file " << _OutDir << EOL;

        if(!_Tpl->Parse())
        {
            return FALSE;
        }

        if(!_Tpl->Save(_OutDir, 2))
        {
            return FALSE;
        }

        _Tpl->Clean();
        break;

    case ACT_ADDNOTE:
        CHP = 16100;
        m.Normalise();
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }

        if(SetViaAlways)
        {
            m.AddOurVia();
        }

        _Tpl->Clean();
        _Tpl->SetMsg(m);
        Log.Level(LOGI) << "Add note " << _Tpl->GetName() << " to msg " << tmt <<
                        EOL;

        if(!_Tpl->Parse())
        {
            return FALSE;
        }

        CHP = 16101;

        while((tmt = strchr(_Tpl->Body, '\n')) != NULL)
        {
            *tmt = '\r';
        }
        tmt  = m._Body;
        CHP  = 16102;
        size =
            ((tmt != NULL) ? strlen(tmt) : 0) + strlen(_Tpl->Body) + 1;
        m._Body  = (char *)malloc(size);
        m.fEmpty = 0;
        CheckMem(m._Body);
        CHP = 16103;
        RSTRLCPY(m._Body, _Tpl->Body, size);
        CHP = 16104;

        if(tmt != NULL)
        {
            RSTRLCAT(m._Body, tmt, size);
            free(tmt);
        }

        CHP = 16105;
        _Tpl->Clean();
//          m.fChanged = 1;
        CHP = 16106;

        if(!b.WriteMsg(m))
        {
            tmt = b.MessageName();
            Log.Level(LOGE) << "Error rewriting message " << tmt << EOL;
            return FALSE;
        }

        CHP = 16107;
        break;

    case ACT_ADDKLUDGE:
        CHP = 162;
        m.Normalise();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << b.MessageName() << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }
        Kludge * TKlu;
        char kName[SMALL_BUFF_SIZE];
        RSTRLCPY(kName, "\1", SMALL_BUFF_SIZE);
        RSTRLCAT(kName, _OutDir, SMALL_BUFF_SIZE);

        TKlu = new Kludge(kName, _TplName);
        m._Klu.AddToEnd(TKlu);

        break;

    case ACT_CALL:
        m.Normalise();
        tmt = StrAsTpl(m, _TplName);
        Log.Level(LOGI) << "Execute program " << tmt << EOL;

        if(_Tpl != NULL)
        {
            _Tpl->Clean();
            _Tpl->SetMsg(m);

            if(!_Tpl->Parse())
            {
                free(tmt);
                return FALSE;
            }

            if(!_Tpl->Save(_OutDir, 1))
            {
                free(tmt);
                return FALSE;
            }

            _Tpl->Clean();
        }

        rcc = ExecP(tmt);
        unlink(_OutDir);

        if(rcc < 0)
        {
            Log.Level(LOGE) << "Error executing " << tmt << EOL;
        }
        else
        {
            Log.Level(LOGI) << "Execution done. Error code == " << rcc <<
                            EOL;
        }

        free(tmt);
        break;

    case ACT_ROUTE:
    case ACT_ROUTEFBOX:
    case ACT_ROUTEHUB:
        CHP  = 17;
        tmt2 = FileInbound;

        if(sd->_FileInbound != NULL)
        {
            FileInbound = sd->_FileInbound;
        }

        m.Normalise();

        if(_Act == ACT_ROUTEHUB)
        {
            _f = m._ToAddr;
            _f.Node(Ndl.FindHub(_f));
            _f.Point(0);
            f = _f;
        }
        else
        {
            if(_f.Zone() & FA_TOMASK)
            {
                f = m._ToAddr;

                if(!(_f.Point() & FA_TOMASK))
                {
                    f.Point(0);
                }
            }
            else
            {
                f = _f;
            }
        }

        if((m.fLok == 0 && m.fSent == 0 && m.fAS == 0) || Before != NULL)
        {
            Log.Level(LOGI) << "Route message from " << m._FromAddr;
            Log.Level(LOGI) << " to " << m._ToAddr;
            Log.Level(LOGI) << " via " << f.ToStr() << EOL;

            RSTRLCPY(m._RoutedVia, f.ToStr(), 127);
        }

        if(Before != NULL)
        {
            Log.Level(LOGI) << " Execute 'BeforeRoute' ScanDir." << EOL;
            Before->DoWithRoute(*sd->_Base, m);
            m._RoutedVia[0] = '\0';
        }

        if(m.fLok == 1 || m.fSent == 1 || m.fAS == 1)
        {
            Log.Level(LOGE) << "Error: the message from " << m._FromAddr;
            Log.Level(LOGE) << " to " << m._ToAddr << " has ";
            if(m.fLok == 1)
            {
                Log.Level(LOGE) << "Locked";
            }
            else if(m.fSent == 1)
            {
                Log.Level(LOGE) << "Sent";
            }
            else if(m.fAS == 1)
            {
                Log.Level(LOGE) << "Archive/Sent";
            }
            Log.Level(LOGE) << " flag set and will not be routed" << EOL;
            p.Clean();
            return TRUE;
        }

        p.Set(f);
        tmt = f.ToStr();
        m.AddOurVia();

        if(_Act == ACT_ROUTEFBOX)
        {
            rc = p.AddMsg(m, _Flav, 1);
        }
        else
        {
            rc = p.AddMsg(m, _Flav, 0);
        }

        switch(rc)
        {
        case BSY:
            Log.Level(LOGW) << f << " is Busy now." << EOL;
            p.Clean();
            FileInbound = tmt2;
            return TRUE;

        case NULLPKT:
            Log.Level(LOGW) << "?UT file for address " << f <<
                            " is null size. Message " <<
                            b.MessageName() <<
                            " skipped." << EOL;
            p.Clean();
            FileInbound = tmt2;
            return TRUE;

        case PKTERROR:
            Log.Level(LOGE) << "Error routing message " <<
                            b.MessageName() <<
                            " to " << f << EOL;
            p.Clean();
            FileInbound = tmt2;
            return FALSE;

        case ATTERROR:
            Log.Level(LOGE) <<
                            "Error routing files attached to message " <<
                            b.MessageName() <<
                            " to " << f << EOL;
            p.Clean();
            FileInbound = tmt2;
            return FALSE;

        case BADPKT:
            Log.Level(LOGE) << "?LO file for address " << f <<
                            " is invalid. Message " <<
                            b.MessageName() <<
                            " skipped." << EOL;
            p.Clean();
            FileInbound = tmt2;
            return TRUE;

        default:
            break;
        } // switch
        p.Clean();
        LogTraffic(m, f);
        tmt = b.MessageName();

        if(KillMode == KILL_ALWAYS ||
                (KillMode == KILL_FLAG && m.fKillSent))
        {
            if(!b.DeleteMsg())
            {
                Log.Level(LOGE) << "Error deleting message " << tmt << EOL;
                FileInbound = tmt2;
                return FALSE;
            }
        }

        if(After != NULL)
        {
            Log.Level(LOGI) << " Execute 'AfterRoute' ScanDir." << EOL;
            RSTRLCPY(m._RoutedVia, f.ToStr(), 127);
            After->DoWithRoute(*sd->_Base, m);
            m._RoutedVia[0] = '\0';
        }

        FileInbound = tmt2;
        break;

    case ACT_POLL:
        CHP = -17;

        if(_f.Zone() & FA_TOMASK)
        {
            f = m._ToAddr;

            if(!(_f.Point() & FA_TOMASK))
            {
                f.Point(0);
            }
        }
        else
        {
            f = _f;
        }

        Log.Level(LOGI) << "Poll " << f << EOL;
        p.Set(f);
        rc = p.Poll(_Flav);

        switch(rc)
        {
        case BSY:
            Log.Level(LOGW) << f << " is Busy now." << EOL;
            p.Clean();
            return TRUE;

        case PKTERROR:
            Log.Level(LOGE) << "Error generating poll to " << f << EOL;
            p.Clean();
            return FALSE;

        default:
            break;
        }
        p.Clean();
        break;

    case ACT_NEWMSG:
        CHP = 18;
        d   = new cMSG();
        CHP = 1801;
        _Tpl->Clean();
        _Tpl->SetMsg(m, *d);
        CHP = 1802;
        d->_Time = time(NULL);

        Log.Level(LOGI) << "Create new msg in " << _Base->BaseName() <<
                        EOL;

        if(_Base->Open() != TRUE)
        {
            Log.Level(LOGE) << "Error opening base '" <<
                            _Base->BaseName() << "'" << EOL;
            return FALSE;
        }

        CHP = 1803;
        PrepareMsg(m, *d, (NormalMask *)_Mask);
        CHP = 1804;
        m.Normalise();
        CHP = 1805;
        d->fChanged = 1;

        if(!_Tpl->Parse())
        {
            CHP = 1806;
            delete d;
            _Base->Close();
            return FALSE;
        }

        CHP = 1807;
        CHP = 1808;

        if(!_Tpl->Save(*d))
        {
            delete d;
            _Base->Close();
            CHP = 1809;
            return FALSE;
        }

        CHP = 1810;

        if(SetViaAlways)
        {
            d->AddOurVia();
        }

        if(!_Base->WriteNewMsg(*d))
        {
            Log.Level(LOGE) << "Error writing new message " <<
                            _Base->MessageName() << EOL;
            delete d;
            _Base->Close();
            return FALSE;
        }

        CHP = 1811;
        _Tpl->Clean();
        CHP = 1812;
        delete d;
        _Base->Close();
        break;

    case ACT_REWRITE:
        CHP = 19;
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }

        Log.Level(LOGI) << "Rewrite msg " << tmt << EOL;
        PrepareMsg(m, m, (NormalMask *)_Mask);
        m.Normalise();

        if(SetViaAlways)
        {
            m.AddOurVia();
        }

//         m.fChanged = 1;
        if(!b.WriteMsg(m))
        {
            Log.Level(LOGE) << "Error rewriting message " << tmt << EOL;
            return FALSE;
        }

        break;

    case ACT_RECODE:
        CHP = 1901;
        m.Normalise();
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }

        Log.Level(LOGI) << "Recode msg " << tmt << EOL;
        m.Recode(_TplName);

        if(!b.WriteMsg(m))
        {
            Log.Level(LOGE) << "Error recoding message " << tmt << EOL;
            return FALSE;
        }

        break;

    case ACT_DISPLAY:
        CHP = 20;
        tmt = StrAsTpl(m, _TplName);
        Log.Level(LOGE) << tmt << EOL;
        free(tmt);
        break;

    case ACT_SCRIPT:
        CHP = 2001;

        if(DoThisWord(_TplName) != SS_OK)
        {
            return FALSE;
        }

        break;

    case ACT_SPLIT:
    {
        int Parts;
        int Lns;
        int CurPart;
        char * sBeg = NULL;
        char * tmt2;
        char * stmt = NULL;
        m.Normalise();
        tmt = b.MessageName();
        if(m.fLok == 1)
        {
            Log.Level(LOGE) << "Error: message " << tmt << " has Locked flag set and cannot be changed" << EOL;
            return FALSE;
        }

        if(SetViaAlways)
        {
            m.AddOurVia();
        }

        Lns = m.Lines();

        if(Lns > _Lines)
        {
            Log.Level(LOGI) << "Splitting message " << tmt << EOL;
            Parts = Lns / _Lines;

            if((Lns % _Lines) != 0)
            {
                Parts++;
            }

            CurPart = 1;
            sBeg    = m.Body();
            tmt2    = sBeg;
            tmt  = (char *)malloc(m.Bytes() + 200);
            stmt = tmt;
            CheckMem(tmt);

            while(*tmt2 != '\0')
            {
                tmt = stmt;
                sprintf(tmt, "\1SPLIT: by RNtrack. Part %d of %d\r",
                        CurPart,
                        Parts);
                tmt += strlen(tmt);

                for(Lns = 0; Lns < _Lines && *tmt2 != '\0'; tmt2++, tmt++)
                {
                    if(*tmt2 == '\r')
                    {
                        Lns++;
                    }

                    *tmt = *tmt2;
                }
                *tmt = '\0';
                m.Body(stmt);
                m.fChanged = TRUE;

                if(!b.WriteNewMsg(m))
                {
                    Log.Level(LOGE) <<
                                    "   Error writing split message." << EOL;
                    free(stmt);
                    m.Body(sBeg);
                    return FALSE;
                }

                CurPart++;
            }
            m.Body(sBeg);
            free(stmt);
            Log.Level(LOGI) << "   Message split to " << Parts <<
                            " parts" << EOL;

            if(!b.DeleteMsg())
            {
                Log.Level(LOGE) << "   Error deleting split message." <<
                                EOL;
                return FALSE;
            }
        }
    };
    break;

    default:
        break;
    } // switch
    CHP = 21;
    return TRUE;
} // Do

#endif // ifndef __SCD_DO_CPP__
