#include "game/board/boo_house.h"

#include "game/msm.h"
#include "game/hsfdraw.h"
#include "game/gamework_data.h"
#include "game/board/player.h"
#include "game/board/model.h"
#include "game/board/com.h"
#include "game/board/boo.h"
#include "game/board/ui.h"
#include "game/board/view.h"
#include "game/board/audio.h"
#include "game/board/main.h"
#include "game/board/star.h"
#include "game/board/player.h"
#include "game/board/window.h"

#include "ext_math.h"

// bss
static s16 houseMdl[6];

// data
static s32 hostMesTbl[6][6] = {
    { 0x7000C, 0x7000D, 0x7000E, 0x7000F, 0x70010, 0x70011 },
    { 0x70012, 0x70013, 0x70014, 0x70015, 0x70016, 0x70017 },
    { 0x70018, 0x70019, 0x7001A, 0x7001B, 0x7001C, 0x7001D }, 
    { 0x7001E, 0x7001F, 0x70020, 0x70021, 0x70022, 0x70023 },
    { 0x70024, 0x70025, 0x70026, 0x70027, 0x70028, 0x70029 }, 
    { 0x7002A, 0x7002B, 0x7002C, 0x7002D, 0x7002E, 0x7002F },
};
static BoardModelParam houseMdlTbl[6] = {
    { 0x90000, { 0, 1, 0, 0, 0 }, 0xFFFF },
    { 0x90001, { 1, 1, 0, 0, 0 }, 0xFFFF },
    { 0x90003, { 1, 1, 0, 0, 0 }, 0xFFFF },
    { 0x90004, { 1, 1, 0, 0, 0 }, 0xFFFF },
    { 0x90004, { 1, 1, 0, 0, 0 }, 0xFFFF },
    { 0x90007, { 0, 1, 0, 0, 0 }, 0xFFFF },
};
static s32 booMotTbl[3] = {
    0x20013, 0x20016, 0xFFFFFFFF 
};
static s32 houseMotTbl[9][3] = {
    { 0x20001, 0x20003, 0x20004 },
    { 0x20009, 0x2000B, 0x2000C },
    { 0x2000E, 0x20010, 0x20011 },
    { 0x20018, 0x2001A, 0x2001B },
    { 0x2001D, 0x2001F, 0x20020 },
    { 0x20022, 0x20024, 0x20025 },
    { 0x20018, 0x2001A, 0x2001B },
    { 0x20001, 0x20003, 0x20004 },
    { 0x20001, 0x20003, 0x20004 }
};

// sbss
static s8 currPlayer;
static s8 stealTarget;
static s8 comStarStealTarget;
static s32 comCoinStealTarget;
static s8 stealAmountStr[8];
static Process* houseProc;

// sdata
static s16 houseShowMot = 0xFFFF;
static s16 houseHideMot = 0xFFFF;
static s16 ballMdl = 0xFFFF;
static s16 booMdl = 0xFFFF;
static s16 lbl_801D37F8 = 0xFFFF;
static s16 hostMdl = 0xFFFF;
static s16 houseMot[3] = { 0xFFFF, 0xFFFF, 0xFFFF };

// determined functions
static void ExecBooHouse(void);
static void DestroyBooHouse(void);
static void PickComStealType(s32);
static void OpenBooHouse(void);
static void CloseBooHouse(void);
static void CreateBooHouseModel(void);
static void KillBooHouseModel(void);
static void ExecNullSteal(void);
static void ExecStarSteal(void);
static void ExecCoinSteal(void);
static void ApplySteal(void);
static void ApplyCoinSteal(s16 arg0, s16 arg1);
static void ApplyStarSteal(void);
static void ApplyBooLight(void);
static void SetBooBallPos(void);

// FUNCTIONS //
void BoardBooHouseHostSet(s16 arg0) {
    hostMdl = arg0;
}

s16 BoardBooHouseHostGet(void) {
    return hostMdl;
}

