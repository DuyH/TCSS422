/*
 *  queue_test.c
 *
 *  Created on: Jan 11, 2016
 *  Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 *  Testing the implementation of FIFO queue.c file. queue.c is implemented using a linked-list structure.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "queue.h"


/**
 * Test the enqueue function of queue.c. This function also prints out each element of the queue as
 * they are added.
 *
 * Parameters:	Queue* queue:	A pointer to the head of the queue
 * 				PCB *pcbs: array of PCB's
 *              int numPcbs: Number of PCB's to be created
 */
void testEnqueue(Queue *queue, PCB *pcbs, int numPcbs) {
    printf("Testing enqueue with %d PCBs...\n", numPcbs);
    for (int n = 0; n < numPcbs; n++) printQueue(enqueue(queue, &pcbs[n]), 1);
}

/**
 * Test the dequeue function of queue.c. Dequeue happens at the front of the queue.
 * The content of the element removed will be printed.
 *
 * Parameters:	Queue * queue: A pointer to the head of the queue
 */
void testDequeue(Queue *queue) {
    printf("Testing dequeue...\n");
    while (queue != NULL) {
        printQueue(queue, 0);
        PCB *pcb = dequeue(queue);
        printQueue(queue, 0);
        toString(pcb);
    }
}

/**
 * Test peek function of queue.c, returning the head of queue without a dequeue.
 *
 * Parameters: Queue* queue: A pointer to the head of the queue
 * Returns: PCB pcb, the head of queue
 */
void testPeek(Queue *queue) {
    printf("Testing peek...\n");
    printf("Queue before peek:\n");
    printQueue(queue, 0);
    printf("Peeking: ");
    toString(peek(queue));
    printf("Queue after peek:\n");
    printQueue(queue, 0);
}

/**
 * Generate elements for an array of PCB structures based on specified size.
 * The rand()%31 + 0 function came from a formula on website:
 * http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
 *
 * Parameters:  PCB pcbs[]: array of PCB's
 *              int numPcbs: Number of PCB's to be created
 */
void createPCBS(PCB pcbs[], int numPcbs) {
    // Initialize each PCB with random priority (0-31 range)
    for (int n = 0; n < numPcbs; n++) {
        PCB *pcb = create();
        pcb->pid = n + 1; // Start with PID: 01
        pcb->priority = rand() % 31 + 1;
        pcbs[n] = *pcb;
        toString(pcb);
    }
}

/**
 * Main function.
 * The rand()%21 + 10 function came from formula on website:
 * //source: http://www.dreamincode.net/forums/topic/69684-how-to-use-rand-in-a-certain-range-of-numbers/
 */
int main() {

    // Create Queue and display to console:
    Queue *queue = calloc(1, sizeof(Queue));
    printf("Queue created: head == %p (NULL)\n\n", queue->head);

    // Create PCBs and display to console:
    srand((unsigned int)time(NULL)); // Random seed
    int numPcbs = rand() % 21 + 10; // Range 10-30 PCB's
    PCB *pcbs = malloc(numPcbs * sizeof(PCB));
    printf("%d PCB's initialized:\n", numPcbs);
    printf("=====================\n");
    createPCBS(pcbs, numPcbs);
    printf("\n");

    // Testing isEmpty before adding to queue:
    printf("Testing isEmpty function: \n");
    printf("Is the queue empty? (1 indicates empty): %d\n", isEmpty(queue));
    printf("\n");

    // Enqueue the array of PCB's and display to console:
    testEnqueue(queue, pcbs, numPcbs);
    printf("\n");

    // Testing isEmpty after populating queue:
    printf("Testing isEmpty function: \n");
    printf("Is the queue empty? (1 indicates empty): %d\n", isEmpty(queue));
    printf("\n");

    // Peek at the queue and print queue again to ensure head is still there:
    testPeek(queue);
    printf("\n");

    // Deqeueue the array of PCB's and display to console:
    testDequeue(queue);
    printf("\n");

    printf("Finished Tests");

    return 0;
}
