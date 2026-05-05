#include <stdio.h>
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include "sche.h"

#define time_Q 5

PCB* sche_FCFS(queue* ready_q, PCB* run_p) {
    if (run_p == NULL) {
        run_p = q_pop(ready_q);
    }
    return run_p;
}

PCB* sche_RR(queue* ready_q, heap* ready_h, PCB* run_p, int mode) {
    PCB* bf_run_p = run_p;

    if (run_p == NULL) {
        run_p = q_pop(ready_q);
    }
    else if (run_p -> Q <= 0) {
        run_p -> Q = time_Q;
        push_ready_q(ready_q, ready_h, run_p, mode);
        run_p = q_pop(ready_q);
    }

    if (bf_run_p != run_p) {
        run_p -> Q = time_Q;
    }

    return run_p;
}

PCB* sche_non_preem_SJF(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_SJ_fix);
    }

    return run_p;
}

PCB* sche_non_preem_Priority(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_Priority_fix);
    }

    return run_p;
}

PCB* sche_preem_SJF(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_SJ_burst);
    }
    else if (ready_h -> size > 0) {
        if (compare_Priority_burst(run_p, ready_h -> array[0])) {
            push_heap(ready_h, run_p, &compare_SJ_burst);
            run_p = pop_heap(ready_h, &compare_SJ_burst);
        }
    }

    return run_p;
}

PCB* sche_preem_Priority(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_Priority_burst);
    }
    else if (ready_h -> size > 0) {
        if (compare_Priority_burst(run_p, ready_h -> array[0]) < 0) {
            push_heap(ready_h, run_p, &compare_Priority_burst);
            run_p = pop_heap(ready_h, &compare_Priority_burst);
        }
    }

    return run_p;
}