/*
 * pcb_test.c
 *
 * TCSS 422 '16
 * Assignment 1
 * Authors: Duy Huynh, Jeffrey LeCompte, Trung Dang, Brandon Scholer
 *
 * This program tests the pcb structure by instantiating and populating a pcb.
 */

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"
#include <time.h>

/*
 * Main driver to test the PCB struct.
 */
int main(void) {

    // Create a random number of PCB's (0-20 range)
    srand(time(0)); // Random seed
    int numPcbs = rand() % 20;
    PCB pcb_array[numPcbs];

    // Instantiate just one PCB and print its contents:
    printf("-- initial generated PCB --\n");
    PCB * pcb = create();
    toString(pcb);

    // Continue to generate a random amount of PCB's and print out their contents:
    printf("\n-- random generated priorities --\n");

    for (int n = 0; n < numPcbs; n++) {
        int priority = rand() % 31 + 1;
        PCB * pcb = create();
        pcb->pid = n;
        pcb->priority = priority;
        pcb->state = new;
        pcb_array[n] = *pcb;

        toString(&pcb_array[n]);
    }
}



