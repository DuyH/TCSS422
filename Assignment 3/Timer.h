/*
 * Timer.h
 *
 *  Created on: Feb 10, 2016
 *      Author: trung
 */

#ifndef TIMER_H_
#define TIMER_H_

struct timer {
	int count;
};
typedef struct timer Timer;


Timer *Timer_initialize();

int Timer_coundown();

#endif /* TIMER_H_ */
