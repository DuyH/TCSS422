/*
 *  cpu.c
 *
 *  Created on: Jan 20, 2016
 *  Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 *  This program represents a CPU in terms of a Round-Robin scheduler, utilizing the PCB and Queue from Assignment 1.
 */

#include "cpu.h"

#define MAX_PROCESS 30
#define STR_LEN 200

/**
 * Creates and appends output to a file
 *
 *Parameters: char * string: the string to be added
 */
void file_handler(char *string) {
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
PCB *dispatch(Queue *ready_Queue) {

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
Queue *fetchProcess(Queue *newProcess, Queue *readyQueue, enum interrupt_state type, int printCounter) {
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
                sprintf(changingProcess, "\nRunning Process: %s Switching To: %s\n", toString(readyPCB),
                        toString(readyQueue->head->pcb));
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


/**
 * Function that creates 0-5 new processes and puts them into a list.
 */
Queue *createNewProcesses(Queue *queue, int numb_process) {
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

int main() {

    // House Keeping before CPU work:
    remove_file();
    srand(time(0)); // Seed random generator
    unsigned int PC = rand() % 1001 + 3000;
    int total_procs, ctx_switch_count = 0;

    // Create the ready queue
    Queue *readyQueue = calloc(1, sizeof(Queue));

    // Create the terminated queue
    Queue *terminatedQueue = calloc(1, sizeof(Queue));

    // Prepare for file writing:
    char process_queue_string[STR_LEN];
    sprintf(process_queue_string, "New process initialized: ");

    // CPU: Represent a time quantum. Assumed every process has the same time quantum.
    while (total_procs <= MAX_PROCESS - 5) {

        // 1a. Create a queue of new processes, 0 - 5 processes at a time:
        int num_proc_created = rand() % 6;
        total_procs += num_proc_created;
        Queue *newProcesses = calloc(1, sizeof(Queue));
        newProcesses = createNewProcesses(newProcesses, num_proc_created);


        // 1b. Print newly created process queue to console:
        printf("Number of new processes created this round: %d, total: %d\n", num_proc_created, total_procs);
        printf("Newly created processes list: ");
        printQueue(newProcesses, 0);
        printf("\n");

        // 1c. Print newly created processes queue to file:
        file_handler(process_queue_string);
        file_handler(queue_toString(newProcesses, 0));


        // Iterate through the newly created processes list until empty:
        while (!isEmpty(newProcesses)) {

            //Save the system stack
            sysStack = PC;

            //Scheduler fetches a process from process list and put to readyQueue
            readyQueue = fetchProcess(newProcesses, readyQueue, timer, ctx_switch_count);
            //printf("Ready queue: ");
            //printf("%s", queue_toString(readyQueue, 0));
            ctx_switch_count++;
        }
        //printf("Ready queue: ");
        //printQueue(readyQueue, 0);
    }

    return 0;
}
