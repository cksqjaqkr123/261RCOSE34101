#ifndef MY_HEADER_RUN_PROC
#define MY_HEADER_RUN_PROC

#include "DS.h"
#include "sche.h"

void check_job_q(queue* ready_q, heap* ready_h, queue** job_q, int tick, int mode, int* pid);

void check_IO(PCB** wait_list, PCB** run_p, queue* ready_q, heap* ready_h, int mode);

void push_ready_q(queue* ready_q, heap* ready_h, PCB* proc, int mode);

PCB* sche(queue* ready_q, heap* ready_h, PCB* run_p, int tick, int mode);

void proc_run(PCB** run_p, int tick, int* proc_cnt, int* turn_t, int* idle);

#endif