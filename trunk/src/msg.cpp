/*
 *  RNtrack - FTN message tracker/router
 *
 *  msg.cpp - Work with messages
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

#ifndef __unix__
#include <io.h>
#endif
#ifndef __GNUC__
#include <direct.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "constant.hpp"
#include "vars.hpp"
#include "log.hpp"
#include "nodelist.hpp"
#include "utils.hpp"
#include "aka.hpp"
#include "age.hpp"
#include "attach.hpp"
#include "msg.hpp"
#include <smapi/msgapi.h>
#include <smapi/progprot.h>
#include <smapi/prog.h>

#ifdef __WATCOMC__
#include <smapi/months.c>
#endif

#if defined(__sun__) || defined(__OSX__)
#define strftim strftime
#endif

// ---------------------------
//char months[][4] = {
//        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
//        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
//};

char *FromTime(time_t tmt) {
static char buf[40];
tm *t = localtime(&tmt);
   sprintf(buf,  "%02u %3.3s %02u  %02u:%02u:%02u",
                                   t->tm_mday, months_ab[t->tm_mon], t->tm_year % 100,
                                   t->tm_hour, t->tm_min, t->tm_sec);

   buf[19] = '\0';
   return buf;
}


time_t ToTime(char *txt) {
struct tm t;
char mon[4];
int i;
// struct tm *t2;
time_t tt;
 
   sscanf(txt, "%02u %3s %02u  %02u:%02u:%02u",
         &t.tm_mday, mon, &t.tm_year,
	 &t.tm_hour, &t.tm_min, &t.tm_sec
   );
													     
   t.tm_isdst = -1;
   t.tm_mon = 0;
   if (t.tm_year < 70) t.tm_year += 100;
   for (i = 0; i < 12; i++) {
      if (strcasecmp(months_ab[i],mon) == 0) {
         t.tm_mon = i;
	 break;
      }
  }
  tt = mktime(&t);
  return (tt!=(time_t)-1?tt:time(NULL));
}

#if 0

static int _mdays [13] =
            {
/* Jan */   0,
/* Feb */   31,
/* Mar */   31+28,
/* Apr */   31+28+31,
/* May */   31+28+31+30,
/* Jun */   31+28+31+30+31,
/* Jul */   31+28+31+30+31+30,
/* Aug */   31+28+31+30+31+30+31,
/* Sep */   31+28+31+30+31+30+31+31,
/* Oct */   31+28+31+30+31+30+31+31+30,
/* Nov */   31+28+31+30+31+30+31+31+30+31,
/* Dec */   31+28+31+30+31+30+31+31+30+31+30,
/* Jan */   31+28+31+30+31+30+31+31+30+31+30+31
            };

#define WOFC( a, b )    ( (uint)a | (((uint)b)<<8) )

time_t FMkTime(tm *pTm) {
unsigned int  Days;
int     Years;

   /*Get number of years since 1970*/
   Years = pTm->tm_year - 70;

   /*Calculate number of days during these years,*/
   /*including extra days for leap years         */
   Days = Years * 365 + ((Years + 1) / 4);

   /*Add the number of days during this year*/
   Days += _mdays [pTm->tm_mon] + pTm->tm_mday - 1;
   if((pTm->tm_year & 3) == 0 && pTm->tm_mon > 1)
       Days++;

   /*Convert to seconds, and add the number of seconds this day*/
   return(((time_t) Days * 86400L) + ((time_t) pTm->tm_hour * 3600L) +
          ((time_t) pTm->tm_min * 60L) + (time_t) pTm->tm_sec);
}
tm *FLocalTime(time_t *pt){
static struct tm   m;
int t = *pt;
int LeapDay;

   m.tm_sec  = (int) (t % 60); t /= 60;
   m.tm_min  = (int) (t % 60); t /= 60;
   m.tm_hour = (int) (t % 24); t /= 24;
   m.tm_wday = (int) ((t + 4) % 7);

   m.tm_year = (int) (t / 365 + 1);
   do {
      m.tm_year--;
      m.tm_yday = (int) (t - m.tm_year * 365 - ((m.tm_year + 1) / 4));
   } while(m.tm_yday < 0);
   m.tm_year += 70;

   LeapDay = ((m.tm_year & 3) == 0 && m.tm_yday >= _mdays [2]);

   for(m.tm_mon = m.tm_mday = 0; m.tm_mday == 0; m.tm_mon++)
        if(m.tm_yday < _mdays [m.tm_mon + 1] + LeapDay)
            m.tm_mday = m.tm_yday + 1 - (_mdays [m.tm_mon] + (m.tm_mon != 1 ? LeapDay : 0));

   m.tm_mon--;

   m.tm_isdst = -1;

    return(&m);
}




