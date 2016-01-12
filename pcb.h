/*
 * pcb.h
 *
 *  Created on: Jan 11, 2016
 *      Author: trung, duy
 */

#ifndef PCB_H_
#define PCB_H_

typedef enum process_state {
	new,
	ready,
	running,
	waiting,
	terminated
}state;

typedef struct pcb_type {
	int pid;
	int priority;
	enum process_state state;
} PCB;


int getPID (PCB *pcb);

int getPriority (PCB *pcb);

const char* getStateName(enum process_state state);

void toString(PCB * pcb);

#endif /* PCB_H_ */

