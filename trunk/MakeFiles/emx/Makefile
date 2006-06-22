# $Id: Makefile,v 1.4 2005/04/02 07:14:04 ph0enix Exp $
CC=	gcc

PERL=D:/PERLLIB/LIB/5.00553/os2

DEBUG=-s -g

CFLAGS=	-Wall -funsigned-char -Wno-char-subscripts -O3 $(DEBUG)
CDEFS=	-DOS2 -DDO_PERL -DDOSISH -DEMBED
# -D__NOSCRIPTS__
COPT=	-I../../hpp -I../../.. -I$(PERL)/CORE -O3 -Zomf
SRCDIR= ../../src/
LFLAGS=	-Zomf -Zcrtdll -Zlinker /PM:VIO $(DEBUG) -L../../../smapi
EXEEND= _os2.exe

ALL: rntrack$(EXEEND)

TARGET= f

OBJS=	fidoaddr.obj \
	log.obj \
	age.obj \
	aka.obj \
	attach.obj \
	badmsg.obj \
	cfg.obj \
	configure.obj \
	rntrack.obj \
	getopt.obj \
	help.obj \
	msg.obj \
	msgbase.obj \
	nodelist.obj \
	vars.obj \
	outbound.obj \
	parsetpl.obj \
	passwd.obj \
	pktbase.obj \
	scandir.obj \
	sqbase.obj \
	tmstamp.obj \
	utils.obj \
	mask.obj \
	wildmat.obj \
	badpkt.obj \
	script.obj \
	domain.obj \^M
	filebox.obj \^M
	string.o^M

PERLLIBS=\
        $(PERL)/auto/DB_File/DB_File.lib \
        $(PERL)/auto/SDBM_File/SDBM_File.lib \
        $(PERL)/auto/Fcntl/Fcntl.lib \
        $(PERL)/auto/IO/IO.lib \
        $(PERL)/auto/POSIX/POSIX.lib \
        $(PERL)/auto/OS2/Process/Process.lib \
        $(PERL)/auto/OS2/ExtAttr/ExtAttr.lib \
        $(PERL)/auto/OS2/REXX/REXX.lib \
        $(PERL)/auto/DynaLoader/DynaLoader.lib \
        -L$(PERL)/CORE -llibperl -lsocket -lm -lbsd -ldb

%.obj: %.c
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

%.obj: $(SRCDIR)%.cpp
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<

# Thunderbirds are go!


rntrack$(EXEEND): $(OBJS)
	$(CC) $(LFLAGS) -o rntrack$(EXEEND) $(OBJS) -lsmapiemo $(PERLLIBS)

clean:
	-del *.obj
	-del rntrack$(EXEEND)
