#include "math.h"
#include "ext_math.h"
#include "game/object.h"
#include "game/window.h"
#include "game/hsfman.h"
#include "game/process.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/board/tutorial.h"

Process* lbl_1_bss_0;

//TODO: unknown type
extern s32 lbl_1_bss_A8[];

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

void fn_1_144(void) {
    _ClearFlag(0x1000BU);
    boardTutorialF = 0;
    lbl_1_bss_0 = omInitObjMan(0x3E, 0x2000);
    omGameSysInit(lbl_1_bss_0);
    lbl_1_bss_A8[0] = omovlevtno;
    lbl_1_bss_A8[1] = omovlstat;
    fn_1_658C(lbl_1_bss_0);
    omAddObjEx(lbl_1_bss_0, 0x2000, 0U, 0U, -1, fn_1_4C);
}

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

void fn_1_6F4(s32 window, f32 centerX, f32 centerY, s32 toSmallF)
{
    WindowData* winPtr;
    f32 smallPosX;
    f32 smallPosY;
    f32 winPosX; 
    f32 winPosY;
    f32 width;
    f32 height;
    f32 smallScaleX;
    f32 smallScaleY;
    f32 posX;
    f32 posY;
    f32 scaleX;
    f32 scaleY;
    s32 time;

    winPtr = (WindowData *)&winData[window];
    winPosX = winPtr->pos_x;
    winPosY = winPtr->pos_y;
    width = winPtr->w;
    height = winPtr->h;
    smallPosX = winPosX + (width * centerX);
    smallScaleX = 4.0f / width;

    // adjust horizontal position
    if (((4.0f + smallPosX) - (winPosX + width)) >= 0.0f) {
        smallPosX = (winPosX + width) - 4.0f;
    } else {
        if ((winPosX - (smallPosX - 2.0f)) >= 0.0f) {
            smallPosX = winPosX;
        } else {
            smallPosX = smallPosX - 2.0f;
        }
    }

    smallPosY = winPosY + (height * centerY);
    smallScaleY = 4.0f / height;

    // adjust vertical position
    if (((4.0f + smallPosY) - (winPosY + height)) >= 0.0f) {
        smallPosY = (winPosY + height) - 4.0f;
    } else {
        if ((winPosY - (smallPosY - 2.0f)) >= 0.0f) {
            smallPosY = winPosY;
        } else {
            smallPosY = smallPosY - 2.0f;
        }
    }

    if (toSmallF != 0) {
        HuWinPosSet(window, smallPosX, smallPosY);
        HuWinScaleSet(window, smallScaleX, smallScaleY);
        posX = smallPosX;
        scaleX = smallScaleX;
        posY = smallPosY;
        scaleY = smallScaleY;
    } else {
        HuWinPosSet(window, winPosX, winPosY);
        HuWinScaleSet(window, 1.0f, 1.0f);
        posX = winPosX;
        scaleX = 1.0f;
        posY = winPosY;
        scaleY = 1.0f;
    }
    HuWinDispOn(window);

    // animation loop
    for (time = 0; time <= 15; ++time) {
        HuPrcVSleep();
        if (toSmallF != 0) {
            if (time <= 0xA) {
                posX = (time >= 10.0f) ? winPosX : (f32)(smallPosX + ((winPosX - smallPosX) * sind(9.0f * time)));
                scaleX = (time >= 10.0f) ? 1.0f : (f32)(smallScaleX + ((1.0f - smallScaleX) * sind(9.0f * time)));
            } else {
                posY = ((time - 0xA) >= 5.0f) ? winPosY : (f32)(smallPosY + ((winPosY - smallPosY) * sind(18.0f * (time - 0xA))));
                scaleY = ((time - 0xA) >= 5.0f) ? 1.0f : (f32)(smallScaleY + ((1.0f - smallScaleY) * sind(18.0f * (time - 0xA))));
            }
        } else if (time <= 0xA) {
            posY  = (time >= 10.0f) ? smallPosY : (f32)(winPosY + ((smallPosY - winPosY) * sind(9.0f * time)));
            scaleY  = (time >= 10.0f) ? smallScaleY : (f32)(1.0 + ((smallScaleY - 1.0f) * sind(9.0f * time)));
        } else {
            posX = ((time - 0xA) >= 5.0f) ? smallPosX : (f32)(winPosX + ((smallPosX - winPosX) * sind(18.0f * (time - 0xA))));
            scaleX = ((time - 0xA) >= 5.0f) ? smallScaleX : (f32)(1.0 + ((smallScaleX - 1.0f) * sind(18.0f * (time - 0xA))));
        }
        HuWinPosSet(window, posX, posY);
        HuWinScaleSet(window, scaleX, scaleY);
    }

    if (toSmallF != 0) {
        HuWinPosSet(window, winPosX, winPosY);
        HuWinScaleSet(window, 1.0f, 1.0f);
    } else {
        HuWinPosSet(window, smallPosX, smallPosY);
        HuWinScaleSet(window, smallScaleX, smallScaleY);
    }
    HuPrcVSleep();
}

