/***********************************************************************************************
 * cpu.h
 *
 * Programming Team:
 * Duy Huynh
 * Jeffrey LeCompte
 * Trung Dang
 * Brandon Scholor
 *
 * TCSS 422 - Winter 2016
 * Date: 1/20/16
 * Assignment 2
 *
 * Description:
 * This header file defines the class and methods for the cpu implementation
 *
 ************************************************************************************************/

#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "pcb.h"

/* Enumerating interrupt states. */
typedef enum interrupt_state {
    timer, io, normal
} Interrupt_type;

/* A struct representing a CPU. */
typedef struct cpu_type {
    unsigned int timer;
    unsigned int pc;
    unsigned int sysStack;
    PCB_p currentProcess;
    Queue_p readyQueue;
    Queue_p terminatedQueue;
    Queue_p newProcessesQueue;
} CPU;

typedef CPU *CPU_p;

/* CPU Constructor */
CPU_p CPU_constructor(void);          // constructs a new cpu object in the heap

/* CPU destructor */
void CPU_destructor(CPU_p);              // frees memory allocated to pcb object

/* Setters */

void CPU_set_pc(CPU_p, unsigned int);           // sets this->pc to int value

void CPU_set_current_process(CPU_p, PCB_p); // sets this->current_process to pcb pointer

void CPU_set_readyQueue(CPU_p, Queue_p); // sets this->readyQueue to queue pointer

void CPU_set_terminatedQueue(CPU_p, Queue_p); // sets this->terminatedQueue to queue pointer

void CPU_set_newProcessesQueue(CPU_p, Queue_p); // sets this->newProcessesQueue to queue pointer

/* Getters */

unsigned int CPU_get_pc(CPU_p);                 // returns this cpu's pc

PCB_p CPU_get_current_proc(CPU_p); // returns this cpu's currently running process (pcb pointer)

Queue_p CPU_get_readyQueue(CPU_p);        // returns this cpu's readyQueue queue

Queue_p CPU_get_terminatedQueue(CPU_p); // returns this cpu's terminatedQueue queue

Queue_p CPU_get_newProcessesQueue(CPU_p); // returns this cpu's newProcesses queue

/* ADT Functions */

Queue_p CPU_enqueue_readyQueue(CPU_p, PCB_p); // Enqueues a PCB object to the CPU's readyQueue

PCB_p CPU_dequeue_readyQueue(CPU_p); // Dequeues a PCB object from the CPU's readyQueue

Queue_p CPU_enqueue_terminatedQueue(CPU_p, PCB_p); // Enqueues a PCB object to the CPU's terminatedQueue

PCB_p CPU_dequeue_terminatedQueue(CPU_p); // Dequeues a PCB object from the CPU's terminatedQueue

/* Set CPU's System Stack */
void CPU_push_sysStack(CPU_p, unsigned int); // Pushes unsigned int value onto cpu's sysStack

/* Get CPU's System Stack */
unsigned int CPU_pop_sysStack(CPU_p);  // Pops off int value from cpu's sysStack

/* Utility Functions */

void CPU_dispatcher(CPU_p cpu, Interrupt_type interrupt_type);

void CPU_scheduler(CPU_p cpu, Interrupt_type interrupt_type, int);

void CPU_pseudo_isr(CPU_p cpu, int);

PCB_p dispatch(CPU_p);                          // Dispatches...

Queue_p CPU_fetch_process(CPU_p, Interrupt_type, int);   // Fetches new process

Queue_p CPU_create_processes(Queue_p, int, int);     // Creates new processes

void CPU_file_handler(char *string);            // Handles file writing

void CPU_remove_file();                         // Removes existing file

#endif //ASSIGNMENT1_CPU_H
