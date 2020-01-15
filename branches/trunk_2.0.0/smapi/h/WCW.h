/* $Id$
 *  Watcom C for Win32 (NT) compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* WATCOM C/C++ for Windows NT */

#ifndef SMAPI_WCW_H
#define SMAPI_WCW_H

#ifndef __WATCOMC__
  #error This file may be used only with Watcom C !
#endif
#if !defined(__WIN32__) && !defined(__NT__)
  #error This file may be used only with Watcom C Win32/NT target !
#endif


#    define _stdc
#    define _intr
#    define _intcast
#    define _veccast
#    define _fast
#    define farread  read
#    define farwrite write

#    define _XPENTRY pascal

/*#  define mysleep(x) Sleep(x*1000) */ /* winbase.h */

#    include <limits.h>
#    ifndef MAXPATHLEN
#      define MAXPATHLEN NAME_MAX
#    endif

#  define HAS_sopen     3   /* sopen() : in io.h, 3 or 4 parameters */

#endif
