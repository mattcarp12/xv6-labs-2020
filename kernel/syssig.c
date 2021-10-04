//
// Signal handler system calls

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"


uint64 sys_sigalarm(void)
{
    struct proc *p = myproc();
    if (argint(0, &p->alarm.interval) < 0)
        return -1;
    uint64 handler_pointer;
    if (argaddr(1, &handler_pointer) < 0)
        return -1;

    p->alarm.handler = (void (*)())handler_pointer;

    //printf("Alarm Ticks: %d\t Alarm Handler: %p \t Alarm Handler: %p \n", p->alarm_ticks, p->alarm_handler, handler_pointer);

    return 0;
}
uint64 sys_sigreturn(void)
{
    return 0;
}

