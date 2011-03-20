/*
 *  RNtrack - FTN message tracker/router
 *
 *  mytypes.hpp - Local types definitions
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


#ifndef _MYTYPES_HPP_
#define _MYTYPES_HPP_

#ifdef HAVE_CONFIG_H
    #include "constant.hpp"
#endif

#ifdef HAVE_SYS_STAT_H
    #include <sys/stat.h>
#endif

#include "smapi/typedefs.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef struct stat s_stat;
#ifndef FALSE
    #define FALSE (0)
#endif
#ifndef TRUE
    #define TRUE  (!FALSE)
#endif
#define OK        (0)
#define On        (1)

#endif
