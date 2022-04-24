# TarBzParser
C library to parse .tar.bz2 files in the resource restricted (f.e. embedded) environment.

With the library it is possible to pick out some data from huge tar, and tar.bz2 files without the need to extract them completely.

## How to compile

* clone dimitri-rebrikov/TarBzParser
* clone dimitri-rebrikov/bzip2 into the same (parent) directory
* `cd TarBzParser`
* `mkdir build`
* `cd build`
* `cmake ..`
* `make all test`
* see test/*Test.c files for examples how to use the library