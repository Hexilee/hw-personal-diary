cmake_minimum_required(VERSION 3.8)
project(pd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
#set(CMAKE_CXX_FLAGS_RELEASE "-O2")
include_directories(src)

add_executable(pdadd src/pdadd.cpp src/diary.cpp)
add_executable(pdshow src/pdshow.cpp src/diary.cpp)
add_executable(pdlist src/pdlist.cpp src/diary.cpp)
add_executable(pdremove src/pdremove.cpp src/diary.cpp)