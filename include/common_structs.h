#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

#include "types.h"
#include "dolphin/dvd.h"

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
    struct process *first_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    s32 sleep_time;
    u32 base_sp;
    jmp_buf jump;
    void (*dtor)(void);
    void *user_data;
} Process;

typedef struct player_config {
    s16 character;
    s16 pad_idx;
    s16 diff;
    s16 group;
    s16 iscom;
} PlayerConfig;

typedef struct wipe_state {
    u8 unk[52];
    float duration;
    u8 unk2[20];
} WipeState;

typedef struct file_list_entry {
    char *name;
    s32 file_id;
} FileListEntry;

typedef struct data_read_stat {
    s32 dir_id;
    void *dir;
    void *file;
    u32 raw_len;
    u32 comp_type;
    BOOL used;
    s32 num;
    u32 status;
    DVDFileInfo file_info;
} DataReadStat;

#endif
