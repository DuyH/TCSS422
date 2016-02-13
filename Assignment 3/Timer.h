/***********************************************************************************************
 * timer.h
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
 * Header defines structures and functions used in implementation of a timer to be used in simulation
 *
 ************************************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#define QUANTUM 5

typedef struct timer {
	long int count;
} Timer;

typedef Timer *Timer_p;

/* Timer Constructor */
Timer_p Timer_constructor(long int);    // constructs a new Timer object in the heap

/* Timer Destructor */
void Timer_destructor(Timer_p);    // constructs a new Timer object in the heap

void Timer_set_count(Timer_p timer, long int time);

long int Timer_get_count(Timer_p timer);

/* Utility Functions */
int Timer_countDown(Timer_p);   // decrements the Timer, returning a 1 if countdown reaches 0.

#endif /* TIMER_H_ */
