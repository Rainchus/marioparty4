#include "REL/w03Dll.h"
#include "game/data.h"
#include "game/hsfman.h"

//file is full of old names and old signatures...needs updating
//is also missing half the functions in this TU

void fn_1_313C(void);
void fn_1_3218(void);
void fn_1_3304(void);
extern Process* lbl_1_bss_70;
extern s8 lbl_1_bss_7C;
extern s16 lbl_1_data_310;
extern char* lbl_1_data_34C[];

// #define MAKE_DATA_NUM(dir, file) (((dir) << 16)+(file))
// #define MAKE_DIR_NUM(dir) ((dir) << 16)

// #define DATA_NUM_LISTEND -1

s32 lbl_1_data_318[] = {
    DATA_MAKE_NUM(0x0077, 0x0016),
    DATA_MAKE_NUM(0x0077, 0x0017),
    DATA_MAKE_NUM(0x0077, 0x0018),
    DATA_MAKE_NUM(0x0077, 0x0019),
    DATA_MAKE_NUM(0x0077, 0x001A),
    DATA_NUM_LISTEND
};

void fn_1_3058(void) {
    lbl_1_data_310 = fn_8006D9A4(0x770015, &lbl_1_data_318, 0);
    fn_1_3304();
}

s32 fn_1_309C(void) {
    fn_800688E8(0);
    lbl_1_bss_70 = HuPrcChildCreate(fn_1_313C, 0x2003U, 0x2000U, 0, lbl_801D3ED0);
    HuPrcDestructorSet2(lbl_1_bss_70, fn_1_3218);

    while (lbl_1_bss_70) {
        HuPrcVSleep();
    }
    
    fn_800688E8(1);
    return lbl_1_bss_7C;
}

s32 fn_800747C4(s32, s32, s32);                         /* extern */
extern s16 lbl_1_data_310;
extern f64 lbl_1_rodata_100;
extern f32 lbl_1_rodata_108;
extern f32 lbl_1_rodata_E8;
extern f64 lbl_1_rodata_F0;
extern f64 lbl_1_rodata_F8;

void fn_1_3304(void) {
    Point3d sp8;
    f32 temp_f31;
    s32 var_r31;
    

    if (lbl_1_bss_0->unk1 != 0) {
        var_r31 = fn_800745F0(0, 0x4000);
    } else {
        var_r31 = fn_800745F0(0, 0x8000);
    }
    var_r31 = fn_800747C4(0, var_r31, 0x02000000);
    fn_80074210(0, var_r31, &sp8);
    temp_f31 = lbl_1_rodata_E8;
    sp8.x = sp8.x + (lbl_1_rodata_F0 * sin((lbl_1_rodata_F8 * temp_f31) / lbl_1_rodata_100));
    sp8.z = sp8.z + (lbl_1_rodata_F0 * cos((lbl_1_rodata_F8 * temp_f31) / lbl_1_rodata_100));
    sp8.y = 45.0f + sp8.y;
    fn_8006F158(lbl_1_data_310, &sp8);
    fn_8006E2B8(lbl_1_data_310, 2, 0x40000001);
}

s32 fn_1_3478(s32);
void fn_1_3814(s32);
void fn_1_3968(s32);
void fn_1_3E88(s32);
void fn_1_3F5C(s32);
void fn_8005DAC4(f32, f32);
extern s8 lbl_1_bss_7C;
extern f32 lbl_1_rodata_D8;
extern f32 lbl_1_rodata_DC;
extern f32 lbl_1_rodata_E0;
extern f32 lbl_1_rodata_E4;

void fn_1_313C(void) {
    s32 temp_r31;

    temp_r31 = GWSystem.player_curr;
    lbl_1_bss_7C = 0;
    lbl_1_bss_0->unk3 = 1;
    if (fn_1_3478(temp_r31) != 0) {
        fn_8005DAC4(lbl_1_rodata_D8, lbl_1_rodata_DC);
        fn_800884F4(0);
        fn_1_3968(temp_r31);
        fn_1_3E88(temp_r31);
        fn_1_3F5C(temp_r31);
        lbl_1_bss_7C = 1;
    }
    fn_8005DAC4(lbl_1_rodata_E0, lbl_1_rodata_E4);
    fn_1_3814(temp_r31);
    HuPrcEnd();
}

extern s32 lbl_1_bss_70;
extern s16 lbl_1_data_312;
extern s16 lbl_1_data_314;
extern s16 lbl_1_data_316;

void fn_1_3218(void) {
    if (lbl_1_data_316 != -1) {
        HuWinKill(lbl_1_data_316);
        lbl_1_data_316 = -1;
    }
    if (lbl_1_data_314 != -1) {
        fn_8006DB90(lbl_1_data_314);
        lbl_1_data_314 = -1;
    }
    if (lbl_1_data_312 != -1) {
        fn_800637CC(GWSystem.player_curr, lbl_1_data_312);
        lbl_1_data_312 = -1;
    }
    lbl_1_bss_0->unk3 = 0;
    lbl_1_bss_70 = 0;
}

s32 BoardWinChoiceGet(void);
void fn_1_4354(s32);
s32 fn_80061FDC(s32);
s32 fn_80063EC0(s32);
void fn_80063EEC(s32, s32);
void fn_8006E47C(s16, s32, f32, f32, s32);
s32 fn_8006E91C(s16);
void fn_80070390(s32, s32, s32, s32);
void fn_80070770(s32);
void fn_80072DA8(s32);
s32 fn_800747C4(s32, s16, s32);
extern s16 lbl_1_data_310;
extern f64 lbl_1_rodata_100;
extern f32 lbl_1_rodata_10C;
extern f32 lbl_1_rodata_110;
extern f32 lbl_1_rodata_114;
extern f32 lbl_1_rodata_118;
extern f32 lbl_1_rodata_11C;
extern f32 lbl_1_rodata_E8;
extern f64 lbl_1_rodata_F8;

