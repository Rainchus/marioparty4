#include "math.h"
#include "ext_math.h"
#include "game/object.h"
#include "game/window.h"
#include "game/hsfman.h"
#include "game/process.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/board/tutorial.h"
#include "game/pad.h"
#include "REL/mentDll.h"
#include "game/printfunc.h"
#include "game/hsfmotion.h"

Process* lbl_1_bss_0;
//TODO: unknown type
extern s32 lbl_1_bss_A8[];

s32 lbl_1_data_0[][4] = {
    { 0x00000037, 0x00000038, 0x00000036, 0x00000039 },
    { 0x00000043, 0x00000045, 0x00000044, 0x00000043 },
    { 0x00000040, 0x00000042, 0x00000041, 0x00000040 },
    { 0x0000004B, 0x0000004D, 0x0000004C, 0x0000004B },
    { 0x00000046, 0x00000048, 0x00000047, 0x00000046 },
    { 0x0000003E, 0x0000003F, 0x0000003E, 0x0000003E },
    { 0x0000003A, 0x0000003B, 0x0000003C, 0xFFFFFFFF },
};

s32 lbl_1_data_70 = -1;

// char lbl_1_data_74[] = ">>>>>>>>>> CAMERA DATA <<<<<<<<<<";
// char lbl_1_data_96[] = "CENTER : %.2f, %.2f, %.2f";
// char lbl_1_data_B0[] = "ROT    : %.2f, %.2f, %.2f";
// char lbl_1_data_CA[] = "ZOOM   : %.2f";

extern s32 _prolog();
extern void _epilog();
void fn_1_144(void);
void fn_1_2318(s32);
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

//fn_1_254
f32 CosineEaseInOut(f32 arg8, f32 arg9, f32 argA, f32 argB) {
    if (argA >= argB) {
        return arg9;
    }
    return (arg8 + ((arg9 - arg8) * (1.0 - cos((M_PI * ((90.0f / argB) * argA)) / 180.0))));
}

