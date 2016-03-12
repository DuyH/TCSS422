/*
 * priorityqueue.c
 *
 * TCSS 422 '16
 * Assignment 1
 * Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 * Represents an implementation of a priority queue for FIFO queues consisting of PCB's.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include "PriorityQueue.h"

#define PRIORITY_NUMBERS 4		// Range of priorities, as stated

/*
*instantiates a priority queue with a specified number of FIFO Queues.
*/
PQueue_p PQueue_constructor() {
	
	int i;
	PQueue_p thisPQueue = calloc(PRIORITY_NUMBERS, sizeof(p_queue));
	for (i = 0; i < PRIORITY_NUMBERS; i++)
	{
		Queue_p curQueue = calloc(PRIORITY_NUMBERS, sizeof(Queue));
		thisPQueue->pri_Queue[i] = curQueue;
		
	}
    return thisPQueue;
}

	void PQueue_destructor(PQueue_p queue)  {      // frees memory allocated to queue object
		free(queue);
	}
/*
* adds a pcb to the Priority Queue
*/
PQueue_p PQueue_enqueue(PQueue_p priority_Queue, PCB_p pcb) {
	int p = pcb->priority;
	priority_Queue->pri_Queue[p] = Queue_enqueue(priority_Queue->pri_Queue[p], pcb);	// enqueues the new node into the Queue dictated by the pcb priority
	priority_Queue->size++;
	return priority_Queue;
}

/*
* checks the next node that will be dequeued without removing it.
*/
PCB_p PQueue_peek(PQueue_p priority_Queue) {
	int i;
	PCB_p pcb;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		
		if (!Queue_isEmpty(priority_Queue->pri_Queue[i])) {		//checks whether the head is empty or not
			pcb = Queue_peek(priority_Queue->pri_Queue[i]);
			break;
		}
	}
	return pcb;
}

/*
* dequeues the highest priority pcb from its FIFO queue
*/
PCB * PQueue_dequeue(PQueue_p priority_Queue) {
	int i;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		
		if (!Queue_isEmpty(priority_Queue->pri_Queue[i])) {		// checks that the current FIFO queue is not empty
			PCB * removed = Queue_dequeue(priority_Queue->pri_Queue[i]);	// grabs the value dequeued from the FIFO queue
			return removed;
		}
	}
	return NULL;
}

/*
* displays the current iteration of the Priority Queue
* takes an integer to determine if contents of last item should be shown.
*/
void PQueue_print(PQueue_p priority_Queue, int showContents){
	int i;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		printf("Q%02d: ", i);
		Queue_print(priority_Queue->pri_Queue[i], showContents);    // prints the queues in priority order
	}
}

int PQueue_isEmpty(PQueue_p queue) {
	int i, count;
	for (i = 0; i < 4; i++) {
		if (Queue_isEmpty(queue->pri_Queue[i])){
			count++;
		}
	}
	return (count == 4);
}
