#include "unsplit.h"
#include "game/audio.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/board/main.h"
#include "game/board/audio.h"
#include "game/board/player.h"
#include "game/board/space.h"
#include "game/board/ui.h"

// structs
typedef struct structActiveMG {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
} structActiveMG;

typedef struct bitcopy {
    struct {
        u8 field00_bit0 : 1;
        u8 field00_bit1 : 3;
        u8 field00_bit4 : 2;
        u8 field00_bit6 : 1;
        u8 field00_bit7 : 1;
    };
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s16 unk_04;
} bitcopy;

// bss
static structActiveMG activeMG[4];

// data
static s32 luckyMessTbl[9] = {
    0x00140000, 0x00140005, 0x0014000A, 0x0014000F,
    0x00140014, 0x00140019, 0x00140000, 0x00140000,
    0x00140000
};

// sbss
static u8 mgType;
static s32 luckyF;
static s16 mgNext;
static omObjData* mgSetupObj;
static Process* mgSetupProc;

// sdata

// sdata2

// determined functions
void BoardMGSetupExec(void);
void DestroyMGSetup(void);
void ExecMGSetup(void);
void CreateMGSetup(void);
void HideLuckyValue(void);
void BoardMGSetupPlayPop(s32, s16);

// FUNCTIONS //

void BoardMGSetupExec(void) {
    mgSetupProc = HuPrcChildCreate(&ExecMGSetup, 0x2006, 0x3800, 0, boardMainProc);
    HuPrcDestructorSet2(mgSetupProc, &DestroyMGSetup);
    while (mgSetupProc != 0) {
        HuPrcVSleep();
    }
}

static void DestroyMGSetup(void) {
    GWSystem.player_curr = 0;
    mgSetupProc = NULL;
}

static inline s32 setupObjGet(void) {
    bitcopy* work = (bitcopy*) mgSetupObj->work;
    return work->field00_bit1;
}

static void ExecMGSetup(void) {
    s32 sp60[9] = {
        0x750000, 0x760000, 0x770000,
        0x780000, 0x790000, 0x7A0000,
        0x7B0000, 0x7C0000, 0x7D0000
    };
    Vec sp54;
    u16 var_r24;
    s32 var_r22;
    s32 var_r23;
    s32 var_r31;
    u32 var_r30;
    bitcopy* temp_r29;
    bitcopy* temp_r28;
    bitcopy* temp_r27;
    bitcopy* temp_r26;
    bitcopy* temp_r25;

    luckyF = 0;
    mgNext = 0;
    GWSystem.player_curr = -1;
    GWSystem.unk_32 = 1;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        activeMG[var_r31].unk_00 = -1;
        activeMG[var_r31].unk_04 = 0;
    }
    BoardPlayerMoveAwayStartCurr(GWPlayer[GWSystem.player_curr].space_curr, 1);
    BoardCameraMoveSet(0);
    BoardCameraTargetSpaceSet(BoardSpaceStarGetCurr());
    sp54.x = 0.0f;
    sp54.y = 150.0f;
    sp54.z = 0.0f;
    BoardCameraMotionStartEx(-1, NULL, &sp54, 1300.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    WipeCreate(1, 0, 0x15);
    
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardFilterFadeInit(0x1E, 0xA0U);
    CreateMGSetup();
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    if (BoardRandMod(0x64U) < 5U) {
        HuPrcSleep(0x1E);
        luckyF = 1;
        temp_r29 = (bitcopy*) mgSetupObj->work;
        temp_r29->field00_bit1 = 4;
        temp_r29->unk_02 = 0;
        temp_r29->unk_03 = 0;
        temp_r29->unk_04 = 0;
        HuAudFXPlay(0x35C);
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        temp_r28 = (bitcopy*) mgSetupObj->work;
        temp_r28->field00_bit1 = 1;
        temp_r28->unk_02 = 0;
        temp_r28->unk_03 = 0;
        temp_r28->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        var_r30 = luckyMessTbl[GWBoardGet()];
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        temp_r27 = (bitcopy*) mgSetupObj->work;
        temp_r27->field00_bit1 = 5;
        temp_r27->unk_02 = 0;
        temp_r27->unk_03 = 0;
        temp_r27->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
        switch (GWSystem.unk_32) {
            case 1:
                var_r30 = luckyMessTbl[GWBoardGet()] + 1;
                break;
            case 2:
                var_r30 = luckyMessTbl[GWBoardGet()] + 2;
                break;
            case 3:
                var_r30 = luckyMessTbl[GWBoardGet()] + 3;
                break;
        }
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        var_r30 = luckyMessTbl[GWBoardGet()] + 4;
        BoardWinCreate(2, var_r30, BoardWinPortraitGetStar());
        BoardWinWait();
        BoardWinKill();
        HideLuckyValue();
    } else {
        temp_r26 = (bitcopy*) mgSetupObj->work;
        temp_r26->field00_bit1 = 1;
        temp_r26->unk_02 = 0;
        temp_r26->unk_03 = 0;
        temp_r26->unk_04 = 0;
        while (setupObjGet() != 7) {
            HuPrcVSleep();
        }
    }
    temp_r25 = (bitcopy*) mgSetupObj->work;
    temp_r25->field00_bit1 = 6;
    temp_r25->unk_02 = 0;
    temp_r25->unk_03 = 0;
    temp_r25->unk_04 = 0;
    while (setupObjGet() != 7) {
        HuPrcVSleep();
    }
    HuDataDirClose(0x70000);
    HuDataDirClose(0x20000);
    HuDataDirClose(sp60[GWBoardGet()]);
    HuPrcSleep(2);
    if (_CheckFlag(0xBU) != 0) {
        var_r23 = 0x140000;
    } else {
        var_r23 = mgInfoTbl[mgNext].data_dir;
    }
    var_r22 = BoardDataDirReadAsync(var_r23);
    BoardAudSeqFadeOut(0, 0x3E8U);
    _SetFlag(0x1000EU);
    WipeColorSet(0xFFU, 0xFFU, 0xFFU);
    WipeCreate(2, 0, -1);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXAllStop();
    _SetFlag(0x1001CU);
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        BoardStatusItemHideSet(var_r31, 1);
    }
    ((bitcopy*) (mgSetupObj->work))->field00_bit0 = 1;
    BoardDataAsyncWait(var_r22);
    var_r24 = mgNext + 0x191;
    BoardMGSetupPlayPop(mgType, var_r24);
    GWSystem.mg_next_type = -1;
    GWMGAvailSet(var_r24);
    GWSystem.mg_next = var_r24 - 0x191;
    _SetFlag(0x10002U);
    if (GWSystem.turn == GWSystem.max_turn) {
        _SetFlag(0xAU);
    }
    BoardNextOvlSet(3);
    HuPrcEnd();
}
