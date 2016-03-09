tinyray
=======

About
-----

I'm building a raytracer!

Because everybody should... and my C really needs brushing up;

Building
--------

```bash
cd build
cmake ..
make
make tests
```

Bison & Flex
----

TinyRay uses bison and flex for parsing, so these need to be installed.

On OSX, the following may be necessary to make sure that CMake finds the versions of bison and flex installed with homebrew.

```bash
export CMAKE_PREFIX_PATH=`brew --prefix`/opt/bison/bin:`brew --prefix`/opt/flex/bin
```
Contact
-------

guy@rumblesan.com if you have any questions

