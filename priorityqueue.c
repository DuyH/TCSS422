//
// Created by jef on 1/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "priorityqueue.h"

#define PRIORITY_NUMBERS 32		// number of priorities

/*
*instantiates a priority queue.
*/
p_queue * create_pqueue() {
	
	// creates a priority queue with 32 FIFO queues.
	int i = 0;
	p_queue * thisQueue = (p_queue*)malloc(sizeof(p_queue));
	for (i; i < PRIORITY_NUMBERS; i++)
	{
		Node * curNode = malloc(sizeof(Node));
		curNode->data = NULL;
		curNode->next = NULL;
		thisQueue->pri_Queue[i] = curNode;
		
	}

    return thisQueue;
}

/*
* adds a pcb to the Priority Queue
*/
void add(p_queue * priority_Queue, PCB *pcb) {
	Node * tempNode = malloc(sizeof(Node));
	tempNode->data = pcb;			// creates a node that holds the pcb data
	enqueue(priority_Queue->pri_Queue[pcb->priority], tempNode);	// enqueues the new node into the Queue dictated by the pcb priority
}

/*
* checks the next node that will be dequeued without removing it.
*/
void check(p_queue * priority_Queue) {
	int i = 0;
	for (i; i < PRIORITY_NUMBERS; i++) {
		
		if (priority_Queue->pri_Queue[i]->data != NULL) {		//checks if the head contains a pcb
			peek(priority_Queue->pri_Queue[i]);
			break;
		}
	}
}

/*
* dequeues the highest priority pcb from its FIFO queue
*/
PCB * pop_pcb(p_queue * priority_Queue) {
	int i = 0;
	for (i; i < PRIORITY_NUMBERS; i++) {
		
		if ((priority_Queue->pri_Queue[i])->data != NULL) {		// checks that the current FIFO queue is not null
			PCB * removed = dequeue(priority_Queue->pri_Queue[i])->data;	// grabs the value dequeued from the FIFO queue
			return removed;
		}
	}
}

/*
* displays the current iteration of the Priority Queue
*/
void display(p_queue * priority_Queue){
	int i = 0;
	for (i; i < PRIORITY_NUMBERS; i++) {
		if ((priority_Queue->pri_Queue[i])->next != NULL) { // checks if whether there is another node in the queue
			printQueue(priority_Queue->pri_Queue[i], 0);	// prints the queues in priority order
		}
	}
}