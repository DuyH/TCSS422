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
 * CPU Constructor:
 */
CPU_p CPU_constructor(void) {
    CPU_p cpu = malloc(sizeof(CPU));
    cpu->pc = 0;
    cpu->sysStack = 0;
    cpu->currentProcess = NULL;
    cpu->readyQueue = calloc(1, sizeof(Queue));
    cpu->terminatedQueue = calloc(1, sizeof(Queue));
    cpu->newProcessesQueue = calloc(1, sizeof(Queue));
    return cpu;
}




/**
 * Creates and appends output to a file
 *
 * Parameters: char * string: the string to be added
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
PCB *dispatch(CPU_p cpu) {

    PCB *currentPCB = Queue_dequeue(cpu->readyQueue);
    if (currentPCB != NULL) {
        currentPCB->state = running;
        cpu->sysStack = currentPCB->pc_value;
    }

    return currentPCB;
}

/**
 * SCHEDULER
 * Fetch a process from the newly created process list and put it
 * in the ready queue to be running.
 */
Queue *fetchProcess(CPU_p cpu, State state_type, int printCounter) {
    PCB *readyPCB;
    if (state_type == timer) {

        if (Queue_isEmpty(cpu->newProcessesQueue)) {
            char noPrint[STR_LEN];
            sprintf(noPrint, "No process to be scheduled! List is empty.\n");
            file_handler(noPrint);
        } else {
            char transfer_PCB[STR_LEN];
            readyPCB = Queue_dequeue(cpu->newProcessesQueue);
            readyPCB->state = ready;

            cpu->readyQueue = Queue_enqueue(cpu->readyQueue, readyPCB);
            sprintf(transfer_PCB, "Process transfered to readyQueue: %s", PCB_toString(readyPCB));
            file_handler(transfer_PCB);

            if (printCounter % 4 == 0) {
                char changingProcess[STR_LEN];
                sprintf(changingProcess, "\nRunning Process: %s Switching To: %s\n", PCB_toString(readyPCB),
                        PCB_toString(cpu->readyQueue->head->pcb));
                file_handler(changingProcess);
            }
        }
    }

    //Dispatcher dequeues a ready process and puts it in running state
    PCB *runningProcess = dispatch(cpu);
    if (printCounter % 4 == 0) {
        char newProcess[STR_LEN];
        sprintf(newProcess, "Previous Process: %s New Process: %s\n", PCB_toString(readyPCB), PCB_toString(runningProcess));
        file_handler(newProcess);
        file_handler(queue_toString(cpu->readyQueue, 0));

    }
    return cpu->readyQueue;
}


/**
 * Function that creates 0-5 new processes and puts them into a list.
 */
Queue *createNewProcesses(Queue *queue, int numb_process) {
    int n;
    for (n = 0; n < numb_process; n++) {
        PCB *pcb = PCB_constructor();
        pcb->pid = n + 1; // Start with PID: 01
        pcb->priority = rand() % 31 + 1;
        pcb->state = created;
        queue = Queue_enqueue(queue, pcb);
    }
    return queue;
}

int main() {

    // House Keeping:
    srand(time(0)); // Seed random generator
    unsigned int PC = rand() % 1001 + 3000;
    int total_procs, ctx_switch_count = 0;


    // Create CPU:
    CPU *cpu = CPU_constructor();

    // Prepare for file writing:
    remove_file();
    char process_queue_string[STR_LEN];
    sprintf(process_queue_string, "New process initialized: ");

    // CPU: Represent a time quantum. Assumed every process has the same time quantum.
    while (total_procs <= MAX_PROCESS - 5) {

        // 1a. Create a queue of new processes, 0 - 5 processes at a time:
        int num_proc_created = rand() % 6;
        total_procs += num_proc_created;
        cpu->newProcessesQueue = createNewProcesses(cpu->newProcessesQueue, num_proc_created);


        // 1b. Print newly created process queue to console:
        printf("Number of new processes created this round: %d, total: %d\n", num_proc_created, total_procs);
        printf("Newly created processes list: ");
        Queue_print(cpu->newProcessesQueue, 0);
        printf("\n");

        // 1c. Print newly created processes queue to file:
        file_handler(process_queue_string);
        file_handler(queue_toString(cpu->newProcessesQueue, 0));


        // Iterate through the newly created processes list until empty:
        while (!Queue_isEmpty(cpu->newProcessesQueue)) {

            // Psuedo-push of the PC to System Stack:
            cpu->sysStack = PC;

            //Scheduler fetches a process from process list and put to readyQueue
            cpu->readyQueue = fetchProcess(cpu, timer, ctx_switch_count);
            //printf("Ready queue: ");
            //printf("%s", queue_toString(readyQueue, 0));
            ctx_switch_count++;


            // Each time process is scheduled + put into readywueue, print this process + it
            // Every fourth ctx switch, print contents of running PCB
            // Print "Switching to: " + contents of head PCB from ready queue
            // Do the context switch
            // Print the running PCB again and head PCB from ready queue
            // Print out the rest of the ready queue
        }
        //printf("Ready queue: ");
        //printQueue(readyQueue, 0);
    }

    return 0;
}
