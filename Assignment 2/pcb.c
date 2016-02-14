/***********************************************************************************************
 * pcb.c
 *
 * Programming Team:
 * Duy Huynh
 * Jeffrey LeCompte
 * Trung Dang
 * Brandon Scholer
 *
 * TCSS 422 - Winter 2016
 * Date: 1/20/16
 * Assignment 2
 *
 * Description:
 * PCB structure consisting of a pid, priority, and state.
 *
 ************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

/**
 * Constructs a PCB object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created PCB object.
 */
PCB_p PCB_constructor() {
    PCB_p pcb = (PCB_p) malloc(sizeof(PCB));
    return pcb;
}

/**
 * Frees allocated memory used by the PCB object.
 *
 * Parameters:  PCB_p pcb: pointer to the PCB object.
 */
void PCB_destructor(PCB_p pcb) {
    free(pcb);
}

/**
 * Set the id of this PCB
 *
 *Parameters:   PCB_p pcb: A pointer to the PCB structure
 *              int new_pid: The new value to be the pid
 */
void PCB_set_pid(PCB_p pcb, int new_pid) {
    pcb->pid = new_pid;
}

/**
 *Set the Priority of this PCB
 *
 *Parameters:   PCB_p pcb: A pointer to the PCB structure
 *              int new_priority: The new priority
 */
void PCB_set_priority(PCB_p pcb, int new_priority) {
    pcb->priority = new_priority;
}

/**
 *Set the state of this PCB
 *
 *Parameters:   PCB_p pcb: A pointer to the PCB structure
 *              enum process_state new_state: the new state
 */
void PCB_set_state(PCB_p pcb, State new_state) {
    if (pcb != NULL)
        pcb->state = new_state;
}

/**
 *Set the pc_value of this PCB
 *
 *Parameters:   PCB_p pcb: A pointer to the PCB structure
 *              int new_pc_value: the new pc_value
 */
void PCB_set_pc(PCB_p pcb, int new_pc_value) {
    pcb->pc_value = new_pc_value;
}

/**
 * Get the id of this PCB
 *
 * Parameters:  PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int id of PCB object.
 */
int PCB_get_pid(PCB_p pcb) {
    return pcb->pid;
}

/**
 * Get the priority of this PCB
 *
 * Parameters:  PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int priority of PCB object.
 */
int PCB_get_priority(PCB_p pcb) {
    return pcb->priority;
}

/**
 * Get the state of this PCB
 *
 * Parameters:  PCB_p  pcb: A pointer to the PCB structure
 * Returns:     State of PCB object.
 */
State PCB_get_state(PCB_p pcb) {
    return pcb->state;
}

/**
 * Get the PC value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int PC value of PCB object.
 */
unsigned int PCB_get_PC(PCB_p pcb) {
    return pcb->pc_value;
}

/**
 * Retrieve the descriptive name of pcb's state, given enumeration.
 *
 * Parameters:  State state: Enumeration of State
 * Returns:     char State string value.
 */
const char *PCB_get_state_string(State state) {
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
        case interrupted:
            return "interrupted";
        case terminated:
            return "terminated";
        default:
            return "0";
    }
}

/**
 * Returns the contents of this PCB as a string(char *).
 *
 * Parameters:  PCB_p pcb: A pointer to the PCB structure
 * Returns:     char PCB string representation.
 */
char *PCB_toString(PCB_p pcb) {
    static char pcbString[200];
    sprintf(pcbString, "PID: %d, Priority: %d, State: %s, PC_Value: %d\n",
            PCB_get_pid(pcb), PCB_get_priority(pcb),
            PCB_get_state_string(pcb->state), PCB_get_PC(pcb));
    return pcbString;
}

/**
 * Print the contents of this PCB to console.
 *
 * Parameters:  PCB_p pcb: A pointer to the PCB structure
 */
void PCB_print(PCB_p pcb) {
    printf("PID: %02d, Priority: %02d, State: %s\n", PCB_get_pid(pcb),
           PCB_get_priority(pcb), PCB_get_state_string(pcb->state));
}
