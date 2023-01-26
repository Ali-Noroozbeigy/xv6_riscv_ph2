#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/info.h"
#include "kernel/param.h"

int main(){

    if(settickets(100) == -1){
        exit(-1);
    }

    int pid_1 = fork();

    if (pid_1 > 0){
        int pid_2 = fork();

        if (pid_2 == 0){
            settickets(200);
            int x = 0;
            for(int i=0; i<10000000; i++)
                x += 1;
        }

        else{
            int x = 0;
            for (int i = 0; i < 10000000; i++)
                x += 1;

            struct processes_info p;
            getprocessesinfo(&p);

            printf("number of process: %d\n", p.num_processes);
            for (int i=0; i<p.num_processes; i++){
                printf("pid[%d]: %d\n", i, p.pids[i]);
                printf("tickets[%d]: %d\n", i, p.tickets[i]);
                printf("ticks[%d]: %d\n", i, p.ticks[i]);
            }

            wait(0);
            wait(0);
        }
    }

    else{
        settickets(300);
        int x = 0;
        for(int i=0; i<10000000; i++)
            x += 1;
    }

    exit(0);
};