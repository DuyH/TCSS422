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
    int i, n, idNum = 0, pNum = 0, dequeue_Count;
    // Queue count
    int queue_count = 0;
	
	for (i = 0; i < 10; i++) {																// Creates the PCB's and puts them in the Priority Queue.
        queue_count++;
        for (n = 0; n < 10; n++) {
			int pNum = rand() % 32;
			PCB * pcb = create();
			
			pcb->priority = pNum;
			pcb->state = new;

			add(priority_Q, pcb);
			pcb->pid = idNum;
			idNum++;
		}
		
		display(priority_Q, 0, queue_count);												//displays the current state of the priority queue after ten additions
		printf("\n\n");																		//gives gap in display
		
			for (dequeue_Count = rand() %3 + 4; dequeue_Count > 0; dequeue_Count--) {		//creates a loop for a random number between 4 and 6
			PCB * removed = pop_pcb(priority_Q);											//pops a pcb from the priority queue
			toString(removed);																//prints the contents of the removed pcb
			
		}
		printf("\n\n");																		//gives a gap in the display
	}
	
	display(priority_Q, 1, queue_count);													//displays the priority queue
	
	return 0;
	
}