//fn_1_32C
f32 SinusoidalInterpolation(f32 arg8, f32 arg9, f32 argA, f32 argB) {
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

s32 fn_1_1434(s32 arg0, s32 arg1, s32 arg2) {
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

s32 fn_1_1A5C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r28;
    s32 var_r25 = 0;

    var_r28 = fn_1_113C(0, 0, 0, 0, 0.5f, 0.5f, arg1, 0, arg0);
    HuWinMesSet(var_r28, arg0);
    var_r25 = fn_1_18D8(var_r28, 0);
    fn_1_164C(var_r28, 0.5f, 0.5f);
    return var_r25;
}

s32 fn_1_1DD8(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_r28;
    s32 var_r25 = 0;
    
    var_r28 = fn_1_113C(0, 0, 0, 0, 0.5f, 0.5f, arg1, 0, arg0);
    HuWinMesSet(var_r28, arg0);
    var_r25 = fn_1_18D8(var_r28, 1);
    fn_1_164C(var_r28, 0.5f, 0.5f);
    return var_r25;
}

s32 fn_1_2154(s32 arg0) {
    f32 sp8[2];
    f32 temp_f29;
    f32 temp_f28;
    s32 ret;
    f32 sizeX;
    f32 sizeY;

    HuWinMesMaxSizeGet(1, sp8, arg0);
    sizeX = sp8[0];
    sizeY = sp8[1];
    temp_f29 = (576.0f - sizeX) / 2;
    temp_f28 = 385.0f - sizeY;
    if (lbl_1_data_70 == -1) {
        lbl_1_data_70 = ret = HuWinExCreateStyled(temp_f29, temp_f28, sizeX, sizeY, -1, 1);
    } else {
        fn_1_2318(0);
        lbl_1_data_70 = ret = HuWinExCreateStyled(temp_f29, temp_f28, sizeX, sizeY, -1, 1);
    }
    HuWinBGTPLvlSet(lbl_1_data_70, 0.0f);
    HuWinMesSet(lbl_1_data_70, arg0);
    HuWinMesSpeedSet(lbl_1_data_70, 0);
    HuWinDispOn(lbl_1_data_70);
    return lbl_1_data_70;
}

void fn_1_2318(s32 arg0) {
    if (lbl_1_data_70 != -1) {
        HuWinExCleanup(lbl_1_data_70);
        lbl_1_data_70 = -1;
    }
}

void fn_1_236C(f32 arg9) {
    MentDllUnkBss64Struct* temp = &lbl_1_bss_64;

    if ((HuPadBtn[0] & 0x200)) {
        if ((HuPadBtn[0] & 0x20)) {
            temp->center.z = temp->center.z - (HuPadStkY[0] / 10.0f);
        } else {
            temp->center.x += HuPadStkX[0] / 10.0f;
            temp->center.y = temp->center.y + (HuPadStkY[0] / 10.0f);
        }
    }
    if ((HuPadBtn[0] & 0x800)) {
        temp->rot.x -= HuPadStkY[0] / 100.0f;
        temp->rot.y = temp->rot.y + (HuPadStkX[0] / 100.0f);
        if (temp->rot.x < 0.0f) {
            temp->rot.x += 360.0f;
        }

        if (temp->rot.x >= 360.0f) {
            temp->rot.x -= 360.0f;
        }
        if (temp->rot.y < 0.0f) {
            temp->rot.y += 360.0f;
        }
        if (temp->rot.y >= 360.0f) {
            temp->rot.y -= 360.0f;
        }
    }
    if ((HuPadBtn[0] & 0x400)) {
        temp->zoom = temp->zoom - (HuPadStkY[0] / 10.0f);
    }
    print8(0x18, 0x28, 1.0f, ">>>>>>>>>> CAMERA DATA <<<<<<<<<<");
    print8(0x18, 0x32, 1.0f, "CENTER : %.2f, %.2f, %.2f", temp->center.x, temp->center.y, temp->center.z);
    print8(0x18, 0x3C, 1.0f, "ROT    : %.2f, %.2f, %.2f", temp->rot.x, temp->rot.y, temp->rot.z);
    print8(0x18, 0x46, 1.0f, "ZOOM   : %.2f", temp->zoom);
}

void fn_1_2750(omObjData* obj) {
    MentDllUnkBss64Struct* temp = &lbl_1_bss_64;
    if (temp->func != NULL) {
        temp->func();
    }
    Center.x = temp->center.x;
    Center.y = temp->center.y;
    Center.z = temp->center.z;
    CRot.x = temp->rot.x;
    CRot.y = temp->rot.y;
    CRot.z = temp->rot.z;
    CZoom = temp->zoom;
}

void fn_1_2808(void (*arg0)(void)) {
    fn_1_29A0(&lbl_1_bss_64);
    lbl_1_bss_64.func = arg0;
}

void fn_1_2844(Process* arg0, void (*arg1)(void)) {
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 42.0f, 20.0f, 5000.0f, 1.2f);
    lbl_1_bss_64.func = arg1;
    lbl_1_bss_64.func2 = &fn_1_236C;
    omAddObjEx(arg0, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(arg0, 0x7FD9, 0U, 0U, -1, fn_1_2750);
}

void fn_1_2964(MentDllUnkBss64Struct* arg0) {
    arg0->center.x = arg0->prevCenter.x;
    arg0->center.y = arg0->prevCenter.y;
    arg0->center.z = arg0->prevCenter.z;
    arg0->rot.x = arg0->prevRot.x;
    arg0->rot.y = arg0->prevRot.y;
    arg0->rot.z = arg0->prevRot.z;
    arg0->zoom = arg0->prevZoom;
}

void fn_1_29A0(MentDllUnkBss64Struct* arg0) {
    arg0->unk_40 = 0.0f;
    arg0->prevCenter.x = arg0->center.x;
    arg0->prevCenter.y = arg0->center.y;
    arg0->prevCenter.z = arg0->center.z;
    arg0->prevRot.x = arg0->rot.x;
    arg0->prevRot.y = arg0->rot.y;
    arg0->prevRot.z = arg0->rot.z;
    arg0->prevZoom = arg0->zoom;
}

static inline f32 SmoothInterpolate(f32 arg0, f32 arg1, f32 arg2) {
    return (arg1 + arg0 * (arg2 - 1.0f)) / arg2;
}

void fn_1_29E4(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8) {    
    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, arg8);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, arg8);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, arg8);
    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, arg8);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, arg8);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, arg8);
    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, arg8);
}

void fn_1_2C50(MentDllUnkBss64Struct* arg0, f32 arg8) {    
    arg0->center.x = SmoothInterpolate(arg0->center.x, arg0->prevCenter.x, arg8);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg0->prevCenter.y, arg8);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg0->prevCenter.z, arg8);
    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg0->prevRot.x, arg8);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg0->prevRot.y, arg8);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg0->prevRot.z, arg8);
    arg0->zoom = SmoothInterpolate(arg0->zoom, arg0->prevZoom, arg8);
}

inline f32 LinearInterpolation(f32 arg0, f32 arg1, f32 arg8, f32 arg9)  {
    if (arg9 <= arg8) {
        return arg1;
    } else {
        return arg0 + ((arg8 / arg9) * (arg1 - arg0));
    }
}

void fn_1_2EBC(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_3138(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;
    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;
    arg0->zoom = arg1->prevZoom;
}

void fn_1_33EC(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9, f32 argA) {
    arg1->prevCenter.x = LinearInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = LinearInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = LinearInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = LinearInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = LinearInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = LinearInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = LinearInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, argA);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, argA);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, argA);

    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, argA);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, argA);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, argA);

    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, argA);
}

void fn_1_3858(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = SinusoidalInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = SinusoidalInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = SinusoidalInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = SinusoidalInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = SinusoidalInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = SinusoidalInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = SinusoidalInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_3CAC(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = SinusoidalInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = SinusoidalInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = SinusoidalInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = SinusoidalInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = SinusoidalInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = SinusoidalInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = SinusoidalInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;
    
    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;
    
    arg0->zoom = arg1->prevZoom;
}

void fn_1_4138(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9, f32 argA) {
    arg1->prevCenter.x = SinusoidalInterpolation(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = SinusoidalInterpolation(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = SinusoidalInterpolation(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = SinusoidalInterpolation(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = SinusoidalInterpolation(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = SinusoidalInterpolation(arg0->prevRot.z, arg1->rot.z, arg8, arg9);
    
    arg1->prevZoom = SinusoidalInterpolation(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, argA);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, argA);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, argA);

    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, argA);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, argA);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, argA);

    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, argA);
}

