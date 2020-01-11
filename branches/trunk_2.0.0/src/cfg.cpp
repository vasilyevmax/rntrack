/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */



/*
 *  RNtrack - FTN message tracker/router
 *
 *  cfg.(y|hpp|cpp) - Config file parser
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

#define YYDEBUG 0
/* #define YYERROR_VERBOSE */
#ifdef HAVE_CONFIG_H
# include "aconfig.h"
#endif

#include <stdlib.h>
#ifdef HAVE_MALLOC_H
   #include <malloc.h>
#endif
#include "msg.hpp"
#include "outbound.hpp"
#include "fidoaddr.hpp"
#include "vars.hpp"
#include "configure.hpp"
#include "constant.hpp"
#include "log.hpp"
#include "aka.hpp"
#include "age.hpp"
#include "scandir.hpp"
#include "attach.hpp"
#include "badpkt.hpp"
#include "badmsg.hpp"
#include "domain.hpp"
#include "filebox.hpp"
#include "passwd.hpp"
#include "nodelist.hpp"
#include "script.hpp"

#undef YYSTYPE               /* Perl also uses bison? damn! */

extern int DetectError;
extern bool NoTokensF;

extern FA   cffa;
extern FA   cffa1;
extern FA   cffa2;

static int brf = FALSE, arf = FALSE, renumberf = FALSE, unpackf = FALSE, freshf = FALSE;
static ScanDir *wsd = NULL;
static char *FileName = NULL;
static char *BPktDir = NULL;
static char *ScriptBefore = NULL;
static char *ScriptAfter = NULL;
static tTimes *tt;
static IndBiList<tTimes> *_TTimes;
static MSGBASE *mbase;
static Mask *msk = NULL;
static int MaskMode;
static int rc;
static int FlagMode = 0;
static Action *act = NULL;

static void CheckETTime(void) {
time_t tmt;
   if (tt->_ETime != 0 && tt->_ETime < tt->_STime) {
      tmt = tt->_ETime;
      tt->_ETime = (23*60*60)+(59*60)+59;
      tt->_ETime += TimeOfBeginOfDay(-1);
      _TTimes->AddToEnd(tt);
      tt = new tTimes;
      tt->_STime = TimeOfBeginOfDay(-1);
      tt->_ETime = tmt;
   }
}

static int PrepareMask(Mask &m) {
ScanDir *sd;
char ErrMess[128];

   CHP = 23700;
   sd = ScanDirs.GetLast();
   if (sd == NULL) {
      strcpy(ErrMess,"'");
      strcat(ErrMess,m.MaskName());
      strcat(ErrMess,":' without 'ScanDir:'");
      yyerror(ErrMess);
      return -1;
   }
   m.sd = sd;
   return 0;
}

static void AddReadyMask(Mask &m) {
ScanDir *sd;

   switch (PrevMask) {
      case 0: // first mask.
      case 1: // after action.
         LastDo = new DoList();
         sd = ScanDirs.GetLast();
         sd->_DoLists.AddToEnd(LastDo);
         PrevMask = 2;
         break;
      case 2: // after MASK.
         break;
   }
   LastDo->AddMask(m);
}


static int CheckMaskMode(char *f) {
char Buff[128];
   if (MaskMode != 0) {
      strcpy(Buff,"You can use '");
      strcat(Buff,f);
      strcat(Buff,"' flag only in 'Mask:'.");
      yyerror(Buff);
      return -1;
   }
   return 0;
}


static int ctoi(char *s) {
   char *foo;
   int res = 0;

   res = strtoul(s, &foo, 0);
   if (*foo)	/* parse error */
      return 0;
   return res;
}






# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "cfg.hpp".  */
#ifndef YY_YY_SRC_CFG_HPP_INCLUDED
# define YY_YY_SRC_CFG_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    _DOMAIN = 327,
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

/* Copy the second part of user declarations.  */



