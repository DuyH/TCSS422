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
#include <stdbool.h>
#include <string.h>
#include "queue.h"

/**
 * Add new node to rear of queue. An empty queue results in the new node being the new head.
 * Example call: enqueue(&queue, &pcb);
 *
 * Parameters:	Queue *queue: pointer to head of queue list
 * 				PCB *pcb: pointer to pcb to be added
 * Returns: Pointer to head of Queue.
 */
Queue *Queue_enqueue(Queue *queue, PCB *pcb) {

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
PCB *Queue_dequeue(Queue *queue) {

    if (queue->size == 0) {
        printf("There was nothing to dequeue\n");
        return NULL;
    } else {
        queue->size--;
        PCB *returnPcb = queue->head->pcb;
        queue->head = queue->head->next;
        //if (queue->size == 0) queue->rear = queue->head;
        return returnPcb;
    }

}

/**
 * Returns the contents of the head node of the list without a dequeue.
 * Example call: toString(peek(&queue));
 */
PCB *Queue_peek(Queue *queue) {
	return queue->head->pcb;
}

/**
 * Returns if queue is empty or not.
 */
int Queue_isEmpty(Queue *queue) {
    return queue->size == 0;
}

/**
 * Prints the content of the queue with the option to include the contents of the last Node in the queue.
 * Example call: printQueue(&queue, 0);
 *
 * Parameters:  Queue * head: A pointer to the head of the queue
 * 				int printLastNode: 1 to print contents of the last Node, 0 to omit.
 */
void Queue_print(Queue *queue, int printLastNode) {
    if (queue->size == 0) {
        printf("Queue is empty!\n");
    } else {
        Node *current = queue->head;
        while (current != NULL) {
            printf("P%d(%d)", current->pcb->pid, current->pcb->priority);
            if (current->next != NULL) printf("->");
            current = current->next;
            if(current == NULL) printf("-*");
        }
        if(printLastNode) {
            printf(" contents: ");
            PCB_toString(queue->rear->pcb);
        }else printf("\n");
    }
}
 
/**
 *Returns the contents of the queue as a string with the option to include the contents of the
 *last Node in the queue.
 *
 *Parameters: Queue *head: A pointer to the head of the queue
 *Parameters: int printLastNode: 1 to print contents of the last Node, 0 to omit.
 */
char * queue_toString(Queue *queue, int printLastNode) {
    static char queue_string[500];
    if (queue->size == 0) {
        sprintf(queue_string, "Queue is empty!\n");
    } else {
        
        char first_part[50], second_part[50], third_part[50], fourth_part[50], fifth_part[50];
        Node *current = queue->head;
        while (current != NULL) {
            sprintf(first_part, "P%d(%d)", current->pcb->pid, current->pcb->priority);
            strcat(queue_string, first_part);
            if (current->next != NULL) strcat(queue_string, "->");
            current = current->next;
            if(current == NULL) strcat(queue_string, "-*");
        }
        if(printLastNode) {
            strcat(queue_string, " contents: ");
            sprintf(fifth_part, "%s", PCB_toString(queue->rear->pcb));
            strcat(queue_string, fifth_part);
        }else {
            
            strcat(queue_string, "\n");
        }
    }
    return queue_string;
}

