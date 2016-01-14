/*
 * queue.h
 *
 *  Created on: Jan 11, 2016
 *      Author: Trung Dang
 *
 *  Header defines structures and functions used in implementation of a queue with linked-list data structure.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

typedef struct node_type {
	PCB * data;
	struct node_type *next;
}Node;

Node * enqueue (Node *head, Node *new);

Node * dequeue(Node *head);

Node * peek(Node *head);

void printQueue(Node *head, int printLastNode);

#endif /* QUEUE_H_ */
