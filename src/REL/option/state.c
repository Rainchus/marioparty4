#include "REL/option.h"
#include "game/hsfman.h"
#include "game/memory.h"
#include "game/window.h"
#include "game/wipe.h"

#include "dolphin.h"

typedef struct {
    /* 0x00 */ WindowWork *window;
    /* 0x04 */ s32 quitTimer;
    /* 0x08 */ s16 light;
} StateWork; // Size 0xC

typedef struct {
    Vec src;
    Vec dest;
    GXColor color;
} UnkLightDataStruct; // Size 0x1C TODO same as m446Dll::unkStruct10 and present::UnkPresentStruct3

static void HandleState(omObjData *object);

omObjData *lbl_1_bss_28;

static UnkLightDataStruct lightTbl = {
    { 0.0f, 300.0f, 0.0f },
    { 0.0f, -300.0f, -600.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
};

static Vec shadowPosTbl[3] = {
    { 0.0f, 3000.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

omObjData *fn_1_2E04(void)
{
    omObjData *object;
    StateWork *work;
    LightData *lightData;

    object = omAddObjEx(lbl_1_bss_8, 1000, 0, 0, 4, HandleState);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(StateWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    lbl_1_bss_10 = fn_1_7F8();
    lbl_1_bss_18 = fn_1_15A4();
    work->window = fn_1_A44C(0);
    Hu3DLighInit();
    work->light = Hu3DGLightCreateV(&lightTbl.src, &lightTbl.dest, &lightTbl.color);
    Hu3DGLightInfinitytSet(work->light);
    lightData = &Hu3DGlobalLight[work->light];
    Hu3DShadowCreate(30.0f, 20.0f, 5000.0f);
    Hu3DShadowTPLvlSet(0.45f);
    Hu3DShadowPosSet(&shadowPosTbl[0], &shadowPosTbl[1], &shadowPosTbl[2]);
    return object;
}

void fn_1_2F4C(omObjData *object)
{
    StateWork *work = object->data;

    fn_1_A3C(lbl_1_bss_10);
    fn_1_1798(lbl_1_bss_18);
    fn_1_A6AC(work->window);
    HuMemDirectFree(work);
}

static void HandleState(omObjData *object)
{
    StateWork *work = object->data;

    switch (object->unk10) {
        case 0:
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            WipeCreate(WIPE_MODE_IN, -1, 60);
            object->unk10 = 2;
            break;
        case 2:
            if (WipeStatGet() != 0 || work->window->state != 0) {
                break;
            }
            fn_1_1A2C(lbl_1_bss_18, 1);
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            if (fn_1_1A70(lbl_1_bss_18) != 0) {
                break;
            }
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            fn_1_A6EC(work->window);
            fn_1_A71C(work->window, MAKE_MESSID(47, 167)); // Would you like to leave?
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window->state != 0) {
                break;
            }
            fn_1_A880(work->window, 1);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window->state != 0) {
                break;
            }
            fn_1_A704(work->window);
            if (work->window->choice == 0) {
                work->quitTimer = 0;
                object->unk10 = 7;
            }
            else {
                object->unk10 = 2;
            }
            break;
        case 7:
            object->unk10 = 8;
            work->quitTimer = 0;
            /* fallthrough */
        case 8:
            if (work->window->state == 0 && work->quitTimer++ >= 60) {
                omSysExitReq = 1;
            }
            break;
    }
}
