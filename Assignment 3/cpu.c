/***********************************************************************************************
 * cpu.c
 *
 * Programming Team:
 * Duy Huynh
 * Jeffrey LeCompte
 * Trung Dang
 * Brandon Scholer
 *
 * TCSS 422 - Winter 2016
 * Date: 2/12/16
 * Assignment 3
 *
 * Description:
 * This program represents a CPU in terms of a Round-Robin scheduler, utilizing the PCB and Queue from Assignment 1.
 *
 ************************************************************************************************/

#include "cpu.h"

#define MAX_PROCESS 30
#define MAX_IO_TRAPS 4
#define DEVICE_ARRAY_1 1
#define DEVICE_ARRAY_2 2

// File for saving text
FILE *file;
//unsigned int CTX_SWITCH_COUNT = 1;

/* CPU Constructor */
CPU_p CPU_constructor(void) {
    CPU_p cpu = (CPU_p) malloc(sizeof(CPU));
    cpu->pc = 0;
    cpu->timer = Timer_constructor(QUANTUM);
    cpu->sysStack = 0;
    cpu->currentProcess = NULL;
    cpu->readyQueue = Queue_constructor();
    cpu->terminatedQueue = Queue_constructor();
    cpu->newProcessesQueue = Queue_constructor();
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
    printf("INTERRUPT: %u\n", interrupt_type);
    switch (interrupt_type) {
        case INTERRUPT_TIMER:
            // 1. Put process back into the readyQueue
            Queue_enqueue(cpu->readyQueue, cpu->currentProcess);

            // 2. Change its state from interrupted to ready
            PCB_set_state(cpu->currentProcess, ready);

            // 3. Make call to dispatcher
            CPU_dispatcher(cpu, INTERRUPT_TIMER);

            fprintf(file, "PID %d is running, ", cpu->currentProcess->pid);
            fprintf(file, "PID %d put in ready queue\n", cpu->readyQueue->head->pcb->pid);
            printf("PID %d is running, ", cpu->currentProcess->pid);
            printf("PID %d put in ready queue\n", cpu->readyQueue->head->pcb->pid);

            // 4. Returned from dispatcher, do any housekeeping
            // Nothing here to do at the moment!

            // 5. Returns to pseudo-ISR
            break;
        case INTERRUPT_IO:
            // 1. Put waiting process into the readyQueue
            Queue_enqueue(cpu->readyQueue, Queue_dequeue(device->waitingQueue));

            fprintf(file, "I/O completion interrupt: PID %d is running, ", cpu->currentProcess->pid);
            fprintf(file, "PID %d in ready queue\n", device->waitingQueue->head->pcb->pid);
            printf("I/O completion interrupt: PID %d is running, ", cpu->currentProcess->pid);
            printf("PID %d in ready queue\n", device->waitingQueue->head->pcb->pid);
            break;
        default:
            CPU_dispatcher(cpu, INTERRUPT_NORMAL);
            break;
    }
    fprintf(file, "\n");
    printf("\n");
    return;
}

void CPU_dispatcher(CPU_p cpu, Interrupt_type interrupt_type) {
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
    }

    // 5. Return to the scheduler
    // returns prevalent stuff to scheduler, but not for this project
    return;
}

void CPU_pseudo_isr(CPU_p cpu, Interrupt_type interrupt_type, int PC, IO_p device) {

        // 1. Change the state of the running process to interrupted
        PCB_set_state(cpu->currentProcess, interrupted);

        // 2. Save the CPU state to the PCB
        PCB_set_pc(cpu->currentProcess, cpu->pc);

        //Replace PC of CPU will value stored in systemStack
        cpu->pc = cpu->sysStack;

        //cpu->pc = CPU_pop_sysStack(cpu);

        // 3. "Do an up-call" to the scheduler
        CPU_scheduler(cpu, interrupt_type, PC, device);
    }

/**
 * Removes the text file if already in place
 */
void CPU_remove_file() {
    remove("discontinuities.txt");
    return;
}

/**
 * Function that creates 0-5 new processes and puts them into a list.
 */
