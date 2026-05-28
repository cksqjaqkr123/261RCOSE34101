#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include "sche.h"
#include <stdio.h>
#include <stdlib.h>


#define time_Q 5

// Transfers processes arriving at the current tick from Job Queue to Ready Queue (State transition: New -> Ready)
void check_job_q(queue* ready_q, heap* ready_h, queue** job_q, int tick, int mode, int* pid) {
    if (tick >= 51) return;

    qnode* tmp = job_q[tick] -> head;

    while (tmp != NULL) {
        tmp -> proc -> PID = *pid;
        *pid += 1;
        printf("******************************************************\n");
        printf("process (PID : %d) was arrived.\n", tmp -> proc -> PID);
        printf("CPU burst time : %d, I/O burst time : %d, I/O cycle : %d\n", tmp -> proc -> CPU_burst_t, tmp -> proc -> IO_burst_t, tmp -> proc -> IO_cycle);
        printf("Priority : %d\n", tmp -> proc -> Priority);
        printf("******************************************************\n");
        // Push to appropriate queue/heap based on scheduling policy
        push_ready_q(ready_q, ready_h, tmp -> proc, mode);
        tmp = tmp -> nextq;
    }
}

// Polls the Wait List to identify completed I/O operations and triggers CPU Yields
void check_IO(PCB** wait_list, PCB** run_p, queue* ready_q, heap* ready_h, int mode) {
    int flag = 0;
    int idx = -1;

    // Linearly traverses the wait_list array (O(N) polling)
    for (int i = 0; i < 100; i++) {
        if (wait_list[i] != NULL) {
            wait_list[i] -> IO_burst_remain -= 1;

            // Re-enters Ready state upon I/O completion (State transition: Wait -> Ready)
            if (wait_list[i] -> IO_burst_remain == 0) {
                printf("process (PID : %d) I/O task ended.\n", wait_list[i] -> PID);
                wait_list[i] -> IO_burst_remain = wait_list[i] -> IO_burst_t;
                push_ready_q(ready_q, ready_h, wait_list[i], mode);
                wait_list[i] = NULL;

                if (flag == 0) {
                    flag = 1;
                    idx = i;
                }
            }
        }
        else {
            // Caches empty slot index for potential new Wait process insertions
            if (flag == 0) {
                flag = 1;
                idx = i;
            }
        }
    }

    if (*run_p == NULL) return;

    // Checks if the running process hit its I/O cycle boundary (State transition: Run -> Wait)
    if ((*run_p) -> IO_cycle_remain == 0) {
        (*run_p) -> IO_cycle_remain = (*run_p) -> IO_cycle;
        (*run_p) -> Q = time_Q;
        if (idx < 0) kernel_panic(); // Throws panic on Wait list overflow
        else {
        printf("into waiting status due to I/O cycle (PID : %d)\n", (*run_p) -> PID);
        wait_list[idx] = *run_p;  // Voluntary CPU Yield
        *run_p = NULL;
        }
    }
}

// Wrapper function to insert into FIFO Queue or Min-heap depending on the selected mode
void push_ready_q(queue* ready_q, heap* ready_h, PCB* proc, int mode) {
    if (mode <= 2) q_push(ready_q, proc);
    else if (mode == 3) push_heap(ready_h, proc, &compare_SJ_fix);
    else if (mode == 4) push_heap(ready_h, proc, &compare_Priority_fix);
    else if (mode == 5) push_heap(ready_h, proc, &compare_SJ_burst);
    else if (mode == 6) push_heap(ready_h, proc, &compare_Priority_burst);
}

// Dispatcher function triggering the specific scheduling policy logic
PCB* sche(queue* ready_q, heap* ready_h, PCB* run_p, int tick, int mode) {

    if (mode == 1) {
        run_p = sche_FCFS(ready_q, run_p);
    }
    else if (mode == 2) {
        run_p = sche_RR(ready_q, ready_h, run_p, mode);
    }
    else if (mode == 3) {
        run_p = sche_non_preem_SJF(ready_h, run_p);
    }
    else if (mode == 4) {
        run_p = sche_non_preem_Priority(ready_h, run_p);
    }
    else if (mode == 5) {
        run_p = sche_preem_SJF(ready_h, run_p);
    }
    else if (mode == 6) {
        run_p = sche_preem_Priority(ready_h, run_p);
    }

    return run_p;
};

// Simulates CPU execution tick and handles process termination
void proc_run(PCB** run_p, int tick, int* proc_cnt, int* turn_t, int time_cnt, int gant[]) {
    if (*run_p == NULL) {
        gant[time_cnt] = -1;
        printf("[idle]\n");
        return;
    }

    // Decrement operational counters by 1 tick
    (*run_p) -> CPU_burst_remain -= 1;
    (*run_p) -> IO_cycle_remain -= 1;
    (*run_p) -> Q -= 1;

    printf("process (PID : %d) was run. (CPU burst Left : %d)\n", (*run_p) -> PID, (*run_p) -> CPU_burst_remain);
    gant[time_cnt] = (*run_p) -> PID;  // Record execution for Gantt chart
    
    // Complete Process Termination (State transition: Run -> Terminated)
    if ((*run_p) -> CPU_burst_remain == 0) {
        printf("...and successfully terminated.\n");
        *proc_cnt += 1;
        *turn_t += tick - (*run_p) -> Arrival_t; // Accumulate Turnaround Time
        *run_p = NULL;  // Free CPU resource
    }

    return;
}





