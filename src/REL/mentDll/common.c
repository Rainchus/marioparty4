#include "REL/mentDll.h"
#include "game/wipe.h"
#include "game/board/tutorial.h"
#include "math.h"
#include "game/hsfman.h"
#include "game/window.h"

Process* lbl_1_bss_0;

extern s32 _prolog();
extern void _epilog();

void fn_1_144(void);

typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

void fn_1_0(omObjData* arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = NULL;
        omOvlReturnEx(1, 1);
    }
}

void fn_1_4C(omObjData* object) {
    if (omSysExitReq != 0) {
        object->func = fn_1_0;
        WipeCreate(2, 0, -1);
    }
}

s32 _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    fn_1_144();
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}

// void fn_1_144(void) {
//     _ClearFlag(0x1000BU);
//     boardTutorialF = 0;
//     lbl_1_bss_0 = omInitObjMan(0x3E, 0x2000);
//     omGameSysInit(lbl_1_bss_0);
//     lbl_1_bss_A8->unk0 = omovlevtno;
//     lbl_1_bss_A8[1] = omovlstat;
//     fn_1_658C(lbl_1_bss_0);
//     omAddObjEx(lbl_1_bss_0, 0x2000, 0U, 0U, -1, fn_1_4C);
// }

f32 fn_1_20C(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argB <= argA) {
        return arg9;
    }
    return arg8 + ((argA / argB) * (arg9 - arg8));
}

f32 fn_1_234(f32 arg8, f32 arg9, f32 argA) {
    return (arg9 + (arg8 * (argA - 1.0f))) / argA;
}

f32 fn_1_254(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg9;
    }
    return (arg8 + ((arg9 - arg8) * (1.0 - cos((M_PI * ((90.0f / argB) * argA)) / 180.0))));
}

f32 fn_1_32C(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg9;
    }
    return (arg8 + ((arg9 - arg8) * sin((M_PI * ((90.0f / argB) * argA)) / 180.0)));
}

f32 fn_1_3F4(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg8;
    }
    return (arg8 + ((arg9 - arg8) * sin((M_PI * ((360.0f / argB) * argA)) / 180.0)));
}

void fn_1_4B0(s32 arg0) {
    HuPrcSleep(arg0);
}

void fn_1_4D8(void) {
    HuPrcVSleep();
}

void fn_1_4F8(void) {
    while (1) {
        HuPrcVSleep();
    }
}

void fn_1_50C(void) {
    s32 temp_r3 = 0;

    temp_r3 = Hu3DGLightCreate(0.0f, 700.0f, 1200.0f, 0.0f, -1.0f, 0.0f, 255, 255, 255);
    Hu3DGLightPosAimSet(temp_r3, 0.0f, 700.0f, 1200.0f, 0.0f, 0.0f, 640.0f);
    Hu3DGLightInfinitytSet(temp_r3);
}

void fn_1_5E8(s32 arg0) {
    Point3d sp24 = {0.0f, 3000.0f, 800.0f};
    Point3d sp18 = {0.0f, 0.0f, 640.0f};
    Point3d spC = {0.0f, 1.0f, 0.0f};

    if (arg0 == 3) {
        sp24.x = sp18.x = 1200.0f;
    }
    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&sp24, &spC, &sp18);
}

void fn_1_6D0(void) {
    HuWinInit(1);
}

