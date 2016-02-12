/***********************************************************************************************
 * IO.c
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
#include <stdio.h>
#include "io.h"
#include "cpu.h"

IO_p IO_constructor(){
    IO_p io = calloc(1, sizeof(IO_p));
    io->timer = Timer_constructor(1800); //TODO randomize this number, based on what?
    io->waitingQueue = Queue_constructor();
    return io;
}

void IO_destructor(IO_p io) {
    Timer_destructor(io->timer);
    free(io);
}