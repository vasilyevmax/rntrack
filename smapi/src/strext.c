/* $Id: $
 * Provide extra set of functions to operate with strings.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */

/* standard headers */
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include <compiler.h>

#ifdef HAS_STRINGS_H
    #include <strings.h>
#endif

#include "memory.h"
#include "strext.h"

/***  Implementation  *******************************************************/

int ctoi(const char *s)
{
    char *foo;
    unsigned long res;
    if(!s) return 0;
    res = strtoul(s, &foo, 0);
    if (*foo)	/* parse error */
        return 0;
    if (res>(((unsigned)-1)>>1))  /* Too big */
        return 0;
    return (int)res;
}

char *_fast strocpy(char *dst, const char *src)
{
    const char *orig;
    if(!(src&&dst))return (char*)src;
    orig = src;
    memmove(dst, src, strlen(src) + 1);
    return (char*)orig;
}

char *_fast firstchar(const char *strng, const char *delim, int findword)
{
    int isw=0, sl_s, wordno = 0;
    register int sl_d, x;
    register const char *string=strng;
    const char *oldstring=strng;

    /* We can't do *anything* if the string or delim is NULL or blank... */

    if ( !string || !*strng || !delim || !*delim )
    {
        return NULL;
    }

    sl_d = (int)strlen(delim);

    for (string = strng; *string; string++)
    {
        for (x = 0, isw = 0; x <= sl_d; x++)
        {
            if (*string == delim[x])
            {
                isw=1;
            }
        }

        if (isw == 0)
        {
            oldstring = string;
            break;
        }
    }

    sl_s = (int)strlen(string);

    for (wordno = 0; string - oldstring < sl_s; string++)
    {
        for (x = 0, isw = 0; x <= sl_d; x++)
        {
            if (*string == delim[x])
            {
                isw = 1;
                break;
            }
        }

        if (!isw && string == oldstring)
        {
            wordno++;
        }

        if (isw && string != oldstring)
        {
            for (x = 0, isw = 0; x <= sl_d; x++)
            {
                if (*(string + 1) == delim[x])
                {
                    isw = 1;
                    break;
                }
            }

            if (isw == 0)
            {
                wordno++;
            }
        }

        if (wordno == findword)
        {
            if (string == oldstring || string == oldstring + sl_s)
            {
                return (char*)string;
            }
            else
            {
                return (char*)string + 1;
            }
        }
    }

    return NULL;
}

char *strrstr(const char *HAYSTACK, const char *NEEDLE)
{
    char *start = NULL, *temp = NULL;

    if(HAYSTACK&&NEEDLE)
    {
        temp = strstr(HAYSTACK, NEEDLE);
        while (temp  != NULL)
        {
            start = temp;
            temp = strstr(temp+1,NEEDLE);
        }
    }
    return start;
}

/*
 * Find the first occurrence of find in s ignoring case
 */
char *fc_stristr(const char *str, const char *find)
{
    char ch, sc;
    const char *str1 = NULL, *find1 = NULL;

    if(str&&find)
    {
        find++;
        ch = *(find-1);
        if (ch != 0)
        {
            do
            {
                do
                {
                    str++;
                    if ((sc = *(str-1)) == 0) return (NULL);
                }
                while (tolower((unsigned char) sc) != tolower((unsigned char) ch));

                for(str1=str,find1=find; *find1 && *str1 && tolower(*find1)==tolower(*str1); str1++,find1++);

            }
            while (*find1);
            str--;
        }
    }
    return ((char *)str);
}

char *stripLeadingChars(char *str, const char *chr)
{
    if (str && chr && *chr)
    {
        int i = (int)strspn(str, chr);
        memmove(str, str + i, strlen(str) - i+1);
    }
    return str;
}
/*DOC
  Input:  str is a \0-terminated string
          chr contains a list of characters.
  Output: stripTrailingChars returns a pointer to a string
  FZ:     all trailing characters which are in chr are deleted.
          str is changed and returned (not reallocated, simply shorted).
*/
char *stripTrailingChars(char *str, const char *chr)
{
    char *i;
    register int l;

    if( str && chr && (l=(int)strlen(str))>0 )
    {
        i = str+l-1;
        while( (NULL != strchr(chr, *i)) && (i>=str) )
            *i-- = '\0';
    }
    return str;
}


char *strUpper(char *str)
{
    char *temp = str;

    if(str) while(*str != 0)
        {
            *str = (char)toupper(*str);
            str++;
        }
    return temp;
}

char *strLower(char *str)
{
    char *temp = str;

    if(str) while(*str != 0)
        {
            *str = (char)tolower(*str);
            str++;
        }
    return temp;
}

char *sstrdup(const char *src)
{
    char *ptr;

    if (src == NULL) return NULL;
    /*    if (!strlen(src)) return NULL; */
    ptr = strdup (src);
    if (ptr == NULL)
    {
        abort();
    }
    return ptr;
}

/* safe strcmp */
int sstrcmp(const char *str1, const char *str2)
{
    if( str1==str2 ) return 0;  /* strings match */
    if( str1==NULL ) return -1; /* str1(NULL) < str2(not NULL) */
    if( str2==NULL ) return 1;  /* str1(not NULL) > str2(NULL) */
    return strcmp(str1,str2);   /* compare strings */
}