time_t ToTime(char *txt) {
tm t;
char mon[4];
int i;
time_t tt;

   sscanf(txt, "%02u %3s %02u  %02u:%02u:%02u",
                                   &t.tm_mday, mon, &t.tm_year,
                                   &t.tm_hour, &t.tm_min, &t.tm_sec
                                   );

   t.tm_isdst = 0;
   t.tm_mon = 0;
   if (t.tm_year < 70) t.tm_year += 100;
   for (i = 0; i < 12; i++) {
      if (stricmp(months[i],mon) == 0) {
         t.tm_mon = i;
         break;
      }
   }
   tt = mktime(&t);
//   if (daylight == 1) {
//      tt -= 60*60;
//   }
   return tt;
}

time_t FTime(time_t *p) {
time_t a;
time_t time_of_day;
char buffer[ 80 ];

    time_of_day = time( NULL );
    strftime( buffer, 80, "%d %h %y  %H:%M:%S",
	       localtime( &time_of_day ) );
   a = ToTime(buffer);
   if (p != NULL) *p = a;
   return a;
}
// ---------------------------

#endif
int Kludge::operator == (const Kludge &k) const {
   if (_Name == NULL && k._Name != NULL) return FALSE;
   if (_Name != NULL && k._Name == NULL) return FALSE;
   if (_Name != NULL && k._Name != NULL && stricmp(_Name,k._Name) != 0) return FALSE;
   if (_Body == NULL && k._Body != NULL) return FALSE;
   if (_Body != NULL && k._Body == NULL) return FALSE;
   if (_Body != NULL && k._Body != NULL && stricmp(_Body,k._Body) != 0) return FALSE;
   return TRUE;
}

void Kludge::Print(void) {
   if (_Name != NULL) Log.Level(LOGD) << "'" << _Name << "'";
   if (_Body != NULL) Log.Level(LOGD) << " --- '" << _Body << "'";;
   Log.Level(LOGD) << EOL;
}

int Kludge::Save(FILE *fh) {
   if (_Name != NULL && strlen(_Name) != 0) {
      if (fwrite(_Name,strlen(_Name),1,fh) != 1) {
         Log.Level(LOGD) << "Kludge::Save!--1>" << EOL;
         return FALSE;
      }
   }
   if (_Body != NULL && strlen(_Body) != 0) {
      if (fwrite(" ",1,1,fh) != 1) {
         Log.Level(LOGD) << "Kludge::Save!--2>" << EOL;
         return FALSE;
      }
      if (fwrite(_Body,strlen(_Body),1,fh) != 1) {
         Log.Level(LOGD) << "Kludge::Save!--3>" << EOL;
         return FALSE;
      }
   }
   if (fwrite("\r",1,1,fh) != 1) {
         Log.Level(LOGD) << "Kludge::Save!--4>" << EOL;
      return FALSE;
   }
   return TRUE;
}

Kludge::Kludge(char *N, char *B) { 
   _Name = NULL;
   _Body = NULL;
   Set(N,B);
}

Kludge::Kludge(char *Txt) { 
char *tmt;
char *p, *p2, *s;

   _Name = NULL;
   _Body = NULL;
   CHP = 310;
   if (strlen(Txt) == 0) return;
   tmt = strdup(Txt);
   p = tmt + strlen(tmt) - 1;
   while (p != tmt && *p == ' ') {
      *p = '\0';
      p--;
   }
   CHP = 311;
   if (strlen(tmt) == 0) {
      free(tmt);
      return;
   }
   CHP = 312;
   p = tmt;
   s = tmt;
   while (*s != ' ' && *s != '\0') s++;
   if (*s == '\0') {
      p2 = NULL;
   } else {
      *s = '\0';
      s++;
      while (*s == ' ') s++;
      p2 = s;
   }
   CHP = 313;
   if (p2 != NULL && strstr(p2,"* Origin:") == p2) { // Work around for ' * Origin:'
      CHP = 314;
      Set(" * Origin:", p2+10);
   } else {
      Set(p,p2);
   }
   free(tmt);
   CHP = 315;
}

void Kludge::Set(char *N, char *B) { 
char * MY_N;  // _N is defined in NetBSD system headers ...
char * MY_B;
    if (N != NULL ) {
      MY_N = strdup(N);
   } else {
      MY_N = NULL;
   }
   if (B != NULL ) {
      MY_B = strdup(B);
   } else {
      MY_B = NULL;
   }
   if (_Name != NULL) free(_Name);
   if (_Body != NULL) free(_Body);
   _Name = MY_N;
   _Body = MY_B; 
}


Kludge::~Kludge() { 
// printf("Kludge destroyed\n");
   Clear();
}

void Kludge::Clear(void) { 
   if (_Name != NULL) {
      free(_Name); 
      _Name = NULL;
   }
   if (_Body != NULL) {
      free(_Body); 
      _Body = NULL;
   }
}