Queue *CPU_create_processes(Queue *queue, int numb_process, int process_ID, long int time_count) {
    int n;
    static int proc_id = 1;
    for (n = 0; n < numb_process; n++) {
        PCB_p pcb = PCB_constructor();
        PCB_set_pid(pcb, proc_id++);
        PCB_set_priority(pcb, rand() % 31 + 1);
        PCB_set_state(pcb, created);
        PCB_set_pc(pcb, 0);
        PCB_set_max_pc(pcb, 2345);
        PCB_set_creation(pcb, time_count);
        PCB_set_termination(pcb, 0);
        PCB_set_terminate(pcb, rand() % 5); // Our terminate values are 0-4
        PCB_set_term_count(pcb, 0);
        // IO_1 trap taken care of in constructor
        // IO_2 trap taken care of in constructor
        queue = Queue_enqueue(queue, pcb);
        fprintf(file, "Process created: PID %d at %ld\n", PCB_get_pid(pcb), PCB_get_creation(pcb));
        printf("Process created: PID %d at %ld\n", PCB_get_pid(pcb), PCB_get_creation(pcb));
    }
    return queue;
}

/**
* Function that checks pending I/O requests. returns 0 if not and 1 if there is
*/
int CPU_check_io_request(PCB_p pcb, int device_num) {
//    int PC = PCB_get_PC(pcb);
    int index;
    for (index = 0; index < MAX_IO_TRAPS; index++) {
        int check_request = PCB_get_io_trap_index(pcb, index, device_num);
        if (pcb->pc_value < check_request) break;
        else if (pcb->pc_value == check_request) return 1;
    }
    return 0;
}

/**
* Function that handles the I/O traps.
*/
void CPU_io_trap_handler(CPU_p cpu, IO_p device, int device_num) {

    fprintf(file, "I/O trap request: I/O device %d, ", device_num);
    printf("I/O trap request: I/O device %d, ", device_num);

    Queue_enqueue(device->waitingQueue, cpu->currentProcess);
    fprintf(file, "PID %d put into waiting queue, ", device->waitingQueue->rear->pcb->pid);
    printf("PID %d put into waiting queue, ", device->waitingQueue->rear->pcb->pid);

    if (!Queue_isEmpty(cpu->readyQueue)) {
        cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
        fprintf(file, "PID %d dispatched\n", cpu->currentProcess->pid);
        printf("PID %d dispatched\n", cpu->currentProcess->pid);
    }else{
        fprintf(file, "No PID dispatched; empty readyQueue\n");
        printf("No PID dispatched; empty readyQueue\n");
    }

}

