#ifndef _GAME_HSFMAN_H
#define _GAME_HSFMAN_H

#include "common.h"
#include "game/memory.h"
#include "game/hsfformat.h"
#include "game/sprite.h"

typedef struct model_data {
    u8 unk_00;
    u8 unk_01;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    char unk_10[0x12];
    u16 unk_22;
    char unk_24[0x24];
    u32 unk_48;
    char unk_4C[0x4];
    u32 unk_50;
    u32 unk_54;
    char unk_58[0xC];
    f32 unk_64;
    char unk_68[0xC];
    f32 unk_74;
    char unk_78[0x1C];
    f32 unk_94;
    char unk_98[0x2C];
    HsfData *hsfData;
    char unk_C8[0x4];
    f32 unk_CC;
    f32 unk_D0;
    f32 unk_D4;
    f32 unk_D8;
    f32 unk_DC;
    f32 unk_E0;
    f32 unk_E4;
    f32 unk_E8;
    f32 unk_EC;
    f32 unk_F0[3][4];
    char unk_120[0x4];
} ModelData;
typedef struct ThreeDCameraStruct {
    f32 unk_00;
    f32 start;
    f32 end;
    char unk_04[0x4C];
} ThreeDCameraStruct;
typedef struct ThreeDProjectionStruct {
    s8 unk_00;
    char unk_01[0x3];
    AnimData *unk_04;
    char unk_08[0xC];
    Point3d unk_14;
    Point3d unk_20;
    Vec unk_2C;
    Mtx unk_38;
    char unk_68[0x30];
} ThreeDProjectionStruct;
typedef struct ThreeDShadowStruct {
    char unk_00[0x2];
    u16 unk_02;
    void*unk_04;
    char unk_08[0x90];
} ThreeDShadowStruct;

#endif
