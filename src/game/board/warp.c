#include "game/board/warp.h"

extern void omVibrate(s16, s16, s16, s16);
extern void fn_800816CC(s32, s32);
extern void fn_80081884(f32);
extern void fn_8008181C(void);
extern s32 fn_8008186C(void);
extern f32 BoardModelMotionTimeGet(s16);
extern void BoardModelHookReset(s16);
extern s32 BoardModelHookSet(s16, char*, s16);
extern void BoardPlayerPosSet(s32, f32, f32, f32);
extern void BoardPlayerRotYSet(s32, f32);
extern void Hu3DModelObjPosGet(s16, char*, Vec*);
extern s32 BoardModelMotionEndCheck(s16);
extern void BoardPlayerPosSetV(s32, Point3d*);
void BoardPlayerRotSet(s32, f32, f32, f32);
void BoardCameraVisibleSet(s32);
void BoardCameraSTargetetSpace(s16);
extern void BoardRotateDiceNumbers(s32);
extern void BoardPlayerPosGet(s32, Vec*);
void BoardPlayerMotionStart(s16, s32, s32);

extern Process* boardMainProc;
extern s32 boardTutorialData[4];
extern s16 boardPlayerMdl[4];

void fn_80080D54(s32 arg0) {
    omVibrate(arg0, 0xC, 4, 2);
    lbl_801D4028 = HuPrcChildCreate(fn_80080DF8, 0x2003U, 0x3800U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_801D4028, fn_80081048);

    while (lbl_801D4028 != NULL) {
        HuPrcVSleep();
    }
    GWPlayer[arg0].color = 3;
}

