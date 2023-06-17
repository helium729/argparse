# argparse

This is a library for parsing command line arguments. It is designed to be
simple and easy to use. It is also designed to be extensible, additonal 
types can be added to the library.

The library can be linked as a static library in any platform with a C++ compiler and 
C++ STL support. 

## Compilation

For Linux/MSYS2, the following commands can be used to compile the library:

```
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<your prefix>
    make -j4
    make install
```

For other platforms, the library can be compiled using CMake and corresponding build system.

## Usage
See main.cc in scatk[https://github.com/helium729/scatk] as an example.

