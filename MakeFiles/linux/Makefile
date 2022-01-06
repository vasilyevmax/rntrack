#
# Makefile for building RNTrack in Linux
#
# Build options:
# ENABLE_SCRIPTS=1
#    Build with embedded Perl
# ENABLE_SYSLOG_LOG_FORMAT=1
#    Write log file lines like syslog(3)
# ENABLE_LOG_PID=1
#    Write the Process ID number into log file lines.
# CONFIG=/path/to/config.file
#    Alternate config file location
# USE_CLANG=1
#    Use Clang compiler instead of gcc
# USE_MUSL=1
#    Use musl libc instead of glibc. Implies USE_CLANG=0
# ARCH=i486
# ARCH=i686
# ARCH=x86_64
#    Target platform architecture. On default x86_64 is used
# STATIC=1
#    Link RNtrack staticly. Implies USE_MUSL=1
# DEBUG=1
#    Build a debug version of the executable

PREFIX = /usr
STATIC ?= 0
USE_MUSL ?= 0
USE_CLANG ?= 0
ARCH ?= x86_64
DEBUG ?= 0

ifeq ($(STATIC), 1)
    USE_MUSL = 1
endif

SMAPIDIR := ../../smapi
ifeq ($(DEBUG),0)
    ifeq ($(USE_MUSL), 1)
        CC := $(ARCH)-linux-musl-g++
        CFLAGS := -O3 -Wall -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    else ifeq ($(USE_CLANG), 1)
        CC := clang++
        CFLAGS := -O3 -Wall -Wextra -ferror-limit=0 -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    else
        CC := g++
        CFLAGS := -O3 -Wall -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    endif
else
    ifeq ($(USE_MUSL), 1)
        CC := $(ARCH)-linux-musl-g++
        CFLAGS := -g -O2 -Wall -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    else ifeq ($(USE_CLANG), 1)
        CC := clang++
        CFLAGS := -g -O2 -Wall -Wextra -ferror-limit=0 -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    else
        CC := g++
        CFLAGS := -g -O2 -Wall -fPIC -fno-rtti -I../../hpp -I../../src -I$(SMAPIDIR)/h -I$(SMAPIDIR)/src
    endif
endif

ifeq ($(ARCH), i486)
    CFLAGS += -march=i486
else ifeq ($(ARCH), i686)
    CFLAGS += -march=i686
endif

CDEFS = -Dunix -D__linux__ -DHAVE_UNISTD_H -DHAVE_FCNTL_H -DHAVE_MALLOC_H \
        -DHAVE_STRING_H -DHAVE_TIME_H -DHAVE_SYS_TIME_H -DHAVE_UTIME_H \
        -DHAVE_LOCALE_H

ifeq ($(DEBUG), 0)
    ifeq ($(STATIC), 1)
        LFLAGS := -s -static -pie -z text -L$(SMAPIDIR) -lsmapilnx
    else
        LFLAGS := -s -L$(SMAPIDIR) -lsmapilnx
    endif
else
    ifeq ($(STATIC), 1)
        LFLAGS := -static -pie -z text -L$(SMAPIDIR) -lsmapilnx
    else
        LFLAGS := -L$(SMAPIDIR) -lsmapilnx
    endif
endif

SRCDIR = ../../src/
DOCDIR = ../../doc/
#CONFIG = /etc/ftn/rntrack.cfg

# set to 1 to enable (in command line: make ENABLE_SCRIPTS=1 ENABLE_LOG_PID=1 ENABLE_SYSLOG_LOG_FORMAT=1)
ENABLE_SCRIPTS ?= 0
ENABLE_LOG_PID ?= 0
ENABLE_SYSLOG_LOG_FORMAT ?= 0

ifeq ($(ENABLE_SCRIPTS),1)
#    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] $$Config{ccdlflags} ", join(" ",grep(!/(^$|-fstack-protector|-fno-strict-aliasing|-Wdeclaration-after-statement)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
#    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] ", join(" ",grep(!/(^$|-fno-strict-aliasing|-Wdeclaration-after-statement)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
    CFLAGS += $(shell perl -MConfig -e 'my @v=split(/\./,"$$]"); print "-D__PERL_VERSION__=".join("",@v)." -D__PERL_MAJOR__=$$v[0] -D__PERL_MINOR__=$$v[1] ", join(" ",grep(!/(^$$|-Wdeclaration-after-statement|-fstack-clash-protection|redhat-hardened-cc1|redhat-annobin-cc1)/,split(" ",$$Config{ccflags}))), " -I$$Config{archlibexp}/CORE"')
    LFLAGS += $(shell perl -e 'use ExtUtils::Embed; print join(" ",grep(!/DynaLoader|redhat-hardened-ld/,split(" ",ldopts(0))));')
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

#$(SRCDIR)cfg.cpp: $(SRCDIR)cfg.y
#	bison -l -d $< -o $(SRCDIR)cfg.cpp

smapi:
	make -C $(SMAPIDIR) -f makefile.lnx USE_MUSL=$(USE_MUSL) ARCH=$(ARCH) \
		USE_CLANG=$(USE_CLANG) DEBUG=$(DEBUG)

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
