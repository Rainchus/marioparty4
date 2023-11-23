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

typedef struct unkStruct145A98 {
    s16  unk_00;
    char unk_02[10];
    s16  unk_0C;
    char unk_0E[6];
    u8   unk_14;
    char unk_15[0x53];
} unkStruct145A98; // sizeof 0x68

typedef struct unkStruct1D3B44 {
    struct unkStruct1D3B44 *prev;
    char unk_04[0x1A];
    u16  unk_1E;
} unkStruct1D3B44; // sizeof ???

#endif
