#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/info.h"
#include "kernel/param.h"

int main(){
    int ticket_for_test = 50;

    if(settickets(ticket_for_test) == -1){
        exit(-1);
    }


    struct processes_info p;
    getprocessesinfo(&p);

    printf("number of process: %d\n", p.num_processes);
    for (int i=0; i<p.num_processes; i++){
        printf("pid[%d]: %d\n", i, p.pids[i]);
        printf("tickets[%d]: %d\n", i, p.tickets[i]);
        printf("ticks[%d]: %d\n", i, p.ticks[i]);
    }

    if(fork()==0){
        int x = 0;
        for(int i=0; i<160000000 ; i++)
            x+=1;
    }

    else{
        int x = 0;
        for(int i=0; i<80000000 ; i++)
            x+=1;
        getprocessesinfo(&p);

        printf("number of process: %d\n", p.num_processes);
        for (int i = 0; i < p.num_processes; i++) {
            printf("pid[%d]: %d\n", i, p.pids[i]);
            printf("tickets[%d]: %d\n", i, p.tickets[i]);
            printf("ticks[%d]: %d\n", i, p.ticks[i]);
        }
    }

    exit(0);
}

