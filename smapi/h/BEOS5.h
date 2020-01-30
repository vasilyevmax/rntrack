/* $Id$
 *  GNU C for BeOS compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* BeOS 5.x (Unix clone, GNU C) */

#ifndef SMAPI_BEOS5_H
#define SMAPI_BEOS5_H

#ifndef __GNUC__
    #error This file may be used only with GNU C !
#endif

#ifndef __BEOS__
    #error This file may be used only with GNU C on BeOS
#endif


#  define _XPENTRY
#  define SMAPI_EXT extern
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds
#ifndef _stdc
    #define _stdc     /*__stdcall*/ /* produce compiler warnings */
#endif
#ifndef cdecl
    #define cdecl     __cdecl
#endif

#  define pascal
#  define near
#  undef  far
#  define far

#  define farread read
#  define farwrite write

#  define mymkdir(a) mkdir((a), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)

#  define tell(a) lseek((a),0,SEEK_CUR)

#  include <fcntl.h>

#ifndef SH_DENYNONE
    #define SH_DENYNONE 0
#endif
#ifndef SH_DENYNO
    #define SH_DENYNO 0
#endif
#ifndef SH_DENYALL
    #define SH_DENYALL 1
#endif

#  define mysleep(x) sleep(x)
/*#  define sleep(x) snooze(x*1000000l)   use sleep() from unistd.h */
#  define HAS_sleep     1
#  define HAS_mktime    1  /* in <time.h> */
#  define HAS_strftime  1  /* in <time.h> */
#  define HAS_snprintf  1
#  define HAS_vsnprintf 1
#  define HAS_popen_close 1 /* popen(); pclose() */
#  define HAS_strcasecmp  1
#  define HAS_strncasecmp 1
#  define HAS_strlwr      1
#  define HAS_strupr      1

#  define stricmp(s1,s2) strcasecmp(s1,s2)
#  define strnicmp(s1,s2,z) strncasecmp(s1,s2,z)

#  define HAS_DIRENT_H         1  /* <dirent.h> */
#  define HAS_UNISTD_H         1  /*? <unistd.h> conflicts with be/kernel/OS.h ?*/
#  define HAS_PWD_H            1  /* <pwd.h> */
#  define HAS_GRP_H            1  /* may be used "#include <grp.h>" */
#  define HAS_SIGNAL_H         1  /* <signal.h> */
#  define USE_STAT_MACROS      1
#  define HAS_SYS_PARAM_H      1
#  define HAS_SYS_SYSEXITS_H   1  /*  <sys/sysexits.h> */
#  define HAS_SYS_WAIT_H       1  /* <sys/wait.h> */
#  define HAS_SYS_STATVFS_H    1

typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

typedef unsigned long dword;
typedef signed long sdword;

typedef signed short sshort;
typedef unsigned short ushort;

typedef signed long slong;
typedef unsigned long ulong;


typedef   signed char        hCHAR;              /*  1 byte */
typedef   signed char       hSCHAR;              /*  1 byte */
typedef unsigned char       hUCHAR;              /*  1 byte */

typedef   signed char        hINT8;              /*  1 byte */
typedef   signed char       hSINT8;              /*  1 byte */
typedef unsigned char       hUINT8;              /*  1 byte */

typedef   signed short      hINT16;              /*  2 bytes */
typedef   signed short     hSINT16;              /*  2 bytes */
typedef unsigned short     hUINT16;              /*  2 bytes */

typedef   signed int        hINT32;              /*  4 bytes */
typedef   signed int       hSINT32;              /*  4 bytes */
typedef unsigned int       hUINT32;              /*  4 bytes */

typedef   signed long long  hINT64;              /*  8 bytes */
typedef   signed long long hSINT64;              /*  8 bytes */
typedef unsigned long long hUINT64;              /*  8 bytes */
#define HAS_INT64

#endif
