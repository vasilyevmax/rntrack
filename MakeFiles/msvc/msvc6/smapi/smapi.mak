# Microsoft Developer Studio Generated NMAKE File, Based on smapi.dsp
!IF "$(CFG)" == ""
CFG=smapi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to smapi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "smapi - Win32 Release" && "$(CFG)" != "smapi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "smapi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\smapi.lib"


CLEAN :
	-@erase "$(INTDIR)\api_jam.obj"
	-@erase "$(INTDIR)\api_sdm.obj"
	-@erase "$(INTDIR)\date2bin.obj"
	-@erase "$(INTDIR)\dosdate.obj"
	-@erase "$(INTDIR)\fexist.obj"
	-@erase "$(INTDIR)\ffind.obj"
	-@erase "$(INTDIR)\flush.obj"
	-@erase "$(INTDIR)\ftnaddr.obj"
	-@erase "$(INTDIR)\genmsgid.obj"
	-@erase "$(INTDIR)\gnmsgid.obj"
	-@erase "$(INTDIR)\locking.obj"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\months.obj"
	-@erase "$(INTDIR)\msgapi.obj"
	-@erase "$(INTDIR)\parsenn.obj"
	-@erase "$(INTDIR)\patmat.obj"
	-@erase "$(INTDIR)\qksort.obj"
	-@erase "$(INTDIR)\setfsize.obj"
	-@erase "$(INTDIR)\sq_area.obj"
	-@erase "$(INTDIR)\sq_hash.obj"
	-@erase "$(INTDIR)\sq_help.obj"
	-@erase "$(INTDIR)\sq_idx.obj"
	-@erase "$(INTDIR)\sq_kill.obj"
	-@erase "$(INTDIR)\sq_lock.obj"
	-@erase "$(INTDIR)\sq_misc.obj"
	-@erase "$(INTDIR)\sq_msg.obj"
	-@erase "$(INTDIR)\sq_read.obj"
	-@erase "$(INTDIR)\sq_uid.obj"
	-@erase "$(INTDIR)\sq_write.obj"
	-@erase "$(INTDIR)\strext.obj"
	-@erase "$(INTDIR)\strftim.obj"
	-@erase "$(INTDIR)\structrw.obj"
	-@erase "$(INTDIR)\tdelay.obj"
	-@erase "$(INTDIR)\trail.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\weekday.obj"
	-@erase "$(OUTDIR)\smapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\..\smapi\h" /I "..\..\..\..\smapi\src" /D "NDEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smapi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\smapi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\api_jam.obj" \
	"$(INTDIR)\api_sdm.obj" \
	"$(INTDIR)\date2bin.obj" \
	"$(INTDIR)\dosdate.obj" \
	"$(INTDIR)\fexist.obj" \
	"$(INTDIR)\ffind.obj" \
	"$(INTDIR)\flush.obj" \
	"$(INTDIR)\ftnaddr.obj" \
	"$(INTDIR)\genmsgid.obj" \
	"$(INTDIR)\gnmsgid.obj" \
	"$(INTDIR)\locking.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\months.obj" \
	"$(INTDIR)\msgapi.obj" \
	"$(INTDIR)\parsenn.obj" \
	"$(INTDIR)\patmat.obj" \
	"$(INTDIR)\qksort.obj" \
	"$(INTDIR)\setfsize.obj" \
	"$(INTDIR)\sq_area.obj" \
	"$(INTDIR)\sq_hash.obj" \
	"$(INTDIR)\sq_help.obj" \
	"$(INTDIR)\sq_idx.obj" \
	"$(INTDIR)\sq_kill.obj" \
	"$(INTDIR)\sq_lock.obj" \
	"$(INTDIR)\sq_misc.obj" \
	"$(INTDIR)\sq_msg.obj" \
	"$(INTDIR)\sq_read.obj" \
	"$(INTDIR)\sq_uid.obj" \
	"$(INTDIR)\sq_write.obj" \
	"$(INTDIR)\strext.obj" \
	"$(INTDIR)\strftim.obj" \
	"$(INTDIR)\structrw.obj" \
	"$(INTDIR)\tdelay.obj" \
	"$(INTDIR)\trail.obj" \
	"$(INTDIR)\weekday.obj"

