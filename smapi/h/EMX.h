/* $Id$
 * EMX (GNU C on OS/2) compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* EMX for 32-bit OS/2 and RSX for Windows NT (GNU C) */

#ifndef SMAPI_EMX_H
#define SMAPI_EMX_H

#ifndef __GNUC__
    #error This file may be used only with GNU C !
#endif

#ifndef __EMX__
    #error This file may be used only with EMX (GNU C) on OS/2 !
#endif


#ifndef __LITTLE_ENDIAN__
    #define __LITTLE_ENDIAN__  /* using to select functions/macroses for read & write binary values */
#endif

#undef __UNIX__

#  define _stdc
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds
#  define cdecl
#  define pascal
#if defined(__32BIT__)
    #define near
    #undef  far
    #define far
    #define farread(a,b,c)  read(a,b,c)
    #define farwrite(a,b,c) write(a,b,c)
#endif

#  define mymkdir(a) mkdir((a), 0)

#  define strcasecmp stricmp
#  define strncasecmp strnicmp

#  define _XPENTRY
#  define SMAPI_EXT extern

#  define mysleep(x) sleep(x)
#  define HAS_sleep     1  /* sleep(): stdlib.h, unistd.h */
#  define HAS_snprintf  1
#  define HAS_vsnprintf 1
#  define HAS_strlwr    1  /* strlwr() in string.h */
#  define HAS_strupr    1  /* strupr() in string.h */
//#  define HAS_getpid    1  /* getpid() in process.h, unistd.h */
#  define HAS_spawnvp   1  /* spawnvp() in process.h */
#  define HAS_strftime  1  /* strftime() in time.h  */
#  define HAS_mktime    1  /* mktime() in time.h */
#  define HAS_popen_close 1 /* popen(); pclose() */
#  define HAS_sopen     4   /* sopen() : in io.h, 4 parameters */

#  define HAS_DOS_H     1  /* use "#include <dos.h>" for _int86 () etc. */
#  define HAS_DIRENT_H  1  /* use "#include <dirent.h>" for opendir() etc. */
#  define HAS_IO_H      1  /* use "#include <io.h>" */
#  define HAS_SHARE_H   1  /* may use "#include <share.h> */
#  define HAS_UNISTD_H  1  /* use "#include <unistd.h> */
#  define HAS_SIGNAL_H  1  /* <signal.h> */
#  define HAS_PROCESS_H 1  /* may use "#include <process.h> */
#  define HAS_PWD_H
#  define HAS_UTIME_H   1

#  define USE_STAT_MACROS

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
//typedef unsigned short ushort;

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
