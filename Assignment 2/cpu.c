/***********************************************************************************************
* cpu.c
*
* Programming Team:
* Duy Huynh
* Jeffrey LeCompte
* Trung Dang
* Brandon Scholor
*
* TCSS 422 - Winter 2016
* Date: 1/20/16
* Assignment 2
*
* Description:
* This program represents a CPU in terms of a Round-Robin scheduler, utilizing the PCB and Queue from Assignment 1.
*
************************************************************************************************/

#include "cpu.h"

#define MAX_PROCESS 30
#define STR_LEN 200
#define CPU_CYCLES 100

// File for saving text
FILE *file;
unsigned int CTX_SWITCH_COUNT = 0;

/* CPU Constructor */
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

/* CPU Destructor */

void CPU_destructor(CPU_p cpu) {
    free(cpu);
}

/* CPU Setters */

void CPU_set_pc(CPU_p cpu, unsigned int pc) {
    cpu->pc = pc;
}

void CPU_set_current_process(CPU_p cpu, PCB_p pcb) {
    cpu->currentProcess = pcb;
}

void CPU_set_readyQueue(CPU_p cpu, Queue_p queue) {
    cpu->readyQueue = queue;
}

void CPU_set_terminatedQueue(CPU_p cpu, Queue_p queue) {
    cpu->terminatedQueue = queue;
}

void CPU_set_newProcessesQueue(CPU_p cpu, Queue_p queue) {
    cpu->newProcessesQueue = queue;
}

/* CPU Getters */
unsigned int CPU_get_pc(CPU_p cpu) {
    return cpu->pc;
}

PCB_p CPU_get_current_proc(CPU_p cpu) {
    return cpu->currentProcess;
}

Queue_p CPU_get_readyQueue(CPU_p cpu) {
    return cpu->readyQueue;
}

Queue_p CPU_get_terminatedQueue(CPU_p cpu) {
    return cpu->terminatedQueue;
}

Queue_p CPU_get_newProcessesQueue(CPU_p cpu) {
    return cpu->newProcessesQueue;
}

/* CPU ADT Functions */

Queue_p CPU_enqueue_readyQueue(CPU_p cpu, PCB_p pcb) {
    return Queue_enqueue(CPU_get_readyQueue(cpu), pcb);

}

PCB_p CPU_dequeue_readyQueue(CPU_p cpu) {
    return Queue_dequeue(CPU_get_readyQueue(cpu));
}

Queue_p CPU_enqueue_terminatedQueue(CPU_p cpu, PCB_p pcb) {
    return Queue_enqueue(CPU_get_terminatedQueue(cpu), pcb);
}

PCB_p CPU_dequeue_terminatedQueue(CPU_p cpu) {
    return Queue_dequeue(CPU_get_terminatedQueue(cpu));
}

void CPU_push_sysStack(CPU_p cpu, unsigned int sysStack) {
    cpu->sysStack = sysStack;
}

unsigned int CPU_pop_sysStack(CPU_p cpu) {
    return cpu->sysStack;
}

void CPU_scheduler(CPU_p cpu, Interrupt_type interrupt_type) {
    switch (interrupt_type) {
        case timer:

            // 1. Put process back into the readyQueue
            Queue_enqueue(cpu->readyQueue, cpu->currentProcess);

            // 2. Change its state from interrupted to ready
            PCB_set_state(cpu->currentProcess, ready);

            // 3. Make call to dispatcher
            CPU_dispatcher(cpu);

            // 4. Returned from dispatcher, do any housekeeping
            // Nothing here to do at the moment!

            // 5. Returns to pseudo-ISR
            break;
        default:
            printf("Unknown interrupt type!\n");
            break;
    }
    return;
}

