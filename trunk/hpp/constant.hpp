/*
 *  RNtrack - FTN message tracker/router
 *
 *  constants.hpp - Main constants definitions
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

#ifndef _CONST_HPP_
#define _CONST_HPP_

#ifdef HAVE_CONFIG_H
    #include "aconfig.h"
#endif

#if !defined(__OS2__) && defined(__EMX__)
    #define __OS2__
#endif

#if defined(__NT__) || defined(__MINGW32__) || defined(_WINDOWS)
    #define OsType         "/W32"
    #define PATHDELIMS     "\\"
    #define PATHDELIMC     '\\'
#elif defined(__OS2__) || defined(__os2__)
    #define OsType         "/OS2"
    #define PATHDELIMS     "\\"
    #define PATHDELIMC     '\\'
#elif defined(__DJGPP__) || defined(__DOS4G__)
    #define OsType         "/386"
    #define PATHDELIMS     "\\"
    #define PATHDELIMC     '\\'
#elif defined (__unix__)
    #if defined (__linux__)
        #define OsType "/LNX"
    #elif defined (__FreeBSD__)
        #define OsType "/FBSD"
    #elif defined (__OpenBSD__)
        #define OsType "/OBSD"
    #elif defined (__NetBSD__)
        #define OsType "/NBSD"
    #elif defined (__sun__)
        #define OsType "/SUN"
    #elif defined (_AIX)
        #define OsType "/AIX"
    #elif defined (__OSX__)
        #define OsType "/OSX"
    #elif defined (__PLATFORM_TYPE__)
        #define OsType "/"__PLATFORM_TYPE__
    #else
        #define OsType "/Unix"
    #endif
    #define PATHDELIMS     "/"
    #define PATHDELIMC     '/'
#endif

#ifndef PACKAGE_NAME
    #define PACKAGE_NAME "RNTrack"
#endif
#ifdef VERSION
    #undef VERSION
#endif
#define VERSION               "1.31"
#ifdef __PERL_VERSION__
    #define Perl              "/Perl"
#else
    #define Perl
#endif
#define ProgVersion           VERSION ""OsType ""Perl
#define ProductLO             0xff
#define ProductHI             0x16
#define Copyright \
    "\n(C) 2003-2006 Alex Soukhotine (2:5030/1157)\n    2007-2011 Stas Degteff (2:5080/102)\n    2009-2011 Michael Dukelsky (2:5020/1042)\n"

#ifndef DefaultConfig
    #ifdef __unix__
        #define DefaultConfig "/etc/ftn/rntrack.cfg"
    #else
        #define DefaultConfig "rntrack.cfg"
    #endif
#endif

#ifdef __unix__
    #define MsgExtension ".msg"
    #define PktExtension ".pkt"
    #define BsyExtension ".bsy"
    #define PntExtension ".pnt"
#else
    #define MsgExtension ".MSG"
    #define PktExtension ".PKT"
    #define BsyExtension ".BSY"
    #define PntExtension ".PNT"
#endif

#define MAXCFGLINE       4096
#define DELIMETERS       " \t"
#define STRDELIMETERS    "\t\""
#define MAXPOINTS        1024

#define LOGE             100
#define LOGW             101
#define LOGI             102
#define LOGN             103
#define LOGD             105

#define BUFF_SIZE        1024
#define SMALL_BUFF_SIZE  512

#endif
