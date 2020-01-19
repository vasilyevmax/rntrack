/* $Id$
 *  GNU C on many unix-like OS : compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* Declarations for UNIX clones: Linux, FreeBSD, SUNOS (Solaris), MacOS etc. */

#ifndef SMAPI_UNIX_H
#define SMAPI_UNIX_H

#ifndef __GNUC__
    #error This file may be used only with GNU C !
#endif

#ifndef __UNIX__
    #error This file may be used only with GNU C on unix-like OS !
#endif

#  define SMAPI_EXT extern
#  define _stdc
#  define _intr
#  define _intcast
#  define _veccast
#  define _fast
#  define _loadds

#  define cdecl
#  define pascal
#  define near
#  undef  far
#  define far

#  define farread read
#  define farwrite write

#  define HAS_UTIME_H 1

#if (defined(__APPLE__) && defined(__MACH__)) || defined(__NetBSD__) || \
    defined(__FreeBSD__) || defined(_AIX) || defined(__SUN__) || \
    defined(__LINUX__) || defined(__osf__) || defined(__hpux) || \
    defined(__OpenBSD__) || defined(__CYGWIN__) || defined(__QNXNTO__)
    #define mymkdir(a) mkdir((a), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#else
    #define mymkdir(a) __mkdir((a), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#endif

#if !defined(__SUN__) && !defined(__QNXNTO__)
    #define tell(a) lseek((a),0,SEEK_CUR)
#endif

#ifndef stricmp
    #define stricmp strcasecmp
#endif
#ifndef strnicmp
    #define strnicmp strncasecmp
#endif

#if !defined(USG)
    #define HAS_SYS_PARAM_H
#endif

#if ((defined(BSD) && (BSD >= 199103)) || (defined(__FreeBSD__) && (__FreeBSD__ == 4)))
    /* now we can be sure we are on BSD 4.4 */
    #define HAS_SYS_MOUNT_H
#endif

/* FreeBSD >=5.x */
#if (defined(__FreeBSD__) && (__FreeBSD__ >= 5))
    #define HAS_SYS_STATVFS_H
#endif

/* we are not on any BSD-like OS */
/* list other UNIX os'es without getfree mechanism here */
#if defined( __svr4__ ) || defined( __SVR4 )
    #define HAS_SYS_STATVFS_H
#endif

#if defined(__SPARC__)
    #define HAS_SYS_STATVFS_H
    #define HAS_SYS_STATFS_H
    #define HAS_SYS_VFS_H
#endif

#if defined (__LINUX__)
    #if defined(__GLIBC__)
        #define HAS_SYS_STATVFS_H
    #else
        #define HAS_SYS_VFS_H
    #endif
#endif

#ifndef LONG_MAX
    #include <limits.h>
#endif

#  include <fcntl.h>
#ifndef O_BINARY
    #define O_BINARY 0 /* O_BINARY flag has no effect under UNIX */
#endif

#ifndef O_TEXT
    #define O_TEXT   0 /* O_TEXT flag has no effect under UNIX */
#endif

#ifndef SH_DENYNONE
    #define SH_DENYNONE 0
#endif
#ifndef SH_DENYNO
    #define SH_DENYNO 0
#endif
#ifndef SH_DENYALL
    #define SH_DENYALL 1
#endif

#  define _XPENTRY

/* Other OS's may sleep with other functions */

#if defined(__SUN__)
    #define mysleep(x) sleep(x)
    /*#    define sleep(x)   usleep(x*1000000l)*/
    #define HAS_sleep     1
#elif defined(__BSD__) || defined(__CYGWIN__) || defined(__LINUX__) || defined(__APPLE__) || defined (__QNXNTO__)
    #define mysleep(x) sleep(x)
    #define HAS_sleep     1
#endif
#ifndef __SUN__ /* SunOs 2.7 not have snprintf() and vsnprintf in libc */
    /* If you known test for this - please report to developers */
    #define HAS_snprintf  1
    #define HAS_vsnprintf 1
#endif

#if !defined(__QNXNTO__)
    #define HAS_SYSEXITS_H       1  /*  <sysexits.h> */
#endif /* __QNXNTO__ */
#  define HAS_UNISTD_H         1  /* <unistd.h> */
#  define HAS_PWD_H            1  /* <pwd.h> */
#  define HAS_GRP_H            1  /* may be used "#include <grp.h>" */
#  define HAS_SIGNAL_H         1  /* <signal.h> */
#  define HAS_SYS_WAIT_H       1  /* <sys/wait.h> */
#  define USE_STAT_MACROS      1

#if defined(__LINUX__) || defined(__BSD__) || defined(__CYGWIN__) || \
    defined(__APPLE__) || defined(__SUN__) || defined(__QNXNTO__)
    #define HAS_mktime    1 /* <time.h> */
    #define HAS_strftime  1 /* <time.h> */
    #define HAS_DIRENT_H  1 /* <dirent.h> */
#endif

#if defined(__CYGWIN__)
    #define HAS_strupr 1 /* <string.h> from libc (newlib) */
#endif

#if defined(__LINUX__) || defined(__BSD__)
    #define HAS_SYSLOG_H     1
    #define HAS_SYS_SYSLOG_H 1
#endif

#if defined(__QNXNTO__)
    #define HAS_sopen 1     /* <fcntl.h> */
    #define HAS_STRINGS_H 1
    #define HAS_SYSLOG_H 1
#endif

#  define HAS_popen_close 1 /* popen(); pclose() */


typedef unsigned bit;

typedef unsigned char byte;
typedef signed char sbyte;

typedef unsigned short word;
typedef signed short sword;

#if defined(__ALPHA__) || defined(__X86_64__)    /* add other 64 bit systems here */
    typedef unsigned int dword;
    typedef signed   int sdword;
#else             /* 32 and 16 bit machines */
    typedef unsigned long dword;
    typedef signed long sdword;
#endif


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

#if defined(__ALPHA__)      /* add other 64 bit systems here */
    typedef   signed long     hINT64;              /*  4 bytes */
    typedef   signed long    hSINT64;              /*  4 bytes */
    typedef unsigned long    hUINT64;              /*  4 bytes */
    #define HAS_INT64
#else
    #if __WORDSIZE == 64
        typedef long int        hINT64;              /*  8 bytes */
        typedef long int       hSINT64;              /*  8 bytes */
        typedef unsigned long int hUINT64;           /*  8 bytes */
        #define HAS_INT64
    #elif __GLIBC_HAVE_LONG_LONG
        typedef long long int   hINT64;              /*  8 bytes */
        typedef long long int  hSINT64;              /*  8 bytes */
        typedef unsigned long long int hUINT64;      /*  8 bytes */
        #define HAS_INT64
    #elif __GNUC__>2 || (__GNUC__==2 && __GNUC_MINOR__>=8)
        /* Test please GNU C before 2.8 ! (Stas Degteff) */
        typedef   signed long long  hINT64;          /*  8 bytes */
        typedef   signed long long hSINT64;          /*  8 bytes */
        typedef unsigned long long hUINT64;          /*  8 bytes */
        #define HAS_INT64
    #endif
#endif

#endif
