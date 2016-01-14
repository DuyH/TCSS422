//
// Created by jef on 1/11/16.
//

#include <stdlib.h>
#include <stdio.h>
#include "priorityqueue.h"

#define PRIORITY_NUMBERS 32

//instantiates a priority queue.
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
    // when called from main
    // struct p_queue *ptr = create();
    return thisQueue;
}

void add(p_queue * priority_Queue, PCB *pcb) {
	Node * tempNode = malloc(sizeof(Node));
	//Node * currentNode = priority_Queue->pri_Queue[pcb->priority];
	tempNode->data = pcb;
	//printf("data = %d ", tempNode->data->priority);
	enqueue(priority_Queue->pri_Queue[pcb->priority], tempNode);
	//printf("queue worked: %d\n", priority_Queue->pri_Queue[pcb->priority]->next->data->priority);
}

void check(p_queue * priority_Queue) {
	int i = 0;
	for (i; i < PRIORITY_NUMBERS; i++) {
		
		if ((priority_Queue->pri_Queue[i])->data != NULL) {
			peek(priority_Queue->pri_Queue[i]);
			break;
		}
	}
}

PCB * pop_pcb(p_queue * priority_Queue) {
	int i = 0;
	for (i; i < PRIORITY_NUMBERS; i++) {
		
		if ((priority_Queue->pri_Queue[i])->data != NULL) {
			PCB * removed = dequeue(priority_Queue->pri_Queue[i])->data;
			return removed;
		}
	}
}

void display(p_queue * priority_Queue){
	int i = 0;
	//printf("number of priorities: %d\n", PRIORITY_NUMBERS);
	for (i; i < PRIORITY_NUMBERS; i++) {
		if ((priority_Queue->pri_Queue[i])->next != NULL) {
			printQueue(priority_Queue->pri_Queue[i], 0);
		}
	}
}