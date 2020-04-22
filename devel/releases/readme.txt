Netmail tracker RNtrack X.XX.XXX
==============================
File naming scheme:
rntrack-M_NN_HH-PPPCCCCC-BBB.ZZZ

where:
"rntrack" : name of the program
 M        : Major version number
 NN       : Minor version number
 HH       : Patch number
 PPP      : Platform of binary (executable) file
            or abbreviation of content ("src", "doc")
 CCCC     : Compiler used for build (for some platforms only)
 BBB      : Build options ("perl" etc.)
 ZZZ      : File suffix indicates archive format

Examples.
1. rntrack-X_XX_XXX-w32msvs.zip
    RNtrack X.XX.XXX Win32 executable complied without support of Perl scripts
    using Miscrosoft Visual Studio. Includes documentation.
2. rntrack-X_XX_XXX-w64msvs.zip
    RNtrack X.XX.XXX Windows x64 executable complied without support of Perl scripts
    using Miscrosoft Visual Studio. Includes documentation.
3. rntrack-X_XX_XXX-src.tar.bz2
    RNtrack X.XX.XXX sources.
4. rntrack-X_XX_XXX-lnx-x86_64.tar.bz2
    RNtrack X.XX.XXX GNU/Linux binary,
    linked without support of Perl scripts. Includes documentation.
5. rntrack-X_XX_XXX-doc.zip
    RNtrack X.XX.XXX documentation.

X.XX.XXX XXXX-XX-XX (Subversion rev.XXXX, tag "version-X.XX.XXX")
------------------------------------------------------------

2.1.0 2020-04-22 (Subversion rev.323, tag "version-2.1.0")
----------------------------------------------------------
# do not pack messages when at least one of Locked, Sent,
  Archive/Sent attributes is set
# reset Received, Sent, KillSent, Local, Hold message attributes
  when packing the message to a packet
! fix date when a month name in the message header is not found
# add USE_CLANG=1 for using Clang compiler in linux

2.0.30 2020-02-14 (Subversion rev.295, tag "version-2.0.30")
------------------------------------------------------------
! fix FreeBSD build. Patch by Sergey Anohin 2:5034/10
# replace tag "version-2.0.26" by current tag

2.0.26 2020-02-12 (Subversion rev.291, tag "version-2.0.26")
------------------------------------------------------------
! remove lines from node1042 configuration sample trying
  to delete flags from a .pkt
! fix linux build with Perl
# small translation edits in English manual
! fix FreeBSD build. Patch by Sergey Anohin 2:5034/10

2.0.3 2020-01-31 (Subversion rev.260, tag "version-2.0.3")
----------------------------------------------------------
# add RNtrack configuration files from 2:5020/1042

2.0.2 2020-01-30 (Subversion rev.257)
------------------------------------
# upgrade smapi library from v.2.4.1 to v.2.5.1
! fix Visual Studio 6 build
# add Windows x64 build
# add Visual Studio 2019 solution
# update Russian manual
# make a new translation of the amended manual from Russian into English
# add manual in the form of man-pages and plain text in English
# change default path of configuration file: "~/fido/etc/rntrack.conf" under
  a UNIX-like OS, "%USERPROFILE%\fido\rntrack.cfg" under Windows or
  "rntrack.cfg" under another OS
# change the log date format to ISO 8601

1.41 2019-09-29 (Subversion rev.191)
-----------------------------------
# add a log message at LogLevel=2 with full path of the created pkt.

1.40 2019-09-29 (Subversion rev.190)
-----------------------------------
! test simple boolean value before testing a function value.
! fix compatibility with new portage version, add 1.39 version for gentoo.

1.39 2019-06-14 (Subversion rev.188)
-----------------------------------
# change fonts in Manual_ru.odt.
! fix small issues in README, INSTALL and BUG-REPORTING.
! Create solution for a build using MS Visual C++ 2010
  and fix sources for that.

1.38 2019-06-08 (Subversion rev.184)
-----------------------------------
! Fix variable initialization.
! Fix defined and/or set but unused variables.
! Fix conversion from string constant to ‘char *’.
! Fix similar issue breaking strict-aliasing rules in sqbase.cpp.
! Fix dereferencing type-punned pointer breaking strict-aliasing rules in api_sdm.c.

1.37 2019-06-07 (Subversion rev.179)
-----------------------------------
! Fix build under FreeBSD 12.0. Patch by andrew clarke 3:633/267.
! Fix build under linux (Ubuntu server 18.04 LTS). Patch by mark lewis 1:3634/12.

1.36 2018-08-25 (Subversion rev.174)
-----------------------------------
! Fix a bug in not deleting a flag after ScanDir of an empty base.
  Bug report by Alex Barinov 2:5020/715

1.35 2018-08-25 (Subversion rev.172)
-----------------------------------
! Fix a bug in setting message attributes.
  Bug report by Alex Barinov 2:5020/715

1.34 2018-08-25 (Subversion rev.171)
-----------------------------------
! Gentoo linux: fix repository path in layman config
! Share presence check. Patch by Max Vasilyev 2:5057/77
# Add man page to linux makefile
# Add rntrack.spec for .rpm build
! Remove recursion in a makefile variable definition.
  Thanks to Benny Pedersen 2:230/38
! Change deprecated AM_PROG_INSTALL macro for AC_PROG_INSTALL one
! Fix erroneously overwriting timesRead msg field with a point number

1.33 2013-01-08 (Subversion rev.161)
-----------------------------------
! DJGPP makefile fixed. Patch by Max Vasilyev 2:5057/77
! Mingw32 makefile was fixed for the case with no scripts support
# Gentoo linux ebuild
! An incorrect log message for Action: AddNote was fixed

1.32 2011-04-26 (Subversion rev.156)
-----------------------------------
# Some editorial changes in the manual
! A syntax error was fixed in the manual text
! A bug in comparing a text to a mask was fixed