void Kludge::Recode(char *RecodeTable) {
char *tmt;

   if (_Body != NULL) {
      tmt = _Body;
      while (*tmt != '\0') {
         *tmt = RecodeTable[(unsigned char)*tmt];
         tmt++;
      }
   }

   if (_Name != NULL) {
      tmt = _Name;
      while (*tmt != '\0') {
         *tmt = RecodeTable[(unsigned char)*tmt];
         tmt++;
      }
   }
}


// ---------------------------


cMSG::cMSG() {
   _Body = NULL;
   Clear();
}

// ---------------------------

cMSG::~cMSG() {
   if (_Body != NULL) free (_Body);
   _Klu.Clear();
}   

// ---------------------------

void cMSG::Clear(void) {
   CHP = 315020;
   if (_Body != NULL) {
      CHP = 315021;
      free(_Body);
   }
   _Body = NULL;
   CHP = 315022;
   memset(_Subject,0,72);
   memset(_FromName,0,36);
   memset(_ToName,0,36);
   memset(_Reserved,0,8);
   memset(_RoutedVia,0,128);
   memset(_AreaName,0,128);
   CHP = 315023;
   _FromAddr.Clean();
   CHP = 315024;
   _ToAddr.Clean();
   CHP = 315025;
   fNoZone = 1;
   fEmpty = 1;
   _Cost = 0;
   _TimesRead = 0;
   _ReplyTo = 0;
   _NextReply = 0;
   fChanged = fPrivate = fCrash = fReceived = fSend =
   fFileAttach = fTransit = fOrphan = fKillSend = fLocal =
   fHold = fFileRequest = fRRQ = fIRR = fARQ = fFURQ = fDIR =
   fIMM = fCFM = fTFS = fKFS  = fEchomail = fScanned = fLok = 
   fAS = 0;
   CHP = 315026;
   _Klu.Clear();
   CHP = 315028;
}

// ---------------------------

unsigned long MsgID(void) {
static unsigned int LastMSGID = 0;
   return ((time(NULL) << 3) + LastMSGID++);
}
// ---------------------------


