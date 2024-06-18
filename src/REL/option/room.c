#include "REL/option.h"
#include "game/audio.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/window.h"

typedef struct {
    /* 0x00 */ omObjData *background;
    /* 0x04 */ omObjData *rumbleArrowPair;
    /* 0x08 */ omObjData *soundArrowPair;
    /* 0x0C */ omObjData *recordArrowPair;
    /* 0x10 */ WindowWork *optionDescWindow;
    /* 0x14 */ WindowWork *btnLegendWindow;
    /* 0x18 */ s32 selectedOption;
    /* 0x1C */ s32 mode;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[6];
    /* 0x28 */ BOOL cameraDoneF;
} RoomWork; // Size 0x2C

#define MODE_DISABLED 0
#define MODE_HANDLE_ROOM 1

#define SEL_CHANGE_LEFT 0
#define SEL_CHANGE_RIGHT 1

static void ChangeSelection(omObjData *object, s32 selChange);
static void HandleRoom(omObjData *object);
static omObjData *CreateBackground(void);
static void KillBackground(omObjData *background);
static omObjData *CreateArrowPair(void);
static void KillArrowPair(omObjData *arrowPair);

omObjData *lbl_1_bss_18;

static omObjFunc modes[] = { NULL, HandleRoom };

omObjData *fn_1_15A4(void)
{
    omObjData *object;
    RoomWork *work;

    object = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(RoomWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->selectedOption = 0;
    work->unk20 = -1;
    work->cameraDoneF = 0;
    fn_1_B74(lbl_1_bss_10, 600.0f, 60.0f, 120.0f, 1);
    fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 1);
    work->background = CreateBackground();
    lbl_1_bss_38 = fn_1_4028();
    lbl_1_bss_40 = fn_1_80E4();
    lbl_1_bss_30 = fn_1_3158();
    lbl_1_bss_20 = fn_1_21F8();
    work->rumbleArrowPair = CreateArrowPair();
    work->soundArrowPair = CreateArrowPair();
    work->recordArrowPair = CreateArrowPair();
    omSetRot(work->rumbleArrowPair, 0.0f, 0.0f, 0.0f);
    omSetRot(work->soundArrowPair, 0.0f, 120.0f, 0.0f);
    omSetRot(work->recordArrowPair, 0.0f, 240.0f, 0.0f);
    work->optionDescWindow = fn_1_A44C(0);
    work->btnLegendWindow = fn_1_A44C(1);
    return object;
}

void fn_1_1798(omObjData *object)
{
    RoomWork *work = object->data;

    KillBackground(work->background);
    fn_1_42DC(lbl_1_bss_38);
    fn_1_322C(lbl_1_bss_30);
    fn_1_825C(lbl_1_bss_40);
    fn_1_241C(lbl_1_bss_20);
    KillArrowPair(work->rumbleArrowPair);
    KillArrowPair(work->soundArrowPair);
    KillArrowPair(work->recordArrowPair);
    fn_1_A6AC(work->optionDescWindow);
    fn_1_A6AC(work->btnLegendWindow);
    HuMemDirectFree(work);
}

static const float guidePosTbl[3] = { 45.0f, 165.0f, 285.0f };

static void ChangeSelection(omObjData *object, s32 selChange)
{
    RoomWork *work = object->data;
    float sp10;
    float spC;
    float sp8;
    float guideDestPos;

    work->selectedOption += (selChange == SEL_CHANGE_LEFT) ? -1 : 1;
    if (work->selectedOption < 0) {
        work->selectedOption = 2;
    }
    else if (work->selectedOption >= 3) {
        work->selectedOption = 0;
    }
    fn_1_C88(lbl_1_bss_10, &sp10, &spC, &sp8);
    fn_1_B74(lbl_1_bss_10, fn_1_BF8(lbl_1_bss_10), fn_1_C28(lbl_1_bss_10) + (selChange == SEL_CHANGE_LEFT ? -120.0f : 120.0f), spC, 96);
    if (work->selectedOption == 2 && selChange == SEL_CHANGE_LEFT) {
        guideDestPos = guidePosTbl[2] - 360.0f;
    }
    else if (work->selectedOption == 0 && selChange == SEL_CHANGE_RIGHT) {
        guideDestPos = 360.0f + guidePosTbl[0];
    }
    else {
        guideDestPos = guidePosTbl[work->selectedOption];
    }
    fn_1_2508(lbl_1_bss_20, guideDestPos, 430.0f, 96);
}

