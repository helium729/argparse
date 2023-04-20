# cmake version
cmake_minimum_required(VERSION 3.0)

# project name
project(argparse)

# search for source files
file(GLOB_RECURSE SOURCES "src/*.cc")

# search for header files
file(GLOB_RECURSE HEADERS "include/*.h")

# include directories
include_directories(include)

# combine source and header files
set(SOURCES ${SOURCES} ${HEADERS})

# add library
add_library(argparse STATIC ${SOURCES})

# install
install(TARGETS argparse DESTINATION lib)
# install headers
install(DIRECTORY include/argparse DESTINATION include)

