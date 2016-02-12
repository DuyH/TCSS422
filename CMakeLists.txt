cmake_minimum_required(VERSION 3.3)
project(Assignment3)

find_package(Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Assignment\ 2/cpu.c Assignment\ 2/pcb.c Assignment\ 2/queue.c)
add_executable(cpu Assignment\ 3/cpu.c Assignment\ 3/pcb.c Assignment\ 3/queue.c "Assignment 3/timer.c" "Assignment 3/io.h" "Assignment 3/io.c")