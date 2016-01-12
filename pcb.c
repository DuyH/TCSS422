/*
 * pcb.c
 * Authors: Duy Huynh & Jeffrey LeCompte, Trung Dang
 * Sources:
 *         https://en.wikipedia.org/wiki/Process_control_block
 *         http://www.tutorialspoint.com/operating_system/os_processes.htm
 *         https://courses.cs.washington.edu/courses/cse451/07wi/lectures/4-process.pdf
 *         http://stackoverflow.com/questions/4938854/process-control-block
 *         Detailed PCB Example: http://www.brokenthorn.com/Resources/OSDev24.html
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

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
        default: return "0";
    }
}


int getPID (PCB *pcb) {
	return pcb->pid;
}

int getPriority (PCB *pcb) {
	return pcb->priority;
}

enum process_state getState(PCB *pcb) {
	return pcb->state;
}

void toString(PCB * pcb) {
    printf("contents: PID: %d, Priority: %d, State: %s\n", pcb->pid, pcb->priority, getStateName(pcb->state));
}
