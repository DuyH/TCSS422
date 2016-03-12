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
 * Simulates execution cycles of the CPU, complete with IO traps, IO completion interrupts, Timer interrupts, and
 * terminating processes. Since processes are able to have the property of NOT terminating over the course of a
 * simulation, this program will simulate CPU cycles until all processes have been terminated OR until a defined
 * number of cycles has been reached, whichever comes first.
 *
 ************************************************************************************************/

#include "cpu.h"

// Maximum cycles before simulation termination
#define MAX_SIMULATION_CYCLES 100000

#define MAX_PROCESS 30 // Limit simulation to this many processes at a time

// Max IO processes during simulation
#define MAX_IO_PROCESSES 50

// Max Compute Intensive processes during simulation
#define MAX_INTENSIVE_PROCESSES 25

// Max Producer-Consumer pairs during simulation
#define MAX_PROCON_PROCESSES 10

// Max Mutual Resource Users during simulation
#define MAX_MUTUAL_RESOURCE_PROCESSES 5

// Priority levels for simulation
#define NUM_PRIORITIES 4

#define MAX_IO_TRAPS 4
#define DEVICE_ARRAY_1 1
#define DEVICE_ARRAY_2 2

// Global Variable for each Producer-Consumer pair to manipulate
int procon_globals[10];

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
    cpu->readyQueue = PQueue_constructor();
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

void CPU_set_readyQueue(CPU_p cpu, PQueue_p queue) {
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

PQueue_p CPU_get_readyQueue(CPU_p cpu) {
    return cpu->readyQueue;
}

Queue_p CPU_get_terminatedQueue(CPU_p cpu) {
    return cpu->terminatedQueue;
}

Queue_p CPU_get_newProcessesQueue(CPU_p cpu) {
    return cpu->newProcessesQueue;
}

/* CPU ADT Functions */

PQueue_p CPU_enqueue_readyQueue(CPU_p cpu, PCB_p pcb) {
    return PQueue_enqueue(CPU_get_readyQueue(cpu), pcb);
}

PCB_p CPU_dequeue_readyQueue(CPU_p cpu) {
    return PQueue_dequeue(CPU_get_readyQueue(cpu));
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

void CPU_scheduler(CPU_p cpu, Interrupt_type interrupt_type, IO_p device) {
    switch (interrupt_type) {
        case INTERRUPT_TIMER:
            fprintf(file, "=======TIMER INTERRUPT=======\n");
            printf("=======TIMER INTERRUPT=======\n");
            if (cpu->currentProcess != NULL) {
                // 1. Put process back into the readyQueue
                fprintf(file, "Timer interrupt: PID %d was running, ", cpu->currentProcess->pid);
                printf("Timer interrupt: PID %d was running, ", cpu->currentProcess->pid);
                PQueue_enqueue(cpu->readyQueue, cpu->currentProcess);

                // 2. Change its state from interrupted to ready
                PCB_set_state(cpu->currentProcess, ready);
            }

            // 3. Make call to dispatcher
            int successfulDispatch = CPU_dispatcher(cpu, INTERRUPT_TIMER);
            if (successfulDispatch) {
                fprintf(file, "PID %d dispatched.\n\n", cpu->currentProcess->pid);
                printf("PID %d dispatched.\n\n", cpu->currentProcess->pid);
            } else {
                fprintf(file, "No PID was dispatched; readyQueue was empty!\n\n");
                printf("No PID was dispatched; readyQueue was empty!\n\n");
            }

            // 4. Returned from dispatcher, do any housekeeping
            // Nothing here to do at the moment!

            // 5. Returns to pseudo-ISR
            break;
        case INTERRUPT_IO:
            fprintf(file, "=======IO INTERRUPT=======\n");
            printf("=======IO INTERRUPT=======\n");

            // IF there is a currently running process
            if (cpu->currentProcess != NULL) {
                // 1. Put waiting process into the readyQueue
                fprintf(file, "I/O completion interrupt: PID %d is running, ", cpu->currentProcess->pid);
                printf("I/O completion interrupt: PID %d is running, ", cpu->currentProcess->pid);
            } else {
                fprintf(file, "I/O completion interrupt: No process was running, ");
                printf("I/O completion interrupt: No process was running, ");
            }
            fprintf(file, "PID %d put in ready queue\n\n", device->waitingQueue->head->pcb->pid);
            printf("PID %d in ready queue\n\n", device->waitingQueue->head->pcb->pid);
            PQueue_enqueue(cpu->readyQueue, Queue_dequeue(device->waitingQueue));
            break;
        default:
            CPU_dispatcher(cpu, INTERRUPT_NORMAL);
            break;
    }
    return;
}

int CPU_dispatcher(CPU_p cpu, Interrupt_type interrupt_type) {

    // 1. Save the state of current process into its PCB (PC value)
    // Per Canvas Discussions, DON'T DO THIS AGAIN HERE! It's in ISR.

    // As long as we have processes in the ready Queue...
    int empty = PQueue_isEmpty(cpu->readyQueue);
    if (empty) {

        // 2. Then dequeue next waiting process
        cpu->currentProcess = PQueue_dequeue(cpu->readyQueue);

        // 3. Change its state to running
        PCB_set_state(cpu->currentProcess, running);

        if (interrupt_type == INTERRUPT_TIMER) {
            // 4. Copy its PC value to sysStack, replacing the interrupted process
            CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));
        }

        return 1; // return 1 if a process was available to dispatch
    }

    // 5. Return to the scheduler
    return 0; // No process was dispatched
}