void BoardBooHouseCreate(void) {
    Vec sp14;
    Vec sp8;

    if ((GWBoardGet() == 7) || (GWBoardGet() == 8)) {
        return;
    }
    BoardSpaceLinkTransformGet(0x08000000, &sp14, &sp8, 0);
    houseMdl[0] = BoardModelCreateParam(&houseMdlTbl[0], &sp14, &sp8);
    if (hostMdl != -1) {
        BoardModelVisibilitySet(hostMdl, 0);
    }
    HuDataDirClose(0x90000);
}

void BoardBooHouseKill(void) {
    if (houseMdl[0] != -1) {
        BoardModelKill(houseMdl[0]);
        houseMdl[0] = -1;
    }
}

void BoardBooHouseExec(s32 arg0) {
    currPlayer = arg0;
    if (BoardPlayerSizeGet(currPlayer) != 2) {
        BoardDiceDigit2DShowSet(0);
        houseProc = HuPrcChildCreate(&ExecBooHouse, 0x2003, 0x3800, 0, boardMainProc);
        HuPrcDestructorSet2(houseProc, &DestroyBooHouse);
        while (houseProc != 0U) {
            HuPrcVSleep();
        }
        BoardDiceDigit2DShowSet(1);
    }
}

static void ExecBooHouse(void) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 temp_r29;
    s32 var_r31;
    s16 var_r30;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;

    _SetFlag(0x10018);
    var_r28 = BoardDataDirReadAsync(0x90000);
    var_r30 = GWPlayer[currPlayer].space_curr;
    BoardPlayerIdleSet(currPlayer);
    if (BoardPlayerCoinsGet(currPlayer) < 5) {
        BoardWinCreate(0, 0x70001, -1);
        BoardWinWait();
        BoardWinKill();
        BoardDataAsyncWait(var_r28);
        HuPrcEnd();
    }
    BoardWinCreateChoice(0, 0x70000, -1, 0);
    if (GWPlayer[currPlayer].com != 0) {
        if (BoardBooComUseCheck(currPlayer) != 0) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    if (BoardWinChoiceGet() != 0) {
        BoardDataAsyncWait(var_r28);
        HuPrcEnd();
    }
    
    for (var_r26 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (currPlayer != var_r31) {
            var_r26 += GWStarsGet(var_r31);
        }
    }
    
    for (var_r27 = var_r31 = 0; var_r31 < 4; var_r31++) {
        if (currPlayer != var_r31) {
            var_r27 += BoardPlayerCoinsGet(var_r31);
        }
    }
    BoardWinKill();
    BoardDiceDigit2DShowSet(0);
    BoardAudSeqPause(0, 1, 0x3E8);
    BoardDataAsyncWait(var_r28);
    temp_r29 = BoardSpaceLinkFlagSearch(0, var_r30, 0x02000000);
    BoardSpacePosGet(0, var_r30, &sp38);
    BoardSpacePosGet(0, temp_r29, &sp2C);
    PSVECSubtract(&sp2C, &sp38, &sp20);
    PSVECNormalize(&sp20, &sp20);
    temp_f31 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -15.0f;
    sp14.y = temp_f31;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], &sp14, &sp8, 1370.0f, -1.0f, 0x1B);
    CreateBooHouseModel();
    OpenBooHouse();
    BoardPlayerRotSet(currPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(currPlayer, var_r30, temp_r29);
    BoardPlayerIdleSet(currPlayer);
    BoardMusStart(1, 1, 0x7F, 0);
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), houseMot[0], 0.0f, 10.0f, 0x40000001);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][0], BoardWinPortraitGet());
    BoardWinWait();

