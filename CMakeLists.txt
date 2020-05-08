cmake_minimum_required(VERSION 3.5)
project(BeerGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

#next 5 commands are to enable test coverage report on LCOV

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
find_package(Threads)
find_package(PkgConfig)

if(EXISTS $ENV{HOME}/Qt/5.14.1/gcc_64)
  set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.14.1/gcc_64)
endif()

include_directories(src)

add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(tests)

enable_testing()
add_test(NAME misc COMMAND beergame-tests)
