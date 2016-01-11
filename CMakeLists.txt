cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pcb.c)
add_executable(pcb pcb_test.c pcb.c priorityqueue.c)