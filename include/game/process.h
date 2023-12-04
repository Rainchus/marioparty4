#ifndef _GAME_PROCESS_H
#define _GAME_PROCESS_H

#include "dolphin/types.h"

#define PROCESS_STAT_PAUSE 0x1
#define PROCESS_STAT_UPAUSE 0x2
#define PROCESS_STAT_PAUSE_EN 0x4
#define PROCESS_STAT_UPAUSE_EN 0x8

typedef struct jump_buf {
    u32 lr;
    u32 cr;
    u32 sp;
    u32 r2;
    u32 pad;
    u32 regs[19];
    double flt_regs[19];
} jmp_buf;

typedef struct process {
    struct process *next;
    struct process *prev;
    struct process *child;
    struct process *parent;
    struct process *next_child;
    struct process *first_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    int sleep_time;
    u32 base_sp;
    jmp_buf jump;
    void (*dtor)(void);
    void *user_data;
} Process;

void HuPrcInit(void);
void HuPrcEnd(void);
Process *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size);
void HuPrcChildLink(Process *parent, Process *child);
void HuPrcChildUnlink(Process *process);
Process *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, Process *parent);
void HuPrcChildWatch(void);
Process *HuPrcCurrentGet(void);
int HuPrcKill(Process *process);
void HuPrcChildKill(Process *process);
void HuPrcSleep(int time);
void HuPrcVSleep(void);
void HuPrcWakeup(Process *process);
void HuPrcDestructorSet2(Process *process, void (*func)(void));
void HuPrcDestructorSet(void (*func)(void));
void HuPrcCall(int tick);
void *HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);
void HuPrcSetStat(Process *process, u16 value);
void HuPrcResetStat(Process *process, u16 value);
void HuPrcAllPause(int flag);
void HuPrcAllUPause(int flag);

#endif