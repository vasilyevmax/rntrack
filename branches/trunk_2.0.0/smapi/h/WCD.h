/* $Id$
 *  Watcom C for DOS compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* WATCOM C/C++ for DOS (16 bit) */

#ifndef SMAPI_WCD_H
#define SMAPI_WCD_H

#ifndef __WATCOMC__
  #error This file may be used only with Watcom C !
#endif

#ifndef __DOS__
  #error This file may be used only with Watcom C 16 bit DOS target !
#endif


#  define _stdc      cdecl
#  define _intr      interrupt far
#  define _intcast   void (_intr *)()
#  define _veccast   _intcast
#  define _fast      pascal

#  ifdef __FAR_DATA__
#    define farread    read
#    define farwrite   write
#  else
#    define farread    trivial_farread
#    define farwrite   trivial_farwrite
#    define NEED_trivial_farread   1
#    define NEED_trivial_farwrite  1
     int trivial_farread( int handle, void far *buffer, unsigned len );
     int trivial_farwrite( int handle, void far *buffer, unsigned len );
#  endif

#  define HAS_dos_read 1      /* dos_read() */
#  define dos_read _dos_read  /* _dos_read() in dos.h */
#  define HAS_sopen     3   /* sopen() : in io.h, 3 or 4 parameters */

#  define _XPENTRY   pascal

#endif
