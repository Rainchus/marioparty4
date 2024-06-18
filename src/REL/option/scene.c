#include "REL/executor.h"
#include "REL/option.h"
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
    /* 0x00 */ s16 spr;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float opacity;
    /* 0x08 */ float opacityChange;
} LRButtonWork; // Size 0xC

static void HandleLRBtn(void);
static void fn_1_354(s16 arg0, s32 arg1, s32 arg2);
static void fn_1_468(void);
static void HandleScene(omObjData *arg0);
static void KillScene(void);

Process *lbl_1_bss_8;
static omObjData *scene;
static s32 rumbleF;

void ModuleProlog(void)
{
    lbl_1_bss_8 = omInitObjMan(0x40, 0x2000);
    omGameSysInit(lbl_1_bss_8);
    HuWinInit(1);
    rumbleF = GWGameStat.rumble;
    scene = omAddObjEx(lbl_1_bss_8, 1000, 0, 0, 0, HandleScene);
    scene->unk10 = 0;
    lbl_1_bss_28 = fn_1_2E04();
}

void fn_1_160(s16 sprite, BOOL hiddenF, s32 fadeInTime)
{
    LRButtonWork *work;
    Process *process;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(LRButtonWork), MEMORY_DEFAULT_NUM);
    work->spr = sprite;
    work->opacityChange = 1.0f / fadeInTime;
    if (hiddenF) {
        work->opacityChange = work->opacityChange;
        work->opacity = 0.0f;
    }
    else {
        work->opacityChange = -work->opacityChange;
        work->opacity = 1.0f;
    }
    espDispOn(work->spr);
    espTPLvlSet(work->spr, work->opacity);
    process = HuPrcChildCreate(HandleLRBtn, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void HandleLRBtn(void)
{
    LRButtonWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        work->opacity += work->opacityChange;
        if (work->opacity > 1.0f) {
            work->opacity = 1.0f;
            break;
        }
        if (work->opacity < 0.0f) {
            work->opacity = 0.0f;
            break;
        }
        espTPLvlSet(work->spr, work->opacity);
        HuPrcVSleep();
    }
    espTPLvlSet(work->spr, work->opacity);
    if (work->opacity <= 0.0f) {
        espDispOff(work->spr);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
}

static void fn_1_354(s16 sprite, s32 arg1, s32 arg2)
{
    LRButtonWork *work;
    Process *process;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(LRButtonWork), MEMORY_DEFAULT_NUM);
    work->spr = sprite;
    work->opacityChange = 1.0f / arg2;
    if (arg1 != 0) {
        work->opacityChange = work->opacityChange;
        work->opacity = 0.0f;
    }
    else {
        work->opacityChange = -work->opacityChange;
        work->opacity = 1.0f;
    }
    Hu3DModelAttrReset(work->spr, 1);
    Hu3DModelTPLvlSet(work->spr, work->opacity);
    process = HuPrcChildCreate(fn_1_468, 0x3000, 0x1500, 0, HuPrcCurrentGet());
    process->user_data = work;
}

static void fn_1_468(void)
{
    LRButtonWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        work->opacity += work->opacityChange;
        if (work->opacity > 1.0f) {
            work->opacity = 1.0f;
            break;
        }
        if (work->opacity < 0.0f) {
            work->opacity = 0.0f;
            break;
        }
        Hu3DModelTPLvlSet(work->spr, work->opacity);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(work->spr, work->opacity);
    if (work->opacity <= 0.0f) {
        Hu3DModelAttrSet(work->spr, 1);
    }
    HuMemDirectFree(work);
    HuPrcEnd();
}

BOOL fn_1_550(u16 btn)
{
    u32 temp_r31 = HuPadBtnDown[0] & btn;

    return (temp_r31 != 0);
}

BOOL fn_1_584(u16 arg0)
{
    u32 temp_r31 = HuPadDStkRep[0] & arg0;

    return (temp_r31 != 0);
}

BOOL fn_1_5B8(u16 arg0)
{
    u32 temp_r31 = HuPadDStk[0] & arg0;

    return (temp_r31 != 0);
}

static void HandleScene(omObjData *object)
{
    switch (object->unk10) {
        case 0:
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (!omSysExitReq) {
                break;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            HuAudFadeOut(1000);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (WipeStatGet() == 0) {
                fn_1_2F4C(lbl_1_bss_28);
                if (rumbleF != GWGameStat.rumble) {
                    omSysExitReq = 0;
                    KillScene();
                }
                omOvlReturnEx(1, 1);
            }
            break;
    }
}

static void KillScene(void)
{
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
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    SLCommonSet();
    if (SLSave() == 0) {
        GWSaveModeSet(1);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 20);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
}
