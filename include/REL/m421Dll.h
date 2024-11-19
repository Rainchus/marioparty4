#ifndef M421DLL_H
#define M421DLL_H

#include "game/object.h"

typedef struct UnkM421DllStruct {
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0C;
} UnkM421DllStruct;

typedef struct M421DllCameraStruct {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u32 unk_0C;
    float unk_10;
    float unk_14;
    float unk_18;
    Vec unk_1C;
    Vec unk_28;
    float unk_34;
    s32 unk_38;
    s32 unk_3C;
    float unk_40;
    UnkM421DllStruct unk_44;
    char unk54[0x30];
    float unk_84;
    char unk88[0x4];
    float unk_8C;
    float unk_90;
    s32 unk_94;
    char unk98[0xC];
} M421DllCameraStruct; /* size = 0xA4 */ // same as M443DllCameraStruct and M460

void fn_1_4648(Process *process);
void fn_1_48B0(void);
void fn_1_B15C(Process *process, omObjData *object);
void fn_1_B1BC(void);

#endif
