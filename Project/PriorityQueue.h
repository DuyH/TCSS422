/***********************************************************************************************
 * queue.h
 *
 * Programming Team:
 * Duy Huynh
 * Jeffrey LeCompte
 * Trung Dang
 * Brandon Scholer
 *
 * TCSS 422 - Winter 2016
 * Date: 2/10/16
 * Assignment 3
 *
 * Description:
 * Header defines structures and functions used in implementation of a queue with linked-list data structure.
 *
 ************************************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

#include "pcb.h"

typedef struct node {
    PCB_p pcb;
    struct node *next;
} Node;

typedef struct queue {
    Node *head, *rear;
    int priority, size, counter;
} PQueue;

typedef PQueue *PQueue_p;

/* Queue Constructor */

PQueue_p PQueue_constructor();        // constructs a new queue object in the heap

/* Queue Destructor */

void PQueue_destructor(PQueue_p);        // frees memory allocated to queue object

/* Getters */

int PQueue_get_size(PQueue_p);            // returns the size of this queue

int PQueue_get_counter(PQueue_p);         // returns this queue's counter

/* ADT Functions */

PQueue_p PQueue_enqueue(PQueue_p, PCB_p); // Enqueues a pcb object to a queue object

PCB_p PQueue_dequeue(PQueue_p);       // Dequeues a pcb object from a queue object

PCB_p PQueue_peek(PQueue_p); // Returns a pcb object from a queue object without dequeueing

int PQueue_isEmpty(PQueue_p);           // Returns 1 if queue is empty or 0 if not

/* Utility Functions */

void PQueue_print(PQueue_p, int); // Prints queue; 1: prints last Node, 0: does not print last Node

char *PQueue_toString(PQueue_p, int);    // Returns a character array of the queue

#endif /* QUEUE_H_ */
