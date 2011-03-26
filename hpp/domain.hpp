/*
 *  RNtrack - FTN message tracker/router
 *
 *  domain.hpp - Domain routines
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

#ifndef _DOMAIN_HPP_
#define _DOMAIN_HPP_

#include "fidoaddr.hpp"

char * GetDomain(FA const & Addr);
int SetDomain(FA & f, char * tmt);
void DestroyDomain(void);

#endif

