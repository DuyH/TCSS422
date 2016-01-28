/*
 * pcb.h
 *
 * TCSS 422 '16
 * Assignment 1
 * Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 * PCB header file consisting of a pid, priority, state and method to print its contents.
 *
*/

#ifndef PCB_H_
#define PCB_H_

typedef enum process_state {
	created,
	new,
	ready,
	running,
	waiting,
	terminated
} state;

typedef struct pcb_type {
	int pid;
	int priority;
	enum process_state state;
	int pc_value;
} PCB;

PCB * create();

int getPID (PCB *pcb);

int getPriority (PCB *pcb);

const char* getStateName(enum process_state state);

int getPC_value (PCB *pcb);

void setPID (PCB *pcb, int new_pid);

void setPriority (PCB *pcb, int new_priority);

void setState (PCB *pcb, enum process_state new_state);

void setPC_value (PCB *pcb, int new_pc_value);

char * toString(PCB * pcb);

void printPCB(PCB * pcb);

#endif /* PCB_H_ */
