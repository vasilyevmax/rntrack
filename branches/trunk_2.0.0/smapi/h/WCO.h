/* $Id$
 *  Watcom C for OS/2 compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* WATCOM C/C++ for OS/2 */

#ifndef SMAPI_WCO_H
#define SMAPI_WCO_H

#ifndef __WATCOMC__
  #error This file may be used only with Watcom C !
#endif
#if !defined(__OS2__) && !defined(__OS2V2__)
  #error This file may be used only with Watcom C OS/2 target !
#endif


#    define _stdc
#    define _intr
#    define _intcast
#    define _veccast
#    define _fast
#    define farread  read
#    define farwrite write

#    define _XPENTRY   _System

/*#  define mysleep(x) DosSleep(x*1000)*/  /* os2/bsedos.h */

#  define HAS_sopen     3   /* sopen() : in io.h, 3 or 4 parameters */

#endif
