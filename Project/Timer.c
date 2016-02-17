/***********************************************************************************************
 * timer.c
 *
 * Programming Team:
 * Duy Huynh
 * Jeffrey LeCompte
 * Trung Dang
 * Brandon Scholer
 *
 * TCSS 422 - Winter 2016
 * Date: 2/10/16
 * Assignment 3
 *
 * Description:
 * Represents a timer for the simulation.
 *
 ************************************************************************************************/

#include <stdlib.h>
#include "timer.h"

/**
 * Constructs a Timer object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created Timer object.
 */
Timer_p Timer_constructor(long int time) {
    Timer_p timer = (Timer_p) malloc(sizeof(Timer));
    timer->count = time;
    timer->reset = time;
    return timer;
}

void Timer_destructor(Timer_p timer) {
    free(timer);
}

void Timer_set_count(Timer_p timer, long int time) {
    timer->count = time;
}

long int Timer_get_count(Timer_p timer) {
    return timer->count;
}

/**
 * Counts down by decrementing the Timer.
 *
 * Parameters: Timer_p timer: A pointer to a Timer.
 * Returns:	   int 1 if timer reaches the end of countdown, 0 otherwise.
 */
int Timer_countDown(Timer_p timer) {
    timer->count--;
    if (timer->count == 0) return 1;
    return 0;
}

void Timer_reset(Timer_p timer) {
    timer->count = timer->reset;
}