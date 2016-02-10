/*
 * Timer.c
 *
 *  Created on: Feb 10, 2016
 *      Author: trung
 */

#include <stdlib.h>
#include "Timer.h"

Timer *Timer_initialize() {
	Timer * timer = calloc(1, sizeof(Timer));
	timer->count = 300;
	return timer;
}

int Timer_countDown(Timer * timer) {
	timer->count--;
	if (timer->count == 0) return 1;
	return 0;
}

