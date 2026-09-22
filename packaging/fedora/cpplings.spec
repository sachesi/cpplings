Name:           cpplings
# The release workflow sets Version to the tag it builds.
Version:        0.1.0
Release:        1%{?dist}
Summary:        Small exercises to get you used to reading and writing modern C++

License:        MIT
URL:            https://github.com/sachesi/cpplings
Source0:        %{url}/archive/refs/tags/v%{version}.tar.gz#/%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc-c++

# The exercises are compiled with `c++` while cpplings runs.
Requires:       gcc-c++
Recommends:     libasan
Recommends:     libubsan
Recommends:     libtsan

%description
cpplings is a collection of small C++23 exercises in the style of Rustlings.
Each exercise doesn't compile or fails its tests; you fix it in your editor
while cpplings watches the file, reruns it on every save and moves you on once
it passes. Exercises are compiled with the checked standard library debug mode
and with sanitizers when their runtimes are installed.

%prep
%autosetup -n %{name}-%{version}

%build
%cmake -DCMAKE_BUILD_TYPE=Release
%cmake_build

%install
%cmake_install

%check
%{buildroot}%{_bindir}/%{name} --version
cd "$(mktemp -d)"
echo | %{buildroot}%{_bindir}/%{name} init
cd %{name}
echo | %{buildroot}%{_bindir}/%{name} run intro1
! %{buildroot}%{_bindir}/%{name} run intro2

%files
%license LICENSE
%doc README.md
%{_bindir}/%{name}

%changelog
* Wed Sep 23 2026 sachesi <xsachesi@pm.me> - 0.1.0-1
- Initial package.
