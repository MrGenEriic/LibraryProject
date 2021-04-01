cmake_minimum_required(VERSION 3.17)
project(LibraryProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibraryProject LibraryCore.cpp Library.cpp Library.h)