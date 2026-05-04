#include <stdio.h>
#include "DS.h"
#include <stdlib.h>

void kernel_panic(void) {
    exit(1);
}

PCB* make_proc(int pid) {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = pid;

    new_PCB -> Arrival_t = rand() % 51;
    new_PCB -> Priority = rand() % 10;

    new_PCB -> CPU_burst_remain = new_PCB -> CPU_burst_t = rand() % 30;
    new_PCB -> IO_burst_remain = new_PCB -> IO_burst_t = rand() % 15;
    new_PCB -> IO_cycle_remain = new_PCB -> IO_cycle = rand() % 40;
    
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

qnode* make_qnode(PCB* proc) {
    qnode* new_qnode = malloc(sizeof(qnode));

    new_qnode -> proc = proc;
    new_qnode -> nextq = NULL;

    return new_qnode;
}
queue* q_make() {
    queue* new_q = malloc(sizeof(queue));

    new_q -> head = NULL;
    new_q -> tail = NULL;
    new_q -> cnt = 0;

    return new_q;
}

void q_push(queue* q, PCB* proc) {

    qnode* new_qnode = make_qnode(proc);

    if (q -> head == NULL) {
        q -> head = new_qnode;
        q -> tail = new_qnode;
    }
    else {
        q -> tail -> nextq = new_qnode;
        q -> tail = new_qnode;
    }
    q -> cnt += 1;
}

PCB* q_pop(queue* q) {
    qnode* qtmp = NULL;
    PCB* ptmp = NULL;

    if (q -> head != NULL) {
        qtmp = q -> head;
        q -> head = qtmp -> nextq;
        if (qtmp -> nextq == NULL) q -> tail = NULL;
        qtmp -> nextq = NULL;
    }

    if (qtmp != NULL) {
        q -> cnt -= 1;
        ptmp = qtmp -> proc;
    }
    free(qtmp);
    return ptmp;
}
