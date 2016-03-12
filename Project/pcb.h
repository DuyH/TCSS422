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
 * Date: 2/10/16
 * Assignment 3
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

typedef enum process_type {
    io, producer, consumer, intensive, mutual
} Process_Type;

typedef struct pcb {
    int pid;                        // id number
    int priority;                   // priority
    enum process_state state;       // state of the process
    unsigned int pc_value;          // pc value
    unsigned int max_pc;            // the max pc value before reset
    long int creation;              // clock time at process creation
    long int termination;           // clock time at process termination
    unsigned int terminate;         // max number for process termination, 0 for no termination
    unsigned int term_count;        // counter until process termination
    unsigned int boost;             // starvation field for priority switch
    unsigned int boost_start;       // PC Value when the boost was triggered (for starvation)
    enum process_type type;         // differentiates different processes

    unsigned int lock[4];
    unsigned int trylock[4];
    unsigned int unlock[4];

    unsigned int pair_name;         // Pair "name"

    unsigned int io_trap_1[4];
    unsigned int io_trap_2[4];      // arrays where io trap will occur
} PCB;

typedef PCB *PCB_p;

/* PCB Constructor */
PCB_p PCB_constructor(Process_Type);// constructs a new pcb object in the heap

/* PCB Destructor */
void PCB_destructor(PCB_p);         // frees memory allocated to pcb object

/* Setters */

void PCB_set_pid(PCB_p, int);       // sets this->pid to int value

void PCB_set_priority(PCB_p, int);  // sets this->priority to int value

void PCB_set_state(PCB_p, State);   // sets this->state to State value

void PCB_set_pc(PCB_p, int);        // sets this->pc to int value

void PCB_set_max_pc(PCB_p, int);    // sets this->max_pc to int value

void PCB_set_creation(PCB_p, long int);  // sets this->creation to int value

void PCB_set_termination(PCB_p, long int); // sets this->termination to int value

void PCB_set_terminate(PCB_p, int); // sets this->terminate to int value

void PCB_set_term_count(PCB_p, int); // sets this->term_count to int value

void PCB_set_io_trap_1(PCB_p, int, int); // sets->io_trap_1 to int value at int index

void PCB_set_io_trap_2(PCB_p, int, int); // sets->io_trap_2 to int value at int index

/* Getters */

int PCB_get_pid(PCB_p);             // returns pid value

int PCB_get_priority(PCB_p);        // returns priority value

State PCB_get_state(PCB_p);         // returns state value

unsigned int PCB_get_PC(PCB_p);              // returns pc value

unsigned int PCB_get_max_pc(PCB_p);         // returns max_pc value

long int PCB_get_creation(PCB_p);       // returns creation value

long int PCB_get_termination(PCB_p);    // returns termination value

unsigned int PCB_get_terminate(PCB_p);      // returns terminate value

unsigned int PCB_get_term_count(PCB_p);     // returns term_count value;

unsigned int *PCB_get_io_trap(PCB_p, int); // returns the referenced io_trap array;

unsigned int PCB_get_io_trap_index(PCB_p, int, int); // returns the referenced index of the referenced io_trap array;

/* Utility Functions */

void PCB_increment_PC(PCB_p); // increments the PC value

void PCB_increment_term_count(PCB_p); // increments term_count

const char *PCB_get_state_string(State);   // returns state value

const char *PCB_get_type_string(Process_Type);   // returns process type value

char *PCB_toString(PCB_p); // returns pointer to character array of this pcb's contents

void PCB_print(PCB_p);              // prints to console this pcb's contents

#endif /* PCB_H_ */
