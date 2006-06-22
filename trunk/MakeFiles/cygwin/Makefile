# $Id: Makefile,v 1.4 2005/04/02 07:14:04 ph0enix Exp $
CC	= g++
CFLAGS	=  -mno-cygwin -Wall -W -fno-rtti -fno-strict-aliasing -I../../hpp -I../../src -O1
CDEFS	= -D__NT__ -DNDEBUG -DWIN32 -DWIN32IOP_H
LFLAGS	= -s -mno-cygwin -L$(SRCDIR)smapi -lsmapicyg -lmingwex
SRCDIR	= ../../src/
EXEEND= _w32.exe
#CONFIG	= c:\\ftn\\rntrack.cfg

# uncomment to enable
#ENABLE_SCRIPTS=1
#ENABLE_LOG_PID=1
#ENABLE_SYSLOG_LOG_FORMAT=1

ifeq ($(ENABLE_SCRIPTS), 1)
    CFLAGS += `perl -MExtUtils::Embed -e ccopts`
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
	cd $(SRCDIR)smapi && make -f makefile.cyg

rntrack: smapi $(OBJS)
	$(CC) -o rntrack$(EXEEND) $(OBJS) $(LFLAGS) 

clean:
	-rm -f $(SRCDIR)smapi/*.o
	-rm -f $(SRCDIR)smapi/*.a
	-rm -f *.o
	-rm -f *~
	-rm -f core                                                                                                
	-rm -f rntrack$(EXEEND)
