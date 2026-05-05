#include "tick.h"
#include "DS.h"
#include "DS_2.h"
#include "run_proc.h"
#include <stdio.h>
#include <stdlib.h>
#define N 5

int main(void) {

    int mode = 0;

    printf("모드를 입력 (1 : FCFS, 2 : RR, 3 : Non-p-SJF, 4 : Non-p-Priority, 5 : p-SJF, 6 : p-Priority)\n");
    scanf("%d", &mode);

    srand(10000);


    tick(N, mode);
}
