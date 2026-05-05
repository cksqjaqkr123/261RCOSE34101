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

PCB* sche_RR(queue* ready_q, PCB* run_p, int mode) {
    PCB* bf_run_p = run_p;

    if (run_p == NULL) {
        run_p = q_pop(ready_q);
    }
    else if (run_p -> Q <= 0) {
        run_p -> Q = time_Q;
        push_ready_q(ready_q, run_p, mode);
        run_p = q_pop(ready_q);
    }

    if (bf_run_p != run_p) {
        run_p -> Q = time_Q;
    }

    return run_p;
}