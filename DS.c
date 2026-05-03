#include <stdio.h>
#include "DS.h"
#include <stdlib.h>

PCB* make_proc() {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = rand() % 10000;

    new_PCB -> Arrival_t = rand() % 50;
    new_PCB -> Priority = rand() % 10;

    new_PCB -> CPU_burst_t = rand() % 30;
    new_PCB -> IO_burst_t = rand() % 15;
    new_PCB -> IO_cycle = rand() % 30;

    new_PCB -> next = NULL;

    return new_PCB;
}

void print_PCB(PCB* proc) {
    printf("PID : %d\n", proc -> PID);
    printf("Arrival Time : %d\n", proc -> Arrival_t);
    printf("Priortiy : %d\n", proc -> Priority);
    printf("CPU burst time : %d\n", proc -> CPU_burst_t);
    printf("IO burst time : %d\n", proc -> IO_burst_t);
}

queue* q_make() {
    queue* new_q = malloc(sizeof(queue));

    new_q -> head = NULL;
    new_q -> tail = NULL;
    new_q -> cnt = 0;

    return new_q;
}

void q_push(queue* q, PCB* proc) {
    if (q -> head == NULL) {
        q -> head = proc;
        q -> tail = proc;
    }
    else {
        q -> tail -> next = proc;
        q -> tail = proc;
    }
    q -> cnt += 1;
}

PCB* q_pop(queue* q) {
    PCB* tmp = NULL;

    if (q -> head != NULL) {
        tmp = q -> head;
        q -> head = tmp -> next;
        if (tmp -> next == NULL) q -> tail = NULL;
        tmp -> next = NULL;
    }

    if (tmp != NULL) q -> cnt -= 1;

    return tmp;
}