cmake_minimum_required(VERSION 3.16)
project(externalsort)

set(CMAKE_CXX_STANDARD 14)

add_executable(externalsort main.cpp functions.h functions.cpp)