void CPU_dispatcher(CPU_p cpu) {

    // Save pointers to the previous and next process (needed so we can print)
    PCB_p prevProcess = cpu->currentProcess;
    PCB_p nextProcess = Queue_peek(cpu->readyQueue);

    if (CTX_SWITCH_COUNT % 4 == 0) {
        printf("Interrupted Process: %s", PCB_toString(prevProcess));
        printf("Switching to: %s\n", PCB_toString(nextProcess));

        fprintf(file, "Interrupted Process: %s", PCB_toString(prevProcess));
        fprintf(file, "Switching to: %s\n", PCB_toString(nextProcess));
    }

    // 1. Save the state of current process into its PCB (PC value)
    // Per Canvas Discussions, DON'T DO THIS AGAIN HERE! It's in ISR.

    // 2. Then dequeue next waiting process
    cpu->currentProcess = Queue_dequeue(cpu->readyQueue);

    // 3. Change its state to running
    PCB_set_state(cpu->currentProcess, running);

    // 4. Copy its PC value to sysStack, replacing the interrupted process
    cpu->sysStack = PCB_get_PC(cpu->currentProcess);

    if (CTX_SWITCH_COUNT % 4 == 0) {
        printf("Last Process: %s", PCB_toString(prevProcess));
        printf("Current Process: %s", PCB_toString(nextProcess));
        printf("Ready Queue: %s\n\n", Queue_toString(cpu->readyQueue, 0));

        fprintf(file, "Last Process: %s", PCB_toString(prevProcess));
        fprintf(file, "Current Process: %s", PCB_toString(nextProcess));
        fprintf(file, "Ready Queue: %s\n\n", Queue_toString(cpu->readyQueue, 0));
    }

    // 5. Return to the scheduler
    // returns prevalent stuff to scheduler, but not for this project
    return;
}

void CPU_pseudo_isr(CPU_p cpu) {
    // 1. Change the state of the running process to interrupted
    PCB_set_state(cpu->currentProcess, interrupted);

    // 2. Save the CPU state to the PCB
    PCB_set_pc(cpu->currentProcess, cpu->pc);

    // 3. "Do an up-call" to the scheduler
    CPU_scheduler(cpu, timer);
    return;
}

/* Utility Functions */

///**
// * Creates and appends output to a file
// *
// * Parameters: char * string: the string to be added
// */
//void CPU_file_handler(char *string) {
//    FILE *fp;
//    fp = fopen("scheduleTrace.txt", "a+");
//    fputs(string, fp);
//    fclose(fp);
//    return;
//}

/**
 * Removes the text file if already in place
 */
void CPU_remove_file() {
    remove("scheduleTrace.txt");
    return;
}

///**
// * SCHEDULER
// * Fetch a process from the newly created process list and put it
// * in the ready queue to be running.
// */
//Queue_p CPU_fetch_process(CPU_p cpu, Interrupt_type interrupt_type, int printCounter) {
//    PCB_p readyPCB;
//    if (interrupt_type == timer) {
//
//        if (Queue_isEmpty(cpu->newProcessesQueue)) {
//            char noPrint[STR_LEN];
//            sprintf(noPrint, "No process to be scheduled! List is empty.\n");
//            CPU_file_handler(noPrint);
//        } else {
//            char transfer_PCB[STR_LEN];
//            readyPCB = Queue_dequeue(cpu->newProcessesQueue);
//            PCB_set_state(readyPCB, ready);
//
//            cpu->readyQueue = Queue_enqueue(cpu->readyQueue, readyPCB);
//            sprintf(transfer_PCB, "Process transfered to readyQueue: %s", PCB_toString(readyPCB));
//            CPU_file_handler(transfer_PCB);
//
//            if (printCounter % 4 == 0) {
//                char changingProcess[STR_LEN];
//                sprintf(changingProcess, "\nRunning Process: %s Switching To: %s\n", PCB_toString(readyPCB),
//                        PCB_toString(cpu->readyQueue->head->pcb));
//                CPU_file_handler(changingProcess);
//            }
//        }
//    }
//
//    //Dispatcher dequeues a ready process and puts it in running state
//    PCB *runningProcess = dispatch(cpu);
//    if (printCounter % 4 == 0) {
//        char newProcess[STR_LEN];
//        sprintf(newProcess, "Previous Process: %s New Process: %s\n", PCB_toString(readyPCB),
//                PCB_toString(runningProcess));
//        CPU_file_handler(newProcess);
//        CPU_file_handler(Queue_toString(cpu->readyQueue, 0));
//
//    }
//    return cpu->readyQueue;
//}


