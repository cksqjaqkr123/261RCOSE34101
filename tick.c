#include <stdio.h>
#include <stdlib.h>
#include "DS.h"
#include "run_proc.h"

void tick(int n, int mode) {
    queue* q = q_make();
    PCB* tmp = NULL;
    PCB* run_p = NULL;

    qnode* t = NULL;
    int proc_cnt = 0;
    int time_cnt = 0;

    for (int i = 0;i<n;i++) {
        q_push(q, make_proc(i));
    }

    queue** job_q = make_job_q(q);
    queue* ready_q = q_make();
    PCB** wait_list = make_wait_list();

    while (proc_cnt < n) {
        printf("------------------------\n");
        printf("time : %d\n",time_cnt);
        
        run_p = sche(ready_q, run_p, time_cnt, mode);
        proc_run(run_p, time_cnt, &proc_cnt);
        check_IO(wait_list, &run_p, ready_q, mode);
        check_job_q(ready_q, job_q, time_cnt, mode);
        

        time_cnt += 1;

    }

    for (int i = 0;i<n;i++) {
        tmp = q_pop(q);
        free(tmp);
    }


}