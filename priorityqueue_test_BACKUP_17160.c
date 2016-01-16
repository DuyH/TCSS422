/*
 * priorityqueue_test.c
 *
 * TCSS 422 '16
 * Assignment 1
 * Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 * Testing the implementation of a priority queue for FIFO queues consisting of PCB's.
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityqueue.h"



int main() {

	p_queue * priority_Q = create_pqueue();													//sets up a priority queue

    srand(time(0));
    int i, n, pid = 0, dequeue_Count;
    // Queue count
    int queue_count = 0;
<<<<<<< HEAD
	
<<<<<<< HEAD
	for (i = 0; i < 10; i++) {
		// Creates the PCB's and puts them in the Priority Queue.
		for (n = 0; n < 10; n++) {
			int pNum = rand() % 31;
			printf("random pri: %d ", pNum);
=======
	for (i = 0; i < 10; i++) {																// Creates the PCB's and puts them in the Priority Queue.
        queue_count++;
        for (n = 0; n < 10; n++) {
			int pNum = rand() % 32;
>>>>>>> d0d208b864ccd01f985353463b493cb083ca4c67
=======

	for (i = 0; i < 10; i++) {																// Creates the PCB's and puts them in the Priority Queue.
        queue_count++;
        for (n = 0; n < 10; n++) {
			// Create and add pcb to pqueue
>>>>>>> 3d3f54fb473c8a603ebe987af07041fd46b995cb
			PCB * pcb = create();
			pcb->priority = rand() % 32;; // Assign random priority (0-31 range)
			add(priority_Q, pcb);
<<<<<<< HEAD
<<<<<<< HEAD
			printf("added: %d\n", n);
		}
		printf("works\n");
		int dequeue_Count = rand() %2 + 4;
			for (; dequeue_Count > 0; dequeue_Count--) { 
			
			PCB * removed = pop_pcb(priority_Q);
			//printf("priority: %d\n", removed->priority);
			printf("still Works\n");
			toString(removed);
			printf("not working\n");
=======
			pcb->pid = idNum;
			idNum++;
=======
			pcb->pid = pid++;
>>>>>>> 3d3f54fb473c8a603ebe987af07041fd46b995cb
		}

        // Print off current state of priority queue:
		display(priority_Q, 0, queue_count);												//displays the current state of the priority queue after ten additions
		printf("\n\n");																		//gives gap in display

        // Print off PCB's that have been dequeued:
        printf("PCB's that have been dequeued:\n");
        for (dequeue_Count = rand() %3 + 4; dequeue_Count > 0; dequeue_Count--) {	    	//creates a loop for a random number between 4 and 6
			PCB * removed = pop_pcb(priority_Q);											//pops a pcb from the priority queue
			toString(removed);																//prints the contents of the removed pcb
<<<<<<< HEAD
			
>>>>>>> d0d208b864ccd01f985353463b493cb083ca4c67
=======
>>>>>>> 3d3f54fb473c8a603ebe987af07041fd46b995cb
		}
		printf("\n\n");																		//gives a gap in the display
	}

	display(priority_Q, 1, queue_count);													//displays the priority queue

	return 0;

}