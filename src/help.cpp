/*
 *  RNtrack - FTN message tracker/router
 *
 *  help.hpp - Help functions
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

#include <stdio.h>
#include "constant.hpp"
#include "help.hpp"

//#ifndef __WATCOMC__
#include <iostream>
using std::cout;
using std::flush;
//#else
//#include <iostream.h>
//#endif

void Hello(void)
{
    cout << "RNtrack " << ProgVersion;
#if defined (__PERL_VERSION__) && defined (__PERL_MAJOR__)
    cout << " (Perl " << __PERL_MAJOR__ << "." <<
            int((__PERL_VERSION__ % 1000000) / 1000) << 
            "." << __PERL_VERSION__ % 1000 << ") ";
//#if defined( __PERL_MAJOR__ ) && defined( __PERL_MINOR__ )
//   cout << " (Perl " << __PERL_MAJOR__ << "." << int( __PERL_MINOR__ / 1000)
// << "." << __PERL_MINOR__ % 1000 << ") ";
#endif
    cout << Copyright << "\n";
    cout << flush;
}

void Help(void)
{
    cout <<
    "Syntax: rntrack -c \"ConfigFile\" - To select configuration file\n";
    cout << "                -u              - Unpack outbound\n";
    cout <<
    "                -t              - Do ScanDir: with expired date of execution\n";
    cout << "                -?              - To view help text again\n";
    cout <<
    "                -h              - To view program version and command line options\n";
    cout << "                -v              - To view program version\n";
    cout << flush;
}
