/*
 * dispatcher.c
 *
 *  Created on: Jan 26, 2016
 *      Author: trung
 */

#include "dispatcher.h"

PCB * dispatch(Queue *readyQueue) {
	PCB *readyPCB = dequeue(readyQueue);
	readyPCB->state = running;
	return readyPCB;
}