/*
 *  RNtrack - FTN message tracker/router
 *
 *  fidoaddr.cpp - Work with FTN-addresses
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
 
#include        <string.h>
#include        "fidoaddr.hpp"
#include        <stdlib.h>
#include        <ctype.h>

#undef _DEBUG

/*--------------------------------------------------------------------------*/


FA::FA(const FA &r) {
   zone_v  = r.zone_v;
   net_v   = r.net_v;
   node_v  = r.node_v;
   point_v = r.point_v;
}



FA::FA(void){
   Clean();
}



/*--------------------------------------------------------------------------*/

int FACmp(unsigned int r1, unsigned int r2) {
   if (r1 & FA_ANYMASK) return TRUE;
   if (r2 & FA_ANYMASK) return TRUE;
   return ((r1 & 0xffff) == (r2 & 0xffff));
}

int FA::operator == (const FA &r) const {
int rc,rc2;

   rc = TRUE;
   if (zone_v & FA_NOTMASK) rc = !rc;
   if (r.zone_v & FA_NOTMASK) rc = !rc;
   rc2 = (FACmp(zone_v,r.zone_v) && FACmp(net_v,r.net_v) &&
          FACmp(node_v,r.node_v) && FACmp(point_v,r.point_v));
   return (rc == rc2);
}

int FA::operator != (const FA &r) const {
int rc,rc2;

   rc = TRUE;
   if (zone_v & FA_NOTMASK) rc = !rc;
   if (r.zone_v & FA_NOTMASK) rc = !rc;
   rc2 = (FACmp(zone_v,r.zone_v) && FACmp(net_v,r.net_v) &&
          FACmp(node_v,r.node_v) && FACmp(point_v,r.point_v));
   return (rc != rc2);
}

/*--------------------------------------------------------------------------*/


FA & FA::operator = (const FA &r){
   zone_v  = r.zone_v;
   net_v   = r.net_v;
   node_v  = r.node_v;
   point_v = r.point_v;
   return *this;
}


/*--------------------------------------------------------------------------*
 *
 *      General Zone/Net/Node/Point parser
 *
**/

unsigned int _ParseOneDigit(char *&p) {
unsigned int tmp;

   if (*p == ANYMASK_CHAR[0]) { p++; return FA_ANYMASK; }
   if (*p == LSTMASK_CHAR[0]) { p++; return FA_LSTMASK; }
   if (*p == TOMASK_CHAR[0]) { p++; return FA_TOMASK; }
   if (*p == FROMMASK_CHAR[0]) { p++; return FA_FROMMASK; }
   if (*p == OURMASK_CHAR[0]) { p++; return FA_OURMASK; }
   if (*p == SUBMASK_CHAR[0]) { p++; return FA_SUBMASK; }
   if (*p == NHOLDMASK_CHAR[0]) { p++; return FA_HOLDMASK; }
   if (*p == NHUBMASK_CHAR[0]) { p++; return FA_HUBMASK; }
   if (*p == NPVTMASK_CHAR[0]) { p++; return FA_PVTMASK; }
   if (*p == NDOWNMASK_CHAR[0]) { p++; return FA_DOWNMASK; }
   if (!isdigit((uchar)*p)) return FA_NOTDEF;
   tmp = atoi(p);
   while (isdigit((uchar)*p)) p++;
   if (tmp > 65535U) return FA_NOTDEF;
   return tmp;
}

unsigned int _ParseZone (char *&p) {
char *t;
unsigned int tmp;
// Parsing zone 'XX:'
   t = p;
   tmp = _ParseOneDigit(t);
   if (tmp == FA_NOTDEF) {
      return FA_NOTDEF;
   }
   if (tmp == FA_SUBMASK) {
      return FA_NOTDEF;
   }
   if (*t != ':') {
      return FA_NOTDEF;
   }
   p = t + 1;
   return tmp;
}


unsigned int _ParseNet (char *&p) {
char *t;
unsigned int tmp;

   t = p;
   tmp = _ParseOneDigit(t);

   if (tmp == FA_NOTDEF) {
      return FA_NOTDEF;
   }
   if (tmp == FA_SUBMASK) {
      return FA_NOTDEF;
   }
   if (*t != '/') {
      return FA_NOTDEF;
   }
   p = t + 1;
   return tmp;

}

unsigned int _ParseNode (char *&p) {
char *t;
unsigned int tmp;

   if (*p == '.') {  // catch '.XX'
      p++;
      return FA_NOTDEF;
   }
   t = p;
   tmp = _ParseOneDigit(t);
   if (tmp == FA_SUBMASK) {
      return FA_NOTDEF;
   }
   if (tmp != FA_NOTDEF) {
      if (*t != '.' && *t != '\0' && *t != ' ' && *t != '@') {
         p = t;
         return FA_NOTDEF;
      }
   }
   p = t;
   return tmp;
}

