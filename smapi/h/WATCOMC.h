/* $Id$
 *  Watcom C compiler-specific declarations for any platform
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */

/* Watcom C/C++ all variants (DOS-16, DOS-32, Win, OS/2, QNX) */

#ifndef SMAPI_WATCOMC_H
#define SMAPI_WATCOMC_H

#ifndef __WATCOMC__
    #error This file may be used only with Watcom C !
#endif


#  define mode_t int
#  define SMAPI_EXT extern


#if ( __WATCOMC__ > 1000 )
    /* Watcom C 10.0 */
    #define mktemp _mktemp
#endif

#  define strcasecmp  stricmp
#  define strncasecmp strnicmp
#  define snprintf    _snprintf
#  define vsnprintf   _vsnprintf
#  define HAS_snprintf
#  define HAS_vsnprintf
#  define HAS_spawnvp
#  define HAS_getpid
#  define HAS_strftime    /* strftime() in time.h  */
#  define HAS_mktime      /* mktime() in time.h */
#  define HAS_mktemp    1

#  define HAS_MALLOC_H     /* may be used "#include <malloc.h>"  (see alc.h) */
#  define HAS_IO_H         /* may use "#include <io.h> */
#  define HAS_SHARE_H      /* may use "#include <share.h> */
#  define HAS_DIRECT_H
#  define HAS_SYS_UTIME_H  /* #include <sys/utime.h> in alternate to <utime.h> */
#  define HAS_DOS_H
#  define HAS_SIGNAL_H  1  /* <signal.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

#  define mymkdir(x)    mkdir(x) /*<direct.h>*/
#  define HAS_mkdir
#  include <dos.h>
#  define mysleep(x)    sleep(x) /* dos.h */
#  define HAS_sleep

#if defined(__WATCOMC__DOS4G__) /* WATCOM C/C++ for DOS4G */
    #include "WCX.h"
#elif defined(__WATCOMC__DOS__) /* WATCOM C/C++ for MS-DOS (16 bit)*/
    #include "WCD.h"
#elif defined(__WATCOMC__OS2__)/* WATCOM C/C++ for OS/2 */
    #include "WCO.h"
#elif defined(__WATCOMC__NT__) /* WATCOM C/C++ for Windows NT */
    #include "WCW.h"
#endif


typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

#ifdef __ALPHA__    /* add other 64 bit systems here */
    typedef unsigned int dword;
    typedef signed   int sdword;
#else             /* 32 and 16 bit machines */
    typedef unsigned long dword;
    typedef signed long sdword;
#endif

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

#ifdef __ALPHA__    /* add other 64 bit systems here */
    typedef   signed int        hINT32;              /*  4 bytes */
    typedef   signed int       hSINT32;              /*  4 bytes */
    typedef unsigned int       hUINT32;              /*  4 bytes */
#else
    typedef   signed long       hINT32;              /*  4 bytes */
    typedef   signed long      hSINT32;              /*  4 bytes */
    typedef unsigned long      hUINT32;              /*  4 bytes */
#endif

#if __WATCOMC__ >1000
    typedef   signed __int64    hINT64;            /*  8 bytes */
    typedef   signed __int64   hSINT64;            /*  8 bytes */
    typedef unsigned __int64   hUINT64;            /*  8 bytes */
    #define HAS_INT64
#endif

#endif
