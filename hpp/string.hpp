/*
 *  RNtrack - FTN message tracker/router
 *
 *  string.hpp - String subroutines
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

#ifndef _STRING_HPP_
#define _STRING_HPP_

#include <string.h>

/*
#if defined(__OpenBSD__)
    # define my_strlcpy strlcpy
    # define my_strlcat strlcat
#else
*/
size_t my_strlcpy(char * dst, const char * src, size_t siz);
size_t my_strlcat(char * dst, const char * src, size_t siz);
// #endif


#define RSTRLCPY(d, s, l) \
    if(my_strlcpy((d), (s), (l) + 1) > (l)) \
        Log.Level(LOGD) << __FILE__ << " (line " << __LINE__ << \
        "): strlcpy() error (src=\'" << (s) << "\' dest=\'" << (d) << \
        "\' length=" << (l) << EOL

#define RSTRLCAT(d, s, l) \
    if(my_strlcat((d), (s), (l) + 1) > (l)) \
        Log.Level(LOGD) << __FILE__ << " (line " << __LINE__ << \
        "): strlcat() error (src=\'" << (s) << "\' dest=\'" << (d) << \
        "\' length=" << (l) << EOL

#endif