s32 fn_1_3478(s32 arg0) {
    Point3d sp38;
    Point3d sp2C;
    Point3d sp20;
    f32 sp1C;
    f32 sp18;
    Point3d sp14;
    Point3d sp8;

    s16 temp_r28;
    s32 temp_r3;
    s32 var_r29;
    s32 var_r30;
    s32 temp;
    s32 temp_r26;
    f32 float_temp;
    s32 i, j;

    sp14.x = 0.0f;
    sp14.y = 150.0f;
    sp14.z = 0.0f;

    sp8.x = -15.0f;
    sp8.y = 0.0f;
    sp8.z = 0.0f;

    fn_8005DB6C(lbl_1_data_310, &sp8, &sp14, lbl_1_rodata_114, lbl_1_rodata_118, 0x15);
    temp_r28 = GWPlayer[arg0].space_curr;
    fn_8006310C(arg0, &sp2C);
    temp = fn_800747C4(0, temp_r28, 0x02000000);
    fn_80074210(0, temp, &sp38);
    PSVECSubtract(&sp38, &sp2C, &sp20);
    float_temp = atan2(sp20.x, sp20.z) / 3.141592653589793f * 180.0f;
    fn_80067C90(arg0, (float_temp), 0xF);
    
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    
    fn_80067B98(arg0);
    HuAudFXPlay(0x447);
    fn_8006E47C(lbl_1_data_310, 4, 0.0f, 5.0f, 0);
    HuPrcSleep(6);
    
    while (fn_8006E91C(lbl_1_data_310) == 0) {
        HuPrcVSleep();
    }
    
    fn_8006E47C(lbl_1_data_310, 1, 0.0f, 5.0f, 0x40000001);
    temp_r26 = fn_80061FDC(arg0);
    BoardWinCreate(2, 0x160010, 8);
    fn_800706D0(temp_r26, 3);
    BoardWinWait();
    if (fn_80063EC0(arg0) < 5) {
        BoardWinCreate(2, 0x160013, 8);
        BoardWinWait();
        BoardWinKill();
        return 0;
    }
    var_r29 = 0;
    goto test;
    while (1) {
        fn_80070390(2, 0x160011, 8, 0);
        fn_80070770(0x10);
        
        if (GWPlayer[arg0].com != 0) {
            fn_1_4354(arg0);
        }
        
        BoardWinWait();
        BoardWinKill();
        switch (BoardWinChoiceGet()) {
        case 0:
            var_r29 = 1;
            break;
        case 2:
            fn_80072DA8(arg0);
            break;
        default:
        case 1:
            BoardWinCreate(2, 0x160014, 8);
            BoardWinWait();
            BoardWinKill();
            return 0;
        }
        test:
        if (var_r29 != 0) {
            fn_80071034(0, 1, 1000);
            for (j = 0; j < 5; j++) {
                fn_80063EEC(arg0, -1);
                HuAudFXPlay(14);
                HuPrcSleep(6);            
            }
            HuAudFXPlay(15);
            BoardWinKill();
            return 1;
        }
    }
}

extern s8 lbl_1_bss_7C;
extern f32 lbl_1_rodata_120;
extern f32 lbl_1_rodata_124;

void fn_1_3814(s32 arg0) {
    Point3d sp14;
    Point3d sp8;
    f32 temp;

    fn_8006E47C(lbl_1_data_310, 2, 0.0f, 10.0f, 0x40000001);
    temp = (180.0f + fn_80063448(arg0));
    fn_80067C90(arg0, temp, 0xF);
    
    while (fn_8006874C(arg0) == 0) {
        HuPrcVSleep();
    }
    
    fn_8005D284(1);
    fn_8005D834(arg0);
    if (lbl_1_bss_7C != 0) {
        fn_80074210(0, GWPlayer[arg0].space_curr, &sp14);
        fn_8006310C(arg0, &sp8);
        fn_80066F44(arg0, &sp8, &sp14, 0x14);
        while (GWPlayer[arg0].moving) {
            HuPrcVSleep();
        }
    }
    fn_80067B98(arg0);
    fn_8005E0C0();
}

