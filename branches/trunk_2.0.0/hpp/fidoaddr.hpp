/*
 *  RNtrack - FTN message tracker/router
 *
 *  fidoaddr.hpp - Work with FTN-addresses
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

#ifndef FIDOADDR_HPP
#define FIDOADDR_HPP

#include <string.h>
#include "log.hpp"
#include "mytypes.hpp"

#define FA_NOTMASK     0x80000000U
#define FA_ANYMASK     0x40000000U
#define FA_LSTMASK     0x20000000U
#define FA_NOTDEF      0x10000000U
#define FA_FROMMASK    0x08000000U
#define FA_TOMASK      0x04000000U
#define FA_OURMASK     0x02000000U
#define FA_SUBMASK     0x01000000U
#define FA_HOLDMASK    0x00100000U
#define FA_HUBMASK     0x00200000U
#define FA_PVTMASK     0x00400000U
#define FA_DOWNMASK    0x00800000U

#define FA_BADACT      0xb1f00000U
#define FA_BADROUTE    0xfbf00000U
#define FA_BADMASK     0x1c000000U
#define FA_BADPKT      0xbff00000U

#define FA_MASK        0xeff00000U
#define FA_ALLMASK     0xfff00000U

#define TOMASK_CHAR    "%"
#define FROMMASK_CHAR  "$"
#define LSTMASK_CHAR   "#"
#define NHOLDMASK_CHAR "H"
#define NDOWNMASK_CHAR "D"
#define NHUBMASK_CHAR  "U"
#define NPVTMASK_CHAR  "P"
#define ANYMASK_CHAR   "*"
#define NOTMASK_CHAR   "!"
#define OURMASK_CHAR   "@"
#define SUBMASK_CHAR   "&"

class FA
{
private:
    dword zone_v;
    dword net_v;
    dword node_v;
    dword point_v;
public:
    int Parse(const char * & p);

    inline dword Zone()  const
    {
        return zone_v;
    }
    inline dword Net()   const
    {
        return net_v;
    }
    inline dword Node()  const
    {
        return node_v;
    }
    inline dword Point() const
    {
        return point_v;
    }
    inline void Clean(void)
    {
        zone_v = net_v = node_v = point_v = FA_NOTDEF;
    }
    inline int Masked(void)
    {
        return (zone_v & FA_MASK) || (net_v & FA_MASK) ||
               (node_v & FA_MASK) || (point_v & FA_MASK);
    }

    inline int MaskValid(void)
    {
        return !((zone_v & FA_BADMASK) || (net_v & FA_BADMASK) ||
                 (node_v & FA_BADMASK) ||
                 (!(point_v & FA_NOTDEF) && (point_v & FA_BADMASK)));
    }

    inline int ActValid(void)
    {
        return !((zone_v & FA_BADACT) || (net_v & FA_BADACT) ||
                 (node_v & FA_BADACT) || (point_v & FA_BADACT));
    }

    inline int RouValid(void)
    {
        return !((zone_v & FA_BADROUTE) || (net_v & FA_BADROUTE) ||
                 (node_v & FA_BADROUTE) || (point_v & FA_BADROUTE));
    }

    inline int PKTValid(void)
    {
        return !((zone_v & FA_BADPKT) || (net_v & FA_BADPKT) ||
                 (node_v & FA_BADPKT) || (point_v & FA_BADPKT));
    }

    inline int AnyMask(void)
    {
        return (zone_v & FA_ALLMASK) || (net_v & FA_ALLMASK) ||
               (node_v & FA_ALLMASK) || (point_v & FA_ALLMASK);
    }

    void Zone(dword i)
    {
        zone_v = i;
    }
    void Net(dword i)
    {
        net_v = i;
    }
    void Node(dword i)
    {
        node_v = i;
    }
    void Point(dword i)
    {
        point_v = i;
    }
    char * ToStr(void) const;

    FA(void);
    FA(const FA &);

    int operator ==(const FA & a) const;
    int operator !=(const FA & a) const;
    FA & operator =(const FA & a);
    int Valid(void) const;
};

char * fatoa(unsigned int i, char * t);

/*--------------------------------------------------------------------------*/

// LogStream & operator <<(LogStream & os, FA & f);
LogStream & operator <<(LogStream & os, FA const & f);

// void Parse_NetNode(char * netnode, word * zone, word * net, word * node,
//                    word * point);

#endif // FIDOADDR_HPP
