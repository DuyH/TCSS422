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

/**
 * The default state of a PCB
 */
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

/**
 * Get the id of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
int getPID (PCB *pcb) {
	return pcb->pid;
}

/**
 * Get the priority of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
int getPriority (PCB *pcb) {
	return pcb->priority;
}

/**
 * Get the state of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
enum process_state getState(PCB *pcb) {
	return pcb->state;
}

/**
 * Print the content of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
void toString(PCB * pcb) {
    printf("contents: PID: %d, Priority: %d, State: %s\n", pcb->pid, pcb->priority, getStateName(pcb->state));
}