void fn_1_1A2C(omObjData *object, s32 mode)
{
    RoomWork *work = object->data;

    work->mode = mode;
    object->func = modes[mode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 fn_1_1A70(omObjData *object)
{
    RoomWork *work = object->data;

    return work->mode;
}

static const s32 optionDescTbl[] = { MAKE_MESSID(47, 1), MAKE_MESSID(47, 7), MAKE_MESSID(47, 4) };

static void HandleRoom(omObjData *object)
{
    RoomWork *work = object->data;

    switch (object->unk10) {
        case 0:
            if (!work->cameraDoneF) {
                fn_1_B74(lbl_1_bss_10, 600.0f, 60.0f, 120.0f, 1);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 1);
                work->cameraDoneF = TRUE;
            }
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) != 0) {
                break;
            }
            fn_1_A6EC(work->optionDescWindow);
            fn_1_A71C(work->optionDescWindow, optionDescTbl[work->selectedOption]);
            fn_1_A6EC(work->btnLegendWindow);
            fn_1_A71C(work->btnLegendWindow, MAKE_MESSID(47, 14));
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 7;
                }
                else if (fn_1_584(1)) {
                    ChangeSelection(object, SEL_CHANGE_LEFT);
                    fn_1_A704(work->optionDescWindow);
                    fn_1_A704(work->btnLegendWindow);
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (fn_1_584(2)) {
                    ChangeSelection(object, SEL_CHANGE_RIGHT);
                    fn_1_A704(work->optionDescWindow);
                    fn_1_A704(work->btnLegendWindow);
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (fn_1_550(PAD_BUTTON_A)) {
                    fn_1_A704(work->optionDescWindow);
                    fn_1_A704(work->btnLegendWindow);
                    HuAudFXPlay(2);
                    object->unk10 = 3;
                }
            }
            break;
        case 3:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                switch (work->selectedOption) {
                    case 0:
                        fn_1_3290(lbl_1_bss_30, 1);
                        object->unk10 = 4;
                        break;
                    case 1:
                        fn_1_4388(lbl_1_bss_38, 1);
                        object->unk10 = 5;
                        break;
                    case 2:
                        fn_1_82B0(lbl_1_bss_40, 1);
                        object->unk10 = 6;
                        break;
                }
            }
            break;
        case 4:
            if (fn_1_39D4(lbl_1_bss_30) == 0) {
                object->unk10 = 1;
            }
            break;
        case 5:
            if (fn_1_43CC(lbl_1_bss_38) == 0) {
                object->unk10 = 1;
            }
            break;
        case 6:
            if (fn_1_82F4(lbl_1_bss_40) == 0) {
                object->unk10 = 1;
            }
            break;
        case 7:
            fn_1_A704(work->optionDescWindow);
            fn_1_A704(work->btnLegendWindow);
            object->unk10 = 8;
            /* fallthrough */
        case 8:
            if (work->optionDescWindow->state == 0 && work->btnLegendWindow->state == 0) {
                fn_1_1A2C(object, MODE_DISABLED);
            }
            break;
    }
}

static omObjData *CreateBackground(void)
{
    omObjData *background;

    background = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    background->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 0));
    Hu3DModelLayerSet(background->model[0], 0);
    Hu3DModelShadowMapSet(background->model[0]);
    return background;
}

static void KillBackground(omObjData *background)
{
    Hu3DModelKill(background->model[0]);
}

static omObjData *CreateArrowPair(void)
{
    omObjData *arrowPair;

    arrowPair = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    Hu3DModelLayerSet(arrowPair->model[0], 0);
    arrowPair->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 6));
    return arrowPair;
}

static void KillArrowPair(omObjData *arrow)
{
    Hu3DModelKill(arrow->model[0]);
}
