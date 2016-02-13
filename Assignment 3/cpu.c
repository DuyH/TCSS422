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
#include <pthread.h>
#include "cpu.h"
#include "timer.h"
#include "io.h"


#define MAX_PROCESS 30
#define STR_LEN 200
#define CPU_CYCLES 100
#define MAX_DEVICES 2
#define MAX_IO_TRAPS 4
#define DEVICE_ARRAY_1 1
#define DEVICE_ARRAY_2 2

// File for saving text
FILE *file;
unsigned int CTX_SWITCH_COUNT = 1;

/* CPU Constructor */
CPU_p CPU_constructor(void) {
    CPU_p cpu = malloc(sizeof(CPU));
    cpu->pc = 0;
    cpu->timer = 0; // TODO: Should this also be a Timer object?
    cpu->sysStack = 0;
    cpu->currentProcess = NULL;
    cpu->readyQueue = calloc(30, sizeof(Queue));
    cpu->terminatedQueue = calloc(30, sizeof(Queue));
    cpu->newProcessesQueue = calloc(30, sizeof(Queue));
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

void CPU_scheduler(CPU_p cpu, Interrupt_type interrupt_type, int PC, IO_p device) {
    while (!Queue_isEmpty(cpu->newProcessesQueue)) {
        PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
        PCB_set_state(temp_pcb, ready);
        //PCB_set_pc(temp_pcb, PC);
        Queue_enqueue(cpu->readyQueue, temp_pcb);
        fprintf(file, "Process ID: %u Enqueued\n", temp_pcb->pid);
        fprintf(file, "%s", PCB_toString(temp_pcb));
    }
    fprintf(file, "\n");
    switch (interrupt_type) {
        case INTERRUPT_TIMER:
            // 1. Put process back into the readyQueue
            Queue_enqueue(cpu->readyQueue, cpu->currentProcess);

            // 2. Change its state from interrupted to ready
            PCB_set_state(cpu->currentProcess, ready);

            // 3. Make call to dispatcher
            CPU_dispatcher(cpu, INTERRUPT_TIMER);

            // 4. Returned from dispatcher, do any housekeeping
            // Nothing here to do at the moment!

            // 5. Returns to pseudo-ISR
            return;
            break;
        case INTERRUPT_IO:
            // 1. Put waiting process into the readyQueue
            Queue_enqueue(cpu->readyQueue, Queue_dequeue(device->waitingQueue));
            break;
        default:
            CPU_dispatcher(cpu, INTERRUPT_NORMAL);
            break;
    }
    return;
}

void CPU_dispatcher(CPU_p cpu, Interrupt_type interrupt_type) {

    // Save pointers to the previous and next process (needed so we can print)
    PCB_p prevProcess = cpu->currentProcess;
    PCB_p nextProcess = Queue_peek(cpu->readyQueue);
    if (CTX_SWITCH_COUNT % 4 == 0) {
    	if (prevProcess != NULL)
    		fprintf(file, "Running process: %s", PCB_toString(prevProcess));
    	if (nextProcess != NULL)
    		fprintf(file, "Switching to: %s", PCB_toString(nextProcess));
    }
    // 1. Save the state of current process into its PCB (PC value)
    // Per Canvas Discussions, DON'T DO THIS AGAIN HERE! It's in ISR.

    // 2. Then dequeue next waiting process
    if (!Queue_isEmpty(cpu->readyQueue))
        cpu->currentProcess = Queue_dequeue(cpu->readyQueue);

    // 3. Change its state to running
    PCB_set_state(cpu->currentProcess, running);

    if (interrupt_type == INTERRUPT_TIMER) {
        // 4. Copy its PC value to sysStack, replacing the interrupted process
        CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));
    } else if (interrupt_type == INTERRUPT_NORMAL) {
        CPU_set_pc(cpu, cpu->sysStack);
    }

    if (CTX_SWITCH_COUNT % 4 == 0) {
    	if (prevProcess != NULL)
    		fprintf(file, "Last Process: %s", PCB_toString(prevProcess));
    	if (nextProcess != NULL)
    		fprintf(file, "Current running Process: %s", PCB_toString(nextProcess));
    	fprintf(file, "Ready Queue: %s", Queue_toString(cpu->readyQueue, 0));
    }

    // 5. Return to the scheduler
    // returns prevalent stuff to scheduler, but not for this project
    return;
}

