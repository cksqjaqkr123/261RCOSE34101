#ifndef MY_HEADER_SCHE
#define MY_HEADER_SCHE

#include "DS.h"

PCB* sche_FCFS(queue* ready_q, PCB* run_p);
PCB* sche_RR(queue* ready_q, PCB* run_p, int mode);

#endif