void fn_1_6F4(s16 arg0, s32 arg1, f32 arg8, f32 arg9) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    WindowData* temp_r29;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f18;
    f32 var_f19;
    f32 var_f20;
    f32 var_f21;
    f32 var_f22;
    f32 var_f23;
    f32 var_f30;
    f32 var_f31;
    s32 var_r31;

    sp8 = arg8;
    spC = arg9;
    temp_r29 = &winData[arg0];
    temp_f29 = temp_r29->pos_x;
    temp_f28 = temp_r29->pos_y;
    temp_f25 = (f32) temp_r29->w;
    temp_f24 = (f32) temp_r29->h;
    temp_f31 = temp_f29 + (temp_f25 * sp8);
    temp_f27 = 4.0f / temp_f25;
    if (((4.0f + temp_f31) - (temp_f29 + temp_f25)) >= 0.0f) {
        var_f31 = (temp_f29 + temp_f25) - 4.0f;
    } else {
        if ((temp_f29 - (temp_f31 - 2.0f)) >= 0.0f) {
            var_f31 = temp_f29;
        } else {
            var_f31 = temp_f31 - 2.0f;
        }
    }
    temp_f30 = temp_f28 + (temp_f24 * spC);
    temp_f26 = 4.0f / temp_f24;

    if (((4.0f + temp_f30) - (temp_f28 + temp_f24)) >= 0.0f) {
        var_f30 = (temp_f28 + temp_f24) - 4.0f;
    } else {
        if ((temp_f28 - (temp_f30 - 2.0f)) >= 0.0f) {
            var_f30 = temp_f28;
        } else {
            var_f30 = temp_f30 - 2.0f;
        }
    }
    if (arg1 != 0) {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
        var_f23 = var_f31;
        var_f21 = temp_f27;
        var_f22 = var_f30;
        var_f20 = temp_f26;
    } else {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
        var_f23 = temp_f29;
        var_f21 = 1.0f;
        var_f22 = temp_f28;
        var_f20 = 1.0f;
    }
    HuWinDispOn(arg0);
    for (var_r31 = 0; var_r31 <= 15; var_r31++) {
        HuPrcVSleep();
        if (arg1 != 0) {
            if (var_r31 <= 0xA) {
                if ((f32) var_r31 >= 10.0f) {
                    var_f19 = temp_f29;
                } else {
                    var_f19 = (var_f31 + ((temp_f29 - var_f31) * sin((M_PI * (9.0f * (f32) var_r31)) / 180.0)));
                }
                var_f23 = var_f19;
                if ((f32) var_r31 >= 10.0f) {
                    var_f18 = 1.0f;
                } else {
                    var_f18 = (temp_f27 + ((1.0f - temp_f27) * sin((M_PI * (9.0f * (f32) var_r31)) / 180.0)));
                }
                var_f21 = var_f18;
            } else {
                if ((f32) (var_r31 - 0xA) >= 5.0f) {
                    sp24 = temp_f28;
                } else {
                    sp24 = (var_f30 + ((temp_f28 - var_f30) * sin((M_PI * (18.0f * (f32) (var_r31 - 0xA))) / 180.0)));
                }
                var_f22 = sp24;
                if ((f32) (var_r31 - 0xA) >= 5.0f) {
                    sp20 = 1.0f;
                } else {
                    sp20 = (temp_f26 + ((1.0f - temp_f26) * sin((M_PI * (18.0f * (f32) (var_r31 - 0xA))) / 180.0)));
                }
                var_f20 = sp20;
            }
        } else if (var_r31 <= 0xA) {
            if ((f32) var_r31 >= 10.0f) {
                sp1C = var_f30;
            } else {
                sp1C = (temp_f28 + ((var_f30 - temp_f28) * sin((M_PI * (9.0f * var_r31)) / 180.0)));
            }
            var_f22 = sp1C;
            if ((f32) var_r31 >= 10.0f) {
                sp18 = temp_f26;
            } else {
                sp18 = (f32) (1.0 + ((temp_f26 - 1.0f) * sin((M_PI * (9.0f * var_r31)) / 180.0)));
            }
            var_f20 = sp18;
        } else {
            if ((f32) (var_r31 - 0xA) >= 5.0f) {
                sp14 = var_f31;
            } else {
                sp14 = (temp_f29 + ((var_f31 - temp_f29) * sin((M_PI * (18.0f * (var_r31 - 0xA))) / 180.0)));
            }
            var_f23 = sp14;
            if ((f32) (var_r31 - 0xA)>= 5.0f) {
                sp10 = temp_f27;
            } else {
                sp10 = (1.0 + ((temp_f27 - 1.0f) * sin((M_PI * (18.0f * (var_r31 - 0xA))) / 180.0)));
            }
            var_f21 = sp10;
        }
        HuWinPosSet(arg0, var_f23, var_f22);
        HuWinScaleSet(arg0, var_f21, var_f20);
    }
    if (arg1 != 0) {
        HuWinPosSet(arg0, temp_f29, temp_f28);
        HuWinScaleSet(arg0, 1.0f, 1.0f);
    } else {
        HuWinPosSet(arg0, var_f31, var_f30);
        HuWinScaleSet(arg0, temp_f27, temp_f26);
    }
    HuPrcVSleep();
}