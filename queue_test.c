/*
 * queue_test.c
 *
 *  Created on: Jan 11, 2016
 *      Author: Trung Dang
 *
 *      Testing the implementation of FIFO queue.c file. queue.c is implemented using a linked-list structure.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "queue.h"


/**
 * Test the enqueue function of queue.c. This function also prints out each element of the queue as
 * they are added.
 *
 * Parameters:	Node* head:	A pointer to the head of the queue
 * 				PCB * pcbs:	A pointer to the array of structures of PCB type
 * 				int size  :	The size of the array
 */
Node * testEnqueue(Node *head, PCB *pcbs, int size) {
	printf("Testing enqueue with %d PCBs...\n", size);
	int i = 1, printLastNodeOrNot = 0;
	PCB *p;
	for (p = pcbs; p < pcbs + size; p++ ) {
		Node *newNode = (Node *) malloc(sizeof(Node));
		newNode->data = p;
		head = enqueue(head, newNode);
		printQueue(head, printLastNodeOrNot);
		i++;
	}
	return head;
}
/**
 * Test the dequeue function of queue.c. Dequeue happens at the front of the queue.
 * The content of the element removed will be printed.
 *
 * Parameters:	Node * head: A pointer to the head of the queue
 */
void testDequeue(Node *head) {
	printf("Testing dequeue...\n");
	int printLastNodeOrNot = 1;
	while (head != NULL) {
		Node * result = dequeue(&head);
		printQueue(head, printLastNodeOrNot);
		printf("\n\tcontents: PID %d, Priority %d, State: %s\n", result->data->pid,
				result->data->priority, getStateName(result->data->state));
	}
}
/**
 * Generate elements for an array of PCB structures based on specified size.
 * The rand()%31 function came from a formula on website:
 * http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
 *
 * Parameters:	PCB *pcbs:	A pointer to the array of structures to be generated
 * 				int size:	The size of the array
 */
PCB * createPCBS(PCB *pcbs, int size) {
	int i = 0;
	PCB *p;
	for (p = pcbs; p < pcbs + size; p++) {
		(*p).pid = i;
		i++;
		(*p).priority = rand()%31;
		(*p).state = new;
	}
	return pcbs;
}

/**
 *	Print the content of the array of structures specified in the parameter.
 *
 *	Parameters:	PCB * pcbs:	A pointer to the array of structures to be printed
 *				int size:	The size of the array
 */
void printPCBS(PCB *pcbs, int size) {
	PCB *p;
	int counter = 0;
	for (p = pcbs; p < pcbs + size; p++) {
		printf("\tPCB%d(PID: %d, Priority: %d, State: %s)\n", counter++, (*p).pid, (*p).priority, getStateName((*p).state));
	}
}

/**
 * Main function.
 * The rand()%21 function came from formula on website:
 * //source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
 */
int main() {
	Node *head = NULL;
	srand (time (0));		//Set the rand() to generate a new series each time the program is run
	int pcbs_size = rand()%21;
	PCB * pcbs = calloc(pcbs_size, sizeof(PCB));	//allocate space for an array of PCBs
	createPCBS(pcbs, pcbs_size);
	printf("Queue created: head == %p (NULL)\n", head);
	printf("PCB initialized:\n");
	printPCBS(pcbs, pcbs_size);
	head = testEnqueue(head, pcbs, pcbs_size);
	testDequeue(head);
	return 0;
}