void fn_1_3968(s32 arg0) {
    s32 var_r29 = 0;
    s32 var_r28 = 0;
    s32 sp48[] = {0x005F0065, 0x001A0065, 0x006D0065, 0x008A0065, 0x00850065, 0x00110065, 0x000D0065, 0x00810065};
    Point3d sp3C;
    Point3d sp30;
    Point3d sp24;
    Point3d sp18;
    s32 sp10[2] = {0x00770013, 0x00770014};
    f32 spC;
    s16 sp8;
    
    f32 temp_f30;
    f32 temp_f28;
    f32 temp_f31;
    f32 temp_f27;

    s16 character;

    lbl_1_data_314 = fn_8006D9A4(sp10[lbl_1_bss_0->unk1], NULL, 0);
    character = GWPlayer[arg0].character;
    lbl_1_data_312 = fn_8006374C(arg0, sp48[character]);
    
    Hu3DModelObjPosGet(fn_8006DBD4(lbl_1_data_310), "itemhook_oya", &sp3C);
    fn_8006310C(arg0, &sp30);
    temp_f30 = fn_8005FBE8(&sp3C, &sp30);
    PSVECSubtract(&sp3C, &sp30, &sp24);
    PSVECNormalize(&sp24, &sp24);
    PSVECScale(&sp24, &sp24, temp_f30 / lbl_1_rodata_108);
    fn_80063A1C(arg0, 4, 0.0f, lbl_1_rodata_11C, 0);
    HuPrcSleep(5);
    
    spC = fn_80063448(arg0);
    temp_f27 = 180.0f + spC;
    var_r29 = 0;
    sp8 = 0;
    temp_f28 = 40.0f;
    
    while (1) {
        temp_f31 = __OSs16tof32(&sp8);
        sp24.y = temp_f28 + (-0.08166667f * (0.75f * (temp_f31 * temp_f31)));
        PSVECAdd(&sp30, &sp24, &sp30);
        temp_f30 = fn_8005FBE8(&sp3C, &sp30);
        if (temp_f30 < lbl_1_rodata_11C) {
            sp24.x = sp24.z = 0.0f;
            sp30.x = sp3C.x;
            sp30.z = sp3C.z;
        }
        
        if (var_r29 == 0) {
            if (sp3C.y < sp30.y) {
                var_r29 = 1;
            }
        } else {
            fn_8005FF28(&spC, temp_f27, 5.142857f);
            fn_80063374(arg0, spC);
        }
        
        if (sp30.y <= sp3C.y && var_r29 != 0) {
            sp30.y = sp3C.y;
            break;
        }
        fn_80062FA4(arg0, &sp30);
        HuPrcVSleep();
        sp8 += 1;        
    }
    
    fn_80070DEC(1, 0x18, 0x7F, 0);
    fn_80063040(arg0, 0.0f, 0.0f, 0.0f);
    
    
    fn_8006F73C(lbl_1_data_310, "itemhook_oya",  GetCurrentPlayerIndex(GetCurrentPlayer(arg0)));
    fn_8006394C(arg0, lbl_1_data_312, 0x40000001);
    HuAudFXPlay(0x44F);
    fn_8006E47C(lbl_1_data_310, 5, 0.0f, lbl_1_rodata_11C, 0);
    
    sp18.x = -15.0f;
    sp18.y = 180.0f;
    sp18.z = 0.0f;
    
    fn_8005DB6C(lbl_1_data_310, &sp18, 0, 4000.0f, lbl_1_rodata_118, 0x150);
    
    for (var_r28 = 0, sp8 = 0; ; sp8++) {
        if (var_r28 == 0) {
            if (sp8 == 0x78U) {
                WipeColorSet(0, 0, 0);
                WipeCreate(2, 0, -1);
                var_r28 = 1;
            }
        } else if (WipeStatGet() == 0) {
            break;
        }
        HuPrcVSleep();
    }
}


void fn_8005D7B4(s32);                                   /* extern */
void fn_80062FA4(s32, Point3d*);                       /* extern */
void fn_8006F800(s16);                                 /* extern */
extern f32 lbl_1_rodata_108;
extern f32 lbl_1_rodata_124;
extern f64 lbl_1_rodata_F0;

void fn_1_48EC(s32);                                   /* extern */
void fn_1_4A9C(void);                                      /* extern */
void fn_1_5838(s32);                                   /* extern */
s32 fn_1_62D0(void);                                    /* extern */
void fn_80088638(s32);                                 /* extern */
void fn_80088790(s32, s32);                              /* extern */
extern s8 lbl_1_bss_7D;


