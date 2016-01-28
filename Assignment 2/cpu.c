/*
 * os.c
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */

#include "cpu.h"

#define STR_LEN 200

/**
 * Creates and appends output to a file
 *
 *Parameters: char * string: the string to be added
 */
void file_handler(char * string){
    FILE *fp;
    fp = fopen("scheduleTrace.txt", "a+");
    fputs(string, fp);
    fclose(fp);
}

/**
 * Removes the text file if already in place
 */
void remove_file() {
    remove("scheduleTrace.txt");
}

/****** DISPATCHER ***********/
PCB * dispatch(Queue *ready_Queue) {
    
    PCB *currentPCB = dequeue(ready_Queue);
    if (currentPCB != NULL) {
    currentPCB->state = running;
    sysStack = currentPCB->pc_value;
    }
    
    return currentPCB;
}

/**
 * SCHEDULER
 * Fetch a process from the newly created process list and put it
 * in the ready queue to be running.
 */
Queue * fetchProcess(Queue *newProcess, Queue *readyQueue, enum interrupt_state type, int printCounter) {
    PCB *readyPCB;
    if (type == timer) {
        
        if (isEmpty(newProcess)) {
            char noPrint[STR_LEN];
            sprintf(noPrint, "No process to be scheduled! List is empty.\n");
            file_handler(noPrint);
        } else {
            char transfer_PCB[STR_LEN];
            readyPCB = dequeue(newProcess);
            readyPCB->state = ready;
            
            readyQueue = enqueue(readyQueue, readyPCB);
            sprintf(transfer_PCB, "Process transfered to readyQueue: %s", toString(readyPCB));
            file_handler(transfer_PCB);
        
            if (printCounter % 4 == 0) {
                char changingProcess[STR_LEN];
                sprintf(changingProcess, "\nRunning Process: %s Switching To: %s\n", toString(readyPCB), toString(readyQueue->head->pcb));
                file_handler(changingProcess);
            }
        }
    }
    
    //Dispatcher dequeues a ready process and puts it in running state
    PCB *runningProcess = dispatch(readyQueue);
    if (printCounter % 4 == 0) {
        char newProcess[STR_LEN];
        sprintf(newProcess, "Previous Process: %s New Process: %s\n", toString(readyPCB), toString(runningProcess));
        file_handler(newProcess);
        file_handler(queue_toString(readyQueue, 0));
            
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
    remove_file();
	srand(time(0));
	unsigned int PC = rand() % 1001 + 3000;
    int maxProcess = 30, processes = 0;
    int printCounter = 0;


	//Create the ready queue
	Queue *readyQueue = calloc(1, sizeof(Queue));

    char process_queue_string[STR_LEN];
	sprintf(process_queue_string, "New process initialized: ");
	//Represent a time quantum. Assumed every process has the same time quantum.
	while (processes <= maxProcess) {
		//Random integer 0 - 5
		int numb_process = rand() % 6 +1;

		//Create a list of new processes: 0 - 5 processes
		Queue *newProcess = calloc(1, sizeof(Queue));

		processes += numb_process;

		//Initialize new process and put them in a queue
		newProcess = initializeNewQueue(newProcess, numb_process);
        file_handler(process_queue_string);
		file_handler(queue_toString(newProcess, 0));

		while (!isEmpty(newProcess)) {
			//Save the system stack
			sysStack = PC;

			//Scheduler fetches a process from process list and put to readyQueue
			readyQueue = fetchProcess(newProcess, readyQueue, timer, printCounter);
			//printf("Ready queue: ");
			//printf("%s", queue_toString(readyQueue, 0));
            printCounter++;
		}
		//printf("Ready queue: ");
		//printQueue(readyQueue, 0);
	}

	return 0;
}
