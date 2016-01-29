/***********************************************************************************************
* cpu.h
*
* Programming Team:
* Duy Huynh
* Jeffrey LeCompte
* Trung Dang
* Brandon Scholor
*
* Date: 1/20/16
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

/**
 * Enumerating interrupt states.
 */
typedef enum interrupt_state {
    timer
} Interrupt_type;

/**
 * A struct representing a CPU.
 */
typedef struct cpu_type {
    unsigned int pc;
    unsigned int sysStack;
    PCB *currentProcess;
    Queue *readyQueue;
    Queue *terminatedQueue;
    Queue *newProcessesQueue;
} CPU;

typedef CPU *CPU_p;

/* CPU Constructor */
CPU_p CPU_constructor(void);

/* CPU destructor */
void CPU_destructor(CPU_p);

/* CPU getters & setters */

/* Set CPU's PC */
void CPU_set_pc(CPU_p, unsigned int);

/* Get CPU's PC */
unsigned int CPU_get_pc(CPU_p);

/* Set CPU's System Stack */
void CPU_push_sysStack(CPU_p, unsigned int);

/* Get CPU's System Stack */
unsigned int CPU_pop_sysStack(CPU_p);

/* Set CPU's currently running process */
void CPU_set_current_process(CPU_p, PCB_p);

/* Get CPU's currently running process */
PCB *get_current_process(CPU *cpu_p);

/* Utility Functions */

PCB *dispatch(CPU_p);

Queue *fetchProcess(CPU_p, State, int printCounter);

Queue *createNewProcesses(Queue *queue, int numb_process);

void file_handler(char *string);

void remove_file();

#endif //ASSIGNMENT1_CPU_H
