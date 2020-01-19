# $Id$
CC		= g++
CFLAGS	=  -mno-cygwin -Wall -W -fno-rtti -fno-strict-aliasing -I../../hpp -I../../src -I../../smapi/h -I../../smapi/src -O1
CDEFS	= -D__NT__ -DNDEBUG -DWIN32 -DWIN32IOP_H -DHAVE_IO_H \
		  -DHAVE_TIME_H -DHAVE_UTIME_H -DHAVE_LOCALE_H
SMAPIDIR= ../../smapi
LFLAGS	= -s -L$(SMAPIDIR)smapi -lsmapimgw
SRCDIR	= ../../src/
SRCDIR1 = ..\\..\\src\\
EXEEND	= _w32.exe
ifeq ($(TERM),msys)
RM	= rm
else
RM	= del /Q
endif
#CONFIG = c:\\\\ftn\\\\rntrack.cfg

# uncomment or use in comand line to enable features: 
# Embedded Perl
#ENABLE_SCRIPTS=1
# Write PID/TID in log lines
#ENABLE_LOG_PID=1
# Use log lines format like syslog format
#ENABLE_SYSLOG_LOG_FORMAT=1

ifeq ($(ENABLE_SCRIPTS), 1)
#	 CFLAGS += $(shell perl -e '@v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1]"; use ExtUtils::Embed; ccopts' | sed 's/-fstack-protector//' )
	CFLAGS += $(shell perl -MExtUtils::Embed -MConfig -e '@v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] $$Config{ccdlflags} ", join(" ",grep(!/-fstack-protector/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE";' )
	LFLAGS += $(shell perl -MExtUtils::Embed -e ldopts )
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
	$(CC) $(CFLAGS) $(CDEFS) -c $<

%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) -c $<

# Thunderbirds are go!

smapi:
	make -C $(SMAPIDIR) -f makefile.mgw

rntrack: rntrack$(EXEEND)

rntrack$(EXEEND): $(OBJS) smapi
	$(CC) -o rntrack$(EXEEND) $(OBJS) $(LFLAGS)

clean:
	-$(RM) $(SMAPIDIR)/*.o
	-$(RM) $(SMAPIDIR)/*.a
	-$(RM) *.o
	-$(RM) *~
	-$(RM) core

distclean: clean
	-$(RM) rntrack$(EXEEND)