/* safety strncmp */
int sstrncmp(const char *str1, const char *str2, size_t length)
{
    if( str1==str2 ) return 0;  /* strings match */
    if( str1==NULL ) return -1; /* str1(NULL) < str2(not NULL) */
    if( str2==NULL ) return 1;  /* str1(not NULL) > str2(NULL) */
    return strncmp(str1,str2, length);  /* compare strings */
}

/* safe stricmp (case-insencitive) */
int sstricmp(const char *str1, const char *str2)
{
    if( str1==str2 ) return 0;  /* strings match */
    if( str1==NULL ) return -1; /* str1(NULL) < str2(not NULL) */
    if( str2==NULL ) return 1;  /* str1(not NULL) > str2(NULL) */
    return stricmp(str1,str2);   /* compare strings */
}

/* safety strnicmp (case-insencitive) */
int sstrnicmp(const char *str1, const char *str2, size_t length)
{
    if( str1==str2 ) return 0;  /* strings match */
    if( str1==NULL ) return -1; /* str1(NULL) < str2(not NULL) */
    if( str2==NULL ) return 1;  /* str1(not NULL) > str2(NULL) */
    return strnicmp(str1,str2, length);  /* compare strings */
}

/* From binkd sources (tools.c), modified by Stas Degteff
 * Copyes not more than len chars from src into dst, but, unlike strncpy(),
 * it appends '\0' even if src is longer than len.
 * Return dst
 * Prevent memory faults:
 *  - if dst is NULL doing nothing and return NULL
 *  - if src is NULL and dst not NULL store '\0' into dst[0] and return it.
 */
char *strnzcpy (char *dst, const char *src, size_t len)
{
    assert(len>0);
    if (!dst) return NULL;
    if (!src || len==1)
    {
        dst[0]='\0';
        return dst;
    }
    dst[len - 1] = 0;
    return strncpy (dst, src, len - 1);
}

/* From binkd sources (tools.c), modified by Stas Degteff
 * Concantenate not more than len chars from src into dst, but, unlike
 * strncat(), it appends '\0' even if src is longer than len.
 * Return dst
 * Prevent memory faults:
 *  - if dst is NULL doing nothing and return NULL
 *  - if src is NULL doing nothing and return dst.
 */
char *strnzcat (char *dst, const char *src, size_t len)
{
    size_t x;

    if (!dst) return NULL;
    if (!src) return dst;
    x = strlen (dst);
    return strnzcpy (dst + x, src, len);
}

char *strseparate(char **stringp, const char *delim)
{
    char *p, *q;

    if (!(stringp&&delim)) return NULL;

    p = *stringp;
    if (p == NULL || *p == '\0')
        return NULL;

    q = strpbrk (p, delim);
    if (q != NULL)
    {
        *stringp = q + 1;
        *q = '\0';
        while (**stringp && strchr(delim, **stringp)) (*stringp)++;
    }
    else
        *stringp = NULL;
    return p;
}

char *extract_CVS_keyword(char *str)
{
    size_t l;
    char *tmp, *r;

    if(!str)
        return NULL;

    tmp = strchr(str, 0x20);

    if ((!tmp)||(!*(++tmp)))
        return NULL;

    l = strlen(tmp);

    if (l<3)
        return NULL;

    r = (char *)malloc(l-1);
    if (!r)
        return NULL;

#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
    strncpy(r, tmp, l-2);
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic pop
#endif

    r[l-2] = 0;

    return r;
}

int copyString(char *str, char **pmem)
{
    if (!(str&&pmem))
        return 1;

    nfree(*pmem);
    *pmem = (char *) sstrdup (str);

    return 0;
}

int copyStringUntilSep(char *str, char *seps, char **dest)
{
    char *sepPos;

    if ((!str) || (!(*str)) || !(seps&&dest) )
        return 0;

    nfree(*dest);
    sepPos = strpbrk(str, seps);
    if (sepPos)
    {
        *dest = (char *)malloc(sepPos - str + 1);
        strnzcpy(*dest, str, sepPos - str);

        return (int)(sepPos - str);
    }

    *dest = (char *) sstrdup(str);
    return (int)strlen(str);
}

/* helper function for s_str_array */
int findInStrArray(s_str_array const *ss, char const *find)
{
    int ii = 0;
    assert(ss != NULL && find != NULL);

    while(ii < ss->count && stricmp(find, STR_N(ss, ii))) ++ii;
    if(ii < ss->count)
        return ii;

    return -1;
}

char *StrArray2String(s_str_array *ss)
{
    int ii;
    int size;
    char *string;
    assert(ss != NULL);

    if(ss->count == 0)
        return NULL;

    size = (int)STR_A_SSIZE(ss);
    string = (char *)smalloc(size);
    memcpy(string, STR_N(ss, 0), size);
    /* \0 -> ' ' */
    for(ii = 1; ii < ss->count; ++ii)
        string[ss->data.offsets[ii] - 1 - ss->data.offsets[0]] = ' ';

    return string;
}
