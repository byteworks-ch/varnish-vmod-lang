Summary: Lang VMOD for Varnish
Name: vmod-lang
Version: 1.0
Release: 1%{?dist}
License: BSD
Group: System Environment/Daemons
Source0: libvmod-lang.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: varnish >= 4.0.2
BuildRequires: make
BuildRequires: python-docutils
BuildRequires: varnish >= 4.0.2
BuildRequires: varnish-libs-devel >= 4.0.2

%description
A varnish vmod for language detection based on the accept language header


%prep
%setup -n libvmod-lang-trunk


%build
# this assumes that VARNISHSRC is defined on the rpmbuild command line, like this:
# rpmbuild -bb --define 'VARNISHSRC /home/user/rpmbuild/BUILD/varnish-3.0.3' redhat/*spec
./configure VARNISHSRC=%{VARNISHSRC} VMODDIR="$(PKG_CONFIG_PATH=%{VARNISHSRC} pkg-config --variable=vmoddir varnishapi)" --prefix=/usr/ --docdir='${datarootdir}/doc/%{name}'
make
make check


%install
make install DESTDIR=%{buildroot}


%clean
[ %{buildroot} != "/" ] && %{__rm} -rf %{buildroot}


%files
%defattr(-,root,root,-)
%{_libdir}/varnis*/vmods/
%doc /usr/share/doc/lib%{name}/*
%{_mandir}/man?/*


%changelog
* Fri May 09 2014 Michael Bischof <mb@byteworks.ch> - 1.0-1
- Initial version.