"$(OUTDIR)\smapi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\smapi.lib" "$(OUTDIR)\smapi.bsc"


CLEAN :
	-@erase "$(INTDIR)\api_jam.obj"
	-@erase "$(INTDIR)\api_jam.sbr"
	-@erase "$(INTDIR)\api_sdm.obj"
	-@erase "$(INTDIR)\api_sdm.sbr"
	-@erase "$(INTDIR)\date2bin.obj"
	-@erase "$(INTDIR)\date2bin.sbr"
	-@erase "$(INTDIR)\dosdate.obj"
	-@erase "$(INTDIR)\dosdate.sbr"
	-@erase "$(INTDIR)\fexist.obj"
	-@erase "$(INTDIR)\fexist.sbr"
	-@erase "$(INTDIR)\ffind.obj"
	-@erase "$(INTDIR)\ffind.sbr"
	-@erase "$(INTDIR)\flush.obj"
	-@erase "$(INTDIR)\flush.sbr"
	-@erase "$(INTDIR)\ftnaddr.obj"
	-@erase "$(INTDIR)\ftnaddr.sbr"
	-@erase "$(INTDIR)\genmsgid.obj"
	-@erase "$(INTDIR)\genmsgid.sbr"
	-@erase "$(INTDIR)\gnmsgid.obj"
	-@erase "$(INTDIR)\gnmsgid.sbr"
	-@erase "$(INTDIR)\locking.obj"
	-@erase "$(INTDIR)\locking.sbr"
	-@erase "$(INTDIR)\memory.obj"
	-@erase "$(INTDIR)\memory.sbr"
	-@erase "$(INTDIR)\months.obj"
	-@erase "$(INTDIR)\months.sbr"
	-@erase "$(INTDIR)\msgapi.obj"
	-@erase "$(INTDIR)\msgapi.sbr"
	-@erase "$(INTDIR)\parsenn.obj"
	-@erase "$(INTDIR)\parsenn.sbr"
	-@erase "$(INTDIR)\patmat.obj"
	-@erase "$(INTDIR)\patmat.sbr"
	-@erase "$(INTDIR)\qksort.obj"
	-@erase "$(INTDIR)\qksort.sbr"
	-@erase "$(INTDIR)\setfsize.obj"
	-@erase "$(INTDIR)\setfsize.sbr"
	-@erase "$(INTDIR)\sq_area.obj"
	-@erase "$(INTDIR)\sq_area.sbr"
	-@erase "$(INTDIR)\sq_hash.obj"
	-@erase "$(INTDIR)\sq_hash.sbr"
	-@erase "$(INTDIR)\sq_help.obj"
	-@erase "$(INTDIR)\sq_help.sbr"
	-@erase "$(INTDIR)\sq_idx.obj"
	-@erase "$(INTDIR)\sq_idx.sbr"
	-@erase "$(INTDIR)\sq_kill.obj"
	-@erase "$(INTDIR)\sq_kill.sbr"
	-@erase "$(INTDIR)\sq_lock.obj"
	-@erase "$(INTDIR)\sq_lock.sbr"
	-@erase "$(INTDIR)\sq_misc.obj"
	-@erase "$(INTDIR)\sq_misc.sbr"
	-@erase "$(INTDIR)\sq_msg.obj"
	-@erase "$(INTDIR)\sq_msg.sbr"
	-@erase "$(INTDIR)\sq_read.obj"
	-@erase "$(INTDIR)\sq_read.sbr"
	-@erase "$(INTDIR)\sq_uid.obj"
	-@erase "$(INTDIR)\sq_uid.sbr"
	-@erase "$(INTDIR)\sq_write.obj"
	-@erase "$(INTDIR)\sq_write.sbr"
	-@erase "$(INTDIR)\strext.obj"
	-@erase "$(INTDIR)\strext.sbr"
	-@erase "$(INTDIR)\strftim.obj"
	-@erase "$(INTDIR)\strftim.sbr"
	-@erase "$(INTDIR)\structrw.obj"
	-@erase "$(INTDIR)\structrw.sbr"
	-@erase "$(INTDIR)\tdelay.obj"
	-@erase "$(INTDIR)\tdelay.sbr"
	-@erase "$(INTDIR)\trail.obj"
	-@erase "$(INTDIR)\trail.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\weekday.obj"
	-@erase "$(INTDIR)\weekday.sbr"
	-@erase "$(OUTDIR)\smapi.bsc"
	-@erase "$(OUTDIR)\smapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /I "..\..\..\..\smapi\h" /I "..\..\..\..\smapi\src" /D "_DEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smapi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\api_jam.sbr" \
	"$(INTDIR)\api_sdm.sbr" \
	"$(INTDIR)\date2bin.sbr" \
	"$(INTDIR)\dosdate.sbr" \
	"$(INTDIR)\fexist.sbr" \
	"$(INTDIR)\ffind.sbr" \
	"$(INTDIR)\flush.sbr" \
	"$(INTDIR)\ftnaddr.sbr" \
	"$(INTDIR)\genmsgid.sbr" \
	"$(INTDIR)\gnmsgid.sbr" \
	"$(INTDIR)\locking.sbr" \
	"$(INTDIR)\memory.sbr" \
	"$(INTDIR)\months.sbr" \
	"$(INTDIR)\msgapi.sbr" \
	"$(INTDIR)\parsenn.sbr" \
	"$(INTDIR)\patmat.sbr" \
	"$(INTDIR)\qksort.sbr" \
	"$(INTDIR)\setfsize.sbr" \
	"$(INTDIR)\sq_area.sbr" \
	"$(INTDIR)\sq_hash.sbr" \
	"$(INTDIR)\sq_help.sbr" \
	"$(INTDIR)\sq_idx.sbr" \
	"$(INTDIR)\sq_kill.sbr" \
	"$(INTDIR)\sq_lock.sbr" \
	"$(INTDIR)\sq_misc.sbr" \
	"$(INTDIR)\sq_msg.sbr" \
	"$(INTDIR)\sq_read.sbr" \
	"$(INTDIR)\sq_uid.sbr" \
	"$(INTDIR)\sq_write.sbr" \
	"$(INTDIR)\strext.sbr" \
	"$(INTDIR)\strftim.sbr" \
	"$(INTDIR)\structrw.sbr" \
	"$(INTDIR)\tdelay.sbr" \
	"$(INTDIR)\trail.sbr" \
	"$(INTDIR)\weekday.sbr"

