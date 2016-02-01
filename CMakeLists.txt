cmake_minimum_required(VERSION 3.3)
project(Assignment1)

find_package(Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Assignment\ 2/cpu.c Assignment\ 2/pcb.c Assignment\ 2/queue.c)
add_executable(cpu Assignment\ 2/cpu.c Assignment\ 2/pcb.c Assignment\ 2/queue.c)
add_executable(pthread pthread_example.c)
target_link_libraries(pthread ${CMAKE_THREAD_LIBS_INIT})