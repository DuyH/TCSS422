/*
 * scheduler.h
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "queue.h"

extern sysStack;

Queue * schedule(Queue *processes, Queue *readyQueue);

#endif /* SCHEDULER_H_ */