void cMSG::Normalise(void) {
char *tmt;
IndBiList<Kludge>::ElemPtr Klu;
Kludge *TKlu;
char Ad1[500],Ad2[50];
FA f;
char Buff[4096];
int fIntlE;
int fMsgidE;
int fFlagsE;
int fFromptE;
int fToptE;

   CHP = 31501;
   fIntlE = FALSE;
   fMsgidE = FALSE;
   fFlagsE  = FALSE;
   fFromptE = FALSE;
   fToptE = FALSE;
   CHP = 31502;
   if ((_FromAddr.Zone() & FA_NOTDEF) && UseOwnZone) {
      _FromAddr.Zone(FA_ANYMASK);
      _FromAddr.Zone(GetMyAka(_FromAddr).Zone());
   }
   if ((_ToAddr.Zone() & FA_NOTDEF) && UseOwnZone) {
      _ToAddr.Zone(FA_ANYMASK);
      _ToAddr.Zone(GetMyAka(_ToAddr).Zone());
   }

   Klu = _Klu.GetFirst();
   CHP = 31503;
   while (Klu != NULL) {
      CHP = 31504;
      if (Klu->Name() != NULL) {
         CHP = 31505;
         if (stricmp(Klu->Name(),"\1INTL") == 0) {
            if ((_FromAddr.Zone() & FA_NOTDEF) || (_ToAddr.Zone() & FA_NOTDEF)) {
               Klu->Set(NULL,NULL);
            } else {
               CHP = 31506;
               fIntlE = TRUE;
               f = _FromAddr;
               f.Point(0);       
               strcpy(Ad1,f.ToStr());
               f = _ToAddr;
               f.Point(0);       
               strcpy(Ad2,f.ToStr());
               sprintf(Buff,"%s %s",Ad2,Ad1);
               CHP = 31507;
               Klu->Set("\1INTL",Buff);
               CHP = 31508;
            }
         } else if (stricmp(Klu->Name(),"\1MSGID:") == 0) {
            CHP = 31509;
            fMsgidE = TRUE;
            if (fChanged) {
               if (_FromAddr.Zone() & FA_NOTDEF) {
                  Klu->Set(NULL,NULL);
               } else {
                  CHP = 31510;
                  strcpy(Ad1,_FromAddr.ToStr());
                  sprintf(Buff,"%s %08lx",Ad1,MsgID());
                  CHP = 31511;
                  Klu->Set("\1MSGID:",Buff);
                  CHP = 31512;
               }
            }
         } else if (stricmp(Klu->Name(),"\1FMPT") == 0) {
            CHP = 31513;
            fFromptE = TRUE;
            if (_FromAddr.Point() & 0xffff) {
               CHP = 31514;
               sprintf(Buff,"%u",(word) (_FromAddr.Point() & 0xffff));
               CHP = 31515;
               Klu->Set("\1FMPT",Buff);
               CHP = 31516;
            } else {
               CHP = 31517;
               Klu->Set(NULL,NULL);
               CHP = 31518;
            }
         } else if (stricmp(Klu->Name(),"\1TOPT") == 0) {
            CHP = 31519;
            fToptE = TRUE;
            if (_ToAddr.Point() & 0xffff) {
               CHP = 31520;
               sprintf(Buff,"%u",(word) (_ToAddr.Point() & 0xffff));
               CHP = 31521;
               Klu->Set("\1TOPT",Buff);
               CHP = 31522;
            } else {
               CHP = 31523;
               Klu->Set(NULL,NULL);
               CHP = 31524;
            }
         } else if (stricmp(Klu->Name()," * Origin:") == 0) {
            CHP = 31525;
            strcpy(Buff,Klu->Body());
            tmt = strrchr(Buff,'(');
            CHP = 31526;
            if (tmt != NULL) *tmt = '\0';
            strcat(Buff,"(");
            strcat(Buff,_FromAddr.ToStr());
            strcat(Buff,")");
            CHP = 31527;
            Klu->Set(" * Origin:",Buff);
            CHP = 31528;
         } else if (stricmp(Klu->Name(),"\1FLAGS") == 0) {
            CHP = 31529;
            fFlagsE = TRUE;
            if (strlen(SomeFlagsToStr(Ad1)) != 0) {
               CHP = 31530;
               Klu->Set("\1FLAGS",Ad1);
               CHP = 31531;
            } else {
               CHP = 31532;
               Klu->Set(NULL,NULL);
               CHP = 31533;
            }
            CHP = 31534;
         }
         CHP = 31535;
      }
      CHP = 31536;
      Klu++;
      CHP = 31537;
   }

   CHP = 31547;
   if (ForceINTL && (!fIntlE)) {
      if ((!(_FromAddr.Zone() & FA_NOTDEF)) && (!(_ToAddr.Zone() & FA_NOTDEF))) {
         CHP = 31548;
         f = _FromAddr;
         f.Point(0);       
         strcpy(Ad1,f.ToStr());
         f = _ToAddr;
         f.Point(0);       
         strcpy(Ad2,f.ToStr());
         sprintf(Buff,"\1INTL %s %s",Ad2,Ad1);
         CHP = 31549;
         TKlu = new Kludge(Buff);
         _Klu.AddToEnd(TKlu);
         CHP = 31550;
      }
   }

   if (!fMsgidE) {
      CHP = 31551;
      if (!(_FromAddr.Zone() & FA_NOTDEF)) {
         strcpy(Ad1,_FromAddr.ToStr());
         sprintf(Buff,"\1MSGID: %s %08lx",Ad1,MsgID());
         CHP = 31552;
         TKlu = new Kludge(Buff);
         _Klu.AddToEnd(TKlu);
      }
      CHP = 31553;
   }

   if ((_FromAddr.Point() & 0xffff) && (!fFromptE)) {
      CHP = 31554;
      sprintf(Buff,"\1FMPT %u",(word)(_FromAddr.Point() & 0xffff));
      CHP = 31555;
      TKlu = new Kludge(Buff);
      _Klu.AddToEnd(TKlu);
      CHP = 31556;
   }

   if ((_ToAddr.Point() & 0xffff) && (!fToptE)) {
      CHP = 31557;
      sprintf(Buff,"\1TOPT %u",(word)(_ToAddr.Point() & 0xffff));
      CHP = 31558;
      TKlu = new Kludge(Buff);
      _Klu.AddToEnd(TKlu);
      CHP = 31559;
   }

   if (strlen(SomeFlagsToStr(Ad1)) != 0 && (!fFlagsE)) {
      CHP = 31560;
      sprintf(Buff,"\1FLAGS %s",Ad1);
      CHP = 31561;
      TKlu = new Kludge(Buff);
      _Klu.AddToEnd(TKlu);
      CHP = 31562;
   }

   CHP = 31563;
//   NewVia.Clear();

}      



