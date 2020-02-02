/* $Id: $
 *  Provide functions to operate with memory arrays.
 *  Check to low memory when allocated.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"

#ifndef __LITTLE_ENDIAN__
/*
 *  put_dword
 *
 *  Writes a 4 byte word in little endian notation, independent of the local
 *  system architecture.
 */

void put_dword(byte *ptr, dword value)
{
    ptr[0] = (value & 0xFF);
    ptr[1] = (value >> 8) & 0xFF;
    ptr[2] = (value >> 16) & 0xFF;
    ptr[3] = (value >> 24) & 0xFF;
}

/*
 *  put_word
 *
 *  Writes a 4 byte word in little endian notation, independent of the local
 *  system architecture.
 */

void put_word(byte *ptr, word value)
{
    ptr[0] = (value & 0xFF);
    ptr[1] = (value >> 8) & 0xFF;
}
#endif

/* safe malloc, realloc, calloc */

void *smalloc(size_t size)
{
    void *ptr = (void *)malloc(size);
    if (ptr == NULL)
    {
        /* w_log(LL_CRIT, "out of memory"); */
        abort();
    }
    return ptr;
}

void *srealloc(void *ptr, size_t size)
{
    void *newptr = (void *)realloc(ptr, size);
    if (newptr == NULL)
    {
        /* w_log(LL_CRIT, "out of memory"); */
        abort();
    }
    return newptr;
}

void *scalloc(size_t nmemb, size_t size)
{
    void *ptr = smalloc(size*nmemb);
    memset(ptr,'\0',size*nmemb);
    return ptr;
}

void *memdup(void *p, size_t size)
{
    void *newp;
    newp = smalloc(size);
    memcpy(newp, p, size);
    return newp;
}
