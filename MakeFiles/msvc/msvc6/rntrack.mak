# Microsoft Visual C++ NMAKE File.

PERL_BASEDIR=C:\Perl
!if defined(SCRIPTS_ENABLE)
!if ![perl perlconf.pl perlconf.tmp]
!if exists("perlconf.tmp")
!include "perlconf.tmp"
!if ![del "perlconf.tmp"]
!endif
!else
!error Can't include perlconf.tmp!
!endif
!else
!error Can't execute perlconf.pl!
!endif
EXEFILE=rntrack_perl.exe
!else
CPP_PERL=
LINK32_PERL=
EXEFILE=rntrack.exe
!endif

!IF "$(CFG)" == ""
CFG=rntrack - Win32 Debug
!MESSAGE No configuration specified. Defaulting to rntrack - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "rntrack - Win32 Release" && "$(CFG)" != "rntrack - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rntrack - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\$(EXEFILE)"

!ELSE 

ALL : "smapi - Win32 Release" "$(OUTDIR)\$(EXEFILE)"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"smapi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\age.obj"
	-@erase "$(INTDIR)\aix_conv.obj"
	-@erase "$(INTDIR)\aka.obj"
	-@erase "$(INTDIR)\attach.obj"
	-@erase "$(INTDIR)\badmsg.obj"
	-@erase "$(INTDIR)\badpkt.obj"
	-@erase "$(INTDIR)\cfg.obj"
	-@erase "$(INTDIR)\configure.obj"
	-@erase "$(INTDIR)\dirent.obj"
	-@erase "$(INTDIR)\domain.obj"
	-@erase "$(INTDIR)\fidoaddr.obj"
	-@erase "$(INTDIR)\filebox.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\help.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mask.obj"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\msgbase.obj"
	-@erase "$(INTDIR)\nodelist.obj"
	-@erase "$(INTDIR)\outbound.obj"
	-@erase "$(INTDIR)\parsetpl.obj"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\pktbase.obj"
	-@erase "$(INTDIR)\rntrack.obj"
	-@erase "$(INTDIR)\scandir.obj"
	-@erase "$(INTDIR)\script.obj"
	-@erase "$(INTDIR)\sqbase.obj"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\tmstamp.obj"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vars.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wildmat.obj"
	-@erase "$(OUTDIR)\$(EXEFILE)"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\hpp" /I "..\..\..\src" /D "NDEBUG" /D "_CONSOLE" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rntrack.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\rntrack.pdb" /machine:I386 /out:"$(OUTDIR)\$(EXEFILE)"
LINK32_OBJS= \
	"$(INTDIR)\age.obj" \
	"$(INTDIR)\aix_conv.obj" \
	"$(INTDIR)\aka.obj" \
	"$(INTDIR)\attach.obj" \
	"$(INTDIR)\badmsg.obj" \
	"$(INTDIR)\badpkt.obj" \
	"$(INTDIR)\cfg.obj" \
	"$(INTDIR)\configure.obj" \
	"$(INTDIR)\dirent.obj" \
	"$(INTDIR)\domain.obj" \
	"$(INTDIR)\fidoaddr.obj" \
	"$(INTDIR)\filebox.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\help.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mask.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\msgbase.obj" \
	"$(INTDIR)\nodelist.obj" \
	"$(INTDIR)\outbound.obj" \
	"$(INTDIR)\parsetpl.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\pktbase.obj" \
	"$(INTDIR)\rntrack.obj" \
	"$(INTDIR)\scandir.obj" \
	"$(INTDIR)\script.obj" \
	"$(INTDIR)\sqbase.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\tmstamp.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\vars.obj" \
	"$(INTDIR)\wildmat.obj" \
	".\smapi\Release\smapi.lib"

"$(OUTDIR)\$(EXEFILE)" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS) $(LINK32_PERL)
<<

!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\$(EXEFILE)" "$(OUTDIR)\rntrack.bsc"

!ELSE 

