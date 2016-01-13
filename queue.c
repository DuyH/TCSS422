/*
 *  queue.c
 *
 *  Created on: Jan 11, 2016
 *  Author: Trung Dang
 *
 *  A linked-list implementation of FIFO queue. Supports enqueue, dequeue, and print queue.
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Add the specified node to the end of the queue. If the queue is empty (head is NULL),
 * enqueueing will result in the head pointer points to the newNode
 *
 * Parameters:	Node * head: A pointer to the head of the queue
 * 				Node *newNode: A pointer to the new element to be added
 */
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
/**
 * Remove the least recently added element of the queue (the element at the front of the queue)
 *
 * Parameters:	Node **head: A pointer to the address of the head of the queue.
 */
Node * dequeue(Node **head){
	Node * toBeReturned = *head;
	*head = (*head)->next;
	return toBeReturned;
}

/**
 * Under development!
 */
Node * peek(Node *head) {
	return head;
}

/**
 * Print the content of the queue. The last node of the queue is printed or not depends on the control
 * variable printLastNode
 *
 * Parameters:	Node * head:	A pointer to the head of the queue
 * 				int printLastNode:	A control value to specified whether
 * 									 to print the last node of the queue or not
 */
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

