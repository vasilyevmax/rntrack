/* $Id$
 *  Microsoft Visual C/C++ compiler-specific declarations
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also http://www.gnu.org, license may be found here.
 */

/* MS Visual C/C++ */

#ifndef SMAPI_MSVC_H
    #define SMAPI_MSVC_H
    #ifndef _MSC_VER
        #error This file used only with MS Visual C !
    #endif

    #if _MSC_VER<1000
        #error This file used only with MS Visual C !
    #endif

    #if _MSC_VER<1200
        #error We can't build RNtrack on your MS Visual C version, sorry.
    #endif

    #ifdef _MAKE_DLL
        #define _MAKE_DLL_MVC_
        #ifndef _SMAPI_EXT
            #define SMAPI_EXT __declspec(dllimport)
        #else
            #define SMAPI_EXT __declspec(dllexport)
        #endif /* _SMAPI_EXT */
    #else  /* ifdef _MAKE_DLL */
        #define SMAPI_EXT    extern
    #endif /* ifdef _MAKE_DLL */
    /* must be included before function redefenition like '#define fileno _fileno' */
    #include <sys/stat.h>
    #include <stdio.h>
    #include <io.h>
    #include <direct.h>
    #include <process.h>
    /* system functions substitutions for DLL build */
    #define fileno       _fileno
    #define read         _read
    #define lseek        _lseek
    #define sopen        _sopen
    #define write        _write
    #define tell         _tell
    #define close        _close
    #define unlink       _unlink
    #define tzset        _tzset
    #define stricmp      _stricmp
    #define strnicmp     _strnicmp
    #define fstat        _fstat
    #define strdup       _strdup
    #define strupr       _strupr
    #define strlwr       _strlwr
    #define stat         _stat
    #define getpid       _getpid
    #define chsize       _chsize
    #define open         _open
    #define access       _access
    #define spawnvp      _spawnvp
    #define spawnl       _spawnl
    #define dup          _dup
    #define mktemp       _mktemp
    #define fdopen       _fdopen
    #define chdir        _chdir
    #define getcwd       _getcwd
    #define isatty       _isatty

    #include <limits.h>
    #ifndef MAXPATHLEN
        #define MAXPATHLEN _MAX_PATH
    #endif

    /* must be included before macro redefenition '# define SH_DENYNONE _SH_DENYNO' */
    #include <share.h>
    #ifndef SH_DENYNONE
        #ifdef _SH_DENYNO
            #define SH_DENYNONE _SH_DENYNO
        #else
            #pragma message("Please set SH_DENYNONE to proprietary value: used for file locking")
        #endif
    #endif
    #ifndef SH_DENYNO
        #ifdef SH_DENYNONE
            #define SH_DENYNO SH_DENYNONE
        #else
            #pragma message("Please set SH_DENYNO to proprietary value: used for file locking")
        #endif
    #endif
    /* must be included before function redefenition '#define P_WAIT _P_WAIT'  */
    #include <process.h>
    #ifndef P_WAIT
        #ifdef _P_WAIT
            #define P_WAIT       _P_WAIT   /* process.h */
        #else
            #pragma message("Please set P_WAIT to proprietary value: used for spawnvp() call")
        #endif
    #endif

    #define _stdc
    #ifndef pascal
        #define pascal
    #endif
    #ifndef far
        #define far
    #endif
    #define _fast
    #define near
    #define _XPENTRY
    #define _intr
    #define _intcast
    #define _veccast
    #define _loadds
    #define cdecl

    #define strcasecmp  stricmp
    #define strncasecmp strnicmp

    #define sleep(x)    Sleep(1000L*(x))
    #define mysleep(x)  Sleep(1000L*(x))
    #define farread     read
    #define farwrite    write

    #define mode_t int

    /* define macrofunctions for fexist.c */
    #ifndef S_ISDIR
        #define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
    #endif
    #ifndef S_ISREG
        #define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
    #endif

    /* define constants for 2nd parameter of access() function */
    #ifndef F_OK                  /* does file exist */
        #define F_OK 0
    #endif

    #ifndef X_OK                  /* is it executable by caller */
        #define X_OK  1
    #endif

    #ifndef R_OK                  /* is it readable by caller */
        #define R_OK 04
    #endif

    #ifndef W_OK                  /* is it writable by caller */
        #define W_OK 02
    #endif

    #define mymkdir       _mkdir
    #define snprintf      _snprintf
    #define vsnprintf     _vsnprintf
    #define HAS_snprintf       /* snprintf() presents */
    #define HAS_vsnprintf      /* vsnprintf() presents */
    #define HAS_spawnvp        /* spawnwp() presents */
    #define HAS_strftime
    #define HAS_mktime
    #define HAS_sopen
    #define HAS_sleep
    #define HAS_strupr

    #define USE_SYSTEM_COPY     /* OS have system call for files copiing */
    #define USE_SYSTEM_COPY_WIN32
    #define USE_STAT_MACROS     /* S_ISDIR, S_ISREG and stat() presents */

    #define HAS_IO_H         /* may use "#include <io.h> */
    #define HAS_SHARE_H      /* may use "#include <share.h> */
    #define HAS_MALLOC_H     /* use "#include <malloc.h>" for malloc() etc. */
    #define HAS_SYS_UTIME_H  /* #include <sys/utime.h> in alternate to <utime.h> */
    #define HAS_DIRECT_H     /* #include <direct.h> */
    #define HAS_PROCESS_H   /* may use "#include <process.h> */

    typedef unsigned bit;

    typedef unsigned char byte;
    typedef signed char sbyte;

    typedef unsigned short word;
    typedef signed short sword;

    #if defined(__ALPHA__) || defined(__X86_64__)    /* 64 bit system */
        typedef unsigned int dword;
        typedef signed   int sdword;
    #else             /* 32 and 16 bit machines */
        typedef unsigned long dword;
        typedef signed long sdword;
    #endif

    typedef signed short sshort;
    typedef unsigned short ushort;

    typedef signed long slong;
    typedef unsigned long ulong;

    typedef   signed char        hCHAR;              /*  1 byte */
    typedef   signed char       hSCHAR;              /*  1 byte */
    typedef unsigned char       hUCHAR;              /*  1 byte */

    typedef   signed __int8      hINT8;              /*  1 byte */
    typedef   signed __int8     hSINT8;              /*  1 byte */
    typedef unsigned __int8     hUINT8;              /*  1 byte */

    typedef   signed __int16    hINT16;              /*  2 bytes */
    typedef   signed __int16   hSINT16;              /*  2 bytes */
    typedef unsigned __int16   hUINT16;              /*  2 bytes */

    typedef   signed __int32    hINT32;              /*  4 bytes */
    typedef   signed __int32   hSINT32;              /*  4 bytes */
    typedef unsigned __int32   hUINT32;              /*  4 bytes */

    #if defined(__ALPHA__) || defined(__X86_64__)    /* 64 bit system */
        typedef   signed __int64    hINT64;          /*  8 bytes */
        typedef   signed __int64   hSINT64;          /*  8 bytes */
        typedef unsigned __int64   hUINT64;          /*  8 bytes */
        #define HAS_INT64
    #endif /* 64 bit system */
#endif
