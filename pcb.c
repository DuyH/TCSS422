//
// Created by jef on 1/6/16.
// Worked on by Duy
// Sources:
//          https://en.wikipedia.org/wiki/Process_control_block
//          http://www.tutorialspoint.com/operating_system/os_processes.htm
//          https://courses.cs.washington.edu/courses/cse451/07wi/lectures/4-process.pdf
//          http://stackoverflow.com/questions/4938854/process-control-block
//          Detailed PCB Example: http://www.brokenthorn.com/Resources/OSDev24.html
//

#include <stdlib.h>
#include <stdio.h>

enum process_state {new, ready, running, waiting, terminated};

typedef struct pcb {

    int pid;                    /* identification number */
    int priority;               /* priority */
    enum process_state state;   /* current state */
    // Program counter, stack pointer, registers
    // Address space info (how much memory it takes)
    struct PCB *next_pcb;       /* ptr to next PCB */
    // Expected execution time (burst)

} PCB;

typedef PCB * PCB_p;

void toString(){

}
