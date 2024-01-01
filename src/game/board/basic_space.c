#include "common.h"
#include "game/process.h"
#include "game/audio.h"

void BoardCameraViewSet(s32);                            /* extern */
void fn_8006310C(s32, Vec*);                             /* extern */
void fn_800638C4(s32);                         /* extern */
void fn_80063A1C(s32, s32, f32, f32, s32);                 /* extern */
void fn_80063EEC(s32, s32);                              /* extern */
void fn_80067B98(s32);                                 /* extern */
void fn_80067C90(s32, s16, s16);                           /* extern */
s32 fn_8006874C(s32);                               /* extern */
s8 fn_8007FE70(Point3d*, s8);                        /* extern */
s32 fn_80080058(s32);                                /* extern */
void fn_800B3FE0(s16, s32);                                /* extern */
void omVibrate(s16, s16, s16, s16);

void BoardEventLandBlue(s32 arg0) {
    Point3d sp8;
    f32 temp_f1;
    s32 var_r29;
    s8 temp_r28;
    s32 var_r30;

    BoardCameraViewSet(2);
    fn_80067C90(arg0, 0, 0xF);
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    if (_CheckFlag(0x1000BU) != 0) {
        BoardCameraMotionWait();
        fn_800B3FE0(0xA, 0);
    }
    var_r30 = 3;
    if (GWSystem.last5_effect == 1) {
        var_r30 *= 2;
    }
    fn_8006310C(arg0, &sp8);
    sp8.y += 250.0f;
    temp_r28 = fn_8007FE70(&sp8, var_r30);
    HuAudFXPlay(0x347);
    BoardCameraMotionWait();
    fn_80063A1C(arg0, 0xC, 0.0f, 4.0f, 0);
    
    for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
        fn_80063EEC(arg0, 1);
        HuAudFXPlay(7);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    while (fn_80080058(temp_r28) == 0) {
        HuPrcVSleep();
    }
    GWPlayer[arg0].color = 1;
    fn_800638C4(arg0);
    fn_80067B98(arg0);
}

void BoardEventLandRed(s32 arg0) {
    Point3d sp8;
    s32 var_r29;
    s8 temp_r28;
    s32 var_r30;
    void* temp_r3;

    BoardCameraViewSet(2);
    omVibrate(arg0, 0xC, 6, 6);
    fn_80067C90(arg0, 0, 0xF);
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    if (_CheckFlag(0x1000BU) != 0) {
        BoardCameraMotionWait();
        fn_800B3FE0(0xB, 0);
    }
    var_r30 = 3;
    if (GWSystem.last5_effect == 1) {
        var_r30 *= 2;
    }
    fn_8006310C(arg0, &sp8);
    sp8.y += 250.0f;
    temp_r28 = fn_8007FE70(&sp8, -var_r30);
    HuAudFXPlay(0x348);
    BoardCameraMotionWait();
    fn_80063A1C(arg0, 0xD, 0.0f, 4.0f, 0);
    for (var_r29 = 0; var_r29 < var_r30; var_r29++) {
        fn_80063EEC(arg0, -1);
        HuAudFXPlay(14);
        HuPrcSleep(6);
    }
    HuAudFXPlay(0xF);
    
    while (fn_80080058(temp_r28) == 0) {
        HuPrcVSleep();
    }
    GWPlayer[arg0].color = 2;
    fn_800638C4(arg0);
    fn_80067B98(arg0);
}