"$(OUTDIR)\smapi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\smapi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\api_jam.obj" \
	"$(INTDIR)\api_sdm.obj" \
	"$(INTDIR)\date2bin.obj" \
	"$(INTDIR)\dosdate.obj" \
	"$(INTDIR)\fexist.obj" \
	"$(INTDIR)\ffind.obj" \
	"$(INTDIR)\flush.obj" \
	"$(INTDIR)\ftnaddr.obj" \
	"$(INTDIR)\genmsgid.obj" \
	"$(INTDIR)\gnmsgid.obj" \
	"$(INTDIR)\locking.obj" \
	"$(INTDIR)\memory.obj" \
	"$(INTDIR)\months.obj" \
	"$(INTDIR)\msgapi.obj" \
	"$(INTDIR)\parsenn.obj" \
	"$(INTDIR)\patmat.obj" \
	"$(INTDIR)\qksort.obj" \
	"$(INTDIR)\setfsize.obj" \
	"$(INTDIR)\sq_area.obj" \
	"$(INTDIR)\sq_hash.obj" \
	"$(INTDIR)\sq_help.obj" \
	"$(INTDIR)\sq_idx.obj" \
	"$(INTDIR)\sq_kill.obj" \
	"$(INTDIR)\sq_lock.obj" \
	"$(INTDIR)\sq_misc.obj" \
	"$(INTDIR)\sq_msg.obj" \
	"$(INTDIR)\sq_read.obj" \
	"$(INTDIR)\sq_uid.obj" \
	"$(INTDIR)\sq_write.obj" \
	"$(INTDIR)\strext.obj" \
	"$(INTDIR)\strftim.obj" \
	"$(INTDIR)\structrw.obj" \
	"$(INTDIR)\tdelay.obj" \
	"$(INTDIR)\trail.obj" \
	"$(INTDIR)\weekday.obj"

