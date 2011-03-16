/*
 *  RNtrack - FTN message tracker/router
 *
 *  getopt.hpp - Parse command line paremeters
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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "getopt.hpp"

static int optionInd = 1;
static int optionOpt;
char * optionArg;

int ParseCmdArgs(int argc, char ** argv, char * opts)
{
    static int sp = 1;
    int c;
    char * cp;

    if(optionInd < argc && argv[optionInd][0] == '-' && argv[optionInd][1] ==
       '\0')
    {
        if((cp = strchr(opts, '-')) != NULL)
        {
            optionInd++;
            return '-';
        }
        else
        {
            optionInd++;
            return '?';
        }
    }

    if(sp == 1)
    {
        if(optionInd >= argc || argv[optionInd][0] != '-' ||
           argv[optionInd][1] == '\0')
        {
            return EOF;
        }
        else if(strcmp(argv[optionInd], "--") == 0)
        {
            optionInd++;
            return EOF;
        }
    }

    optionOpt = c = argv[optionInd][sp];

    if(c == ':' || (cp = strchr(opts, c)) == NULL)
    {
        fprintf(stderr, "%s: illegal option -- %c\n", argv[0], c);

        if(argv[optionInd][++sp] == '\0')
        {
            optionInd++;
            sp = 1;
        }

        return '?';
    }

    if(*++cp == ':')
    {
        if(argv[optionInd][sp + 1] != '\0')
        {
            optionArg = &argv[optionInd++][sp + 1];
        }
        else if(++optionInd >= argc)
        {
            fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0],
                    c);
            sp = 1;
            return '?';
        }
        else
        {
            optionArg = argv[optionInd++];
        }

        sp = 1;
    }
    else
    {
        if(argv[optionInd][++sp] == '\0')
        {
            sp = 1;
            optionInd++;
        }

        optionArg = NULL;
    }

    return c;
} /* getopt */