repeatWindowView:
    HuAudFXPlay(0x4C);
    BoardWinCreateChoice(1, hostMesTbl[GWBoardGet()][1], BoardWinPortraitGet(), 0);
    if (var_r27 == 0) {
        BoardWinChoiceDisable(0);
    }
    if ((BoardPlayerCoinsGet(currPlayer) < 0x32) || (var_r26 == 0)) {
        BoardWinChoiceDisable(1);
    }
    BoardWinAttrSet(0x10);
    if (GWPlayer[currPlayer].com != 0) {
        PickComStealType(currPlayer);
    }
    BoardWinWait();
    stealTarget = BoardWinChoiceGet();
    BoardWinKill();
    while (BoardStatusStopCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    switch (stealTarget) {
        case 0:
            ExecCoinSteal();
            break;
        case 1:
            ExecStarSteal();
            break;
        case 2:
            ExecNullSteal();
            break;
        case 3:
            BoardViewMapExec(currPlayer);
            goto repeatWindowView;
    }
    if (stealTarget != 2) {
        ApplySteal();
        BoardStatusShowSet(currPlayer, 0);
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), houseMot[1], 0.0f, 10.0f, 0x40000001);
    CloseBooHouse();
    BoardCameraViewSet(1);
    BoardCameraRotSet(0.0f, 0.0f);
    BoardCameraTargetPlayerSet(currPlayer);
    BoardAudSeqPause(0, 0, 0x3E8);
    BoardPlayerRotSet(currPlayer, 0.0f, temp_f31, 0.0f);
    BoardPlayerMoveBetween(currPlayer, temp_r29, var_r30);
    KillBooHouseModel();
    BoardStatusShowSetAll(1);
    BoardPlayerIdleSet(currPlayer);
    HuPrcEnd();
}

static void DestroyBooHouse(void) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 3; var_r31++) {
        if (houseMot[var_r31] != -1) {
            BoardModelMotionKill(BoardBooHouseHostGet(), houseMot[var_r31]);
            houseMot[var_r31] = -1;
        }
    }
    if (houseShowMot != -1) {
        BoardModelMotionKill(houseMdl[0], houseShowMot);
        houseShowMot = -1;
    }
    if (houseHideMot != -1) {
        BoardModelMotionKill(houseMdl[1], houseHideMot);
        houseHideMot = -1;
    }
    BoardWinKill();
    KillBooHouseModel();
    HuDataDirClose(0x90000);
    _ClearFlag(0x10018);
    houseProc = 0;
}

static void PickComStealType(s32 arg0) {
    s32 var_r31;
    s32 var_r30;
    s32 var_r28;

    var_r30 = var_r28 = 0;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 != arg0) {
            var_r30 += BoardPlayerCoinsGet(var_r31);
            var_r28 += GWStarsGet(var_r31);
        }
    }
    if (BoardPlayerCoinsGet(arg0) >= 0x32) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            if ((var_r31 != arg0) && (GWStarsGet(var_r31) != 0) && (((s32) GWSystem.team == 0) || (var_r31 != BoardPlayerSameTeamFind(arg0)))) {
                if (var_r30 != 0) {
                    BoardComKeySetDown();
                } else {
                    BoardComKeySetUp();
                }
                return;
            }
        }
    }
    BoardComKeySetUp();
}

static void OpenBooHouse(void) {
    s16 temp_r31;
    s32 temp_r5;
    s32 var_r30;

    ballMdl = BoardBooCreate(currPlayer, 0);
    temp_r31 = BoardBooHouseHostGet();
    BoardModelMotionStart(temp_r31, 1, 0x40000001);
    
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        houseMot[var_r30] = BoardModelMotionCreate(temp_r31, houseMotTbl[GWBoardGet()][var_r30]);
    }
    BoardModelMotionStart(temp_r31, houseMot[0], 0x40000001);
    BoardModelVisibilitySet(temp_r31, 1);
    HuAudFXPlay(0x337);
    HuAudFXPlay(0x344);
    BoardModelMotionStart(houseMdl[0], 0, 0);
    BoardModelMotionSpeedSet(houseMdl[0], 1.0f);
    BoardModelHookSet(houseMdl[0], "yoko01", houseMdl[1]);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelHookSet(houseMdl[0], "yoko03", houseMdl[2]);
    BoardModelHookSet(houseMdl[0], "yoko04", houseMdl[3]);
    BoardModelHookSet(houseMdl[0], "yoko05", houseMdl[4]);
    BoardModelHookSet(houseMdl[0], "yoko9", houseMdl[5]);
    BoardModelHookSet(houseMdl[0], "yoko06", temp_r31);
    if (GWBoardGet() == 5) {
        BoardModelPosSet(temp_r31, 0.0f, 0.0f, -25.0f);
    } else {
        BoardModelPosSet(temp_r31, 0.0f, 0.0f, 0.0f);
    }
    BoardModelMotionStart(houseMdl[3], 0, 0x40000001);
    BoardModelMotionStart(houseMdl[4], 0, 0x40000001);
    booMdl = BoardModelCreate(0x20012, booMotTbl, 0);
    BoardModelMotionStart(booMdl, 1, 0x40000001);
    BoardModelVisibilitySet(booMdl, 1);
    BoardModelHookSet(houseMdl[0], "yoko8", booMdl);
    lbl_801D37F8 = BoardModelCreate(0x90008, NULL, 0);
    BoardModelVisibilitySet(lbl_801D37F8, 0);
    BoardModelLayerSet(lbl_801D37F8, 2);
    BoardModelMotionStart(houseMdl[1], 0, 0x40000001);

    while (BoardModelMotionTimeGet(houseMdl[0]) < 90.0f) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(houseMdl[0], houseShowMot, 0.0f, 10.0f, 0x40000001);
    BoardModelMotionShiftSet(houseMdl[1], houseHideMot, 0.0f, 10.0f, 0x40000001);
    BoardModelHookObjReset(houseMdl[0], "yoko02");
    SetBooBallPos();
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), houseMot[2], 0.0f, 10.0f, 0);
}

