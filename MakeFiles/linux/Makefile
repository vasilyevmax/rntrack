#
# Makefile for building RNTrack in Linux
#
# Build options:
# PREFIX=/usr/local
#    Alternative prefix. On default it is /usr
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

PREFIX ?= /usr
ARCH ?= x86_64
# set to 1 to enable (in command line: make ENABLE_SCRIPTS=1 ENABLE_LOG_PID=1 ENABLE_SYSLOG_LOG_FORMAT=1)
STATIC ?= 0
USE_MUSL ?= 0
USE_CLANG ?= 0
DEBUG ?= 0
ENABLE_SCRIPTS ?= 0
ENABLE_LOG_PID ?= 0
ENABLE_SYSLOG_LOG_FORMAT ?= 0

ifeq ($(STATIC), 1)
    USE_MUSL = 1
endif

HPPDIR := ../../hpp
SRCDIR := ../../src
SMAPIDIR := ../../smapi
smapi_HDIR := $(SMAPIDIR)/h
smapi_SRCDIR :=$(SMAPIDIR)/src
DOCDIR = ../../doc

ifeq ($(DEBUG),0)
    ifeq ($(USE_MUSL), 1)
        CC := $(ARCH)-linux-musl-g++
        CFLAGS := -O3 -Wall -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
    else ifeq ($(USE_CLANG), 1)
        CC := clang++
        CFLAGS := -O3 -Wall -Wextra -ferror-limit=0 -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
    else
        CC := g++
        CFLAGS := -O3 -Wall -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
    endif
else
    ifeq ($(USE_MUSL), 1)
        CC := $(ARCH)-linux-musl-g++
        CFLAGS := -g -O2 -Wall -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
    else ifeq ($(USE_CLANG), 1)
        CC := clang++
        CFLAGS := -g -O2 -Wall -Wextra -ferror-limit=0 -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
    else
        CC := g++
        CFLAGS := -g -O2 -Wall -fPIC -fno-rtti -I$(HPPDIR) -I$(SRCDIR) -I$(smapi_HDIR) -I$(smapi_SRCDIR)
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
        LFLAGS := -s -static -pie -z text
    else
        LFLAGS := -s
    endif
else
    ifeq ($(STATIC), 1)
        LFLAGS := -static -pie -z text
    endif
endif



ifeq ($(ENABLE_SCRIPTS),1)
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

.PHONY: all
all: rntrack $(DOCDIR)/rntrack.1.gz ;

include $(SMAPIDIR)/makefile.lnx

rntrack: $(smapi_OBJS) $(OBJS)
	$(CC) -o rntrack $(smapi_OBJS) $(OBJS) $(LFLAGS)

$(OBJS): %.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(CDEFS) -c $(SRCDIR)/$*.cpp

#$(SRCDIR)/cfg.cpp: $(SRCDIR)/cfg.y
#	bison -l -d $< -o $@

$(DOCDIR)/rntrack.1.gz : $(DOCDIR)/rntrack.1
	gzip -9c $<   > $@

BINDIR := $(DESTDIR)$(PREFIX)/bin
MAN1DIR := $(DESTDIR)$(PREFIX)/share/man/man1

.PHONY: install
install: rntrack $(DOCDIR)/rntrack.1.gz | $(BINDIR) $(MAN1DIR)
	install $< $(BINDIR)
	install -m 0644 $(DOCDIR)/rntrack.1.gz $(MAN1DIR)

$(BINDIR):
	mkdir -p $@

$(MAN1DIR):
	mkdir -p $@


.PHONY: uninstall
uninstall:
	-rm -f $(BINDIR)/rntrack
	-rm -f $(MAN1DIR)/rntrack.1.gz

.PHONY: clean distclean
clean:
	-rm -f *.o
	-rm -f *~
	-rm -f core

distclean: clean
	-rm -f $(DOCDIR)/rntrack.1.gz
	-rm -f rntrack
