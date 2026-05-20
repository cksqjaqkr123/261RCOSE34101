#include <stdio.h>
#include "DS.h"
#include <stdlib.h>

void kernel_panic(void) {
    printf("panic!!!!\n");
    exit(1);
}

PCB* make_proc(void) {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = 0;

    new_PCB -> Arrival_t = rand() % 31;
    new_PCB -> Priority = rand() % 10;

    new_PCB -> CPU_burst_remain = new_PCB -> CPU_burst_t = rand() % 10 + 1;
    new_PCB -> IO_burst_remain = new_PCB -> IO_burst_t = rand() % 10 + 1;
    new_PCB -> IO_cycle_remain = new_PCB -> IO_cycle = rand() % 15 + 1;
    new_PCB -> Q = 0;
    
    new_PCB -> next = NULL;

    return new_PCB;
}

PCB* make_proc_CPU_B(void) {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = 0;

    new_PCB -> Arrival_t = rand() % 31;
    new_PCB -> Priority = rand() % 10;

    new_PCB -> CPU_burst_remain = new_PCB -> CPU_burst_t = rand() % 10 + 5;
    new_PCB -> IO_burst_remain = new_PCB -> IO_burst_t = rand() % 5 + 1;
    new_PCB -> IO_cycle_remain = new_PCB -> IO_cycle = rand() % 20 + 5;
    new_PCB -> Q = 0;
    
    new_PCB -> next = NULL;

    return new_PCB;
}

PCB* make_proc_IO_B(void) {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = 0;

    new_PCB -> Arrival_t = rand() % 31;
    new_PCB -> Priority = rand() % 10;

    new_PCB -> CPU_burst_remain = new_PCB -> CPU_burst_t = rand() % 5 + 1;
    new_PCB -> IO_burst_remain = new_PCB -> IO_burst_t = rand() % 10 + 5;
    new_PCB -> IO_cycle_remain = new_PCB -> IO_cycle = rand() % 3 + 1;
    new_PCB -> Q = 0;
    
    new_PCB -> next = NULL;

    return new_PCB;
}


PCB* make_non_rand_proc(int Arrival, int Priority, int CPU_burst, int IO_burst, int IO_cycle) {
    PCB* new_PCB = malloc(sizeof(PCB));

    new_PCB -> PID = 0;

    new_PCB -> Arrival_t = Arrival;
    new_PCB -> Priority = Priority;

    new_PCB -> CPU_burst_remain = new_PCB -> CPU_burst_t = CPU_burst;
    new_PCB -> IO_burst_remain = new_PCB -> IO_burst_t = IO_burst;
    new_PCB -> IO_cycle_remain = new_PCB -> IO_cycle = IO_cycle;
    new_PCB -> Q = 0;
    
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

void free_PCB_q(queue* q) {
    qnode* tmp = q -> head;
    while (tmp != NULL) {
        free(tmp -> proc);
        tmp = tmp -> nextq;
    }
}

void free_q(queue* q) {
    qnode* tmp = q -> head;
    qnode* del_node = NULL;
    while (tmp != NULL) {
        del_node = tmp;
        tmp = tmp -> nextq;
        free(del_node);
    }
    free(q);
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