"$(OUTDIR)\smapi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("smapi.dep")
!INCLUDE "smapi.dep"
!ELSE 
!MESSAGE Warning: cannot find "smapi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "smapi - Win32 Release" || "$(CFG)" == "smapi - Win32 Debug"
SOURCE=..\..\..\..\smapi\src\api_jam.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\api_jam.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\api_jam.obj"	"$(INTDIR)\api_jam.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\api_sdm.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\api_sdm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\api_sdm.obj"	"$(INTDIR)\api_sdm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\date2bin.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\date2bin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\date2bin.obj"	"$(INTDIR)\date2bin.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\dosdate.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\dosdate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\dosdate.obj"	"$(INTDIR)\dosdate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\fexist.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\fexist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\fexist.obj"	"$(INTDIR)\fexist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\ffind.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\ffind.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\ffind.obj"	"$(INTDIR)\ffind.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\flush.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\flush.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\flush.obj"	"$(INTDIR)\flush.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\ftnaddr.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\ftnaddr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\ftnaddr.obj"	"$(INTDIR)\ftnaddr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\genmsgid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\genmsgid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\genmsgid.obj"	"$(INTDIR)\genmsgid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\gnmsgid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\gnmsgid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\gnmsgid.obj"	"$(INTDIR)\gnmsgid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\locking.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\locking.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\locking.obj"	"$(INTDIR)\locking.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\memory.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\memory.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\memory.obj"	"$(INTDIR)\memory.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\months.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\months.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\months.obj"	"$(INTDIR)\months.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\msgapi.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\msgapi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\msgapi.obj"	"$(INTDIR)\msgapi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\parsenn.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\parsenn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\parsenn.obj"	"$(INTDIR)\parsenn.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\patmat.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\patmat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\patmat.obj"	"$(INTDIR)\patmat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\qksort.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\qksort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\qksort.obj"	"$(INTDIR)\qksort.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\setfsize.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\setfsize.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\setfsize.obj"	"$(INTDIR)\setfsize.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_area.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_area.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_area.obj"	"$(INTDIR)\sq_area.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_hash.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_hash.obj"	"$(INTDIR)\sq_hash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_help.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_help.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_help.obj"	"$(INTDIR)\sq_help.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_idx.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_idx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_idx.obj"	"$(INTDIR)\sq_idx.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_kill.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_kill.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_kill.obj"	"$(INTDIR)\sq_kill.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_lock.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_lock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_lock.obj"	"$(INTDIR)\sq_lock.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_misc.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_misc.obj"	"$(INTDIR)\sq_misc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_msg.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_msg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_msg.obj"	"$(INTDIR)\sq_msg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_read.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_read.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_read.obj"	"$(INTDIR)\sq_read.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_uid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_uid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_uid.obj"	"$(INTDIR)\sq_uid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\sq_write.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_write.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_write.obj"	"$(INTDIR)\sq_write.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\strext.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\strext.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\strext.obj"	"$(INTDIR)\strext.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\strftim.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\strftim.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\strftim.obj"	"$(INTDIR)\strftim.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\structrw.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\structrw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\structrw.obj"	"$(INTDIR)\structrw.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\tdelay.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\tdelay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\tdelay.obj"	"$(INTDIR)\tdelay.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\trail.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\trail.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\trail.obj"	"$(INTDIR)\trail.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\smapi\src\weekday.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\weekday.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\weekday.obj"	"$(INTDIR)\weekday.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

