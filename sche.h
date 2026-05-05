#ifndef MY_HEADER_SCHE
#define MY_HEADER_SCHE

#include "DS.h"
#include "DS_2.h"

PCB* sche_FCFS(queue* ready_q, PCB* run_p);
PCB* sche_RR(queue* ready_q, heap* ready_h, PCB* run_p, int mode);
PCB* sche_non_preem_SJF(heap* ready_h, PCB* run_p);
PCB* sche_non_preem_Priority(heap* ready_h, PCB* run_p);
PCB* sche_preem_SJF(heap* ready_h, PCB* run_p);
PCB* sche_preem_Priority(heap* ready_h, PCB* run_p);

#endif

