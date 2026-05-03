#ifndef MY_HEADER_H
#define MY_HEADER_H

typedef struct PCB {
    int PID;

    int Arrival_t;
    int Priority;

    int CPU_burst_t;
    int IO_burst_t;
    int IO_cycle;


    struct PCB* next;

} PCB;

typedef struct {
    PCB* head;
    PCB* tail;
    int cnt;

} queue;

PCB* make_proc();
void print_PCB(PCB* proc);

queue* q_make();
void q_push(queue* q, PCB* proc);
PCB* q_pop(queue* q);




#endif