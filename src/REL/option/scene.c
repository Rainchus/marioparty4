#include "REL/option.h"
#include "REL/executor.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/objsub.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "rel_sqrt_consts.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
} UnkSceneDataStruct; // Size 0xC

static void fn_1_270(void);
static void fn_1_354(s16 arg0, s32 arg1, s32 arg2);
static void fn_1_468(void);
static void fn_1_5EC(omObjData *arg0);
static void fn_1_6E8(void);

Process *lbl_1_bss_8;
static omObjData *lbl_1_bss_4;
static s32 lbl_1_bss_0;

void ModuleProlog(void) {
    lbl_1_bss_8 = omInitObjMan(0x40, 0x2000);
    omGameSysInit(lbl_1_bss_8);
    HuWinInit(1);
    lbl_1_bss_0 = GWGameStat.rumble;
    lbl_1_bss_4 = omAddObjEx(lbl_1_bss_8, 1000, 0, 0, 0, fn_1_5EC);
    lbl_1_bss_4->unk10 = 0;
    lbl_1_bss_28 = fn_1_2E04();
}

void fn_1_160(s16 arg0, s32 arg1, s32 arg2) {
    UnkSceneDataStruct *temp_r31;
    Process *temp_r30;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkSceneDataStruct), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk08 = 1.0f / arg2;
    if (arg1 != 0) {
        temp_r31->unk08 = temp_r31->unk08;
        temp_r31->unk04 = 0.0f;
    } else {
        temp_r31->unk08 = -temp_r31->unk08;
        temp_r31->unk04 = 1.0f;
    }
    espDispOn(temp_r31->unk00);
    espTPLvlSet(temp_r31->unk00, temp_r31->unk04);
    temp_r30 = HuPrcChildCreate(fn_1_270, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    temp_r30->user_data = temp_r31;
}

static void fn_1_270(void) {
    UnkSceneDataStruct *temp_r31 = HuPrcCurrentGet()->user_data;

    while (1) {
        temp_r31->unk04 += temp_r31->unk08;
        if (temp_r31->unk04 > 1.0f) {
            temp_r31->unk04 = 1.0f;
            break;
        }
        if (temp_r31->unk04 < 0.0f) {
            temp_r31->unk04 = 0.0f;
            break;
        }
        espTPLvlSet(temp_r31->unk00, temp_r31->unk04);
        HuPrcVSleep();
    }
    espTPLvlSet(temp_r31->unk00, temp_r31->unk04);
    if (temp_r31->unk04 <= 0.0f) {
        espDispOff(temp_r31->unk00);
    }
    HuMemDirectFree(temp_r31);
    HuPrcEnd();
}

static void fn_1_354(s16 arg0, s32 arg1, s32 arg2) {
    UnkSceneDataStruct *temp_r31;
    Process *temp_r30;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(UnkSceneDataStruct), MEMORY_DEFAULT_NUM);
    temp_r31->unk00 = arg0;
    temp_r31->unk08 = 1.0f / arg2;
    if (arg1 != 0) {
        temp_r31->unk08 = temp_r31->unk08;
        temp_r31->unk04 = 0.0f;
    } else {
        temp_r31->unk08 = -temp_r31->unk08;
        temp_r31->unk04 = 1.0f;
    }
    Hu3DModelAttrReset(temp_r31->unk00, 1);
    Hu3DModelTPLvlSet(temp_r31->unk00, temp_r31->unk04);
    temp_r30 = HuPrcChildCreate(fn_1_468, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    temp_r30->user_data = temp_r31;
}

static void fn_1_468(void) {
    UnkSceneDataStruct *temp_r31 = HuPrcCurrentGet()->user_data;

    while (1) {
        temp_r31->unk04 += temp_r31->unk08;
        if (temp_r31->unk04 > 1.0f) {
            temp_r31->unk04 = 1.0f;
            break;
        }
        if (temp_r31->unk04 < 0.0f) {
            temp_r31->unk04 = 0.0f;
            break;
        }
        Hu3DModelTPLvlSet(temp_r31->unk00, temp_r31->unk04);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(temp_r31->unk00, temp_r31->unk04);
    if (temp_r31->unk04 <= 0.0f) {
        Hu3DModelAttrSet(temp_r31->unk00, 1);
    }
    HuMemDirectFree(temp_r31);
    HuPrcEnd();
}

s32 fn_1_550(u16 arg0) {
    u32 temp_r31 = HuPadBtnDown[0] & arg0;

    return (temp_r31 != 0);
}

s32 fn_1_584(u16 arg0) {
    u32 temp_r31 = HuPadDStkRep[0] & arg0;

    return (temp_r31 != 0);
}

s32 fn_1_5B8(u16 arg0) {
    u32 temp_r31 = HuPadDStk[0] & arg0;

    return (temp_r31 != 0);
}

static void fn_1_5EC(omObjData *arg0) {
    switch (arg0->unk10) {
        case 0:
            arg0->unk10 = 1;
            /* fallthrough */
        case 1:
            if (omSysExitReq == 0) {
                break;
            }
            arg0->unk10 = 2;
            /* fallthrough */
        case 2:
            WipeCreate(2, 0, 0x3C);
            HuAudFadeOut(1000);
            arg0->unk10 = 3;
            /* fallthrough */
        case 3:
            if (WipeStatGet() == 0) {
                fn_1_2F4C(lbl_1_bss_28);
                if (lbl_1_bss_0 != GWGameStat.rumble) {
                    omSysExitReq = 0;
                    fn_1_6E8();
                }
                omOvlReturnEx(1, 1);
            }
            break;
    }
}

static void fn_1_6E8(void) {
    s16 temp_r31;

    if (SLSaveFlagGet() == 0) {
        return;
    }
    Hu3DAllKill();
    HuSprClose();
    HuSprInit();
    espInit();
    HuPrcVSleep();
    temp_r31 = espEntry(0x860020, 0x1388, 0);
    espPosSet(temp_r31, 288.0f, 240.0f);
    espAttrReset(temp_r31, 4);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(1, 0, 0xA);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    SLCommonSet();
    if (SLSave() == 0) {
        GWSaveModeSet(1);
    }
    WipeCreate(2, 0, 0x14);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
}
