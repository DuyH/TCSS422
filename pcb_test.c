//
// Created by Duy Huynh on 1/11/16.


#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

int main(void) {

    // Create a pcb
    PCB pcb;
    pcb.pid = 1;
    pcb.priority = 10;
    pcb.state = terminated;

    // Print out the pcb
    toString(pcb);
    printf("PID: %d", pcb.pid);

    // Create another pcb

    // Print out the pcb

}



