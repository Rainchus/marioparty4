#ifndef M443DLL_H
#define M443DLL_H

#include "game/object.h"

typedef struct M443DllCameraStruct {
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
    float unk_44;
    float unk_48;
    float unk_4C;
    float unk_50;
    char unk54[0x24];
    float unk_78;
    float unk_7C;
    float unk_80;
    char unk84[0x1C];
    u32 unk_A0;
} M443DllCameraStruct; /* size = 0xA4 */

typedef struct M443DllWorkStruct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    char unk10[0xC];
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    char unk28[0xC];
    s16 unk34;
    char unk3A[0x12];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    s32 unk60;
    char unk64[0x4];
    s32 unk68;
    char unk6C[0x14];
    s32 unk80;
    char unk84[0x4];
    f32 unk88;
    char unk8C[0x4];
    f32 unk90;
    char unk94[0x4];
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    s32 unkA8;
    s32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    f32 unkBC;
    f32 unkC0;
    Vec unkC4;
    Vec unkD0;
    Vec unkDC;
    Vec unkE8;
    char unkF4[0xC];
    M443DllCameraStruct* unk100;
    M443DllCameraStruct* unk104;
} M443DllWorkStruct; /* size = 0x134 */

void fn_1_3FE8(u32 arg0);
u32 fn_1_3FFC(void);
M443DllCameraStruct *fn_1_40AC(s32 arg0);
M443DllCameraStruct *fn_1_4148(u32 arg0);
M443DllCameraStruct *fn_1_41B0(u32 arg0);
void fn_1_421C(s32 arg0, s32 arg1);
s32 fn_1_42CC(void);
u32 fn_1_42E4(void);
s32 fn_1_42FC(void);
void fn_1_4314(s32 arg0, float arg8);
s32 fn_1_4368(s32 arg0);
void fn_1_43AC(s32 arg0);
void fn_1_43DC(s32 arg0);
float fn_1_488C(float arg8, float arg9, float argA);
void fn_1_4A5C(Process *arg0);
void fn_1_4AB0(void);
void fn_1_5444(Process *arg0);
void fn_1_565C(void);

#endif
