/*
 * scheduler.h
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "queue.h"

extern int sysStack;

/**
 * Fetch the next process in newly created list of process
 * and put it in ready queue.
 */
Queue * fetchProcess(Queue *processes, Queue *readyQueue);





#endif /* SCHEDULER_H_ */