ALL : "smapi - Win32 Debug" "$(OUTDIR)\$(EXEFILE)" "$(OUTDIR)\rntrack.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"smapi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\age.obj"
	-@erase "$(INTDIR)\age.sbr"
	-@erase "$(INTDIR)\aix_conv.obj"
	-@erase "$(INTDIR)\aix_conv.sbr"
	-@erase "$(INTDIR)\aka.obj"
	-@erase "$(INTDIR)\aka.sbr"
	-@erase "$(INTDIR)\attach.obj"
	-@erase "$(INTDIR)\attach.sbr"
	-@erase "$(INTDIR)\badmsg.obj"
	-@erase "$(INTDIR)\badmsg.sbr"
	-@erase "$(INTDIR)\badpkt.obj"
	-@erase "$(INTDIR)\badpkt.sbr"
	-@erase "$(INTDIR)\cfg.obj"
	-@erase "$(INTDIR)\cfg.sbr"
	-@erase "$(INTDIR)\configure.obj"
	-@erase "$(INTDIR)\configure.sbr"
	-@erase "$(INTDIR)\dirent.obj"
	-@erase "$(INTDIR)\dirent.sbr"
	-@erase "$(INTDIR)\domain.obj"
	-@erase "$(INTDIR)\domain.sbr"
	-@erase "$(INTDIR)\fidoaddr.obj"
	-@erase "$(INTDIR)\fidoaddr.sbr"
	-@erase "$(INTDIR)\filebox.obj"
	-@erase "$(INTDIR)\filebox.sbr"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\getopt.sbr"
	-@erase "$(INTDIR)\help.obj"
	-@erase "$(INTDIR)\help.sbr"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\log.sbr"
	-@erase "$(INTDIR)\mask.obj"
	-@erase "$(INTDIR)\mask.sbr"
	-@erase "$(INTDIR)\msg.obj"
	-@erase "$(INTDIR)\msg.sbr"
	-@erase "$(INTDIR)\msgbase.obj"
	-@erase "$(INTDIR)\msgbase.sbr"
	-@erase "$(INTDIR)\nodelist.obj"
	-@erase "$(INTDIR)\nodelist.sbr"
	-@erase "$(INTDIR)\outbound.obj"
	-@erase "$(INTDIR)\outbound.sbr"
	-@erase "$(INTDIR)\parsetpl.obj"
	-@erase "$(INTDIR)\parsetpl.sbr"
	-@erase "$(INTDIR)\passwd.obj"
	-@erase "$(INTDIR)\passwd.sbr"
	-@erase "$(INTDIR)\pktbase.obj"
	-@erase "$(INTDIR)\pktbase.sbr"
	-@erase "$(INTDIR)\rntrack.obj"
	-@erase "$(INTDIR)\rntrack.sbr"
	-@erase "$(INTDIR)\scandir.obj"
	-@erase "$(INTDIR)\scandir.sbr"
	-@erase "$(INTDIR)\script.obj"
	-@erase "$(INTDIR)\script.sbr"
	-@erase "$(INTDIR)\sqbase.obj"
	-@erase "$(INTDIR)\sqbase.sbr"
	-@erase "$(INTDIR)\string.obj"
	-@erase "$(INTDIR)\string.sbr"
	-@erase "$(INTDIR)\tmstamp.obj"
	-@erase "$(INTDIR)\tmstamp.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vars.obj"
	-@erase "$(INTDIR)\vars.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wildmat.obj"
	-@erase "$(INTDIR)\wildmat.sbr"
	-@erase "$(OUTDIR)\rntrack.bsc"
	-@erase "$(OUTDIR)\$(EXEFILE)"
	-@erase "$(OUTDIR)\rntrack.ilk"
	-@erase "$(OUTDIR)\rntrack.map"
	-@erase "$(OUTDIR)\rntrack.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\..\hpp" /I "..\..\..\src" /D "_CONSOLE" /D "_DEBUG" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\rntrack.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\age.sbr" \
	"$(INTDIR)\aix_conv.sbr" \
	"$(INTDIR)\aka.sbr" \
	"$(INTDIR)\attach.sbr" \
	"$(INTDIR)\badmsg.sbr" \
	"$(INTDIR)\badpkt.sbr" \
	"$(INTDIR)\cfg.sbr" \
	"$(INTDIR)\configure.sbr" \
	"$(INTDIR)\dirent.sbr" \
	"$(INTDIR)\domain.sbr" \
	"$(INTDIR)\fidoaddr.sbr" \
	"$(INTDIR)\filebox.sbr" \
	"$(INTDIR)\getopt.sbr" \
	"$(INTDIR)\help.sbr" \
	"$(INTDIR)\log.sbr" \
	"$(INTDIR)\mask.sbr" \
	"$(INTDIR)\msg.sbr" \
	"$(INTDIR)\msgbase.sbr" \
	"$(INTDIR)\nodelist.sbr" \
	"$(INTDIR)\outbound.sbr" \
	"$(INTDIR)\parsetpl.sbr" \
	"$(INTDIR)\passwd.sbr" \
	"$(INTDIR)\pktbase.sbr" \
	"$(INTDIR)\rntrack.sbr" \
	"$(INTDIR)\scandir.sbr" \
	"$(INTDIR)\script.sbr" \
	"$(INTDIR)\sqbase.sbr" \
	"$(INTDIR)\string.sbr" \
	"$(INTDIR)\tmstamp.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\vars.sbr" \
	"$(INTDIR)\wildmat.sbr"

