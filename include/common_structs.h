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

#endif