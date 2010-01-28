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
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FD /c
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
# ADD CPP /nologo /W3 /Gm /ZI /Od /D "_DEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR /FD /GZ /c
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

SOURCE=..\..\..\..\src\smapi\1stchar.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_jam.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_sdm.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\cvtdate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\date2bin.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\dosdate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\fexist.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\ffind.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\flush.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\genmsgid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\gnmsgid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\locking.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\months.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\msgapi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\parsenn.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\patmat.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\qksort.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\setfsize.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_area.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_hash.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_help.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_idx.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_kill.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_lock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_misc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_msg.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_read.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_uid.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\sq_write.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\strextra.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\strftim.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\strocpy.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\structrw.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\tdelay.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\trail.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\weekday.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_brow.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_jam.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_jamp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_sdm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_sdmp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_sq.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\api_sqp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\apidebug.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\compiler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\cvsdate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\dr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\ffind.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\msgapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\old_msg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\patmat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\prog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\progprot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\stamp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\strextra.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\typedefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\src\smapi\unused.h
# End Source File
# End Group
# End Target
# End Project
