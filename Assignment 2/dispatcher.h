/*
 * dispatcher.h
 *
 *  Created on: Jan 20, 2016
 *      Author: trung
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "queue.h"

extern int sysStack;

PCB *dispatch(Queue *queue);

#endif /* DISPATCHER_H_ */
