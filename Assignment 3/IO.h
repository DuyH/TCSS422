/***********************************************************************************************
 * IO.h
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
 * Header defines structures and functions used in implementation an IO trap
 *
 ************************************************************************************************/

#ifndef IO_H
#define IO_H

#include "timer.h"
#include "queue.h"

typedef struct io {
    Timer_p timer;
    Queue_p waitingQueue;

} IO;

typedef IO *IO_p;

/* IO Constructor */
IO_p IO_constructor(void);          // constructs a new IO object in the heap

/* IO Destructor */
void IO_destructor(IO_p);           // frees memory allocated to IO object

/* Utility Functions */

#endif //IO_H
