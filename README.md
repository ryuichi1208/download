download
========

Command line file downloader

download is a small C program for downloading files.  Mulitple downloads run
concurrently in separate threads, with the option of live progress output.

Library Dependencies
--------------------

download relies on the curl and ncurses shared libraries.  The curl library
performs the actual data download operations, while ncurses is used to refresh
the terminal display when live progress is enabled.  Both libraries are readily
available on most Mac/Linux systems.  See the links below for more information.

curl - 
[http://curl.haxx.se/](http://curl.haxx.se/) <br>
ncurses - 
[http://www.gnu.org/software/ncurses/](http://www.gnu.org/software/ncurses/)

The pthread library is also linked, but this should be available by default on
most systems.

Setup
-----

Start by cloning the git repository.  Once that completes, change to the project
directory.

    $ git clone https://github.com/mark-github/download.git
    ...
    $ cd download

Building
--------

There are two options for building.

* make
* Bash scripts

###make

A simple `Makefile` is provided to compile and link the download program by
default.

    $ make
    gcc -Wall -o download -lcurl -lncurses -lpthread src/*.c

If `gdb` debugging is required, the debug target will build with the necessary
options.

    $ make debug
    gcc -Wall -g -o download -lcurl -lncurses -lpthread src/*.c

Finally, the clean target will delete the program executable and its debug
directory, if present.

    $ make clean
    if [ -f download ]; then rm -f download; fi;
    if [ -d download.dSYM ]; then rm -rf download.dSYM; fi;

Currently, there is no install target (i.e. `$ make install`).

###Bash scripts

As an alternative to the included `Makefile`, `compile.sh` and `run.sh` will
build and run the program, respectively.  (`run.sh` actually calls `compile.sh` 
prior to execution.)

Running
-------

Supply the `-h` option to get a brief list of available arguments.

    $ download -h
    download [-hp] [-d <directory>] [-f <file>] [...]
        -d <directory> | save downloaded files into <directory>
        -h             | print this help message
        -p             | display progress during download
        -f <file>      | download the URLs listed in <file>
        -s             | disable SSL peer and host verification

For example, to download two files into the `/tmp` directory, run the following 
command:

    $ download -d /tmp http://example.com/file_a http://example.com/file_b

If a download directory is not specified, files will be saved to the current
working directory.

The `-f` option specifies a text file containing a list of URLs to download, one
per line.  This can be combined with explicit URL arguments, for instance:

    $ download -f ~/files_to_download.txt google.com

The `-p` option enables live progress output via ncurses.
