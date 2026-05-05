#include <stdio.h>
#include <stdlib.h>
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"

void tick(int n, int mode) {
    queue* q = q_make();
    PCB* tmp = NULL;
    PCB* run_p = NULL;
    
    qnode* t = NULL;
    int proc_cnt = 0;
    int time_cnt = 0;
    int wait_t = 0;
    int turn_t = 0;


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
        proc_run(&run_p, time_cnt, &proc_cnt, &turn_t);

        wait_t += ready_q -> cnt;

        check_IO(wait_list, &run_p, ready_q, mode);
        check_job_q(ready_q, job_q, time_cnt, mode);
        

        time_cnt += 1;

    }

    heap* x = make_heap();

    for (int i = 0;i<n;i++) {
        tmp = q_pop(q);
        push_heap(x, tmp, &compare_Job);
        q_push(q, tmp);
    }
    for (int i = 0;i<n;i++) {
        tmp = pop_heap(x, &compare_Job);
        printf("pid : %d, cpu_burst : %d\n", tmp -> PID, tmp -> CPU_burst_t);
    }

    printf("***************************\n");
    
    for (int i = 0;i<n;i++) {
        tmp = q_pop(q);
        push_heap(x, tmp, &compare_Priority);
        q_push(q, tmp);
    }
    for (int i = 0;i<n;i++) {
        tmp = pop_heap(x, &compare_Priority);
        printf("pid : %d, priority : %d, cpu_burst : %d\n", tmp -> PID, tmp -> Priority, tmp -> CPU_burst_t);
    }

    for (int i = 0;i<n;i++) {
        tmp = q_pop(q);
        free(tmp);
    }

    printf("===========================\n");
    printf("All processes are terminated successfully.\n");
    printf("average waiting time : %.3f, average turnarround time : %.3f\n", (double) wait_t / n, (double) turn_t / n);
}