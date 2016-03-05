cmake_minimum_required(VERSION 3.3)
project(Project)

find_package(Threads)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Project/cpu.c Project/pcb.c Project/queue.c Project/)
add_executable(project Project/cpu.c Project/pcb.c Project/queue.c Project/PriorityQueue.c "Project/timer.c" "Project/timer.c" "Project/io.c")