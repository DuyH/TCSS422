/***********************************************************************************************
 * io.c
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
 * IO trap representation for simulation
 *
 ************************************************************************************************/

#include <stdlib.h>
#include "io.h"
#include "cpu.h"

/**
 * Constructs an IO object in the heap, returning a pointer to it.
 *
 * Returns: Pointer to created IO object.
 */
IO_p IO_constructor() {
    IO_p io = calloc(1, sizeof(IO_p));
    srand((unsigned int) time(NULL)); // Random seed
    io->timer = Timer_constructor(QUANTUM * (rand() % 3 + 3)); // 3-5 times larger than Quantum
    io->waitingQueue = Queue_constructor();
    return io;
}

/**
 * Frees allocated memory used by the IO object.
 *
 * Parameters:  IO_p io: pointer to the IO object to be freed.
 */
void IO_destructor(IO_p io) {
    Timer_destructor(io->timer);
    Queue_destructor(io->waitingQueue);
    free(io);
}