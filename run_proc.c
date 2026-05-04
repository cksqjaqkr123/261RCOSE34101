#include "run_proc.h"
#include <stdio.h>
#include <stdlib.h>

queue** make_job_q(queue* procs) {
    queue** new_job_q = malloc(sizeof(queue*) * 51);
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
    PCB** new_wait_list = malloc(sizeof(PCB*) * 100);
    for (int i = 0; i < 100; i++) {
        new_wait_list[i] = NULL;
    }
    return new_wait_list;
}

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
    if (run_p == NULL) {
        run_p = q_pop(ready_q);
    }
    return run_p;
};

void proc_run(PCB** run_p, int tick, int* proc_cnt) {
    if (*run_p == NULL) return;

    (*run_p) -> CPU_burst_remain -= 1;
    (*run_p) -> IO_cycle_remain -= 1;

    if ((*run_p) -> CPU_burst_remain == 0) {
        printf("process was successfully terminated at %d (pid : %d)\n", tick, (*run_p) -> PID);
        *proc_cnt += 1;
        *run_p = NULL;
    }
    else {
        printf("process (PID : %d) is running. (CPU burst Left : %d\n)", (*run_p) -> PID, (*run_p) -> CPU_burst_remain);
    }
    return;
}





