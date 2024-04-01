#include "REL/option.h"
#include "game/esprite.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"

static void fn_1_A770(UnkWindowDataStruct *arg0, s32 arg1, s16 arg2);
static void fn_1_A860(UnkWindowDataStruct *arg0);
static void fn_1_A8A4(void);

UnkWindowDataStruct *fn_1_A44C(s32 arg0) {
    UnkWindowDataStruct *temp_r31;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkWindowDataStruct), MEMORY_DEFAULT_NUM);
    temp_r31->unk18 = 0;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk20 = 0;
    temp_r31->unk00 = HuPrcChildCreate(fn_1_A8A4, 0x2000, 0x2000, 0, lbl_1_bss_8);
    temp_r31->unk00->user_data = temp_r31;
    temp_r31->unk08 = arg0;
    switch (temp_r31->unk08) {
        case 0:
            temp_r31->unk04 = HuWinExCreateStyled(-10000.0f, 360.0f, 480, 80, -1, 1);
            HuWinBGTPLvlSet(temp_r31->unk04, 0.8f);
            HuWinMesSpeedSet(temp_r31->unk04, 0);
            HuWinMesPalSet(temp_r31->unk04, 7, 0, 0, 0);
            break;
        case 1:
            temp_r31->unk04 = HuWinExCreateStyled(-10000.0f, 326.0f, 480, 40, -1, 0);
            HuWinAttrSet(temp_r31->unk04, 0x800);
            HuWinBGTPLvlSet(temp_r31->unk04, 0.0f);
            HuWinMesSpeedSet(temp_r31->unk04, 0);
            break;
        case 2:
            temp_r31->unk04 = HuWinExCreateStyled(-10000.0f, 88.0f, 224, 34, -1, 0);
            HuWinAttrSet(temp_r31->unk04, 0x800);
            HuWinBGTPLvlSet(temp_r31->unk04, 0.0f);
            HuWinMesSpeedSet(temp_r31->unk04, 0);
            break;
        case 3:
            temp_r31->unk04 = HuWinExCreateStyled(175.0f, 100.0f, 300, 34, -1, 0);
            HuWinBGTPLvlSet(temp_r31->unk04, 0.0f);
            HuWinMesSpeedSet(temp_r31->unk04, 0);
            break;
    }
    HuWinDrawNoSet(temp_r31->unk04, 0x3F);
    fn_1_A828(temp_r31);
    HuSprExecLayerSet(0x3F, 2);
    return temp_r31;
}

void fn_1_A6AC(UnkWindowDataStruct *arg0) {
    HuWinExCleanup(arg0->unk04);
    HuPrcKill(arg0->unk00);
    HuMemDirectFree(arg0);
}

void fn_1_A6EC(UnkWindowDataStruct *arg0) {
    if (arg0->unk0C == 0) {
        arg0->unk20 = 1;
    }
}

void fn_1_A704(UnkWindowDataStruct *arg0) {
    if (arg0->unk0C != 0) {
        arg0->unk20 = 2;
    }
}

void fn_1_A71C(UnkWindowDataStruct *arg0, s32 arg1) {
    if (arg0->unk20 == 0) {
        HuWinMesSet(arg0->unk04, arg1);
    } else {
        arg0->unk18 = arg1;
    }
}

static void fn_1_A770(UnkWindowDataStruct *arg0, s32 arg1, s16 arg2) {
    HuWinInsertMesSet(arg0->unk04, arg1, arg2);
}

void fn_1_A7B0(UnkWindowDataStruct *arg0, float arg1, float arg2) {
    HuWinPosSet(arg0->unk04, arg1, arg2);
}

void fn_1_A7F0(UnkWindowDataStruct *arg0) {
    HuWinDispOn(arg0->unk04);
    arg0->unk0C = 1;
}

void fn_1_A828(UnkWindowDataStruct *arg0) {
    HuWinDispOff(arg0->unk04);
    arg0->unk0C = 0;
}

static void fn_1_A860(UnkWindowDataStruct *arg0) {
    if (arg0->unk20 == 0) {
        arg0->unk20 = 3;
    }
    arg0->unk10 = 1;
}

void fn_1_A880(UnkWindowDataStruct *arg0, s32 arg1) {
    if (arg0->unk20 == 0) {
        arg0->unk20 = 4;
    }
    arg0->unk14 = 1;
    arg0->unk1C = arg1;
}

static void fn_1_A8A4(void) {
    UnkWindowDataStruct *temp_r31 = HuPrcCurrentGet()->user_data;

    while (1) {
        switch (temp_r31->unk20) {
            case 1:
                fn_1_A7F0(temp_r31);
                HuWinExAnimIn(temp_r31->unk04);
                break;
            case 2:
                HuWinExAnimOut(temp_r31->unk04);
                fn_1_A828(temp_r31);
                break;
            case 3:
                HuWinMesWait(temp_r31->unk04);
                temp_r31->unk10 = 0;
                break;
            case 4:
                temp_r31->unk1C = HuWinChoiceGet(temp_r31->unk04, temp_r31->unk1C);
                temp_r31->unk14 = 0;
                break;
        }
        if (temp_r31->unk18 != 0) {
            HuWinMesSet(temp_r31->unk04, temp_r31->unk18);
            temp_r31->unk18 = 0;
        }
        temp_r31->unk20 = 0;
        if (temp_r31->unk10 != 0) {
            temp_r31->unk20 = 3;
        }
        if (temp_r31->unk14 != 0) {
            temp_r31->unk20 = 4;
        }
        HuPrcVSleep();
    }
}
