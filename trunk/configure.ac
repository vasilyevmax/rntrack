# RNtrack                                      -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
# $Id:$

AC_INIT(RNtrack, 1.13, stas_degteff@users.sourceforge.net)
AC_CONFIG_SRCDIR(src/rntrack.cpp)
AC_CONFIG_AUX_DIR(MakeFiles)
AC_CANONICAL_SYSTEM
#AC_PREREQ(2.59)
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(hpp/aconfig.h:hpp/aconfig.hin)

# Checks for programs.
#AM_PROG_LEX
#AC_PROG_YACC
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_RANLIB
#AM_PROG_LIBTOOL
AM_PROG_INSTALL
AC_CHECK_PROG(PERL,perl,perl)

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h locale.h malloc.h stddef.h unistd.h utime.h sys/utime.h io.h time.h iostream iostream.h direct.h])
dnl AC_CHECK_HEADERS([OS.h])dnl For smapi only

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STAT
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)


# Checks for library functions.
dnl AC_FUNC_CLOSEDIR_VOID
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_REALLOC
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_UTIME_NULL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([setlocale stricmp strcasecmp tzset utime])dnl for rntrack/src
dnl AC_CHECK_FUNCS([alarm ftruncate rmdir _rmdir ])dnl For smapi only

# Byteorder check
AC_C_BIGENDIAN_CROSS
if test $ac_cv_c_bigendian = yes; then
 AC_DEFINE(_AIX_CONV,1,[Need rotate byte order])
fi

# OS type
case "$target" in
 *-*linux*   )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(__linux__,1,[OS is Linux])
  ;;
 *-*freebsd* )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(__FreeBSD__,1,[OS is FreeBSD])
  ;;
 *-*openbsd* )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(__OpenBSD__,1,[OS is OpenBSD])
  ;;
 *-*netbsd*  )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(__NetBSD__,1,[OS is NetBSD])
  ;;
 *-*solaris* )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(__sun__,1,[OS is Sun Solaris])
  ;;
 *-*aix*     )
  AC_DEFINE(unix,1,[OS is Unix])
  AC_DEFINE(_AIX,1,[OS is IBM AIX])
  ;;
 *-*darwin*  )
  AC_DEFINE(__OSX__,1,[OS is Apple MacOS X])
  ;;
 *-*mingw32* )
  AC_DEFINE(__NT__,1,[OS is Win32])
  ;;
 *-*djgpp*   )
  AC_DEFINE(__DJGPP__,1,[OS is DOS])
  AC_DEFINE(__DOS4G__,1,[DOS protected mode])
  ;;
 *-*os2-emx* )
  AC_DEFINE(__OS2__,1,[OS is IBM OS/2])
  AC_DEFINE(__EMX__,1,[OS/2 EMX])
  ;;
esac

AC_DEFINE_UNQUOTED(__PLATFORM_TYPE__,$target_os,[target platform])

# EOF OS-specific


# Optional arguments

AC_ARG_ENABLE(log-pid,           [  --enable-log-pid			enable pid logging ],
  AC_DEFINE(LOG_SHOW_PID,1,[enable pid logging]) )
AC_ARG_ENABLE(syslog-log-format, [  --enable-syslog-log-format		syslog-like log structure ],
  AC_DEFINE(SYSLOG_LOG_FORMAT,1,[syslog-like log structure]) )
AC_ARG_ENABLE(scripts,		 [  --enable-scripts			enable Perl-scripting (auto)],
  [if test $enableval = yes; then
   AC_PROG_PERL_VERSION(5.8.0)
   if test $ac_perl_result = yes; then
	AC_DEFINE(__PERL_NEW__,1,[Perl 5.8+ installed])
   fi
  fi],
  AC_DEFINE(__NOSCRIPTS__,1,[disable Perl-scripting]) )
# EOF Optional arguments


AC_CONFIG_FILES([Makefile
		 src/smapi/Makefile
		 src/Makefile])
AC_OUTPUT
