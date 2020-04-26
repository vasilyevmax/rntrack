/* $Id$
 *  Provides function to dynamically change the size of a file

 *  Written by Scott Dudley
 *  777 Downing St.    FidoNet     1:249/106
 *  Kingston, Ont.     Internet    sjd@f106.n249.z1.fidonet.org
 *  Canada  K7M 5N3    BBS         1-613-634-3058, V.32bis
 *
 *  Copyright 1989-1994 by SCI Communications.
 *  Copyright 1997-2003 Husky Developers Team.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see file COPYING. If not, write to the
 * Free Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * See also https://www.gnu.org, license may be found here.
 */
/* standard headers */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#include "compiler.h"
/* compiler-dependent headers */
#ifdef HAS_DOS_H
    #include <dos.h>
#endif

#ifdef HAS_IO_H
    #include <io.h>
#endif

#ifdef HAS_UNISTD_H
    #include <unistd.h>
#endif
/***  Declarations & defines  ***********************************************/
int _fast setfsize(int fd, long size);

/***  Implementation  *******************************************************/

#ifdef __DOS__
/* Call DOS Fn 40H: Write to File via Handle
 * AH    0x40
 * BX    file handle
 * CX    number of bytes to write (Note: 0 means truncate the file)
 * DS:DX address of a buffer containing the data to write
 * Returns: AX    error code if CF is set to CY
 *                number of bytes actually written  use for error test
 *
 * DOS 3.0+ If CX is 0000H on entry, the file is truncated at the
 * current file position -- or the file is padded to that position.
 */
int _fast setfsize(int fd, long size)
{
    union REGS r;
    long pos = tell(fd);

    lseek(fd, size, SEEK_SET);
    memset(&r, 0, sizeof(r));
    r.h.ah = 0x40;

#if defined (__DOS16__) || defined (__DJGPP__)
    r.x.bx = fd;
    int86(0x21, &r, &r);

#elif defined (__DPMI__)
    r.x.ebx = fd;
    int386(0x21, &r, &r);
#endif

    lseek(fd, pos, SEEK_SET);
    return 0;
}

#elif defined (__OS2__)

#define INCL_DOSFILEMGR
#include <os2.h>

int _fast setfsize(int fd, long size)
{
    return (int)DosSetFileSize((HFILE)fd, (ULONG)size); /*ULONG & HFILE defined in os2.h*/
}

#elif defined (__UNIX__)

int _fast setfsize(int fd, long size)
{
    return ftruncate(fd, size);
}

#elif defined (__WIN32__)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winbase.h>

int _fast setfsize(int fd, long size)
{
#if defined (__MSVC__) || defined (__MINGW32__)
    return chsize(fd, size);

#else
    SetFilePointer((HANDLE)fd, size, NULL, FILE_BEGIN);
    return !SetEndOfFile((HANDLE)fd);

#endif
}

#else  /* ifdef __DOS__ */
#error Unknown OS
#endif /* ifdef __DOS__ */
