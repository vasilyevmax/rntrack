/*
 *  RNtrack - FTN message tracker/router
 *
 *  scripts.cpp - Work with scripts
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

// If you want to compile program with script subsystem
// define __PERL_VERSION__ in makefile with digital number of version without point character
// for perl 5.8.0 defines __PERL_VERSION__ as 5008000
//
// Check points 60*
// last CHP == 60055

#ifdef HAVE_CONFIG_H
    #include "aconfig.h"
    #undef BYTEORDER
    #undef HAVE_CONFIG_H
#endif

#if defined (__PERL_VERSION__)
    #undef BYTEORDER
    #include <EXTERN.h>
    #include <perl.h>
#endif

#include "script.hpp"
#if defined (__PERL_VERSION__)
    #include "constant.hpp"
    #include "vars.hpp"
    #include "parsetpl.hpp"
    #include "string.hpp"
    #include <XSUB.h>
#endif
#include "unused.h"

#define MSGVARNAME "main::FMSG"
#define KLUVARNAME "main::FKludges"

#if defined(__PERL_VERSION__)
static HV *m = NULL;                      // MSG
static HV *k = NULL;                      // Kludges
static PerlInterpreter *PerlSystem = NULL;
static cMSG *CurrMsg;
static int ScriptSystemInitialised = FALSE;

// --------------------------------------------------------------------
//        Perl extensions.
// --------------------------------------------------------------------

#if __PERL_VERSION__ < 5010000
    #if !defined _MSC_VER && (__GNUC__ + 0 < 4)
        //  extern "C" static void boot_DynaLoader _((CV *cv)); // not used
        extern "C" static void perl_Log( CV* cv);
        extern "C" static void perl_Update( CV* cv);
        extern "C" static void perl_ExistsInNodelist( CV* cv);
        extern "C" static void perl_FindHub( CV* cv);
        extern "C" static void perl_NewMsg( CV* cv);
    #endif
    #define XSdEfInE XS
#else
    #define XSdEfInE static XSPROTO
#endif

#define FromSP(i)       (char *)SvPV(ST(i), n_a); if (n_a == 0) sp_s  = (char *)""
#define XCAL            (char *)malloc(n_a + 1)


XSdEfInE(perl_Log)
{
    char * sp_s;

    dXSARGS;
    char * str;
    STRLEN n_a;

    cv  = cv;
    CHP = 60005;

    if(items != 1)
    {
        Log.Level(LOGE) << " perl_log() argument count (need 1, exist" <<
                        (int)items << ")." << EOL;
        abort();
    }

    sp_s = FromSP(0);
    str  = XCAL;
    strcpy(str, sp_s);
    Log.Level(LOGI) << str << EOL;
    free(str);
    XSRETURN_EMPTY;
    CHP = 60013;
}

XSdEfInE(perl_Update)
{
    // char *sp_s;
    dXSARGS;
    char * str;
    STRLEN n_a;
    SV ** tmt;
    FA a;
    unsigned int i;

    cv  = cv;
    CHP = 600014;

    if(items != 0)
    {
        Log.Level(LOGE) <<
                        "perl_Update() argument count (should be 0, actually " <<
                        (int)items << ")." << EOL;
        abort();
    }

    if(CurrMsg == NULL)
    {
        Log.Level(LOGE) <<
                        "perl_Update(): Attempt to update failed. No active message." <<
                        EOL;
        abort();
    }

    CHP = 600015;
    tmt = hv_fetch(m, "FromName", 8, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        RSTRLCPY(CurrMsg->_FromName, str, 36);
    }

    tmt = hv_fetch(m, "FromAddr", 8, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        a.Parse((const char * &)str);
        CurrMsg->_FromAddr = a;
    }

    CHP = 600016;
    tmt = hv_fetch(m, "ToName", 6, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        RSTRLCPY(CurrMsg->_ToName, str, 36);
    }

    tmt = hv_fetch(m, "ToAddr", 6, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        a.Parse((const char * &)str);
        CurrMsg->_ToAddr = a;
    }

    CHP = 600017;
    tmt = hv_fetch(m, "Subject", 7, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        RSTRLCPY(CurrMsg->_Subject, str, 72);
    }

    tmt = hv_fetch(m, "Body", 4, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        RSTRLCPY(CurrMsg->_Body, str, n_a);
    }

    tmt = hv_fetch(m, "AreaName", 8, FALSE);

    if(tmt != NULL)
    {
        str = SvPV(*tmt, n_a);
        RSTRLCPY(CurrMsg->_AreaName, str, 128);
    }

    tmt = hv_fetch(m, "Cost", 4, FALSE);

    if(tmt != NULL)
    {
        i = SvIV(*tmt);
        CurrMsg->_Cost = i;
    }

    tmt = hv_fetch(m, "TimesRead", 9, FALSE);

    if(tmt != NULL)
    {
        i = SvIV(*tmt);
        CurrMsg->_TimesRead = i;
    }

    tmt = hv_fetch(m, "ReplyTo", 7, FALSE);

    if(tmt != NULL)
    {
        i = SvIV(*tmt);
        CurrMsg->_ReplyTo = i;
    }

    tmt = hv_fetch(m, "NextReply", 9, FALSE);

    if(tmt != NULL)
    {
        i = SvIV(*tmt);
        CurrMsg->_NextReply = i;
    }

    CHP = 60020;
    XSRETURN_EMPTY;
}

XSdEfInE(perl_ExistsInNodelist)
{
    dXSARGS;
    char * sp_s;
    char * str;
    char * tmt;
    STRLEN n_a;
    FA fa;

    cv  = cv;
    CHP = 60030;

    if(items != 1)
    {
        Log.Level(LOGE) <<
                        " perl_ExistsInNodelist() argument count (should be 1, actually "
                        << (int)items << ")." << EOL;
        abort();
    }

    sp_s = FromSP(0);

    if(!Ndl.Enabled())
    {
        XSRETURN_IV(1);
    }

    str = XCAL;
    strcpy(str, sp_s);
    tmt = str;
    fa.Parse((const char * &)tmt);

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "perl_ExistsInNodelist(\"" << str << "\") as "
                        << fa << EOL;
    }

    free(str);

    if(!fa.Valid())
    {
        XSRETURN_IV(1);
    }

    CHP = 60035;
    XSRETURN_IV(Ndl.ExistInNodelist(fa) != (unsigned int)-1);
}

XSdEfInE(perl_FindHub)
{
    dXSARGS;
    char * sp_s;
    char * str;
    char * tmt;
    STRLEN n_a;
    FA fa;

    cv  = cv;
    CHP = 60030;

    if(items != 1)
    {
        Log.Level(LOGE) <<
                        " perl_FindHub() argument count (should be 1, actually " <<
                        (int)items << ")." << EOL;
        abort();
    }

    sp_s = FromSP(0);

    if(!Ndl.Enabled())
    {
        XSRETURN_IV(1);
    }

    str = XCAL;
    strcpy(str, sp_s);
    tmt = str;
    fa.Parse((const char * &)tmt);

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "perl_FindHub(\"" << str << "\") as " <<
                        fa << EOL;
    }

    free(str);

    if(!fa.Valid())
    {
        XSRETURN_IV(1);
    }

    CHP = 60035;
    XSRETURN_IV(Ndl.FindHub(fa));
}

//usage:
// NewMsg($MsgBase, $FromName, $FromAddr, $ToName, $ToAddr, $Subject,
//        $Flags, $Kludges, $Body)

XSdEfInE(perl_NewMsg)
{
    dXSARGS;
    cMSG * msg;
    FA addr;
    STRLEN n_a;
    MSGBASE * mb;
    IndBiList<Kludge>::ElemPtr Klu;
    char * base;
    char * tmp = NULL;
    cv  = cv;
    CHP = 60056;

    if(items < 9)
    {
        Log.Level(LOGE) <<
                        " perl_NewMsg() argument count (should be 9, actually " <<
                        (int)items << ")." << EOL;
        abort();
    }

    CHP  = 60057;
    base = SvPV(ST(0), n_a);
    CHP  = 600571;

    mb   = MakeBase(base);

    if(mb == NULL)
    {
        Log.Level(LOGE) << " perl_NewMsg(): MakeBase(" << base << ") error"
                        << EOL;
        abort();
    }

    CHP = 600572;

    if(!mb->Set(base, BASE_OUT))
    {
        Log.Level(LOGE) << " perl_NewMsg(): Invalid message base name."
                        << EOL;
        //  delete mb;
        mb = NULL;
        abort();
    }

    CHP = 600573;

    if(!mb->CheckOut())
    {
        Log.Level(LOGE) << " perl_NewMsg(): mb->CheckOut failed" << EOL;
        // delete mb;
        mb = NULL;
        abort();
    }

    CHP = 600574;

    // mb->Rewind();

    CHP = 600575;

    if(mb->Open() != TRUE)
    {
        Log.Level(LOGE) << " perl_NewMsg() Error opening base '" <<
                        mb->BaseName() << "'" << EOL;
        abort();
    }

    CHP = 60058;
    msg = new cMSG;
    msg->_Time = time(NULL);


    tmp = SvPV(ST(1), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    RSTRLCPY(msg->_FromName, tmp, 36);

    tmp = SvPV(ST(2), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    addr.Parse((const char * &)tmp);

    msg->_FromAddr = addr;
    tmp = SvPV(ST(3), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    RSTRLCPY(msg->_ToName, tmp, 36);

    tmp = SvPV(ST(4), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    addr.Parse((const char * &)tmp);

    msg->_ToAddr = addr;
    tmp = SvPV(ST(5), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    RSTRLCPY(msg->_Subject, tmp, 72);

    // 6 - flags (not implemented yet)
    tmp = SvPV(ST(6), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    // 7 - kludges (not implemented yet)
    tmp = SvPV(ST(6), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    tmp = SvPV(ST(8), n_a);

    if(n_a == 0)
    {
        tmp = (char *)"";
    }

    msg->SetBody(tmp, n_a);

    // msg->fChanged = 1;

    CHP = 60059;

    msg->Normalise();

    /*
    Kludge *TKlu;

    TKlu = new Kludge("\1TESTK ddd");
    msg->_Klu.AddToEnd(TKlu);

    TKlu = new Kludge("\1TESTK1 ggg");
    msg->_Klu.AddToEnd(TKlu);
    */

    CHP = 60060;

    if(SetViaAlways)
    {
        msg->AddOurVia();
    }

    if(!mb->WriteNewMsg(*msg))
    {
        Log.Level(LOGE) << "perl_NewMsg() Error writing new message " <<
                        mb->MessageName() << EOL;
        mb->Close();
        abort();
    }

    mb->Close();

    XSRETURN_EMPTY;
}


