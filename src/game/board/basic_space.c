#include "game/board/basic_space.h"

void BoardTutorialHookExec(s16, s32);
void BoardCameraViewSet(s32);
void omVibrate(s16, s16, s16, s16);
void BoardPlayerPosGet(s32, Vec*);
s32 BoardModelPosGet(s16, Vec*);
void BoardPlayerMotionEndWait(s32);
void BoardPlayerMotionShiftSet(s32, s32, f32, f32, s32);
void BoardPlayerCoinsAdd(s32, s32);
void BoardRotateDiceNumbers(s32);
void BoardCameraAnimBlendSet(s32, s16, s16);
s32 BoardPlayerAnimBlendCheck(s32);

omObjData *lbl_8013A1F0[4] = {
    (omObjData *)NULL,
    (omObjData *)NULL,
    (omObjData *)NULL,
    (omObjData *)NULL
};

s32 lbl_8013A200[10] = {
    0x7000C, 0x7000D,
    0x7000E, 0x7000F,
    0x70010, 0x70011,
    0x70012, 0x70013,
    0x70014, 0x70015
};

void BoardEventLandBlue(s32 arg0) {
    Point3d sp8;
    f32 temp_f1;
    s32 var_r29;
    s8 temp_r28;
    s32 var_r30;

    BoardCameraViewSet(2);
    BoardPlayerAnimBlendSet(arg0, 0, 0xF);
    while (BoardPlayerAnimBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
    if (_CheckFlag(0x1000BU) != 0) {
        BoardCameraMotionWait();
        BoardTutorialHookExec(0xA, 0);
    }
    var_r30 = 3;
    if (GWSystem.last5_effect == 1) {
        var_r30 *= 2;
    }
    BoardPlayerPosGet(arg0, &sp8);
    sp8.y += 250.0f;
    temp_r28 = fn_8007FE70(&sp8, var_r30);
    HuAudFXPlay(0x347);
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(arg0, 0xC, 0.0f, 4.0f, 0);
    
    for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
        BoardPlayerCoinsAdd(arg0, 1);
        HuAudFXPlay(7);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    while (fn_80080058(temp_r28) == 0) {
        HuPrcVSleep();
    }
    GWPlayer[arg0].color = 1;
    BoardPlayerMotionEndWait(arg0);
    BoardRotateDiceNumbers(arg0);
}

void BoardEventLandRed(s32 arg0) {
    Point3d sp8;
    s32 var_r29;
    s8 temp_r28;
    s32 var_r30;
    void* temp_r3;

    BoardCameraViewSet(2);
    omVibrate(arg0, 0xC, 6, 6);
    BoardPlayerAnimBlendSet(arg0, 0, 0xF);
    while (BoardPlayerAnimBlendCheck(arg0) == 0) {
        HuPrcVSleep();
    }
    if (_CheckFlag(0x1000BU) != 0) {
        BoardCameraMotionWait();
        BoardTutorialHookExec(0xB, 0);
    }
    var_r30 = 3;
    if (GWSystem.last5_effect == 1) {
        var_r30 *= 2;
    }
    BoardPlayerPosGet(arg0, &sp8);
    sp8.y += 250.0f;
    temp_r28 = fn_8007FE70(&sp8, -var_r30);
    HuAudFXPlay(0x348);
    BoardCameraMotionWait();
    BoardPlayerMotionShiftSet(arg0, 0xD, 0.0f, 4.0f, 0);
    for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
        BoardPlayerCoinsAdd(arg0, -1);
        HuAudFXPlay(14);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    
    while (fn_80080058(temp_r28) == 0) {
        HuPrcVSleep();
    }
    GWPlayer[arg0].color = 2;
    BoardPlayerMotionEndWait(arg0);
    BoardRotateDiceNumbers(arg0);
}

s8 fn_8007FE70(Point3d* arg0, s8 arg1) {
    omObjData* var_r30 = NULL;
    bitcopy* temp_r31;
    s8 var_r27;
    s8 var_r29;
    
    for (var_r29 = 0; var_r29 < 4; var_r29++) {
        if (lbl_8013A1F0[var_r29] == 0) {
            break;
        }
    }
    if (var_r29 == 4) {
        return -1;
    }
    
    var_r30 = omAddObjEx(boardObjMan, 0x10A, 0, 0, -1, &fn_80080360);
    lbl_8013A1F0[var_r29] = var_r30;
    temp_r31 = (bitcopy *) var_r30->work;
    temp_r31->hide = 0;
    temp_r31->field08_bit2 = 0;
    if (arg1 < 0) {
        var_r27 = 1;
    } else {
        var_r27 = 0;
    }
    temp_r31->field08_bit1 = var_r27;
    temp_r31->field08_bit3 = 0;
    temp_r31->unk_02 = __abs(arg1) / 10;
    temp_r31->unk_03 = __abs(arg1) % 10;
    temp_r31->unk_01 = (s8) (var_r29 + 1);
    temp_r31->unk_04 = 0;
    temp_r31->unk_06 = 0;
    fn_80080124(temp_r31, arg0);
    var_r30->trans.x = arg0->x;
    var_r30->trans.y = arg0->y;
    var_r30->trans.z = arg0->z;
    var_r30->rot.x = 0.0f;
    var_r30->rot.y = 0.01f;
    temp_r31->field08_bit2 = 1;
    return temp_r31->unk_01;
}

s32 fn_80080058(s32 arg0) {
    int *sp8;

    if ((arg0 <= 0) || (arg0 > 4)) {
        return arg0;
    }
    if (lbl_8013A1F0[arg0 - 1] != 0) {
        sp8 = lbl_8013A1F0[arg0 - 1]->work;
        return 0;
    }
    return 1;
}

void fn_800800C4(s32 arg0) {
    bitcopy* temp_r4;

    if ((arg0 <= 0) || (arg0 > 4)) {
        return;
    }
    if (lbl_8013A1F0[arg0 - 1] != 0) {
        ((bitcopy*) lbl_8013A1F0[arg0 - 1]->work)->hide = 1;
    }
}

const s32 lbl_801D56B0[2] = {0x70016, 0x70017};

void fn_80080124(bitcopy* arg0, Vec* arg1) {
    f32 var_f31;

    if (arg0->field08_bit1 != 0) {
        var_f31 = 2.5f;
    } else {
        var_f31 = 1.5f;
    }
    arg0->unk_08 = BoardModelCreate(lbl_801D56B0[arg0->field08_bit1], NULL, 0);
    arg0->unk_0A = BoardModelCreate(lbl_8013A200[arg0->unk_02], NULL, 0);
    arg0->unk_0C = BoardModelCreate(lbl_8013A200[arg0->unk_03], NULL, 0);
    arg0->unk_0E = BoardModelCreate(0x7000A, NULL, 0);
    BoardModelPosSetV(arg0->unk_08, arg1);
    BoardModelPosSetV(arg0->unk_0A, arg1);
    BoardModelPosSetV(arg0->unk_0C, arg1);
    BoardModelPosSetV(arg0->unk_0E, arg1);
    BoardModelMotionStart(arg0->unk_08, 0, 0);
    BoardModelMotionStart(arg0->unk_0A, 0, 0);
    BoardModelMotionStart(arg0->unk_0C, 0, 0);
    BoardModelMotionTimeSet(arg0->unk_08, var_f31);
    BoardModelMotionTimeSet(arg0->unk_0A, var_f31);
    BoardModelMotionTimeSet(arg0->unk_0C, var_f31);
    BoardModelMotionSpeedSet(arg0->unk_08, 0.0f);
    BoardModelMotionSpeedSet(arg0->unk_0A, 0.0f);
    BoardModelMotionSpeedSet(arg0->unk_0C, 0.0f);
    BoardModelScaleSet(arg0->unk_08, 0.001, 0.001, 0.001);
    BoardModelScaleSet(arg0->unk_0A, 0.001, 0.001, 0.001);
    BoardModelScaleSet(arg0->unk_0C, 0.001, 0.001, 0.001);
    BoardModelScaleSet(arg0->unk_0E, 0.001, 0.001, 0.001);
    BoardModelLayerSet(arg0->unk_08, 1);
    BoardModelLayerSet(arg0->unk_0A, 1);
    BoardModelLayerSet(arg0->unk_0C, 1);
    BoardModelLayerSet(arg0->unk_0E, 1);
    if (arg0->unk_02 == 0) {
        BoardModelVisibilitySet(arg0->unk_0A, 0);
    }
}

void fn_80080360(omObjData* arg0) {
    s32 temp_r0;
    bitcopy* temp_r31;

    temp_r31 = (bitcopy*) arg0->work;
    if ((temp_r31->hide != 0) || (BoardIsKill() != 0)) {
        if (temp_r31->unk_0E != -1) {
            BoardModelKill(temp_r31->unk_0E);
            temp_r31->unk_0E = -1;
        }
        if (temp_r31->unk_08 != -1) {
            BoardModelKill(temp_r31->unk_08);
            temp_r31->unk_08 = -1;
        }
        if (temp_r31->unk_0A != -1) {
            BoardModelKill(temp_r31->unk_0A);
            temp_r31->unk_0A = -1;
        }
        if (temp_r31->unk_0C != -1) {
            BoardModelKill(temp_r31->unk_0C);
            temp_r31->unk_0C = -1;
        }
        lbl_8013A1F0[temp_r31->unk_01 - 1] = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    if (temp_r31->field08_bit2 != 0) {
        if (temp_r31->unk_04 != 0) {
            temp_r31->unk_04 -= 1;
            return;
        }
        
        switch (temp_r31->field08_bit3) {
        case 0:
            fn_800804F8(arg0, temp_r31);
            return;
        case 1:
            fn_800806B0(arg0, temp_r31);
            return;
        case 3:
            fn_8008094C(arg0, temp_r31);
            return;
        case 4:
            fn_80080AF4(arg0, temp_r31);
            break;
        }
    }
}

void fn_800804F8(omObjData* arg0, bitcopy* arg1) {
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;

    OSu16tof32(&arg1->unk_06, &temp_f29);
    temp_f29 = sin(M_PI * temp_f29 / 180.0);
    temp_f30 = temp_f29;
    arg0->rot.x = 405.0f * temp_f29;
    BoardModelScaleSet(arg1->unk_0E, temp_f30, temp_f30, temp_f30);
    BoardModelPosSet(arg1->unk_0E, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotYSet(arg1->unk_0E, arg0->rot.x);
    if (arg1->unk_06 < 0x5A) {
        arg1->unk_06 += 6;
        return;
    }
    
    arg1->field08_bit3 = 1;
    arg1->unk_06 = 0;
    BoardModelScaleSet(arg1->unk_08, temp_f30, temp_f30, temp_f30);
    BoardModelPosSet(arg1->unk_08, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotYSet(arg1->unk_08, arg0->rot.x);
    BoardModelScaleSet(arg1->unk_0C, temp_f30, temp_f30, temp_f30);
    BoardModelPosSet(arg1->unk_0C, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotYSet(arg1->unk_0C, arg0->rot.x);
    BoardModelScaleSet(arg1->unk_0A, temp_f30, temp_f30, temp_f30);
    BoardModelPosSet(arg1->unk_0A, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    BoardModelRotYSet(arg1->unk_0A, arg0->rot.x);
}

void fn_800806B0(omObjData* arg0, bitcopy* arg1) {
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f27;
    f32 var_f26;
    f32 var_f25;
    f32 var_f24;

    OSu16tof32(&arg1->unk_06, &temp_f30);
    
    if (arg1->unk_02 != 0) {
        var_f29 = 140.0f;
    } else {
        var_f29 = 105.0f;
    }
    temp_f28 = (200.0 * sin((M_PI * (2.0f * temp_f30)) / 180.0));
    temp_f30 = sin((M_PI * temp_f30) / 180.0);
    arg0->rot.x = 45.0f + (315.0f * temp_f30);
    if (arg1->unk_02 != 0) {
        var_f27 = arg0->trans.x + (temp_f30 * -var_f29);
        var_f24 = arg0->trans.x + ((temp_f30 * -var_f29) / 3.0f);
        var_f26 = arg0->trans.x + (temp_f30 * var_f29);
        var_f25 = arg0->trans.x + ((temp_f30 * var_f29) / 3.0f);
    } else {
        var_f24 = arg0->trans.x;
        var_f25 = arg0->trans.x;
        var_f26 = arg0->trans.x + (temp_f30 * var_f29);
        var_f27 = arg0->trans.x + (temp_f30 * -var_f29);
    }
    BoardModelPosSet(arg1->unk_0E, var_f27, arg0->trans.y + temp_f28, arg0->trans.z);
    BoardModelPosSet(arg1->unk_08, var_f24, arg0->trans.y + temp_f28, arg0->trans.z);
    BoardModelPosSet(arg1->unk_0C, var_f26, arg0->trans.y + temp_f28, arg0->trans.z);
    BoardModelPosSet(arg1->unk_0A, var_f25, arg0->trans.y + temp_f28, arg0->trans.z);
    BoardModelRotYSet(arg1->unk_0E, arg0->rot.x);
    BoardModelRotYSet(arg1->unk_08, arg0->rot.x);
    BoardModelRotYSet(arg1->unk_0C, arg0->rot.x);
    BoardModelRotYSet(arg1->unk_0A, arg0->rot.x);
    if (arg1->unk_06 < 0x5A) {
        arg1->unk_06 += 6;
        return;
    }
    arg0->trans.y += temp_f28;
    arg1->field08_bit3 = 3;
    arg1->unk_06 = 0;
}

void fn_8008094C(omObjData* arg0, bitcopy* arg1) {
    Vec sp8;
    f32 temp_f29;
    f32 var_f30;

    OSu16tof32(&arg1->unk_06, &temp_f29);
    temp_f29 = (f32) sin((M_PI * temp_f29) / 180.0);
    if (arg1->field08_bit1 != 0) {
        var_f30 = (-50.0f * temp_f29) + arg0->trans.y;
    } else {
        var_f30 = (50.0f * temp_f29) + arg0->trans.y;
    }
    BoardModelPosGet(arg1->unk_0E, &sp8);
    BoardModelPosSet(arg1->unk_0E, sp8.x, var_f30, sp8.z);
    BoardModelPosGet(arg1->unk_08, &sp8);
    BoardModelPosSet(arg1->unk_08, sp8.x, var_f30, sp8.z);
    BoardModelPosGet(arg1->unk_0C, &sp8);
    BoardModelPosSet(arg1->unk_0C, sp8.x, var_f30, sp8.z);
    BoardModelPosGet(arg1->unk_0A, &sp8);
    BoardModelPosSet(arg1->unk_0A, sp8.x, var_f30, sp8.z);
    if (arg1->unk_06 < 0x5A) {
        arg1->unk_06 += 6;
        return;
    }
    arg1->field08_bit3 = 4;
    arg1->unk_06 = 0;
    arg1->unk_04 = 0x12;
    arg0->scale.x = 1.0f;
    arg0->scale.y = 1.0f;
}

void fn_80080AF4(omObjData* arg0, bitcopy* arg1) {
    const u16 sp8 = ((arg1->unk_06 * 2) % 180);
    f32 temp_f31;
    
    OSu16tof32(&sp8, &temp_f31);
    if (sp8 <= 90.0f) {
        arg0->scale.x = 0.5 * cos((M_PI * temp_f31) / 180.0);
        arg0->scale.y = 2.5 * sin((M_PI * temp_f31) / 180.0);
    } else {
        arg0->scale.x = 2.5 * sin((M_PI * temp_f31) / 180.0);
        arg0->scale.y = 0.5 * cos((M_PI * temp_f31) / 180.0);
    }
    if (0.0f == arg0->scale.x) {
        arg0->scale.x = 0.0001f;
    }
    if (0.0f == arg0->scale.y) {
        arg0->scale.y = 0.0001f;
    }
    BoardModelScaleSet(arg1->unk_0E, arg0->scale.x, arg0->scale.y, 1.0f);
    BoardModelScaleSet(arg1->unk_08, arg0->scale.x, arg0->scale.y, 1.0f);
    BoardModelScaleSet(arg1->unk_0C, arg0->scale.x, arg0->scale.y, 1.0f);
    BoardModelScaleSet(arg1->unk_0A, arg0->scale.x, arg0->scale.y, 1.0f);
    if (arg1->unk_06 < 0x5A) {
        arg1->unk_06 += 3;
        if (arg1->unk_06 > 0x5A) {
            arg1->unk_06 = 0x5A;
        }
    } else {
        BoardModelVisibilitySet(arg1->unk_08, 0);
        BoardModelVisibilitySet(arg1->unk_0A, 0);
        BoardModelVisibilitySet(arg1->unk_0C, 0);
        BoardModelVisibilitySet(arg1->unk_0E, 0);
        arg1->hide = 1;
    }
}
