#ifndef XV6_RISCV_PH2_INFO_H
#define XV6_RISCV_PH2_INFO_H
#include "param.h"
struct processes_info{
    int num_processes;
    int pids[NPROC];
    int ticks[NPROC];
    int tickets[NPROC];
};
#endif //XV6_RISCV_PH2_INFO_H
