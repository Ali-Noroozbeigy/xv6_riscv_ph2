#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/info.h"
#include "kernel/param.h"

#define N  10

void
print(const char *s)
{
    write(1, s, strlen(s));
}

void
forktest(void)
{
    int n, pid;

    print("fork test\n");

    for(n=0; n<N; n++){
        pid = fork();
        int x = 0;
        if(pid < 0)
            break;
        if(pid == 0){
            for(int f=0; f<10; f++)
                x+=1;
            exit(0);
        }
    }

//    if(n == N){
//        print("fork claimed to work N times!\n");
//        exit(1);
//    }

    for(; n > 0; n--){
        if(wait(0) < 0){
            print("wait stopped early\n");
            exit(1);
        }
    }

    if(wait(0) != -1){
        print("wait got too many\n");
        exit(1);
    }

    print("fork test OK\n");
}

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
        for(int i=0; i<10000000 ; i++)
            x+=1;
    }

    else{
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

