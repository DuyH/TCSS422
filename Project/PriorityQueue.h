//
// Created by jef on 1/11/16.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "pcb.h"
#include "queue.h"

typedef struct p_queue {
    Queue * pri_Queue[4];
    int size;
} p_queue;

typedef p_queue * PQueue_p;

/* Queue Constructor */

PQueue_p PQueue_constructor();        // constructs a new queue object in the heap

/* Queue Destructor */

void PQueue_destructor(PQueue_p);        // frees memory allocated to queue object

/* Getters */

int PQueue_p_get_size(PQueue_p);            // returns the size of this queue

int PQueue_p_get_counter(PQueue_p);         // returns this queue's counter

/* ADT Functions */

PQueue_p PQueue_enqueue(PQueue_p, PCB_p); // Enqueues a pcb object to a queue object

PCB_p PQueue_dequeue(PQueue_p);       // Dequeues a pcb object from a queue object

PCB_p PQueue_peek(PQueue_p); // Returns a pcb object from a queue object without dequeueing

int PQueue_isEmpty(PQueue_p);           // Returns 1 if queue is empty or 0 if not

/* Utility Functions */

void PQueue_print(PQueue_p, int); // Prints queue; 1: prints last Node, 0: does not print last Node

char *PQueue_toString(PQueue_p, int);    // Returns a character array of the queue


#endif /* PRIORITYQUEUE_H */
