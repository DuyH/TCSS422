//
// Created by jef on 1/11/16.
//

#include "pcb.h"

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

typedef struct p_queue {
    int val;
    struct PCB *pcb;
} p_queue;

int * create();

void add(PCB *pcb);

void check();

void remove(p_queue * node);

void display();

#endif /* PRIORITYQUEUE_H */