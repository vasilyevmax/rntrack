/*
 *  RNtrack - FTN message tracker/router
 *
 *  widmat.hpp - Pattern matching
 *
 *  Copyright (c) 2003-2005 Alex Soukhotine, 2:5030/1157
 *	
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  $Id$
 */

/*
 *
 *  Do shell-style pattern matching for ?, \, [], and * characters.
 *  Might not be robust in face of malformed patterns; e.g., "foo[a-"
 *  could cause a segmentation violation.  It is 8bit clean.
 *
 *  Written by Rich $alz, mirror!rs, Wed Nov 26 19:03:17 EST 1986.
 *  Rich $alz is now <rsalz@osf.org>.
 *  April, 1991:  Replaced mutually-recursive calls with in-line code
 *  for the star character.
 *
 *  Special thanks to Lars Mathiesen <thorinn@diku.dk> for the ABORT code.
 *  This can greatly speed up failing wildcard patterns.  For example:
 *	pattern: -*-*-*-*-*-*-12-*-*-*-m-*-*-*
 *	text 1:	 -adobe-courier-bold-o-normal--12-120-75-75-m-70-iso8859-1
 *	text 2:	 -adobe-courier-bold-o-normal--12-120-75-75-X-70-iso8859-1
 *  Text 1 matches with 51 calls, while text 2 fails with 54 calls.  Without
 *  the ABORT code, it takes 22310 calls to fail.  Ugh.  The following
 *  explanation is from Lars:
 *  The precondition that must be fulfilled is that DoMatch will consume
 *  at least one character in text.  This is true if *p is neither '*' nor
 *  '\0'.)  The last return has ABORT instead of FALSE to avoid quadratic
 *  behaviour in cases like pattern "*a*b*c*d" with text "abcxxxxx".  With
 *  FALSE, each star-loop has to run to the end of the text; with ABORT
 *  only the last one does.
 *
 *  Once the control of one instance of DoMatch enters the star-loop, that
 *  instance will return either TRUE or ABORT, and any calling instance
 *  will therefore return immediately after (without calling recursively
 *  again).  In effect, only one star-loop is ever active.  It would be
 *  possible to modify the code to maintain this context explicitly,
 *  eliminating all recursive calls at the cost of some complication and
 *  loss of clarity (and the ABORT stuff seems to be unclear enough by
 *  itself).  I think it would be unwise to try to get this into a
 *  released version unless you have a good test data base to try it out
 *  on.
 */

#ifndef _WILDMAT_HPP_
#define _WILDMAT_HPP_

int wildmat(const char * text, const char * p);

#endif
