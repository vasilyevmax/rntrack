/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_CFG_HPP_INCLUDED
# define YY_YY_SRC_CFG_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
    #define YYDEBUG 0
#endif
#if YYDEBUG
    extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype
{
    _LOGFILE = 258,
    _LOGLEVEL = 259,
    _NODELIST = 260,
    _INDEXFILE = 261,
    _NODELISTPATH = 262,
    _ADDRESS = 263,
    _SYSOPNAME = 264,
    _USEOWNZONE = 265,
    _FORCEINTL = 266,
    _LOOPSTR = 267,
    _SCANDIR = 268,
    _MASK = 269,
    _SMASK = 270,
    _PMASK = 271,
    _BODYMASK = 272,
    _SBODYMASK = 273,
    _PBODYMASK = 274,
    _KLUDGEMASK = 275,
    _SKLUDGEMASK = 276,
    _PKLUDGEMASK = 277,
    _ACTION = 278,
    _MAXAGE = 279,
    _BADMESSAGES = 280,
    _NOLOGIGNORE = 281,
    _AKA = 282,
    _SKIPHIDDENFILES = 283,
    _FILEINBOUND = 284,
    _OUTBOUND = 285,
    _ADDTONULLPKT = 286,
    _TEMPMAIL = 287,
    _TRAFFICLOG = 288,
    _PASSWORD = 289,
    _UTC = 290,
    _ORIGIN = 291,
    _TEARLINE = 292,
    _INCLUDE = 293,
    _APKTDIR = 294,
    _CHECKPOINTS = 295,
    _SETVIAALWAYS = 296,
    _FRESH = 297,
    _CREATEMISSINGBASE = 298,
    _USENEWVIA = 299,
    _SCRIPTMASK = 300,
    _SSCRIPTMASK = 301,
    _PSCRIPTMASK = 302,
    _MAXATTACHSIZE = 303,
    _SEMAPHORE = 304,
    _SCRIPTFILE = 305,
    _USEASO = 306,
    _USEBRAKE = 307,
    _FILEBOXDIR = 308,
    _KILLROUTEDMESSAGE = 309,
    _IGNOREBSY = 310,
    _AFTERSCRIPT = 311,
    _BEFORESCRIPT = 312,
    _AGEFROMVIA = 313,
    _MAXNODELISTAGE = 314,
    _USEFILEBOXES = 315,
    _FILEBOXTYPE = 316,
    _LONG = 317,
    _TMLONG = 318,
    _TMSHORT = 319,
    _BRAKE = 320,
    _SOFTCHECKINNODELIST = 321,
    _BADPACKETS = 322,
    _IGNOREATTACHPATH = 323,
    _MAXPKTSIZE = 324,
    _MAXMSGSIZE = 325,
    _TIMESTAMPFILE = 326,
    _DOMAINP = 327,
    _FILEBOX = 328,
    _TRAFFICLOGTEMPLATE = 329,
    _STRIPPATHINPKT = 330,
    _CRLF = 331,
    _SKIP = 332,
    _DELETE = 333,
    _EXIT = 334,
    _MOVE = 335,
    __EOF = 336,
    _STRING = 337,
    _BEFOREROUTE = 338,
    _AFTERROUTE = 339,
    _DIGIT_ = 340,
    _RENUMBER = 341,
    _UNPACK = 342,
    _DAILY = 343,
    _WEEKLY = 344,
    _FLAG = 345,
    _NEVER = 346,
    _HARD = 347,
    _SOFT = 348,
    _ALWAYS = 349,
    _ADDNOTE = 350,
    _COPY = 351,
    _REWRITE = 352,
    _IGNORE = 353,
    _DISPLAY = 354,
    _DELFILE = 355,
    _NEWMSG = 356,
    _WRITEFILE = 357,
    _APPENDTOFILE = 358,
    _CALL = 359,
    _ROUTE = 360,
    _ROUTEFBOX = 361,
    _ROUTEHUB = 362,
    _POLL = 363,
    _DELETEATTACH = 364,
    _CHANGEPATH = 365,
    _MOVEATTACH = 366,
    _ASCRIPT = 367,
    _TOLOWERPATH = 368,
    _TOUPPERPATH = 369,
    _COPYATTACHFBOX = 370,
    _MOVEATTACHFBOX = 371,
    _COPYATTACH = 372,
    _SPLIT = 373,
    _RECODE = 374,
    _ADDKLUDGE = 375,
    _HOLD = 376,
    _CRASH = 377,
    _DIRECT = 378,
    _NORMAL = 379,
    _IMMEDIATE = 380,
    LEXERR = 381
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{


    int          in;
    char         *ch;
    long         ln;
    KillModeT    kmode;
    CheckPointsT pmode;
    tBadMsgMode  bmode;
    tBadMsgMode  bpmode;
    fileboxType	fbtype;
    time_t       t;
    PKTMode      pktmode;


};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_CFG_HPP_INCLUDED  */
