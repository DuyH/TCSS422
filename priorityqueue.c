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
#include "priorityqueue.h"

#define PRIORITY_NUMBERS 32		// Range of priorities, as stated

/*
*instantiates a priority queue with a specified number of FIFO Queues.
*/
p_queue * create_pqueue() {
	
	int i;
	p_queue * thisPQueue = calloc(PRIORITY_NUMBERS, sizeof(p_queue));
	for (i = 0; i < PRIORITY_NUMBERS; i++)
	{
		Queue * curQueue = calloc(1, sizeof(Queue));
		thisPQueue->pri_Queue[i] = curQueue;
		
	}

    return thisPQueue;
}

/*
* adds a pcb to the Priority Queue
*/
void add(p_queue * priority_Queue, PCB *pcb) {
	int p = pcb->priority;
	enqueue(priority_Queue->pri_Queue[p], pcb);	// enqueues the new node into the Queue dictated by the pcb priority
}

/*
* checks the next node that will be dequeued without removing it.
*/
void check(p_queue * priority_Queue) {
	int i;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		
		if (!isEmpty(priority_Queue->pri_Queue[i])) {		//checks whether the head is empty or not
			peek(priority_Queue->pri_Queue[i]);
			break;
		}
	}
}

/*
* dequeues the highest priority pcb from its FIFO queue
*/
PCB * pop_pcb(p_queue * priority_Queue) {
	int i;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		
		if (!isEmpty(priority_Queue->pri_Queue[i])) {		// checks that the current FIFO queue is not empty
			PCB * removed = dequeue(priority_Queue->pri_Queue[i]);	// grabs the value dequeued from the FIFO queue
			return removed;
		}
	}
}

/*
* displays the current iteration of the Priority Queue
* takes an integer to determine if contents of last item should be shown.
*/
void display(p_queue * priority_Queue, int showContents, int queue_count){
	int i;
	for (i = 0; i < PRIORITY_NUMBERS; i++) {
		printf("Q%02d: ", i);
		printQueue(priority_Queue->pri_Queue[i], showContents);    // prints the queues in priority order
	}
}