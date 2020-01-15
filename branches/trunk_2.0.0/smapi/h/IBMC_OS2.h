/* $Id$
 *  IBM C/Set++ for OS/2 compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* IBM C/Set++ for OS/2 */

#ifndef SMAPI_IBMC_OS2_H
#define SMAPI_IBMC_OS2_H

#ifndef __IBMC__
  #error This file may be used only with IBM C/Set++ and IBM VisualAge C/C++ for OS/2 !
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
#  undef  far
#  define far

#  define farread read
#  define farwrite write
#  define mysleep(x) DosSleep(1000L*(x))
#  define sleep(x)   DosSleep(1000L*(x))
#  define HAS_sleep     1

#  define _XPENTRY pascal far

#  define HAS_MALLOC_H        /* use "#include <malloc.h>" for malloc() etc. */
#  define HAS_IO_H     1  /* may use "#include <io.h> */
#  define HAS_SHARE_H  1  /* may use "#include <share.h> */
#  define HAS_DIRECT_H 1  /* may use "#include <direct.h> */
#  define HAS_PROCESS_H   /* may use "#include <process.h> */


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
