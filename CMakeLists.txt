cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pcb.c queue_test.c)
add_executable(queue queue_test.c pcb.c queue.c)
add_executable(pcb pcb_test.c pcb.c)
add_executable(queueTest queue.c pcb.c)