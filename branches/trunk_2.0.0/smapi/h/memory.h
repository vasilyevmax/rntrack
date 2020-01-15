/**************************************************************************
 * $Id$
 *  Provide functions to operate with memory arrays and compiler-indepenent
 *  I/O integers/long with fixed bytes order.
 *  Check to low memory when allocated.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 **************************************************************************/

#ifndef SMAPI_MEMORY_H__
#define SMAPI_MEMORY_H__

#include "compiler.h"

/***  Declarations & defines  ***********************************************/

/* Safety free malloc'ed memory chunk */
#define nfree(a) { if (a != NULL) { free(a); a = NULL; } }

void *memdup(void *p, size_t size);
/*DOC
 * Input:  a chunk of memory, with size bytes
 * Output: a copy of it, malloc'ed
 */	

/*
   safe malloc, realloc, calloc
   if no memory allocated -- abort()
*/
void *smalloc(size_t size);
void *srealloc(void *ptr, size_t size);
void *scalloc(size_t nmemb, size_t size);


#ifdef __LITTLE_ENDIAN__

#define put_dword(ptr, val)	(*(dword *)(ptr) = (val))
#define put_word(ptr, val)	(*(word *)(ptr) = (val))
#define get_dword(ptr)		(*(dword *)(ptr))
#define get_word(ptr)		(*(word *)(ptr))

#else

void put_word(byte *ptr, word value);
void put_dword(byte *ptr, dword value);
/*
 *  get_dword
 *
 *  Reads in a 4 byte word that is stored in little endian (Intel) notation
 *  and converts it to the local representation n an architecture-
 *  independent manner
 */

#define get_dword(ptr)            \
   ((dword)((unsigned char)(ptr)[0]) |           \
    (((dword)((unsigned char)(ptr)[1])) << 8)  | \
    (((dword)((unsigned char)(ptr)[2])) << 16) | \
    (((dword)((unsigned char)(ptr)[3])) << 24))  \

/*
 *  get_word
 *
 *  Reads in a 2 byte word that is stored in little endian (Intel) notation
 *  and converts it to the local representation in an architecture-
 *  independent manner
 */

#define get_word(ptr)         \
    ((word)((unsigned char)(ptr)[0]) |         \
     (((word)((unsigned char)(ptr)[1])) << 8 ))

#endif /* __LITTLE_ENDIAN__ */


#endif
