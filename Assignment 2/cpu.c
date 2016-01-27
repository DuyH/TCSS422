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
#include "scheduler.h"
#include "dispatcher.h"


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


    int maxProcess = 30, processes = 0;


	//Create the ready queue
	Queue *readyQueue = malloc(sizeof(Node));

	//Represent a time quantum. Assumed every process has the same time quantum.
	while (processes <= maxProcess) {

		//Random integer 0 - 5
		int numb_process = rand() % 6;

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

			//Scheduler fetches a process from process list and put to readyQueue
			readyQueue = fetchProcess(newProcess, readyQueue);
			printf("Ready queue: ");
			printQueue(readyQueue,0);

			//Dispatcher dequeues a ready process and put it in running state
			PCB *runningProcess = dispatch(readyQueue);
			printf("Running process: ");
			toString(runningProcess);
			printf("ReadyQueue after dispatched: ");
			printQueue(readyQueue, 0);



		}
		//printf("Ready queue: ");
		//printQueue(readyQueue, 0);
	}

	return 0;
}
