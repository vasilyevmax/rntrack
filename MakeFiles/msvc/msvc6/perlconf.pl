# $Id:$
# Embedded Perl build autoconfiguration script

$file = $ARGV[0] || die;

use Config;
($perl_incl = $Config::Config{libpth})  =~ s/^\"(.*)\"$/$1/;
($perl_lib  = $Config::Config{libperl}) =~ s/^\"(.*)\"$/$1/;

$perl_version="$]";
($perl_major,$perl_minor) = split /\./, $perl_version;
$perl_version =~ s/\.//;

open(FILE, ">$file") || die;
print FILE <<EOT;
!if !defined(CPP_PERL)
CPP_PERL= -I \$(PERL_BASEDIR)$perl_incl\\CORE\\ -D__PERL_VERSION__=$perl_version -D__PERL_MAJOR__=$perl_major -D__PERL_MINOR__=$perl_minor
!endif
!if !defined(LINK32_PERL)
LINK32_PERL=\$(PERL_BASEDIR)$perl_incl\\CORE\\$perl_lib
!endif
EOT
close(FILE);
