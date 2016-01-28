//
// Created by jef on 1/27/16.
//

#ifndef ASSIGNMENT1_CPU_H
#define ASSIGNMENT1_CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "pcb.h"

typedef enum interrupt_state {
    timer
} interrupt_type;

/*
 * Global variable for frame pointer
 */
int sysStack;

PCB * dispatch(Queue *readyQueue);

Queue * fetchProcess(Queue *newProcess, Queue *readyQueue, enum interrupt_state, int printCounter);

Queue * initializeNewQueue(Queue * queue, int numb_process);

void file_handler(char * string);

void remove_file();

#endif //ASSIGNMENT1_CPU_H
