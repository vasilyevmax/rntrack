/*
 *  RNtrack - FTN message tracker/router
 *
 *  parsetpl.hpp - Work with template files
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

#ifndef _PARSETPL_HPP_
#define _PARSETPL_HPP_

#include "fidoaddr.hpp"
#include "msg.hpp"
#include "configure.hpp"

class ScanDir;

#define TPLADD 4096

class Template
{
    char * TplName;
    FILE * fh;
    char * CurrLinePos;
    uint MaxBodySize;
    char * FName;
public:
    char * LastTplLine;
    cMSG * From;
    cMSG * To;
    ScanDir * sd;
    char * RoutedVia;
    char * Body;
    uint BodySize;
    Template();
    ~Template();
    int AddTok(char * T);
    void AddChar(char c);
    void AddStr(const char * c);
    void AddInt(int i);
    int GetOneLine(void);
    int ParseOneLine(void);
    int Parse(void);

    void SetMsg(cMSG & F, cMSG & T)
    {
        From = &F;
        To   = &T;
    }
    void SetMsg(cMSG & F)
    {
        From = &F;
        To   = &F;
    }
    bool Set(char * Name);
    int  Save(char * name, int Mode);
    int  Save(cMSG & m);
    void Normalise(void);
    void Clean(void);
};

char * StrAsTpl(cMSG & m, char * s);

#endif