"$(OUTDIR)\rntrack.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.17 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\rntrack.pdb" /map:"$(INTDIR)\rntrack.map" /debug /machine:I386 /out:"$(OUTDIR)\$(EXEFILE)" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\age.obj" \
	"$(INTDIR)\aix_conv.obj" \
	"$(INTDIR)\aka.obj" \
	"$(INTDIR)\attach.obj" \
	"$(INTDIR)\badmsg.obj" \
	"$(INTDIR)\badpkt.obj" \
	"$(INTDIR)\cfg.obj" \
	"$(INTDIR)\configure.obj" \
	"$(INTDIR)\dirent.obj" \
	"$(INTDIR)\domain.obj" \
	"$(INTDIR)\fidoaddr.obj" \
	"$(INTDIR)\filebox.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\help.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mask.obj" \
	"$(INTDIR)\msg.obj" \
	"$(INTDIR)\msgbase.obj" \
	"$(INTDIR)\nodelist.obj" \
	"$(INTDIR)\outbound.obj" \
	"$(INTDIR)\parsetpl.obj" \
	"$(INTDIR)\passwd.obj" \
	"$(INTDIR)\pktbase.obj" \
	"$(INTDIR)\rntrack.obj" \
	"$(INTDIR)\scandir.obj" \
	"$(INTDIR)\script.obj" \
	"$(INTDIR)\sqbase.obj" \
	"$(INTDIR)\string.obj" \
	"$(INTDIR)\tmstamp.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\vars.obj" \
	"$(INTDIR)\wildmat.obj" \
	".\smapi\Debug\smapi.lib"

"$(OUTDIR)\$(EXEFILE)" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $(CPP_PERL) $<
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $(CPP_PERL) $<
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $(CPP_PERL) $<
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $(CPP_PERL) $<
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $(CPP_PERL) $<
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("rntrack.dep")
!INCLUDE "rntrack.dep"
!ELSE 
!MESSAGE Warning: cannot find "rntrack.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "rntrack - Win32 Release" || "$(CFG)" == "rntrack - Win32 Debug"
SOURCE=..\..\..\src\age.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\age.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\age.obj"	"$(INTDIR)\age.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\aix_conv.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\aix_conv.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\aix_conv.obj"	"$(INTDIR)\aix_conv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\aka.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\aka.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\aka.obj"	"$(INTDIR)\aka.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\attach.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\attach.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\attach.obj"	"$(INTDIR)\attach.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\badmsg.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\badmsg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\badmsg.obj"	"$(INTDIR)\badmsg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\badpkt.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\badpkt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\badpkt.obj"	"$(INTDIR)\badpkt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\cfg.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\cfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\cfg.obj"	"$(INTDIR)\cfg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\configure.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\configure.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\configure.obj"	"$(INTDIR)\configure.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\dirent.c

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\dirent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\dirent.obj"	"$(INTDIR)\dirent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\domain.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\domain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\domain.obj"	"$(INTDIR)\domain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\fidoaddr.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\fidoaddr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\fidoaddr.obj"	"$(INTDIR)\fidoaddr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\filebox.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\filebox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\filebox.obj"	"$(INTDIR)\filebox.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\getopt.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\getopt.obj"	"$(INTDIR)\getopt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\help.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\help.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\help.obj"	"$(INTDIR)\help.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\log.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\log.obj"	"$(INTDIR)\log.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\mask.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\mask.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\mask.obj"	"$(INTDIR)\mask.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\msg.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\msg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\msg.obj"	"$(INTDIR)\msg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\msgbase.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\msgbase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\msgbase.obj"	"$(INTDIR)\msgbase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\nodelist.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\nodelist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\nodelist.obj"	"$(INTDIR)\nodelist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\outbound.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\outbound.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\outbound.obj"	"$(INTDIR)\outbound.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\parsetpl.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\parsetpl.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\parsetpl.obj"	"$(INTDIR)\parsetpl.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\passwd.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\passwd.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\passwd.obj"	"$(INTDIR)\passwd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\pktbase.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\pktbase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\pktbase.obj"	"$(INTDIR)\pktbase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\rntrack.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\rntrack.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\rntrack.obj"	"$(INTDIR)\rntrack.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\scandir.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\scandir.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\scandir.obj"	"$(INTDIR)\scandir.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\script.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\script.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\script.obj"	"$(INTDIR)\script.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\sqbase.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\sqbase.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\sqbase.obj"	"$(INTDIR)\sqbase.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\string.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\string.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\string.obj"	"$(INTDIR)\string.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\tmstamp.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\tmstamp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\tmstamp.obj"	"$(INTDIR)\tmstamp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\utils.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\vars.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\vars.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\vars.obj"	"$(INTDIR)\vars.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\wildmat.cpp

!IF  "$(CFG)" == "rntrack - Win32 Release"


"$(INTDIR)\wildmat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"


"$(INTDIR)\wildmat.obj"	"$(INTDIR)\wildmat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(CPP_PERL) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "rntrack - Win32 Release"

"smapi - Win32 Release" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F ".\smapi.mak" CFG="smapi - Win32 Release" 
   cd ".."

"smapi - Win32 ReleaseCLEAN" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F ".\smapi.mak" CFG="smapi - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "rntrack - Win32 Debug"

"smapi - Win32 Debug" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F ".\smapi.mak" CFG="smapi - Win32 Debug" 
   cd ".."

"smapi - Win32 DebugCLEAN" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F ".\smapi.mak" CFG="smapi - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 

