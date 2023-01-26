#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/info.h"
#include "kernel/param.h"

#define N  1000

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
        if(pid < 0)
            break;
        if(pid == 0)
            exit(0);
    }

    if(n == N){
        print("fork claimed to work N times!\n");
        exit(1);
    }

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

//    forktest();

//    struct processes_info p;
//    printf("%p", &p);
//    getprocessesinfo(&p);

//    printf("number of process: %d\n", p.num_processes);
//    for (int i=0; i<NPROC; i++){
//        printf("pid[%d]: %d\n", i, p.pids[i]);
//        printf("tickets[%d]: %d\n", i, p.tickets[i]);
//        printf("ticks[%d]: %d\n", i, p.ticks[i]);
//    }

/* part without bug */
    struct processes_info p;
    getprocessesinfo(&p);

    exit(0);
}

