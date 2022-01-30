# $Id$
#
# Common makefiles part (include-file)

VERMAJOR= 2
VERMINOR= 5
VERH =  2.5
VER  =  2.5.2
SRCDIR = src/
HDIR   = h/

OBJS    = api_jam$(OBJ) \
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

HEADERS = $(HDIR)api_brow.h \
          $(HDIR)apidebug.h \
          $(HDIR)api_jam.h \
          $(HDIR)api_jamp.h \
          $(HDIR)api_sdm.h \
          $(HDIR)api_sdmp.h \
          $(HDIR)api_sq.h \
          $(HDIR)api_sqp.h \
          $(HDIR)BCD.h \
          $(HDIR)BCO.h \
          $(HDIR)BCW.h \
          $(HDIR)BEOS5.h \
          $(HDIR)BORLANDC.h \
          $(HDIR)compiler.h \
          $(HDIR)cvsdate.h \
          $(HDIR)DJGPP.h \
          $(HDIR)dr.h \
          $(HDIR)EMX.h \
          $(HDIR)ffind.h \
          $(HDIR)ftnaddr.h \
          $(HDIR)genmsgid.h \
          $(HDIR)HIGHC.h \
          $(HDIR)IBMC_OS2.h \
          $(HDIR)locking.h \
          $(HDIR)memory.h \
          $(HDIR)MINGW32.h \
          $(HDIR)MSC.h \
          $(HDIR)msgapi.h \
          $(HDIR)MSVC.h \
          $(HDIR)old_msg.h \
          $(HDIR)patmat.h \
          $(HDIR)prog.h \
          $(HDIR)progprot.h \
          $(HDIR)pstdint.h \
          $(HDIR)SASC.h \
          $(HDIR)stamp.h \
          $(HDIR)strext.h \
          $(HDIR)typedefs.h \
          $(HDIR)typesize.h \
          $(HDIR)UNIX.h \
          $(HDIR)unused.h \
          $(HDIR)WATCOMC.h \
          $(HDIR)WCD.h \
          $(HDIR)WCO.h \
          $(HDIR)WCW.h \
          $(HDIR)WCX.h