void fn_1_4790(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = CosineEaseInOut(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = CosineEaseInOut(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = CosineEaseInOut(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = CosineEaseInOut(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = CosineEaseInOut(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = CosineEaseInOut(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = CosineEaseInOut(arg0->prevZoom, arg1->zoom, arg8, arg9);
}

void fn_1_4C54(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9) {
    arg1->prevCenter.x = CosineEaseInOut(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = CosineEaseInOut(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = CosineEaseInOut(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = CosineEaseInOut(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = CosineEaseInOut(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = CosineEaseInOut(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = CosineEaseInOut(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = arg1->prevCenter.x;
    arg0->center.y = arg1->prevCenter.y;
    arg0->center.z = arg1->prevCenter.z;
    
    arg0->rot.x = arg1->prevRot.x;
    arg0->rot.y = arg1->prevRot.y;
    arg0->rot.z = arg1->prevRot.z;
    
    arg0->zoom = arg1->prevZoom;
}

void fn_1_5150(MentDllUnkBss64Struct* arg0, MentDllUnkBss64Struct* arg1, f32 arg8, f32 arg9, f32 argA) {
    arg1->prevCenter.x = CosineEaseInOut(arg0->prevCenter.x, arg1->center.x, arg8, arg9);
    arg1->prevCenter.y = CosineEaseInOut(arg0->prevCenter.y, arg1->center.y, arg8, arg9);
    arg1->prevCenter.z = CosineEaseInOut(arg0->prevCenter.z, arg1->center.z, arg8, arg9);

    arg1->prevRot.x = CosineEaseInOut(arg0->prevRot.x, arg1->rot.x, arg8, arg9);
    arg1->prevRot.y = CosineEaseInOut(arg0->prevRot.y, arg1->rot.y, arg8, arg9);
    arg1->prevRot.z = CosineEaseInOut(arg0->prevRot.z, arg1->rot.z, arg8, arg9);

    arg1->prevZoom = CosineEaseInOut(arg0->prevZoom, arg1->zoom, arg8, arg9);

    arg0->center.x = SmoothInterpolate(arg0->center.x, arg1->prevCenter.x, argA);
    arg0->center.y = SmoothInterpolate(arg0->center.y, arg1->prevCenter.y, argA);
    arg0->center.z = SmoothInterpolate(arg0->center.z, arg1->prevCenter.z, argA);

    arg0->rot.x = SmoothInterpolate(arg0->rot.x, arg1->prevRot.x, argA);
    arg0->rot.y = SmoothInterpolate(arg0->rot.y, arg1->prevRot.y, argA);
    arg0->rot.z = SmoothInterpolate(arg0->rot.z, arg1->prevRot.z, argA);

    arg0->zoom = SmoothInterpolate(arg0->zoom, arg1->prevZoom, argA);
}

void fn_1_5818(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg4) {
    case 0:
        Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0);
        break;
    case 1:
        Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000001);
        break;
    case 2:
        Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000002);
        break;
    }
    arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
}

void fn_1_59A0(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg0->work[3] != arg0->motion[arg2]) {
        arg0->work[3] = arg0->motion[arg2];
        switch (arg4) {
        case 0:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0);
            break;
        case 1:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000001);
            break;
        case 2:
            Hu3DMotionShiftSet(arg0->model[arg1], arg0->motion[arg2], 0.0f, arg3, 0x40000002);
            break;
        }
        arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    }
}

void fn_1_5B50(omObjData* arg0, s32 arg1, s32 arg2, s32 arg3) {
    (void)arg1;
    Hu3DMotionShiftSet(arg0->model[1], arg0->motion[arg1], 0.0f, arg3, 0);
    arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
    arg0->work[0] = 1;
    arg0->work[1] = arg2;
    arg0->work[2] = arg3 + 1;
}

void fn_1_5C08(omObjData* arg0) {
    s32 temp;
    
    if (arg0->work[0] != 0) {
        if (arg0->work[2] != 0) {
            arg0->work[2] -= 1;
            return;
        }
        if ((arg0->work[2] == 0) && (Hu3DMotionEndCheck(arg0->model[1]) != 0)) {
            temp = arg0->work[1];
            Hu3DMotionShiftSet(arg0->model[1], arg0->motion[temp], 0.0f, 15.0f, 0x40000001);
            arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
            arg0->work[0] = arg0->work[1] = arg0->work[2] = 0;
        }
    }
}

void fn_1_5CDC(omObjData* arg0, s32 arg1, s32 arg2) {
    HuPrcSleep(arg2 + 1);
    do {
        HuPrcVSleep();
    } while (Hu3DMotionEndCheck(arg0->model[arg1]) == 0);
}