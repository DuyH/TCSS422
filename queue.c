/*
 *  queue.c
 *
 *  Created on: Jan 11, 2016
 *  Author: Duy Huynh
 *  A linked-list implementation of FIFO queue. Supports enqueue, dequeue, and print queue.
 */

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * Add new node to end of queue list at the rear. An empty list results in the new node being the new head of list.
 *
 * Parameters:	Queue *queue: pointer to head of queue list
 * 				PCB *pcb: pointer to pcb to be added
 */
Queue * enqueue (Queue *queue, PCB *pcb) {

    // Ready a new node to add to list:
    Node *node = malloc(sizeof(Node));
    node->pcb = pcb;
    node->next = NULL;

    // Node becomes head in empty list, otherwise appended to rear.
    if (queue->size == 0) {
        queue->head = node;
        queue->head->next = queue->rear;
    }else {
        queue->rear->next = node; // Update old rear's next to new node.
    }

    // New node always becomes the new rear node
    queue->rear = node;

    // Keep track of list size
    queue->size++;

    return queue;
}
/**
 * Remove and return the head of the queue.
 *
 * Parameters:	Node **head: A pointer to the address of the head of the queue.
 */
PCB * dequeue(Queue *queue) {

    if (queue->size == 0) {
        printf("There was nothing to dequeue\n");
        return NULL;
    } else {
        queue->size--;
        printf("Dequeueing the head which is: %p", queue->head);
        PCB *returnPcb = queue->head->pcb;
        queue->head = queue->head->next;
        return returnPcb;
    }

}

/**
 * Under development!
 */
PCB * peek(Queue *queue) {
	return queue->head->pcb;
}

/**
 * Returns if queue is empty or not.
 */
int isEmpty(Queue *queue) {
    return queue->size; // Returning 0 means empty queue
}

///**
// * Print the content of the queue. The last node of the queue is printed or not depends on the control
// * variable printLastNode
// *
// * Parameters:	Node * head:	A pointer to the head of the queue
// * 				int printLastNode:	A control value to specified whether
// * 									 to print the last node of the queue or not
// */
void printQueue(Queue *queue, int printLastNode) {
    if (queue->size == 0) {
        printf("Nothing in queue to print!\n");
    } else {
        int counter = 1;
        Node *current = queue->head;
        printf("Q: ");
        while (current != NULL) {
            printf("P%d", counter++);
            if (current->next != NULL) printf("->");
            current = current->next;
            if(current == NULL) printf("-*");
        }
        if(printLastNode) {
            printf(" : ");
            toString(queue->rear->pcb);
        }else {
            printf("\n");
        }

    }
}

int main(void) {

    // Instantiate pcb
    PCB pcb;
    toString(&pcb);

    // Populate first pcb with stuff
    create();
    pcb.state = terminated;
    pcb.priority = 12;
    pcb.pid = 1337;
    toString(&pcb);

    // Populate second pcb with stuff
    PCB pcb1;
    pcb1.state = running;
    pcb1.priority = 3;
    pcb1.pid = 32;
    toString(&pcb1);

    // Populate second pcb with stuff
    PCB pcb2;
    pcb2.state = running;
    pcb2.priority = 76;
    pcb2.pid = 129;
    toString(&pcb2);

    // Create a queue
    Queue queue = {NULL, NULL, 0};
    printQueue(&queue, 0);

    // Example of how to enqueue
    printf("Enqueueing pcb\n");
    enqueue(&queue, &pcb);
    toString(queue.head->pcb);
    toString(queue.rear->pcb);

    printf("Enqueueing another pcb\n");
    enqueue(&queue, &pcb1);
    toString(queue.head->pcb);
    toString(queue.rear->pcb);

    printf("Enqueueing another pcb\n");
    enqueue(&queue, &pcb2);
    toString(queue.head->pcb);
    toString(queue.rear->pcb);


    // Example of calling peek
    toString(peek(&queue));
    printQueue(&queue, 0);

    toString(dequeue(&queue));
    toString(dequeue(&queue));
    toString(dequeue(&queue));
    toString(dequeue(&queue));



}