void CPU_pseudo_isr(CPU_p cpu, Interrupt_type interrupt_type, IO_p device) {

    // IF there is a running process:
    if (cpu->currentProcess != NULL) {
        // 1. Change the state of the running process to interrupted
        PCB_set_state(cpu->currentProcess, interrupted);

        // 2. Save the CPU state to the PCB
        PCB_set_pc(cpu->currentProcess, cpu->pc);
    }


    //Replace PC of CPU will value stored in systemStack
    cpu->pc = cpu->sysStack;

    //cpu->pc = CPU_pop_sysStack(cpu);

    // 3. "Do an up-call" to the scheduler
    CPU_scheduler(cpu, interrupt_type, device);
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
//Queue *CPU_create_processes(Queue_p queue, int numb_process, int process_ID, long int time_count) {
//
//    int n;
//    static int proc_id = 1;
//    for (n = 0; n < numb_process; n++) {
//        PCB_p pcb = PCB_constructor();
//    }
//    fprintf(file, "\n");
//    printf("\n");
//    return queue;
//}

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

    fprintf(file, "=======IO TRAP HANDLER=======\n");
    printf("=======IO TRAP HANDLER=======\n");
    fprintf(file, "I/O trap request: I/O device %d, ", device_num);
    printf("I/O trap request: I/O device %d, ", device_num);

    Queue_enqueue(device->waitingQueue, cpu->currentProcess);
    fprintf(file, "PID %d put into waiting queue, ", device->waitingQueue->rear->pcb->pid);
    printf("PID %d put into waiting queue, ", device->waitingQueue->rear->pcb->pid);

    if (!PQueue_isEmpty(cpu->readyQueue)) {
        cpu->currentProcess = PQueue_dequeue(cpu->readyQueue);
        fprintf(file, "PID %d dispatched\n", cpu->currentProcess->pid);
        printf("PID %d dispatched\n", cpu->currentProcess->pid);
    } else {
        fprintf(file, "No PID dispatched; empty readyQueue\n");
        printf("No PID dispatched; empty readyQueue\n");
    }
    fprintf(file, "\n");
    printf("\n");

}

/*****************************
 * Process Manager
 *****************************/

// Process Manager constructor

// Process Manager deconstructor