static void CloseBooHouse(void) {
    BoardModelPosSet(ballMdl, 0.0f, 0.0f, 0.0f);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelMotionShiftSet(houseMdl[1], 0, 90.0f, 10.0f, 0);
    BoardModelMotionShiftSet(houseMdl[0], 0, 90.0f, 10.0f, 0);
    HuPrcSleep(0xA);
    
    while (BoardModelMotionShiftIDGet(houseMdl[0]) != -1) {
        HuPrcVSleep();
    }
    while (BoardModelMotionTimeGet(houseMdl[0]) < 165.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x336);
    BoardAudSeqFadeOut(1, 0x3E8);
    
    while (BoardModelMotionEndCheck(houseMdl[0]) == 0) {
        HuPrcVSleep();
    }
    BoardModelHookReset(houseMdl[0]);
    BoardBooKill();
    ballMdl = -1;
}

static void CreateBooHouseModel(void) {
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 != 0) {
            houseMdl[var_r31] = BoardModelCreateParam(&houseMdlTbl[var_r31], 0, 0);
        }
    }
    houseShowMot = BoardModelMotionCreate(houseMdl[0], 0x90009);
    houseHideMot = BoardModelMotionCreate(houseMdl[1], 0x9000A);
}

static void KillBooHouseModel(void) {
    s32 temp_r4;
    s32 var_r31;

    for (var_r31 = 1; var_r31 < 6; var_r31++) {
        if (houseMdl[var_r31] != -1) {
            BoardModelKill(houseMdl[var_r31]);
            houseMdl[var_r31] = -1;
        }
    }
    if (booMdl != -1) {
        BoardModelKill(booMdl);
        booMdl = -1;
    }
    if (lbl_801D37F8 != -1) {
        BoardModelKill(lbl_801D37F8);
        lbl_801D37F8 = -1;
    }
    BoardModelVisibilitySet(BoardBooHouseHostGet(), 0);
}

static void ExecNullSteal(void) {
    HuAudFXPlay(0x4C);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][5], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
}