void cMSG::AddKludge(char *&Txt) {
char *tmt, *tmt2;
char *p, *p2, *s,*s2;
FA tAddr;
Kludge *TKlu;

   CHP = 300;
   if (strlen(Txt) == 0) return;
   p = Txt;
   while (*Txt != '\0' && *Txt != '\n' && *Txt != '\r') Txt++;
   CHP = 302;
   tmt = (char *) malloc(Txt - p + 1);
   CheckMem(tmt);
   CHP = 303;
   strncpy(tmt,p,Txt - p);
   tmt[Txt - p] = '\0';

// Skip one eol after kludge.
   if (Txt[0] != '\0') {
      if ((Txt[0] == '\n' && Txt[1] == '\r')
        || (Txt[0] == '\r' && Txt[1] == '\n')) {
         Txt += 2;
      } else {
         if (*Txt == '\n' || *Txt == '\r') Txt++;
      }
   }
   CHP = 304;
   p = tmt + strlen(tmt) - 1;
   while (p != tmt && *p == ' ') {
      *p = '\0';
      p--;
   }
   CHP = 305;
   if (strlen(tmt) == 0) {
      free(tmt);
      return;
   }
   CHP = 306;
   tmt2 = strdup(tmt);
   p = tmt;
   s = tmt;
   while (*s != ' ' && *s != '\0') s++;
   if (*s == '\0') {
      p2 = "\0";
   } else {
      *s = '\0';
      s++;
      while (*s == ' ') s++;
      p2 = s;
   }

Log.Level(LOGD) << "Split kludge. p == '" << p << "', p2 == '" << p2 << "'" << EOL;

   CHP = 307;
   if (*p == '\0' && strstr(p2,"* Origin:") == p2 && fEchomail) { // Origin (
      CHP = 30909;
      s = strrchr(p2,'(');
      s2 = strrchr(p2,')');
      if (s2 != NULL) *s2 = '\0';
      CHP = 30910;
      tAddr.Clean();
      if (s != NULL) {
         s++;
        tAddr.Parse(s);
      }
      CHP = 30911;
      if (s2 != NULL) *s2 = ')';
      CHP = 30912;
      if (tAddr.Valid()) {
         Log.Level(LOGD) << "Parse Origin: FromAddr == '" << tAddr << "'" << EOL;
         _FromAddr.Zone(tAddr.Zone());
         _FromAddr.Net(tAddr.Net());
         _FromAddr.Node(tAddr.Node());
         _FromAddr.Point(tAddr.Point());
      }
      CHP = 30913;

   } else if (stricmp(p,"\1FMPT") == 0) {   // FMPT <int> Kludge.
      _FromAddr.Point(atoi(p2));
   } else if (stricmp(p,"\1TOPT") == 0) {  // TOPT <int> Kludge
      _ToAddr.Point(atoi(p2));
   } else if (stricmp(p,"\1INTL") == 0) { // INTL ToAddr FromAddr
      tAddr.Parse(p2);
      Log.Level(LOGD) << "Parse INTL: ToAddr   == '" << tAddr << "'" << EOL;
      if (tAddr.Valid()) {
         _ToAddr.Zone(tAddr.Zone());
         _ToAddr.Net(tAddr.Net());
         _ToAddr.Node(tAddr.Node());
      }
      tAddr.Parse(p2);
      Log.Level(LOGD) << "Parse INTL: FromAddr == '" << tAddr << "'" << EOL;
      if (tAddr.Valid()) {
         _FromAddr.Zone(tAddr.Zone());
         _FromAddr.Net(tAddr.Net());
         _FromAddr.Node(tAddr.Node());
      }
   } else if (stricmp(p,"\1FLAGS") == 0) { // FLAGS Flg [FLG]
      p = strtok(p2," ");
      while (p != NULL) {
         if (stricmp(p,"DIR") == 0) {
            fDIR = 1;
         } else if (stricmp(p,"IMM") == 0) {
           fIMM = 1;
         } else if (stricmp(p,"TFS") == 0) {
           fTFS = 1;
         } else if (stricmp(p,"KFS") == 0) {
           fKFS = 1;
         } else if (stricmp(p,"PVT") == 0) {
           fPrivate = 1;
         } else if (stricmp(p,"HLD") == 0) {
           fHold = 1;
         } else if (stricmp(p,"CRA") == 0) {
           fCrash = 1;
         } else if (stricmp(p,"K/S") == 0) {
           fKillSend = 1;
         } else if (stricmp(p,"SNT") == 0) {
           fSend = 1;
         } else if (stricmp(p,"RCV") == 0) {
           fReceived = 1;
         } else if (stricmp(p,"FIL") == 0) {
           fFileAttach = 1;
         } else if (stricmp(p,"FRQ") == 0) {
           fFileRequest = 1;
         } else if (stricmp(p,"RRQ") == 0) {
           fRRQ = 1;
         } else if (stricmp(p,"CFM") == 0) {
           fCFM = 1;
         } else if (stricmp(p,"LOK") == 0) {
           fLok = 1;
         } else if (stricmp(p,"A/S") == 0) {
           fAS = 1;
         }
         p = strtok(NULL," ");
      }
   } else if (stricmp(p,"\1MSGID:") == 0) { // MSGID: <SomeId>
   // from MSGID: we take only missed parameters.
      tAddr.Parse(p2);
      if (tAddr.Valid()) {
         Log.Level(LOGD) << "MSGID is valid. FTN addr == '" << tAddr << "'" << EOL;
         if (_ToAddr.Zone() & FA_NOTDEF) {
            _ToAddr.Zone(tAddr.Zone());
         }
         if (_FromAddr.Zone() & FA_NOTDEF) {
            _FromAddr.Zone(tAddr.Zone());
         }
         if (_FromAddr.Net() & FA_NOTDEF) {
            _FromAddr.Net(tAddr.Net());
         }
         if (_FromAddr.Node() & FA_NOTDEF) {
            _FromAddr.Node(tAddr.Node());
         }
         if (_FromAddr.Point() & FA_NOTDEF) {
            _FromAddr.Point(tAddr.Point());
         }
      }
   }

   CHP = 308;
   TKlu = new Kludge(tmt2);
   _Klu.AddToEnd(TKlu);
   CHP = 308001;
   free(tmt);
   CHP = 308002;
   free(tmt2);
   CHP = 309;
}


