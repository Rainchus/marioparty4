#include "REL/option.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ omObjData *system;
    /* 0x04 */ omObjData *pad;
    /* 0x08 */ omObjData *padFilter;
    /* 0x0C */ omObjData *hand;
    /* 0x10 */ omObjData *highlightOn;
    /* 0x14 */ WindowWork *window[2];
    /* 0x20 */ s32 mode;
    /* 0x20 */ BOOL rumbleF;
    /* 0x24 */ BOOL cameraDoneF;
    /* 0x28 */ s32 changeTimer;
} RumbleWork; // Size 0x2C

#define MODE_DISABLED 0
#define MODE_HANDLE_RUMBLE 1 // TODO room.c should have access to this

static void HandleRumble(omObjData *object);
static omObjData *CreateHand(void);
static void KillHand(omObjData *hand);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *system);
static void StartSystemMotion(omObjData *system, s32 rumbleF, BOOL slowF);
static omObjData *CreatePad(void);
static void KillPad(omObjData *pad);
static void ShakePad(omObjData *pad, BOOL on);
static omObjData *CreatePadFilter(void);
static void KillPadFilter(omObjData *padFilter);
static omObjData *CreateHighlightOn(void);
static void KillHighlightOn(omObjData *highlightOn);

omObjData *lbl_1_bss_30;

static omObjFunc modes[] = { NULL, HandleRumble };

omObjData *fn_1_3158(void)
{
    omObjData *object;
    RumbleWork *work;

    object = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RumbleWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->rumbleF = GWGameStat.rumble;
    work->system = CreateSystem();
    StartSystemMotion(work->system, work->rumbleF, 0);
    work->pad = CreatePad();
    ShakePad(work->pad, work->rumbleF);
    work->padFilter = CreatePadFilter();
    work->highlightOn = CreateHighlightOn();
    work->hand = CreateHand();
    fn_1_3290(object, MODE_DISABLED);

    return object;
}

void fn_1_322C(omObjData *object)
{
    RumbleWork *work = object->data;

    KillHand(work->hand);
    KillSystem(work->system);
    KillPad(work->pad);
    KillHighlightOn(work->highlightOn);
    KillPadFilter(work->padFilter);
    HuMemDirectFree(work);
}
// SetMode
void fn_1_3290(omObjData *object, s32 mode)
{
    RumbleWork *work = object->data;

    work->mode = mode;
    object->func = modes[mode];
    object->unk10 = 0;
    object->unk10 = 0;
}
// GetMode
s32 fn_1_39D4(omObjData *object)
{
    RumbleWork *work = object->data;

    return work->mode;
}

static void HandleRumble(omObjData *object)
{
    RumbleWork *work = object->data;
    s32 i;

    switch (object->unk10) {
        case 0:
            work->window[0] = fn_1_A44C(0);
            work->window[1] = fn_1_A44C(1);
            fn_1_AF0(lbl_1_bss_10, -519.62f, 135.0f, 300.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, -315.64f, 135.0f, 182.25f, 0x28);
            fn_1_3D54(object);
            Hu3DModelLayerSet(work->padFilter->model[0], 1);
            work->cameraDoneF = FALSE;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->hand->model[0], 1);
                work->cameraDoneF = TRUE;
                Hu3DModelHookSet(work->system->model[0], "target", work->hand->model[0]);
            }
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 15));
            fn_1_A6EC(work->window[0]);
            if (work->rumbleF) {
                fn_1_A71C(work->window[0], MAKE_MESSID(47, 2));
            }
            else {
                fn_1_A71C(work->window[0], MAKE_MESSID(47, 3));
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 4;
                }
                else if (fn_1_584(8) && !work->rumbleF) {
                    StartSystemMotion(work->system, 1, TRUE);
                    work->rumbleF = TRUE;
                    work->changeTimer = 0;
                    GWRumbleSet(1);
                    object->unk10 = 3;
                }
                else if (fn_1_584(4) && work->rumbleF) {
                    StartSystemMotion(work->system, 0, TRUE);
                    work->rumbleF = FALSE;
                    work->changeTimer = 0;
                    GWRumbleSet(0);
                    object->unk10 = 3;
                }
            }
            break;
        case 3:
            if (work->changeTimer++ >= 60) {
                HuAudFXPlay(0x83C);
                ShakePad(work->pad, work->rumbleF);
                if (work->rumbleF) {
                    HuPadRumbleSet(0, 60, 10, 5);
                    Hu3DMotionTimeSet(work->highlightOn->model[0], 0.0f);
                    Hu3DModelAttrReset(work->highlightOn->model[0], 1);
                }
                else {
                    Hu3DModelAttrSet(work->highlightOn->model[0], 1);
                }
                object->unk10 = 1;
            }
            break;
        case 4:
            fn_1_A704(work->window[1]);
            fn_1_A704(work->window[0]);
            Hu3DModelAttrSet(work->hand->model[0], 1);
            fn_1_3E1C(object);
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window[1]->state == 0 && work->window[0]->state == 0 && !fn_1_3ED0(lbl_1_bss_30)) {
                for (i = 0; i < 2; i++) {
                    fn_1_A6AC(work->window[i]);
                }
                Hu3DModelHookReset(work->system->model[0]);
                fn_1_AF0(lbl_1_bss_10, -519.62f, 120.0f, 300.0f, 0x28);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
                fn_1_3290(object, MODE_DISABLED);
            }
            break;
    }
}