void fn_1_3E88(s32 arg0) {
    lbl_1_bss_7D = 0;
    fn_1_48EC(arg0);
    fn_1_5838(arg0);
    lbl_1_bss_7D = 1;
    fn_80088638(arg0);
    fn_80088790(arg0, 1);
    WipeCreate(1, 0, 0x15);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    while (fn_1_62D0() != 3) {
        HuPrcVSleep();
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_4A9C();
    fn_80071034(0, 0, 0x3E8);
}

void fn_1_3F5C(s32 arg0) {
    Mtx sp38;
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    f32 temp_f31;
    s16 temp_r28;
    s32 var_r31;
    s16 var_r30;

    if (lbl_1_bss_0->unk1 != 0) {
        lbl_1_bss_0->unk1 = 0;
        var_r30 = fn_800745F0(0, 0x8000);
    } else {
        lbl_1_bss_0->unk1 = 1;
        var_r30 = fn_800745F0(0, 0x4000);
    }
    temp_r28 = fn_800747C4(0, var_r30, 0x02000000);
    fn_8005D7B4(0);
    fn_8006F800(lbl_1_data_310);
    if (lbl_1_bss_0->unk1 != 0) {
        var_r31 = fn_800745F0(0, 0x4000);
    } else {
        var_r31 = fn_800745F0(0, 0x8000);
    }
    var_r31 = fn_800747C4(0, var_r31, 0x02000000);
    fn_80074210(0, var_r31, &sp8);
    temp_f31 = 0.0f;
    sp8.x = (sp8.x + (lbl_1_rodata_F0 * sin((lbl_1_rodata_F8 * temp_f31) / 180.0f)));
    sp8.z = (sp8.z + (lbl_1_rodata_F0 * cos((lbl_1_rodata_F8 * temp_f31) / 180.0f)));
    sp8.y = 45.0f + sp8.y;
    fn_8006F158(lbl_1_data_310, &sp8);
    fn_8006E2B8(lbl_1_data_310, 2, 0x40000001);
    fn_8006E2B8(lbl_1_data_310, 1, 0x40000001);
    fn_8006F0D4(lbl_1_data_310, 0.0f);
    PSMTXIdentity(sp38);
    fn_8006EFBC(lbl_1_data_310, sp38);
    sp20.x = 0.0f;
    sp20.y = 150.0f;
    sp20.z = 0.0f;
    sp14.x = -15.0f;
    sp14.y = 0.0f;
    sp14.z = 0.0f;
    fn_8005DB6C(lbl_1_data_310, &sp14, &sp20, lbl_1_rodata_114, lbl_1_rodata_118, 1);
    fn_80074210(0, temp_r28, &sp2C);
    fn_80062FA4(arg0, &sp2C);
    GWPlayer[arg0].space_curr = var_r30;
    fn_80063374(arg0, lbl_1_rodata_124);
    fn_80067B98(arg0);
    HuPrcSleep(2);
    fn_8005D7B4(1);
    fn_8006E2B8(lbl_1_bss_C[2], 0, 0x40000001);
    fn_8006E0B0(lbl_1_bss_C[2], 1, 0x64);
    fn_8008853C(0);
    HuPrcSleep(2);
    fn_8008853C(1);
    WipeCreate(1, 0, 0x15);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    BoardWinCreate(2, 0x16000F, 8);
    BoardWinWait();
    BoardWinKill();
}

void fn_800712C8(void);                                    /* extern */
void fn_80071328(void);                                    /* extern */

void fn_1_4354(s32 arg0) {
    s32 sp8;
    s32 starPos;
    s32 var_r30;

    var_r30 = 0;
    starPos = GWSystem.star_pos;
    
    if (lbl_1_bss_0->unk1 != 0) {
        if ((starPos == 1) || (starPos == 2) || (starPos == 3) || (starPos == 4)) {
            var_r30 = 1;
        }
    } else if ((starPos == 0) || (starPos == 5) || (starPos == 6) || (starPos == 7)) {
        var_r30 = 1;
    }
    if (fn_80063EC0(arg0) < 0x14) {
        var_r30 = 1;
    }
    if (var_r30 != 0) {
        fn_800712C8();
        return;
    }
    fn_80071328();
}

f32 lbl_1_bss_80[20][2];

typedef struct w03StructUnk3 {
/* 0x00 */ s16 unk_00;
/* 0x02 */ s16 model;
/* 0x04 */ f32 unk_04;
/* 0x08 */ Vec unk_08;
/* 0x14 */ Vec unk_14;
} w03StructUnk3;

typedef struct w03StructUnk2 {
/* 0x00 */ struct {
        u8 unkbit_00 : 1;
        u8 unkbit_01 : 2;
        u8 unkbit_03 : 1;
        u8 unkbit_04 : 1;
    };
    s8 unk_01;
    s8 unk_02;
    u8 unk_03;
    s16 model;
    char unk_06[2];
    w03StructUnk3* unk_08;
} w03StructUnk2;

void fn_1_4424(w03StructUnk2* arg0) {
    Mtx sp108;
    Mtx spD8;
    Mtx spA8;
    Mtx sp78;
    Point3d sp6C;
    Point3d sp60;
    Vec sp54;
    Vec sp48;
    Point3d sp3C;
    Vec sp30;
    Vec sp24;
    Vec sp18;
    s32 sp14;
    f32 temp;
    s16 spC;
    s16 sp8;
    f32 temp_f30;
    s16 temp_r23;
    s16 var_r25;
    f32 sp10;
    f32 sp10_2;
    s16 i;
    char* temp_r22;
    w03StructUnk3* temp_r27;
    ModelData* temp_r28;

    memset(&lbl_1_bss_80, 0, 0xA0);
    sp48.x = sp54.x = 0.0f;
    sp48.y = sp54.y = 0.0f;
    sp48.z = sp54.z = 0.0f;
    sp14 = 0;
    BoardSpaceFlagPosGet(0, 0x8000U, &sp6C);
    BoardSpaceFlagPosGet(0, 0x8000U, &sp60);
    if (lbl_1_bss_0->unk1 != 0) {
        PSVECSubtract(&sp6C, &sp60, &sp3C);
    } else {
        PSVECSubtract(&sp60, &sp6C, &sp3C);
    }
    sp10_2 = 180.0f * (atan2(-sp3C.x, -sp3C.z) / 3.141592653589793);
    BoardModelMotionStart(lbl_1_data_314, 0, 0U);
    BoardModelMotionSpeedSet(lbl_1_data_314, 8.0f);
    HuPrcSleep(1);
    temp_r23 = BoardModelIDGet(lbl_1_data_314);
    temp_r28 = &Hu3DData[temp_r23];
    temp_r22 = lbl_1_data_34C[lbl_1_bss_0->unk1];
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_314), temp_r22, &sp48);
    sp24.x = 0.0f;
    sp24.y = 1.0f;
    sp24.z = 0.0f;
    for (i = var_r25 = 0; i < 20;) {
        Hu3DMotionExec(temp_r23, temp_r28->unk_08, temp_r28->unk_64, 0);
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_314), temp_r22, &sp54);
        temp_r28->unk_64 = (f32) (temp_r28->unk_64 + temp_r28->unk_68);
        if (temp_r28->unk_64 > 400.0f) {
            break;
        }
        
        if (var_r25 % 4 == 0 && ((s16) var_r25 != 0)) {
            temp_r27 = &arg0->unk_08[i];
            temp_r27->unk_00 = 1;
            temp_f30 = (0.5f - BoardRandFloat()) * 10;
            OSf32tos16(&temp_f30, &sp8);
            sp8 = (sp8 / 10) * 10;
            OSs16tof32(&sp8, &temp_f30);
            lbl_1_bss_80[i+1][0] = temp_f30;
            lbl_1_bss_80[i+1][1] = temp_r28->unk_64;
            sp30 = sp48;
            sp18 = sp54;
            BoardMTXCalcLookAt(spA8, &sp18, &sp24, &sp30);
            PSMTXTranspose(spA8, spA8);
            PSMTXRotRad(spD8, 0x7A, 0.017453292f * temp_f30);
            PSMTXTrans(sp108, 0.0f, -350.0f, 0.0f);
            PSMTXConcat(spD8, sp108, sp108);
            PSMTXConcat(spA8, sp108, sp108);
            PSMTXTrans(sp78, sp54.x, sp54.y, sp54.z);
            PSMTXConcat(sp78, sp108, sp78);
            Hu3DMtxTransGet(sp78, &temp_r27->unk_08);
            BoardModelPosSetV(temp_r27->model, &temp_r27->unk_08);
            BoardModelVisibilitySet(temp_r27->model, 1);
            i++;
        }
        sp48 = sp54;
        var_r25++;
    }
    arg0->unk_03 = i;
}

