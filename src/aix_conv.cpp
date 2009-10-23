/*
 *  RNtrack - FTN message tracker/router
 *
 *  aix_conv.cpp - AIX byte order transform
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

#include "aix_conv.hpp"

#ifdef _AIX_CONV
short int RotateShort (short int s) {
char *c,b;
    c=(char *)& s;
    b=c[0];
    c[0]=c[1];
    c[1]=b;
    return s;
}

int RotateInt (int i) {
char *c,b;
    c=(char *)& i;
    b=c[0];
    c[0]=c[3];
    c[3]=b;
    b=c[1];
    c[1]=c[2];
    c[2]=b;
    return i;
}

int AIXConvPKTH (tPKTH &PKTH) {
    PKTH.FromNode=RotateShort(PKTH.FromNode);
    PKTH.ToNode=RotateShort(PKTH.ToNode);
    PKTH.Year=RotateShort(PKTH.Year);
    PKTH.Month=RotateShort(PKTH.Month);
    PKTH.Day=RotateShort(PKTH.Day);
    PKTH.Hour=RotateShort(PKTH.Hour);
    PKTH.Minute=RotateShort(PKTH.Minute);
    PKTH.Second=RotateShort(PKTH.Second);
    PKTH.Baud=RotateShort(PKTH.Baud);
    PKTH.c0002=RotateShort(PKTH.c0002);
    PKTH.FromNet=RotateShort(PKTH.FromNet);
    PKTH.ToNet=RotateShort(PKTH.ToNet);
    PKTH.FromZone=RotateShort(PKTH.FromZone);
    PKTH.ToZone=RotateShort(PKTH.ToZone);
    PKTH.AuxNet=RotateShort(PKTH.AuxNet);
    PKTH.c0100=RotateShort(PKTH.c0100);
    PKTH.c0001=RotateShort(PKTH.c0001);
    PKTH.FromZone2=RotateShort(PKTH.FromZone2);
    PKTH.ToZone2=RotateShort(PKTH.ToZone2);
    PKTH.FromPoint=RotateShort(PKTH.FromPoint);
    PKTH.ToPoint=RotateShort(PKTH.ToPoint);
    return 0;
}
#endif
