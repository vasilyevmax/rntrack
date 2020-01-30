/* $Id$
 *  Microsoft C compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* Microsoft C or Microsoft QuickC for MS-DOS or OS/2 */

#ifndef SMAPI_MSC_H
#define SMAPI_MSC_H

#ifndef _MSC_VER
    #  error This file used only with Microsoft C or Microsoft QuickC for MS-DOS or OS/2 !
#endif

#ifndef __LITTLE_ENDIAN__
    #define __LITTLE_ENDIAN__
#endif

#  define _stdc cdecl
#  define _intr cdecl interrupt far
#  define _intcast void (_intr *)()
#  define _veccast _intcast

#if _MSC_VER >= 600
    #define _fast _fastcall
#else
    #define _fast pascal
#endif

#  define farmalloc(n)    _fmalloc(n)
#  define farfree(p)      _ffree(p)
#  define farrealloc(p,n) _frealloc(p,n)

#if _MSC_VER >= 600
    #define farcalloc(a,b) _fcalloc(a,b)
#else
    void far *farcalloc(int n, int m);
#endif

#ifdef __OS2__
    /* just don't use 16 bit OS/2, we doubt that it still works */
    #define farread read
    #define farwrite write
    #define _XPENTRY pascal far
    #define mysleep(x) DosSleep(1000L*(x))
    #define sleep(x) DosSleep(1000L*(x))
    #define HAS_sleep     1
#else
    #define _XPENTRY
    #define mymkdir(x) _mkdir(x)
#endif

#  define HAS_MALLOC_H  1  /* use "#include <malloc.h>" for malloc() etc. */
#  define HAS_IO_H      1  /* may use "#include <io.h> */
#  define HAS_SHARE_H   1  /* may use "#include <share.h> */
#  define HAS_PROCESS_H 1  /* may use "#include <process.h> */
#  define HAS_DOS_H     1  /* definitions for MS-DOS interface routines */
#  define HAS_DIRECT_H  1  /* function declarations for directory handling/creation */
#  define HAS_SYS_UTIME_H 1 /* definitions/declarations for utime() */

#  define USE_STAT_MACROS


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

typedef   signed long       hINT32;              /*  4 bytes */
typedef   signed long      hSINT32;              /*  4 bytes */
typedef unsigned long      hUINT32;              /*  4 bytes */

#endif
