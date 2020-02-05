/* $Id$
 *  SAS C for AmigaDOS compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* SAS C for AmigaDOS defines ************************************/
#ifndef SMAPI_SASC_H
#define SMAPI_SASC_H

#ifndef __SASC__
    #error This file may be used only with SAS C for AmigaDOS !
#endif


#define _stdc
#define _intr
#define _intcast
#define _veccast
#define _fast
#define _loadds

#define cdecl
#define pascal
#define near
#undef  far
#define far

#define farread read
#define farwrite write
#define mymkdir(a) mkdir((a))

#define mysleep(x) unused(x)

#include <fcntlh.>
#ifndef O_BINARY
    #define O_BINARY 0 /* O_BINARY flag has no effect under UNIX */
#endif

#define _XPENTRY

#error "Don't know how to implement record locking."
/* Using an executable that does no support record locking is
   discouraged in a multitasking environment. If you want to
   do it anyway, you may uncomment this line. Record locking is used
   to obtain a lock on the very first byte of a SQD file which
   indicates that no other program should use the message area now.
*/
/*#define unlock(a,b,c) unused(a)*/
/*#define lock(a,b,c) 0*/

#define SH_DENYNONE 0

typedef unsigned bit;

/*typedef unsigned char byte;*/
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

/* Not all compilers support this, test please (Stas Degteff) */
typedef   signed long long  hINT64;              /*  8 bytes */
typedef   signed long long hSINT64;              /*  8 bytes */
typedef unsigned long long hUINT64;              /*  8 bytes */
#define HAS_INT64

#endif