int FA::Parse(char *&p) {
int NotFlag;

   if (strlen(p) == 0) {
      zone_v = net_v = node_v = point_v = FA_NOTDEF;
      return FALSE;
   }
   while( *p == ' ') p++;
   NotFlag = FALSE;
   if (*p == NOTMASK_CHAR[0]) { // Found NOT flag. This flag is set _only_ on ZONE
      NotFlag = TRUE;
      p++;
   }
   zone_v = _ParseZone(p);
   net_v = _ParseNet(p);
   node_v = _ParseNode(p);

   if (*p == '.') {
      p++;
      point_v = _ParseOneDigit(p);
   } else {
      point_v = FA_NOTDEF;
   }

   if (node_v & FA_MASK) {
      if ((zone_v & FA_NOTDEF) && (net_v & FA_NOTDEF) && (point_v & FA_NOTDEF)) {
         zone_v = node_v;
         net_v = node_v;
         point_v = node_v;
      }
   }
// Now, check errors.
   if (point_v & FA_SUBMASK) {   // set point submask
   // I do not understand, who needs it...
   }
   
   if (!(zone_v & FA_NOTDEF) && (net_v & FA_NOTDEF)) { // zone exists but not a net.
      zone_v = FA_NOTDEF;
      node_v = FA_NOTDEF;
      point_v = FA_NOTDEF;
      while(*p > ' ') p++;
   }

   if (!(net_v & FA_NOTDEF) && (node_v & FA_NOTDEF)) { // net exists but not a node.
      zone_v = FA_NOTDEF;
      net_v = FA_NOTDEF;
      point_v = FA_NOTDEF;
      while(*p > ' ') p++;
   }
   if (*p == '@') { // skip domain.
      while(*p > ' ') p++;
   }
   if (*p > ' ') { // exists something not parsed...
      zone_v = FA_NOTDEF;
      net_v = FA_NOTDEF;
      node_v = FA_NOTDEF;
      point_v = FA_NOTDEF;
      while(*p > ' ') p++;
   }
   if ((node_v & FA_TOMASK) && !(point_v & FA_TOMASK)) {
      zone_v = FA_TOMASK;
      net_v = FA_TOMASK;
   }
   if (point_v == FA_NOTDEF && (zone_v != FA_NOTDEF && net_v != FA_NOTDEF &&
       node_v != FA_NOTDEF)) point_v = 0;
   if (NotFlag) {
      zone_v |= FA_NOTMASK;
   }
   return TRUE;
}

/*--------------------------------------------------------------------------*/

char *fatoa(unsigned int i, char *tmp) {
char *tmt;
   tmt = tmp;
   tmp[0] = '\0';
   if (i & FA_NOTMASK) {
      strcpy(tmp,NOTMASK_CHAR);
   }
   if (i & FA_ANYMASK) { strcat(tmp,ANYMASK_CHAR); return (tmp); }
   if (i & FA_NOTDEF) { strcat(tmp,"?"); return (tmp); }
   if (i & FA_LSTMASK) { strcat(tmp,LSTMASK_CHAR); return (tmp); }
   if (i & FA_FROMMASK) { strcat(tmp,FROMMASK_CHAR); return (tmp); }
   if (i & FA_TOMASK) { strcat(tmp,TOMASK_CHAR); return (tmp); }
   if (i & FA_OURMASK) { strcat(tmp,OURMASK_CHAR); return (tmp); }
   if (i & FA_SUBMASK) { strcat(tmp,SUBMASK_CHAR); return (tmp); }
   if (i & FA_HOLDMASK) { strcat(tmp,NHOLDMASK_CHAR); return (tmp); }
   if (i & FA_PVTMASK) { strcat(tmp,NPVTMASK_CHAR); return (tmp); }
   if (i & FA_DOWNMASK) { strcat(tmp,NDOWNMASK_CHAR); return (tmp); }
   if (i & FA_HUBMASK) { strcat(tmp,NHUBMASK_CHAR); return (tmp); }   
   if (tmp[0] != '\0') tmp++;
   sprintf(tmp,"%u",i & 0xffff);
   return tmt;
}

char *FA::ToStr(void) const {
static char buf[120];
char tmp[8];

    strcpy(buf,fatoa(zone_v,tmp));
    strcat(buf,":");
    strcat(buf,fatoa(net_v,tmp));
    strcat(buf,"/");
    strcat(buf,fatoa(node_v,tmp));
    if (point_v != 0 && (point_v & FA_NOTDEF) == 0) {
       strcat(buf,".");
       strcat(buf,fatoa(point_v,tmp));
    }
    return buf;
}

/*--------------------------------------------------------------------------*/

LogStream &operator <<(LogStream &os,FA const &f) {
    os << f.ToStr();
    return (os);
}

/*--------------------------------------------------------------------------*/

int FA::Valid(void) const {
   if ((zone_v & FA_NOTDEF) && (net_v & FA_NOTDEF) 
       && (node_v & FA_NOTDEF) && (point_v & FA_NOTDEF)) {
      return FALSE; 
   }
   else {
      return TRUE;
   }
}


void Parse_NetNode(char *netnode,word *zone,word *net,word *node,word *point) {
FA f;
   f.Parse(netnode);
   *zone = f.Zone() & 0xffff;
   *net = f.Net() & 0xffff;
   *node = f.Node() & 0xffff;
   *point = f.Point() & 0xffff;
}
