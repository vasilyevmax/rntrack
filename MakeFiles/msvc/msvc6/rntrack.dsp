# Microsoft Developer Studio Project File - Name="rntrack" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=rntrack - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rntrack.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rntrack.mak" CFG="rntrack - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rntrack - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "rntrack - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rntrack - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\hpp" /I "..\..\..\src" /D "NDEBUG" /D "_CONSOLE" /D "__NT__" /D "__NOSCRIPTS__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\hpp" /I "..\..\..\src" /D "_CONSOLE" /D "_DEBUG" /D "__NT__" /D "__NOSCRIPTS__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.17 /subsystem:console /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "rntrack - Win32 Release"
# Name "rntrack - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\age.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\aix_conv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\aka.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\attach.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\badmsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\badpkt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cfg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\configure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dirent.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\domain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\fidoaddr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\filebox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\getopt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\help.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mask.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\msg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\msgbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\nodelist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\outbound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\parsetpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\passwd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\pktbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rntrack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\scandir.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\script.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sqbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tmstamp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\utils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vars.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\wildmat.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\hpp\a_list.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\age.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\aix_conv.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\aka.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\attach.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\badmsg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\badpkt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\configure.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\constant.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\dirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\domain.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\fidoaddr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\filebox.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\getopt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\help.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\log.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\mask.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\msg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\msgbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\mytypes.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\nodelist.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\outbound.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\parsetpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\passwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\pktbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\scandir.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\script.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\sqbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\tmstamp.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\tpkt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\smapi\typedefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\utils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\vars.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\wildmat.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