void fn_1_48EC(s32 arg0) {
    Point3d spC;
    omObjData* obj;
    s32 i;
    w03StructUnk2* temp_r31;
    w03StructUnk3* temp_r30;

    obj = omAddObjEx(boardObjMan, 0x101, 0U, 0U, -1, fn_1_50D4);
    lbl_1_bss_74 = obj;
    temp_r31 = OM_GET_WORK_PTR(obj, w03StructUnk2);
    temp_r31->unkbit_00 = 0;
    temp_r31->unk_01 = 0;
    temp_r31->unkbit_03 = 0;
    temp_r31->unkbit_04 = 0;
    temp_r31->unk_02 = -1;
    temp_r31->unkbit_01 = arg0;
    temp_r31->unk_08 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xA00, 0x10000000U);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_C[2]), "coin", &spC);
    temp_r31->model = BoardModelCreate(0x770007, NULL, 0);
    BoardModelVisibilitySet(temp_r31->model, 0);
    BoardModelPosSetV(temp_r31->model, &spC);
    BoardModelLayerSet(temp_r31->model, 2U);
    memset(temp_r31->unk_08, 0, 0xA00U);

    for (i = 0; i < 0x50; i++) {
        temp_r30 = &temp_r31->unk_08[i];
        temp_r30->model = BoardModelCreate(0x70009, 0, 1);
        BoardModelVisibilitySet(temp_r30->model, 0);
        BoardModelMotionStart(temp_r30->model, 0, 0x40000001U);        
    }
    
    fn_1_4424(temp_r31);
}

extern omObjData* lbl_1_bss_74;

typedef struct w03UnkStruct4 {
     /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
    };   
} w03UnkStruct4;

void fn_1_4A9C(void) {
    ((w03UnkStruct4*)&lbl_1_bss_74->work[0])->unk00_bit0 = 1;
}

void fn_1_4ABC(w03StructUnk2* arg0) {
    Point3d sp8;
    f32 temp_f31;
    w03StructUnk3* temp_r31;
    s32 i;
    
    //reg alloc hack
    (void)i;
    (void)i;
    
    BoardModelPosGet(lbl_1_data_310, &sp8);
    sp8.y += lbl_1_rodata_180;

    for (i = 0; i < arg0->unk_03; i++) {
        temp_r31 = &arg0->unk_08[i];
        if (temp_r31->unk_00 == 1) {
            if (BoardVecMinDistCheck(&sp8, &temp_r31->unk_08, lbl_1_rodata_184) != 0) {
                temp_r31->unk_00 = -1;
                BoardModelVisibilitySet(temp_r31->model, 0);
                CharModelLayerSetAll(2);
                CharModelCoinEffectCreate(1, &temp_r31->unk_08);
                BoardPlayerCoinsAdd((arg0->unk_00 >> 5) & 3, 1);
                HuAudFXPlay(7);
            }
            BoardModelPosSetV(temp_r31->model, &temp_r31->unk_08);
        }        
    }

    BoardModelPosGet(lbl_1_data_310, &sp8);

    for (i = arg0->unk_03; i < 0x50; i++) {
        temp_r31 = &arg0->unk_08[i];
        if (temp_r31->unk_00 == 1) {
            temp_r31->unk_04 += lbl_1_rodata_168;
            temp_f31 = lbl_1_rodata_188 * (temp_r31->unk_04 * temp_r31->unk_04);
            PSVECAdd(&temp_r31->unk_14, &temp_r31->unk_08, &temp_r31->unk_08);
            temp_r31->unk_08.y += lbl_1_rodata_18C * temp_f31;
            if (temp_r31->unk_08.y < lbl_1_rodata_190) {
                temp_r31->unk_00 = -1;
                BoardModelVisibilitySet(temp_r31->model, 0);
            } else if (BoardVecMinDistCheck(&sp8, &temp_r31->unk_08, lbl_1_rodata_184) != 0) {
                temp_r31->unk_00 = -1;
                BoardModelVisibilitySet(temp_r31->model, 0);
                BoardPlayerCoinsAdd((arg0->unk_00 >> 5) & 3, 1);
                CharModelLayerSetAll(2);
                CharModelCoinEffectCreate(1, &temp_r31->unk_08);
                HuAudFXPlay(7);
            } else {
                BoardModelPosSetV(temp_r31->model, &temp_r31->unk_08);
            }
        }        
    }
}


extern omObjData* lbl_1_bss_74;

