/*
 * queue.h
 *
 *  Created on: Jan 11, 2016
 *      Author: trung
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

typedef struct node_type {
	PCB * data;
	struct node_type *next;
}Node;

void enqueue (Node *head);

Node * dequeue(Node *head);

Node * peek(Node *head);

#endif /* QUEUE_H_ */
