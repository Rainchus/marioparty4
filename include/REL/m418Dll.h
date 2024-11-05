#ifndef M418DLL_H
#define M418DLL_H

#include "dolphin.h"

typedef void (*M418DllFunc)(void);

typedef struct M418DllUnkStruct {
    M418DllFunc unk0;
    Vec center;
    char unk10[0xC];
    Vec rot;
    char unk28[0xC];
    f32 zoom;
    char unk38[0x4];
    f32 unk3C[3];
    char unk48[0x4];
} M418DllUnkStruct; // sizeof 0x4C

void fn_1_ABC4(omObjData*, s32, s32, s32, s32);
void fn_1_B104(M418DllUnkStruct*, Vec, Vec);
void fn_1_B41C(M418DllUnkStruct*);

#endif
