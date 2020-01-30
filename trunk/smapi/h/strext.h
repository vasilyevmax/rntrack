/* $Id$
 *  Provide extra set of functions to operate with strings.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

#ifndef SMAPI_STREXT_H__
#define SMAPI_STREXT_H__

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Replace last char with '\0' if last char is strip-char
 */
char *_fast Strip_Trailing(char *str, char strip);

/* Add add-char to end of string (size of the str is not checked!!!)
 */
char *_fast Add_Trailing(char *str, char add);

/* Copy src to dst; return src
 */
char *_fast strocpy(char *dst, const char *src);

/* Return pointer to 1st char of specified word in string (by word number)
 */
char* _fast firstchar(const char *strng, const char *delim, int findword);


char *strrstr(const char *HAYSTACK, const char *NEEDLE);

/*DOC
  Input:  two constant null-terminated strings
  Output: NULL or the point to a null-terminated string
  FZ:     finds the LAST occurence of NEEDLE in HAYSTACK
          (same as strstr but last occurence
*/

char *fc_stristr(const char *str, const char *find);
/*
 * Find the first occurrence of find in s ignoring case
 */

char   *stripLeadingChars(char *str, const char *chr);
/*DOC
  Input:  str is a \0-terminated string
          chr contains a list of characters.
  Output: stripLeadingChars returns a pointer to a string
  FZ:     all leading characters which are in chr are deleted.
          str is changed and returned.
*/


/*DOC
  Input:  str is a \0-terminated string
          chr contains a list of characters.
  Output: stripTrailingChars returns a pointer to a string
  FZ:     all trailing characters which are in chr are deleted.
          str is changed and returned (not reallocated, simply shorted).
*/
char *stripTrailingChars(char *str, const char *chr);


#define stripRoundingChars(str,chrs) (stripTrailingChars(stripLeadingChars((str),(chrs)),(chrs)))


char   *strUpper(char *str);
/*DOC
  Input:  str is a \0 terminated string
  Output: str
  FZ:     strUpper converts the string from lower case to upper case.
  */

char   *strLower(char *str);
/*DOC
  Input:  str is a \0 terminated string
  Output: str
  FZ:     strLower converts the string from upper case to lower case.
*/

char *sstrdup(const char *src);

/* safe strdup for line part */
#define sstrndup(src,len) strncpy(smalloc(len),src,len)

/* safe strlen: if src==NULL return 0 */
#define sstrlen(src) ( src ? strlen(src) : 0 )

/* safe strcpy: if src==NULL or dst==NULL don't copy and return NULL */
#define sstrcpy(dst,src) ( (src)&&(dst) ? strcpy(dst,src) : NULL )

/* safe strncpy: if src==NULL or dst==NULL don't copy and return NULL */
#define sstrncpy(dst,src,len) ( (src)&&(dst) ? strncpy(dst,src,len) : NULL )

/* Copyes not more than len chars from src into dst, but, unlike strncpy(),
 * it appends '\0' even if src is longer than len.
 * Return dst
 * Prevent memory faults:
 *  - if dst is NULL doing nothing and return NULL
 *  - if src is NULL and dst not NULL store '\0' into dst[0] and return it.
 */
char *strnzcpy (char *dst, const char *src, size_t len);

/* Concantenates not more than len chars from src into dst, but, unlike
 * strncat(), it appends '\0' even if src is longer than len.
 * Return dst
 * Prevent memory faults:
 *  - if dst is NULL doing nothing and return NULL
 *  - if src is NULL doing nothing and return dst.
 */
char *strnzcat (char *dst, const char *src, size_t len);

/* safe strstr: if str==NULL or find==NULL return NULL */
#define sstrstr(str,find) ( (str)&&(find) ? strstr(str,find) : NULL )

/* safe stristr: if str==NULL or find==NULL return NULL */
#define sstristr(str,find) ( (str)&&(find) ? fc_stristr(str,find) : NULL )

/* safe strcmp */
int sstrcmp(const char *str1, const char *str2);

/* safe strncmp */
int sstrncmp(const char *str1, const char *str2, size_t length);

/* safe stricmp (case-insencitive) */
int sstricmp(const char *str1, const char *str2);

/* safety strnicmp (case-insencitive) */
int sstrnicmp(const char *str1, const char *str2, size_t length);

/* safety string envelope (use this in functions calls) */
#define sstr(ss) ( ss ? ss : "" )


char *strseparate(register char **stringp, register const char *delim);

/* Extract contents from CVS/RCS keyvords (like $Revision$)
 * Return malloc'ed string
 */
char *extract_CVS_keyword(char *str);

/* Convert char to integer with range checking
 */
int ctoi(const char *s);

/* Copy string from str to (*pmem), allocating memory as needed
   NOTE! *pmem must be NULL, if not NULL, it will be free().
 */
int copyString(char *str, char **pmem);

/* Copy chars from str to (*dest) until one of the chars in seps appears
 * memory is allocated as needed
 * *dest will be freed if non-NULL
 * returns number of chars copied
 */
int copyStringUntilSep(char *str, char *seps, char **dest);

/* Structures for compact storage of array of NUL-terminated strings of
 * various length.
 * s_str_array is just one memory allocation and contains no pointers,
 * so it can be freed by single free() and copied with memcpy()
 * Use for nonmutable collections of (short) strings.
 */
typedef union str_mess
{
    int offsets[1];   /* offsets in bytes from start of union, used as index for strings[] */
    char strings[1];  /* NUL-terminated strings */
} u_str_mess;

typedef struct str_array
{
    int count;        /* Number of entries in data.offset array */
    u_str_mess data;
} s_str_array;

/* Get an address of n-th string in s_str_array *a */
#define STR_N(a,n) &((a)->data.strings[(a)->data.offsets[n]])

/* Offset of a byte just after last allocated byte (after last '\0') */
#define STR_A_OFFSET_END(a) (a->data.offsets[a->count-1] + \
                          strlen(STR_N(a, a->count-1)) + 1)

/* Calculate used memory size for s_str_array *a */
#define STR_A_SIZE(a) (offsetof(s_str_array, data) + \
                      STR_A_OFFSET_END(a))

/* Calculate memory size used for strings in s_str_array->data.strings[] */
#define STR_A_SSIZE(a) (STR_A_OFFSET_END(a) - \
		               a->data.offsets[0])

/* Get an index of 'find' in ss
 * Case insensitive full match is used
 * -1 if no match */
int findInStrArray(s_str_array const *ss, char const *find);

s_str_array *copyStrArray(s_str_array *ss);

/* Parse strings like "token1, token2,token3 token4" into s_str_array */
s_str_array *makeStrArray(char *token);

char *StrArray2String(s_str_array *ss);

#ifdef __cplusplus
}
#endif

#endif