s32 fn_1_113C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg8, f32 arg9, s32 arg6, s32 arg4, s32 arg5) {
    f32 sp14[2];
    s32 temp_r30;

    if (arg6 % 2 == 0) {
        arg2 = (arg2 * 0x15) + 0x10;
        arg3 = (arg3 * 0x1A) + 0x10;
        arg1 = (445.0f - arg3);
        switch (arg0) {           
        case -1:
            arg0 = 0x10;
            break;
        case 0:
            arg0 = (1.0f + ((576.0f - arg2) / 2));
            break;
        case 1:
            arg0 = (556.0f - arg2);
            break;
        }
    } else {
        HuWinMesMaxSizeGet(1, sp14, arg5);
        arg2 = sp14[0];
        arg3 = sp14[1];
        arg0 = (556.0f - arg2);
        arg1 = (445.0f - arg3);
    }
    temp_r30 = HuWinExCreateStyled(arg0, arg1, arg2, arg3, -1, 1);
    if (arg6 == 1) {
        HuWinAttrSet(temp_r30, 0x10U);
    }
    HuWinMesPalSet(temp_r30, 7U, 0U, 0U, 0U);
    winData[temp_r30].active_pad = 1;
    fn_1_6F4(temp_r30, arg8, arg9, 1);
    return temp_r30;
}

s32 fn_1_1434(s32 arg0) {
    return fn_1_113C(arg0, 0, 0x15, 2, 0.5f, 0.5f, 2, 0, 0);
}

void fn_1_164C(s32 arg0, f32 arg8, f32 arg9) {
    HuWinMesSet(arg0, 0x250004);
    HuPrcVSleep();
    fn_1_6F4(arg0, arg8, arg9, 0);
    HuWinExCleanup(arg0);
}

void fn_1_16AC(s32 arg0) {
    HuWinMesSet(arg0, 0x250004);
    HuPrcVSleep();
    fn_1_6F4(arg0, 0, 0.5f, 0.5f);
    HuWinExCleanup(arg0);
}

void fn_1_1714(s32 arg0, s32 arg1) {
    if ((arg1 == -999) || (arg1 == 0)) {
        return;
    }
    if (arg1 == -1000) {
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) == 1);
        return;
    }
    if (arg1 > 0) {
        HuPrcSleep(arg1);
        return;
    }
    HuWinComKeyReset();
    HuWinMesWait(arg0);
    HuWinComKeyReset();
}

void fn_1_17A4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 temp_r28 = 0;
    s32 var_r30 = 0;

    (void)arg0;
    
    temp_r28 = HuWinKeyWaitNumGet(arg1);
    if ((arg2 == -1) || (arg2 >= (s32) (temp_r28 - 1))) {
        arg2 = temp_r28 - 1;
    }
    HuWinComKeyReset();
    for (i = 0; i < temp_r28; i++) {
        var_r30 = 0;
        do {
            HuPrcVSleep();
        } while (HuWinStatGet(arg0) != 1);
        
        if (i == arg2) {
            HuWinAttrSet(arg0, 0x400);
            var_r30 = 1;
        }
        
        while (1) {
            HuPrcVSleep();
            if (var_r30 != 0) {
                if (var_r30 == 1 && HuWinStatGet(arg0) != 1) {
                    var_r30 = 2;
                } else if (var_r30 == 2) {
                    HuPrcSleep(arg3);
                    HuWinAttrReset(arg0, 0x400);
                    HuWinKeyWaitEntry(arg0);
                    break;
                }
            } else if (HuWinStatGet(arg0) != 1) {
                break;
            }
        }
    }
    HuWinComKeyReset();
    HuWinMesWait(arg0);
    HuWinComKeyReset();
    HuWinComKeyReset();
}

s32 fn_1_18D8(s32 arg0, s32 arg1) {
    s32 temp_r31;

    HuWinComKeyReset();
    temp_r31 = HuWinChoiceGet(arg0, arg1);
    HuWinComKeyReset();
    return temp_r31;
}

void fn_1_1928(s32 arg0, s32 arg1, s32 arg2) {
    HuWinInsertMesSet(arg0, arg1, arg2);
}

void fn_1_1968(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg3 == -999) {
        HuWinMesSpeedSet(arg0, 0);
    } else {
        HuWinMesSpeedSet(arg0, 1);
    }
    HuWinMesSet(arg0, arg1);
    if (arg2 == -1) {
        if ((arg3 != -999) && (arg3 != 0)) {
            if (arg3 == -1000) {
                do {
                    HuPrcVSleep();
                } while (HuWinStatGet(arg0) == 1);
                return;
            }
            if (arg3 > 0) {
                HuPrcSleep(arg3);
                return;
            }
            HuWinComKeyReset();
            HuWinMesWait(arg0);
            HuWinComKeyReset();
        }
    } else {
        fn_1_17A4(arg0, arg1, arg2, arg3);
    }
}

s32 fn_1_1A5C(s32 arg0, s32 arg1) {
    s32 var_r28;
    s32 var_r25 = 0;

    var_r28 = fn_1_113C(0, 0, 0, 0, 0.5f, 0.5f, arg1, 0, arg0);
    HuWinMesSet(var_r28, arg0);
    var_r25 = fn_1_18D8(var_r28, 0);
    fn_1_164C(var_r28, 0.5f, 0.5f);
    return var_r25;
}