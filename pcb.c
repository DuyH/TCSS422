/*
 * pcb.c
 *
 * TCSS 422 '16
 * Assignment 1
 * Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 * PCB structure consisting of a pid, priority, and state.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

/**
 * Retrieve the descriptive name of pcb's state, given enumeration.
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
 * Reserve memory for a PCB in the heap.
 */
PCB * create() {
    PCB * pcb = calloc(3, sizeof(PCB));
    return pcb;
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
 * Parameters - PCB * pcb: A pointer to the PCB structure
 */
enum process_state getState(PCB *pcb) {
	return pcb->state;
}

/**
 * Print the contents of this PCB to console.
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
void toString(PCB * pcb) {
    printf("contents: PID: %d, Priority: %d, State: %s\n", pcb->pid, pcb->priority, getStateName(pcb->state));
}
