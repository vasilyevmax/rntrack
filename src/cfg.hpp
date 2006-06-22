#ifndef BISON_______SRC_CFG_HPP
# define BISON_______SRC_CFG_HPP

#ifndef YYSTYPE
typedef union {
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
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	_LOGFILE	257
# define	_LOGLEVEL	258
# define	_NODELIST	259
# define	_INDEXFILE	260
# define	_NODELISTPATH	261
# define	_ADDRESS	262
# define	_SYSOPNAME	263
# define	_USEOWNZONE	264
# define	_FORCEINTL	265
# define	_LOOPSTR	266
# define	_SCANDIR	267
# define	_MASK	268
# define	_SMASK	269
# define	_PMASK	270
# define	_BODYMASK	271
# define	_SBODYMASK	272
# define	_PBODYMASK	273
# define	_KLUDGEMASK	274
# define	_SKLUDGEMASK	275
# define	_PKLUDGEMASK	276
# define	_ACTION	277
# define	_MAXAGE	278
# define	_BADMESSAGES	279
# define	_NOLOGIGNORE	280
# define	_AKA	281
# define	_SKIPHIDDENFILES	282
# define	_FILEINBOUND	283
# define	_OUTBOUND	284
# define	_ADDTONULLPKT	285
# define	_TEMPMAIL	286
# define	_TRAFFICLOG	287
# define	_PASSWORD	288
# define	_UTC	289
# define	_ORIGIN	290
# define	_TEARLINE	291
# define	_INCLUDE	292
# define	_APKTDIR	293
# define	_CHECKPOINTS	294
# define	_SETVIAALWAYS	295
# define	_FRESH	296
# define	_CREATEMISSINGBASE	297
# define	_USENEWVIA	298
# define	_SCRIPTMASK	299
# define	_SSCRIPTMASK	300
# define	_PSCRIPTMASK	301
# define	_MAXATTACHSIZE	302
# define	_SEMAPHORE	303
# define	_SCRIPTFILE	304
# define	_USEASO	305
# define	_USEBRAKE	306
# define	_FILEBOXDIR	307
# define	_KILLROUTEDMESSAGE	308
# define	_IGNOREBSY	309
# define	_AFTERSCRIPT	310
# define	_BEFORESCRIPT	311
# define	_AGEFROMVIA	312
# define	_MAXNODELISTAGE	313
# define	_USEFILEBOXES	314
# define	_FILEBOXTYPE	315
# define	_LONG	316
# define	_TMLONG	317
# define	_TMSHORT	318
# define	_BRAKE	319
# define	_SOFTCHECKINNODELIST	320
# define	_BADPACKETS	321
# define	_IGNOREATTACHPATH	322
# define	_MAXPKTSIZE	323
# define	_MAXMSGSIZE	324
# define	_TIMESTAMPFILE	325
# define	_DOMAIN	326
# define	_FILEBOX	327
# define	_TRAFFICLOGTEMPLATE	328
# define	_STRIPPATHINPKT	329
# define	_CRLF	330
# define	_SKIP	331
# define	_DELETE	332
# define	_EXIT	333
# define	_MOVE	334
# define	__EOF	335
# define	_STRING	336
# define	_BEFOREROUTE	337
# define	_AFTERROUTE	338
# define	_DIGIT_	339
# define	_RENUMBER	340
# define	_UNPACK	341
# define	_DAILY	342
# define	_WEEKLY	343
# define	_FLAG	344
# define	_NEVER	345
# define	_HARD	346
# define	_SOFT	347
# define	_ALWAYS	348
# define	_ADDNOTE	349
# define	_COPY	350
# define	_REWRITE	351
# define	_IGNORE	352
# define	_DISPLAY	353
# define	_DELFILE	354
# define	_NEWMSG	355
# define	_WRITEFILE	356
# define	_APPENDTOFILE	357
# define	_CALL	358
# define	_ROUTE	359
# define	_ROUTEFBOX	360
# define	_ROUTEHUB	361
# define	_POLL	362
# define	_DELETEATTACH	363
# define	_CHANGEPATH	364
# define	_MOVEATTACH	365
# define	_ASCRIPT	366
# define	_TOLOWERPATH	367
# define	_TOUPPERPATH	368
# define	_COPYATTACHFBOX	369
# define	_MOVEATTACHFBOX	370
# define	_COPYATTACH	371
# define	_SPLIT	372
# define	_RECODE	373
# define	_ADDKLUDGE	374
# define	_HOLD	375
# define	_CRASH	376
# define	_DIRECT	377
# define	_NORMAL	378
# define	_IMMEDIATE	379
# define	LEXERR	380


extern YYSTYPE yylval;

#endif /* not BISON_______SRC_CFG_HPP */
