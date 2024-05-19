#include "REL/m446Dll.h"

#include "game/hsfman.h"

unkStruct2* fn_1_1C64(s32 arg0) {
    unkStruct2* temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC, 0x10000000U);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk0 = HuMemDirectMallocNum(HEAP_SYSTEM, arg0 * 4, 0x10000000U);
    if (!temp_r3->unk0) {
        HuMemDirectFree(temp_r3);
        return NULL;
    }
    temp_r3->unk4 = arg0;
    temp_r3->unk8 = 0;
    return temp_r3;
}

void fn_1_1CF8(unkStruct2* arg0) {
    HuMemDirectFree(arg0->unk0);
    HuMemDirectFree(arg0);
}

s32 fn_1_1D30(unkStruct2* arg0, s32 arg1) {
    if (arg0->unk4 <= arg0->unk8) {
        return 0;
    } else {
        arg0->unk0[arg0->unk8] = arg1;
        arg0->unk8++;
        return 1;
    }
}

s32 fn_1_1D6C(unkStruct2* arg0, s32* arg1) {
    if (arg0->unk8 <= 0) {
        return 0;
    } else {
        arg0->unk8--;
        arg1[0] = arg0->unk0[arg0->unk8];
        return 1;
    }
}

s32 fn_1_1DA8(unkStruct2* arg0, s32* arg1) {
    if (arg0->unk8 <= 0) {
        return 0;
    } else {
        arg1[0] = *(&arg0->unk0[arg0->unk8] - 1);
        return 1;
    }
}

BOOL fn_1_1DDC(unkStruct2* arg0) {
    return arg0->unk8 == 0;
}

s32 fn_1_1DEC(unkStruct2* arg0) {
    return arg0->unk8;
}

unkStruct3* fn_1_1DF4(s32 arg0) {
    unkStruct3* temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xC, 0x10000000);
    if (!temp_r3) {
        return NULL;
    }
    temp_r3->unk4 = 0;
    temp_r3->unk8 = 0;
    temp_r3->unk0 = arg0;
    return temp_r3;
}

void fn_1_1E5C(unkStruct3* arg0) {
    HuMemDirectFree(arg0);
}