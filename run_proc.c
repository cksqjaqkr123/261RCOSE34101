#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include "sche.h"
#include <stdio.h>
#include <stdlib.h>


#define time_Q 5

void check_job_q(queue* ready_q, queue** job_q, int tick, int mode) {
    if (tick >= 51) return;

    qnode* tmp = job_q[tick] -> head;

    while (tmp != NULL) {
        printf("process arrived at %d (pid : %d)\n", tick, tmp -> proc -> PID);
        printf("CPU burst time : %d, I/O burst time : %d, I/O cycle : %d\n", tmp -> proc -> CPU_burst_t, tmp -> proc -> IO_burst_t, tmp -> proc -> IO_cycle);
        push_ready_q(ready_q, tmp -> proc, mode);
        tmp = tmp -> nextq;
    }
}

void check_IO(PCB** wait_list, PCB** run_p, queue* ready_q, int mode) {
    int flag = 0;
    int idx = -1;

    for (int i = 0; i < 100; i++) {
        if (wait_list[i] != NULL) {
            wait_list[i] -> IO_burst_remain -= 1;
            if (wait_list[i] -> IO_burst_remain == 0) {
                printf("process's I/O task ended (PID : %d)\n", wait_list[i] -> PID);
                wait_list[i] -> IO_burst_remain = wait_list[i] -> IO_burst_t;
                push_ready_q(ready_q, wait_list[i], mode);
                wait_list[i] = NULL;

                if (flag == 0) {
                    flag = 1;
                    idx = i;
                }
            }
        }
        else {
            if (flag == 0) {
                flag = 1;
                idx = i;
            }
        }
    }

    if (*run_p == NULL) return;

    if ((*run_p) -> IO_cycle_remain == 0) {
        (*run_p) -> IO_cycle_remain = (*run_p) -> IO_cycle;
        (*run_p) -> Q = time_Q;
        if (idx < 0) kernel_panic();
        else {
        printf("into waiting status due to I/O cycle (PID : %d)\n", (*run_p) -> PID);
        wait_list[idx] = *run_p;
        *run_p = NULL;
        }
    }
}

void push_ready_q(queue* ready_q, PCB* proc, int mode) {
    q_push(ready_q, proc);
}

PCB* sche(queue* ready_q, PCB* run_p, int tick, int mode) {

    if (mode == 1) {
        run_p = sche_FCFS(ready_q, run_p);
    }
    else if (mode == 2) {
        run_p = sche_RR(ready_q, run_p, mode);
    }

    return run_p;
};

void proc_run(PCB** run_p, int tick, int* proc_cnt, int* turn_t) {
    if (*run_p == NULL) return;

    (*run_p) -> CPU_burst_remain -= 1;
    (*run_p) -> IO_cycle_remain -= 1;
    (*run_p) -> Q -= 1;

    if ((*run_p) -> CPU_burst_remain == 0) {
        printf("process was successfully terminated at %d (pid : %d)\n", tick, (*run_p) -> PID);
        *proc_cnt += 1;
        *turn_t += tick - (*run_p) -> Arrival_t;
        *run_p = NULL;
    }
    else {
        printf("process (PID : %d) is running. (CPU burst Left : %d\n)", (*run_p) -> PID, (*run_p) -> CPU_burst_remain);
    }
    return;
}





