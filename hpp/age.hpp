/*
 *  RNtrack - FTN message tracker/router
 *
 *  age.hpp - Message age routines
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

#ifndef _AGE_HPP_
#define _AGE_HPP_

#ifdef HAVE_CONFIG_H
    #include "constant.hpp"
#endif

#include <time.h>

int SetMaxAge(int tmt);
int AgeIsOver(time_t D, uint MAge);
int AgeIs(time_t D);

#endif

