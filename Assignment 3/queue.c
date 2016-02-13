/***********************************************************************************************
 * queue.c
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
 * A linked-list implementation of FIFO queue. Supports enqueue, dequeue, peek, isEmpty, print queue.
 *
 ************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

/**
 * Constructs a Queue object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created Queue object.
 */
Queue_p Queue_constructor() {
    Queue_p queue = calloc(30, sizeof(Queue_p));
    queue->head = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->counter = 0;
    return queue;
}

/**
 * Frees allocated memory used by the Queue object.
 *
 * Parameters:  Queue_p queue: pointer to Queue object.
 */
void Queue_destructor(Queue_p queue) {

    // Free allocated memory for each Node in Queue
    while (queue->head != NULL)
        free(Queue_dequeue(queue));

    // Then free the Queue itself
    free(queue);
}

/**
 * Returns the size of the Queue object.
 *
 * Parameters:  Queue_p queue: pointer to Queue object.
 * Returns:     int size of the Queue object.
 */
int Queue_get_size(Queue_p queue) {
    return queue->size;
}

/**
 * Returns the counter of the Queue object.
 *
 * Parameters:  Queue_p queue: pointer to Queue object.
 * Returns:     int counter of the Queue object.
 */
int Queue_get_counter(Queue_p queue) {
    return queue->counter;
}

/**
 * Add new node to rear of queue. An empty queue results in the new node being the new head.
 * Example call: enqueue(&queue, &pcb);
 *
 * Parameters:  Queue_p queue: pointer to head of queue list
 * 				PCB_p pcb: pointer to pcb to be added
 *
 * Returns:     Pointer to head of Queue.
 */
Queue_p Queue_enqueue(Queue_p queue, PCB_p pcb) {

    // Ready a new node to add to list:
    Node *node = malloc(sizeof(Node));
    node->pcb = pcb;
    //node->pcb->pid = queue->counter;
    node->next = NULL;

    // Node becomes head in empty list, otherwise appended to rear.

    queue->size == 0 ? (queue->head = queue->rear = node) : (queue->rear->next =
                                                                     node);
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
 * Parameters:  Queue_p queue: A pointer to the head of the queue.
 * Returns:     Contents (pcb) of head node.
 */
PCB_p Queue_dequeue(Queue_p queue) {

    if (queue->size == 0) {
        return NULL;
    } else {
        queue->size--;
        PCB_p returnPcb = queue->head->pcb;
        queue->head = queue->head->next;
        //if (queue->size == 0) queue->rear = queue->head;
        return returnPcb;
    }

}

/**
 * Returns the contents of the head node of the list without a dequeue.
 * Example call: toString(peek(&queue));
 *
 * Parameters:  Queue_p queue: pointer to Queue object.
 * Returns:     PCB_p pointer to head Node's PCB in Queue object.
 */
PCB_p Queue_peek(Queue_p queue) {
    if (!Queue_isEmpty(queue))
        return queue->head->pcb;
    else
        return NULL;
}

/**
 * Returns if queue is empty or not.
 *
 * Parameters:  Queue_p queue: pointer to Queue object.
 * Returns:     int 1 if Queue object is empty, 0 if otherwise.
 */
int Queue_isEmpty(Queue_p queue) {
    return queue->size == 0;
}

/**
 * Prints the content of the queue with the option to include the contents of the last Node in the queue.
 * Example call: printQueue(&queue, 0);
 *
 * Parameters:  Queue_p  head: A pointer to the head of the queue
 * 				int printLastNode: 1 to print contents of the last Node, 0 to omit.
 */
void Queue_print(Queue_p queue, int printLastNode) {
    if (queue->size == 0) {
        printf("Queue is empty!\n\n");
    } else {
        Node *current = queue->head;
        while (current != NULL) {
            printf("P%d(%d)", current->pcb->pid, current->pcb->priority);
            if (current->next != NULL)
                printf("->");
            current = current->next;
            if (current == NULL)
                printf("-*");
        }
        if (printLastNode) {
            printf(" contents: ");
            PCB_toString(queue->rear->pcb);;
        } else
            printf("\n");
    }
}

/**
 *Returns the contents of the queue as a string with the option to include the contents of the
 *last Node in the queue.
 *
 *Parameters: Queue_p head: A pointer to the head of the queue
 *Parameters: int printLastNode: 1 to print contents of the last Node, 0 to omit.
 */
char *Queue_toString(Queue_p queue, int printLastNode) {
    char *queue_string = calloc(500, sizeof(char));
    if (queue->size == 0) {
        sprintf(queue_string, "Queue is empty!\n");
    } else {

        char first_part[100];
        Node *current = queue->head;
        while (current != NULL) {
            sprintf(first_part, "P%d(%d)", current->pcb->pid,
                    current->pcb->priority);
            strcat(queue_string, first_part);
            if (current->next != NULL)
                strcat(queue_string, "->");
            else
                strcat(queue_string, "-*");
            current = current->next;

        }
//        if (printLastNode) {
//            strcat(queue_string, " contents: ");
//            sprintf(first_part, "%s", PCB_toString(queue->rear->pcb));
//            strcat(queue_string, first_part);
//        } else {
//
        strcat(queue_string, "\n");
//        }
    }
    return queue_string;
}