// --------------------------------------------------------------------
//        Init and stop
// --------------------------------------------------------------------

static void xs_init(void)
{
    static char * file = (char *)__FILE__;

    newXS("Log", perl_Log, file);
    newXS("Update", perl_Update, file);
    newXS("ExistsInNodelist", perl_ExistsInNodelist, file);
    newXS("FindHub", perl_FindHub, file);
    newXS("NewMsg", perl_NewMsg, file);
#if __PERL_VERSION__ >= 5008000 /* for Perl 5.8.* and above, see Makefile */
    //  newXS("DynaLoader::boot_DynaLoader",
    // (void(*)(PerlInterpreter*,CV*))boot_DynaLoader, file); // not used
#else /* for old Perl */
    //  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file); // not used
#endif
}

#endif /* defined(__PERL_VERSION__) */

int InitScriptSystem(void)
{
#if defined (__PERL_VERSION__)
    //char *embedding[] = { NULL, "", "0" };

    PerlSystem = perl_alloc();

    if(PerlSystem != NULL)
    {
        perl_construct(PerlSystem);
        // perl_parse(PerlSystem, xs_init, 1, embedding, NULL);
        return 1;
    }
    else
    {
        return 0;
    }
#else
    return 1;
#endif /* defined(__PERL_VERSION__) */
}

