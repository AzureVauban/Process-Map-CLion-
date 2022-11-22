cmake_minimum_required(VERSION 3.23)
project(Process_Map__CLion_)

set(CMAKE_CXX_STANDARD 17)

add_executable(Process_Map__CLion_ solution.cpp Include/Nodes.h)
add_subdirectory(Catch2_Tests)