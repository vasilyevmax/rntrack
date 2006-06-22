# $Id: makefile.be,v 1.1.1.1 2005/01/14 19:22:14 ph0enix Exp $
#
# Legacy makefile for building on BeOS with gcc
# No support for the Husky build environment

CC=	gcc
CFLAGS=	-Wall
CDEFS=	-DUNIX
COPT=	-O3
OBJ=	.o

# on i386, you may add this
# -fomit-frame-pointer -fstrength-reduce -fPIC -m486

LIB=	ar

TARGET=	libsmapibe.a

all: $(TARGET)

include makefile.inc


# Thunderbirds are go!

.c.o:
	$(CC) $(CFLAGS) $(CDEFS) $(COPT) -c $<
	$(LIB) r $(TARGET) $@

$(TARGET): $(OBJS)

clean:
	-rm *.o

distclean: clean
	-rm $(TARGET)