void InitScriptValues(void)
{
#if defined (__PERL_VERSION__)
    CHP = 60045;

    if(!ScriptSystemInitialised)
    {
        return;
    }

    sv_setpv(perl_get_sv("main::ConfigFile", TRUE), ConfigFile);
    sv_setpv(perl_get_sv("main::LogFile", TRUE), LogFileName);
    sv_setiv(perl_get_sv("main::LogLevel", TRUE), LogLevel);
    sv_setpv(perl_get_sv("main::SysopName", TRUE), SysopName);
    sv_setpv(perl_get_sv("main::TrafficLog", TRUE), TrafficLog);
    sv_setpv(perl_get_sv("main::Version", TRUE), ProgVersion);
    CHP = 60055;
#endif /* defined(__PERL_VERSION__) */
}

int StopScriptSystem(void)
{
#if defined (__PERL_VERSION__)
    if(PerlSystem != NULL)
    {
        CHP = 60056;
        perl_destruct(PerlSystem);
        CHP = 60057;
        perl_free(PerlSystem);
        CHP = 60058;
        PerlSystem = NULL;
    }

    return 1;
#else
    return 1;
#endif /* defined(__PERL_VERSION__) */
}

int _LoadScriptFile(char * fname)
{
#if defined (__PERL_VERSION__)
    dSP;

    char * perlargs[] =
    {
        (char *)"", (char *)fname, NULL
    };
    int rc;


    PUSHMARK(SP);
#if __PERL_VERSION__ >= 5008000
    /* for Perl 5.8.* and above, see Makefile */
    rc = perl_parse(PerlSystem,
                    (void (*)(PerlInterpreter *))xs_init,
                    2, perlargs, NULL);
#else
    /* for old Perl */
    rc = perl_parse(PerlSystem, xs_init, 2, perlargs, NULL);
#endif
    SPAGAIN;
    PUTBACK;

    if(rc != 0)
    {
        Log.Level(100) << "Error parsing script file '" <<
                       fname << "'." << EOL;
        Log.Level(100) <<
                       "See output to stderr to look error message." << EOL;
        return -1;
    }

    setlocale(LC_TIME, "C");
    ScriptSystemInitialised = TRUE;
#else
    unused(fname);
#endif /* defined(__PERL_VERSION__) */
    return 0;
} // _LoadScriptFile

