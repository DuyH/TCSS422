//
// Created by jef on 1/11/16.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "pcb.h"
#include "queue.h"

typedef struct p_queue {
    Queue * pri_Queue[32];
} p_queue;

p_queue * create_pqueue();

void add(p_queue * priority_Queue, PCB *pcb);

void check(p_queue * priority_Queue);

PCB * pop_pcb(p_queue * priority_Queue);

void display(p_queue * priority_Queue);

#endif /* PRIORITYQUEUE_H */