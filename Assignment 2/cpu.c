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

	//Random integer 0 - 5
	int numb_process = rand() % 6, maxProcess = 30, processes = 0;


	//Create the ready queue
	Queue *readyQueue = malloc(sizeof(Node));

	while (processes <= maxProcess) {
		//Create a list of new processes: 0 - 5 processes
		Queue *newProcess = calloc(numb_process, sizeof(Node));

		processes += numb_process;

		//Initialize new process and put them in a queue
		newProcess = initializeNewQueue(newProcess, numb_process);
		printf("New process initialized: ");
		printQueue(newProcess, 0);


		while (!isEmpty(newProcess)) {
			//Save the system stack
			sysStack = PC;


			PCB *readyPCB = dequeue(newProcess);
			readyPCB->state = ready;

			readyQueue = enqueue(readyQueue, readyPCB);

		}
		printf("Ready queue: ");
		printQueue(readyQueue, 0);
	}

	return 0;
}