static omObjData *CreateHand(void)
{
    omObjData *hand;

    hand = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    hand->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 15));
    Hu3DModelLayerSet(hand->model[0], 3);
    omSetRot(hand, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrSet(hand->model[0], 1);
    return hand;
}

static void KillHand(omObjData *hand)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(hand->model[i]);
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *system;

    system = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    system->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 2));
    Hu3DModelAttrSet(system->model[0], 0x40000002);
    if (GWRumbleGet()) {
        Hu3DMotionTimeSet(system->model[0], 60.0f);
    }
    else {
        Hu3DMotionTimeSet(system->model[0], 0.0f);
    }
    return system;
}

static void KillSystem(omObjData *system)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(system->model[i]);
    }
}

static void StartSystemMotion(omObjData *system, s32 rumbleF, BOOL slowF)
{
    s16 model = system->model[0];

    Hu3DModelAttrReset(system->model[0], 0x40000002);
    Hu3DModelAttrReset(system->model[0], 0x40000001);
    if (rumbleF) {
        Hu3DMotionStartEndSet(model, 60.0f, 120.0f);
        if (slowF) {
            Hu3DMotionTimeSet(model, 60.0f);
        }
        else {
            Hu3DMotionTimeSet(model, 119.0f);
        }
    }
    else {
        Hu3DMotionStartEndSet(model, 0.0f, 60.0f);
        if (slowF) {
            Hu3DMotionTimeSet(model, 0.0f);
        }
        else {
            Hu3DMotionTimeSet(model, 59.0f);
        }
    }
}

static omObjData *CreatePad(void)
{
    omObjData *pad;

    pad = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    pad->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 9));
    Hu3DModelAttrSet(pad->model[0], 0x40000001);
    return pad;
}

static void KillPad(omObjData *pad)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(pad->model[i]);
    }
}

static void ShakePad(omObjData *pad, BOOL on)
{
    if (on) {
        Hu3DModelAttrReset(pad->model[0], 0x40000002);
        Hu3DModelAttrSet(pad->model[0], 0x40000001);
    }
    else {
        Hu3DModelAttrSet(pad->model[0], 0x40000002);
        Hu3DModelAttrReset(pad->model[0], 0x40000001);
    }
}

static omObjData *CreatePadFilter(void)
{
    omObjData *object;

    object = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    object->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 10));
    Hu3DModelAttrSet(object->model[0], 0x40000002);
    Hu3DModelLayerSet(object->model[0], 2);

    return object;
}

static void KillPadFilter(omObjData *padFilter)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(padFilter->model[i]);
    }
}
// ZoomIn
void fn_1_3D54(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->model[0];

    Hu3DMotionStartEndSet(model, 0.0f, 40.0f);
    Hu3DMotionTimeSet(model, 0.0f);
    Hu3DModelAttrReset(work->padFilter->model[0], 0x40000002);
    Hu3DModelAttrReset(work->padFilter->model[0], 0x40000001);
    Hu3DModelLayerSet(work->padFilter->model[0], 2);
    HuAudFXPlay(0x83D);
}
// ZoomOut
void fn_1_3E1C(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 model = work->padFilter->model[0];

    Hu3DMotionStartEndSet(model, 40.0f, 80.0f);
    Hu3DMotionTimeSet(model, 40.0f);
    Hu3DModelAttrReset(work->padFilter->model[0], 0x40000002);
    Hu3DModelAttrReset(work->padFilter->model[0], 0x40000001);
    HuAudFXPlay(0x83E);
}
// GetPadFilterMotionDone
BOOL fn_1_3ED0(omObjData *object)
{
    RumbleWork *work = object->data;
    s16 padFilterModel = work->padFilter->model[0];

    return !Hu3DMotionEndCheck(padFilterModel);
}

static omObjData *CreateHighlightOn(void)
{
    omObjData *highlightOn;

    highlightOn = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    highlightOn->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 11));
    if (GWRumbleGet()) {
        Hu3DModelAttrReset(highlightOn->model[0], 1);
    }
    else {
        Hu3DModelAttrSet(highlightOn->model[0], 1);
    }
    return highlightOn;
}

static void KillHighlightOn(omObjData *highlightOn)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(highlightOn->model[i]);
    }
}
