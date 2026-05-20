#include <stdio.h>
#include <stdlib.h>
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include <unistd.h>

void tick(int n, int mode, int Test_mode, int B_mode) {
    queue* q = q_make();
    PCB* tmp = NULL;
    PCB* run_p = NULL;
    
    qnode* t = NULL;
    int proc_cnt = 0;
    int pid = 0;
    int time_cnt = 0;
    int wait_t = 0;
    int turn_t = 0;
    int idle_flag = 0;

    if (Test_mode == 1) {
        if (B_mode == 1)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc());
            }
        }
        else if (B_mode == 2)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc_CPU_B());
            }
        }
        else if (B_mode == 3)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc_IO_B());
            }
        }
        else exit(-1);
    }
    else if (Test_mode == 2) {
        tmp = make_non_rand_proc(0, 3, 8, 0, 1000000);
        q_push(q, tmp);
        tmp = make_non_rand_proc(1, 1, 4, 0, 1000000);
        q_push(q, tmp);
        tmp = make_non_rand_proc(2, 4, 9, 0, 1000000);
        q_push(q, tmp);
        tmp = make_non_rand_proc(0, 2, 5, 0, 1000000);
        q_push(q, tmp);
        tmp = NULL;
    }
    else exit(-1);

    queue** job_q = make_job_q(q);
    queue* ready_q = q_make();
    heap* ready_h = make_heap();
    PCB** wait_list = make_wait_list();

    while (proc_cnt < n) {
        printf("-------------------------\n");
        printf("<time : %d>\n",time_cnt);
        
        idle_flag = 0;

        run_p = sche(ready_q, ready_h, run_p, time_cnt, mode);
        proc_run(&run_p, time_cnt, &proc_cnt, &turn_t, &idle_flag);

        if (idle_flag) printf("[idle]\n");

        if (mode <= 2) wait_t += ready_q -> cnt;
        else wait_t += ready_h -> size;
        

        check_IO(wait_list, &run_p, ready_q, ready_h, mode);
        check_job_q(ready_q, ready_h, job_q, time_cnt, mode, &pid);
        
        time_cnt += 1;

        usleep(500000);

    }


    for (int i = 0;i<n;i++) {
        tmp = q_pop(q);
        free(tmp);
    }

    printf("===========================\n");
    printf("All processes are terminated successfully.\n");
    printf("average waiting time : %.3f, average turnarround time : %.3f\n", (double) wait_t / n, (double) turn_t / n);
}