void fn_80080DF8(void) {
    s32 currPlayer;
    f32 var_f1;
    s32 temp_r3[8] = {291, 355, 419, 483, 547, 611, 675, 739};
    
    lbl_801D4038 = 0;
    currPlayer = GWSystem.player_curr;
    HuAudFXPlay(0x34A);
    BoardCameraViewSet(3);
    BoardCameraMotionWait();
    BoardPlayerAnimBlendSet(currPlayer, 0, 15);

    while (BoardPlayerAnimBlendCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    
    BoardRotateDiceNumbers(currPlayer);
    if (_CheckFlag(0x1000B) != 0) {
        BoardTutorialHookExec(0x12, 0);
        boardTutorialData[0] = 0;
    }
    fn_800816CC(currPlayer, 3);
    fn_80081884(18.0f);
    fn_8008181C();
    lbl_801D4037 = fn_8008186C();
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    fn_800810A4(currPlayer);

    while (1) {
        switch (lbl_801D4038) {
            case 0:
                if (BoardModelMotionTimeGet(lbl_801D3748) < 15.0f) {
                    break;
                }
                BoardModelHookReset(lbl_801D3748);
                Hu3DModelObjPosGet(BoardModelIDGet(lbl_801D3748), lbl_801D3750, &lbl_801A4AC0);
                BoardSpacePosGet(0, GWPlayer[currPlayer].space_curr, &lbl_801A4AC0);
                lbl_801A4AC0.y += 700.0f;
                BoardPlayerPosSetV(currPlayer, &lbl_801A4AC0);
                lbl_801D4038 = 1;
                HuAudFXPlay(temp_r3[GWPlayer[currPlayer].character]);
                break;
            case 1:
                fn_800811BC(currPlayer);
                break;
            case 2:
                if (BoardModelMotionEndCheck(lbl_801D3748) == 0) break;
                lbl_801D4038 = 6;
                break;
            case 3:
                fn_80081278(currPlayer);
                break;
            case 4:
                fn_80081428(currPlayer);
                break;
            case 5:
                fn_800814CC(currPlayer);
                break;
            case 6:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}

void fn_80081048(void) {
    if (lbl_801D3748 != -1) {
        BoardModelKill(lbl_801D3748);
        lbl_801D3748 = -1;
    }
    if (lbl_801D374A != -1) {
        BoardModelKill(lbl_801D374A);
        lbl_801D374A = -1;
    }
    lbl_801D4028 = NULL;
}

static inline PlayerState* GetPlayer(s32 index) {
    return &GWPlayer[index];
}

static inline s16 GetBoardPlayer(s32 index) {
    PlayerState *player = GetPlayer(index);
    return boardPlayerMdl[player->player_idx];
}

void fn_800810A4(s32 arg0) {
    Point3d sp8;
    s16 temp_r30 = GetBoardPlayer(arg0);

    lbl_801D3748 = BoardModelCreate(0x70001, NULL, 0);
    BoardSpacePosGet(0, GWPlayer[arg0].space_curr, &sp8);
    lbl_801D4030 = 1500.0f + sp8.y;
    BoardModelLayerSet(lbl_801D3748, 2);
    BoardCameraTargetSetModel(lbl_801D3748);
    BoardModelMotionStart(lbl_801D3748, 0, 0);
    BoardModelHookSet(lbl_801D3748, lbl_801D3750, temp_r30);
    BoardModelPosSetV(lbl_801D3748, &sp8);
    HuAudFXPlay(0x343);
    BoardPlayerRotYSet(arg0, 0.0f);
    BoardPlayerPosSet(arg0, 0.0f, 0.0f, 0.0f);
    BoardRotateDiceNumbers(arg0);
}

void fn_800811BC(s32 arg0) {
    f32 temp_f1;

    lbl_801A4AC0.y += 20.0f;
    BoardPlayerPosSetV(arg0, &lbl_801A4AC0);
    if (!(lbl_801A4AC0.y < lbl_801D4030)) {
        WipeColorSet(0U, 0U, 0U);
        WipeCreate(2, 0, 0x15);
        
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        lbl_801A4AC0.y = lbl_801D4030;
        BoardModelVisibilitySet(lbl_801D3748, 0);
        lbl_801D4038 = 3;
    }
}

void fn_80081278(s32 arg0) {
    f32 temp_f1;
    s32 var_r31;

    lbl_801D4034 = GWPlayer[lbl_801D4037].space_curr;
    GWPlayer[arg0].space_curr = lbl_801D4034;
    BoardSpacePosGet(0, lbl_801D4034, &lbl_801A4AC0);
    lbl_801D4030 = lbl_801A4AC0.y;
    lbl_801A4AC0.y += 1500.0f;
    BoardPlayerPosSetV(arg0, &lbl_801A4AC0);
    BoardPlayerRotSet(arg0, 180.0f, 180.0f, 0.0f);
    
    for (var_r31 = 0, lbl_801D4036 = var_r31; var_r31 < 4; var_r31++) {
        if (lbl_801D4034 == GWPlayer[var_r31].space_curr) {
            lbl_801D374C[lbl_801D4036] = var_r31;
            lbl_801D4036++;
        }
    }
    lbl_801D374A = BoardModelCreate(0x70002, NULL, 0);
    BoardModelVisibilitySet(lbl_801D374A, 0);
    BoardModelMotionSpeedSet(lbl_801D374A, 0.0f);
    BoardCameraVisibleSet(0);
    BoardCameraSTargetetSpace(lbl_801D4034);
    HuPrcSleep(1);
    WipeCreate(1, 0, 0x15);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardCameraVisibleSet(1);
    lbl_801D402C = -10.0f;
    lbl_801D4038 = 4;
}

void fn_80081428(s32 arg0) {
    lbl_801D402C += -2.0f;
    lbl_801A4AC0.y += lbl_801D402C;
    if (lbl_801A4AC0.y <= (150.0f + lbl_801D4030)) {
        lbl_801A4AC0.y = lbl_801D4030;
        lbl_801D4038 = 5;
        HuAudFXPlay(0x345);
        HuAudFXPlay(0x33D);
    }
    BoardPlayerPosSetV(arg0, &lbl_801A4AC0);
}

void fn_800814CC(s32 arg0) {
    Vec sp18;
    Point3d spC;
    s16 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    s16 var_r31;
    s32 temp_r30;

    sp18.x = 288.0f;
    sp18.y = 240.0f;
    sp18.z = 700.0f;
    Hu3D2Dto3D(&sp18, 1, &sp18);
    BoardModelPosSetV(lbl_801D374A, &sp18);
    BoardModelVisibilitySet(lbl_801D374A, 1);
    BoardModelMotionStart(lbl_801D374A, 0, 0x40000001);
    
    for (var_r31 = 0; var_r31 < lbl_801D4036; var_r31++) {
        temp_r30 = lbl_801D374C[var_r31];
        omVibrate(temp_r30, 0xC, 4, 2);
        BoardPlayerMotionStart(temp_r30, 6, 0x40000001);
    }
    BoardPlayerRotSet(arg0, 0.0f, 0.0f, 0.0f);
    BoardPlayerPosGet(arg0, &spC);
    spC.y = lbl_801D4030;
    BoardPlayerPosSetV(arg0, &spC);
    temp_f29 = 4.0f;
    
    for (var_f31 = 0.0f, sp8 = var_f31; var_f31 < 180.0f; var_f31 += temp_f29) {
        temp_f30 = sin((M_PI * var_f31) / 180.0);
        BoardModelScaleSet(lbl_801D374A, 0.5f + temp_f30, 0.5f + temp_f30, 0.5f + temp_f30);
        HuPrcVSleep();
    }
    BoardModelVisibilitySet(lbl_801D374A, 0);
    HuPrcSleep(0x3C);
    
    for (var_r31 = 0; var_r31 < lbl_801D4036; var_r31++) {
        BoardRotateDiceNumbers(lbl_801D374C[var_r31]);
    }
    lbl_801D4038 = 6;
}