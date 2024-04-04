#include "dolphin.h"
#include "game/object.h"
#include "REL/w03Dll.h"
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/hsfdraw.h"

//BSS
char lbl_1_bss_130[8];
omObjData* lbl_1_bss_12C;
s16 lbl_1_bss_128;
s32 lbl_1_bss_124;
Process* lbl_1_bss_120;

//function signatures
void fn_1_67F8(void);
void fn_1_6884(void);
void fn_1_767C(omObjData* arg0);
s32 fn_1_6898(s32 arg0);
void fn_1_6B98(s32 arg0);
void fn_1_6F9C(s32 arg0);
void fn_1_767C(omObjData* arg0);
void fn_1_735C(s32 arg0);
void fn_1_77E4(s32 arg0);

typedef struct unkWorkStruct {
    struct {
        u8 temp1 : 1;
    };
    s8 unk_01[3];
    f32 unk_04;
} unkWorkStruct;

//data
s32 lbl_1_data_368[] = {
    0x00000105, 0x00000145, 0x00000185,
    0x000001C5, 0x00000205, 0x00000245,
    0x00000285, 0x000002C5
};

s16 lbl_1_data_388 = -1;
s16 lbl_1_data_38A = -1;
s16 lbl_1_data_38C = -1;
s32 lbl_1_data_390[] = {
    0x00770026,
    0x00770027,
    0x00770028,
    -1
};

void fn_1_63F4(s32 arg0) {
    Vec spC;
    unkWorkStruct* work = OM_GET_WORK_PTR(lbl_1_bss_12C, unkWorkStruct);

    work->unk_04 = 0.0f;

    BoardModelPosGet(lbl_1_data_388, &spC);
    if (arg0 != 0) {
        spC.y = -185.0f;
    } else {
        spC.y = 10.0f;
    }

    BoardModelPosSetV(lbl_1_data_388, &spC);
}

void fn_1_6494(void) {
    Vec sp14;
    Vec sp8;
    unkWorkStruct* temp_r31;

    lbl_1_data_388 = BoardModelCreate(0x77000E, NULL, 0);
    lbl_1_data_38C = BoardModelCreate(0x77000F, NULL, 0);
    lbl_1_data_38A = BoardModelCreate(0x2000D, &lbl_1_data_390[0], 0);
    BoardModelMotionStart(lbl_1_data_38A, 1, 0x40000001);
    BoardModelHookSet(lbl_1_data_38A, "itemhook_R", lbl_1_data_38C);
    BoardModelHookSet(lbl_1_data_388, "hei01", lbl_1_data_38A);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_C[0]), "ikada", &sp14);
    BoardSpaceFlagPosGet(0, 0x200, &sp8);
    sp14.x = sp8.x + (400.0 * sin(-(M_PI / 2)));
    sp14.z = sp8.z + (400.0 * cos(-(M_PI / 2)));
    BoardModelPosSetV(lbl_1_data_388, &sp14);
    lbl_1_bss_12C = omAddObjEx(boardObjMan, 0x101, 0, 0, -1, (void*)fn_1_767C);
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_12C, unkWorkStruct);
    temp_r31->temp1 = 0;
    temp_r31->unk_04 = 0.0f;
    lbl_1_bss_124 = 0;
}

s32 fn_1_6698(void) {
    Vec sp14;
    Vec sp8;

    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_C[0]), "ikada", &sp14);
    BoardSpaceFlagPosGet(0, 0x200, &sp8);
    sp14.x = sp8.x + (400.0 * sin(-(M_PI / 2)));
    sp14.z = sp8.z + (400.0 * cos(-(M_PI / 2)));
    BoardModelPosSetV(lbl_1_data_388, (Point3d* ) &sp14);
    return 1;
}

s16 fn_1_675C(void) {
    BoardDiceDigit2DShowSet(0);
    lbl_1_bss_120 = HuPrcChildCreate(fn_1_67F8, 0x2003, 0x2000, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_120, fn_1_6884);

    while (lbl_1_bss_120 != 0) {
        HuPrcVSleep();
    }

    BoardDiceDigit2DShowSet(1);
    return lbl_1_bss_128;
}

