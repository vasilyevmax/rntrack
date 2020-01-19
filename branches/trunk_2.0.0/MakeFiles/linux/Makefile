# $Id$
# Makefile for build RNTrack in linux
# Build options:
# ENABLE_SCRIPTS=1
#    Build with embedded Perl
# ENABLE_SYSLOG_LOG_FORMAT=1
#    Write log file lines like syslog(3)
# ENABLE_LOG_PID=1
#    Write the Process ID number into log file lines.
# CONFIG=/path/to/config.file
#    Alternate config file location

PREFIX=/usr
CC	= g++
SMAPIDIR= ../../smapi
CFLAGS	= -Wall -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src -O3
CDEFS	= -Dunix -D__linux__ -DHAVE_UNISTD_H -DHAVE_FCNTL_H -DHAVE_MALLOC_H \
          -DHAVE_STRING_H -DHAVE_TIME_H -DHAVE_SYS_TIME_H -DHAVE_UTIME_H \
          -DHAVE_LOCALE_H
LFLAGS	= -s -L$(SMAPIDIR) -lsmapilnx
SRCDIR	= ../../src/
DOCDIR	= ../../doc/
#CONFIG	= /etc/ftn/rntrack.cfg

# set to 1 for enable (in command line: make ENABLE_SCRIPTS=1 ENABLE_LOG_PID=1 ENABLE_SYSLOG_LOG_FORMAT=1)
ENABLE_SCRIPTS?=0
ENABLE_LOG_PID?=0
ENABLE_SYSLOG_LOG_FORMAT?=0

ifeq ($(ENABLE_SCRIPTS), 1)
#    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] $$Config{ccdlflags} ", join(" ",grep(!/(^$|-fstack-protector|-fno-strict-aliasing|-Wdeclaration-after-statement)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
#    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] ", join(" ",grep(!/(^$|-fno-strict-aliasing|-Wdeclaration-after-statement)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] ", join(" ",grep(!/(^$$|-Wdeclaration-after-statement)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
    LFLAGS += $(shell perl -e 'use ExtUtils::Embed; print join(" ",grep(!/DynaLoader/,split(" ",ldopts(0))));')
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
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

%.o: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

#$(SRCDIR)cfg.cpp: $(SRCDIR)cfg.y
#	bison -l -d $< -o $(SRCDIR)cfg.cpp

smapi:
	make -C $(SMAPIDIR) -f makefile.lnx

rntrack: smapi $(OBJS)
	$(CC) -o rntrack $(OBJS) $(LFLAGS)

rntrack.1.gz : $(DOCDIR)rntrack.1
	gzip -9c $(DOCDIR)rntrack.1 > $(DOCDIR)rntrack.1.gz

.PHONY: install
install: rntrack rntrack.1.gz
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	cp $(DOCDIR)rntrack.1.gz $(DESTDIR)$(PREFIX)/share/man/man1

.PHONY: uninstall
uninstall:
	-rm -f $(BINDIR)$(DIRSEP)rntrack
	-rm -f $(MAN1DIR)$(DIRSEP)rntrack.1.gz

.PHONY: clean
clean:
	-rm -f $(SMAPIDIR)/*.o
	-rm -f $(SMAPIDIR)/*.a
	-rm -f *.o
	-rm -f $(DOCDIR)rntrack.1.gz
	-rm -f *~
	-rm -f core
	-rm -f rntrack
