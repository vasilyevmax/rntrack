# RNTrack -*Automake*-
# $Id$

#AUTOMAKE_OPTIONS = foreign

SUBDIRS = smapi .

bin_PROGRAMS = rntrack
rntrack_SOURCES = age.cpp aka.cpp attach.cpp badmsg.cpp badpkt.cpp cfg.cpp configure.cpp domain.cpp fidoaddr.cpp \
		    filebox.cpp getopt.cpp help.cpp log.cpp mask.cpp msgbase.cpp msg.cpp nodelist.cpp outbound.cpp \
		    parsetpl.cpp passwd.cpp pktbase.cpp rntrack.cpp scandir.cpp script.cpp sqbase.cpp string.cpp \
		    tmstamp.cpp utils.cpp vars.cpp wildmat.cpp

rntrack_LDFLAGS = -L$(srcdir)/smapi

rntrack_LDADD = $(srcdir)/smapi/libsmapi.a

INCLUDES = -I$(top_srcdir)/hpp -I$(srcdir)
CFLAGS = $(CFLAGS) -pedantic -Wall -fno-rtti @PERL_CFLAGS@
#LFLAGS = $(LFLAGS) @PERL_LFLAGS@
