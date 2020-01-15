/* $Id: $
 *
 * Routines for parsing ftn address.
 * Initial code by Nick Voronin (2:5030/1554)
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* standard headers */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "compiler.h"
#include "ftnaddr.h"

long read_ftn_long(const char *str, const char **end)
{
long i = 0, imax = LONG_MAX/10;
unsigned digit, lastdigmax=LONG_MAX%10;
	assert(str != NULL);
	assert(end != NULL);

	*end = str;
	if(*str != '-')
	{
		while( (digit = (unsigned)(*str - '0')) <= 9)
		{
			if(i < imax || (i == imax && digit <= lastdigmax))
				i = i * 10 + digit;
			else
				goto Fail; /* overflow */
			++str;
		}
	}
	else
	{
		++str;
		if(*str != '1')
			goto Fail;
		++str;
		i = -1;
	}
	*end = str;
return i;
Fail:
return LONG_MAX;
}

/*
 *	Function parse fidonet frl-1002.001 address.
 * IN:
 *  str : string with possible leading spaces or tabs
 *	netAddr : must be initialized by zero or default values.
 *	mask : mandatory values in address string.
 *	end : valid address to store pointer or NULL.
 * OUT:
 *	Returns mask of explicitly given values in str, or'ed with FTNADDR_ERROR
 *	        if error occured or if not all mandatory values are given
 *	*end : pointer to character that stops scan or pointer 
 *         to str if error occured.
 *  netAddr : values parsed from str or old values if error occured.
 * NOTE:
 *  parts of address not explicitly given in str stays intact in netAddr
 *  structure.
 *  in case when FTNADDR_ERROR is returned netAddr is unmodified even 
 *  if returned mask indicated some sucessfully parsed address' parts.
 */

int parseFtnAddr(const char *str, hs_addr *netAddr, int len, int mask, const char **end)
{
char *allocated = NULL;
const char *end_loc;
int  result = 0;

	assert(str);
	assert(netAddr);

	allocated = (char*)malloc(len + 1);
	if (!allocated)
	{
		if(end != NULL)
			*end = str;
		return FTNADDR_ERROR;
	}

	memcpy(allocated, str, len);
	allocated[len] = '\0';

	result = parseFtnAddrZ(allocated, netAddr, mask, &end_loc);
	if(end != NULL)
		*end = str + (end_loc - allocated);

	free(allocated);

return result;
}

int parseFtnAddrZ(const char *str, hs_addr *netAddr, int mask, const char **end)
{
/*                  0    1    2    3    4     5    6     7     8     9  */
const char s[] = {'\0', ':', '/', '.', '@', '\0', ' ', '\t', '\r', '\n'};
const char *ptr, *tmp;
int result = 0;
size_t sym = 0;
long i = 0;
hs_addr netAddrOld = *netAddr;

	assert(str);
	assert(netAddr);

	tmp = str;

	/* skip leading spaces and tabs 
	 * isspace may be too much, it skips cr&lf which may be objectionable */
	while (*tmp && (*tmp == ' ' || *tmp == '\t')) ++tmp;

	ptr = tmp;

	i = read_ftn_long(tmp, &tmp);
	if(i == LONG_MAX)
		goto Fail;

	/* find first key symbol */
	while(++sym < sizeof(s) && *tmp != s[sym]);

	/* there was a number in the beginning of string */
	if(ptr != tmp)
	{
		if(sym < 4) /* < @ */
			/* found symbol is next to the number,
			 * assume omitted symbol */
			--sym;
		else if(sym < sizeof(s))
			/* single number or number followed by '@' 
			 * is assumed to be node number */
			sym = 2;
		else
			goto Fail;

		/* go directly inside the loop since number is already read */
		goto Sw;
	}

	/* now sym is a key symbol which should be before number in examination (\0 for zone) */
	while(sym < 4)
	{
		/* skip key symbol */
		ptr = ++tmp;
		i = 0;

		i = read_ftn_long(tmp, &tmp);
		if(i == LONG_MAX || ptr == tmp)
			goto Fail;
Sw:
		switch(sym)
		{
			case 0: /* zone */
				if(i > 0 && i <= 32767)
				{
					netAddr->zone = (sword)i;
					result = FTNADDR_ZONE;
				}
				else
					goto Fail;
				break;
			case 1: /* net */
				if(i > 0 && i <= 32767)
				{
					netAddr->net = (sword)i;
					result |= FTNADDR_NET;
				}
				else
					goto Fail;
				break;
			case 2: /* node */
				if(i >= -1 && i <= 32767)
				{
					netAddr->node = (sword)i;
					result |= FTNADDR_NODE;
				}
				else
					goto Fail;
				break;
			case 3: /* point */
				if(i >= -1 && i <= 32767)
				{
					netAddr->point = (sword)i;
					result |= FTNADDR_POINT;
				}
				else
					goto Fail;
				break;
		}

		if(*tmp != s[++sym])
		{
			while(++sym < sizeof(s) && *tmp != s[sym]) ;
			/* we can skip anything, but then next symbol should be 
			 * either '@' or whitespace or '\0' */
			if(sym < 4) 
				goto Fail;
		}
	}

	if(sym == 4) /* @ */
	{
		ptr = ++tmp;
		i = 0;
		while((i < 8) && *tmp && (isdigit(*tmp) || isalpha(*tmp)))
		{
			netAddr->domain[i] = *tmp;
			++tmp;
			++i;
		}
		netAddr->domain[i] = 0;
		result |= FTNADDR_DOMAIN;
	}
/* If we parsed enough from string then it's ok 
 * and we don't really care which character stops scan. */	
/*	else if(sym >= sizeof(s) && ...) goto Fail; */

	if(~result & mask)
		goto Fail;

	if(end != NULL)
		*end = tmp;
return result;
Fail:
	/* in case of error *end points on the beginning of string */
	if(end != NULL)
		*end = str;

	*netAddr = netAddrOld;
return FTNADDR_ERROR | result;
}