// ---------------------------

void cMSG::Recode(char *RecodeTable){
char *tmt;
IndBiList<Kludge>::ElemPtr Klu;
int i;

   if (_Body != NULL) {
      tmt = _Body;
      while (*tmt != '\0') {
         *tmt = RecodeTable[(unsigned char)*tmt];
         tmt++;
      }
   }

   for (i = 0; i < 72; i++) {
      _Subject[i] = RecodeTable[(unsigned char)_Subject[i]];
   }

   for (i = 0; i < 36; i++) {
      _FromName[i] = RecodeTable[(unsigned char)_FromName[i]];
   }

   for (i = 0; i < 36; i++) {
      _ToName[i] = RecodeTable[(unsigned char)_ToName[i]];
   }

   Klu = _Klu.GetFirst();
   while (Klu != NULL) {
      Klu->Recode(RecodeTable);
      Klu++;
   }
}


unsigned int cMSG::LoopCount(char *LS) {
IndBiList<Kludge>::ElemPtr Klu;
int lc;

   lc = 0;

//   Log.Level(LOGD) << "------------------------------------------------------" << EOL;
//   Log.Level(LOGD) << "Search loop string '" << LS << "'" << EOL;
//   Log.Level(LOGD) << "------------------------------------------------------" << EOL;
   Klu = _Klu.GetFirst();
   while (Klu != NULL) {
      if (LS != NULL && Klu->Name() != NULL && stricmp(Klu->Name(),"\1VIA") == 0 
          && Klu->Body() != NULL && strstr(Klu->Body(),LS) != NULL) lc++;
      Klu++;
   }
   return lc;
}
// ---------------------------

unsigned int cMSG::AttachSize(void) {
int i;
   i = GetAttSize(*this);
   if (i == -1) return 0;
   return i;
}

// ---------------------------
unsigned int cMSG::Lines(void) {
unsigned int i;
char *tmt;
   i = 0;
   tmt = _Body;
   if (tmt == NULL) return 0;
   while (*tmt != '\0') {
      if (*tmt == '\r') i++;
      tmt++;
   }
   if (tmt != _Body && (*(tmt-1) != '\r')) i++;
   return i;
}

unsigned int cMSG::Bytes(void) {
   if (_Body == NULL) return 0;
   return strlen(_Body);
}
// ---------------------------
void cMSG::SetBody(char *Txt, unsigned int Len) {

   _Body = (char *) malloc(Len + 1);
   memset(_Body,0,Len + 1);
   memcpy(_Body,Txt,Len);
   fEmpty = 0;
}

// ---------------------------
char *cMSG::FlagsToStr(char *Str) {
   Str[0] = '\0';
   if (fPrivate) strcat(Str,"Pvt ");
   if (fCrash) strcat(Str,"Cra ");
   if (fReceived) strcat(Str,"Rcv ");
   if (fSend) strcat(Str,"Snt ");
   if (fFileAttach) strcat(Str,"Att ");
   if (fTransit) strcat(Str,"Trn ");
   if (fOrphan) strcat(Str,"Orp ");
   if (fKillSend) strcat(Str,"K/S ");
   if (fLocal) strcat(Str,"Loc ");
   if (fHold) strcat(Str,"Hld ");
   if (fFileRequest) strcat(Str,"FRQ ");
   if (fRRQ) strcat(Str,"RRQ ");
   if (fIRR) strcat(Str,"IRR ");
   if (fARQ) strcat(Str,"ARQ ");
   if (fFURQ) strcat(Str,"FURQ ");
   if (fDIR) strcat(Str,"Dir ");
   if (fIMM) strcat(Str,"Imm ");
   if (fCFM) strcat(Str,"Cfm ");
   if (fTFS) strcat(Str,"TFS ");
   if (fKFS) strcat(Str,"KFS ");
   if (fScanned) strcat(Str,"Scn ");
   if (fLok) strcat(Str,"Lok ");
   if (fAS) strcat(Str,"A/S ");
   if (Str[0] != '\0') Str[strlen(Str)-1] = '\0';
   return Str;
}

// ---------------------------