void fn_1_67F8(void) {
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    lbl_1_bss_128 = 0;

    if (fn_1_6898(temp_r31) != 0) {
        fn_1_6F9C(temp_r31);
        fn_1_6B98(temp_r31);
        fn_1_735C(temp_r31);
        lbl_1_bss_128 = 1;
    }

    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    HuPrcEnd();
}

void fn_1_6884(void) {
    lbl_1_bss_120 = 0;
}

typedef struct unkPos {
    s32 x;
    s32 y;
    s32 z;
} unkPos;

unkPos lbl_1_data_3B8[6] = {
    {5, 20, 5},
    {21, 35, 7},
    {31, 50, 10},
    {51, 80, 15},
    {81, 100, 17},
    {101, 999, 20},
};

s32 fn_1_6898(s32 arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    s32 var_r27;
    s32 temp_r3;
    s32 i, j;
    s32 temp, temp2;

    BoardPlayerIdleSet(arg0);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_388), "hei01", &sp20);
    BoardPlayerPosGet(arg0, &sp14);
    PSVECSubtract(&sp20, &sp14, &sp8);
    temp_f31 = 180.0 * (atan2(sp8.x, sp8.z) / M_PI);
    BoardCameraTargetModelSet(lbl_1_data_388);
    BoardPlayerMotBlendSet(arg0, temp_f31, 15);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    BoardCameraTargetModelSet(-1);
    BoardWinCreate(2, 0x160009, 2);
    BoardWinWait();
    temp_r3 = BoardPlayerCoinsGet(arg0);

    if (temp_r3 < 5) {
        BoardWinCreate(2, 0x16000A, 2);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }

    for (var_r27 = i = 0; i < ARRAY_COUNT(lbl_1_data_3B8); i++) {
        temp = lbl_1_data_3B8[i].x;
        temp2 = lbl_1_data_3B8[i].y;
        if (temp_r3 >= temp) {
            if (temp_r3 <= temp2) {
                var_r27 = lbl_1_data_3B8[i].z;
                break;
            }
        }      
    }

    sprintf(lbl_1_bss_130, "%d", var_r27);

    j = 0;
    while (j == 0) {
        BoardWinCreateChoice(2, 0x16000B, 2, 0);
        BoardWinInsertMesSet(lbl_1_bss_130, 2);
        BoardWinAttrSet(0x10);

        if (GWPlayer[arg0].com != 0) {
            fn_1_77E4(arg0);
        }

        BoardWinWait();
        BoardWinKill();

        switch (BoardWinChoiceGet()) {
        case 0:
            j = 1;
            break;
        case 1:
        case -1:
            BoardWinCreate(2, 0x16000E, 2);
            BoardWinWait();
            BoardWinKill();
            return 0;
        default:
            BoardViewMapExec(arg0);
        }
    }

    for (i = 0; i < var_r27; i++) {
        BoardPlayerCoinsAdd(arg0, -1);
        HuAudFXPlay(0xE);
        HuPrcSleep(6);             
    }

    HuAudFXPlay(0xF);
    BoardWinCreate(2, 0x0016000C, 2);
    BoardWinWait();
    BoardWinKill();
    return 1;
}

s32 BoardDAngleCalcRange(float *value, float min, float range);

