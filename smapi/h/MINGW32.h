/* $Id$
 * Mingw32 and cygwin in mingw-mode compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */

/* MinGW32 & cygwin's 'gcc -mno-cygwin' */

/* Applied to:
   - MINGW32 for 32-bit Windows NT on Intel and AXP;
   - MINGW32 cross-compiler from unixes;
   - Cygwin GCC with option -mno-cygwin.
*/

#ifndef SMAPI_MINGW32_H
#define SMAPI_MINGW32_H

#ifndef __GNUC__
    #error This file may be used only with GNU C !
#endif

#ifndef __MINGW32__
    #error This file may be used only with MSys/MinGW (GNU C) on unix-like OS or Cygwin (GNU C) on Win32 !
#endif


#ifndef __LITTLE_ENDIAN__
    #define __LITTLE_ENDIAN__
#endif

#  define _stdc
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds
#  define cdecl
#  define pascal __stdcall
#  define near
#  undef  far
#  define far
#  define _XPENTRY
#  define SMAPI_EXT extern

#  define farread _read
#  define farwrite _write
#  define fdopen _fdopen
#  define close _close
#  define open _open
#  define lseek _lseek
#  define tell _tell
#  define write _write
#  define read _read

#  define sleep(sec) Sleep((sec)*1000l)
#  define mysleep(sec) Sleep((sec)*1000l)
#  define HAS_sleep     1
#  define HAS_strupr

#  define mymkdir mkdir

/*#  define strcasecmp  stricmp*/
/*#  define strncasecmp strnicmp*/

#ifndef LONG_MAX
    #include <limits.h>
#endif

/* older mingw headers are too lazy ... */
#  include <share.h>
#  define sopen _sopen
#ifndef SH_DENYRW
    #define SH_DENYRW 0x10
#endif
#ifndef SH_DENYWR
    #define SH_DENYWR 0x20
#endif
#ifndef SH_DENYRD
    #define SH_DENYRD 0x30
#endif
#ifndef SH_DENYNO
    #define SH_DENYNO 0x40
#endif

#  define HAS_spawnvp    /* spawnvp() present */
#  define HAS_mktime     /* time.h */
#  define HAS_strftime   /* time.h */
#  define HAS_ACCESS    /* access() in io.h */
#  define HAS_sopen     3   /* sopen() : in io.h, 3 or 4 parameters */

#  define HAS_MALLOC_H   /* may use "#include <malloc.h>" for malloc() etc. */
#  define HAS_IO_H       /* may use "#include <io.h> */
#  define HAS_SHARE_H    /* may use "#include <share.h> */
#  define HAS_DIRENT_H   /* may use "#include <dirent.h> */
#  define HAS_SYS_UTIME_H  /* #include <sys/utime.h> in alternate to <utime.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

/* Latest version has sys/param.h for sure, though its equivalence
 * with unix sys/param.h is questionable. Added for MAXPATHLEN definition */
#  define HAS_SYS_PARAM_H /* may use "#include <sys/param.h> */

#  define USE_STAT_MACROS

typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

typedef unsigned long dword;
typedef signed long sdword;

typedef signed short sshort;
/*typedef unsigned short ushort;*/

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
