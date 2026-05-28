#ifndef MY_HEADER_H
#define MY_HEADER_H

// Spec of PCB
typedef struct PCB {
    int PID;

    int Arrival_t;
    int Priority;

    int CPU_burst_t;
    int CPU_burst_remain;
    int IO_burst_t;
    int IO_cycle;
    int IO_cycle_remain;
    int IO_burst_remain;
    int Q;

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
PCB* make_proc(void);
PCB* make_proc_CPU_B(void);
PCB* make_proc_IO_B(void);
PCB* make_non_rand_proc(int Arrival, int Priority, int CPU_burst, int IO_burst, int IO_cycle);
void print_PCB(PCB* proc);

qnode* make_qnode(PCB* proc);
queue* q_make();
void free_PCB_q(queue* q);
void free_q(queue* q);
void q_push(queue* q, PCB* proc);
PCB* q_pop(queue* q);




#endif