#ifndef _COMMON_STRUCTS_H
#define _COMMON_STRUCTS_H

#include "types.h"
#include "common_enums.h"
#include "dolphin/dvd.h"

typedef struct om_ovl_his_data {
    OverlayID overlay;
    int event;
    int stat;
} omOvlHisData;

typedef struct Vec2f {
    f32 x;
    f32 y;
} Vec2f;

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

typedef struct BoardStateSubStruct {
/* 0x00 */ s32 unk0;
/* 0x04 */ u16 unk4;
/* 0x06 */ u16 unk6;
/* 0x08 */ s16 unk8;
} BoardStateSubStruct;

typedef struct BoardState {
/* 0x00 */ char unk00[0x04];
/* 0x04 */ s8 curTurnCount;
/* 0x05 */ s8 maxTurnCount;
/* 0x06 */ char unk06[0x02];
/* 0x08 */ u8 unk08;
/* 0x09 */ s8 doubleCoinsOnSpaceBool;
/* 0x0A */ s8 curPlayerIndex;
/* 0x0C */ char unk0C[4];
/* 0x10 */ BoardStateSubStruct unk10;
/* 0x1A */ char unk1A[0xC6];
} BoardState; //8018fcf8, sizeof 0xE0

typedef struct {
    u8 unk0 : 2;
} PlayerFlags;

typedef struct Player {
/* 0x00 */ u8 	characterID;
/* 0x01 */ s8 	unk01;
/* 0x02 */ s8 	unk02;
/* 0x03 */ s8 	unk03;
/* 0x04 */ s8 	controllerPort;
/* 0x05 */ s8 	items[3];
/* 0x08 */ PlayerFlags flags; //0x02 mini mushroom, 0x04 mega mushroom
/* 0x09 */ s8 	placement; //0x80 1st, 0x20 2nd, 0x40 3rd, 0x60 4th
/* 0x0A */ u8 	spacesLeftToMove;
/* 0x0B */ char unk_0B[5];
/* 0x10 */ s16 	nextABSSpaceIndex;
/* 0x12 */ char unk_12[2];
/* 0x14 */ s8 	blueSpacesLanded;
/* 0x15 */ s8 	redSpacesLanded;
/* 0x16 */ s8 	happeningSpacesLanded;
/* 0x17 */ s8 	chanceSpacesLanded;
/* 0x18 */ char unk_18;
/* 0x19 */ s8 	battleSpacesLanded;
/* 0x1A */ s8 	itemSpacesLanded;
/* 0x1B */ s8 	springSpacesLanded;
/* 0x1C */ s16	coins;
/* 0x1E */ char unk_1E[2];
/* 0x20 */ s16	totalCoinsCollected;
/* 0x22 */ s16 	coinPeak;
/* 0x24 */ char unk_24[6];
/* 0x2A */ s16 	stars;
/* 0x2C */ char unk_2C[4];
} Player; //size of 0x30

typedef struct om_obj_data {
    u16 stat;
    s16 next_idx_alloc;
    s16 prio;
    s16 prev;
    s16 next;
    s16 next_idx;
    s16 group;
    u16 group_idx;
    int unk10;
    void (*func)(struct om_obj_data *);
    Vec3f trans;
    Vec3f rot;
    Vec3f scale;
    u16 mdlcnt;
    s16 *model;
    u16 mtncnt;
    s16 *motion;
    int work[4];
    void *data;
} omObjData;

#endif
