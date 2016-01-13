//
// Created by jef on 1/11/16.
//

#include <stdlib.h>
#include "priorityqueue.h"

int * create() {
    // when called from main
    // struct p_queue *ptr = create();
    return (struct p_queue*)malloc(sizeof(struct p_queue));
}

void add(PCB *pcb) {
    check();
}

void check() {

}

void main() {

}