int main() {
    // House Keeping:
    file = fopen("discontinuities.txt", "w");

    srand((unsigned int) time(NULL)); // Seed random generator
    int total_procs = 0, process_ID = 1;
    IO_p device_1 = IO_constructor();
    IO_p device_2 = IO_constructor();

    // Create CPU:
    CPU *cpu = CPU_constructor();

    int device_1_interrupt, device_2_interrupt, io_request;

    // CPU: Represent an instruction execution.
    unsigned int time_count = 1;

// 1a. Create a queue of new processes, 0 - 5 processes at a time:
    int num_proc_created = 0;
    do {
        num_proc_created = rand() % 6+1;
    } while (total_procs + num_proc_created > MAX_PROCESS);
    total_procs += num_proc_created;

    cpu->newProcessesQueue = CPU_create_processes(cpu->newProcessesQueue,
                                                  num_proc_created, process_ID, time_count);

    process_ID += num_proc_created;

    while (!Queue_isEmpty(cpu->newProcessesQueue)) {
        PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
        PCB_set_state(temp_pcb, ready);
        Queue_enqueue(cpu->readyQueue, temp_pcb);
    }

    cpu->currentProcess = Queue_dequeue(cpu->readyQueue);


    //total_procs <= MAX_PROCESS - 5
    while (time_count < 100000) {


        printf("Check: %u\n", time_count);

        /**** EXECUTION INSTRUCTION ****/
        if (cpu->currentProcess != NULL) {
            //Increment PC by 1 to stimulate instruction execution
            PCB_increment_PC(cpu->currentProcess);
            CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));

            // Reset current process PC value back to 0 if it reached its max PC
            if (cpu->currentProcess->pc_value > cpu->currentProcess->max_pc) PCB_set_pc(cpu->currentProcess, 0);

            // Increase term count every time current process goes over its max PC
            if (PCB_get_PC(cpu->currentProcess) == 0) PCB_increment_term_count(cpu->currentProcess);

            // When a process terminates
            if (PCB_get_terminate(cpu->currentProcess) != 0 &&
                PCB_get_terminate(cpu->currentProcess) == PCB_get_term_count(cpu->currentProcess)) {
                fprintf(file, "Process terminated: PID %d at %u\n", PCB_get_pid(cpu->currentProcess), time_count);
                printf("Process terminated: PID %d at %u\n", PCB_get_pid(cpu->currentProcess), time_count);
                PCB_set_termination(cpu->currentProcess, time_count);
                CPU_enqueue_terminatedQueue(cpu, cpu->currentProcess);
                if (!Queue_isEmpty(cpu->readyQueue)) {
                    cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
                }
                continue;
            }
        }

        /**** CHECK FOR TIMER INTERRUPT ****/
        // Timer interrupt if timer is 0, Timer_interrupt returns 1
        if (Timer_countDown(cpu->timer)) {

            // Reset timer
            Timer_reset(cpu->timer);

            // calls pseudo ISR
            if (cpu->currentProcess != NULL) {
                CPU_pseudo_isr(cpu, INTERRUPT_TIMER, PCB_get_PC(cpu->currentProcess), NULL);
            }


            // Create some more processes until MAX_PROCESS allowed
            int num_proc_created = 0;
            do {
                num_proc_created = rand() % 6 +1;
            } while (total_procs + num_proc_created > MAX_PROCESS);
            total_procs += num_proc_created;

            cpu->newProcessesQueue = CPU_create_processes(cpu->newProcessesQueue,
                                                          num_proc_created, process_ID, time_count);

            process_ID += num_proc_created;

            // Add newly created processes to the CPU's ready Queue
            while (!Queue_isEmpty(cpu->newProcessesQueue)) {
                PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
                PCB_set_state(temp_pcb, ready);
                Queue_enqueue(cpu->readyQueue, temp_pcb);
            }

        }

        /**** CHECK FOR I/O COMPLETION INTERRUPT  ****/
        if (!Queue_isEmpty(device_1->waitingQueue))
            device_1_interrupt = Timer_countDown(device_1->timer);
        if (device_1_interrupt == 1) {
            CPU_pseudo_isr(cpu, INTERRUPT_IO, PCB_get_PC(cpu->currentProcess), device_1);
            Timer_set_count(device_1->timer, QUANTUM * (rand() % 3 + 3));
        }

        if (!Queue_isEmpty(device_2->waitingQueue))
            device_2_interrupt = Timer_countDown(device_2->timer);
        if (device_2_interrupt == 1) {
            CPU_pseudo_isr(cpu, INTERRUPT_IO, PCB_get_PC(cpu->currentProcess), device_2);
            if (device_2->timer->count == -1 || device_2->timer->count == 0)
                Timer_set_count(device_2->timer, QUANTUM * (rand() % 3 + 3));
        }

        /**** CHECK FOR I/O TRAP ****/
        if (cpu->currentProcess != NULL) {
            io_request = CPU_check_io_request(cpu->currentProcess, DEVICE_ARRAY_1);
            if (io_request == 1) {
                CPU_io_trap_handler(cpu, device_1, DEVICE_ARRAY_1);
                if (device_1->timer->count == -1 || device_1->timer->count == 0)
                    Timer_set_count(device_1->timer, QUANTUM * (rand() % 3 + 3));
            }

            io_request = CPU_check_io_request(cpu->currentProcess, DEVICE_ARRAY_2);
            if (io_request == 1) {
                CPU_io_trap_handler(cpu, device_2, DEVICE_ARRAY_2);
                if (device_1->timer->count == -1 || device_1->timer->count == 0)
                    Timer_set_count(device_1->timer, QUANTUM * (rand() % 3 + 3));
            }
        }
        time_count++;
    }
    fclose(file);
    CPU_destructor(cpu);
    return 0;
}