// --------------------------------------------------------------------
//        Work with MSG
// --------------------------------------------------------------------


// --------------------------------------------------------------------
//        Scandirs...
// --------------------------------------------------------------------


int ScriptWordExists(char * word)
{
#if defined (__PERL_VERSION__)
    char Buff[1024];
    SV * val;

    if(!ScriptSystemInitialised)
    {
        return 0;
    }

    sprintf(Buff, "defined(&%s);", word);
    val = perl_eval_pv(Buff, TRUE);

    if(SvIV(val) == 1)
    {
        return 1;
    }

    return 0;
#else
    unused(word);
    return 0;
#endif /* defined(__PERL_VERSION__) */
} // ScriptWordExists


ScrRet DoThisWord(char * word)
{
#if defined (__PERL_VERSION__)
    STRLEN n_a;

    dSP;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    PUTBACK;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "DoThisWord(\"" << word << "\");" << EOL;
    }

    CHP = 60001;
    perl_call_pv(word, G_EVAL | G_SCALAR);
    SPAGAIN;
    PUTBACK;
    FREETMPS;
    LEAVE;
    CHP = 60002;

    if(SvTRUE(ERRSV))
    {
        CHP = 60003;
        Log.Level(LOGE) << SvPV(ERRSV, n_a) << EOL;
        return SS_ERROR;
    }

    CHP = 60004;
    return SS_OK;
#else
    unused(word);
    return SS_ERROR;
#endif /* defined(__PERL_VERSION__) */
} // DoThisWord

ScrRet DoThisWordRc(char * word)
{
#if defined (__PERL_VERSION__)
    STRLEN n_a;
    int i;

    dSP;
    int count;
    ENTER;
    SAVETMPS;
    PUSHMARK(SP);
    PUTBACK;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "DoThisWordRc(\"" << word << "\");" << EOL;
    }

    count = perl_call_pv(word, G_EVAL | G_SCALAR);
    SPAGAIN;

    if(count != 1)
    {
        Log.Level(LOGE) << "Error in Script '" << word <<
                        "'. count == " << count << EOL;
        return SS_ERROR;
    }

    if(SvTRUE(ERRSV))
    {
        Log.Level(LOGE) << SvPV(ERRSV, n_a) << EOL;
        return SS_ERROR;
    }

    i = POPi;
    PUTBACK;
    FREETMPS;
    LEAVE;

    if(LogLevel >= 5)
    {
        Log.Level(LOGD) << "DoThisWordRc(\"" << word << "\") rc == " <<
                        i << EOL;
    }

    switch(i)
    {
    case 0:
        return SS_FALSE;

    case 1:
        return SS_OK;

    case -1:
        return SS_ERROR;

    case -2:
        exit(255);

    case -3:
        abort();

    default:
        return SS_OK;
    }
#else
    unused(word);
    return SS_ERROR;
#endif /* defined(__PERL_VERSION__) */
} // DoThisWordRc

ScrRet DoSomeWord(char * word)
{
    if(ScriptWordExists(word))
    {
        return DoThisWord(word);
    }

    return SS_NOTDEF;
}

ScrRet DoSomeWordRc(char * word)
{
    if(ScriptWordExists(word))
    {
        return DoThisWordRc(word);
    }

    return SS_NOTDEF;
}

