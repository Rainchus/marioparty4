#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

#include "types.h"

typedef struct UnkOvl {
    s32 unk0;
    char unk4[4];
    s32 unk8;
} UnkOvl;

typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;

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
    struct process *last_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    s32 sleep_time;
    void *base_sp;
    jmp_buf jump;
    void (*dtor)(void);
    void *user_data;
} Process;

typedef struct unkStruct1D3B44 {
    struct unkStruct1D3B44 *prev;
    char unk_04[0x1A];
    u16  unk_1E;
} unkStruct1D3B44; // sizeof ???

#endif
