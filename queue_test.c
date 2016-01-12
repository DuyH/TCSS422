/*
 * queue_test.c
 *
 *  Created on: Jan 11, 2016
 *      Author: trung
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "queue.h"

Node * initializeQueue (Node * head){
	Node *curr = head;
	if (curr == NULL ) {
		Node * headNode = (Node *) malloc(sizeof(Node));
		PCB * pcb = (PCB *)malloc (sizeof(PCB));
		pcb->pid = 0;
		pcb->priority = rand()%(32); //source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
		pcb->state = new;
		headNode->data = pcb;
		curr = headNode;

		int i;
		int number_pcb = rand()%21; //source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
		for (i = 1; i <= number_pcb; i++) {
			Node *newNode = (Node *) malloc(sizeof(Node));
			PCB *new_pcb =  (PCB *) malloc(sizeof(PCB));
			new_pcb->pid = i;
			new_pcb->priority = rand()%31;	//source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
			new_pcb->state = new;
			newNode->data = new_pcb;
			curr = enqueue(curr, newNode);
			//if (i == 1) printQueue(head, 0);
			//else printQueue(head, 1);
		}
	}
	head = curr;
	return head;
}

Node * testEnqueue(Node *head, PCB *pcbs, int size) {
	printf("Testing enqueue with %d PCBs...\n", size);
	int i = 1;
	PCB *p;
	for (p = pcbs; p < pcbs + size; p++ ) {
		Node *newNode = (Node *) malloc(sizeof(Node));
		newNode->data = p;
		head = enqueue(head, newNode);
		printQueue(head, 0);
		i++;
	}
	return head;
}
void testDequeue(Node *head) {
	printf("Testing dequeue...\n");
	//Node *curr = head;
	while (head != NULL) {
		Node * result = dequeue(&head);
//		Node *temp = (Node *) malloc(sizeof(Node));
//		temp->data->pid = result->data->pid;
//		temp->data->priority = result->data->priority;
//		temp->data->state = result->data->state;
		printQueue(head, 1);
//		printf("\ncontents: PID %d, Priority %d, State: %s\n", temp->data->pid,
//						temp->data->priority, getStateName(temp->data->state));
		printf("\n\tcontents: PID %d, Priority %d, State: %s\n", result->data->pid,
				result->data->priority, getStateName(result->data->state));

	}
}
PCB * createPCBS(PCB *pcbs, int size) {
	int i = 0;
	PCB *p;
	//PCB *curr = pcbs;;
	for (p = pcbs; p < pcbs + size; p++) {
		(*p).pid = i;
		i++;
		(*p).priority = rand()%31;	//source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
		(*p).state = new;
	}
	//pcbs = curr;
	return pcbs;
}

void printPCBS(PCB *pcbs, int size) {
	PCB *p;
	int counter = 0;
	for (p = pcbs; p < pcbs + size; p++) {
		printf("\tPCB%d(PID: %d, Priority: %d, State: %s)\n", counter++, (*p).pid, (*p).priority, getStateName((*p).state));
	}
}
int main() {
	Node *head = NULL;
	//Node *head2 = NULL;
	srand (time (0));
	int pcbs_size = 4;//rand()%21;
	PCB * pcbs = calloc(pcbs_size, sizeof(PCB));
	createPCBS(pcbs, pcbs_size);
	printf("Queue created: head == %p (NULL)\n", head);
	printf("PCB initialized:\n");
	printPCBS(pcbs, pcbs_size);
	//printQueue("Queue initialized: %");
	head = testEnqueue(head, pcbs, pcbs_size);
	testDequeue(head);

	return 0;
}
