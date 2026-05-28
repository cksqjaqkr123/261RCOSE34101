#include <stdio.h>
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include "sche.h"

#define time_Q 5

// First-Come, First-Served (FCFS)
// Non-preemptive. Simply pops the first arriving process from the Ready Queue in O(1) time.

PCB* sche_FCFS(queue* ready_q, PCB* run_p) {
    if (run_p == NULL) {
        run_p = q_pop(ready_q);
    }
    return run_p;
}

// Round Robin (RR)
// Preemptive. Forces a context switch when the allocated time quantum (time_Q) is exhausted.
PCB* sche_RR(queue* ready_q, heap* ready_h, PCB* run_p, int mode) {
    PCB* bf_run_p = run_p;

    if (run_p == NULL) {
        run_p = q_pop(ready_q);  // Assign a process if CPU is idle
    }
    else if (run_p -> Q <= 0) {
        // Quantum expired: push current process back to Ready Queue and fetch next
        run_p -> Q = time_Q;
        push_ready_q(ready_q, ready_h, run_p, mode);
        run_p = q_pop(ready_q);
    }

    // Reset quantum if a context switch occurred
    if (bf_run_p != run_p) {
        run_p -> Q = time_Q;
    }

    return run_p;
}

// Non-preemptive Shortest Job First (SJF)
// Non-preemptive. Selects the process with the shortest CPU burst from the Min-heap only when CPU is idle.
PCB* sche_non_preem_SJF(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_SJ_fix);
    }

    return run_p;
}

// Non-preemptive Priority
// Non-preemptive. Selects the process with the highest priority (lowest value).
PCB* sche_non_preem_Priority(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_Priority_fix);
    }

    return run_p;
}

// Preemptive SJF (Shortest Remaining Time First)
// Preemptive. Compares remaining burst time every tick. Preempts immediately if a shorter job arrives.
PCB* sche_preem_SJF(heap* ready_h, PCB* run_p) {
    if (run_p == NULL) {
        run_p = pop_heap(ready_h, &compare_SJ_burst);
    }
    else if (ready_h -> size > 0) {
        // Compare remaining time of running process vs. root of Min-heap
        if (compare_SJ_burst(run_p, ready_h -> array[0]) < 0) {
            push_heap(ready_h, run_p, &compare_SJ_burst);   // Return current process to heap
            run_p = pop_heap(ready_h, &compare_SJ_burst);   // Preempt with new process
        }
    }

    return run_p;
}

// Preemptive Priority
// Preemptive. Compares priority values every tick. Preempts if a higher priority process arrives.
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