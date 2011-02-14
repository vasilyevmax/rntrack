/*
 *  RNtrack - FTN message tracker/router
 *
 *  nodelist.hpp - Work with nodelists
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

#ifndef _NODELIST_HPP_
#define _NODELIST_HPP_

#include "fidoaddr.hpp"

#define DefaultIndex   "rntrack.ndl"           // default index file
#define NdlSign        0xfeda3033U             // Signature of nodelist index
#define A_NONE         0x00000000U
#define A_DOWN         0x01000000U
#define A_HOLD         0x02000000U
#define A_HUB          0x03000000U
#define A_HOST         0x04000000U
#define A_PVT          0x05000000U
#define A_REGION       0x06000000U
#define A_NONODE       0xffffffffU
#define A_MASK         0xffff0000U

extern char *NodelistPath;

typedef struct {
   char Name[512];
   time_t  Time;
   dword   StartZone;
} NodeListElem;

typedef struct _Nch {
   dword         Number;
   struct _Nch  *Sub;
} Nch;


class NodeLists {
   NodeListElem *NList;
   int          Lists;
   char         *IndexName;
   Nch          *Index;
   int          StartZone;
private:
   bool CompileNeed(void);
   bool Compile(void);
   bool LoadOneIndex(FILE *fh, Nch *&Ind);
   Nch *Srch(Nch *Addr, unsigned int Number);
public:
   NodeLists();
   ~NodeLists();
   int AddNodelist(char *tmt, int TempZone);
   void IndexFile(char *Name);
   void Print(void);
   bool Load(void);
   unsigned int ExistInNodelist(FA const &f);
   unsigned int GetFlags(FA const &f);
   bool InSubHubs(FA const &Addr, FA const &Mask);
unsigned int FindHub(FA const &f);
   int Enabled(void) { return (Lists != 0); };
   char *Names(char *Buf);
};

int SetMaxNodelistAge(int tmt);
int SetNodelist(char *tmt, int TempZone);
void SayNodelistFlags(FA const &f);

#endif
