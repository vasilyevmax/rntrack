# Make rntrack/386 (DPMI) using Watcom C
#
# $Id$

CC 	= wcc386.exe
CCP 	= wpp386.exe
CDEFS	= /DHAVE_IO_H /DHAVE_MALLOC_H
CFLAGS	= -I$(INCLUDE) -bt=DOS4G /oilmrt /s $(CDEFS)
TOS	= DOS4G
TNAME	= rntrack_386
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
LIB=$(SRCDIR)\smapi\smapiwcx.lib


!ifdef ENABLE_SCRIPTS
CFLAGS+= -d__PERL_VERSION__
# please write here path to perl library - part of output of 'perl -MExtUtils::Embed -e ccopts'
INCLUDE+=
# please write here pathname of perl dinaloader library and path to other perl libraries - parts of output of 'perl -MExtUtils::Embed -e ldopts', directories in of libpath divided by semicolon
LIB+=
libpath=
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
TOS=NT
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

libpath +=$(%watcom)\lib386;$(%watcom)\lib386\dos;
.before
    set include=$(%watcom)\h;


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
    wmake -f makefile.wcx
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

