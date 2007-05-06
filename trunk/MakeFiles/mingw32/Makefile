# $Id$
CC	= g++
CFLAGS	=  -mno-cygwin -Wall -W -fno-rtti -fno-strict-aliasing -I../../hpp -I../../src -O1
CDEFS	= -D__NT__ -DNDEBUG -DWIN32 -DWIN32IOP_H -DHAVE_IO_H
LFLAGS	= -s -L$(SRCDIR)smapi -lsmapimgw
SRCDIR	= ../../src/
SRCDIR1 = ..\\..\\src\\
EXEEND= _w32.exe
#CONFIG	= c:\\\\ftn\\\\rntrack.cfg

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
	make -C $(SRCDIR)smapi -f makefile.mgw

rntrack: smapi $(OBJS)
	$(CC) -o rntrack$(EXEEND) $(OBJS) $(LFLAGS) 

clean:
	-del $(SRCDIR1)smapi\\*.o
	-del $(SRCDIR1)smapi\\*.a
	-del *.o
	-del *~
	-del core                                                                                                
	-del rntrack$(EXEEND)
