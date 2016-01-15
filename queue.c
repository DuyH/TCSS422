/*
 *  queue.c
 *
 *  Created on: Jan 11, 2016
 *  Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 *  A linked-list implementation of FIFO queue. Supports enqueue, dequeue, peek, isEmpty, print queue.
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Add new node to rear of queue. An empty queue results in the new node being the new head.
 * Example call: enqueue(&queue, &pcb);
 *
 * Parameters:	Queue *queue: pointer to head of queue list
 * 				PCB *pcb: pointer to pcb to be added
 * Returns: Pointer to head of Queue.
 */
Queue * enqueue (Queue *queue, PCB *pcb) {

    // Ready a new node to add to list:
    Node *node = malloc(sizeof(Node));
    node->pcb = pcb;
    //node->pcb->pid = queue->counter;
    node->next = NULL;

    // Node becomes head in empty list, otherwise appended to rear.
    queue->size == 0 ? (queue->head = queue->rear = node) : (queue->rear->next = node);

    // New node always becomes the new rear node
    queue->rear = node;

    // Keep track of list size and PID counter
    queue->size++;
    //queue->counter++;

    return queue;
}
/**
 * Remove and return the head of the queue.
 * Example call: dequeue(&queue);
 *
 * Parameters: Queue *queue: A pointer to the head of the queue.
 * Returns: Contents (pcb) of head node.
 */
PCB * dequeue(Queue *queue) {

    if (queue->size == 0) {
        printf("There was nothing to dequeue\n");
        return NULL;
    } else {
        queue->size--;
        PCB *returnPcb = queue->head->pcb;
        queue->head = queue->head->next;
        return returnPcb;
    }

}

/**
 * Returns the contents of the head node of the list without a dequeue.
 * Example call: toString(peek(&queue));
 */
PCB * peek(Queue *queue) {
	return queue->head->pcb;
}

/**
 * Returns if queue is empty or not.
 */
int isEmpty(Queue *queue) {
    return queue->size == 0; // Returning 0 means empty queue
}

/**
 * Prints the content of the queue with the option to include the contents of the last Node in the queue.
 * Example call: printQueue(&queue, 0);
 *
 * Parameters:  Queue * head: A pointer to the head of the queue
 * 				int printLastNode: 1 to print contents of the last Node, 0 to omit.
 */
void printQueue(Queue *queue, int printLastNode) {
    if (queue->size == 0) {
        printf("Nothing in queue to print!\n");
    } else {
        Node *current = queue->head;
        printf("Q: ");
        while (current != NULL) {
            printf("P%d", current->pcb->pid);
            if (current->next != NULL) printf("->");
            current = current->next;
            if(current == NULL) printf("-*");
        }
        if(printLastNode) {
            printf(" contents: ");
            toString(queue->rear->pcb);
        }else {
            printf("\n");
        }
    }
}