/*  1. Randomly pick a priority
 *      Then check if we are allowed to make any more of that priority
 *          If it is priority 0, automatically make Intensive pcb and
 *      If not, repick a priority
 *  2. Randomly pick a process type
 *      Check for hard-number limits for that
 */
Queue_p createProcess(Process_Manager_p manager, Queue_p queue, unsigned int timeCount) {

    fprintf(file, "=======PROCESSES CREATION=======\n");
    printf("=======PROCESSES CREATION=======\n");

    PCB_p pcb/* = (PCB_p) malloc(sizeof(PCB))*/;
    PCB_p pcb1/* = (PCB_p) malloc(sizeof(PCB))*/;

    // Randomly choose a process type:
    Process_Type type;

    // 1. Randomly pick a priority:
    srand((unsigned int) time(NULL)); // Seed random generator
    int randPriority = 0;
    int notUsable = 1;

    while (notUsable) {
        // Choose a randomize priority level
        randPriority = rand() % MAX_PRIORITY_LEVEL;
        double percentage;
        if (manager->num_running != 0)
            percentage = (double) manager->priority_counts[randPriority] / manager->num_running;
        else percentage = 0;

        switch (randPriority) {
            case 0:
                if (percentage < 0.05) notUsable = 0;
                break;
            case 1:
                if (percentage < 0.80) {
                    manager->priority_counts[1]++;
                    notUsable = 0;
                }
                break;
            case 2:
                if (percentage < 0.10) {
                    manager->priority_counts[2]++;
                    notUsable = 0;
                }
                break;
            case 3:
                if (percentage < 0.05) {
                    manager->priority_counts[3]++;
                    notUsable = 0;
                }
                break;
            default:
                break;
        }
    }


    notUsable = 1;
    int pair_flag = 1;
    PCB_p pro_con_pair[2] = {};
    while (notUsable) {
        if (randPriority == 0)
            type = intensive;
        else {
            do {
                type = (Process_Type) rand() % (NUM_PRIORITIES + 1);
            } while (type == intensive);
        }
        // Check hard-number limits:
        switch (type) {
            case io:
                if (manager->process_type_count[(int) type] < MAX_IO_PROCESSES) {
                    manager->process_type_count[(int) type]++;   // Increment the number of this type in manager

                    pro_con_pair[0] = PCB_constructor(type);

                    notUsable = 0;
                }
                break;
            case producer:
                if (manager->process_type_count[(int) type] < MAX_PROCON_PROCESSES) {
                    manager->process_type_count[(int) type]++;
                    manager->process_type_count[(int) consumer]++;

                    pro_con_pair[0] = PCB_constructor(type);
                    pro_con_pair[1] = PCB_constructor(consumer);

                    pair_flag = 2;
                    notUsable = 0;
                }
                break;
            case consumer:
                if (manager->process_type_count[(int) type] < MAX_PROCON_PROCESSES) {
                    manager->process_type_count[(int) type]++;
                    manager->process_type_count[(int) producer]++;

                    pro_con_pair[0] = PCB_constructor(type);
                    pro_con_pair[1] = PCB_constructor(producer);

                    pair_flag = 2;
                    notUsable = 0;
                }
                break;
            case intensive:
                if (manager->process_type_count[(int) type] < MAX_INTENSIVE_PROCESSES) {
                    manager->process_type_count[(int) type]++;
                    manager->priority_counts[0]++;

                    pro_con_pair[0] = PCB_constructor(type);

                    notUsable = 0;
                } else {
                    randPriority = rand() % (NUM_PRIORITIES + 1);
                }
                break;
            case mutual:
                if (manager->process_type_count[(int) type] < MAX_MUTUAL_RESOURCE_PROCESSES) {
                    manager->process_type_count[(int) type]++;
                    manager->process_type_count[(int) type]++;

                    pro_con_pair[0] = PCB_constructor(type);
                    pro_con_pair[1] = PCB_constructor(type);

                    pair_flag = 2;
                    notUsable = 0;
                }
                break;
            default:
                break;
        }
    }

    // Continue detailing the pcb:
    while (pair_flag) {
        // handles producer and consumer
        if (pair_flag == 2)
            pcb = pro_con_pair[1];
        else
            pcb = pro_con_pair[0];
        pair_flag--;

        PCB_set_pid(pcb, manager->num_processes);   // Set PID
        PCB_set_priority(pcb, randPriority);        // Set priority
        PCB_set_state(pcb, created);                // Set state
        PCB_set_pc(pcb, 0);                         // Set PC
        PCB_set_max_pc(pcb, 2345);                  // Set max PC
        PCB_set_creation(pcb, timeCount);           // Set creation time
        PCB_set_termination(pcb, 0);                // init termination
        PCB_set_terminate(pcb, rand() % 5);         // Our terminate values are 0-4
        PCB_set_term_count(pcb, 0);                 // init term count
        manager->num_processes++;                   // Update the number of TOTAL processes
        manager->num_running++;                     // Update number of currently running processes
        manager->priority_counts[randPriority]++;   // Update the number of priorities of that type
        queue = Queue_enqueue(queue, pcb);          // Enqueue newly created PCB to new proc q

        fprintf(file, "Process created: PID %d with Priority %d and Type %s at %ld\n", PCB_get_pid(pcb),
                PCB_get_priority(pcb), PCB_get_type_string(type), PCB_get_creation(pcb));
        printf("Process created: PID %d with Priority %d and Type %s at %ld\n", PCB_get_pid(pcb),
               PCB_get_priority(pcb), PCB_get_type_string(type), PCB_get_creation(pcb));
    }

    return queue;
}

