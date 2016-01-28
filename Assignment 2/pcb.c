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
const char *getStateName(enum process_state state) {
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
PCB *create() {
    PCB *pcb = calloc(3, sizeof(PCB));
    return pcb;
}

/**
 * Get the id of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
int getPID(PCB *pcb) {
    return pcb->pid;
}

/**
 * Get the priority of this PCB
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
int getPriority(PCB *pcb) {
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
 * Get the PC value of this PCB
 *
 *Parameters: PCB * pcb: A pointer to the PCB structure
 */
int get_PC_value(PCB *pcb) {
    return pcb->pc_value;
}

/**
 * Set the id of this PCB
 *
 *Parameters: PCB *pcb: A pointer to the PCB structure
 *Parameters: int new_pid: The new value to be the pid
 */
 void setPID (PCB *pcb, int new_pid) {
    pcb->pid = new_pid;
}

/**
 *Set the Priority of this PCB
 *
 *Parameters: PCB *pcb: A pointer to the PCB structure
 *Parameters: int new_priority: The new priority
 */
void setPriority (PCB *pcb, int new_priority) {
    pcb->priority = new_priority;
}

/**
 *Set the state of this PCB
 *
 *Parameters: PCB *pcb: A pointer to the PCB structure
 *Parameters: enum process_state new_state: the new state
 */
void setState (PCB *pcb, enum process_state new_state) {
    pcb->state = new_state;
}

/**
 *Set the pc_value of this PCB
 *
 *Parameters: PCB *pcb: A pointer to the PCB structure
 *Parameters: int new_pc_value: the new pc_value
 */
void setPC_value (PCB *pcb, int new_pc_value) {
    pcb->pc_value = new_pc_value;
}

/**
 * Returns the contents of this PCB as a string(char *).
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
char * toString(PCB *pcb) {
    static char pcbString[50];
    sprintf(pcbString, "PID: %d, Priority: %d, State: %s PC_Value: %d\n", getPID(pcb), getPriority(pcb), getStateName(pcb->state), get_PC_value(pcb));
    return pcbString;
}

/**
 * Print the contents of this PCB to console.
 *
 * Parameters: PCB * pcb: A pointer to the PCB structure
 */
void printPCB(PCB *pcb) {
    printf("PID: %02d, Priority: %02d, State: %s\n", getPID(pcb), getPriority(pcb), getStateName(pcb->state));
}