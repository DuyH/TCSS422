/*
 * pcb.h
 *
 *  Created on: Jan 11, 2016
 *      Author: trung
 */

#ifndef PCB_H_
#define PCB_H_

enum state { new, ready, running, waiting, terminated };

typedef struct pcb_type {
	int PID;
	int priority;
	enum state;
	struct PCB * next_pcb;
} PCB;

int getPID ();

int getPriority ();

char * toString();

#endif /* PCB_H_ */