s32 fn_1_4D0C(w03StructUnk3** arg0, s16* arg1) {
    w03StructUnk2* temp_r31;

    if (!(lbl_1_bss_74)) {
        return 0;
    }
    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_74, w03StructUnk2);
    *arg0 = temp_r31->unk_08;
    *arg1 = temp_r31->unk_03;
    return 1;
}

void fn_1_4D60(w03StructUnk2* arg0) {
    Point3d sp8;
    f32 temp_f31;
    f32 temp_f30;
    s32 i;
    s32 j;
    w03StructUnk3* temp_r31;

    if (arg0->unk_02 == 1) {
        Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_bss_C[2]), "coin", &sp8);
        for (i = 0; i < 5; i++) {
            for (j = arg0->unk_03; j < 0x50; j++) {
                temp_r31 = &arg0->unk_08[j];
                if (temp_r31->unk_00 == 0) {
                    temp_r31->unk_00 = 1;
                    temp_f31 = 360.0f * BoardRandFloat();
                    temp_f30 = 5.0f * BoardRandFloat();
                    temp_r31->unk_14.x = temp_f30 * sin((3.141592653589793 * temp_f31) / 180.0);
                    temp_r31->unk_14.y = 50.0f + (20.0f * BoardRandFloat());
                    temp_r31->unk_14.z = temp_f30 * cos((3.141592653589793 * temp_f31) / 180.0);
                    temp_r31->unk_08.x = sp8.x;
                    temp_r31->unk_08.y = sp8.y;
                    temp_r31->unk_08.z = sp8.z;
                    BoardModelVisibilitySet(temp_r31->model, 1);
                    BoardModelMotionStart(temp_r31->model, 0, 0x40000001);
                    break;
                }
            }
        }
    }
}

void fn_1_4F24(w03StructUnk2* arg0) {
    s32 var_r30 = 0;
    s32 sp8[4] = {5, 10, 30, 40};
    s32 temp_r29;
    s32 temp_r28;
    
    if (arg0->unk_02 == -1) {
        if (GWTeamGet()) {
            if (GWPlayer[arg0->unkbit_01].rank == 0) {
                var_r30 = 5;
            } else if (GWPlayer[arg0->unkbit_01].rank == 1) {
                var_r30 = 20;
            }
        } else {
            var_r30 = sp8[GWPlayer[arg0->unkbit_01].rank];
        }
        temp_r29 = BoardRandMod(100);
        temp_r28 = BoardRandMod(100);
        if (temp_r29 < var_r30) {
            if (temp_r28 < 30) {
                arg0->unk_02 = 2;
            } else {
                arg0->unk_02 = 1;
            }
        } else {
            arg0->unk_02 = 0;
        }
        if (arg0->unk_02 != 0) {
            BoardModelMotionShiftSet(lbl_1_bss_C[2], 0, 0, 101.0f, 0);
        }
    }
}

void fn_1_50D4(omObjData* arg0) {
    Point3d sp50;
    Point3d sp44;
    Point3d sp38;
    PlayerState* sp18;
    PlayerState* sp14;
    s16 sp10[2];
    s16 spC[2];
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    s32 i, j, k;
    s32 temp_r22;
    s32 temp_r23;
    w03StructUnk3* temp_r30;
    w03StructUnk2* temp_r31;
    w03StructUnk3* temp;

    temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_74, w03StructUnk2);
    if ((temp_r31->unkbit_00 != 0) || (BoardIsKill() != 0)) {
        for (i = 0; i < 0x50; i++) {
            temp = &temp_r31->unk_08[i];
            BoardModelKill(temp->model);
        }

        for (i = 0; i < 4; i++) {
            BoardModelVisibilitySet(BoardPlayerModelGet(i), 1);
        }
        
        BoardModelKill(temp_r31->model);
        HuMemDirectFree(temp_r31->unk_08);
        lbl_1_bss_74 = 0;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        return;
    }
    
    if (lbl_1_data_314 != -1) {
        temp_f31 = BoardModelMotionTimeGet(lbl_1_data_314);
        if (temp_r31->unk_01 == 0) {
            if ((lbl_1_bss_0->unk1 != 0) &&
                ((temp_f31 >= 212.0f)) ||
                (lbl_1_bss_0->unk1 == 0) &&
                ((temp_f31 >= 86.0f))) {
                
                temp_r31->unk_01 = 1;
            }
        } else {
            fn_1_4F24(temp_r31); //inline
        }
        
        if (temp_r31->unk_01 != 0) {
            if (BoardModelMotionEndCheck(lbl_1_bss_C[2]) != 0) {
                BoardModelMotionStart(lbl_1_bss_C[2], 0, 0x40000001);
                BoardModelMotionStartEndSet(lbl_1_bss_C[2], 1, 100);
            }
            if (BoardModelMotionEndCheck(temp_r31->model) != 0) {
                BoardModelVisibilitySet(temp_r31->model, 0);
            }
        }
        
        if (BoardModelMotionTimeGet(lbl_1_bss_C[2]) >= lbl_1_rodata_1BC) {
            if (temp_r31->unkbit_04 == 0) {
                if (temp_r31->unkbit_03 == 0) {
                    HuAudFXPlay(0x43C);
                } else {
                    HuAudFXPlay(0x43D);
                }
                temp_r31->unkbit_04 = 1;
            }
            if (temp_r31->unk_02 == 1) {
                omVibrate(GWSystem.player_curr, 0xC, 4, 2);
                fn_1_4D60(temp_r31); //inline
            } else if ((temp_r31->unk_02 == 2) && (temp_r31->unkbit_03 == 0)) {
                omVibrate(GWSystem.player_curr, 0xC, 0xC, 0);
                BoardModelVisibilitySet(temp_r31->model, 1);
                BoardModelMotionStart(temp_r31->model, 0, 0);
                temp_r31->unkbit_03 = 1;
            }
        }
        
        fn_1_4ABC(temp_r31);
        
        for (i = 0; i < 4; i++) {
            if (i != GWSystem.player_curr) {
                BoardPlayerPosGet(i, &sp50);
                BoardModelPosGet(lbl_1_data_310, &sp44);
                PSVECSubtract(&sp50, &sp44, &sp38);
                if (PSVECMag(&sp38) >= lbl_1_rodata_1C0) {
                    BoardModelVisibilitySet(BoardPlayerModelGet(i), 0);
                } else {
                    BoardModelVisibilitySet(BoardPlayerModelGet(i), 1);
                }
            }
        }
    }
}