char *cMSG::SomeFlagsToStr(char *Str) {
   Str[0] = '\0';
   if (fDIR) strcat(Str,"DIR ");
   if (fIMM) strcat(Str,"IMM ");
   if (fCFM) strcat(Str,"CFM ");
   if (fTFS) strcat(Str,"TFS ");
   if (fKFS) strcat(Str,"KFS ");
   if (fLok) strcat(Str,"LOK ");
   if (fAS) strcat(Str,"A/S ");
   if (Str[0] != '\0') Str[strlen(Str)-1] = '\0';
   return Str;
}

// ---------------------------

void cMSG::ParseMem(char *Buff) {
char *tmt1, *tmt2;
int NewLine;
char BuffForSearch[128];

   CHP = 229;
   if (Buff == NULL || *Buff == '\0') {
      if (UseOwnZone && (_FromAddr.Zone() & FA_NOTDEF)) {
         _FromAddr.Zone(FA_ANYMASK);
         _FromAddr.Zone(GetMyAka(_FromAddr).Zone());
         _ToAddr.Zone(FA_ANYMASK);
         _ToAddr.Zone(GetMyAka(_ToAddr).Zone());
      }
      return;
   }

   CHP = 230;
   tmt1 = Buff;

// Check echomail.
   if (tmt1[0] == 'A' && tmt1[1] == 'R' && tmt1[2] == 'E' && 
       tmt1[3] == 'A' && tmt1[4] == ':') {
      strncpy(_AreaName,&tmt1[5],127);
      _AreaName[127] = '\0';
      tmt2 = strchr(_AreaName,'\n');
      if (tmt2 != NULL) *tmt2 = '\0';
      tmt2 = strchr(_AreaName,'\r');
      if (tmt2 != NULL) *tmt2 = '\0';
      AddKludge(tmt1);
      fEchomail = 1;
   }

// ok. Now copy message and parse kludges.
// Fucked FTN standarts... 
   _Body = (char *) malloc(strlen(tmt1)+1);
   CheckMem(_Body);
   tmt2 = _Body;
   NewLine = TRUE;
   while (*tmt1 != '\0') {
      // 1-st. Replace all 0A0D, 0D0A, smth0Asmth to 0D
      if (tmt1[0] == '\n' && tmt1[1] == '\r') {
         tmt1++;
      } else if (tmt1[0] == '\r' && tmt1[1] == '\n') {
         tmt1[1] = '\r';
         tmt1++;
      } else if (*tmt1 == '\n') {
         tmt1[0] = '\r';
      }

      if (*tmt1 == '\r') {
         NewLine = TRUE;
         *tmt2 = *tmt1;
         tmt2++; tmt1++;
         continue;
      } 
      if (NewLine == TRUE) { // All kludges shoul be start from begin of string.
         strncpy(BuffForSearch,tmt1,126);
	 BuffForSearch[127] = '\0';
         nls_strupr(BuffForSearch);
         if ((strstr(BuffForSearch,"SEEN-BY:") == BuffForSearch)
            || (strstr(BuffForSearch," * ORIGIN:") == BuffForSearch)
            || (strstr(BuffForSearch,"--- ") == BuffForSearch)
            || (strstr(BuffForSearch,"---\n") == BuffForSearch)
            || (strstr(BuffForSearch,"---\r") == BuffForSearch)) {
            AddKludge(tmt1);
            continue;
         } else if (*tmt1 == '\1') {
            AddKludge(tmt1);
            continue;
         }
      }
      NewLine = FALSE;
      *tmt2 = *tmt1;
      tmt2++; tmt1++;
      continue;
   }
   *tmt2 = '\0';
   if (strlen(_Body) != 0) fEmpty = 0;

// If we have not received the Zone for this letter - we shall 
// receive it in the magic way.
   if (UseOwnZone) {
      if (_FromAddr.Zone() & FA_NOTDEF) {
         _FromAddr.Zone(FA_ANYMASK);
         _FromAddr.Zone(GetMyAka(_FromAddr).Zone());
      }
      if (_ToAddr.Zone() & FA_NOTDEF) {
         _ToAddr.Zone(FA_ANYMASK);
         _ToAddr.Zone(GetMyAka(_ToAddr).Zone());
      }
   }
   CHP = 236;
}

// ---------------------------

