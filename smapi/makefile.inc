# $Id$
#
# Common makefiles part (include-file)

VERMAJOR= 2
VERMINOR= 5
VERH =  2.5
VER  =  2.5.2
SRCDIR = src
HDIR   = h

OBJS	= api_jam$(OBJ) \
          api_sdm$(OBJ) \
          date2bin$(OBJ) \
          dosdate$(OBJ) \
          fexist$(OBJ) \
          ffind$(OBJ) \
          flush$(OBJ) \
          ftnaddr$(OBJ) \
          genmsgid$(OBJ) \
          gnmsgid$(OBJ) \
          locking$(OBJ) \
          memory$(OBJ) \
          months$(OBJ) \
          msgapi$(OBJ) \
          parsenn$(OBJ) \
          patmat$(OBJ) \
          qksort$(OBJ) \
          setfsize$(OBJ) \
          sq_area$(OBJ) \
          sq_hash$(OBJ) \
          sq_help$(OBJ) \
          sq_idx$(OBJ) \
          sq_kill$(OBJ) \
          sq_lock$(OBJ) \
          sq_misc$(OBJ) \
          sq_msg$(OBJ) \
          sq_read$(OBJ) \
          sq_uid$(OBJ) \
          sq_write$(OBJ) \
          strext$(OBJ) \
          strftim$(OBJ) \
          structrw$(OBJ) \
          tdelay$(OBJ) \
          trail$(OBJ) \
          weekday$(OBJ)

HEADERS	= $(addprefix $(HDIR)/,api_brow.h \
                               apidebug.h \
                               api_jam.h \
                               api_jamp.h \
                               api_sdm.h \
                               api_sdmp.h \
                               api_sq.h \
                               api_sqp.h \
                               BCD.h \
                               BCO.h \
                               BCW.h \
                               BEOS5.h \
                               BORLANDC.h \
                               compiler.h \
                               cvsdate.h \
                               DJGPP.h \
                               dr.h \
                               EMX.h \
                               ffind.h \
                               ftnaddr.h \
                               genmsgid.h \
                               HIGHC.h \
                               IBMC_OS2.h \
                               locking.h \
                               memory.h \
                               MINGW32.h \
                               months.h \
                               MSC.h \
                               msgapi.h \
                               MSVC.h \
                               old_msg.h \
                               patmat.h \
                               prog.h \
                               progprot.h \
                               pstdint.h \
                               SASC.h \
                               stamp.h \
                               strext.h \
                               typedefs.h \
                               typesize.h \
                               UNIX.h \
                               unused.h \
                               WATCOMC.h \
                               WCD.h \
                               WCO.h \
                               WCW.h \
                               WCX.h)
