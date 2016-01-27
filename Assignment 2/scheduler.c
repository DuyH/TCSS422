/*
 * scheduler.c
 *
 *  Created on: Jan 26, 2016
 *      Author: trung
 */

#include "scheduler.h"

/**
 * Fetch a process from the newly created process list and put it
 * in the ready queue to be running.
 */
Queue * fetchProcess(Queue *newProcess, Queue *readyQueue) {
	if (isEmpty(newProcess)) {
		printf("No process to be scheduled! List is empty.\n");
	} else {
		PCB *readyPCB = dequeue(newProcess);
		readyPCB->state = ready;
		enqueue(readyQueue, readyPCB);
		printf("Process transfered to readyQueue: ");
		toString(readyPCB);
	}
	return readyQueue;
}
