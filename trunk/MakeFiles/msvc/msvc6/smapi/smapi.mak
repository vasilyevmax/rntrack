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

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "smapi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\smapi.lib"


CLEAN :
	-@erase "$(INTDIR)\1stchar.obj"
	-@erase "$(INTDIR)\api_jam.obj"
	-@erase "$(INTDIR)\api_sdm.obj"
	-@erase "$(INTDIR)\cvtdate.obj"
	-@erase "$(INTDIR)\date2bin.obj"
	-@erase "$(INTDIR)\dosdate.obj"
	-@erase "$(INTDIR)\fexist.obj"
	-@erase "$(INTDIR)\ffind.obj"
	-@erase "$(INTDIR)\flush.obj"
	-@erase "$(INTDIR)\genmsgid.obj"
	-@erase "$(INTDIR)\gnmsgid.obj"
	-@erase "$(INTDIR)\locking.obj"
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
	-@erase "$(INTDIR)\strextra.obj"
	-@erase "$(INTDIR)\strftim.obj"
	-@erase "$(INTDIR)\strocpy.obj"
	-@erase "$(INTDIR)\structrw.obj"
	-@erase "$(INTDIR)\tdelay.obj"
	-@erase "$(INTDIR)\trail.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\weekday.obj"
	-@erase "$(OUTDIR)\smapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smapi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\smapi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\1stchar.obj" \
	"$(INTDIR)\api_jam.obj" \
	"$(INTDIR)\api_sdm.obj" \
	"$(INTDIR)\cvtdate.obj" \
	"$(INTDIR)\date2bin.obj" \
	"$(INTDIR)\dosdate.obj" \
	"$(INTDIR)\fexist.obj" \
	"$(INTDIR)\ffind.obj" \
	"$(INTDIR)\flush.obj" \
	"$(INTDIR)\genmsgid.obj" \
	"$(INTDIR)\gnmsgid.obj" \
	"$(INTDIR)\locking.obj" \
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
	"$(INTDIR)\strextra.obj" \
	"$(INTDIR)\strftim.obj" \
	"$(INTDIR)\strocpy.obj" \
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
	-@erase "$(INTDIR)\1stchar.obj"
	-@erase "$(INTDIR)\1stchar.sbr"
	-@erase "$(INTDIR)\api_jam.obj"
	-@erase "$(INTDIR)\api_jam.sbr"
	-@erase "$(INTDIR)\api_sdm.obj"
	-@erase "$(INTDIR)\api_sdm.sbr"
	-@erase "$(INTDIR)\cvtdate.obj"
	-@erase "$(INTDIR)\cvtdate.sbr"
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
	-@erase "$(INTDIR)\genmsgid.obj"
	-@erase "$(INTDIR)\genmsgid.sbr"
	-@erase "$(INTDIR)\gnmsgid.obj"
	-@erase "$(INTDIR)\gnmsgid.sbr"
	-@erase "$(INTDIR)\locking.obj"
	-@erase "$(INTDIR)\locking.sbr"
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
	-@erase "$(INTDIR)\strextra.obj"
	-@erase "$(INTDIR)\strextra.sbr"
	-@erase "$(INTDIR)\strftim.obj"
	-@erase "$(INTDIR)\strftim.sbr"
	-@erase "$(INTDIR)\strocpy.obj"
	-@erase "$(INTDIR)\strocpy.sbr"
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

CPP_PROJ=/nologo /MLd /W3 /Gm /ZI /Od /D "_DEBUG" /D "_LIB" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\smapi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\1stchar.sbr" \
	"$(INTDIR)\api_jam.sbr" \
	"$(INTDIR)\api_sdm.sbr" \
	"$(INTDIR)\cvtdate.sbr" \
	"$(INTDIR)\date2bin.sbr" \
	"$(INTDIR)\dosdate.sbr" \
	"$(INTDIR)\fexist.sbr" \
	"$(INTDIR)\ffind.sbr" \
	"$(INTDIR)\flush.sbr" \
	"$(INTDIR)\genmsgid.sbr" \
	"$(INTDIR)\gnmsgid.sbr" \
	"$(INTDIR)\locking.sbr" \
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
	"$(INTDIR)\strextra.sbr" \
	"$(INTDIR)\strftim.sbr" \
	"$(INTDIR)\strocpy.sbr" \
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
	"$(INTDIR)\1stchar.obj" \
	"$(INTDIR)\api_jam.obj" \
	"$(INTDIR)\api_sdm.obj" \
	"$(INTDIR)\cvtdate.obj" \
	"$(INTDIR)\date2bin.obj" \
	"$(INTDIR)\dosdate.obj" \
	"$(INTDIR)\fexist.obj" \
	"$(INTDIR)\ffind.obj" \
	"$(INTDIR)\flush.obj" \
	"$(INTDIR)\genmsgid.obj" \
	"$(INTDIR)\gnmsgid.obj" \
	"$(INTDIR)\locking.obj" \
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
	"$(INTDIR)\strextra.obj" \
	"$(INTDIR)\strftim.obj" \
	"$(INTDIR)\strocpy.obj" \
	"$(INTDIR)\structrw.obj" \
	"$(INTDIR)\tdelay.obj" \
	"$(INTDIR)\trail.obj" \
	"$(INTDIR)\weekday.obj"

