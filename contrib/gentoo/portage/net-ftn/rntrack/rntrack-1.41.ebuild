# Copyright 1999-2010 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="7"

inherit autotools

DESCRIPTION="A FTN Messages tracker"
SRC_URI="mirror://sourceforge/ftrack-as/${V}/${PN}-$(ver_rs 1 _)-src.tar.bz2"
HOMEPAGE="http://ftrack-as.sourceforge.net/"

SLOT="0"
LICENSE="GPL"
KEYWORDS="~amd64 x86"
IUSE="-perl -perl_fix -log_pid -syslog_log_format"

DEPEND="perl? ( dev-lang/perl )"
RDEPEND="${DEPEND}"

AT_M4DIR="MakeFiles"

src_prepare() {
	eautoreconf || die "eautoreconf failed"

	# apply patch for perl support if need
	use perl_fix || einfo "Please specify perl_fix flag if your build with perl support is unsuccessfull"
	use perl_fix && (eapply -p0 ${FILESDIR}/perl.patch || die "epply failed")

	eapply_user

	# prevent to strip while linking
	sed -e "s:-s -L:-L:" -i MakeFiles/linux/Makefile
}

src_compile() {
	cd MakeFiles/linux
	emake $( use perl && echo "ENABLE_SCRIPTS=1" || echo "ENABLE_SCRIPTS=0" ) \
		$( use log_pid && echo "ENABLE_LOG_PID=1" || echo "ENABLE_LOG_PID=0" ) \
		$( use syslog_log_format && echo "ENABLE_SYSLOG_LOG_FORMAT=1" || echo "ENABLE_SYSLOG_LOG_FORMAT=0" ) \
		|| die "emake failed"
}

src_install() {
	dobin MakeFiles/linux/rntrack
	doman doc/rntrack.1
	dodoc doc/MANUAL* doc/FAQ*
	insinto /etc/ftn
	doins samples/rntrack.cfg
	dodir /etc/ftn/rntrack.samples
	insinto /etc/ftn/rntrack.samples
	doins samples/*
}
