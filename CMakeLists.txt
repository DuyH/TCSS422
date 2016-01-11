cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp pcb_test.c)
add_executable(Assignment1 ${SOURCE_FILES})
add_executable(binarycalculator binarycalculator.c)
add_executable(pcb pcb.c)