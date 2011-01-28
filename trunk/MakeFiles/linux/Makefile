# $Id$
CC	= g++
CFLAGS	= -Wall -fno-rtti -I../../hpp -I../../src -O3
CDEFS	= -Dunix -D__linux__ -DHAVE_UNISTD_H -DHAVE_FCNTL_H -DHAVE_MALLOC_H \
          -DHAVE_STRING_H -DHAVE_TIME_H -DHAVE_SYS_TIME_H -DHAVE_UTIME_H \
	  -DHAVE_LOCALE_H
LFLAGS	= -s -L$(SRCDIR)smapi -lsmapilnx
SRCDIR	= ../../src/
#CONFIG	= /etc/ftn/rntrack.cfg

# set to 1 for enable (in command line: make ENABLE_SCRIPTS=1 ENABLE_LOG_PID=1 ENABLE_SYSLOG_LOG_FORMAT=1)
ENABLE_SCRIPTS?=1
ENABLE_LOG_PID?=1
ENABLE_SYSLOG_LOG_FORMAT?=1

ifeq ($(ENABLE_SCRIPTS), 1)
    CFLAGS += `perl -e '@v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1]";'` `perl -MExtUtils::Embed -e ccopts`
    LFLAGS += `perl -MExtUtils::Embed -e ldopts`
else
    CDEFS  += -D__NOSCRIPTS__
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
	mask.o \
	script.o \
	wildmat.o \
	badpkt.o \
	domain.o \
	filebox.o \
	string.o

%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

$(SRCDIR)cfg.cpp: $(SRCDIR)cfg.y
	bison -l -d $< -o $(SRCDIR)cfg.cpp

# Thunderbirds are go!
smapi:
	make -C $(SRCDIR)smapi -f makefile.lnx

rntrack: smapi $(OBJS)
	$(CC) -o rntrack $(OBJS) $(LFLAGS)

clean:
	-rm -f $(SRCDIR)smapi/*.o
	-rm -f $(SRCDIR)smapi/*.a
	-rm -f *.o
	-rm -f *~
	-rm -f core
	-rm -f rntrack
