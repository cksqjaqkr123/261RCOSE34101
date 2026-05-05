#include <stdio.h>
#include <stdlib.h>
#include "DS_2.h"

#define JOP_Q_SIZE 51
#define WAIT_L_SIZE 100
#define HEAP_SIZE 200

queue** make_job_q(queue* procs) {
    int cnt = 0;
    queue** new_job_q = malloc(sizeof(queue*) * JOP_Q_SIZE);
    qnode* tmp = procs -> head;

    for (int i = 0; i < 51 ; i++) {
        new_job_q[i] = q_make();
    }

    while (tmp != NULL) {
        q_push(new_job_q[tmp -> proc -> Arrival_t], tmp -> proc);

        tmp = tmp -> nextq;
    }

    return new_job_q;
}

PCB** make_wait_list(void) {
    PCB** new_wait_list = malloc(sizeof(PCB*) * WAIT_L_SIZE);
    for (int i = 0; i < WAIT_L_SIZE; i++) {
        new_wait_list[i] = NULL;
    }
    return new_wait_list;
}

heap* make_heap(void) {
    heap* new_heap = malloc(sizeof(heap));

    new_heap -> size = 0;

    for (int i = 0 ; i < HEAP_SIZE ; i++) {
        new_heap -> array[i] = NULL;
    }

    return new_heap;
}

void push_heap(heap* heap, PCB* proc, int (*compare) (PCB*, PCB*)) {
    if (heap -> size >= HEAP_SIZE) return;

    heap -> array[heap -> size] = proc;

    int idx = heap -> size;
    int parent = 0;

    while (idx != 0) {
        parent = (int) (idx - 1) / 2;

        if ((*compare)(proc, heap -> array[parent]) > 0) {
            swap(heap->array, idx, parent);
            idx = parent;
        }
        else break;
    }
    
    heap -> size += 1;
}

PCB* pop_heap(heap* heap, int (*compare) (PCB*, PCB*)) {
    if (heap -> size == 0) return NULL;


    swap(heap -> array, 0, heap -> size - 1);
    heap -> size -= 1;

    int left = 0;
    int right = 0;
    int idx = 0;
    int new_idx = 0;

    while (idx < heap -> size) {
        left = 2 * idx + 1;
        right = 2 * idx + 2;
        new_idx = idx;

        if (left < heap -> size && heap -> array[left] != NULL) {
            if ((*compare)(heap->array[new_idx], heap->array[left]) < 0) {
                new_idx = left;
            }
        }
        if (right < heap -> size && heap -> array[right] != NULL) {
            if ((*compare)(heap->array[new_idx], heap->array[right]) < 0) {
                new_idx = right;
            }
        }

        if (new_idx != idx) {
            swap(heap -> array, idx, new_idx);
            idx = new_idx;
        }
        else break;

    }

    return heap -> array[heap -> size];
}

void swap(PCB** array, int i, int j) {
    PCB* tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

int compare_Priority_fix(PCB* a, PCB* b) {
    int aP = a -> Priority;
    int bP = b -> Priority;

    if (aP < bP) return 1;
    else if (aP == bP) return compare_SJ_fix(a, b);
    else return -1;
}

int compare_SJ_fix(PCB* a, PCB* b) {
    int aJ = a -> CPU_burst_t;
    int bJ = b -> CPU_burst_t;

    if (aJ <= bJ) return 1;
    else return -1;
}

int compare_Priority_burst(PCB* a, PCB* b) {
    int aP = a -> Priority;
    int bP = b -> Priority;

    if (aP < bP) return 1;
    else if (aP == bP) return compare_SJ_burst(a, b);
    else return -1;
}

int compare_SJ_burst(PCB* a, PCB* b) {
    int aJ = a -> CPU_burst_remain;
    int bJ = b -> CPU_burst_remain;

    if (aJ <= bJ) return 1;
    else return -1;
}