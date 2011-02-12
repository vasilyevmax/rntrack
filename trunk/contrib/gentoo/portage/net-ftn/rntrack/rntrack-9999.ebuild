# Copyright 1999-2010 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="2"

inherit eutils autotools flag-o-matic subversion

DESCRIPTION="A FTN Messages tracker"
HOMEPAGE="http://ftrack-as.sourceforge.net/"
ESVN_REPO_URI="https://ftrack-as.svn.sourceforge.net/svnroot/ftrack-as/trunk"

SLOT="0"
LICENSE="GPL"
KEYWORDS="~amd64 ~x86"
IUSE="-perl -log_pid -syslog_log_format"

DEPEND="sys-devel/automake
	perl? ( dev-lang/perl )"
RDEPEND="${DEPEND}"
S=${WORKDIR}/${PN}

AT_M4DIR="MakeFiles"

src_unpack() {
	subversion_src_unpack
}

src_prepare() {
	eautoreconf || die "eautoreconf failed"
	
	# prevent to strip while linking
	sed -e "s:-s -L:-L:" -i MakeFiles/linux/Makefile
}

#src_configure() {
#	econf \
#		$( use_enable perl ) \
#		$( use_enable log_pid ) \
#		$( use_enable syslog_log_format ) \
#		|| die "econf failed"
#}

src_compile() {
	cd MakeFiles/linux
	emake $( useq perl && echo "ENABLE_SCRIPTS=1" || echo "ENABLE_SCRIPTS=0" ) \
		$( useq log_pid && echo "ENABLE_LOG_PID=1" || echo "ENABLE_LOG_PID=0" ) \
		$( useq syslog_log_format && echo "ENABLE_SYSLOG_LOG_FORMAT=1" || echo "ENABLE_SYSLOG_LOG_FORMAT=0" ) \
		|| die "emake failed"
}

src_install () {
	dobin MakeFiles/linux/rntrack
	doman doc/rntrack.1
	dodoc doc/MANUAL* doc/FAQ*
	insinto /etc/ftn
	doins samples/rntrack.cfg
	dodir /etc/ftn/rntrack.samples
	insinto /etc/ftn/rntrack.samples
	doins samples/*
}
