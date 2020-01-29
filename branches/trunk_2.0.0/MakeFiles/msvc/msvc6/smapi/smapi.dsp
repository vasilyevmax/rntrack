# Microsoft Developer Studio Project File - Name="smapi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=smapi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smapi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smapi.mak" CFG="smapi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smapi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "smapi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "smapi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\..\smapi\h" /I "..\..\..\..\smapi\src" /D "NDEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /ZI /Od /I "..\..\..\..\smapi\h" /I "..\..\..\..\smapi\src" /D "_DEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "smapi - Win32 Release"
# Name "smapi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\..\smapi\src\api_jam.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\api_sdm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\date2bin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\dosdate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\fexist.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\ffind.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\flush.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\ftnaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\genmsgid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\gnmsgid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\locking.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\memory.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\months.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\msgapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\parsenn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\patmat.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\qksort.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\setfsize.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_area.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_help.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_idx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_kill.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_lock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_misc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_msg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_read.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_uid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\sq_write.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\strext.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\strftim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\structrw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\tdelay.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\trail.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\src\weekday.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_brow.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_jam.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_jamp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_sdm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_sdmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_sq.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\api_sqp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\apidebug.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\BCD.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\BCO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\BCW.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\BEOS5.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\BORLANDC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\compiler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\cvsdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\DJGPP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\dr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\EMX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\ffind.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\ftnaddr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\genmsgid.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\HIGHC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\IBMC_OS2.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\locking.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\memory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\MINGW32.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\months.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\MSC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\msgapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\MSVC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\old_msg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\patmat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\prog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\progprot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\pstdint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\SASC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\stamp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\strext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\typedefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\typesize.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\UNIX.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\unused.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\WATCOMC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\WCD.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\WCO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\WCW.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\smapi\h\WCX.h
# End Source File
# End Group
# End Target
# End Project
