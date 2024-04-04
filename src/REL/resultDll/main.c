// include "REL/resultDll/main.h"
#include "dolphin.h"
#include "rel_sqrt_consts.h"
#include "game/gamework_data.h"
#include "game/gamework.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/armem.h"
#include "game/animdata.h"
#include "game/hsfman.h"
#include "game/object.h"
#include "game/audio.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/flag.h"
#include "game/wipe.h"
#include "game/objsub.h"
#include "game/pad.h"
// #include "game/frand.h"
#include "game/board/player.h"
// #include "REL/resultDll/battle.h"
extern s16 lbl_1_bss_1A1A[0x21];
extern s16 lbl_1_bss_1A9C[0x20];

// structs
typedef struct unkStructData0 {
  u32 unk0;
  u32 unk4;
  s16 unk8;
  s16 unkA;
  s16 unkC;
  s16 unkE;
  Vec unk10;
  Vec unk1C;
  Vec unk28;
} unkStructData0;
typedef struct unkStructData2A4 {
  u32 unk0;
  u32 unk4;
  f32 unk8;
  f32 unkC;
  s32 unk10;
} unkStructData2A4;
typedef struct unkStructBSS12 {
  s16 unk0;
  s16 unk2;
  s16 unk4;
  s16 unk6;
  s16 unk8;
} unkStructBSS12;

// bss
omObjData* lbl_1_bss_184[2];
Process* lbl_1_bss_180;
s16 lbl_1_bss_17C;
s32 lbl_1_bss_178;
s32 lbl_1_bss_174;
s16 lbl_1_bss_172;
s16 lbl_1_bss_170;
s16 lbl_1_bss_168[4];
s16 lbl_1_bss_158[8];
AnimData* lbl_1_bss_144[5];
AnimData* lbl_1_bss_E4[8][3];
AnimData* lbl_1_bss_E0;
s16 lbl_1_bss_CE[9];
S16Vec lbl_1_bss_9E[8];
s16 lbl_1_bss_9C;
s16 lbl_1_bss_5C[8][4];
// extern ? lbl_1_bss_54;
s16 lbl_1_bss_52;
s16 lbl_1_bss_4A[4];
s16 lbl_1_bss_42[4];
s16 lbl_1_bss_3A[4];
unkStructBSS12 lbl_1_bss_12[4];
// extern ? lbl_1_bss_A;
// extern s16 lbl_1_bss_8;
s32 lbl_1_bss_4;
s32 lbl_1_bss_0;

