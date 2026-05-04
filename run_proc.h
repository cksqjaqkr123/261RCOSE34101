#ifndef MY_HEADER_SCHE
#define MY_HEADER_SCHE

#include "DS.h"

queue** make_job_q(queue *procs);

PCB** make_wait_list(void);

void check_job_q(queue* ready_q, queue** job_q, int tick, int mode);

void check_IO(PCB** wait_list, PCB** run_p, queue* ready_q, int mode);

void push_ready_q(queue* ready_q, PCB* proc, int mode);

PCB* sche(queue* ready_q, PCB* run_p, int tick, int mode);

void proc_run(PCB** run_p, int tick, int* proc_cnt);

#endif