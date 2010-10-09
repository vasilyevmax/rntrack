# $Id$
CC	= g++
CFLAGS	= -Wall -W -fno-rtti -I../../hpp -I../../src -O3
CDEFS	= -DUNIX
LFLAGS	= -s -L${SRCDIR}smapi -lsmapibsd
SRCDIR	= ../../src/
#CONFIG	= /etc/ftn/rntrack.cfg

# uncomment to enable
#ENABLE_SCRIPTS=1
#ENABLE_LOG_PID=1
#ENABLE_SYSLOG_LOG_FORMAT=1

.ifdef ENABLE_SCRIPTS
    CFLAGS += `perl -e 'print "-D__PERL_NEW__" if ($$\>=5.008);'` `perl -MExtUtils::Embed -e ccopts`
    LFLAGS += `perl -MExtUtils::Embed -e ldopts`    
.else
    CDEFS  += -D__NOSCRIPTS__
.endif

.ifdef ENABLE_SYSLOG_LOG_FORMAT
    CFLAGS += -DSYSLOG_LOG_FORMAT
.endif

.ifdef ENABLE_LOG_PID
    CFLAGS += -DLOG_SHOW_PID
.endif

.ifdef CONFIG
    CDEFS += -DDefaultConfig=\"${CONFIG}\"
.endif

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

.PATH.cpp: $(SRCDIR)

.cpp.o:
	${CC} ${CFLAGS} ${CDEFS} -c $<

%.o: $(SRCDIR)%.cpp
	${CC} ${CFLAGS} ${CDEFS} -c $<

${SRCDIR}cfg.cpp: ${SRCDIR}cfg.y
	bison -l -d $< -o ${SRCDIR}cfg.cpp

# Thunderbirds are go!
smapi:
	cd  ${SRCDIR}smapi && make -f makefile.bsd

rntrack: smapi ${OBJS}
	${CC} -o rntrack ${OBJS} ${LFLAGS}

clean:
	-rm -f ${SRCDIR}smapi/*.o 
	-rm -f ${SRCDIR}smapi/*.a
	-rm -f *.o
	-rm -f *~
	-rm -f core
	-rm -f rntrack
