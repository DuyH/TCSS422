/*
 * os.c
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */

#include "cpu.h"

/****** DISPATCHER ***********/
PCB * dispatch(Queue *readyQueue) {
    PCB *readyPCB = dequeue(readyQueue);
    readyPCB->state = running;
    sysStack = readyPCB->pc_value;
    return readyPCB;
}

/**
 * SCHEDULER
 * Fetch a process from the newly created process list and put it
 * in the ready queue to be running.
 */
Queue * fetchProcess(Queue *newProcess, Queue *readyQueue) {
    if (isEmpty(newProcess)) {
        printf("No process to be scheduled! List is empty.\n");
    } else {
        PCB *readyPCB = dequeue(newProcess);
        readyPCB->state = ready;
        enqueue(readyQueue, readyPCB);
        printf("Process transfered to readyQueue: ");
        toString(readyPCB);
    }
    return readyQueue;
}


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

int main () {
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

			//Dispatcher dequeues a ready process and puts it in running state
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
