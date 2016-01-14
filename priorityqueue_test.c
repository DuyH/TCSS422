#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

int main() {
	
	//sets up a priority queue
	p_queue * priority_Q = create_pqueue();
	
	// Decide a random number of PCB's to create, from 1-10 pcb's
    srand(time(0));
    int i, n, pNum = 0;


    // Create a number of pcbs, 0-20
    int numPcbs = rand() % 20;
	
	for (i = 0; i < 10; i++) {
		// Creates the PCB's and puts them in the Priority Queue.
		for (n = 0; n < 10; n++) {
			int pNum = rand() % 31;
			PCB * pcb = create();
			pcb->pid = n;
			pcb->priority = pNum;
			pcb->state = new;

			add(priority_Q, pcb);
		}
		
		int dequeue_Count = rand() %2 + 4;
			for (; dequeue_Count > 0; dequeue_Count--) { 
			PCB * removed = pop_pcb(priority_Q);
			toString(removed);
		}
	}
	
	//displays the priority queue
	display(priority_Q);
	
	return 0;
	
}