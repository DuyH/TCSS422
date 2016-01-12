/*
 * queue.c
 *
 *  Created on: Jan 11, 2016
 *      Author: trung
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"


Node * enqueue (Node *head, Node *newNode){
	Node *curr;
	if (head != NULL) {
		curr = head;
		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = newNode;
	} else {
		head = newNode;
	}
	return head;
}

Node * dequeue(Node **head){
	Node * toBeReturned = *head;
	//Node * newHead;
	*head = (*head)->next;
	return toBeReturned;
}

Node * peek(Node *head) {
	return head;
}

void printQueue(Node *head, int printLastNode) {
	Node *curr, * prev;
	int counter = 1;
	curr = head;
	prev = NULL;
	printf("\tQueue: ");
	while (curr != NULL){
		printf("P%d->", counter);
		counter++;
		prev = curr;
		curr = curr->next;
		if (curr == NULL) printf("-*");
	}
	if (printLastNode == 0) toString(prev->data);
}

