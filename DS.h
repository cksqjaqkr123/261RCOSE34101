#ifndef MY_HEADER_H
#define MY_HEADER_H

typedef struct PCB {
    int PID;

    int Arrival_t;
    int Priority;

    int CPU_burst_t;
    int IO_burst_t;
    int IO_cycle;
    int IO_cycle_remain;
    int IO_burst_remain;
    
    struct PCB* next;

} PCB;

typedef struct qnode {
    PCB* proc;
    
    struct qnode* nextq;
} qnode;

typedef struct queue {
    qnode* head;
    qnode* tail;
    int cnt;

} queue;

void kernel_panic(void);
PCB* make_proc(int pid);
void print_PCB(PCB* proc);

qnode* make_qnode(PCB* proc);
queue* q_make();
void q_push(queue* q, PCB* proc);
PCB* q_pop(queue* q);




#endif