cmake_minimum_required(VERSION 3.3)
project(Assignment1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Assignment\ 2/cpu.c Assignment\ 1/pcb.c)
add_executable(queue Assignment\ 1/queue_test.c Assignment\ 1/pcb.c Assignment\ 1/queue.c)
add_executable(pcb Assignment\ 1/pcb_test.c Assignment\ 1/pcb.c)
add_executable(pqueue Assignment\ 1/priorityqueue_test.c Assignment\ 1/priorityqueue.c Assignment\ 1/pcb.c Assignment\ 1/queue.c)
add_executable(cpu Assignment\ 2/cpu.c Assignment\ 2/scheduler.c Assignment\ 2/pcb.c Assignment\ 2/queue.c Assignment\ 2/dispatcher.c)