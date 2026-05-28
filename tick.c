#include <stdio.h>
#include <stdlib.h>
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include <unistd.h>

// Core state machine loop governing global time ticks and overall process state transitions
void tick(int n, int mode, int Test_mode, int B_mode) {
    queue* q = q_make();
    PCB* tmp = NULL;
    PCB* run_p = NULL;
    
    qnode* t = NULL;
    int proc_cnt = 0;  // Number of terminated processes
    int pid = 0;
    int time_cnt = 0;  // Global time tick variable
    int wait_t = 0;   // Accumulated Waiting Time
    int turn_t = 0;  // Accumulated Turnaround Time

    int gant[10000] = {-1, };  // Timeline array for Gantt chart generation
    int gant_tmp;

    // Environmental setup (Workload generation based on boundaries)
    if (Test_mode == 1) {
        if (B_mode == 1)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc());  // Balanced
            }
        }
        else if (B_mode == 2)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc_CPU_B());  // CPU-Bound
            }
        }
        else if (B_mode == 3)  {
            for (int i = 0;i<n;i++) {
                q_push(q, make_proc_IO_B());  // I/O-Bound
            }
        }
        else exit(-1);
    }
    else if (Test_mode == 2) {
        // Deterministic manual mapping for isolated testing
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

    // Initialization of scheduling data structures
    queue** job_q = make_job_q(q);  // Array of initial arrival queues
    queue* ready_q = q_make();  // FCFS/RR FIFO queue
    heap* ready_h = make_heap();  // SJF/Priority Min-heap structure
    PCB** wait_list = make_wait_list();  // Static list for I/O blocking

    // Main Engine: Executes until all processes reach the 'Terminated' state
    while (proc_cnt < n) {
        printf("-------------------------\n");
        printf("<time : %d>\n",time_cnt);

        // 1. Scheduler Intervention: Selects and dispatches the next process based on policy
        run_p = sche(ready_q, ready_h, run_p, time_cnt, mode);

        // 2. CPU Execution: Simulates processing and checks for termination
        proc_run(&run_p, time_cnt, &proc_cnt, &turn_t, time_cnt, gant);

        // Accumulate Waiting Time for all processes lingering in the ready queues during this tick
        if (mode <= 2) wait_t += ready_q -> cnt;
        else wait_t += ready_h -> size;
        
        // 3. I/O State Check: Validates I/O completions and triggers CPU Yields
        check_IO(wait_list, &run_p, ready_q, ready_h, mode);
        // 4. Job Arrival Check: Pushes newly arriving processes into the ready state at this tick
        check_job_q(ready_q, ready_h, job_q, time_cnt, mode, &pid);

        time_cnt += 1; // Increment global time tick

    }
    gant[time_cnt] = -999;  // End-of-execution marker

    // Garbage Collection to prevent memory leaks
    free_heap(ready_h);
    free_wait_list(wait_list);
    free_job_q(job_q);
    free_PCB_q(q);
    free_q(ready_q);
    free_q(q);

    // Final Simulation Statistics Output
    printf("===========================================\n");
    printf("All processes are terminated successfully.\n");
    printf("average waiting time : %.3f, average turnarround time : %.3f\n", (double) wait_t / n, (double) turn_t / n);
    printf("-------------------------------------------\n");

    // Gantt Chart Rendering Logic (Outputs only state transition boundaries)
    printf("<Gant Chart>\n");
    gant_tmp = -50;

    for (int idx = 1;;idx++) {
        if (gant_tmp != gant[idx]) {
            printf("|(%d) ", idx-1);
            gant_tmp = gant[idx];

            if (gant[idx] == -999) break;
            else if (gant[idx] == -1) printf("idle ");
            else printf("Process %d ", gant[idx]);
        }
    }
    printf("\n");
}