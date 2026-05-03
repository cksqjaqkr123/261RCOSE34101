#include "DS.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
    srand(10000);

    queue* q = q_make();
    PCB* tmp = NULL;

    for (int i = 0;i<10;i++) {
        q_push(q, make_proc());
    }

    for (int i = 0;i<10;i++) {
        tmp = q_pop(q);

        print_PCB(tmp);
        printf("%d\n\n", q -> cnt);

        free(tmp);
    }

    free(q);
}
