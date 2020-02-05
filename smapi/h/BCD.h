/* $Id$
 *  Turbo C and Borland C for DOS compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* Turbo C/C++ & Borland C/C++ for MS-DOS */

#ifndef SMAPI_BCD_H
#define SMAPI_BCD_H

#ifndef __TURBOC__
    #error This file may be used only with Turbo C and Borland C !
#endif

#ifndef __DOS__
    #error This file may be used only with DOS version of Turbo C or Borland C !
#endif

/* for BC++ 3.1 */
#  define strcasecmp stricmp
#  define strncasecmp strncmpi

#  define _stdc cdecl
#  define _intr interrupt far
#  define _intcast void (_intr *)()
#  define _veccast _intcast
#  define _fast _fastcall
#  define _loadds

/* #include <conio.h> */
#  define mysleep(x) delay(x);
#  define sleep(x) delay(x);
#  define HAS_sleep     1

#ifndef _XPENTRY
    #define _XPENTRY
#endif

#  define mode_t int

#endif
