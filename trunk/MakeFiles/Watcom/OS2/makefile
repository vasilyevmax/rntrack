# Make rntrack/OS2 using Watcom C
#
# $Id$

CC 	= wcc386.exe
CCP 	= wpp386.exe
CDEFS	= /oilmrt /s /DOS2 /DHAVE_IO_H /DHAVE_MALLOC_H
CFLAGS	= -I$(INCLUDE) -bt=os2 $(CDEFS)
TOS	= OS2V2
TNAME	= rntrack_os2
SRCDIR	= ..\..\..\src
WORKDIR	= $+ $(%cdrive):$(%cwd) $-
DEBUG	= 0
#CONFIG	= C:\\ftn\\rntrack.cfg

# uncomment to enable
#ENABLE_SCRIPTS=1 #not implemented yet
#ENABLE_LOG_PID=1
#ENABLE_SYSLOG_LOG_FORMAT=1


OBJS= cfg.obj configure.obj rntrack.obj log.obj help.obj
OBJS+= fidoaddr.obj msg.obj msgbase.obj scandir.obj vars.obj age.obj
OBJS+= badmsg.obj aka.obj parsetpl.obj attach.obj outbound.obj
OBJS+= passwd.obj wildmat.obj tmstamp.obj badpkt.obj
OBJS+= sqbase.obj mask.obj getopt.obj cfg.obj utils.obj nodelist.obj
OBJS+= pktbase.obj script.obj domain.obj filebox.obj string.obj

INCLUDE=..\..\..\hpp;$(SRCDIR)
LIB=$(SRCDIR)\smapi\smapiwco.lib


!ifndef ENABLE_SCRIPTS
CFLAGS+= -d__NOSCRIPTS__
!endif

!ifdef ENABLE_SYSLOG_LOG_FORMAT
CFLAGS+= -dSYSLOG_LOG_FORMAT
!endif

!ifdef ENABLE_LOG_PID
CFLAGS+= -dLOG_SHOW_PID
!endif

!ifdef CONFIG
CFLAGS+= -dDefaultConfig="$(CONFIG)"
!endif


!ifndef TNAME
!   error TNAME not defined
!endif

!ifndef TOS
TOS=OS2V2
!endif

!ifndef OBJDIR
OBJDIR=.
!endif

!ifndef SRCDIR
SRCDIR=.
!endif

!ifeq DEBUG 1
CFLAGS += -d_DEBUG
CFLAGS += -d2
CFLAGS += -hw
!endif

libpath = $(%watcom)\lib386;$(%watcom)\lib386\os2;
.before
    set include=$(%watcom)\h;$(%watcom)\h\os2;

# ------------------------- common rules ---------------------------
.extensions:
.extensions: .exe .obj .res .rc .cpp .c .lib .y


.obj: $(OBJDIR)

.cpp: $(SRCDIR)

.c: $(SRCDIR)

#.y: $(SRCDIR)

#.y.cpp: .AUTODEPEND
#    bison -l -v -d $[@
#    if exist $@ del $@
#    move $(SRCDIR)\cfg_tab.c $@
#    move $(SRCDIR)\cfg.out cfg.output

.cpp.obj: .AUTODEPEND
    $(CCP) $[@ $(CFLAGS) /xs $(dbgflags)

.c.obj: .AUTODEPEND
    $(CC) $[@ $(CFLAGS) $(dbgflags)

# ------------------------ make EXE file ---------------------------

$(TNAME).exe : smapi $(OBJS) tmp.lnk
    wlink.exe @tmp.lnk

smapi: .symbolic
    cd  $(SRCDIR)\smapi
    wmake -f makefile.wco
    cd $(WORKDIR)

tmp.lnk : $(__MAKEFILES__)
    %create $^@
    @%append $^@ system $(TOS)
    @%append $^@ name $(TNAME)
    @%append $^@ option Stack=655340
!ifeq debug 1
    @%append $^@ debug watcom all
    @%append $^@ option map
!endif
    @for %i in ( $(OBJS) ) do @%append $^@ file $(OBJDIR)\%i
    @%append $^@ library $(LIB)
clean: .symbolic
	del *.obj
	del $(SRCDIR)\smapi\*.obj
	del $(SRCDIR)\smapi\*.lib
	del tmp.lnk
	del $(TNAME).exe