#if defined (__PERL_VERSION__)
void MakeHash(const char * KName, char * KBody)
{
    char * buff;
    char * tmt;
    char * p1, * p2;

    buff = (char *)malloc(10240);
    tmt  = NULL;

    if(KBody != NULL && KBody[0] != '\0')
    {
        tmt = (char *)malloc(strlen(KBody) * 2 + 2);

        for(p1 = tmt, p2 = KBody; *p2 != '\0'; p1++, p2++)
        {
            if(*p2 == '\'')
            {
                *p1 = '\\';
                p1++;
            }

            *p1 = *p2;
        }
        *p1 = '\0';
    }

    sprintf(buff, "push(@{$" KLUVARNAME "{'%s'}},'%s');",
            (KName != NULL) ? KName : "undef",
            (tmt != NULL) ? tmt : "undef");
    Log.Level(LOGD) << buff << EOL;
    perl_eval_pv(buff, TRUE);
    free(buff);
    free(tmt);
} // MakeHash
#endif /* defined(__PERL_VERSION__) */

void PrepareMsgForScript(cMSG & sm)
{
#if defined (__PERL_VERSION__)
    char * tmt;
    char Buff[128];
    IndBiList<Kludge>::ElemPtr Klu;

    if(!ScriptSystemInitialised)
    {
        return;
    }

    CurrMsg = &sm;

    if(m != NULL)
    {
        hv_undef(m);
        m = NULL;
    }

    if(k != NULL)
    {
        hv_undef(k);
        k = NULL;
    }

    m = perl_get_hv(MSGVARNAME, TRUE);
    k = perl_get_hv(KLUVARNAME, TRUE);
    hv_store(m, "FromName", 8, newSVpv(sm._FromName, 0), 0);
    hv_store(m, "ToName", 6, newSVpv(sm._ToName, 0), 0);
    hv_store(m, "FromAddr", 8, newSVpv(sm._FromAddr.ToStr(), 0), 0);
    tmt = StrAsTpl(sm, "@InetFromAddr");
    hv_store(m, "InetFromAddr", 12, newSVpv(tmt, 0), 0);
    free(tmt);
    hv_store(m, "ToAddr", 6, newSVpv(sm._ToAddr.ToStr(), 0), 0);
    tmt = StrAsTpl(sm, "@InetToAddr");
    hv_store(m, "InetToAddr", 10, newSVpv(tmt, 0), 0);
    free(tmt);
    hv_store(m, "Subject", 7, newSVpv(sm._Subject, 0), 0);
    tmt = StrAsTpl(sm, "@MsgDate");
    hv_store(m, "Date", 4, newSVpv(tmt, 0), 0);
    free(tmt);
    tmt = StrAsTpl(sm, "@MsgAge");
    hv_store(m, "Age", 3, newSVpv(tmt, 0), 0);
    free(tmt);
    tmt = sm.FlagsToStr(Buff);
    nls_strupr(tmt);
    hv_store(m, "Attr", 4, newSVpv(tmt, 0), 0);

    if(sm._Body != NULL && sm.Bytes() != 0)
    {
        hv_store(m, "Body", 4, newSVpv(sm._Body, sm.Bytes()), 0);
        hv_store(m, "Lines", 5, newSViv(sm.Lines()), 0);
    }

    hv_store(m, "Cost", 4, newSViv(sm._Cost), 0);
    hv_store(m, "TimesRead", 9, newSViv(sm._TimesRead), 0);
    hv_store(m, "ReplyTo", 7, newSViv(sm._ReplyTo), 0);
    hv_store(m, "NextReply", 9, newSViv(sm._NextReply), 0);

    if(sm._AreaName[0] != '\0')
    {
        hv_store(m, "AreaName", 8, newSVpv(sm._AreaName, 0), 0);
    }

    // Set kludges
    Klu = sm._Klu.GetFirst();

    while(Klu != NULL)
    {
        MakeHash(Klu->Name(), Klu->Body());
        Klu++;
    }
#else
    if(sm.Body() != NULL)
    {}
#endif /* defined(__PERL_VERSION__) */
} // PrepareMsgForScript


#if defined (__PERL_VERSION__)
#ifdef OS2
char * strdup(const char * src)
{
    char * dest = (char *)malloc(strlen(src) + 1);

    if(dest != NULL)
    {
        RSTRLCPY(dest, src, strlen(src));
    }

    return dest;
}
#endif
#endif /* defined(__PERL_VERSION__) */