Process_Manager_p process_manager_constructor() {
    Process_Manager_p manager_p = malloc(sizeof(Process_Manager_p));
    manager_p->num_processes = 0;
    manager_p->num_running = 0;
    int i;
    for (i = 0; i < 5; i++) {
        manager_p->process_type_count[i] = 0;
    }
    for (i = 0; i < NUM_PRIORITIES; i++) {
        manager_p->priority_counts[i] = 0;
    }
    manager_p->total_pairs = 0;

    return manager_p;
}

void process_manager_destructor(Process_Manager_p manager_p) {
    free(manager_p);
}

//
// 2. randomly pick a priority
// 3.
// 3. Create process of that type, using a function(type){switch(type)}
// 4. Update manager of the process counts


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
    int ran_proc_created = rand() % (NUM_PRIORITIES + 1);

    total_procs += ran_proc_created;

    // creates new process queue with new manager
    Process_Manager_p manager_p = process_manager_constructor();
    int i;
    for (i = 0; i < 5; i++) {
        cpu->newProcessesQueue = createProcess(manager_p, cpu->newProcessesQueue, time_count);
    }

    process_ID += ran_proc_created;

    while (!Queue_isEmpty(cpu->newProcessesQueue)) {
        PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
        PCB_set_state(temp_pcb, ready);
        PQueue_enqueue(cpu->readyQueue, temp_pcb);
    }

    cpu->currentProcess = PQueue_dequeue(cpu->readyQueue);


    // Run the simulation until either all processes terminate or max cycles reached (+1 for printing pretty # cycles)
    while (time_count < MAX_SIMULATION_CYCLES + 1) {

        /**************************************
         *      EXECUTE INSTRUCTION CYCLE     *
         *************************************/
        if (cpu->currentProcess != NULL) {

            //Increment PC by 1 to simulate instruction execution
            PCB_increment_PC(cpu->currentProcess);
            CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));

            // Reset current process PC value back to 0 if it reached its max PC
            if (cpu->currentProcess->pc_value > cpu->currentProcess->max_pc) PCB_set_pc(cpu->currentProcess, 0);

            // Increase term count every time current process goes over its max PC
            if (PCB_get_PC(cpu->currentProcess) == 0) PCB_increment_term_count(cpu->currentProcess);

            /**************************************
             *      TERMINATION DETERMINATION     *
             **************************************/
            if (PCB_get_terminate(cpu->currentProcess) != 0 &&
                PCB_get_terminate(cpu->currentProcess) == PCB_get_term_count(cpu->currentProcess)) {

                fprintf(file, "=======PROCESS TERMINATION=======\n");
                printf("=======PROCESS TERMINATION=======\n");
                fprintf(file, "Process terminated: PID %d at %u\n\n", PCB_get_pid(cpu->currentProcess), time_count);
                printf("Process terminated: PID %d at %u\n\n", PCB_get_pid(cpu->currentProcess), time_count);
                PCB_set_termination(cpu->currentProcess, time_count);
                CPU_enqueue_terminatedQueue(cpu, cpu->currentProcess);
                cpu->currentProcess = NULL;
                if (!PQueue_isEmpty(cpu->readyQueue)) {
                    cpu->currentProcess = PQueue_dequeue(cpu->readyQueue);
                }
            }
        }

        /**************************************
         *      CHECK FOR TIMER INTERRUPT     *
         *************************************/
        // Timer interrupt if timer is 0, Timer_interrupt returns 1
        if (Timer_countDown(cpu->timer)) {

            // Reset timer
            Timer_reset(cpu->timer);

            // calls pseudo ISR
            if (cpu->currentProcess != NULL) {
                CPU_pseudo_isr(cpu, INTERRUPT_TIMER, NULL);
            }
        }

        /**************************************
         *       CREATE NEW PROCESSES          *
         **************************************/

        // 1. Generate a random number of processes to create
        ran_proc_created = rand() % (NUM_PRIORITIES + 1);

        // 2. Increment counters for total number of processes
        total_procs += ran_proc_created;
        process_ID += ran_proc_created;

        // 3. Create randomly chosen number of processes
        int i;
        for (i = 0; i < 5; i++) {
            cpu->newProcessesQueue = createProcess(manager_p, cpu->newProcessesQueue, time_count);
        }

        // 4. Enqueue the freshly created processes into CPU's readyqueue
        while (!Queue_isEmpty(cpu->newProcessesQueue)) {
            PCB_p temp_pcb = Queue_dequeue(cpu->newProcessesQueue);
            PCB_set_state(temp_pcb, ready);
            PQueue_enqueue(cpu->readyQueue, temp_pcb);
        }

        // 5. If there is no currently running process, dequeue from the newly create processes
        if (cpu->currentProcess == NULL && !PQueue_isEmpty(cpu->readyQueue)) {
            cpu->currentProcess = PQueue_dequeue(cpu->readyQueue);
        }

        /****************************************************
         *      CHECK FOR I/O COMPLETION INTERRUPTS         *
         ****************************************************/

        if (!Queue_isEmpty(device_1->waitingQueue)) {
            device_1_interrupt = Timer_countDown(device_1->timer);
            if (device_1_interrupt == 1) {
                CPU_pseudo_isr(cpu, INTERRUPT_IO, device_1);
                if (device_1->timer->count == -1 || device_1->timer->count == 0)
                    Timer_set_count(device_1->timer, QUANTUM * (rand() % 3 + 3));
            }
        }

        if (!Queue_isEmpty(device_2->waitingQueue)) {
            device_2_interrupt = Timer_countDown(device_2->timer);
            if (device_2_interrupt == 1) {
                CPU_pseudo_isr(cpu, INTERRUPT_IO, device_2);
                if (device_2->timer->count == -1 || device_2->timer->count == 0)
                    Timer_set_count(device_2->timer, QUANTUM * (rand() % 3 + 3));
            }
        }

        /***********************************
         *      CHECK FOR I/O TRAP         *
         ***********************************/
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


    fprintf(file, "Simulation finished! Total cycles: %d", time_count - 1);
    printf("Simulation finished! Total cycles: %d", time_count - 1);
    fclose(file);
    CPU_destructor(cpu);
    return 0;
}