/**
 * Function that creates 0-5 new processes and puts them into a list.
 */
Queue *CPU_create_processes(Queue *queue, int numb_process, int process_ID) {
    int n;
    for (n = 0; n < numb_process; n++) {
        PCB *pcb = PCB_constructor();
        PCB_set_pid(pcb, process_ID + n);
        PCB_set_priority(pcb, rand() % 31 + 1);
        PCB_set_state(pcb, created);
        queue = Queue_enqueue(queue, pcb);
    }
    return queue;
}

int main() {
    // Prepare for file writing:
    CPU_remove_file();

    // House Keeping:
    file = fopen("scheduleTrace.txt", "w+");
    fprintf(file, "New process initialized: \n");
    srand(time(NULL)); // Seed random generator
    unsigned int PC = rand() % 1001 + 3000;
    int total_procs = 0, process_ID = 1;


    // Create CPU:
    CPU *cpu = CPU_constructor();
    PCB_p empty_pcb; // this is nothing, acts as place holder (non-null value)
    cpu->currentProcess = empty_pcb;

    // CPU: Represent a time quantum. Assumed every process has the same time quantum.
    while (total_procs <= MAX_PROCESS - 5) {

        // 1a. Create a queue of new processes, 0 - 5 processes at a time:
        int num_proc_created = rand() % 6;
        total_procs += num_proc_created;

        cpu->newProcessesQueue = CPU_create_processes(cpu->newProcessesQueue, num_proc_created, process_ID);
        process_ID += num_proc_created;
        // 1b. Print newly created process queue to console:
        printf("Number of new processes created this round: %d, total: %d\n", num_proc_created, total_procs);
        printf("Newly created processes list: ");
        Queue_print(cpu->newProcessesQueue, 0);
        printf("\n");

        // 1c. Print newly created processes queue to file:
        fprintf(file, "Number of new processes created this round: %d, total: %d\n", num_proc_created, total_procs);
        fprintf(file, "Newly created processes list: ");
        fprintf(file, "%s\n", Queue_toString(cpu->newProcessesQueue, 0));

        // Iterate through the newly created processes list until empty:
        while (!Queue_isEmpty(cpu->newProcessesQueue)) {
            PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
            PCB_set_state(temp_pcb, ready);
            Queue_enqueue(cpu->readyQueue, temp_pcb);

            printf("Process ID: %u Enqueued\n", temp_pcb->pid);
            fprintf(file, "Process ID: %u Enqueued\n", temp_pcb->pid);
            fprintf(file, "%s", PCB_toString(temp_pcb));
            fprintf(file, "\n");
        }

        // puts head of readyQueue as current process and changes state to running
        if (cpu->currentProcess == empty_pcb && !Queue_isEmpty(cpu->readyQueue)) {
            cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
            PCB_set_state(cpu->currentProcess, running);
        }

        // calls pseudo ISR
        CPU_pseudo_isr(cpu);

        CTX_SWITCH_COUNT++;
//            // Psuedo-push of the PC to System Stack:
//            // i don't know about this part quite yet - jef
//            cpu->sysStack = PC;
//
//            // Scheduler fetches a process from process list and put to readyQueue
//            cpu->readyQueue = CPU_fetch_process(cpu, timer, ctx_switch_count);
//
//
//            //printf("Ready queue: ");
//            //printf("%s", queue_toString(readyQueue, 0));

//
//
//            // Each time process is scheduled + put into readywueue, print this process + it
//            // Every fourth ctx switch, print contents of running PCB
//            // Print "Switching to: " + contents of head PCB from ready queue
//            // Do the context switch
//            // Print the running PCB again and head PCB from ready queue
//            // Print out the rest of the ready queue
//        }
        //printf("Ready queue: ");
        //printQueue(readyQueue, 0);
    }

    fclose(file);
    CPU_destructor(cpu);
    return 0;
}
