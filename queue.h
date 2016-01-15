/*
 * queue.h
 *
 *  Created on: Jan 11, 2016
 *      Author: Duy Huynh
 *
 *  Header defines structures and functions used in implementation of a queue with linked-list data structure.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

typedef struct node {
    PCB *pcb;
    struct node *next;
}Node;

typedef struct queue {
    Node *head, *rear;
    int size;
}Queue;

Queue * enqueue (Queue *head, PCB *new);

PCB * dequeue(Queue *head);

PCB * peek(Queue *head);

int isEmpty(Queue *head);

void printQueue(Queue *head, int printLastNode);

#endif /* QUEUE_H_ */
