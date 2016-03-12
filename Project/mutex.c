//
// Created by Brandon on 3/11/2016.
//
#include <stdlib.h>
#include "mutex.h"

/*********************************************
 *            Mutex Functions                *
 ********************************************/

/**
 * Constructs a mutex object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created mutex object.
 */
Mutex_p mutex_constructor(int id) {
    Mutex_p mutex = (Mutex_p )malloc(sizeof(Mutex));
    mutex->lock = 0;
    mutex->mutex_id = id;
    mutex->pcb = NULL;
    mutex->mutex_waiting_queue = Queue_constructor();
    return mutex;
}

/**
 * Frees allocated memory used by the mutex object.
 *
 * Parameters:  Mutex_p mutex: pointer to the mutex object.
 */
void mutex_destructor(Mutex_p mutex) {
    free(mutex);
}

/**
 * Attempts to get a lock on the mutex, adding the pcb to a waiting
 * queue otherwise.
 *
 * Parameters:  Mutex_p mutex: pointer to the mutex object.
 *              PCB_p pcb: pointer to the PCB object.
 * Returns: int indicating success or failure of lock
 */
int mutex_lock(Mutex_p mutex, PCB_p pcb) {
    if (mutex->lock) {
        Queue_enqueue(mutex->mutex_waiting_queue, pcb);
        return 0;
    } else {
        mutex->lock = 1;
        mutex->pcb = pcb;
        return 1;
    }
}

/**
 * Attempts to get a lock on the mutex.
 *
 * Parameters:  Mutex_p mutex: pointer to the mutex object.
 *              PCB_p pcb: pointer to the PCB object.
 * Returns: int indicating the success or failure of lock.
 */
int mutex_trylock(Mutex_p mutex, PCB_p pcb) {
    if (mutex-> lock) return 0;
    else return mutex_lock(mutex, pcb);
}

/**
 * Attempts to unlock the mutex.
 *
 * Parameters:  Mutex_p mutex: pointer to the mutex object.
 *              PCB_p pcb: pointer to the PCB object.
 * Returns: int indicating the success or failure of lock.
 */
void mutex_unlock(Mutex_p mutex, PCB_p pcb) {
    if (mutex->lock && mutex->pcb == pcb) {
        if (Queue_isEmpty(mutex->mutex_waiting_queue)) {
            mutex->lock = 0;
            mutex->pcb = NULL;
        } else {
            mutex->pcb = Queue_dequeue(mutex->mutex_waiting_queue);
        }
    }
}

/*********************************************
 *          Condition Functions              *
 ********************************************/

/**
 * Constructs a condition object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created condition object.
 */
Condition_p condition_constructor(int id){
    Condition_p condition = (Condition_p)malloc(sizeof(Condition));
    condition->condition_id = id;
    condition->pcb = NULL;
    condition->mutex = NULL;
}

/**
 * Frees allocated memory used by the condition object.
 *
 * Parameters:  Condition_p condition: pointer to the condition object.
 */
void condition_destructor(Condition_p condition){
    free(condition);
}

/**
 * Unlocks the mutex, sets the mutex and pcb of condition.
 *
 * Parameters:  Condition_p condition: pointer to condition object.
 *              Mutex_p mutex: pointer to the mutex object.
 *              PCB_p pcb: pointer to the PCB object.
 */
void condition_wait(Condition_p condition, Mutex_p mutex, PCB_p pcb) {
    mutex_unlock(mutex, pcb);
    condition->mutex = mutex;
    condition->pcb = pcb;
}

/**
 * Locks the currently waiting pcb. Returns previous pcb or NULL if
 * no other pcb was waiting.
 *
 * Parameters:  Mutex_p mutex: pointer to the mutex object.
 *              PCB_p pcb: pointer to the PCB object.
 * Returns: PCB_p that was using the condition previously.
 */
PCB_p condition_signal(Condition_p condition, PCB_p pcb) {
    PCB_p previous = condition->pcb;
    if (condition->pcb != NULL) {
        mutex_lock(condition->mutex, condition->pcb);
        condition->pcb = NULL;
        condition->mutex = NULL;
    }
    return previous;
}
