#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/proc.h"
#include "kernel/param.h"
//#include "sys/types.h"
//#include "unistd.h"
//#include "time.h"

int main(){
    int ticket_for_test = 50;

    if(settickets(ticket_for_test) == -1){
        exit(-1);
    }

    struct processes_info *p;

    getprocessesinfo(p);

    printf("number of process: %d\n", p->num_processes);



    exit(0);
}

