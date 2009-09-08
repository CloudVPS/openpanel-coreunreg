%define version 0.9.0

%define libpath /usr/lib
%ifarch x86_64
  %define libpath /usr/lib64
%endif

Summary: coreunreg
Name: openpanel-coreunreg
Version: %version
Release: 1
License: GPLv2
Group: Development
Source: http://packages.openpanel.com/archive/openpanel-coreunreg-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot
Requires: openpanel-core >= 0.8.0
Requires: libgrace

%description
coreunreg
development tool for manipulating the opencore module database
%prep
%setup -q -n openpanel-coreunreg-%version

%build
BUILD_ROOT=$RPM_BUILD_ROOT
./configure
make

%install
BUILD_ROOT=$RPM_BUILD_ROOT
rm -rf ${BUILD_ROOT}
mkdir -p ${BUILD_ROOT}/usr/bin
install -m 755 coreunreg ${BUILD_ROOT}/usr/bin

%post

%files
%defattr(-,root,root)
/