static void ExecStarSteal(void) {
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    s32 var_r30;
    s32 var_r31;

    
    for (var_r30 = 0; var_r30 < 0x32; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(1);
    }
    HuAudFXPlay(0xF);
    BoardBooStealTypeSet(1);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][3], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetAll(0);
    
    while (BoardPickerDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4C);
    Hu3DModelObjPosGet(BoardModelIDGet(houseMdl[0]), "yoko8", &sp14);
    sp14.y += 20.0f;
    BoardModelMotionStart(lbl_801D37F8, 0, 0);
    BoardModelVisibilitySet(lbl_801D37F8, 1);
    BoardModelPosSetV(lbl_801D37F8, &sp14);
    HuPrcSleep(5);

    for (var_r31 = 0xFF; var_r31 > 0; var_r31 -= 0x33) {
        if (var_r31 < 0) {
            var_r31 = 0;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(booMdl, 0);
    
    while (BoardModelMotionEndCheck(lbl_801D37F8) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(lbl_801D37F8, 0);
    BoardCameraMotionStartEx(ballMdl, NULL, NULL, 325.0f, -1.0f, 0x15);
    temp_r29 = BoardBooStealMain();
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], NULL, &sp8, 1370.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    if (temp_r29 == 0) {
        BoardModelMotionStart(booMdl, 2, 0x40000001);
    }
    BoardModelMotionStart(lbl_801D37F8, 0, 0);
    BoardModelVisibilitySet(lbl_801D37F8, 1);
    HuPrcSleep(0xB);
    BoardModelVisibilitySet(booMdl, 1);
    
    for (var_r31 = 0; var_r31 < 0xFF; var_r31 += 0x33) {
        if (var_r31 > 0xFF) {
            var_r31 = 0xFF;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(booMdl, -1);
    
    while (BoardModelMotionEndCheck(lbl_801D37F8) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(lbl_801D37F8, 0);
}

static void ExecCoinSteal(void) {
    Vec sp14;
    Vec sp8;
    s32 temp_r29;
    s32 var_r30;
    s32 var_r31;

    
    for (var_r30 = 0; var_r30 < 5; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    BoardBooStealTypeSet(0);
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][3], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetAll(0);
    
    while (BoardPickerDoneCheck() == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x4C);
    Hu3DModelObjPosGet(BoardModelIDGet(houseMdl[0]), "yoko8", &sp14);
    sp14.y += 20.0f;
    BoardModelMotionStart(lbl_801D37F8, 0, 0);
    BoardModelVisibilitySet(lbl_801D37F8, 1);
    BoardModelPosSetV(lbl_801D37F8, &sp14);
    HuPrcSleep(5);

    for (var_r31 = 0xFF; var_r31 > 0; var_r31 -= 0x33) {
        if (var_r31 < 0) {
            var_r31 = 0;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(booMdl, 0);
    
    while (BoardModelMotionEndCheck(lbl_801D37F8) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(lbl_801D37F8, 0);
    BoardCameraMotionStartEx(ballMdl, NULL, NULL, 325.0f, -1.0f, 0x15);
    temp_r29 = BoardBooStealMain();
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], NULL, &sp8, 1370.0f, -1.0f, 0x15);
    BoardCameraMotionWait();
    if (temp_r29 == 0) {
        BoardModelMotionStart(booMdl, 2, 0x40000001);
    }
    BoardModelMotionStart(lbl_801D37F8, 0, 0);
    BoardModelVisibilitySet(lbl_801D37F8, 1);
    HuPrcSleep(0xB);
    BoardModelVisibilitySet(booMdl, 1);
    
    for (var_r31 = 0; var_r31 < 0xFF; var_r31 += 0x33) {
        if (var_r31 > 0xFF) {
            var_r31 = 0xFF;
        }
        BoardModelAlphaSet(booMdl, var_r31);
        HuPrcVSleep();
    }
    BoardModelAlphaSet(booMdl, -1);
    
    while (BoardModelMotionEndCheck(lbl_801D37F8) == 0) {
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(lbl_801D37F8, 0);
}

void ApplySteal(void) {
    s16 spA;
    s16 sp8;
    s32 temp_r30;
    s32 temp_r6;
    s32 var_r31;
    float var_f31;

    BoardModelHookSet(houseMdl[0], "yoko8", booMdl);
    BoardModelVisibilitySet(booMdl, 1);
    BoardModelPosSet(booMdl, 0.0f, 0.0f, 0.0f);
    BoardModelRotSet(booMdl, 0.0f, 0.0f, 0.0f);
    BoardModelScaleSet(booMdl, 1.0f, 1.0f, 1.0f);
    BoardModelAlphaSet(booMdl, 0xFF);
    var_f31 = BoardDAngleCalc(180.0f + BoardPlayerRotYGet(currPlayer));
    BoardPlayerMotBlendSet(currPlayer, var_f31, 0xF);
    
    while (BoardPlayerMotBlendCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    BoardPlayerIdleSet(currPlayer);
    var_r31 = BoardBooStealValueGet(&spA, &sp8);
    if (var_r31 == 0) {
        ApplyBooLight();
    } else if (stealTarget == 0) {
        ApplyCoinSteal(spA, sp8);
    } else {
        ApplyStarSteal();
    }
    BoardWinCreate(2, hostMesTbl[GWBoardGet()][4], BoardWinPortraitGet());
    BoardWinWait();
    BoardWinKill();
}

void ApplyCoinSteal(s16 arg0, s16 arg1) {
    u32 var_r31;
    s32 var_r30;

    if ((s16) arg1 == 0) {
        var_r31 = 0x70009;
    } else if ((s16) arg1 < 3) {
        var_r31 = 0x70008;
    } else if ((s16) arg1 < 6) {
        var_r31 = 0x70007;
    } else if ((s16) arg1 < 8) {
        var_r31 = 0x70006;
    } else {
        var_r31 = 0x70005;
    }
    sprintf(&stealAmountStr, "%d", arg0);
    HuAudFXPlay(0x4B);
    BoardWinCreate(2, var_r31, 3);
    BoardWinInsertMesSet((s32) &stealAmountStr, 0);
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetForce(currPlayer);
    BoardStatusShowSet(currPlayer, 1);
    BoardPlayerMotionShiftSet(currPlayer, 7, 0.0f, 8.0f, 0);
    
    for (var_r30 = 0; var_r30 < arg0; var_r30++) {
        BoardPlayerCoinsAdd(currPlayer, 1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    BoardPlayerMotionEndWait(currPlayer);
}

void ApplyStarSteal(void) {
    s32 temp_r31;

    HuAudFXPlay(0x4C);
    BoardWinCreate(2, 0x7000A, 3);
    BoardWinWait();
    BoardWinKill();
    BoardStatusShowSetForce(currPlayer);
    BoardStatusShowSet(currPlayer, 1);
    BoardAudSeqPause(1, 1, 0x3E8);
    HuPrcSleep(0x17);
    BoardPlayerVoiceEnableSet(currPlayer, 7, 0);
    BoardPlayerMotionShiftSet(currPlayer, 7, 0.0f, 8.0f, 0);
    HuAudFXPlay(boardStarSndTbl[GWPlayer[currPlayer].character]);
    BoardPlayerStarsAdd(currPlayer, 1);
    HuAudFXPlay(8);
    HuPrcSleep(0xA);
    temp_r31 = HuAudSStreamPlay(6);
    BoardPlayerMotionEndWait(currPlayer);
    
    while (msmStreamGetStatus(temp_r31) != 0) {
        HuPrcVSleep();
    }
    BoardAudSeqPause(1, 0, 0x3E8);
    BoardPlayerMotionEndWait(currPlayer);
    BoardPlayerVoiceEnableSet(currPlayer, 7, 1);
}

void ApplyBooLight(void) {
    BoardWinCreate(2, 0x7000B, 3);
    BoardWinWait();
    BoardWinKill();
    BoardPlayerMotionShiftSet(currPlayer, 8, 0.0f, 8.0f, 0);
    while (BoardPlayerMotionEndCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
}

void SetBooBallPos(void) {
    Mtx sp14;
    Vec sp8;
    s16 var_r31;

    var_r31 = BoardModelIDGet(houseMdl[0]);
    Hu3DModelObjMtxGet(var_r31, "yoko02", sp14);
    Hu3DMtxTransGet(sp14, &sp8);
    BoardModelPosSetV(ballMdl, &sp8);
}

s32 BoardBooComUseCheck(s32 arg0) {
    s32 var_r31;
    u32 var_r30;
    s32 var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    s32 var_r24;

    var_r24 = BoardPlayerCoinsGet(arg0);
    comStarStealTarget = comCoinStealTarget = -1;
    var_r26 = var_r27 = -1;
    switch (GWPlayer[arg0].diff) {
    case 0:
        var_r30 = 0x5F;
        break;
    case 1:
        var_r30 = 0x32;
        break;
    case 2:
        var_r30 = 5;
        break;
    case 3:
        var_r30 = 0;
        break;
    }
    
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        if (var_r31 != arg0) {
            if ((s32) GWSystem.team == 0 || var_r31 != BoardPlayerSameTeamFind(arg0)) {
                if (BoardPlayerItemFind(var_r31, 8) == -1 || BoardRandMod(0x64) < var_r30) {
                    var_r29 = BoardPlayerCoinsGet(var_r31);
                    var_r28 = GWStarsGet(var_r31);
                    if (var_r28 != 0 || var_r29 != 0) {
                        if (var_r28 != 0 || var_r29 >= 5 || var_r24 <= 10 || BoardRandMod(0x64) <= 0x32) {
                            if (var_r27 < var_r29) {
                                var_r27 = var_r29;
                                comCoinStealTarget = var_r31;
                            }
                            if (var_r26 < var_r28) {
                                var_r26 = var_r28;
                                comStarStealTarget = (s8) var_r31;
                            }
                        }
                    }
                }
            }
        }
    }
    if ((var_r26 <= 0) && (var_r27 <= 0)) {
        return 0;
    }
    return 1;
}

void BoardBooHouseTutorialExec(void) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec sp8;
    float temp_f31;
    s16 temp_r28;
    s16 temp_r29;
    s32 temp_r27;
    s32 temp_r4;
    s32 var_r31;
    s32 var_r30;

    temp_r27 = BoardDataDirReadAsync(0x90000);
    temp_r29 = BoardSpaceFlagSearch(0, 0x08000000);
    BoardDataAsyncWait(temp_r27);
    temp_r28 = BoardSpaceLinkFlagSearch(0, temp_r29, 0x02000000);
    BoardSpacePosGet(0, temp_r29, &sp38);
    BoardSpacePosGet(0, temp_r28, &sp2C);
    PSVECSubtract(&sp2C, &sp38, &sp20);
    PSVECNormalize(&sp20, &sp20);
    temp_f31 = atan2d(-sp20.x, -sp20.z);
    sp14.x = -15.0f;
    sp14.y = temp_f31;
    sp14.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = 150.0f;
    sp8.z = 0.0f;
    BoardCameraMotionStartEx(houseMdl[0], &sp14, &sp8, 1370.0f, -1.0f, 0x15);
    
    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (var_r31 != 0) {
            houseMdl[var_r31] = BoardModelCreateParam(&houseMdlTbl[var_r31], NULL, NULL);
        }
    }
    houseShowMot = BoardModelMotionCreate(houseMdl[0], 0x90009);
    houseHideMot = BoardModelMotionCreate(houseMdl[1], 0x9000A);
    OpenBooHouse();
    
    while (BoardModelMotionEndCheck(BoardBooHouseHostGet()) == 0) {
        HuPrcVSleep();
    }
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), houseMot[0], 0.0f, 10.0f, 0x40000001);
    BoardTutorialHookExec(0x1C, 0);
    BoardModelMotionShiftSet(BoardBooHouseHostGet(), houseMot[1], 0.0f, 10.0f, 0x40000001);
    BoardModelPosSet(ballMdl, 0.0f, 0.0f, 0.0f);
    BoardModelHookSet(houseMdl[0], "yoko02", ballMdl);
    BoardModelMotionShiftSet(houseMdl[1], 0, 90.0f, 10.0f, 0);
    BoardModelMotionShiftSet(houseMdl[0], 0, 90.0f, 10.0f, 0);
    HuPrcSleep(0xA);
    while (BoardModelMotionShiftIDGet(houseMdl[0]) != -1) {
        HuPrcVSleep();
    }
    while (BoardModelMotionTimeGet(houseMdl[0]) < 165.0f) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x336);
    BoardAudSeqFadeOut(1, 0x3E8);
    while (BoardModelMotionEndCheck(houseMdl[0]) == 0) {
        HuPrcVSleep();
    }
    BoardModelHookReset(houseMdl[0]);
    BoardBooKill();
    ballMdl = -1;
    
    for (var_r30 = 1; var_r30 < 6; var_r30++) {
        if (houseMdl[var_r30] != -1) {
            BoardModelKill(houseMdl[var_r30]);
            houseMdl[var_r30] = -1;
        }
    }
    if (booMdl != -1) {
        BoardModelKill(booMdl);
        booMdl = -1;
    }
    if (lbl_801D37F8 != -1) {
        BoardModelKill(lbl_801D37F8);
        lbl_801D37F8 = -1;
    }
    BoardModelVisibilitySet(BoardBooHouseHostGet(), 0);
}
