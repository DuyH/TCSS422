/***********************************************************************************************
 * pcb.h
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
 * This header file defines the class and methods for the process control block implementation
 *
 ************************************************************************************************/

#ifndef PCB_H_
#define PCB_H_

typedef enum process_state {
    created, new, ready, running, waiting, interrupted, terminated
} State;

typedef struct pcb_type {
    int pid;
    int priority;
    enum process_state state;
    unsigned int pc_value;
} PCB;

typedef PCB *PCB_p;

/* PCB Constructor */
PCB_p PCB_constructor();            // constructs a new pcb object in the heap

/* PCB Destructor */
void PCB_destructor(PCB_p);         // frees memory allocated to pcb object

/* Setters */

void PCB_set_pid(PCB_p, int);       // sets this->pid to int value

void PCB_set_priority(PCB_p, int);  // sets this->priority to int value

void PCB_set_state(PCB_p, State);   // sets this->state to State value

void PCB_set_pc(PCB_p, int);        // sets this->pc to int value

/* Getters */

int PCB_get_pid(PCB_p);             // returns pid value

int PCB_get_priority(PCB_p);        // returns priority value

State PCB_get_state(PCB_p);         // returns state value

unsigned int PCB_get_PC(PCB_p);              // returns pc value

/* Utility Functions */

const char *PCB_get_state_string(State);   // returns state value

char *PCB_toString(PCB_p); // returns pointer to character array of this pcb's contents

void PCB_print(PCB_p);              // prints to console this pcb's contents

#endif /* PCB_H_ */
