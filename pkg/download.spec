Name:          download
Version:       1.0
Release:       1
BuildArch:     x86_64
Summary:       Command line file downloader
URL:           github.com/mark-github/download
License:       Artistic
Source0:       download.tar.gz
Prefix:        %{_prefix}/local/bin
Requires:      libcurl
Requires:      ncurses-libs
BuildRequires: git
BuildRequires: gcc
BuildRequires: curl-devel
BuildRequires: ncurses-devel

%define git_url https://github.com/mark-github/download.git

%description
"download is a small C program for downloading files.  Multiple downloads run
concurrently in separate threads, with the option of live progress output."

%prep
rm -rf ${RPM_BUILD_DIR}/*
rm -rf ${RPM_SOURCE_DIR}/download.tar.gz

# check out the git project
git clone %{git_url}

# create a source archive and move it to SOURCES
tar czf download.tar.gz download
mv download.tar.gz ${RPM_SOURCE_DIR}


%build
cd download
make


%install
# only install the standalone script
mkdir -p ${RPM_BUILD_ROOT}%{prefix}
#cp ack2/ack-standalone ${RPM_BUILD_ROOT}%{prefix}/ack
cp download/download ${RPM_BUILD_ROOT}%{prefix}/download


%clean
rm -rf ${RPM_BUILD_ROOT}/*
rm -rf ${RPM_BUILD_DIR}/*


%files
%defattr(755,root,root,-)
%{prefix}/download

%changelog
* Fri Sep 27 2013 <mark.regan@gmail.com> 1.0-1
- Created initial spec file
