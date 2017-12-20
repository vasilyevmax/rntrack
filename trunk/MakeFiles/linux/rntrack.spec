Name: rntrack
Version: 1.33
Release: 1
Group: Applications/FTN
Summary: RNtrack - a FTN netmail tracker
Summary(ru): RNtrack - трекер нетмейла в сетях типа "Фидонет"
URL: https://sourceforge.net/projects/ftrack-as/
License: GPL
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
make CONFIG="~/fido/etc/rntrack/rntrack.cfg"

%install
rm -rf %{buildroot}
cd MakeFiles/linux
export DESTDIR=%{buildroot}
%makeinstall
chmod -R a+rX,u+w,go-w %{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root)
%{_bindir}/*
%{_mandir}/man1/*
