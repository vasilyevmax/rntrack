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

void Hello(void) {
   cout << "RNtrack " << ProgVersion << Copyright << "\n";
   cout << flush;
}

void Help(void) {
   cout << "Syntax: rntrack -c \"ConfigFile\"   - To select configuration file\n";
   cout << "                -u                - Unpack outbound\n";
   cout << "                -t                - Do ScanDir: with expired date of execution\n";
   cout << "                -h | -?           - To get this text again\n";
   cout << flush;
}
