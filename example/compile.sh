# check if test directory exists
if [ ! -d "build" ]; then
    mkdir build
else
    rm -rf build/*
fi

if [ ! -d "bin" ]; then
    mkdir bin
fi

set -x

cd build
cmake ../.. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..
make
make install

cd ..

g++ -o ./bin/example ./src/example.cc -I./include -L./lib -largparse

set +x