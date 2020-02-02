# Copyright 1999-2010 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI="4"

inherit eutils subversion

DESCRIPTION="An FTN Messages tracker"
HOMEPAGE="http://ftrack-as.sourceforge.net/"
ESVN_REPO_URI="http://svn.code.sf.net/p/ftrack-as/code/trunk"

SLOT="0"
LICENSE="GPL"
KEYWORDS="~amd64 ~x86"
IUSE="-perl -perl_fix -old_config_path -log_pid -syslog_log_format"

DEPEND="sys-devel/automake
	perl? ( dev-lang/perl )"
RDEPEND="${DEPEND}"
S=${WORKDIR}/${PN}

AT_M4DIR="MakeFiles"

src_unpack() {
	subversion_src_unpack
}

src_prepare() {
	use old_config_path \
		&& einfo "v1.x config file location is used: /etc/ftn/rntrack.cfg" \
		|| einfo "Please specify old_config_path use flag if you want to keep v1.x config file location: /etc/ftn/rntrack.cfg instead of ~/fido/etc/rntrack.conf"

	# apply patch for perl support if needed
	use perl_fix || einfo "Please specify perl_fix use flag if your build with perl support is unsuccessfull"
	use perl_fix && (epatch ${FILESDIR}/perl2.patch.gz || die "epatch failed")
	
	# prevent to strip while linking
	sed -e "s:-s -L:-L:" -i MakeFiles/linux/Makefile
}

src_compile() {
	cd MakeFiles/linux
	emake $( useq perl && echo "ENABLE_SCRIPTS=1" || echo "ENABLE_SCRIPTS=0" ) \
		$( useq log_pid && echo "ENABLE_LOG_PID=1" || echo "ENABLE_LOG_PID=0" ) \
		$( useq old_config_path && echo "CONFIG=/etc/ftn/rntrack.cfg" ) \
		$( useq syslog_log_format && echo "ENABLE_SYSLOG_LOG_FORMAT=1" || echo "ENABLE_SYSLOG_LOG_FORMAT=0" ) \
		|| die "emake failed"
}

src_install() {
	dobin MakeFiles/linux/rntrack
	doman doc/rntrack.1
	dodoc doc/FAQ* doc/report.err* doc/rntrack_*
	insinto /etc/ftn
	doins samples/rntrack.cfg
	dodir /etc/ftn/rntrack.samples
	insinto /etc/ftn/rntrack.samples
	doins samples/*
}
