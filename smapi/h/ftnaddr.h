/* $Id$
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */

#ifndef SMAPI_PARSEFTN_H__
#define SMAPI_PARSEFTN_H__

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _netaddr
{
    sword zone;
    sword net;
    sword node;
    sword point;
    char domain[9];
} hs_addr, *ps_addr;

#define FTNADDR_ZONE	0x01
#define FTNADDR_NET		0x02
#define FTNADDR_NODE	0x04
#define FTNADDR_POINT	0x08
#define FTNADDR_DOMAIN	0x10
#define FTNADDR_ERROR	0x80

#define FTNADDR_GOOD	(FTNADDR_NODE | FTNADDR_NET | FTNADDR_ZONE)
#define FTNADDR_2D	(FTNADDR_NODE | FTNADDR_NET)
#define FTNADDR_4D	(FTNADDR_NODE | FTNADDR_NET | FTNADDR_ZONE)
#define FTNADDR_5D	(FTNADDR_DOMAIN | FTNADDR_NODE | FTNADDR_NET | FTNADDR_ZONE)

/** function converts fidonet address from part of string to HS_NETADDR */
int parseFtnAddr(const char *str, hs_addr *netAddr, int len, int mask, const char **end);

#define parseFtnAddrS(str, netAddr, len) parseFtnAddr((str), (netAddr), (len), FTNADDR_GOOD, NULL)

/** function converts fidonet address from zero-terminated string to HS_NETADDR */
int parseFtnAddrZ(const char *str, hs_addr *netAddr, int mask, const char **end);

#define parseFtnAddrZS(str, netAddr) parseFtnAddrZ((str), (netAddr), FTNADDR_GOOD, NULL)

#ifdef __cplusplus
}
#endif

#endif