void CPU_pseudo_isr(CPU_p cpu, Interrupt_type interrupt_type, int PC, IO_p device) {
    if (cpu->currentProcess != NULL) {
        fprintf(file, "Timer interrupt...\n");

        // 1. Change the state of the running process to interrupted
        PCB_set_state(cpu->currentProcess, interrupted);

        // 2. Save the CPU state to the PCB
        PCB_set_pc(cpu->currentProcess, cpu->pc);

        fprintf(file, "Process interrupted: %s",
                PCB_toString(cpu->currentProcess));

        //Replace PC of CPU will value stored in systemStack
        cpu->pc = cpu->sysStack;

        //cpu->pc = CPU_pop_sysStack(cpu);

        // 3. "Do an up-call" to the scheduler
        CPU_scheduler(cpu, interrupt_type, PC, device);

    } else {
        fprintf(file, "No process currently running. Normal interrupt...\n");
        CPU_scheduler(cpu, INTERRUPT_NORMAL, PC, device);
    }

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

/**
 * Function that creates 0-5 new processes and puts them into a list.
 */
Queue *CPU_create_processes(Queue *queue, int numb_process, int process_ID, long int time_count) {
    int n;
    for (n = 0; n < numb_process; n++) {
        PCB *pcb = PCB_constructor();
        PCB_set_pid(pcb, process_ID + n);
        PCB_set_creation(pcb, time_count);
        PCB_set_priority(pcb, rand() % 31 + 1);
        PCB_set_state(pcb, created);
        PCB_set_pc(pcb, rand() % 3000 + 1500);
        queue = Queue_enqueue(queue, pcb);
        fprintf(file, "Process created: PID %d at %ld", PCB_get_pid(pcb), PCB_get_creation(pcb));
    }
    return queue;
}

/**
* Function that checks pending I/O requests. returns 0 if not and 1 if there is
*/
int CPU_check_io_request(PCB_p pcb, int device_num) {
    int PC = PCB_get_PC(pcb);
    int index;
        for (index = 0; index < MAX_IO_TRAPS; index++) {
            int check_request = PCB_get_io_trap_index(pcb, index, device_num);
            if (index < check_request) break;
            else if (index == check_request) return 1;
        }
    return 0;
}

/**
* Function that handles the I/O traps.
*/
void CPU_io_trap_handler(CPU_p cpu, IO_p device) {
    Queue_enqueue(device->waitingQueue, cpu->currentProcess);
    cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
}

int main() {
    // Prepare for file writing:
    CPU_remove_file();

    // House Keeping:
    file = fopen("scheduleTrace.txt", "w+");

    srand(time(0)); // Seed random generator
    unsigned int PC = 0;
    int total_procs = 0, process_ID = 1;
    IO *device_1 = IO_constructor(), *device_2 = IO_constructor();

    Timer_p timer = Timer_constructor(QUANTUM);

    // Create CPU:
    CPU *cpu = CPU_constructor();
    int interrupt, device_1_interrupt, device_2_interrupt, io_request;

    // CPU: Represent an instruction execution.
    long int time_count = 1;

    //total_procs <= MAX_PROCESS - 5
    while (time_count < 100000) {
        fprintf(file, "***************Instruction cycle %lu ***************\n",
                time_count);
        time_count++;

        // 1a. Create a queue of new processes, 0 - 5 processes at a time:
        int num_proc_created = 0;
        do {
        	num_proc_created = rand() % 6;
        } while (total_procs + num_proc_created > MAX_PROCESS);
        fprintf(file, "Process randomed: %d\n", num_proc_created);
        total_procs += num_proc_created;

        cpu->newProcessesQueue = CPU_create_processes(cpu->newProcessesQueue,
                                                      num_proc_created, process_ID, time_count);

        process_ID += num_proc_created;

        // 1c. Print newly created processes queue to file:
        fprintf(file, "New processes initialized: %d. Total processes: %d\n",
                num_proc_created, total_procs);
        fprintf(file, "Newly created processes list: %s",
                Queue_toString(cpu->newProcessesQueue, 0));



        /**** EXECUTION INSTRUCTION ****/
        //Increment PC by 1 to stimulate instruction execution
        PCB_increment_PC(cpu->currentProcess);
        if (PCB_get_PC(cpu->currentProcess) == 0) PCB_increment_term_count(cpu->currentProcess);
        if (PCB_get_terminate(cpu->currentProcess) != 0 &&
                PCB_get_terminate(cpu->currentProcess) == PCB_get_term_count(cpu->currentProcess)) {
                    fprintf(file, "Process terminated: PID %d at ", PCB_get_pid(cpu->currentProcess), time_count);
                    PCB_set_termination(cpu->currentProcess, time_count);
                    CPU_enqueue_terminatedQueue(cpu, cpu->currentProcess);
                    cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
                    continue;
            }

        fprintf(file, "Current PC: %d. System Stack: %d\n", PC, cpu->sysStack);

        if (cpu->currentProcess != NULL)
            CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));

        /**** CHECK FOR TIMER INTERRUPT ****/
        // Timer interrupt if timer is 0, Timer_interrupt returns 1
        if (interrupt == 1) {
        	// calls pseudo ISR
        	CPU_pseudo_isr(cpu, INTERRUPT_TIMER, PCB_get_PC(cpu->currentProcess), NULL);
        }

        fprintf(file, "Current PC: %d. System Stack: %d\n\n", PCB_get_PC(cpu->currentProcess),
                cpu->sysStack);

        CTX_SWITCH_COUNT++;
        interrupt = Timer_countDown(timer);

        /**** CHECK FOR I/O COMPLETION INTERRUPT  ****/
        device_1_interrupt = Timer_countDown(device_1->timer);
        if (device_1_interrupt == 1) CPU_pseudo_isr(cpu, INTERRUPT_IO, PCB_get_PC(cpu->currentProcess), device_1);

        device_2_interrupt = Timer_countDown(device_2->timer);
        if (device_2_interrupt == 1) CPU_pseudo_isr(cpu, INTERRUPT_IO, PCB_get_PC(cpu->currentProcess), device_2);

        /**** CHECK FOR I/O TRAP ****/
        io_request = CPU_check_io_request(cpu->currentProcess, DEVICE_ARRAY_1);
        if (io_request == 1) CPU_io_trap_handler(cpu, device_1);

        io_request = CPU_check_io_request(cpu->currentProcess, DEVICE_ARRAY_2);
        if (io_request == 1) CPU_io_trap_handler(cpu, device_2);
        
    }
    fclose(file);
    CPU_destructor(cpu);
    return 0;
}
