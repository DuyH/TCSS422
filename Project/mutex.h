//
// Created by Brandon on 3/11/2016.
//

#ifndef PROJECT_MUTEX_H
#define PROJECT_MUTEX_H

#include "pcb.h"
#include "queue.h"

/*****************************
 *       mutex struct        *
 ****************************/
typedef struct mutex {
    int lock;
    int mutex_id;
    PCB_p pcb;
    Queue_p mutex_waiting_queue;
} Mutex;

typedef Mutex * Mutex_p;

/***************************
 *     condition struct    *
 **************************/
typedef struct condition {
    int condition_id;
    PCB_p pcb;
    Mutex_p mutex;
} Condition;

typedef Condition * Condition_p;

/***************************
 *     mutex functions     *
 **************************/
Mutex_p mutex_constructor(int id);

void mutex_destructor(Mutex_p mutex);

int mutex_lock(Mutex_p mutex, PCB_p pcb);

int mutex_trylock(Mutex_p mutex, PCB_p pcb);

void mutex_unlock(Mutex_p mutex, PCB_p pcb);

/***************************
 *     condition struct    *
 **************************/
Condition_p condition_constructor(int id);

void condition_destructor(Condition_p);

void condition_wait(Condition_p, Mutex_p, PCB_p);

PCB_p condition_signal(Condition_p, PCB_p);

#endif //PROJECT_MUTEX_H