void cMSG::AddOurVia(void) {
time_t t;
char Buff[1024];
char *tmt;
struct tm *tt;

   DelLastOurVia();
   Buff[0] = '\0';
   t = time(NULL);
   tt = localtime(&t);
   if (UTC == 99) {
      UTC = tzoffset();
   }
   
   if (NewVIAType == FALSE) {
      sprintf(Buff,"\1Via %s RNtrack %s ", GetMyAka(_ToAddr).ToStr(),ProgVersion);
      strftime(Buff+strlen(Buff),80,"%d %b %Y %H:%M:%S",localtime(&t));
      if (UTC != 99) {
         sprintf(Buff+strlen(Buff)," UTC%+03d00",UTC);
      }
   } else {
      sprintf(Buff,"\1Via %s @", GetMyAka(_ToAddr).ToStr());
      if (UTC != 99) {
         t = t - UTC * (60*60);
      }
      strftime(Buff+strlen(Buff),80,"%Y%m%d.%H%M%S",localtime(&t));
      if (UTC != 99) {
         strcat(Buff,".UTC");
      }
      sprintf(Buff+strlen(Buff)," RNtrack %s",ProgVersion);
   }
   tmt = Buff;
   AddKludge(tmt);
}

void cMSG::DelLastOurVia(void) {
char Buff[1024];
IndBiList<Kludge>::ElemPtr Klu;


   Klu = _Klu.GetLast();
   sprintf(Buff,"%s ", GetMyAka(_ToAddr).ToStr());
   if (Klu != NULL) {
      if (Klu->Name() != NULL && Klu->Body() != NULL) {
         if (stricmp(Klu->Name(),"\1Via") == 0 && 
             (strstr(Klu->Body(),Buff) == Klu->Body()) &&
             (strstr(Klu->Body()," RNtrack ") != NULL)) {
            if (LogLevel >= 5) {
               Log.Level(LOGD) << "Delete our via. Via is '" << Buff << "'" << EOL;
               Log.Level(LOGD) << " Via (or Klu) in msg: " << Klu->Name() << " '--' " << Klu->Body() << EOL;
            }
            _Klu.Remove(Klu);
         }
      }
   }
}

// ---------------------------

cMSG & cMSG::operator =  ( const cMSG &m ){

   _FromAddr = m._FromAddr;
   _ToAddr = m._ToAddr;
   _Body = NULL;
   if (m._Body != NULL) {
      _Body = strdup(m._Body);
   }
   strncpy(_Subject,m._Subject,72);
   strncpy(_FromName,m._FromName,36);
   strncpy(_ToName,m._ToName,36);
   _Cost = m._Cost;
   _TimesRead = _TimesRead;
   _ReplyTo = m._ReplyTo;
   _NextReply = m._NextReply;
   memcpy(_Reserved,m._Reserved,8);
   fEchomail = m.fEchomail; fNoZone = m.fNoZone; fChanged = m.fChanged;
   fPrivate = m.fPrivate;   fCrash = m.fCrash;   fReceived = m.fReceived;
   fSend = m.fSend;   fFileAttach = m.fFileAttach;   fTransit = m.fTransit;
   fOrphan = m.fOrphan;   fKillSend = m.fKillSend;   fLocal = m.fLocal;
   fHold = m.fHold;   fFileRequest = m.fFileRequest;   fRRQ = m.fRRQ;
   fIRR = m.fIRR;   fARQ = m.fARQ;   fFURQ = m.fFURQ;   fDIR  = m.fDIR;
   fIMM = m.fIMM;   fCFM = m.fCFM;   fEmpty = m.fEmpty;   fTFS = m.fTFS;
   fKFS = m.fKFS;   fScanned = m.fScanned; fLok = m.fLok;
   fAS = m.fAS;
   return *this;
}
   
// ---------------------------

void cMSG::Print(void) {
char Buff[128];

   Log.Level(LOGD) << "------------------------------------------------------" << EOL;
   Log.Level(LOGD) << "Message is " << (fEmpty ? "Empty" : "not Empty") << EOL;
   Log.Level(LOGD) << "Message is " << (fEchomail ? "Echomail" : "Netmail") << EOL;
   if (fEchomail) {
      Log.Level(LOGD) << "Area: " << _AreaName << EOL;
   }
   Log.Level(LOGD) << "Kludges:" << EOL;
   INDBILIST_FOREACH(Kludge,_Klu,Klu) Klu->Print();
   Log.Level(LOGD) << "------------------------------------------------------" << EOL;
   Log.Level(LOGD) << "From : " << _FromName << " (" << _FromAddr << ")" << EOL;
   Log.Level(LOGD) << "To   : " << _ToName << " (" << _ToAddr << ")" << EOL;
   Log.Level(LOGD) << "Attr : " << FlagsToStr(Buff) << EOL;
   Log.Level(LOGD) << "Subj : " << _Subject << EOL;
   Log.Level(LOGD) << "Time : " << FromTime(_Time) << EOL;
   Log.Level(LOGD) << "Age  : " << AgeIs(_Time) << EOL;
   Log.Level(LOGD) << "Bytes: " << Bytes() << EOL;
   Log.Level(LOGD) << "Lines: " << Lines() << EOL;
//   Log.Level(LOGD) << "Loop: " << _LoopCount << EOL;
   Log.Level(LOGD) << "------------------------------------------------------" << EOL;
}
