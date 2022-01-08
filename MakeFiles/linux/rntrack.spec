Name: rntrack
Version: 2.2.0
Release: 1%{?dist}
Group: Applications/FTN
Summary: RNtrack - a FTN netmail tracker
Summary(ru): RNtrack - трекер нетмейла в сетях типа "Фидонет"
URL: https://sourceforge.net/projects/ftrack-as/
License: GPLv2
BuildRequires: perl(ExtUtils::Embed)
Requires: perl >= 5.8.8
Source: %{name}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root

%description
RNtrack - a FTN netmail tracker

%description -l ru
RNtrack - трекер нетмейла в сетях типа "Фидонет"

%prep
%setup -q -n %{name}

%build
cd MakeFiles/linux
%make_build CONFIG="~/fido/etc/rntrack/rntrack.conf" DEBUG=1 ENABLE_SCRIPTS=1

%install
cd MakeFiles/linux
%make_install
chmod -R a+rX,u+w,go-w %{buildroot}

%files
%defattr(-,root,root)
%{_bindir}/*
%{_mandir}/man1/*