typedef struct w03UnkStruct5 {
     /* 0x00 */ struct {
        u8 unk00_bit0 : 1;
        u8 unk00_bit1 : 2;
        u8 unk00_bit3 : 1;
        u8 unk00_bit4 : 4;
    };
    /* 0x01 */ char unk_01[3];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
} w03UnkStruct5;

extern omObjData* lbl_1_bss_78;

void fn_1_5838(s32 arg0) {
    Point3d sp18;
    Point3d spC;
    omObjData* obj;
    w03UnkStruct5* temp_r31;

    obj = omAddObjEx(boardObjMan, 0x7E01, 0, 0, -1, &fn_1_5AC8);
    lbl_1_bss_78 = obj;
    temp_r31 = OM_GET_WORK_PTR(obj, w03UnkStruct5);
    temp_r31->unk00_bit0 = 0;
    temp_r31->unk00_bit1 = arg0;
    temp_r31->unk00_bit4 = 1;
    temp_r31->unk00_bit3 = 0;
    switch (GWPlayer[temp_r31->unk00_bit1].diff) {
    case 0:
        temp_r31->unk_08 = (lbl_1_rodata_110 + (lbl_1_rodata_1C4 * BoardRandFloat()));
        break;
    case 1:
        temp_r31->unk_08 = (lbl_1_rodata_1C8 + (lbl_1_rodata_1CC * BoardRandFloat()));
        break;
    case 2:
        temp_r31->unk_08 = (lbl_1_rodata_1D0 + (lbl_1_rodata_1C8 * BoardRandFloat()));
        break;
    case 3:
        temp_r31->unk_08 = lbl_1_rodata_E8;
        break;
    }
    BoardCameraMoveSet(0);
    sp18.x = lbl_1_rodata_E8;
    sp18.y = lbl_1_rodata_17C;
    sp18.z = lbl_1_rodata_E8;
    spC.x = lbl_1_rodata_1D4;
    spC.y = lbl_1_rodata_E8;
    spC.z = lbl_1_rodata_E8;
    BoardCameraMotionStartEx(lbl_1_data_310, &spC, &sp18, 1, 3000.0f, 1);
    BoardModelMotionStart(lbl_1_data_310, 3, 0x40000001U);
    BoardModelMotionStart(lbl_1_data_314, 0, 0U);
    BoardModelMotionSpeedSet(lbl_1_data_314, lbl_1_rodata_1DC);
    fn_1_5C5C(obj, temp_r31);
    BoardCameraMotionWait();
    BoardCameraTargetModelSet(-1);
}

void fn_1_5AC8(omObjData* arg0) {
    s32 temp_r0;
    w03UnkStruct5* temp_r31;

    temp_r31 = OM_GET_WORK_PTR(arg0, w03UnkStruct5);
    if ((temp_r31->unk00_bit0 != 0) || (BoardIsKill() != 0)) {
        lbl_1_bss_78 = NULL;
        omDelObjEx(HuPrcCurrentGet(), arg0);
        if (lbl_1_data_316 != -1) {
            HuWinKill(lbl_1_data_316);
            lbl_1_data_316 = -1;
        }
        return;
    }
    if ((lbl_1_rodata_120 == BoardModelMotionTimeGet(lbl_1_data_310)) || (lbl_1_rodata_198 == BoardModelMotionTimeGet(lbl_1_data_310))) {
        HuAudFXPlay(0x43B);
    }
    switch (temp_r31->unk00_bit4) {
    case 1:
        if (lbl_1_bss_7D != 0) {
            fn_1_629C(2);
            fn_1_62FC();
            BoardCameraTargetModelSet(lbl_1_data_310);
            BoardCameraMoveSet(1);

        }
        break;
    case 2:
        fn_1_5C5C(arg0, (w03UnkStruct5* ) temp_r31);
        break;
    case 3:
        BoardCameraTargetModelSet(-1);
        BoardCameraMoveSet(0);
        temp_r31->unk00_bit0 = 1;
        break;
    }
}

