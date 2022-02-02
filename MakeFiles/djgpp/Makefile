# $Id$
CC	= gxx
SMAPIDIR= ../../smapi
CFLAGS	= -Wall -W -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src -O3
CDEFS	= -D__FLAT__ -DNOSEMAPHORES -DHAVE_DOS_H -DHAVE_UNISTD_H -DHAVE_IO_H -DHAS_strupr -DHAVE_LOCALE_H -DHAVE_TIME_H -DHAVE_UTIME_H
LFLAGS	= -s $(SMAPIDIR)/smapidjg.a
SRCDIR	= ../../src/
SRCDIR1 = ..\\..\\src\\
SMAPIDIR1 = ..\\..\\smapi
EXEEND	= _386.exe
#CONFIG = c:\\\\ftn\\\\rntrack.cfg

# uncomment to enable
#ENABLE_SCRIPTS=1
#ENABLE_LOG_PID=1
#ENABLE_SYSLOG_LOG_FORMAT=1

ifeq ($(ENABLE_SCRIPTS), 1)
    CFLAGS += `perl -e '@v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1]";'` `perl -MExtUtils::Embed -e ccopts`
    LFLAGS += `perl -MExtUtils::Embed -e ldopts`
endif

ifeq ($(ENABLE_SYSLOG_LOG_FORMAT), 1)
    CFLAGS += -DSYSLOG_LOG_FORMAT
endif

ifeq ($(ENABLE_LOG_PID), 1)
    CFLAGS += -DLOG_SHOW_PID
endif

ifdef CONFIG
    CDEFS += -DDefaultConfig=\"$(CONFIG)\"
endif

all: rntrack

OBJS= \
	age.o \
	aix_conv.o \
	aka.o \
	attach.o \
	badmsg.o \
	badpkt.o \
	cfg.o \
	configure.o \
	dirent.o \
	domain.o \
	fidoaddr.o \
	filebox.o \
	getopt.o \
	help.o \
	log.o \
	mask.o \
	msg.o \
	msgbase.o \
	nodelist.o \
	outbound.o \
	parsetpl.o \
	passwd.o \
	pktbase.o \
	rntrack.o \
	scandir.o \
	script.o \
	sqbase.o \
	string.o \
	tmstamp.o \
	utils.o \
	vars.o \
	wildmat.o

%.o: $(SRCDIR)%.c
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(CDEFS) -c $<

%.o: $(SRCDIR)%.cpp
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(CDEFS) -c $<

# Thunderbirds are go!

smapi:
	make -C $(SMAPIDIR) -f makefile.djg static

rntrack: smapi $(OBJS)
	@echo Compiling rntrack$(EXEEND)
	@$(CC) -o rntrack$(EXEEND) $(OBJS) $(LFLAGS)

clean:
	-del $(SMAPIDIR1)\\*.o
	-del $(SMAPIDIR1)\\*.a
	-del *.o
	-del  *~
	-del core
	-del rntrack$(EXEEND)
