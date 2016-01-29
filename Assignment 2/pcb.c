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
const char *PCB_get_state(State state) {
    switch (state) {
        case created:
            return "created";
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
        default:
            return "0";
    }
}

/**
 * Reserve memory for a PCB in the heap.
 */
PCB_p PCB_constructor() {
    PCB_p pcb = calloc(3, sizeof(PCB));
    return pcb;
}

/**
 * Get the id of this PCB
 *
 * Parameters: PCB_p  pcb: A pointer to the PCB structure
 */
int PCB_get_pid(PCB_p pcb) {
    return pcb->pid;
}

/**
 * Get the priority of this PCB
 *
 * Parameters: PCB_p  pcb: A pointer to the PCB structure
 */
int PCB_get_priority(PCB_p pcb) {
    return pcb->priority;
}

/**
 * Get the state of this PCB
 *
 * Parameters - PCB_p  pcb: A pointer to the PCB structure
 */
State getState(PCB_p pcb) {
    return pcb->state;
}

/**
 * Get the PC value of this PCB
 *
 *Parameters: PCB_p  pcb: A pointer to the PCB structure
 */
int get_PC_value(PCB_p pcb) {
    return pcb->pc_value;
}

/**
 * Set the id of this PCB
 *
 *Parameters: PCB_p pcb: A pointer to the PCB structure
 *Parameters: int new_pid: The new value to be the pid
 */
void PCB_set_pid(PCB_p pcb, int new_pid) {
    pcb->pid = new_pid;
}

/**
 *Set the Priority of this PCB
 *
 *Parameters: PCB_p pcb: A pointer to the PCB structure
 *Parameters: int new_priority: The new priority
 */
void PCB_set_priority(PCB_p pcb, int new_priority) {
    pcb->priority = new_priority;
}

/**
 *Set the state of this PCB
 *
 *Parameters: PCB_p pcb: A pointer to the PCB structure
 *Parameters: enum process_state new_state: the new state
 */
void PCB_set_state(PCB_p pcb, State new_state) {
    pcb->state = new_state;
}

/**
 *Set the pc_value of this PCB
 *
 *Parameters: PCB_p pcb: A pointer to the PCB structure
 *Parameters: int new_pc_value: the new pc_value
 */
void PCB_set_pc(PCB_p pcb, int new_pc_value) {
    pcb->pc_value = new_pc_value;
}

/**
 * Returns the contents of this PCB as a string(char *).
 *
 * Parameters: PCB_p pcb: A pointer to the PCB structure
 */
char *PCB_toString(PCB_p pcb) {
    static char pcbString[50];
    sprintf(pcbString, "PID: %d, Priority: %d, State: %s PC_Value: %d\n", PCB_get_pid(pcb), PCB_get_priority(pcb),
            PCB_get_state(pcb->state), get_PC_value(pcb));
    return pcbString;
}

/**
 * Print the contents of this PCB to console.
 *
 * Parameters: PCB_p pcb: A pointer to the PCB structure
 */
void PCB_print(PCB_p pcb) {
    printf("PID: %02d, Priority: %02d, State: %s\n", PCB_get_pid(pcb), PCB_get_priority(pcb),
           PCB_get_state(pcb->state));
}