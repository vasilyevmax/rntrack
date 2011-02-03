# $Id$
# Makefile for build RNTrack in cygwin enviroment
# Build options:
# ENABLE_SCRIPTS=1
#    Build with embedded Perl
# ENABLE_SYSLOG_LOG_FORMAT=1
#    Write log file lines like syslog(3)
# ENABLE_LOG_PID=1
#    Write the Process ID number into log file lines.
# CONFIG=/path/to/config.file
#    Alternate config file location

CC	= g++
CFLAGS	=  -mno-cygwin -Wall -W -fno-rtti -fno-strict-aliasing -I../../hpp -I../../src -O1
CDEFS	= -D__NT__ -DNDEBUG -DWIN32 -DWIN32IOP_H \
	 -DHAVE_STDIO_H -DHAVE_STDLIB_H -DHAVE_STRING_H  -DHAVE_STRINGS_H \
	 -DHAVE_CTYPE_H -DHAVE_SYS_TYPES_H -DHAVE_SYS_STAT_H -DHAVE_UNISTD_H \
	 -DHAVE_FCNTL_H -DHAVE_ERRNO_H -DHAVE_IOSTREAM_H \
          -DHAVE_TIME_H -DHAVE_STDARG_H -DHAVE_ASSERT_H -DHAVE_DIRECT_H -DHAVE_DIRENT_H \
          -DHAVE_SYS_TIME_H -DHAVE_LOCALE_H -DHAVE_UTIME_H -DHAVE_LIMITS_H

LFLAGS	= -s -mno-cygwin -L$(SRCDIR)smapi -lsmapicyg -lmingwex
SRCDIR	= ../../src/
EXEEND= _w32.exe
#CONFIG	= c:\\ftn\\rntrack.cfg

ENABLE_SCRIPTS?=0
ENABLE_LOG_PID?=0
ENABLE_SYSLOG_LOG_FORMAT?=0

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

OBJS=	fidoaddr.o \
	log.o \
	age.o \
	aka.o \
	attach.o \
	badmsg.o \
	cfg.o \
	configure.o \
	rntrack.o \
	getopt.o \
	help.o \
	msg.o \
	msgbase.o \
	nodelist.o \
	vars.o \
	outbound.o \
	parsetpl.o \
	passwd.o \
	pktbase.o \
	scandir.o \
	sqbase.o \
	tmstamp.o \
	utils.o \
	mask.o  \
	wildmat.o \
	badpkt.o \
	script.o \
	domain.o \
	filebox.o \
	string.o

%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(CDEFS) -c $<

%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) -c $<

# Thunderbirds are go!

smapi:
	cd $(SRCDIR)smapi && make -f makefile.cyg static

rntrack: smapi $(OBJS)
	$(CC) -o rntrack$(EXEEND) $(OBJS) $(LFLAGS) 

clean:
	-rm -f $(SRCDIR)smapi/*.o
	-rm -f $(SRCDIR)smapi/*.a
	-rm -f *.o
	-rm -f *~
	-rm -f core                                                                                                
	-rm -f rntrack$(EXEEND)