void fn_1_5C5C(omObjData* arg0, w03UnkStruct5* arg1) {
    Mtx sp110;
    Mtx spE0;
    Mtx spB0;
    Mtx sp80;
    Mtx sp50;
    Point3d sp44;
    Point3d sp38;
    Point3d sp2C;
    Point3d sp20;
    Point3d sp14;
    Point3d sp8;
    s16 temp_r3;
    char* temp_r27;
    ModelDataTemp* temp_r30;

    if (((WipeStatGet() == 0) && (arg1->unk00_bit3) || (BoardModelMotionEndCheck(lbl_1_data_314) != 0))) {
        fn_1_629C(3);
        return;
    }
    if ((BoardModelMotionTimeGet(lbl_1_data_314) >= lbl_1_rodata_1E0) && (arg1->unk00_bit3) == 0) {
        WipeColorSet(0, 0, 0);
        WipeCreate(2, 0, -1);
        arg1->unk00_bit3 = 1;
        BoardAudSeqFadeOut(1, 0x3E8);
    }
    sp38.x = arg0->rot.x;
    sp38.y = arg0->rot.y;
    sp38.z = arg0->rot.z;
    temp_r3 = BoardModelIDGet(lbl_1_data_314);
    temp_r30 = &Hu3DData[temp_r3];
    temp_r27 = lbl_1_data_35C[lbl_1_bss_0->unk1];
    Hu3DMotionExec(temp_r3, temp_r30->unk_08, temp_r30->unk_64, 0);
    Hu3DModelObjPosGet(BoardModelIDGet(lbl_1_data_314), temp_r27, &sp44);
    if (lbl_1_rodata_E8 != temp_r30->unk_64) {
        PSVECSubtract(&sp38, &sp44, &sp2C);
    } else {
        sp2C.x = sp2C.y = sp2C.z = lbl_1_rodata_E8;
    }
    arg0->rot.x = sp44.x;
    arg0->rot.y = sp44.y;
    arg0->rot.z = sp44.z;
    fn_1_602C(arg0, arg1);
    sp8 = sp38;
    sp14 = sp44;
    sp20.x = sp20.z = lbl_1_rodata_E8;
    sp20.y = lbl_1_rodata_168;
    BoardMTXCalcLookAt(sp110, &sp14, &sp20, &sp8);
    PSMTXTranspose(sp110, sp110);
    PSMTXRotRad(spE0, 0x7A, lbl_1_rodata_178 * -arg1->unk_04);
    PSMTXTrans(sp50, lbl_1_rodata_E8, lbl_1_rodata_1E4, lbl_1_rodata_E8);
    PSMTXConcat(spE0, sp50, sp50);
    PSMTXConcat(sp110, sp50, sp50);
    PSMTXTrans(sp80, sp44.x, sp44.y, sp44.z);
    PSMTXConcat(sp80, sp50, sp80);
    Hu3DMtxTransGet(sp80, &sp44);
    PSMTXRotRad(spB0, 0x79, (lbl_1_rodata_1E8 * (lbl_1_rodata_100 * (atan2(-sp2C.x, -sp2C.z) / lbl_1_rodata_F8))));
    PSMTXConcat(spB0, spE0, sp110);
    BoardModelMtxSet(lbl_1_data_310, &sp110);
    BoardModelPosSetV(lbl_1_data_310, &sp44);
    BoardCameraRotSet(lbl_1_rodata_1D4, (lbl_1_rodata_100 * (atan2(sp2C.x, sp2C.z) / lbl_1_rodata_F8)));
}

void fn_1_602C(s32 arg0, w03UnkStruct5* arg1) {
    f32 temp_f31 = 0.0f;
    f32 var_f30;
    f32 var_f29;

    if (GWPlayer[arg1->unk00_bit1].com == 0) {
        var_f30 = HuPadStkX[GWPlayer[arg1->unk00_bit1].port];
    } else {
        var_f30 = fn_1_61A4(arg0, arg1);
    }
    temp_f31 = lbl_1_rodata_1F0 * var_f30;
    if (temp_f31 < lbl_1_rodata_E8) {
        var_f29 = -temp_f31;
    } else {
        var_f29 = temp_f31;
    }
    if (var_f29 < lbl_1_rodata_1F4) {
        arg1->unk_04 *= lbl_1_rodata_1F8;
        return;
    }
    BoardDAngleCalcRange(&arg1->unk_04, temp_f31, lbl_1_rodata_168);
}

f32 fn_1_61A4(s32 arg0, w03UnkStruct5* arg1) {
    w03StructUnk3* sp8;
    f32 temp_f31;
    s16 i;
    w03StructUnk2* temp_r29;
    s16 var_r28;
    f32* temp_r31;

    if (lbl_1_bss_74) {
        temp_r29 = OM_GET_WORK_PTR(lbl_1_bss_74, w03StructUnk2);
        sp8 = temp_r29->unk_08;
        var_r28 = temp_r29->unk_03;
    }

    temp_f31 = BoardModelMotionTimeGet(lbl_1_data_314);
    temp_f31 = temp_f31 + arg1->unk_08;

    for (i = 0; i < var_r28; i++) {
        temp_r31 = lbl_1_bss_80[i];
        if ((temp_r31[1] < temp_f31) && (temp_r31[3] > temp_f31)) {
            return lbl_1_rodata_208 * temp_r31[2];
        }    
    }
    return 0.0f;
}

void fn_1_629C(s8 arg0) {
    w03UnkStruct5* temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_78, w03UnkStruct5);
    temp_r31->unk00_bit4 = arg0;
}

s32 fn_1_62D0(void) {
    w03UnkStruct5* temp_r31 = OM_GET_WORK_PTR(lbl_1_bss_78, w03UnkStruct5);
    return temp_r31->unk00_bit4;
}

void fn_1_62FC(void) {
    f32 sp8[2];
    s32 messageID = 0x000D0005;
    f32 temp0;
    f32 temp1;
    
    HuWinMesMaxSizeGet(1, sp8, messageID);
    temp0 = lbl_1_rodata_20C;
    temp1 = lbl_1_rodata_210;
    lbl_1_data_316 = HuWinCreate(temp0, temp1, sp8[0], sp8[1], 0);
    HuWinBGTPLvlSet(lbl_1_data_316, lbl_1_rodata_E8);
    HuWinMesSpeedSet(lbl_1_data_316, 0);
    HuWinMesSet(lbl_1_data_316, messageID);
}
