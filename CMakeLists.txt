cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Assignment\ 2/cpu.c Assignment\ 2/pcb.c Assignment\ 2/queue.c)
add_executable(cpu Assignment\ 2/cpu.c Assignment\ 2/pcb.c Assignment\ 2/queue.c)