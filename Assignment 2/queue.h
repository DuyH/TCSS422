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
* Date: 1/20/16
* Assignment 2
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
    int size, counter;
} Queue;

typedef Queue *Queue_p;

/* Queue Constructor */
Queue_p Queue_constructor();            // constructs a new queue object in the heap

/* Queue Destructor */
void Queue_destructor(Queue_p);         // frees memory allocated to queue object

/* Setters */

void Queue_set_head(Queue_p, PCB_p);    // sets this->head to pcb

void Queue_set_rear(Queue_p, PCB_p);    // sets this->rear to pcb

void Queue_set_size(Queue_p, int);      // sets this->size to int value

void Queue_set_counter(Queue_p, int);   // sets this->counter to int value

/* Getters */

PCB_p Queue_get_head(Queue_p);          // returns this queue's head value, a pcb

PCB_p Queue_get_rear(Queue_p);          // returns this queue's rear value, a pcb

int Queue_get_size(Queue_p);            // returns the size of this queue

int Queue_get_counter(Queue_p);         // returns this queue's counter

/* ADT Functions */

Queue_p Queue_enqueue(Queue_p, PCB_p);  // Enqueues a pcb object to a queue object

PCB_p Queue_dequeue(Queue_p);           // Dequeues a pcb object from a queue object

PCB_p Queue_peek(Queue_p);              // Returns a pcb object from a queue object without dequeueing

int Queue_isEmpty(Queue_p);             // Returns 1 if queue is empty or 0 if not

/* Utility Functions */

void Queue_print(Queue_p, int);         // Prints queue; 1: prints last Node, 0: does not print last Node

char *Queue_toString(Queue_p, int);    // Returns a character array of the queue

#endif /* QUEUE_H_ */
