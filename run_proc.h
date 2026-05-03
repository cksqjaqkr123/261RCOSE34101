#ifndef MY_HEADER_SCHE
#define MY_HEADER_SCHE

#include "DS.h"

queue** make_job_q(queue *procs);

void check_job_q(queue* ready_q, queue** job_q, int tick, int mode);

void check_IO(queue* wait_q);

void push_ready_q(queue* ready_q, PCB* proc, int mode);

PCB* sche(queue* ready_q, PCB* run_p, int tick, int mode);

void proc_run(PCB* run_p, int tick, int* proc_cnt);

#endif