void fn_1_6B98(s32 arg0) {
    Vec sp30;
    Point3d sp24;
    Vec sp18;
    Point3d spC;
    f32 sp8;
    f32 temp_f1;
    f32 temp_f31;
    s16 var_r31;
    s16 i;

    BoardModelMotionShiftSet(lbl_1_data_38A, 2, 0.0f, 10.0f, 0);
    sp8 = BoardModelRotYGet(lbl_1_data_38A);
    temp_f31 = sp8 + 180.0f;

    while (BoardDAngleCalcRange(&sp8, temp_f31, 3.0f) == 0) {
        BoardModelRotYSet(lbl_1_data_38A, sp8);
        HuPrcVSleep();
    }

    while (BoardModelMotionEndCheck(lbl_1_data_38A) == 0) {
        HuPrcVSleep();
    }

    BoardModelPosGet(lbl_1_data_388, &sp24);
    BoardSpaceFlagPosGet(0, 0x100, &sp30);
    sp18.x = sp30.x + (400.0 * sin(M_PI / 2));
    sp18.z = sp30.z + (400.0 * cos(M_PI / 2));
    sp18.y = sp24.y;
    PSVECSubtract(&sp18, &sp24, &spC);
    spC.x = spC.x / 120.0f;
    spC.y /= 120.0f;
    spC.z = spC.z / 120.0f;
    BoardCameraTargetModelSet(lbl_1_data_388);
    BoardModelMotionShiftSet(lbl_1_data_38A, 3, 0.0f, 4.0f, 0x40000001U);
    HuPrcSleep(4);

    var_r31 = 0;
    for (i = 0; i < 0x78U; i++) {
        PSVECAdd(&spC, &sp24, &sp24);
        temp_f1 = BoardModelMotionTimeGet(lbl_1_data_38A);

        if ((temp_f1 >= 5.0f) && (temp_f1 < 15.0f) && ((s16) var_r31 == 0)) {
            HuAudFXPlay(0x451);
            var_r31 = 1;
        }

        if ((BoardModelMotionTimeGet(lbl_1_data_38A) >= 21.0f) && ((s16) var_r31 != 0)) {
            var_r31 = 0;
        }

        BoardModelPosSetV(lbl_1_data_388, &sp24);
        HuPrcVSleep();       
    }
    
    BoardModelPosSetV(lbl_1_data_388, &sp18);
    BoardCameraTargetModelSet(-1);
    BoardModelMotionShiftSet(lbl_1_data_38A, 2, 0.0f, 10.0f, 0x40000004U);
    sp8 = BoardModelRotYGet(lbl_1_data_38A);
    temp_f31 = 0.0f;

    while (BoardDAngleCalcRange(&sp8, temp_f31, 3.0f) == 0) {
        BoardModelRotYSet(lbl_1_data_38A, sp8);
        HuPrcVSleep();
    }

    while (BoardModelMotionEndCheck(lbl_1_data_38A) == 0) {
        HuPrcVSleep();
    }

    BoardModelMotionShiftSet(lbl_1_data_38A, 1, 0.0f, 10.0f, 0x40000001U);
}

extern s32 lbl_1_data_368[];
// extern w03State* lbl_1_bss_0;

void fn_1_6F9C(s32 arg0) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 var_f30;
    f32 var_f29;
    f32 var_f31;
    s32 temp_r4;
    s32 var_r30;
    s16 model;

    BoardPlayerPosGet(arg0, &sp14);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_388), "chara01", &sp20);
    PSVECSubtract(&sp20, &sp14, &sp8);

    sp8.x /= 60.0f;
    sp8.z /= 60.0f;
    sp8.y = 0.0f;

    if (lbl_1_bss_0->unk0 != 0) {
        var_f30 = 10.0f;
        var_f29 = 0.21f;
        sp14.y += sp20.y;
    } else {
        var_f30 = 0.0f;
        var_f29 = 0.15f;
    }

    lbl_1_bss_124 = 1;
    HuAudFXPlay(lbl_1_data_368[GWPlayer[arg0].character]);
    BoardPlayerMotionShiftSet(arg0, 4, 0.0f, 10.0f, 0);

    for (var_r30 = 0, var_f31 = 0.0f; var_f31 < 60.0f; var_f31 += 1.0f) {
        PSVECAdd(&sp14, &sp8, &sp14);
        sp14.y += 10.0f + var_f30 + (var_f29 * (-0.08166667f * var_f31 * var_f31));
        if (sp14.y <= sp20.y) {
            sp14.y = sp20.y;
            if (var_r30 == 0) {
                BoardPlayerMotionShiftSet(arg0, 5, 0.0f, 8.0f, 0);
                var_r30 = 1;
            }
        }
        BoardPlayerPosSetV(arg0, &sp14);
        HuPrcVSleep();        
    }
    
    BoardPlayerMotionShiftSet(arg0, 5, 0.0f, 8.0f, 0);
    HuPrcSleep(10);
    BoardPlayerIdleSet(arg0);

    if (GWPlayer[arg0].bowser_suit != 0) {
        BoardModelHookSet(lbl_1_data_388, "chara01", BoardPlayerModelGet(arg0));
    } else {
        BoardModelHookSet(lbl_1_data_388, "chara01", BoardPlayerModelGet(arg0));
    }

    BoardPlayerPosSet(arg0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_124 = 0;
}

