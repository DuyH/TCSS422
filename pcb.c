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

    int pid;                    /* identification number (size 4) */
    int priority;               /* priority (size 4) */
    enum process_state state;   /* current state (size 4) */
    struct PCB *next_pcb;       /* ptr to next PCB (size 8) */
    // Program counter, stack pointer, registers
    // Address space info (how much memory it takes)
    // Expected execution time (burst)

} PCB;

typedef PCB * PCB_p;

const char* getStateName(enum process_state state) {
    switch (state) {
        case new:
            return "new";
        case ready:
            return "ready";
        case running:
            return "running";
        case waiting:
            return "waiting";
        case terminated:
            return "terminated";
    }
}

void toString(PCB pcb) {
    printf("PID: %d, Priority: %d, State: %s, Next PCB: %p\n", pcb.pid, pcb.priority, getStateName(pcb.state), pcb.next_pcb);
}

int main(void){
    PCB pcb;
    pcb.pid = 1;
    pcb.state = ready;
    pcb.priority = 4;

    toString(pcb);

}