#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   426

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  174
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  157
/* YYNRULES -- Number of rules.  */
#define YYNRULES  344
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  535

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   381

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   136,     2,   167,   133,   135,   172,     2,
       2,     2,   134,   127,     2,   128,   129,   173,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   132,     2,
       2,     2,     2,     2,   171,   138,     2,     2,   170,   144,
       2,     2,   168,     2,     2,     2,   152,   139,     2,     2,
     131,     2,     2,   159,     2,   169,     2,     2,     2,     2,
       2,   165,     2,   166,     2,     2,     2,   137,   140,   141,
     142,   143,   145,   146,   147,   148,   149,   150,   151,   153,
     154,   155,   130,   156,   157,   158,   160,   161,   162,     2,
     163,   164,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   195,   195,   196,   200,   201,   206,   207,   208,   214,
     215,   216,   217,   218,   219,   220,   226,   227,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   258,   259,
     260,   261,   262,   263,   264,   265,   271,   277,   283,   289,
     295,   296,   297,   303,   309,   315,   321,   327,   333,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   350,   353,   359,   366,   373,   380,   381,   382,   383,
     387,   394,   402,   405,   405,   405,   415,   423,   431,   431,
     440,   443,   444,   445,   448,   451,   452,   453,   456,   464,
     472,   480,   488,   496,   504,   505,   508,   516,   524,   532,
     540,   548,   556,   564,   572,   580,   589,   598,   608,   607,
     625,   624,   642,   641,   659,   667,   668,   669,   670,   673,
     681,   682,   683,   684,   687,   695,   696,   697,   703,   702,
     733,   735,   734,   754,   755,   758,   759,   762,   771,   779,
     787,   796,   809,   820,   819,   833,   832,   847,   848,   858,
     862,   867,   888,   889,   893,   892,   914,   915,   923,   932,
     944,   945,   950,   950,   956,   956,   962,   962,   968,   976,
     980,   992,   996,  1016,   968,  1025,  1026,  1027,  1028,  1031,
    1032,  1035,  1042,  1045,  1046,  1049,  1050,  1050,  1052,  1053,
    1056,  1057,  1057,  1058,  1058,  1061,  1062,  1072,  1082,  1083,
    1084,  1085,  1091,  1097,  1098,  1108,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1131,  1132,  1147,  1153,  1159,  1165,  1165,
    1182,  1188,  1194,  1200,  1200,  1218,  1224,  1230,  1236,  1236,
    1255,  1268,  1255,  1274,  1275,  1278,  1279,  1280,  1281,  1282,
    1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,
    1293,  1294,  1295,  1296,  1297,  1298,  1299,  1300,  1301,  1302,
    1303,  1304,  1305,  1306,  1309,  1322,  1343,  1364,  1364,  1373,
    1379,  1389,  1395,  1398,  1404,  1404,  1445,  1459,  1473,  1486,
    1492,  1492,  1510,  1510,  1533,  1533,  1544,  1544,  1556,  1556,
    1568,  1569,  1570,  1571,  1572,  1575,  1575,  1589,  1599,  1605,
    1610,  1618,  1631,  1644,  1654,  1706,  1707,  1710,  1711,  1712,
    1719,  1726,  1733,  1740,  1747,  1754,  1761,  1768,  1775,  1788,
    1791,  1792,  1795,  1804,  1805
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_LOGFILE", "_LOGLEVEL", "_NODELIST",
  "_INDEXFILE", "_NODELISTPATH", "_ADDRESS", "_SYSOPNAME", "_USEOWNZONE",
  "_FORCEINTL", "_LOOPSTR", "_SCANDIR", "_MASK", "_SMASK", "_PMASK",
  "_BODYMASK", "_SBODYMASK", "_PBODYMASK", "_KLUDGEMASK", "_SKLUDGEMASK",
  "_PKLUDGEMASK", "_ACTION", "_MAXAGE", "_BADMESSAGES", "_NOLOGIGNORE",
  "_AKA", "_SKIPHIDDENFILES", "_FILEINBOUND", "_OUTBOUND", "_ADDTONULLPKT",
  "_TEMPMAIL", "_TRAFFICLOG", "_PASSWORD", "_UTC", "_ORIGIN", "_TEARLINE",
  "_INCLUDE", "_APKTDIR", "_CHECKPOINTS", "_SETVIAALWAYS", "_FRESH",
  "_CREATEMISSINGBASE", "_USENEWVIA", "_SCRIPTMASK", "_SSCRIPTMASK",
  "_PSCRIPTMASK", "_MAXATTACHSIZE", "_SEMAPHORE", "_SCRIPTFILE", "_USEASO",
  "_USEBRAKE", "_FILEBOXDIR", "_KILLROUTEDMESSAGE", "_IGNOREBSY",
  "_AFTERSCRIPT", "_BEFORESCRIPT", "_AGEFROMVIA", "_MAXNODELISTAGE",
  "_USEFILEBOXES", "_FILEBOXTYPE", "_LONG", "_TMLONG", "_TMSHORT",
  "_BRAKE", "_SOFTCHECKINNODELIST", "_BADPACKETS", "_IGNOREATTACHPATH",
  "_MAXPKTSIZE", "_MAXMSGSIZE", "_TIMESTAMPFILE", "_DOMAIN", "_FILEBOX",
  "_TRAFFICLOGTEMPLATE", "_STRIPPATHINPKT", "_CRLF", "_SKIP", "_DELETE",
  "_EXIT", "_MOVE", "__EOF", "_STRING", "_BEFOREROUTE", "_AFTERROUTE",
  "_DIGIT_", "_RENUMBER", "_UNPACK", "_DAILY", "_WEEKLY", "_FLAG",
  "_NEVER", "_HARD", "_SOFT", "_ALWAYS", "_ADDNOTE", "_COPY", "_REWRITE",
  "_IGNORE", "_DISPLAY", "_DELFILE", "_NEWMSG", "_WRITEFILE",
  "_APPENDTOFILE", "_CALL", "_ROUTE", "_ROUTEFBOX", "_ROUTEHUB", "_POLL",
  "_DELETEATTACH", "_CHANGEPATH", "_MOVEATTACH", "_ASCRIPT",
  "_TOLOWERPATH", "_TOUPPERPATH", "_COPYATTACHFBOX", "_MOVEATTACHFBOX",
  "_COPYATTACH", "_SPLIT", "_RECODE", "_ADDKLUDGE", "_HOLD", "_CRASH",
  "_DIRECT", "_NORMAL", "_IMMEDIATE", "LEXERR", "'+'", "'-'", "'.'", "'p'",
  "'P'", "':'", "'$'", "'*'", "'%'", "'!'", "'a'", "'A'", "'M'", "'b'",
  "'c'", "'d'", "'e'", "'E'", "'f'", "'g'", "'h'", "'i'", "'j'", "'k'",
  "'l'", "'L'", "'m'", "'n'", "'o'", "'q'", "'r'", "'s'", "'S'", "'t'",
  "'u'", "'v'", "'x'", "'y'", "'['", "']'", "'#'", "'H'", "'U'", "'D'",
  "'@'", "'&'", "'/'", "$accept", "Conf", "ConfLine", "$@1", "ScriptFile",
  "FileBoxDir", "FileBoxType", "FBOXTYPE", "TrafficLogTemplate",
  "Semaphore", "IncludeF", "Aka", "$@2", "$@3", "TimeStampFile", "APktDir",
  "Address", "$@4", "CheckPoints", "ChkPntMode", "KillRoutedMessage",
  "KillRMode", "SysopName", "TearLine", "LogFile", "LogLevel", "Origin",
  "Nodelist", "NdlZone", "NodelistPath", "IndexFile", "LoopStr",
  "MaxAttachSize", "MaxNodelistAge", "Outbound", "TempMail", "TrafficLog",
  "FileInbound", "MaxAge", "MaxMsgSize", "MaxPktSize", "Password", "$@5",
  "Domain", "$@6", "FileBox", "$@7", "BadMessages", "BadMsgMode",
  "BadPackets", "BadPktMode", "Utc", "UtcOffs", "ScanDir", "$@8", "SDType",
  "$@9", "BeforeAfter", "AddSdParam", "SdParam", "STime", "$@10", "$@11",
  "DaySTime", "DaySSTime", "AnyP", "Time", "@12", "WeekSTime",
  "WeekSSTime", "Flag", "Mask", "$@13", "SMask", "$@14", "PMask", "$@15",
  "MParam", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21", "SyName",
  "MString", "MDigit", "MNot", "MsgAttr", "$@22", "MsgFAttr", "FlagsMode",
  "$@23", "$@24", "FlagsChar", "KludgeMask", "SKludgeMask", "PKludgeMask",
  "KMParam", "$@25", "BodyMask", "SBodyMask", "PBodyMask", "BMParam",
  "$@26", "ScriptMask", "SScriptMask", "PScriptMask", "SCRMParam", "$@27",
  "Action", "$@28", "$@29", "MayBeActTime", "ActionCmd", "AAddNote",
  "AMove", "ACopy", "ARewrite", "$@30", "ADisplay", "AScript", "AAFlag",
  "AFlag", "ADelFile", "ANewMsg", "$@31", "AWriteFile", "AAppendToFile",
  "ACall", "ARoute", "$@32", "ARouteFbox", "$@33", "ARouteHub", "$@34",
  "ACopyAttachFbox", "$@35", "AMoveAttachFbox", "$@36", "RouMode", "APoll",
  "$@37", "AChangePath", "AToLowerPath", "AToUpperPath", "AAddKludge",
  "AMoveAttach", "ACopyAttach", "ASplit", "ARecode", "faddress",
  "FullFtnAddr", "pointaddr", "PntAddr", "nodeaddr", "dw", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,    43,    45,    46,
     112,    80,    58,    36,    42,    37,    33,    97,    65,    77,
      98,    99,   100,   101,    69,   102,   103,   104,   105,   106,
     107,   108,    76,   109,   110,   111,   113,   114,   115,    83,
     116,   117,   118,   120,   121,    91,    93,    35,    72,    85,
      68,    64,    38,    47
};
# endif

#define YYPACT_NINF -484

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-484)))

