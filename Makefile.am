# RNTrack -*Automake*-
# $Id$
AUTOMAKE_OPTIONS = foreign
SUBDIRS = src
DIST_SUBDIRS = doc samples
EXTRA_DIST = AUTHORS BUG-REPORTING COPYING ChangeLog INSTALL KnownBugs README TODO samples

man_MANS = doc/rntrack.1
data_DATA = doc/FAQ doc/FAQ.ru doc/MANUAL doc/MANUAL.ru doc/report.err doc/report.err.ru

dist-hook:
	find $(distdir)/samples $(distdir)/doc -name .svn -exec rm -r '{}' ';'
