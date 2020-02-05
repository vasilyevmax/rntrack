# New ports collection makefile for:    rntrack
# Date created:		Fri Jan 14 00:57:28 MSK 2005
# Whom:			Alex Soukhotine <ph0enix@users.sourceforge.net>
#
# $FreeBSD$
#

PORTNAME=	rntrack
PORTVERSION=	1.12
CATEGORIES=	mail
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE}
MASTER_SITE_SUBDIR=	ftrack-as
DISTNAME=	${PORTNAME}-${PORTVERSION}

MAINTAINER=	ph0enix@users.sourceforge.net
COMMENT=	FTN Messages tracker

USE_BZIP2= 	yes
USE_REINPLACE=	yes
ALL_TARGET=	${PORTNAME}
MAKEFILE=	${WRKSRC}/MakeFiles/FreeBSD/Makefile
MAKE_ENV=	CONFIG\=${PREFIX}/etc/rntrack/rntrack.cfg
MAN1=		rntrack.1

PORTDOCS=	FAQ FAQ.ru README README.ru report.err report.err.ru

pre-configure:
	${CP} ${WRKSRC}/MakeFiles/FreeBSD/Makefile ${WRKSRC}

pre-patch:
	${REINPLACE_CMD} -e "s@../../@@g" ${WRKSRC}/MakeFiles/FreeBSD/Makefile

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/rntrack ${PREFIX}/sbin
	${MKDIR} ${PREFIX}/etc/rntrack/tpl
	${INSTALL_DATA} ${WRKSRC}/samples/node.cfg ${PREFIX}/etc/rntrack/rntrack.cfg-dist
	${INSTALL_DATA} ${WRKSRC}/samples/test.pl ${PREFIX}/etc/rntrack
	${INSTALL_DATA} ${WRKSRC}/doc/rntrack.1 ${PREFIX}/man/man1
	${INSTALL_DATA} ${WRKSRC}/samples/tpl/* ${PREFIX}/etc/rntrack/tpl
	${MKDIR} ${PREFIX}/etc/rntrack/tbl
.for f in alt2koi.tbl koi2alt.tbl
	${INSTALL_DATA} ${WRKSRC}/samples/${f} ${PREFIX}/etc/rntrack/tbl
.endfor
.if !defined(NOPORTDOCS)
	${MKDIR} ${DOCSDIR}
.for f in ${PORTDOCS}
	${INSTALL_DATA} ${WRKSRC}/doc/${f} ${DOCSDIR}
.endfor
.endif

.include <bsd.port.mk>
