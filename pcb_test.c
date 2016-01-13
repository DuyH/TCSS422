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
 * Main driver to test a pcb.
 */
int main(void) {

    // Decide a random number of PCB's to create, from 1-10 pcb's
    srand(time(0));
    int n, pNum = 0;


    // Create an array of pcbs, 0-20
    int numPcbs = rand() % 20;
    PCB pcb_array[numPcbs];

    // Creates an initial PCB
    PCB * pcb = create();

    // Print out the newly instantiated pcb
    printf("-- initial generated PCB --\n");
    toString(pcb);
    printf("\n-- random generated priorities --\n");

    for (n = 0; n < numPcbs; n++) {
        int pNum = rand() % 31 + 1;
        PCB * pcb = create();
        pcb->pid = n;
        pcb->priority = pNum;
        pcb->state = new;
        pcb_array[n] = *pcb;

        toString(&pcb_array[n]);
    }
}



