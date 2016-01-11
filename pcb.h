/*
 * pcb.h
 * Authors: Duy Huynh & Jeffrey LeCompte
 *
 */

#ifndef PCB_H_
#define PCB_H_

typedef enum process_state {
    new,
    ready,
    running,
    waiting,
    terminated
} state;

typedef struct pcb {
    int pid;                    /* identification number (size 4) */
    int priority;               /* priority (size 4) */
    enum process_state state;   /* current state (size 4) */
    struct PCB *next_pcb;       /* ptr to next PCB (size 8) */
    // Program counter, stack pointer, registers
    // Address space info (how much memory it takes)
    // Expected execution time (burst)
} PCB;

void toString(PCB pcb);

#endif /* PCB_H_ */