#define YYTABLE_NINF -345

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -484,   344,  -484,     0,   -68,     5,    15,    22,    25,  -484,
      30,    35,    37,    32,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,    58,   -44,    68,  -484,    70,
      65,    67,    74,    71,    72,   101,   -78,   102,   103,   104,
     105,   -14,    75,   112,   113,  -484,  -484,  -484,    60,   106,
     108,   116,   118,   114,   -62,   121,   122,   119,   123,   -25,
     124,   -34,   125,   151,   152,   156,   157,   158,   159,   127,
    -484,  -484,   130,   131,   166,   167,   168,   169,   170,   171,
     172,   173,   175,   176,   177,   178,   179,   180,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   193,   194,
     195,   196,   197,   198,   199,   200,   203,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,  -484,  -484,  -484,   222,  -484,  -484,   -75,  -484,
    -484,  -484,  -484,    -1,  -484,  -484,  -484,  -484,   -67,  -484,
    -484,  -484,   -67,  -484,  -484,   115,  -484,  -484,  -484,  -484,
     223,  -484,  -484,   -75,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,   224,   225,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,   226,  -484,  -484,
    -484,   229,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,   230,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,   174,
     192,   -69,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
     201,   181,  -484,  -484,  -484,  -484,   227,  -484,   -65,  -484,
    -484,  -484,  -484,   -50,   -67,  -484,   232,   233,   234,   237,
    -484,  -484,   238,   240,  -484,   241,   242,   243,   -99,   -99,
     -99,   -99,  -484,   245,   246,   247,  -484,  -484,   -99,   -99,
     249,   248,   250,   252,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,   -75,  -484,  -484,  -484,  -484,  -484,
     -75,   -75,   251,  -484,   -81,   -77,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,   -50,   253,   -50,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,   255,   257,   258,   259,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,   260,   133,   -75,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,   126,   -15,
     -75,  -484,  -484,  -484,  -484,   261,  -484,  -484,   304,   -75,
     -75,  -484,   -75,   -75,   -75,  -484,   -70,  -484,  -484,   -77,
    -484,   318,   319,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,   134,  -484,
    -484,  -484,  -484,  -484,   -65,  -484,  -484,   -76,   321,  -484,
    -484,  -484,  -484,  -484,   206,   279,   280,  -484,   -75,   277,
     336,   336,   337,  -484,   338,  -484,  -484,  -484,   -67,  -484,
    -484,   290,  -484,  -484,   -22,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,   -22,  -484,  -484,
      18,    18,  -484,  -484,  -484
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,    88,
       0,     0,     0,     0,   138,   172,   174,   176,   243,   243,
     243,   238,   238,   238,   250,     0,     0,     0,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   248,   248,   248,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      72,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,   100,   101,   104,   107,   106,     0,    98,
      53,    17,   108,     0,   178,   178,   178,   240,     0,   241,
     242,   235,     0,   236,   237,     0,   115,   125,   127,   126,
       0,   124,    37,     0,    48,   114,   111,     8,   112,   113,
     118,   135,     0,     0,   134,   102,    99,    82,    87,    91,
      92,    93,    90,    47,    15,    52,   245,     0,   246,   247,
     109,     0,    73,    54,    55,    74,    97,    96,    95,    94,
      45,    58,   110,    56,    76,    77,    78,    79,    75,    49,
     130,   132,   131,     0,   129,    46,   117,   116,    86,   120,
     122,    80,    57,    67,    68,    69,    66,    65,     5,     9,
       6,    10,     7,    14,    20,    50,    51,    24,    25,    18,
      35,    36,    19,    26,    31,    34,    38,    60,    61,    16,
      30,    32,    33,    39,    40,    41,    62,    63,    59,    64,
      27,    28,    29,    21,    22,    23,    11,    12,    13,    42,
      43,    44,     4,    71,   105,   103,   343,   334,   336,   329,
     337,     0,   330,   331,   332,   333,   335,    89,   325,   328,
     327,     0,   141,   143,   144,   139,   170,   173,     0,   175,
     177,   189,   190,   193,     0,   256,     0,     0,     0,     0,
     287,   260,     0,     0,   294,     0,     0,     0,     0,     0,
       0,     0,   272,     0,     0,     0,   318,   319,     0,     0,
       0,     0,     0,     0,   251,   255,   257,   258,   259,   261,
     282,   262,   291,   263,   264,   265,   266,   267,   268,   269,
     270,   279,   277,   271,   273,   274,   275,   283,   276,   278,
     280,   281,   128,    84,     0,   136,   137,   249,    81,   133,
       0,     0,     0,   326,     0,     0,   145,   140,   171,   185,
     186,   187,   188,   179,   192,   194,   193,     0,   193,   285,
     292,   284,   286,   178,   289,   293,     0,     0,     0,   299,
     310,   311,   312,   313,   314,   300,   302,   304,   315,   317,
     321,   290,   306,   308,   322,   323,   324,     0,   253,     0,
     119,   121,   123,   338,   344,   341,   339,   340,     0,   170,
       0,   244,   191,   239,   288,     0,   296,   297,     0,     0,
       0,   305,     0,     0,     0,   320,     0,   252,    85,     0,
     150,     0,     0,   147,   151,   153,   155,   146,   152,   142,
     180,   178,   298,   301,   303,   316,   307,   309,     0,   342,
     149,   148,   157,   166,     0,   295,   254,   154,   156,   181,
     164,   162,   163,   158,     0,   159,   168,   167,     0,     0,
       0,     0,     0,   182,     0,   161,   160,   169,     0,   165,
     183,   196,   195,   184,     0,   234,   201,   203,   224,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   197,   198,   200,
       0,     0,   199,   202,   204
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -135,  -484,  -484,  -484,  -484,  -484,  -450,  -484,  -484,  -484,
    -117,  -484,  -484,  -484,  -484,  -484,  -484,  -133,  -484,  -484,
    -484,  -484,  -484,  -484,  -161,  -142,  -291,  -484,  -484,  -484,
    -484,  -223,  -484,  -484,  -483,  -484,  -484,  -484,    29,  -484,
    -484,  -484,  -484,    69,  -484,  -484,  -484,  -484,    63,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,   281,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -298,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,  -484,
    -484,  -152,   154,  -484,  -484,  -484,  -359
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    71,   263,    72,    73,    74,   198,    75,    76,
      77,    78,   153,   409,    79,    80,    81,   128,    82,   172,
      83,   189,    84,    85,    86,    87,    88,    89,   265,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   354,   103,   360,   104,   361,   105,   151,   106,
     204,   107,   164,   108,   133,   285,   366,   286,   419,   447,
     448,   462,   463,   467,   473,   474,   475,   479,   468,   477,
     367,   109,   134,   110,   135,   111,   136,   287,   288,   420,
     464,   478,   488,   491,   373,   293,   376,   377,   493,   494,
     527,   528,   530,   531,   529,   112,   113,   114,   141,   142,
     115,   116,   117,   137,   138,   118,   119,   120,   176,   177,
     121,   145,   408,   437,   324,   325,   326,   327,   328,   383,
     329,   330,   331,   368,   333,   334,   386,   335,   336,   337,
     338,   429,   339,   430,   340,   431,   341,   433,   342,   434,
     395,   343,   432,   344,   345,   346,   347,   348,   349,   350,
     351,   277,   278,   279,   416,   280,   281
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     294,   353,   289,   290,   266,   417,   418,   161,   266,   470,
     266,   396,   397,   398,   123,   291,   266,   369,   445,   446,
     402,   403,   390,   391,   392,   393,   394,   440,   186,   187,
     485,   486,   188,   147,   148,   149,   150,   194,   195,   196,
     197,   441,   442,   200,   201,   202,   203,   533,   534,   162,
     163,   143,   144,   414,   471,   472,   267,   414,   268,   269,
     270,   271,   267,   495,   268,   269,   270,   292,   370,   371,
     372,   443,   444,   445,   446,   297,   122,   169,   170,   171,
     459,   282,   283,   284,   374,   421,   375,   423,   139,   140,
     124,   415,   272,   273,   274,   275,   276,   125,   272,   273,
     274,   275,   276,   495,   126,   496,   497,   127,   498,   178,
     179,   130,   129,   131,   132,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   146,   152,   180,   154,   155,   498,   156,
     157,   173,   378,   158,   159,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   160,   165,   166,   167,   168,   174,   175,
     182,   181,   183,   295,   184,   296,   185,   190,   191,   193,
     199,   205,   410,   212,   192,   297,   213,   214,   411,   412,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   206,   207,   208,   209,
     210,   211,   215,   216,   217,   218,   219,   220,   221,   222,
     424,   223,   224,   225,   226,   227,   228,   438,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   450,   239,
     240,   241,   242,   243,   244,   245,   246,   453,   454,   247,
     455,   456,   457,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   436,   439,
     466,   458,   449,   469,   532,   352,  -344,   264,   357,   355,
     356,   358,   359,   365,   379,   380,   381,   297,   465,   382,
     384,   362,   385,   387,   388,   389,   483,   399,   400,   401,
     364,   404,   406,   405,   407,   480,   413,   425,   422,   426,
     427,   428,   435,   451,     2,     3,   490,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   452,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     460,   461,    56,    57,    58,    59,   476,   481,   482,   484,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   470,   487,   489,   492,   363,   332
};

