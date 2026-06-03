#include "tick.h"
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int mode = 0;
    int Test_mode = 0;
    int n = 0;
    int seed = 0;
    int B_mode = 0;
    char* sche;

    while (1) {
        printf("Test Mode (1 : Random Number, 2 : Test Case for Report)\n");
        scanf("%d", &Test_mode);
        printf("Please type the following desired sches\n");
        printf("1 : FCFS, 2 : RR, 3 : Non-p-SJF, 4 : Non-p-Priority, 5 : p-SJF, 6 : p-Priority)\n");
        scanf("%d", &mode);

        if ((Test_mode == 1 || Test_mode == 2) && (mode > 0 && mode < 7)) break;
        printf("Incorrect number range. Retry typing.\n");
    }

    if (Test_mode == 1) {
        while(1) {
            printf("Type the number of processes\n");
            scanf("%d", &n);
            if (n > 0) break;
            printf("Incorrect number range. Retry typing.\n");
        }
        printf("Type the desired seed\n");
        scanf("%d", &seed);
        srand(seed);

        while(1) {
            printf("Type the Bound Mode\n");
            printf("1 : balanced, 2 : CPU Bound, 3: I/O Bound\n");
            scanf("%d", &B_mode);
            if (B_mode >= 1 && B_mode <= 3) break;
            printf("Incorrect number range. Retry typing.\n");
        }
    }
    else if (Test_mode == 2) n = 4;

    tick(n, mode, Test_mode, B_mode);

    switch(mode) {
        case 1:
            sche = "FCFS";
            break;
        case 2:
            sche = "RR";
            break;
        case 3:
            sche = "Non-p-SJF";
            break;
        case 4:
            sche = "Non-p-Priority";
            break;
        case 5:
            sche = "p-SJF";
            break;
        case 6:
            sche = "p-Priority";
            break;
    }
    printf("---------------------------\n");
    printf("Simulator Ended : %s, N procs : %d, Seed : %d, Bound flag : %d\n", sche, n, seed, B_mode);
}
