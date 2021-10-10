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

    //printf("Alarm Interval: %d\t Alarm Handler: %p \t Alarm Handler: %p \n", p->alarm.interval, p->alarm.handler, handler_pointer);

    return 0;
}
uint64 sys_sigreturn(void)
{
    struct proc *p = myproc();
    p->trapframe->epc = p->alarm.epc;
    p->trapframe->ra = p->alarm.ra;
    p->trapframe->sp = p->alarm.sp;
    p->trapframe->gp = p->alarm.gp;
    p->trapframe->tp = p->alarm.tp;
    p->trapframe->t0 = p->alarm.t0;
    p->trapframe->t1 = p->alarm.t1;
    p->trapframe->t2 = p->alarm.t2;
    p->trapframe->s0 = p->alarm.s0;
    p->trapframe->s1 = p->alarm.s1;
    p->trapframe->a0 = p->alarm.a0;
    p->trapframe->a1 = p->alarm.a1;
    p->trapframe->a2 = p->alarm.a2;
    p->trapframe->a3 = p->alarm.a3;
    p->trapframe->a4 = p->alarm.a4;
    p->trapframe->a5 = p->alarm.a5;
    p->trapframe->a6 = p->alarm.a6;
    p->trapframe->a7 = p->alarm.a7;
    p->trapframe->s2 = p->alarm.s2;
    p->trapframe->s3 = p->alarm.s3;
    p->trapframe->s4 = p->alarm.s4;
    p->trapframe->s5 = p->alarm.s5;
    p->trapframe->s6 = p->alarm.s6;
    p->trapframe->s7 = p->alarm.s7;
    p->trapframe->s8 = p->alarm.s8;
    p->trapframe->s9 = p->alarm.s9;
    p->trapframe->s10 = p->alarm.s10;
    p->trapframe->s11 = p->alarm.s11;
    p->trapframe->t3 = p->alarm.t3;
    p->trapframe->t4 = p->alarm.t4;
    p->trapframe->t5 = p->alarm.t5;
    p->trapframe->t6 = p->alarm.t6;

    p->alarm.tick_counter = 0;
    p->alarm.handling = 0;
    return 0;
}
