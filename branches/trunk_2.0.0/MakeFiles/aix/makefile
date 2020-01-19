# $Id$
# this file not tested
CC	= g++
SMAPIDIR= ../../smapi
CFLAGS	= -Wall -W -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src -O3
CDEFS	= -DUNIX -D_AIX -D_AIX_CONV
LFLAGS	= -s -L$(SMAPIDIR) -lsmapiaix
SRCDIR	= ../../src/
#CONFIG	= /etc/ftn/rntrack.cfg

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

%.o: %.c
	$(CC) $(CFLAGS) $(CDEFS) -c $<

%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) -c $<

# Thunderbirds are go!

smapi:
	make -C $(SMAPIDIR) -f makefile.aix


rntrack: smapi $(OBJS)
	$(CC) -o rntrack $(OBJS) $(LFLAGS)

clean:
	-rm -f $(SMAPIDIR)/*.o
	-rm -f $(SMAPIDIR)/*.a
	-rm -f *.o
	-rm -f *~
	-rm -f core
	-rm -f rntrack
