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
unsigned int CTX_SWITCH_COUNT = 1;

/* CPU Constructor */
CPU_p CPU_constructor(void) {
	CPU_p cpu = malloc(sizeof(CPU));
	cpu->pc = 0;
	cpu->timer = 0;
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

void CPU_scheduler(CPU_p cpu, Interrupt_type interrupt_type, int PC) {
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
	case timer:
		// 1. Put process back into the readyQueue
		Queue_enqueue(cpu->readyQueue, cpu->currentProcess);

		// 2. Change its state from interrupted to ready
		PCB_set_state(cpu->currentProcess, ready);

		// 3. Make call to dispatcher
		CPU_dispatcher(cpu, timer);

		// 4. Returned from dispatcher, do any housekeeping
		// Nothing here to do at the moment!

		// 5. Returns to pseudo-ISR
		return;
		break;
	default:
		CPU_dispatcher(cpu, normal);
		break;
	}
	return;
}

void CPU_dispatcher(CPU_p cpu, Interrupt_type interrupt_type) {

	// Save pointers to the previous and next process (needed so we can print)
	PCB_p prevProcess = cpu->currentProcess;
	PCB_p nextProcess = Queue_peek(cpu->readyQueue);
	//if (CTX_SWITCH_COUNT % 4 == 0) {
	if (prevProcess != NULL)
		fprintf(file, "Running process: %s", PCB_toString(prevProcess));
	if (nextProcess != NULL)
		fprintf(file, "Switching to: %s", PCB_toString(nextProcess));
	//}
	// 1. Save the state of current process into its PCB (PC value)
	// Per Canvas Discussions, DON'T DO THIS AGAIN HERE! It's in ISR.

	// 2. Then dequeue next waiting process
	if (!Queue_isEmpty(cpu->readyQueue))
		cpu->currentProcess = Queue_dequeue(cpu->readyQueue);

	// 3. Change its state to running
	PCB_set_state(cpu->currentProcess, running);

	if (interrupt_type == timer) {
		// 4. Copy its PC value to sysStack, replacing the interrupted process
		CPU_push_sysStack(cpu, PCB_get_PC(cpu->currentProcess));
	} else if (interrupt_type == normal) {
		CPU_set_pc(cpu, cpu->sysStack);
	}

	//if (CTX_SWITCH_COUNT % 4 == 0) {
	if (prevProcess != NULL)
		fprintf(file, "Last Process: %s", PCB_toString(prevProcess));
	if (nextProcess != NULL)
		fprintf(file, "Current running Process: %s", PCB_toString(nextProcess));
	fprintf(file, "Ready Queue: %s", Queue_toString(cpu->readyQueue, 0));

	//}

	// 5. Return to the scheduler
	// returns prevalent stuff to scheduler, but not for this project
	return;
}

void CPU_pseudo_isr(CPU_p cpu, int PC) {
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
		CPU_scheduler(cpu, timer, PC);

	} else {
		fprintf(file, "No process currently running. Normal interrupt...\n");
		CPU_scheduler(cpu, normal, PC);
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

	srand(time(0)); // Seed random generator
	unsigned int PC = 0;
	int total_procs = 0, process_ID = 1;

	// Create CPU:
	CPU *cpu = CPU_constructor();

	// CPU: Represent a time quantum. Assumed every process has the same time quantum.
	int time_count = 1;
	//total_procs <= MAX_PROCESS - 5
	while (total_procs <= MAX_PROCESS - 5) {
		fprintf(file, "***************TIME QUANTUM = %d***************\n",
				time_count);

		// 1a. Create a queue of new processes, 0 - 5 processes at a time:
		int num_proc_created = 0;

		num_proc_created = rand() % 6;
		total_procs += num_proc_created;

		cpu->newProcessesQueue = CPU_create_processes(cpu->newProcessesQueue,
				num_proc_created, process_ID);

		process_ID += num_proc_created;

		// 1c. Print newly created processes queue to file:
		fprintf(file, "New processes initialized: %d. Total processes: %d\n",
				num_proc_created, total_procs);
		fprintf(file, "Newly created processes list: %s",
				Queue_toString(cpu->newProcessesQueue, 0));

		// puts head of readyQueue as current process and changes state to running
//        if (cpu->currentProcess == empty_pcb && !Queue_isEmpty(cpu->readyQueue)) {
//            cpu->currentProcess = Queue_dequeue(cpu->readyQueue);
//            PCB_set_state(cpu->currentProcess, running);
//        }
		unsigned int random = rand() % 1001 + 3000;
		if (random < 3000) {
			random = rand() % 1001 + 3000;
		}
		PC += random;

		fprintf(file, "Current PC: %d. System Stack: %d\n", PC, cpu->sysStack);

		//if (cpu->currentProcess != NULL)
		CPU_push_sysStack(cpu, PC);

		// calls pseudo ISR
		CPU_pseudo_isr(cpu, PC);

		fprintf(file, "Current PC: %d. System Stack: %d\n\n", PC,
				cpu->sysStack);

		CTX_SWITCH_COUNT++;
		time_count++;
	}
	fclose(file);
	CPU_destructor(cpu);
	return 0;
}
