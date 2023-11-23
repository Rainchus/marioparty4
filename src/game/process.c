#include "common.h"

extern unkStruct145A98 lbl_80145A98[0x100];
extern s32 debugFontColor;
extern s16 lbl_801D3B2C;
extern s16 lbl_801D3B2E;
extern s16 lbl_801D3B3C;
extern unkStruct1D3B44* lbl_801D3B44;

void fn_8000AEF0(void) {
    s32 i;

    debugFontColor = 0xF;
    lbl_801D3B2E = 0;
    
    for (i = 0; i < 0x100; i++) {
        lbl_80145A98[i].unk_14 = 0;
    }
    fn_8000AF54();
}

void fn_8000AF54(void) {
    s32 i;

    lbl_801D3B2E = 0;
    lbl_801D3B2C = 0;
    for (i = 0; i < 0x100; i++) {
        lbl_80145A98[i].unk_0C = (s16) (i + 1);
        lbl_80145A98[i].unk_00 = 0;
        if (lbl_80145A98[i].unk_14 != 0) {
            lbl_80145A98[i].unk_14 = 0;
        }
    }
}

void HuPrcInit(void) {
    lbl_801D3B3C = 0;
    lbl_801D3B44 = NULL;
}

// ...

// HuPrcCall

// HuPrcMemAlloc

// HuPrcMemFree

void HuPrcSetStat(unkStruct1D3B44* arg0, u16 arg1) {
    arg0->unk_1E |= arg1;
}

void HuPrcResetStat(unkStruct1D3B44* arg0, s32 arg1) {
    arg0->unk_1E &= ~arg1;
}

void HuPrcAllPause(s32 arg0) {
    unkStruct1D3B44* var_r31;

    var_r31 = lbl_801D3B44;
    if (arg0 != 0) {
        while (var_r31 != NULL) {
            if ((var_r31->unk_1E & 4) == 0) {
                var_r31->unk_1E |= (u16) 1;
            }
            var_r31 = var_r31->prev;
        }
        return;
    }
    while (var_r31 != NULL) {
        if ((var_r31->unk_1E & 1) != 0) {
            var_r31->unk_1E &= -2;
        }
        var_r31 = var_r31->prev;
    }
}

void HuPrcAllUPause(s32 arg0) {
    unkStruct1D3B44* var_r31;

    var_r31 = lbl_801D3B44;
    if (arg0 != 0) {
        while (var_r31 != NULL) {
            if ((var_r31->unk_1E & 8) == 0) {
                var_r31->unk_1E |= (u16) 2;
            }
            var_r31 = var_r31->prev;
        }
        return;
    }
    while (var_r31 != NULL) {
        if ((var_r31->unk_1E & 2) != 0) {
            var_r31->unk_1E &= -3;
        }
        var_r31 = var_r31->prev;
    }
}
