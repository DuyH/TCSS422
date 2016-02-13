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
    PCB_p pcb = calloc(3, sizeof(PCB));

    int i = 0;
    for (; i < 4; i++) {
    	int new = 300 * (rand() % 3  + 3);
    	int new1 = 300 * (rand() % 3  + 3) + (rand() % 10 + 10);
    	if (i != 0) {
    		new += pcb->io_trap_1[i - 1];
    		new1 += pcb->io_trap_2[i - 1];
    	}
        PCB_set_io_trap_1(pcb, new, i);
        PCB_set_io_trap_2(pcb, new1, i);
    }
    pcb->terminate = rand() % 5;
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

/****************************************************
*                   Setters                         *
****************************************************/

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
*Set the max_pc of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int new_max_pc: the new max_pc value
*/
void PCB_set_max_pc(PCB_p pcb, int new_max_pc) {
  pcb->max_pc = new_max_pc;
}

/**
*Set the creation of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int new_creation: the new creation value
*/
void PCB_set_creation(PCB_p pcb, int new_creation) {
    pcb->creation = new_creation;
}

/**
*Set the termination of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int new_termination: the new termination value
*/
void PCB_set_termination(PCB_p pcb, int new_termination) {
    pcb->termination = new_termination;
}

/**
*Set the terminate of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int new_terminate: the new terminate value
*/
void PCB_set_terminate(PCB_p pcb, int new_terminate) {
    pcb->terminate = new_terminate;
}

/**
*Set the term_count of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int new_term_count: the new term_count value
*/
void PCB_set_term_count(PCB_p pcb, int new_term_count) {
    pcb->term_count = new_term_count;
}

/**
*Set an io_trap of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int io_value: the new io value
*               int index: the index of the new io_value
*/
void PCB_set_io_trap_1(PCB_p pcb, int io_value, int index) {
    pcb->io_trap_1[index] = io_value;
}

/**
*Set an io_trap of this PCB
*
*Parameters:    PCB_p pcb: a pointer to the PCB structure
*               int io_value: the new io value
*               int index: the index of the new io_value
*/
void PCB_set_io_trap_2(PCB_p pcb, int io_value, int index) {
    pcb->io_trap_2[index] = io_value;
}

/****************************************************
*                   Getters                         *
****************************************************/

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
 * Get the max_pc value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int max_pc value of PCB object.
 */
unsigned int PCB_get_max_pc(PCB_p pcb) {
    return pcb->max_pc;
}

/**
 * Get the creation value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int creation value of PCB object.
 */
unsigned int PCB_get_creation(PCB_p pcb) {
    return pcb->creation;
}

/**
 * Get the termination value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int termination value of PCB object.
 */
unsigned int PCB_get_termination(PCB_p pcb) {
    return pcb->termination;
}

/**
 * Get the terminate value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int terminate value of PCB object.
 */
unsigned int PCB_get_terminate(PCB_p pcb) {
    return pcb->terminate;
}

/**
 * Get the term_count value of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int term_count value of PCB object.
 */
unsigned int PCB_get_term_count(PCB_p pcb) {
    return pcb->term_count;
}

/**
 * Get the indicated io_trap of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:      indicated io_trap array of PCB object.
 */
unsigned int * PCB_get_io_trap(PCB_p pcb, int io_trap_num) {
    switch (io_trap_num) {
        case 1 :
            return pcb->io_trap_1;
        case 2 :
            return pcb->io_trap_2;
        default:
            return NULL;
    }
}

/**
 * Get a value of the indicated io_trap of this PCB
 *
 * Parameters:   PCB_p  pcb: A pointer to the PCB structure
 * Returns:     int indicated io_trap value of indicated index of PCB object.
 */
unsigned int PCB_get_io_trap_index(PCB_p pcb, int index, int io_trap_num) {
    switch (io_trap_num) {
        case 1 :
            return pcb->io_trap_1[index];
        case 2 :
            return pcb->io_trap_2[index];
        default:
        	return -1;
    }
}

/****************************************************
*                    Utility                        *
****************************************************/

/**
* Increments the PC value
*
* Parameters: PCB_p pcb: the pcb which has the PC to be incremented.
*/
void PCB_increment_PC(PCB_p pcb) {
    pcb->pc_value++;
}

/**
* Increments the term_count value
*
* Parameters: PCB_p pcb: the pcb which has the term_count to be incremented.
*/
void PCB_increment_term_count(PCB_p pcb) {
    pcb->term_count++;
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