// data
unkStructData0 lbl_1_data_0[13] = {
    {   0x6F0000, 1, 0, -1, -1, 0,
        { 148.0f, 132.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0001, 1, 0, -1, -1, 0,
        { 148.0f, 217.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0002, 1, 0, -1, -1, 0,
        { 148.0f, 302.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0003, 1, 0, -1, -1, 0,
        { 148.0f, 387.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 0, -1, -1, 0,
        { 230.0f, 132.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 4, -1, 0,
        { 230.0f, 217.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 4, -1, 0,
        { 230.0f, 302.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 4, -1, 0,
        { 230.0f, 387.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0005, 0, 0, -1, -1, 0,
        { 410.0f, 132.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 8, -1, 0,
        { 410.0f, 217.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 8, -1, 0,
        { 410.0f, 302.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   0x6F0006, 0, 2, 8, -1, 0,
        { 410.0f, 387.0f, 500.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
    {   -1,       0, 0, -1, -1, 0,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 1.0f, 1.0f, 1.0f } },
};
unkStructData2A4 lbl_1_data_2A4[11] = {
    { 0x6F0043, 10, 288.0f, 240.0f, -1 },
    { 0x6F001D, 10, 288.0f, 60.0f,  -1 },
    { 0x6F001A, 10, 270.0f, 132.0f, -1 },
    { 0x6F001A, 10, 450.0f, 132.0f, -1 },
    { 0x6F001A, 10, 270.0f, 217.0f, -1 },
    { 0x6F001A, 10, 450.0f, 217.0f, -1 },
    { 0x6F001A, 10, 270.0f, 302.0f, -1 },
    { 0x6F001A, 10, 450.0f, 302.0f, -1 },
    { 0x6F001A, 10, 270.0f, 387.0f, -1 },
    { 0x6F001A, 10, 450.0f, 387.0f, -1 },
    { 0,        0,  0.0f,   0.0f,    0 },
};
s16 lbl_1_data_380 = -1;

// rodata
// extern s32 saveExecF;

// functions
void fn_1_6490(void);
void fn_1_8FF8(unkStructData0*);
void fn_1_927C(unkStructData2A4*);
void fn_1_1F4C(void);
void fn_1_2ADC(void);
void fn_1_3B50(s16 arg0, s16 arg1);
void fn_1_3CAC(s16 arg0, s16 arg1);
void fn_1_3E08(void);
void fn_1_3FD8(void);
void fn_1_40DC(void);
void fn_1_423C(s16 (*arg0)[]);
void fn_1_461C(void);
void fn_1_47FC(void);
void fn_1_4D8(void);
void fn_1_888(void);
void fn_1_B78(void);

void ModuleProlog(void) {
    s32 var_r31;
    s32 var_r30;

    OSReport("******* RESULT ObjectSetup *********\n");
    lbl_1_bss_180 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_17C = GWSystem.mg_next;
    if (mgInfoTbl[lbl_1_bss_17C].ovl == 0x26) {
        for (var_r31 = 0; var_r31 < 4; var_r31++) {
            GWPlayerCfg[var_r31].group = GWPlayerCfg[var_r31].group / 2;
        }
    }
    HuDataDirClose(mgInfoTbl[lbl_1_bss_17C].data_dir);
    if (mgInfoTbl[lbl_1_bss_17C].type == 3 || mgInfoTbl[lbl_1_bss_17C].type == 5 || mgInfoTbl[lbl_1_bss_17C].type == 6 || _CheckFlag(0x10000U) == 0) {
        if (_CheckFlag(0x10000) != 0) {
            HuAR_DVDtoARAM(0x70000);
            while (HuARDMACheck() != 0) {}
        }
        omOvlReturnEx(1, 1);
        return;
    }

    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 0.0f;
    Center.z = 0.0f;
    CZoom = 500.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    var_r30 = Hu3DGLightCreate(0.0f, 100.0f, 1000.0f, 0.0f, -0.5f, -1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DGLightInfinitytSet(var_r30);
    lbl_1_bss_174 = 0;
    if (mgInfoTbl[GWSystem.mg_next].type != 4) {
        HuPrcChildCreate(fn_1_4D8, 0x64, 0x3000, 0, lbl_1_bss_180);
    } else {
        HuPrcChildCreate(fn_1_6490, 0x64, 0x3000, 0, lbl_1_bss_180);
    }
    lbl_1_bss_184[0] = omAddObjEx(lbl_1_bss_180, 0x7FDA, 0U, 0U, -1, omOutView);
    HuWinInit(1);
    lbl_1_bss_172 = frandmod(4);
}

void fn_1_4D8(void) {
    Process* sp8;
    s32 var_r27;
    s16 var_r28;
    s16 var_r29;
    s16 var_r30;
    s16 var_r31;

    sp8 = HuPrcCurrentGet();
    HuAudSeqPlay(0x39);
    for (var_r30 = var_r31 = 0; var_r30 < 4; var_r30++) {
        if (GWPlayerCfg[var_r30].iscom != 0) {
            var_r31++;
        }
    }
    if (var_r31 == 4) {
        lbl_1_bss_4 = 1;
    } else {
        lbl_1_bss_4 = 0;
    }
    fn_1_B78();
    HuPrcChildCreate(fn_1_888, 0x64, 0x2000, 0, lbl_1_bss_180);
    WipeCreate(1, 0, 0x14);
    while (WipeStatGet() != 0) HuPrcVSleep();
    HuDataDirClose(0x6F0000);
    lbl_1_bss_178 = 0;
    HuPrcChildCreate(fn_1_3FD8, 0x64, 0x3000, 0, lbl_1_bss_180);
    HuPrcSleep(0xA);
    if (lbl_1_bss_174 == 0) {
        HuPrcSleep(0x14);
    }
    fn_1_1F4C();
    fn_1_40DC();
    fn_1_2ADC();
    var_r29 = HuWinCreate(-10000.0f, 400.0f, 0x140, 0x28, 0);
    HuWinMesSpeedSet(var_r29 , 0);
    HuWinBGTPLvlSet(var_r29 , 0.0f);
    HuWinPriSet(var_r29, 5);
    HuWinAttrSet(var_r29, 0x800);
    HuWinMesSet(var_r29, 0x240007);
    HuPrcSleep(4);
    
    var_r30 = 0;
loopHack:
    if (lbl_1_bss_4 == 0 || var_r30 <= 0x78) {
        for (var_r31 = var_r28 = 0; var_r31 < 4; var_r31++) {
            if (GWPlayerCfg[var_r31].iscom == 0) {
                var_r28 = var_r28 | HuPadBtnDown[GWPlayerCfg[var_r31].pad_idx];
            }
        }

        if ((var_r28 & 0x100) != 0) {
            HuAudFXPlay(0x1C);
        } else {
            HuPrcVSleep();
            var_r30++;
            goto loopHack;
        }
    }

    HuWinKill(var_r29);
    if ((s32) GWSystem.team != 0) {
        fn_1_47FC();
    }
    while (lbl_1_bss_178 == 0) HuPrcVSleep();
    HuAudSeqAllFadeOut(0x3E8);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    if (GWSystem.save_mode == 3) {
        GWSystem.save_mode = 1;
    }
    var_r27 = GWSystem.save_mode;
    
    if (var_r27 != 1 && SLSaveFlagGet() != 0) {
        WipeCreate(2, 0, 0x1E);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        fn_1_461C();
    } else {
        WipeCreate(2, 0, 0x3C);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
    omSysPauseEnable(1);
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while (1) HuPrcVSleep();
}

void fn_1_888(void) {
    f32 var_f29;
    f32 var_f31;
    f32 var_f30;

    var_f31 = 0.0f;
    var_f30 = 0.0f;
    var_f29 = 0.0f;
    lbl_1_bss_0 = 0;

    while (1) {
        if (((HuPadBtn[0] | HuPadBtn[1] | HuPadBtn[2] | HuPadBtn[3]) & 0x100) != 0 || lbl_1_bss_4 != 0) {
            lbl_1_bss_174 = 1;
        } else {
            lbl_1_bss_174 = 0;
        }
        Hu3DModelRotSet(lbl_1_bss_1A9C[4], 0.0f, var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[5], 0.0f, -var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[6], 0.0f, var_f31, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1A9C[7], 0.0f, -var_f31, 0.0f);
        var_f31 += 0.2;
        if (var_f31 >= 360.0f) {
            var_f31 -= 360.0f;
        }
        if (lbl_1_bss_0 != 0) {
            Hu3DModelRotSet(lbl_1_bss_1A9C[8], 0.0f, var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[9], 0.0f, -var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[10], 0.0f, var_f30, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1A9C[11], 0.0f, -var_f30, 0.0f);
            var_f29 += 0.001;
            if (var_f29 > 0.1) {
                var_f29 = 0.1f;
            }
            var_f30 += var_f29;
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
        }
        HuPrcVSleep();
    }
}

s32 lbl_1_data_3A8[6] = { 0x6F0010, 0x6F0011, 0x6F0012, 0x6F0013, 0x6F0014, 0x6F0015 };
s32 lbl_1_data_3C0[6] = { 0x6F001F, 0x6F001E, 0x6F001D, 0x6F0021, 0x6F0020, 0x6F001F };
s16 lbl_1_data_3D8[16] = { 0x140, 0x84, 0x1F4, 0x84, 0x0140, 0xD9, 0x1F4, 0xD9, 0x140, 0x12E, 0x1F4, 0x12E, 0x140, 0x183, 0x1F4, 0x183 };
s16 lbl_1_data_3F8[8] = { 0x4A, 0x84, 0x4A, 0xD9, 0x4A, 0x12E, 0x4A, 0x183 };
Vec lbl_1_data_408[4] = { { 148.0f, 132.0f, 500.0f }, { 148.0f, 217.0f, 500.0f }, { 148.0f, 302.0f, 500.0f }, { 148.0f, 387.0f, 500.0f } };
s16 lbl_1_data_438[8] = { 0xA4, 0x94, 0xA4, 0xE9, 0xA4, 0x13E, 0xA4, 0x193 };
// extern s8 lbl_1_data_448;
// extern ? lbl_1_data_450;
// extern ? lbl_1_data_488;
// extern s8 lbl_1_data_4B8;
// extern s8 lbl_1_data_4C9;
// extern s8 lbl_1_data_4DA;

void fn_1_B78(void) {
    Vec sp14;
    s16 sp8[5];
    AnimData* temp_r22;
    AnimData* temp_r23;
    AnimData* temp_r24;
    s16 temp_r25;
    s16 var_r26;
    s16 temp_r27;
    AnimData* temp_r28;
    s16 temp_r29;
    s16 temp_r3;
    s16 var_r30;
    s16 var_r31;

    fn_1_8FF8(&lbl_1_data_0[0]);
    lbl_1_data_2A4[0].unk0 = lbl_1_data_3A8[mgInfoTbl[lbl_1_bss_17C].type];
    lbl_1_data_2A4[1].unk0 = lbl_1_data_3C0[mgInfoTbl[lbl_1_bss_17C].type];
    fn_1_927C(&lbl_1_data_2A4[0]);
    espDrawNoSet(lbl_1_bss_1A1A[0], 0x7F);
    temp_r28 = HuSprAnimReadFile(0x6F001B);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        lbl_1_bss_CE[var_r31] = HuSprGrpCreate(3);
        lbl_1_bss_9E[var_r31].x = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[var_r31], 0, lbl_1_bss_9E[var_r31].x);
        HuSprPosSet(lbl_1_bss_CE[var_r31], 0, -28.0f, 0.0f);
        
        lbl_1_bss_9E[var_r31].y = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[var_r31], 1, lbl_1_bss_9E[var_r31].y);
        HuSprPosSet(lbl_1_bss_CE[var_r31], 1, 0.0f, 0.0f);
        
        lbl_1_bss_9E[var_r31].z = HuSprCreate(temp_r28, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_CE[var_r31], 2, lbl_1_bss_9E[var_r31].z);
        HuSprPosSet(lbl_1_bss_CE[var_r31], 2, 28.0f, 0.0f);
        HuSprGrpPosSet(lbl_1_bss_CE[var_r31], lbl_1_data_3D8[var_r31 * 2], lbl_1_data_3D8[var_r31 * 2 + 1]);
        
        fn_1_3B50(lbl_1_bss_CE[var_r31], 0x3E7);
    }
    fn_1_3E08();
    fn_1_423C((s16 (*)[]) &sp8[0]);
    temp_r28 = HuSprAnimReadFile(0x6F003A);
    temp_r23 = HuSprAnimReadFile(0x6F003B);
    temp_r24 = HuSprAnimReadFile(0x6F003C);
    temp_r22 = HuSprAnimReadFile(0x6F003E);

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_3A[var_r31] = HuSprGrpCreate(5);
        if (sp8[lbl_1_bss_4A[var_r31]] < 0x64) {
            lbl_1_bss_12[var_r31].unk0 = HuSprCreate(temp_r28, 10, 0);
            HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 0, lbl_1_bss_12[var_r31].unk0);
            HuSprPosSet(lbl_1_bss_3A[var_r31], 0, 30.0f, -25.0f);
        } else {
            lbl_1_bss_12[var_r31].unk0 = HuSprCreate(temp_r22, 10, 0);
            HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 0, lbl_1_bss_12[var_r31].unk0);
            HuSprPosSet(lbl_1_bss_3A[var_r31], 0, 30.0f, -25.0f);
        }
        lbl_1_bss_12[var_r31].unk2 = HuSprCreate(temp_r23, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 1, lbl_1_bss_12[var_r31].unk2);
        HuSprPosSet(lbl_1_bss_3A[var_r31], 1, 12.0f, -25.0f);
        
        lbl_1_bss_12[var_r31].unk4 = HuSprCreate(temp_r24, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 2, lbl_1_bss_12[var_r31].unk4);
        HuSprPosSet(lbl_1_bss_3A[var_r31], 2, 28.0f, -25.0f);
        
        lbl_1_bss_12[var_r31].unk6 = HuSprCreate(temp_r24, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 3, lbl_1_bss_12[var_r31].unk6);
        HuSprPosSet(lbl_1_bss_3A[var_r31], 3, 44.0f, -25.0f);
        
        lbl_1_bss_12[var_r31].unk6 = HuSprCreate(temp_r24, 0, 0);
        HuSprGrpMemberSet(lbl_1_bss_3A[var_r31], 3, lbl_1_bss_12[var_r31].unk6);
        HuSprPosSet(lbl_1_bss_3A[var_r31], 3, 60.0f, -25.0f);

        HuSprGrpPosSet(lbl_1_bss_3A[var_r31], lbl_1_data_438[var_r31 * 2], lbl_1_data_438[var_r31 * 2 + 1]);
        fn_1_3CAC(lbl_1_bss_3A[var_r31], 9);
        HuSprGrpScaleSet(lbl_1_bss_3A[var_r31], 0.0f, 0.0f);
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r29 = GWPlayerCfg[var_r31].character;
        lbl_1_bss_E4[temp_r29][0] = HuSprAnimReadFile(temp_r29 * 3 + 0x6F0022);
        lbl_1_bss_E4[temp_r29][1] = HuSprAnimReadFile(temp_r29 * 3 + 0x6F0023);
        lbl_1_bss_E4[temp_r29][2] = HuSprAnimReadFile(temp_r29 * 3 + 0x6F0024);
        for (var_r30 = 0; var_r30 < 4; var_r30++) {
            lbl_1_bss_5C[temp_r29][var_r30] = Hu3DModelCreateFile(var_r30 + 0x6F0000);
            Hu3DModelScaleSet(lbl_1_bss_5C[temp_r29][var_r30], 1.1f, 1.1f, 1.1f);
            Hu3DAnimCreate(lbl_1_bss_E4[temp_r29], lbl_1_bss_5C[temp_r29][var_r30], "ys22");
            Hu3DModelAttrSet(lbl_1_bss_5C[temp_r29][var_r30], 1);
        }
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_144[var_r31] = HuSprAnimReadFile(var_r31 + 0x6F0016);
    }

    lbl_1_bss_52 = HuSprGrpCreate(4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprGrpMemberSet(lbl_1_bss_52, var_r31, HuSprCreate(lbl_1_bss_144[lbl_1_bss_42[var_r31]], var_r31, 0));
        HuSprPosSet(lbl_1_bss_52, var_r31, lbl_1_data_3F8[var_r31 * 2], lbl_1_data_3F8[var_r31 * 2 + 1]);
        fn_1_3B50(lbl_1_bss_CE[var_r31 * 2], GWStarsGet(lbl_1_bss_4A[var_r31]));
        fn_1_3B50(lbl_1_bss_CE[var_r31 * 2 + 1], BoardPlayerCoinsGet(lbl_1_bss_4A[var_r31]));
        temp_r29 = GWPlayerCfg[lbl_1_bss_4A[var_r31]].character;
        Hu3D2Dto3D(&lbl_1_data_408[var_r31], 1, &sp14);
        Hu3DModelPosSetV(lbl_1_bss_5C[temp_r29][lbl_1_bss_42[var_r31]], &sp14);
        Hu3DModelAttrReset(lbl_1_bss_5C[temp_r29][lbl_1_bss_42[var_r31]], 1);
    }

    for (var_r31 = 4; var_r31 <= 11; var_r31++) {
        Hu3D2Dto3D(&lbl_1_data_0[var_r31].unk10, 1, &sp14);
        Hu3DModelPosSetV(lbl_1_bss_1A9C[var_r31], &sp14);
        Hu3D3Dto2D(&sp14, 1, &sp14);
    }

    temp_r25 = Hu3DModelCreateFile(0x6F0004);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        temp_r3 = Hu3DModelLink(temp_r25);
        lbl_1_bss_168[var_r31] = temp_r3;
        sp14 = lbl_1_data_408[var_r31];
        sp14.x += 5.0f;
        sp14.y += 3.0f;
        sp14.z += 200.0f;
        Hu3D2Dto3D(&sp14, 1, &sp14);
        Hu3DModelPosSetV(temp_r3, &sp14);
        Hu3DModelScaleSet(temp_r3, 1.5f, 1.5f, 1.5f);
    }

    Hu3DModelAttrSet(temp_r25, 1);
    temp_r25 = Hu3DModelCreateFile(0x6F0007);
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        temp_r3 = Hu3DModelLink(temp_r25);
        lbl_1_bss_158[var_r31] = temp_r3;
        sp14 = lbl_1_data_0[var_r31 + 4].unk10;
        sp14.x += 5.0f;
        sp14.y += 3.0f;
        sp14.z += 200.0f;
        Hu3D2Dto3D(&sp14, 1, &sp14);
        Hu3DModelPosSetV(temp_r3, &sp14);
        Hu3DModelScaleSet(temp_r3, 1.5f, 1.5f, 1.5f);
    }

    Hu3DModelAttrSet(temp_r25, 1);
    lbl_1_bss_E0 = HuSprAnimReadFile(0x6F001C);
    lbl_1_bss_9C = HuSprGrpCreate(4);
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        HuSprGrpMemberSet(lbl_1_bss_9C, var_r31, HuSprCreate(lbl_1_bss_E0, var_r31, 0));
        HuSprScaleSet(lbl_1_bss_9C, var_r31, 0.0f, 0.0f);
        HuSprPosSet(lbl_1_bss_9C, var_r31, lbl_1_data_408[var_r31].x - 4.0f, lbl_1_data_408[var_r31].y - 35.0f);
        HuSprAttrSet(lbl_1_bss_9C, var_r31, 4);
    }
    lbl_1_bss_170 = var_r26 = HuSprGrpCreate(4);
    HuSprGrpMemberSet(var_r26, 0, HuSprCreate(HuSprAnimReadFile(0x6F003F), 0x64, 0));
    HuSprAttrSet(var_r26, 0, 4);
    HuSprDrawNoSet(var_r26, 0, 0x7F);
    HuSprGrpMemberSet(var_r26, 1, HuSprCreate(HuSprAnimReadFile(0x6F0040), 0x5A, 0));
    HuSprAttrSet(var_r26, 1, 4);
    HuSprGrpMemberSet(var_r26, 2, HuSprCreate(HuSprAnimReadFile(0x6F0041), 0x50, 0));
    HuSprAttrSet(var_r26, 2, 4);
    HuSprDrawNoSet(var_r26, 2, 0x7F);
    HuSprGrpMemberSet(var_r26, 3, HuSprCreate(HuSprAnimReadFile(0x6F0042), 0x50, 0));
    HuSprAttrSet(var_r26, 3, 4);
    HuSprDrawNoSet(var_r26, 3, 0x7F);
}
