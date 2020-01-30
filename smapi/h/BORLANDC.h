/* $Id$
 *  Turbo C and Borland C compiler-specific declarations for any platform
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* Borland Turbo C/C++ & Borland C/C++ **************/

#ifndef SMAPI_BORLANDC_H
#define SMAPI_BORLANDC_H

#ifndef __TURBOC__
    #error This file may be used only with Turbo C and Borland C !
#endif

#  define HAS_MALLOC_H 1      /* use "#include <malloc.h>" for malloc() etc. */
#  define HAS_DIR_H    1      /* use "#include <dir.h>" for findfirst() etc. */
#  define HAS_DOS_H    1      /* use "#include <dos.h>" for delay(), intr() etc. */
#  define HAS_IO_H     1      /* access(), open(), ... */
#  define HAS_SHARE_H  1  /* may use "#include <share.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */

#if __TURBOC__ == 0x0295
    #define HAS_strftime
    #define HAS_mktime
#endif

#if defined(__TURBOC__DOS__)     /* Turbo C/C++ & Borland C/C++ for MS-DOS */
    #include "BCD.h"

#elif defined(__TURBOC__WIN32__) /* Borland C/C++ for Win32 */
    #include "BCW.h"

#elif defined(__TURBOC__OS2__)   /* Borland C/C++ for OS/2 */
    #include "BCO.h"
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

typedef   signed long       hINT32;              /*  4 bytes */
typedef   signed long      hSINT32;              /*  4 bytes */
typedef unsigned long      hUINT32;              /*  4 bytes */

#if !defined(__DOS__)
    /* Not all compilers support this, test please (Stas Degteff) */
    typedef   signed long long  hINT64;              /*  8 bytes */
    typedef   signed long long hSINT64;              /*  8 bytes */
    typedef unsigned long long hUINT64;              /*  8 bytes */
    #define HAS_INT64
#endif

#endif
