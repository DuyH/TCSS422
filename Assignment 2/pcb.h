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
} PCB;

PCB * create();

int getPID (PCB *pcb);

int getPriority (PCB *pcb);

const char* getStateName(enum process_state state);

void toString(PCB * pcb);

#endif /* PCB_H_ */

