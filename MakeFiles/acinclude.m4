dnl Autoconf M4 macros definitions for RNTrack
dnl
dnl 1. Define macro AC_PROG_PERL_VERSION: check version of the Perl interpreter.
dnl 2. Define macro AC_C_BIGENDIAN_CROSS: check bytes order (big endian or little endian) for cross-compiling or host-compiling.
dnl
dnl $Id:$

# Perl version check (imported from autoconf-archive package)
# (c) Dean Povey <povey@wedgetail.com>
# license AllPermissive
AC_DEFUN([AC_PROG_PERL_VERSION],[dnl
# Make sure we have perl
AC_CHECK_PROG(PERL,perl,perl)

# Check if version of Perl is sufficient
ac_perl_version="$1"
ac_perl_result="unknown"

if test "x$PERL" != "x"; then
  PERL_CFLAGS=`$PERL -MExtUtils::Embed -e ccopts`
  PERL_LFLAGS=`$PERL -MExtUtils::Embed -e ldopts`
  AC_SUBST(PERL_CFLAGS)
  AC_SUBST(PERL_LFLAGS)
  AC_MSG_CHECKING(for perl version greater than or equal to $ac_perl_version)
  # NB: It would be nice to log the error if there is one, but we cannot rely
  # on autoconf internals
  $PERL -e "use $ac_perl_version;" > /dev/null 2>&1
  if test $? -ne 0; then
    AC_MSG_RESULT(no);
    ac_perl_result="no";
    $3
  else
    AC_MSG_RESULT(ok);
    ac_perl_result="yes";
    $2
  fi
else
  AC_MSG_WARN(could not find perl)
fi
])dnl

# Byte order check (big-endian or little-endian)
#  (imported from autoconf-archive package)
# (c) Guido Draheim <guidod@gmx.de>
# license: GPL With AC Exception
AC_DEFUN([AC_C_BIGENDIAN_CROSS],
[AC_CACHE_CHECK(whether byte ordering is bigendian, ac_cv_c_bigendian,
[ac_cv_c_bigendian=unknown
# See if sys/param.h defines the BYTE_ORDER macro.
AC_TRY_COMPILE([#include <sys/types.h>
#include <sys/param.h>], [
#if !BYTE_ORDER || !BIG_ENDIAN || !LITTLE_ENDIAN
 bogus endian macros
#endif], [# It does; now see whether it defined to BIG_ENDIAN or not.
AC_TRY_COMPILE([#include <sys/types.h>
#include <sys/param.h>], [
#if BYTE_ORDER != BIG_ENDIAN
 not big endian
#endif], ac_cv_c_bigendian=yes, ac_cv_c_bigendian=no)])
if test $ac_cv_c_bigendian = unknown; then
AC_TRY_RUN([main () {
  /* Are we little or big endian?  From Harbison&Steele.  */
  union
  {
    long l;
    char c[sizeof (long)];
  } u;
  u.l = 1;
  exit (u.c[sizeof (long) - 1] == 1);
}], ac_cv_c_bigendian=no, ac_cv_c_bigendian=yes,
[ echo $ac_n "cross-compiling... " 2>&AC_FD_MSG ])
fi])
if test $ac_cv_c_bigendian = unknown; then
AC_MSG_CHECKING(to probe for byte ordering)
[
cat >conftest.c <<EOF
short ascii_mm[] = { 0x4249, 0x4765, 0x6E44, 0x6961, 0x6E53, 0x7953, 0 };
short ascii_ii[] = { 0x694C, 0x5454, 0x656C, 0x6E45, 0x6944, 0x6E61, 0 };
void _ascii() { char* s = (char*) ascii_mm; s = (char*) ascii_ii; }
short ebcdic_ii[] = { 0x89D3, 0xE3E3, 0x8593, 0x95C5, 0x89C4, 0x9581, 0 };
short ebcdic_mm[] = { 0xC2C9, 0xC785, 0x95C4, 0x8981, 0x95E2, 0xA8E2, 0 };
void _ebcdic() { char* s = (char*) ebcdic_mm; s = (char*) ebcdic_ii; }
int main() { _ascii (); _ebcdic (); return 0; }
EOF
] if test -f conftest.c ; then
     if ${CC-cc} -c conftest.c -o conftest.o && test -f conftest.o ; then
        if test `grep -l BIGenDianSyS conftest.o` ; then
           echo $ac_n ' big endian probe OK, ' 1>&AC_FD_MSG
           ac_cv_c_bigendian=yes
        fi
        if test `grep -l LiTTleEnDian conftest.o` ; then
           echo $ac_n ' little endian probe OK, ' 1>&AC_FD_MSG
           if test $ac_cv_c_bigendian = yes ; then
            ac_cv_c_bigendian=unknown;
           else
            ac_cv_c_bigendian=no
           fi
        fi
        echo $ac_n 'guessing bigendian ...  ' >&AC_FD_MSG
     fi
  fi
AC_MSG_RESULT($ac_cv_c_bigendian)
fi
if test $ac_cv_c_bigendian = yes; then
  AC_DEFINE(WORDS_BIGENDIAN, 1, [whether byteorder is bigendian])
fi
if test $ac_cv_c_bigendian = unknown; then
  AC_MSG_ERROR(unknown endianess - sorry, please pre-set ac_cv_c_bigendian)
fi
])
