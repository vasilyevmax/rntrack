/* $Id$
 *  Watcom C for DOS-DPMI (DOS4G) compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* WATCOM C/C++ for DOS/DMPI (DOS4G) */

#ifndef SMAPI_WCX_H
#define SMAPI_WCX_H

#ifndef __WATCOMC__
    #error This file may be used only with Watcom C !
#endif
#if defined(__DOS4G__)
    #error This file may be used only with Watcom C DOS4G target !
#endif


#  define _stdc      cdecl
#  define _intr      interrupt far
#  define _intcast   void (_intr *)()
#  define _veccast   _intcast
#  define _fast      pascal

#  define farread    read
#  define farwrite   write

#  define _XPENTRY   pascal

#  define HAS_sopen     3   /* sopen() : in io.h, 3 or 4 parameters */

#endif
