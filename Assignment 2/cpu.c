/*
 * os.c
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

/*
 * Global variable for frame pointer
 */
int sysStack;

Queue * initializeNewQueue(Queue * queue, int numb_process) {
	int n;
	    for (n = 0; n < numb_process; n++) {
	        PCB *pcb = create();
	        pcb->pid = n + 1; // Start with PID: 01
	        pcb->priority = rand() % 31 + 1;
	        pcb->state = created;
	        queue = enqueue(queue, pcb);
	    }
	return queue;
}


int main (){

	srand(time(0));
	unsigned int PC = random() % 1001 + 3000;
	int terminated = 0;
	//Random integer 0 - 5
	int numb_process = rand() % 6;

	//Create a list of new processes: 0 - 5 processes
	Queue *newProcess = calloc(numb_process, sizeof(Node));

	//Create the ready queue
	Queue *readyQueue = malloc(sizeof(Node));

	do {
		//Initialize new process and put them in a queue
		newProcess = initializeNewQueue(newProcess, numb_process);
		printQueue(newProcess, 0);


		while (!isEmpty(newProcess)) {
			//Save the system stack
			sysStack = PC;


			PCB *readyPCB = dequeue(newProcess);
			readyPCB->state = ready;
			readyQueue = enqueue(readyQueue, readyPCB);
			printQueue(readyQueue, 0);
		}

	} while (terminated);

	return 0;
}