static const yytype_uint16 yycheck[] =
{
     142,   153,   135,   136,    85,   364,   365,    85,    85,    85,
      85,   309,   310,   311,    82,    82,    85,    82,    88,    89,
     318,   319,   121,   122,   123,   124,   125,    42,    90,    91,
     480,   481,    94,    77,    78,    79,    80,    62,    63,    64,
      65,    56,    57,    77,    78,    79,    80,   530,   531,   127,
     128,    22,    23,   134,   130,   131,   131,   134,   133,   134,
     135,   136,   131,    85,   133,   134,   135,   134,   133,   134,
     135,    86,    87,    88,    89,    90,    76,    91,    92,    93,
     439,    82,    83,    84,   134,   376,   136,   378,    19,    20,
      85,   172,   167,   168,   169,   170,   171,    82,   167,   168,
     169,   170,   171,    85,    82,   127,   128,    82,   130,    46,
      47,    76,    82,    76,    82,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,    85,    76,    85,    76,    82,   130,    82,
      76,    76,   294,    82,    82,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,    82,    82,    82,    82,    82,    76,    76,
      82,    85,    76,    78,    76,    80,    82,    76,    76,    76,
      76,    76,   354,    76,    85,    90,    76,    76,   360,   361,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    85,    85,    82,    82,
      82,    82,    76,    76,    76,    76,    76,    76,    76,    76,
     383,    76,    76,    76,    76,    76,    76,   409,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,   420,    76,
      76,    76,    76,    76,    76,    76,    76,   429,   430,    76,
     432,   433,   434,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,   165,   173,
     166,   436,   419,   464,   527,    82,   132,    85,    82,    85,
      85,    82,    82,   132,    82,    82,    82,    90,   451,    82,
      82,   129,    82,    82,    82,    82,   478,    82,    82,    82,
     129,    82,    82,    85,    82,   129,    85,    82,    85,    82,
      82,    82,    82,    82,     0,     1,   488,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    82,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      82,    82,    58,    59,    60,    61,    85,   128,   128,   132,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    85,    85,    85,   134,   271,   145
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   175,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    58,    59,    60,    61,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   176,   178,   179,   180,   182,   183,   184,   185,   188,
     189,   190,   192,   194,   196,   197,   198,   199,   200,   201,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   217,   219,   221,   223,   225,   227,   245,
     247,   249,   269,   270,   271,   274,   275,   276,   279,   280,
     281,   284,    76,    82,    85,    82,    82,    82,   191,    82,
      76,    76,    82,   228,   246,   248,   250,   277,   278,   277,
     277,   272,   273,   272,   272,   285,    85,    77,    78,    79,
      80,   222,    76,   186,    76,    82,    82,    76,    82,    82,
      82,    85,   127,   128,   226,    82,    82,    82,    82,    91,
      92,    93,   193,    76,    76,    76,   282,   283,   282,   282,
      85,    85,    82,    76,    76,    82,    90,    91,    94,   195,
      76,    76,    85,    76,    62,    63,    64,    65,   181,    76,
      77,    78,    79,    80,   224,    76,    85,    85,    82,    82,
      82,    82,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,   177,    85,   202,    85,   131,   133,   134,
     135,   136,   167,   168,   169,   170,   171,   325,   326,   327,
     329,   330,    82,    83,    84,   229,   231,   251,   252,   251,
     251,    82,   134,   259,   259,    78,    80,    90,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   288,   289,   290,   291,   292,   294,
     295,   296,   297,   298,   299,   301,   302,   303,   304,   306,
     308,   310,   312,   315,   317,   318,   319,   320,   321,   322,
     323,   324,    82,   325,   216,    85,    85,    82,    82,    82,
     218,   220,   129,   326,   129,   132,   230,   244,   297,    82,
     133,   134,   135,   258,   134,   136,   260,   261,   259,    82,
      82,    82,    82,   293,    82,    82,   300,    82,    82,    82,
     121,   122,   123,   124,   125,   314,   314,   314,   314,    82,
      82,    82,   314,   314,    82,    85,    82,    82,   286,   187,
     325,   325,   325,    85,   134,   172,   328,   330,   330,   232,
     253,   260,    85,   260,   251,    82,    82,    82,    82,   305,
     307,   309,   316,   311,   313,    82,   165,   287,   325,   173,
      42,    56,    57,    86,    87,    88,    89,   233,   234,   244,
     325,    82,    82,   325,   325,   325,   325,   325,   234,   330,
      82,    82,   235,   236,   254,   251,   166,   237,   242,   258,
      85,   130,   131,   238,   239,   240,    85,   243,   255,   241,
     129,   128,   128,   325,   132,   240,   240,    85,   256,    85,
     259,   257,   134,   262,   263,    85,   127,   128,   130,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   264,   265,   268,
     266,   267,   265,   268,   268
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   174,   175,   175,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     177,   176,   176,   178,   179,   180,   181,   181,   181,   181,
     182,   183,   184,   186,   187,   185,   188,   189,   191,   190,
     192,   193,   193,   193,   194,   195,   195,   195,   196,   197,
     198,   199,   200,   201,   202,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   216,   215,
     218,   217,   220,   219,   221,   222,   222,   222,   222,   223,
     224,   224,   224,   224,   225,   226,   226,   226,   228,   227,
     229,   230,   229,   231,   231,   232,   232,   233,   233,   233,
     233,   233,   233,   235,   234,   236,   234,   237,   237,   238,
     238,   238,   239,   239,   241,   240,   242,   242,   243,   243,
     244,   244,   246,   245,   248,   247,   250,   249,   252,   253,
     254,   255,   256,   257,   251,   258,   258,   258,   258,   259,
     259,   260,   260,   261,   261,   262,   263,   262,   264,   264,
     265,   266,   265,   267,   265,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   269,   270,   271,   273,   272,
     274,   275,   276,   278,   277,   279,   280,   281,   283,   282,
     285,   286,   284,   287,   287,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   289,   290,   291,   293,   292,   294,
     295,   296,   297,   298,   300,   299,   301,   302,   303,   303,
     305,   304,   307,   306,   309,   308,   311,   310,   313,   312,
     314,   314,   314,   314,   314,   316,   315,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   325,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   327,
     328,   328,   329,   330,   330
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       0,     3,     1,     2,     2,     2,     1,     1,     1,     1,
       2,     3,     2,     0,     0,     5,     2,     2,     0,     3,
       2,     1,     1,     1,     2,     1,     1,     1,     2,     2,
       2,     2,     2,     3,     0,     1,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     4,
       0,     4,     0,     4,     2,     1,     1,     1,     2,     2,
       1,     1,     1,     2,     2,     1,     2,     2,     0,     3,
       2,     0,     4,     1,     1,     0,     2,     1,     2,     2,
       1,     1,     1,     0,     3,     0,     3,     0,     2,     1,
       3,     3,     1,     1,     0,     4,     0,     2,     1,     3,
       0,     1,     0,     3,     0,     3,     0,     3,     0,     0,
       0,     0,     0,     0,    12,     1,     1,     1,     1,     1,
       1,     2,     1,     0,     1,     1,     0,     2,     1,     2,
       1,     0,     3,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     0,     4,
       2,     2,     2,     0,     4,     2,     2,     2,     0,     2,
       0,     0,     5,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     0,     3,     2,
       2,     1,     2,     2,     0,     5,     3,     3,     4,     2,
       0,     4,     0,     4,     0,     3,     0,     4,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     2,     1,     1,
       3,     2,     2,     2,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     1,     5,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yyx != YYTERROR && yycheck[yyx + yyn] == yyx
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:

    {
            if (SetInclude((yyvsp[-1].ch)) != 0) {
               YYABORT;
            }
         }

    break;

  case 8:

    {
               if (SetAddToNullPkt() != 0) {
                  YYABORT;
               }
            }

    break;

  case 15:

    {
               if (SetCreateMissingBase() != 0) {
                  YYABORT;
               }
            }

    break;

  case 17:

    {
               if (SetForceINTL() != 0) {
                  YYABORT;
               }
            }

    break;

  case 37:

    {
               if (SetNoLogIgnore() != 0) {
                  YYABORT;
               }
            }

    break;

  case 45:

    {
               if (SetIgnoreBSY() != 0) {
                  YYABORT;
               }
            }

    break;

  case 46:

    {
               if (SetIgnoreAttachPath() != 0) {
                  YYABORT;
               }
            }

    break;

  case 47:

    {
               if (SetSetViaAlways() != 0) {
                  YYABORT;
               }
            }

    break;

  case 48:

    {
               if (SetSkipHiddenFiles() != 0) {
                  YYABORT;
               }
            }

    break;

  case 49:

    {
               if (SetSoftCheckInNodelists() != 0) {
                  YYABORT;
               }
            }

    break;

  case 52:

    {
               if (SetNewVia() != 0) {
                  YYABORT;
               }
            }

    break;

  case 53:

    {
               if (SetUseOwnZone() != 0) {
                  YYABORT;
               }
            }

    break;

  case 54:

    {
	            if (SetUseASO() != 0) {
                  YYABORT;
	            }
	         }

    break;

  case 55:

    {
		    if (SetUseBrake() != 0) {
		  YYABORT;
		    }
		 }

    break;

  case 56:

    {
	            if (SetUseFileBoxes() != 0) {
                  YYABORT;
	            }
	         }

    break;

  case 57:

    {
				   if (SetStripPathInPkt() != 0) {
					   YYABORT;
               }
            }

    break;

  case 58:

    {
               if (SetAgeFromVia() != 0) {
                  YYABORT;
               }
            }

    break;

  case 70:

    { YYABORT; }

    break;

  case 71:

    { DetectError = TRUE;
         }

    break;

  case 72:

    {
            avail = 0;
         }

    break;

  case 73:

    {
               if (LoadScriptFile((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
             }

    break;

  case 74:

    {
               if (SetFileBoxDir((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
             }

    break;

  case 75:

    {
                if (SetFileBoxType((yyvsp[0].fbtype)) != 0) {
		  YYABORT;
                }
              }

    break;

  case 76:

    { (yyval.fbtype) = FILEBOXLONG; }

    break;

  case 77:

    { (yyval.fbtype) = FILEBOXTMLONG; }

    break;

  case 78:

    { (yyval.fbtype) = FILEBOXTMSHORT; }

    break;

  case 79:

    { (yyval.fbtype) = FILEBOXBRAKE; }

    break;

  case 80:

    {
                      if (SetTrafficLogTemplate((yyvsp[0].ch)) != 0) {
                         YYABORT;
                      }
                   }

    break;

  case 81:

    {
             if (SetSemaphoreName((yyvsp[0].ch), (yyvsp[-1].ln)) != 0) {
                YYABORT;
             }
          }

    break;

  case 82:

    { (yyval.ch) = (yyvsp[0].ch); }

    break;

  case 83:

    { cffa.Clean(); }

    break;

  case 84:

    { cffa1 = cffa; cffa.Clean(); }

    break;

  case 85:

    {
               if (SetAka(cffa1, cffa) != 0) {
                  YYABORT;
               }
               cffa.Clean();
               cffa1.Clean();
            }

    break;

  case 86:

    {
               if (SetTimeStampFile((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 87:

    {
               if (SetAPktDir((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 88:

    { cffa.Clean(); }

    break;

  case 89:

    {
               if (SetMyAddr(cffa) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 90:

    { SetCheckPoints((yyvsp[0].pmode)); }

    break;

  case 91:

    { (yyval.pmode) = CHECKPNT_NEVER; }

    break;

  case 92:

    { (yyval.pmode) = CHECKPNT_HARD; }

    break;

  case 93:

    { (yyval.pmode) = CHECKPNT_SOFT; }

    break;

  case 94:

    { SetKillRoutedMessages((yyvsp[0].kmode)); }

    break;

  case 95:

    { (yyval.kmode) = KILL_ALWAYS; }

    break;

  case 96:

    { (yyval.kmode) = KILL_NEVER; }

    break;

  case 97:

    { (yyval.kmode) = KILL_FLAG; }

    break;

  case 98:

    {
               if (SetSysopName((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 99:

    {
               if (SetTearline((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 100:

    {
               if (SetLogFile((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 101:

    {
               if (SetLogLevel((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 102:

    {
               if (SetOrigin((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 103:

    {
               if (SetNodelist((yyvsp[-1].ch),(yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 104:

    { (yyval.ln) = -3; }

    break;

  case 105:

    { (yyval.ln) = (yyvsp[0].ln); }

    break;

  case 106:

    {
               if (SetNodelistPath((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 107:

    {
               if (SetIndexFile((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 108:

    {
               if (SetLoopStr((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 109:

    {
               if (SetMaxAttach((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 110:

    {
               if (SetMaxNodelistAge((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 111:

    {
               if (SetOutbound((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 112:

    {
               if (SetTempMail((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 113:

    {
               if (SetTrafficLog((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 114:

    {
               if (SetFileInbound((yyvsp[0].ch)) != 0) {
                  YYABORT;
               }
            }

    break;

  case 115:

    {
               if (SetMaxAge((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 116:

    {
               if (SetMaxMsgSize((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 117:

    {
               if (SetMaxPktSize((yyvsp[0].ln)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 118:

    {
               if (strlen((yyvsp[0].ch)) > 8){
                  yyerror("Password too long. Max password length is a 8 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 119:

    {
               if (SetPasswd(cffa, (yyvsp[-2].ch)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 120:

    {
               if (strlen((yyvsp[0].ch)) > 10){
                  yyerror("Domain too long. Max domain length is a 10 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 121:

    {
               if (SetDomain(cffa, (yyvsp[-2].ch)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 122:

    {
               if (strlen((yyvsp[0].ch)) > 100){
                  yyerror("Path too long. Max path length is a 100 characters.");
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 123:

    {
               if (SetFilebox(cffa, (yyvsp[-2].ch)) != 0) {
                  YYABORT;
               }
               cffa.Clean();
            }

    break;

  case 124:

    {
                if (SetBadMode((yyvsp[0].bmode),FileName) != 0) {
                  YYABORT;
                }
                FileName = NULL;
              }

    break;

  case 125:

    { (yyval.bmode) = SKIP; FileName = NULL;}

    break;

  case 126:

    { (yyval.bmode) = EXIT; FileName = NULL;}

    break;

  case 127:

    { (yyval.bmode) = REMOVE; FileName = NULL;}

    break;

  case 128:

    { (yyval.bmode) = MOVE; FileName = (yyvsp[0].ch);}

    break;

  case 129:

    {
                if (SetBadPktMode((yyvsp[0].bpmode),BPktDir) != 0) {
                  YYABORT;
                }
		BPktDir = NULL;
              }

    break;

  case 130:

    { (yyval.bpmode) = SKIP; BPktDir = NULL;}

    break;

  case 131:

    { (yyval.bpmode) = EXIT; BPktDir = NULL;}

    break;

  case 132:

    { (yyval.bpmode) = REMOVE; BPktDir = NULL;}

    break;

  case 133:

    { (yyval.bpmode) = MOVE; BPktDir = (yyvsp[0].ch);}

    break;

  case 134:

    {
                if (SetUTC((yyvsp[0].ln)) != 0) {
                  YYABORT;
                }
              }

    break;

  case 135:

    { (yyval.ln) = (yyvsp[0].ln); }

    break;

  case 136:

    { (yyval.ln) = (yyvsp[0].ln); }

    break;

  case 137:

    { (yyval.ln) = -(yyvsp[0].ln); }

    break;

  case 138:

    {
              wsd = new ScanDir();
              CheckMem((char *)wsd);
              renumberf = FALSE;
              unpackf = FALSE;
              freshf = FALSE;
              arf = FALSE;
              brf = FALSE;
              _TTimes = &wsd->_Times;
              mbase = NULL;
              PrevMask = 0;
              ScriptBefore = NULL;
              ScriptAfter = NULL;
              FileName = NULL;
           }

    break;

  case 139:

    {
              wsd->SetBase(mbase);
              wsd->_Renumber = renumberf;
              wsd->_Unpack = unpackf;
              wsd->_Fresh = freshf;
              wsd->_FlagFile = FileName;
              wsd->_ScriptBefore = ScriptBefore;
              wsd->_ScriptAfter = ScriptAfter;
              ScanDirs.AddToEnd(wsd);
              if (brf) BeforeRoute = wsd;
              if (arf) AfterRoute = wsd;
           }

    break;

  case 141:

    {
             mbase = MakeBase((yyvsp[0].ch));
             if (mbase == NULL) {
                YYABORT;
             }
             if (!mbase->Set((yyvsp[0].ch),BASE_IN)) {
                delete mbase;
                mbase = NULL;
                yyerror("Unable to open message base.");
                YYABORT;
             }
             if (!mbase->CheckIn()) {
                delete mbase;
                YYABORT;
             }
          }

    break;

  case 143:

    { brf = TRUE; }

    break;

  case 144:

    { arf = TRUE; }

    break;

  case 147:

    {
                  if (renumberf == (int)TRUE) {
                     yyerror("Renumber for this base already set.");
                     YYABORT;
                  } else {
                    renumberf = TRUE;
                  }
               }

    break;

  case 148:

    {
                  if (!ScriptWordExists((yyvsp[0].ch))) {
                     yyerror("Script function not found.");
                     YYABORT;
                  }
                  ScriptBefore = strdup((yyvsp[0].ch));
               }

    break;

  case 149:

    {
                  if (!ScriptWordExists((yyvsp[0].ch))) {
                     yyerror("Script function not found.");
                     YYABORT;
                  }
                  ScriptAfter = strdup((yyvsp[0].ch));
               }

    break;

  case 150:

    {
                  if (freshf == (int)TRUE) {
                     yyerror("Fresh scripts for this base already set.");
                     YYABORT;
                  } else {
                     freshf = TRUE;
                  }
               }

    break;

  case 151:

    {
                  if (unpackf == (int)TRUE) {
                     yyerror("Unpack for this base already set.");
                     YYABORT;
                  } else {
                     unpackf = TRUE;
                  }
                  if (Outbound == NULL) {
                     yyerror("Outbound directory not specified.");
                     YYABORT;
                  }
               }

    break;

  case 152:

    {
                  if (TimeStampFile == NULL) {
                     yyerror("You can't set scanning time without Timestamp File.");
                     YYABORT;
                  }

               }

    break;

  case 153:

    {
                  tt = new tTimes;
                  tt->_STime = TimeOfBeginOfDay(-1);
                  tt->_ETime = 0;
               }

    break;

  case 154:

    {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                  }
               }

    break;

  case 155:

    {
                  tt = new tTimes;
                  tt->_STime = TimeOfBeginOfDay(0);
                  tt->_ETime = 0;
               }

    break;

  case 156:

    {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                  }
               }

    break;

  case 158:

    {
                  if (tt->_STime != 0) {
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                     tt = new tTimes;
                  }
               }

    break;

  case 159:

    {
                  tt->_STime = (yyvsp[0].t) + TimeOfBeginOfDay(-1);
               }

    break;

  case 160:

    {
                  tt->_STime = (yyvsp[-2].t) + TimeOfBeginOfDay(-1);
                  tt->_ETime = (yyvsp[0].t) + TimeOfBeginOfDay(-1) + 59;
               }

    break;

  case 161:

    {
                  time_t i_time;
                  time_t b_time;
                  if ((yyvsp[0].t) == (time_t) 0) {
                     yyerror("Time of pereodical event should be between 00:01 and 23:59");
                     YYABORT;
                  }
                  tt->_STime = TimeOfBeginOfDay(-1);
                  b_time = tt->_STime;
                  do {
                     i_time = tt->_STime;
                     CheckETTime();
                     _TTimes->AddToEnd(tt);
                     tt = new tTimes;
                     tt->_ETime = 0;
                     tt->_STime = i_time + (yyvsp[0].t);
                  } while (tt->_STime < (b_time + (23*60*60)+(59*60)+60));
                  tt->_STime = 0;
            }

    break;

  case 164:

    {
                 if ((yyvsp[0].ln) < 0 || (yyvsp[0].ln) > 23) {
                    yyerror("Hour should be between 00 and 23");
                    YYABORT;
                 } else {
                    (yyval.t) = (time_t) ((yyvsp[0].ln) * 60);
                 }
              }

    break;

  case 165:

    {
                 if ((yyvsp[0].ln) < 0 || (yyvsp[0].ln) > 59 || (yyvsp[-2].t) == (time_t) -1) {
                    (yyval.t) = (time_t)-1;
                    yyerror("Minutes should be between 00 and 59");
                    YYABORT;
                 } else {
                    (yyval.t) = (yyvsp[-2].t) + (time_t) (yyvsp[0].ln);
                    (yyval.t) *= 60;
                 }
              }

    break;

  case 167:

    {
                  CheckETTime();
                  _TTimes->AddToEnd(tt);
                  tt = new tTimes;
               }

    break;

  case 168:

    {
                 if ((yyvsp[0].ln) < 0 || (yyvsp[0].ln) > 6) {
                    yyerror("Day of week should be between 0 and 6");
                    YYABORT;
                 } else {
                    tt->_STime = TimeOfBeginOfDay((yyvsp[0].ln));
                 }
              }

    break;

  case 169:

    {
                 if ((yyvsp[-2].ln) < 0 || (yyvsp[-2].ln) > 6 || (yyvsp[0].ln) < 0 || (yyvsp[0].ln) > 6) {
                    yyerror("Day of week should be between 0 and 6");
                    YYABORT;
                 } else {
                    tt->_STime = TimeOfBeginOfDay((yyvsp[-2].ln));
                    tt->_ETime = TimeOfBeginOfDay((yyvsp[0].ln)) + (23*60*60)+(59*60)+59;
                 }
              }

    break;

  case 170:

    { FileName = NULL; }

    break;

  case 171:

    { FileName = strdup((yyvsp[0].ch)); }

    break;

  case 172:

    { MaskMode = 0; }

    break;

  case 173:

    {
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(NormalMask *)msk);
            }

    break;

  case 174:

    { MaskMode = 0; }

    break;

  case 175:

    {
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(NormalMask *)msk);
            }

    break;

  case 176:

    { MaskMode = 0; }

    break;

  case 177:

    {
               msk->_Type = MASK_ADD;
               AddReadyMask(*(NormalMask *)msk);
            }

    break;

  case 178:

    {
               msk = new NormalMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }

    break;

  case 179:

    {
               ((NormalMask *)msk)->_FromName = strdup((yyvsp[0].ch));
               cffa.Clean();
            }

    break;

  case 180:

    {
               ((NormalMask *)msk)->_FromAddr = cffa;
               if (MaskMode == 0) {
                  rc = ((NormalMask *)msk)->_FromAddr.MaskValid();
               } else {
                  rc = ((NormalMask *)msk)->_FromAddr.ActValid();
               }
               if (!rc) {
                  yyerror("Invalid 'From' Address.");
                  YYABORT;
               }
            }

    break;

  case 181:

    {
               ((NormalMask *)msk)->_ToName = strdup((yyvsp[0].ch));
               cffa.Clean();
            }

    break;

  case 182:

    {
               ((NormalMask *)msk)->_ToAddr = cffa;
               if (MaskMode == 0) {
                  rc = ((NormalMask *)msk)->_ToAddr.MaskValid();
               } else {
                  rc = ((NormalMask *)msk)->_ToAddr.ActValid();
               }
               if (!rc) {
                  yyerror("Invalid 'To' Address.");
                  YYABORT;
               }
               if ((((NormalMask *)msk)->_ToAddr.Zone() & (FA_LSTMASK|FA_HOLDMASK|FA_DOWNMASK|FA_PVTMASK|FA_HUBMASK)) && (!Ndl.Enabled())) {
                  yyerror("You can't use '#','H','D','U' or 'P' mask without nodelist.");
                  YYABORT;
               }
               if ((((NormalMask *)msk)->_ToAddr.Point() & FA_SUBMASK) && (!Ndl.Enabled())) {
                  yyerror("You can't use '&' mask without nodelist.");
                  YYABORT;
               }
            }

    break;

  case 183:

    {
               ((NormalMask *)msk)->_Subject = strdup((yyvsp[0].ch));
               NoTokensF = TRUE;
            }

    break;

  case 184:

    {
               NoTokensF = FALSE;
            }

    break;

  case 186:

    { (yyval.ch) = (char *)"$"; }

    break;

  case 187:

    { (yyval.ch) = (char *)"*"; }

    break;

  case 188:

    { (yyval.ch) = (char *)"%"; }

    break;

  case 190:

    { (yyval.ch) = (char *)"*"; }

    break;

  case 191:

    {
               if ((yyvsp[0].ln) > 65535) {
                  yyerror("Parameter shoul be less that 65535");
                  YYABORT;
               }
               (yyval.ln) = (yyvsp[-1].ln) | (yyvsp[0].ln);
            }

    break;

  case 192:

    { (yyval.ln) = -1; }

    break;

  case 193:

    { (yyval.ln) = 0; }

    break;

  case 194:

    { (yyval.ln) = 0x08000000; }

    break;

  case 196:

    { FlagMode = 1; }

    break;

  case 201:

    { FlagMode = 1; }

    break;

  case 203:

    { FlagMode = 2; }

    break;

  case 205:

    { ((NormalMask *)msk)->fFileAttach = (FlagMode == 2) ? 2 : 1; }

    break;

  case 206:

    { /* Check MaxAttach size*/
               if (CheckMaskMode((char *)"A") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxAttachSize == 0 && MaxAttachSize == 0) {
                  yyerror("Not one (global or local) MaxAttachSize is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxAttach = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 207:

    { /* Check MaxMsg size*/
               if (CheckMaskMode((char *)"M") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxMsgSize == 0 && MaxMsgSize == 0) {
                  yyerror("Not one (global or local) MaxMsgSize is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxMsg = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 208:

    { ((NormalMask *)msk)->fARQ = (FlagMode == 2) ? 2 : 1; }

    break;

  case 209:

    { ((NormalMask *)msk)->fCrash = (FlagMode == 2) ? 2 : 1; }

    break;

  case 210:

    { ((NormalMask *)msk)->fDIR = (FlagMode == 2) ? 2 : 1; }

    break;

  case 211:

    { /* Empty message */
               if (CheckMaskMode((char *)"e") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fEmpty = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 212:

    { /* Check echomail */
               if (CheckMaskMode((char *)"E") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fEchomail = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 213:

    { ((NormalMask *)msk)->fFileRequest = (FlagMode == 2) ? 2 : 1; }

    break;

  case 214:

    { /* Check age */
               if (CheckMaskMode((char *)"g") != 0) {
                  YYABORT;
               }
               if (((NormalMask *)msk)->sd->_MaxAge == 0 && MaxAge == 0) {
                  yyerror("Not one (global or local) MaxAge is not defined.");
                  YYABORT;
               }
               ((NormalMask *)msk)->fMaxAge = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 215:

    { ((NormalMask *)msk)->fHold = (FlagMode == 2) ? 2 : 1; }

    break;

  case 216:

    { ((NormalMask *)msk)->fTransit = (FlagMode == 2) ? 2 : 1; }

    break;

  case 217:

    { ((NormalMask *)msk)->fKFS = (FlagMode == 2) ? 2 : 1; }

    break;

  case 218:

    { ((NormalMask *)msk)->fKillSend = (FlagMode == 2) ? 2 : 1; }

    break;

  case 219:

    { ((NormalMask *)msk)->fLocal = (FlagMode == 2) ? 2 : 1; }

    break;

  case 220:

    { ((NormalMask *)msk)->fLok = (FlagMode == 2) ? 2 : 1; }

    break;

  case 221:

    { ((NormalMask *)msk)->fIMM = (FlagMode == 2) ? 2 : 1; }

    break;

  case 222:

    { ((NormalMask *)msk)->fCFM = (FlagMode == 2) ? 2 : 1; }

    break;

  case 223:

    { ((NormalMask *)msk)->fOrphan = (FlagMode == 2) ? 2 : 1; }

    break;

  case 224:

    { ((NormalMask *)msk)->fPrivate = (FlagMode == 2) ? 2 : 1; }

    break;

  case 225:

    { ((NormalMask *)msk)->fRRQ = (FlagMode == 2) ? 2 : 1; }

    break;

  case 226:

    { ((NormalMask *)msk)->fReceived = (FlagMode == 2) ? 2 : 1; }

    break;

  case 227:

    { ((NormalMask *)msk)->fSend = (FlagMode == 2) ? 2 : 1; }

    break;

  case 228:

    { ((NormalMask *)msk)->fAS = (FlagMode == 2) ? 2 : 1; }

    break;

  case 229:

    { ((NormalMask *)msk)->fTFS = (FlagMode == 2) ? 2 : 1; }

    break;

  case 230:

    { ((NormalMask *)msk)->fFURQ = (FlagMode == 2) ? 2 : 1; }

    break;

  case 231:

    { ((NormalMask *)msk)->fScanned = (FlagMode == 2) ? 2 : 1; }

    break;

  case 232:

    { /* Check existing attach */
               if (CheckMaskMode((char *)"x") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fAttExists = (FlagMode == 2) ? 2 : 1;
            }

    break;

  case 233:

    { ((NormalMask *)msk)->fIRR = (FlagMode == 2) ? 2 : 1; }

    break;

  case 234:

    {
               if (CheckMaskMode((char *)"loop flag") != 0) {
                  YYABORT;
               }
               ((NormalMask *)msk)->fLoop = (FlagMode == 2) ? 2 : 1;
               if (((NormalMask *)msk)->Loops != (unsigned int)-1) {
                  yyerror("Only one loop count should be in mask.");
                  YYABORT;
               }
               ((NormalMask *)msk)->Loops = (yyvsp[0].ln);
            }

    break;

  case 235:

    {
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(KludgeMask *)msk);
            }

    break;

  case 236:

    {
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(KludgeMask *)msk);
            }

    break;

  case 237:

    {
               msk->_Type = MASK_ADD;
               AddReadyMask(*(KludgeMask *)msk);
            }

    break;

  case 238:

    {
               msk = new KludgeMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }

    break;

  case 239:

    {
               ((KludgeMask *)msk)-> _KludgeName = strdup((yyvsp[-2].ch));
               ((KludgeMask *)msk)-> _KludgeBody = strdup((yyvsp[-1].ch));
               ((KludgeMask *)msk)-> _Times = (yyvsp[0].ln);
            }

    break;

  case 240:

    {
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(BodyMask *)msk);
            }

    break;

  case 241:

    {
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(BodyMask *)msk);
            }

    break;

  case 242:

    {
               msk->_Type = MASK_ADD;
               AddReadyMask(*(BodyMask *)msk);
            }

    break;

  case 243:

    {
               msk = new BodyMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }

    break;

  case 244:

    {
               ((BodyMask *)msk)-> _Body = strdup((yyvsp[-2].ch));
               ((BodyMask *)msk)-> _Lines = (yyvsp[-1].ln);
               ((BodyMask *)msk)-> _Bytes = (yyvsp[0].ln);
            }

    break;

  case 245:

    {
               msk->_Type = MASK_NORMAL;
               AddReadyMask(*(ScriptMask *)msk);
            }

    break;

  case 246:

    {
               msk->_Type = MASK_SKIP;
               AddReadyMask(*(ScriptMask *)msk);
            }

    break;

  case 247:

    {
               msk->_Type = MASK_ADD;
               AddReadyMask(*(ScriptMask *)msk);
            }

    break;

  case 248:

    {
               msk = new ScriptMask();
               CheckMem((char *)msk);
               msk->_Type = MASK_NORMAL;
               if (PrepareMask(*msk) != 0) {
                  YYABORT;
               }
            }

    break;

  case 249:

    {
               ((ScriptMask *)msk)->_ScriptName = strdup((yyvsp[0].ch));
               if (!ScriptWordExists((yyvsp[0].ch))) {
                  yyerror("Subroutine not found in scripts.");
                  YYABORT;
               }
            }

    break;

  case 250:

    {
          if (PrevMask == 0) {
             yyerror("Action without Mask.");
             YYABORT;
          }
          wsd = ScanDirs.GetLast();
          PrevMask = 1;
          act = new Action();
          act->sd = wsd;
          act->Before = BeforeRoute;
          act->After = AfterRoute;
         _TTimes = &act->_Times;
       }

    break;

  case 251:

    {
          LastDo->AddAction(*act);
       }

    break;

  case 256:

    { act->_Act = ACT_DELETE; }

    break;

  case 260:

    { act->_Act = ACT_IGNORE; }

    break;

  case 272:

    { act->_Act = ACT_DELETEATTACH; }

    break;

  case 284:

    {
            act->_Act = ACT_ADDNOTE;
            act->_Tpl = new Template();
            if (!act->_Tpl->Set((yyvsp[0].ch))) {
               yyerror("Template file is not accesible.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               YYABORT;
            }
            act->_Tpl->sd = ScanDirs.GetLast();
         }

    break;

  case 285:

    {
            act->_Act = ACT_MOVE;
            act->_Base = MakeBase((yyvsp[0].ch));
            if (act->_Base == NULL) {
               YYABORT;
            }
            if (!act->_Base->Set((yyvsp[0].ch),BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
         }

    break;

  case 286:

    {
            act->_Act = ACT_COPY;
            act->_Base = MakeBase((yyvsp[0].ch));
            if (act->_Base == NULL) {
               YYABORT;
            }
            if (!act->_Base->Set((yyvsp[0].ch),BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
         }

    break;

  case 287:

    {
              MaskMode = 1;
              act->_Act = ACT_REWRITE;
           }

    break;

  case 288:

    {
              act->_Mask = msk;
           }

    break;

  case 289:

    {
            act->_Act = ACT_DISPLAY;
            act->_TplName = strdup((yyvsp[0].ch));
         }

    break;

  case 290:

    {
            act->_Act = ACT_SCRIPT;
            if (!ScriptWordExists((yyvsp[0].ch))) {
               yyerror("Script function not found.");
               YYABORT;
            }
            act->_TplName = strdup((yyvsp[0].ch));
         }

    break;

  case 291:

    {
            act->_Act = ACT_FLAG;
            act->_OutDir = strdup((yyvsp[0].ch));
         }

    break;

  case 292:

    { (yyval.ch) = (yyvsp[0].ch); }

    break;

  case 293:

    {
            act->_Act = ACT_DELFILE;
            act->_OutDir = strdup((yyvsp[0].ch));
         }

    break;

  case 294:

    {
            MaskMode = 1;
            act->_Act = ACT_NEWMSG;
         }

    break;

  case 295:

    {
            act->_Tpl = new Template();
            if (!act->_Tpl->Set((yyvsp[-2].ch))) {
               yyerror("Template file is not accesible.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               YYABORT;
            }
            act->_Tpl->sd =  ScanDirs.GetLast();
            act->_Base = MakeBase((yyvsp[-1].ch));
            if (act->_Base == NULL || !act->_Base->Set((yyvsp[-1].ch),BASE_OUT)) {
               yyerror("Invalid message base name.");
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            if (!act->_Base->CheckOut()) {
               delete act->_Tpl;
               act->_Tpl = NULL;
               delete msk;
               msk = NULL;
               delete act->_Base;
               act->_Base = NULL;
               YYABORT;
            }
            act->_Base->Rewind();
            act->_Mask = msk;

         }

    break;

  case 296:

    {
              act->_Act = ACT_WRITEFILE;
              act->_Tpl = new Template();
              if (!act->_Tpl->Set((yyvsp[-1].ch))) {
                 yyerror("Template file is not accesible.");
                 delete act->_Tpl;
                 act->_Tpl = NULL;
                 YYABORT;
              }
              act->_Tpl->sd =  ScanDirs.GetLast();
              act->_OutDir = strdup((yyvsp[0].ch));
           }

    break;

  case 297:

    {
                   act->_Act = ACT_ADDFILE;
                   act->_Tpl = new Template();
                   if (!act->_Tpl->Set((yyvsp[-1].ch))) {
                      yyerror("Template file is not accesible.");
                      delete act->_Tpl;
                      act->_Tpl = NULL;
                      YYABORT;
                   }
                   act->_Tpl->sd =  ScanDirs.GetLast();
                   act->_OutDir = strdup((yyvsp[0].ch));
              }

    break;

  case 298:

    {
           act->_Act = ACT_CALL;
           act->_Tpl = new Template();
           if (!act->_Tpl->Set((yyvsp[-2].ch))) {
              yyerror("Template file is not accesible.");
              delete act->_Tpl;
              act->_Tpl = NULL;
              YYABORT;
           }
           act->_Tpl->sd =  ScanDirs.GetLast();
           act->_OutDir = strdup((yyvsp[-1].ch));
           act->_TplName = strdup((yyvsp[0].ch));
      }

    break;

  case 299:

    {
           act->_Act = ACT_CALL;
           act->_TplName = strdup((yyvsp[0].ch));
      }

    break;

  case 300:

    { cffa.Clean(); }

    break;

  case 301:

    {
          act->_Act = ACT_ROUTE;
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action Route in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = (yyvsp[-2].pktmode);
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid routing address.");
             YYABORT;
          }
       }

    break;

  case 302:

    { cffa.Clean(); }

    break;

  case 303:

    {
          act->_Act = ACT_ROUTEFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: RouteFilebox.");
	   YYABORT;
	  }
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action RouteFilebox in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = (yyvsp[-2].pktmode);
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid routing address.");
             YYABORT;
          }
       }

    break;

  case 304:

    { cffa.Clean(); }

    break;

  case 305:

    {
          act->_Act = ACT_ROUTEHUB;
          if (act->sd == act->Before|| act->sd == act->After) {
             yyerror("You can not use the Action RouteHub in 'ScanDir: @AfterRoute|@BeforeRoute'");
             YYABORT;
          }
          act->_Flav = (yyvsp[-1].pktmode);
       }

    break;

  case 306:

    { cffa.Clean(); }

    break;

  case 307:

    {
          act->_Act = ACT_COPYATTACHFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: CopyAttachFilebox.");
	   YYABORT;
	  }
          act->_Flav = (yyvsp[-2].pktmode);
          act->_f = cffa;
       }

    break;

  case 308:

    { cffa.Clean(); }

    break;

  case 309:

    {
          act->_Act = ACT_MOVEATTACHFBOX;
	  if (FileBoxDir == NULL)
	  {
	   yyerror("You must define FileBoxDir before using Action: MoveAttachFilebox.");
	   YYABORT;
	  }
          act->_Flav = (yyvsp[-2].pktmode);
          act->_f = cffa;
       }

    break;

  case 310:

    { (yyval.pktmode) = F_HOLD; }

    break;

  case 311:

    { (yyval.pktmode) = F_CRASH; }

    break;

  case 312:

    { (yyval.pktmode) = F_DIRECT; }

    break;

  case 313:

    { (yyval.pktmode) = F_NORMAL; }

    break;

  case 314:

    { (yyval.pktmode) = F_IMMEDIATE; }

    break;

  case 315:

    { cffa.Clean(); }

    break;

  case 316:

    {
          act->_Act = ACT_POLL;
          act->_Flav = (yyvsp[-2].pktmode);
          act->_f = cffa;
          if (act->_f.Point() & FA_NOTDEF) {
             act->_f.Point(0);
          }
          if (!act->_f.RouValid()) {
             yyerror("Invalid poll address.");
             YYABORT;
          }
       }

    break;

  case 317:

    {
               act->_Act = ACT_CHANGEPATH;
               if (strlen((yyvsp[0].ch)) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup((yyvsp[0].ch));
            }

    break;

  case 318:

    {
               act->_Act = ACT_TOLOWERPATH;
            }

    break;

  case 319:

    {
               act->_Act = ACT_TOUPPERPATH;
            }

    break;

  case 320:

    {
               act->_Act = ACT_ADDKLUDGE;
	       act->_OutDir = strdup((yyvsp[-1].ch));
	       act->_TplName = strdup((yyvsp[0].ch));
            }

    break;

  case 321:

    {
               act->_Act = ACT_MOVEATTACH;
               if (!DirExists((yyvsp[0].ch))) {
	         Log.Level(LOGE) << "Target directory '" << (yyvsp[0].ch) << "' not found." << EOL;
               }
               if (strlen((yyvsp[0].ch)) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup((yyvsp[0].ch));
            }

    break;

  case 322:

    {
               act->_Act = ACT_COPYATTACH;
               if (!DirExists((yyvsp[0].ch))) {
	         Log.Level(LOGE) << "Target directory '" << (yyvsp[0].ch) << "' not found." << EOL;
               }
               if (strlen((yyvsp[0].ch)) > 72) {
                  yyerror("New path too long");
                  YYABORT;
               }
               act->_OutDir = strdup((yyvsp[0].ch));
            }

    break;

  case 323:

    {
               act->_Act = ACT_SPLIT;
               if ((yyvsp[0].ln) < 1 || (yyvsp[0].ln) > 65535) {
                  yyerror("Parameter 'Lines' should be positive integer between 1 and 65535");
                  YYABORT;
               }
               act->_Lines = (yyvsp[0].ln);
            }

    break;

  case 324:

    {
               FILE *fp = NULL;
               char buf[512],*p,*q;
               int in,on,count;
               int line = 0;

                  act->_Act = ACT_RECODE;
                  fp = fopen((yyvsp[0].ch),"r");
                  if (fp == NULL) {
                     yyerror("Unable to open file");
                     YYABORT;
                  }
                  act->_TplName = (char *)malloc(256);
                  CheckMem(act->_TplName);
                  for (count = 0; count < 256; count++) act->_TplName[count] = (char) count;
                  count = 0;
                  line = 0;

                  while (fgets((char*)buf,sizeof(buf),fp)) {
                     line++;
                     p = strtok((char*)buf," \t\n#");
                     q = strtok(NULL," \t\n#");
                     if (p != NULL && q != NULL) {
                        in = ctoi((char *)p);
                        if (in > 255) {
                           sprintf(buf, "%s: Error in line %d.", (yyvsp[0].ch), line);
                           yyerror(buf);
                           fclose(fp);
                           free(act->_TplName);
                           YYABORT;
                        }
                        on=ctoi((char *)q);
                        if (in != 0 && on != 0) {
                           if (count++ < 256 ) {
                              act->_TplName[in]=on;
                           } else {
                              sprintf(buf,"Char map table \"%s\" is big",(yyvsp[0].ch));
                              yyerror(buf);
                              fclose(fp);
                              free(act->_TplName);
                              YYABORT;
                           }
                        }
                     } /* if */
                  } /* While */
                  fclose(fp);
            }

    break;

  case 326:

    { cffa.Zone(cffa.Zone() | FA_NOTMASK); }

    break;

  case 329:

    {
                  cffa.Zone(FA_ANYMASK);
                  cffa.Net(FA_ANYMASK);
                  cffa.Node(FA_ANYMASK);
                  cffa.Point(FA_ANYMASK);
               }

    break;

  case 330:

    {
                  cffa.Zone(FA_LSTMASK);
                  cffa.Net(FA_LSTMASK);
                  cffa.Node(FA_LSTMASK);
                  cffa.Point(FA_LSTMASK);
               }

    break;

  case 331:

    {
                  cffa.Zone(FA_HOLDMASK);
                  cffa.Net(FA_HOLDMASK);
                  cffa.Node(FA_HOLDMASK);
                  cffa.Point(FA_HOLDMASK);
               }

    break;

  case 332:

    {
                  cffa.Zone(FA_HUBMASK);
                  cffa.Net(FA_HUBMASK);
                  cffa.Node(FA_HUBMASK);
                  cffa.Point(FA_HUBMASK);
               }

    break;

  case 333:

    {
                  cffa.Zone(FA_DOWNMASK);
                  cffa.Net(FA_DOWNMASK);
                  cffa.Node(FA_DOWNMASK);
                  cffa.Point(FA_DOWNMASK);
               }

    break;

  case 334:

    {
                  cffa.Zone(FA_PVTMASK);
                  cffa.Net(FA_PVTMASK);
                  cffa.Node(FA_PVTMASK);
                  cffa.Point(FA_PVTMASK);
               }

    break;

  case 335:

    {
                  cffa.Zone(FA_OURMASK);
                  cffa.Net(FA_OURMASK);
                  cffa.Node(FA_OURMASK);
                  cffa.Point(FA_OURMASK);
               }

    break;

  case 336:

    {
                  cffa.Zone(FA_FROMMASK);
                  cffa.Net(FA_FROMMASK);
                  cffa.Node(FA_FROMMASK);
                  cffa.Point(FA_FROMMASK);
               }

    break;

  case 337:

    {
                  cffa.Zone(FA_TOMASK);
                  cffa.Net(FA_TOMASK);
                  cffa.Node(FA_TOMASK);
                  cffa.Point(FA_TOMASK);
               }

    break;

  case 338:

    {
                  if ((yyvsp[0].ln) != 0) {
                     yyerror("parse error");
                     YYABORT;
                  }
                  cffa.Zone(FA_TOMASK);
                  cffa.Net(FA_TOMASK);
                  cffa.Node(FA_TOMASK);
                  cffa.Point(0);
               }

    break;

  case 340:

    { cffa.Point((yyvsp[0].ln)); }

    break;

  case 341:

    { cffa.Point(FA_SUBMASK); }

    break;

  case 342:

    {
               cffa.Zone((yyvsp[-4].ln));
               cffa.Net((yyvsp[-2].ln));
               cffa.Node((yyvsp[0].ln));
               cffa.Point(0);
            }

    break;

  case 343:

    { (yyval.ln) = (yyvsp[0].ln); }

    break;

  case 344:

    { (yyval.ln) = FA_ANYMASK; }

    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}




