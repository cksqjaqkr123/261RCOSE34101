#ifndef MY_HEADER_DS
#define MY_HEADER_DS

#include "DS.h"

#define HEAP_SIZE 200

typedef struct heap {
    PCB* array[HEAP_SIZE];
    int size;

} heap;

queue** make_job_q(queue* procs);
PCB** make_wait_list(void);

heap* make_heap(void);
void push_heap(heap* heap, PCB* proc, int (*compare) (PCB*, PCB*));
PCB* pop_heap(heap* heap, int (*compare) (PCB*, PCB*));
void swap(PCB** array, int i, int j);

int compare_Priority(PCB* a, PCB* b);
int compare_Job(PCB* a, PCB* b);

#endif