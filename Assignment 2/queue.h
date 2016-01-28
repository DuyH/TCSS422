/*
 *  queue.h
 *
 *  Created on: Jan 11, 2016
 *  Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
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
    int size, counter;
}Queue;

//Example empty Queue creation: Queue queue = {NULL, NULL, 0};

Queue * enqueue (Queue *head, PCB *new);

PCB * dequeue(Queue *head);

PCB * peek(Queue *head);

int isEmpty(Queue *head);

void printQueue(Queue *head, int printLastNode);

char * queue_toString(Queue *head, int printLastNode);

#endif /* QUEUE_H_ */
