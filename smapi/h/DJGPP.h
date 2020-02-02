/* $Id$
 *  DJGPP version of GNU C on DOS compiler-specific declarations
 *
 * See also https://www.gnu.org, license may be found here.
 */

/* DJGPP for MS-DOS (DPMI, GNU C) */

#ifndef SMAPI_DJGPP_H
#define SMAPI_DJGPP_H

#ifndef __GNUC__
    #error This file may be used only with GNU C !
#endif

#ifndef __DJGPP__
    #error This file may be used only with DJGPP version of GNU C on DOS !
#endif


#ifndef __LITTLE_ENDIAN__
    #define __LITTLE_ENDIAN__  /* using to select functions/macroses for read & write binary values */
#endif

#ifndef __FLAT__
    #define __FLAT__  /* DOS flat memory */
#endif

#if defined(__UNIX__) || defined(__unix__) || defined(unix)
    /* GCC predefined - buggi */
    #undef __unix__
    #undef unix
    #undef _unix
    #undef __UNIX__
    #undef UNIX
    #undef _UNIX
#endif

#  define _stdc
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds

#  define cdecl
#  define pascal
#  define near
/*#  undef  far*/
#  define far
#  define _XPENTRY
#  define SMAPI_EXT extern

#  define farread read
#  define farwrite write

#  define mymkdir(a) mkdir((a), 0)

#if defined(__dj_include_fcntl_h_) && !defined( SH_DENYNONE)
    #ifdef  SH_DENYNO
        #define SH_DENYNONE SH_DENYNO
    #else
        #define SH_DENYNONE 0
    #endif
#endif

#  include <unistd.h>
#  include <io.h>
#  define mysleep(x) sleep(x)
#  define HAS_sleep     1

#  define HAS_spawnvp   1   /* spawnvp() in process.h */
#  define HAS_strftime  1   /* strftime() in time.h  */
#  define HAS_mktime    1   /* mktime() in time.h */
#  define HAS_popen_close 1 /* popen(); pclose() */
#  define HAS_sopen     4   /* sopen() : in io.h, 4 parameters */

#  define HAS_DIR_H     1   /* use "#include <dir.h>" for findfirst() etc. */
#  define HAS_DIRENT_H  1   /* use "#include <dirent.h>" for DIR, opendir() etc. */
#  define HAS_DIRECT_H  1   /* use "#include <direct.h>" for DIR, opendir() etc. */
#  define HAS_DOS_H     1
#  define HAS_DPMI_H    1
#  define HAS_IO_H      1   /* use "#include <io.h> */
#  define HAS_SHARE_H   1   /* may use "#include <share.h> */
#  define HAS_UNISTD_H  1   /* use "#include <unistd.h> */
#  define HAS_SIGNAL_H  1   /* <signal.h> */
#  define HAS_PROCESS_H 1   /* may use "#include <process.h> */
#  define HAS_UTIME_H   1

#  define USE_STAT_MACROS

#  define HAS_SYS_PARAM_H /* may use "#include <sys/param.h> */

#ifndef LONG_MAX
    #include <limits.h>
#endif

typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

typedef unsigned long dword;
typedef signed long sdword;

typedef signed short sshort;
typedef unsigned short ushort;

typedef signed long slong;
typedef unsigned long ulong;


typedef   signed char        hCHAR;              /*  1 byte */
typedef   signed char       hSCHAR;              /*  1 byte */
typedef unsigned char       hUCHAR;              /*  1 byte */

typedef   signed char        hINT8;              /*  1 byte */
typedef   signed char       hSINT8;              /*  1 byte */
typedef unsigned char       hUINT8;              /*  1 byte */

typedef   signed short      hINT16;              /*  2 bytes */
typedef   signed short     hSINT16;              /*  2 bytes */
typedef unsigned short     hUINT16;              /*  2 bytes */

typedef   signed int        hINT32;              /*  4 bytes */
typedef   signed int       hSINT32;              /*  4 bytes */
typedef unsigned int       hUINT32;              /*  4 bytes */

/* Not all GCC support this, test please (Stas Degteff) */
typedef   signed long long  hINT64;              /*  8 bytes */
typedef   signed long long hSINT64;              /*  8 bytes */
typedef unsigned long long hUINT64;              /*  8 bytes */
#define HAS_INT64

#endif