void fn_1_735C(s32 arg0) {
    Vec sp20;
    Vec sp14;
    Point3d sp8;
    f32 temp_f1;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r29;
    s32 temp_r4;
    s32 var_r30;

    temp_r29 = BoardSpaceFlagPosGet(0, 0x100, &sp20);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_388), "chara01", &sp14);
    BoardPlayerPosSetV(arg0, &sp14);
    BoardModelHookObjReset(lbl_1_data_388, "chara01");
    PSVECSubtract(&sp20, &sp14, &sp8);
    
    sp8.x = sp8.x / 60.0f;
    sp8.z = sp8.z / 60.0f;
    sp8.y = 0.0f;
    
    HuAudFXPlay(lbl_1_data_368[GWPlayer[arg0].character]);
    BoardPlayerMotionShiftSet(arg0, 4, 0.0f, 10.0f, 0);
    if (lbl_1_bss_0->unk0 != 0) {
        var_f30 = 0.25f;
    } else {
        var_f30 = 0.2f;
    }
    
    for (var_r30 = 0, var_f31 = 0.0f; var_f31 < 60.0f; var_f31 += 1.0f) {
        PSVECAdd(&sp14, &sp8, &sp14);
        sp14.y += 20.0f + (var_f30 * (-0.08166667f * var_f31 * var_f31));
        if (sp14.y <= sp20.y && var_f31 > 48.0f) {
            sp14.y = sp20.y;
            if (var_r30 == 0) {
                BoardPlayerMotionShiftSet(arg0, 5, 0.0f, 8.0f, 0);
                var_r30 = 1;
            }
        }
        BoardPlayerPosSetV(arg0, &sp14);
        HuPrcVSleep();        
    }
    
    BoardPlayerPosSetV(arg0, &sp20);
    HuPrcSleep(0xA);
    BoardPlayerMotBlendSet(arg0, 0, 15);

    while (BoardPlayerMotBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }

    BoardPlayerIdleSet(arg0);
    GWPlayer[arg0].space_curr = temp_r29;
    GWPlayer[arg0].space_prev = -1;
    BoardPlayerPostTurnHookSet(arg0, fn_1_6698);
    BoardWinCreate(2, 0x16000D, 2);
    BoardWinWait();
    BoardWinKill();
}


void fn_1_767C(omObjData* arg0) {
    Point3d sp8;
    s32 temp_r30;
    unkWorkStruct* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, unkWorkStruct);

    if ( (temp_r31->temp1 != 0) || (BoardIsKill() != 0)) {
        lbl_1_bss_12C = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }

    if ((lbl_1_data_388 != -1) && (lbl_1_bss_124 == 0)) {
        temp_r31->unk_04 += 3.0f;
        if (temp_r31->unk_04 >= 360.0f) {
            temp_r31->unk_04 = (f32) (temp_r31->unk_04 - 360.0f);
        }
        BoardModelPosGet(lbl_1_data_388, &sp8);
        sp8.y = (f32) ((f64) sp8.y + (0.25 * (2.0 * sin((M_PI * (f64) temp_r31->unk_04) / 180.0))));
        BoardModelPosSetV(lbl_1_data_388, &sp8);
    }
}

void fn_1_77E4(s32 arg0) {
    s32 boardIndex;
    s32 var_r30 = 0;

    boardIndex = GWSystem.star_pos;

    if ((boardIndex == 1) || (boardIndex == 2) || (boardIndex == 3) || (boardIndex == 4)) {
        var_r30 = 1;
    }

    if (var_r30 != 0) {
        BoardComKeySetLeft();
        return;
    }

    BoardComKeySetRight();
}