"$(OUTDIR)\smapi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("smapi.dep")
!INCLUDE "smapi.dep"
!ELSE 
!MESSAGE Warning: cannot find "smapi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "smapi - Win32 Release" || "$(CFG)" == "smapi - Win32 Debug"
SOURCE=..\..\..\..\src\smapi\1stchar.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\1stchar.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\1stchar.obj"	"$(INTDIR)\1stchar.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\api_jam.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\api_jam.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\api_jam.obj"	"$(INTDIR)\api_jam.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\api_sdm.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\api_sdm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\api_sdm.obj"	"$(INTDIR)\api_sdm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\cvtdate.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\cvtdate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\cvtdate.obj"	"$(INTDIR)\cvtdate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\date2bin.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\date2bin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\date2bin.obj"	"$(INTDIR)\date2bin.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\dosdate.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\dosdate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\dosdate.obj"	"$(INTDIR)\dosdate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\fexist.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\fexist.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\fexist.obj"	"$(INTDIR)\fexist.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\ffind.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\ffind.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\ffind.obj"	"$(INTDIR)\ffind.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\flush.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\flush.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\flush.obj"	"$(INTDIR)\flush.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\genmsgid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\genmsgid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\genmsgid.obj"	"$(INTDIR)\genmsgid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\gnmsgid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\gnmsgid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\gnmsgid.obj"	"$(INTDIR)\gnmsgid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\locking.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\locking.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\locking.obj"	"$(INTDIR)\locking.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\months.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\months.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\months.obj"	"$(INTDIR)\months.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\msgapi.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\msgapi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\msgapi.obj"	"$(INTDIR)\msgapi.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\parsenn.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\parsenn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\parsenn.obj"	"$(INTDIR)\parsenn.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\patmat.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\patmat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\patmat.obj"	"$(INTDIR)\patmat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\qksort.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\qksort.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\qksort.obj"	"$(INTDIR)\qksort.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\setfsize.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\setfsize.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\setfsize.obj"	"$(INTDIR)\setfsize.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_area.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_area.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_area.obj"	"$(INTDIR)\sq_area.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_hash.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_hash.obj"	"$(INTDIR)\sq_hash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_help.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_help.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_help.obj"	"$(INTDIR)\sq_help.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_idx.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_idx.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_idx.obj"	"$(INTDIR)\sq_idx.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_kill.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_kill.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_kill.obj"	"$(INTDIR)\sq_kill.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_lock.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_lock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_lock.obj"	"$(INTDIR)\sq_lock.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_misc.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_misc.obj"	"$(INTDIR)\sq_misc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_msg.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_msg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_msg.obj"	"$(INTDIR)\sq_msg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_read.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_read.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_read.obj"	"$(INTDIR)\sq_read.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_uid.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_uid.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_uid.obj"	"$(INTDIR)\sq_uid.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\sq_write.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\sq_write.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\sq_write.obj"	"$(INTDIR)\sq_write.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\strextra.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\strextra.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\strextra.obj"	"$(INTDIR)\strextra.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\strftim.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\strftim.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\strftim.obj"	"$(INTDIR)\strftim.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\strocpy.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\strocpy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\strocpy.obj"	"$(INTDIR)\strocpy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\structrw.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\structrw.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\structrw.obj"	"$(INTDIR)\structrw.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\tdelay.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\tdelay.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\tdelay.obj"	"$(INTDIR)\tdelay.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\trail.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\trail.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\trail.obj"	"$(INTDIR)\trail.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\src\smapi\weekday.c

!IF  "$(CFG)" == "smapi - Win32 Release"


"$(INTDIR)\weekday.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "smapi - Win32 Debug"


"$(INTDIR)\weekday.obj"	"$(INTDIR)\weekday.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

