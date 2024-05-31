#include "REL/w02Dll.h"

/* DATA */
extern char lbl_1_data_2A8[0x12];
extern char lbl_1_data_2BA[0x0D];
extern char lbl_1_data_2C8[0x10];

/* RODATA*/
extern f32 lbl_1_rodata_38;
extern f32 lbl_1_rodata_3C;
extern f32 lbl_1_rodata_40;
extern f32 lbl_1_rodata_44;
extern f32 lbl_1_rodata_48;
extern f32 lbl_1_rodata_4C;

/* STRUCTS*/
typedef struct  {
    /* 0x00 */  s16      unk00;
    /* 0x02 */  s16      unk02;
    /* 0x04 */  s32      unk04;
    /* 0x08 */  u8       unk08[0x04];
    /* 0x0C */  Vec      unk0C;
    /* 0x18 */  s16      unk18;
    /* 0x1A */  s16      unk1A;
    /* 0x1C */  u8       unk1C[0x6];
    /* 0x22 */  s16      unk22;
    /* 0x24 */  f32      unk24;
    /* 0x28 */  s16      unk28;
    /* 0x2A */  u8       unk2A[0x2];
    /* 0x2C */  Process* unk2C;
    /* 0x30 */  s16      unk30[3];
    /* 0x36 */  s16      unk36[3];
    /* 0x3C */  omObjData*    unk3C[3];
    /* 0x48 */  s16      unk48[3];
    /* 0x4E */  u8       unk4E[0x2];
    /* 0x50 */  s32      unk50[3];
    /* 0x5C */  u8       unk5C[0x08];
    /* 0x64 */  Vec      unk64;
    /* 0x70 */  Vec      unk70;
    /* 0x7C */  Vec      unk7C;
    /* 0x88 */  s32      unk88[3];
    /* 0x94 */  s16      unk94;
    /* 0x96 */  s16      unk96;
    /* 0x98 */  f32      unk98;
    /* 0x9C */  s16      unk9C;
} unkW02Dice;

typedef struct {
    union {
/* 0x00 */ struct {
        u8 unk7 : 1;
        u8 unk6 : 1;
        u8 unk3 : 3;
        u8 unk1 : 2;
        u8 unk0 : 1;
    };
           u8 unk00;
    };
/* 0x01 */ u8    unk01;
/* 0x02 */ u8    unk02;
/* 0x03 */ u8    unk03;
/* 0x04 */ u16   unk04;
} unkW02DiceBitfields;

/* EXTERN FUNCTIONS */
void fn_1_13D0(void);
void fn_1_1574(unkW02Dice*);                                 /* extern */
void fn_1_1794(unkW02Dice*);                                 /* extern */
void fn_1_1850(omObjData*);                                  /* extern */
void fn_1_2030(unkW02Dice*);                                 /* extern */
void fn_1_2220(unkW02Dice*);                                 /* extern */
s32  fn_1_233C(unkW02Dice*);                                 /* extern */
void fn_1_23B4(unkW02Dice*, s32 i);                          /* extern */
void fn_1_272C(unkW02Dice*);                                 /* extern */

/* LOCAL FUNCTIONS */
void fn_1_1254(unkW02Dice* arg0) {
    Vec sp8;
    s32 i;

    OSReport(lbl_1_data_2A8);
    arg0->unk2C = HuPrcChildCreate(&fn_1_13D0, 0x2005, 0x2000, 0, boardMainProc);
    arg0->unk2C->user_data = arg0;
    arg0->unk94 = 0;
    arg0->unk9C = 0;
    arg0->unk28 = 0;
    Hu3D3Dto2D(&arg0->unk0C, 1, &sp8);

    /* Initialize Matrix */
    arg0->unk64 = arg0->unk70 = arg0->unk7C = sp8;
    arg0->unk7C.y = arg0->unk70.y = arg0->unk64.y = lbl_1_rodata_38;
    arg0->unk7C.z = arg0->unk70.z = arg0->unk64.z = lbl_1_rodata_3C;
    arg0->unk96 = -1;

    for (i = 0; i < 3; i++) {
        arg0->unk3C[i] = 0;
        arg0->unk50[i] = 0;
        arg0->unk30[i] = -1;
        arg0->unk48[i] = -1;
        arg0->unk88[i] = -1;
    }
}

void fn_1_13D0(void) {
    s32 var_r29;
    s32 i;
    s32 var_r30_2;
    unkW02Dice* temp_r31;

    temp_r31 = HuPrcCurrentGet()->user_data;
    temp_r31->unk36[0] = temp_r31->unk36[1] = temp_r31->unk36[2] = 0;
    var_r29 = 0;
    temp_r31->unk96 = 0;
    while (temp_r31->unk96 < temp_r31->unk00) {
        fn_1_1574(temp_r31);
        fn_1_1794(temp_r31);
         while (temp_r31->unk9C == 0) {
            HuPrcVSleep();
         }
         fn_1_2220(temp_r31);
         while (temp_r31->unk9C != 0) {
            HuPrcVSleep();
         }
         temp_r31->unk96 += 1;
    }

    for ( i = 0; i < temp_r31->unk00; i++) {
        var_r29 += temp_r31->unk36[i];
    }
    OSReport(lbl_1_data_2BA, var_r29);

    while (fn_1_233C(temp_r31) == 0) {
        HuPrcVSleep();
    }
    temp_r31->unk94 = (s16) var_r29;
    temp_r31->unk28 = 1;
    if (temp_r31->unk22 != 0) {
        for (i = 0; i < temp_r31->unk00; i++) {
            fn_1_23B4(temp_r31, i);
        }
        temp_r31->unk2C = NULL;
        HuPrcEnd();
    }
    while (TRUE) {
         HuPrcVSleep();
    }
}

void fn_1_1518(unkW02Dice* arg0) {
    OSReport(lbl_1_data_2C8);
    if (arg0->unk2C) {
        HuPrcKill(arg0->unk2C);
    }
    fn_1_2030(arg0);
    fn_1_272C(arg0);
}

void fn_1_1574(unkW02Dice* arg0) {
    Vec sp8;
    f32 temp_f0;
    omObjData* temp_r3;
    s32 temp_r28;
    unkW02DiceBitfields* temp_r29;

    temp_r28 = arg0->unk96;
    arg0->unk30[temp_r28] = BoardModelCreate(arg0->unk04, NULL, 0);
    arg0->unk98 = lbl_1_rodata_40 + BoardRandMod(arg0->unk1A);
    BoardModelMotionStart(arg0->unk30[temp_r28], 0, 0x40000001U);
    BoardModelMotionSpeedSet(arg0->unk30[temp_r28], lbl_1_rodata_44);
    BoardModelMotionTimeSet(arg0->unk30[temp_r28], arg0->unk98);
    temp_r3 = omAddObjEx(boardObjMan, 0x102, 0U, 0U, -1, fn_1_1850);
    temp_r29 = (unkW02DiceBitfields*) temp_r3->work;

    temp_r29->unk7 = 0;
    temp_r29->unk6 = 0;
    temp_r29->unk3 = 0;
    temp_r29->unk1 = temp_r28;

    temp_r29->unk04 = 0;
    temp_r29->unk01 = 3;
    temp_r29->unk02 = 0;
    temp_r3->unk10 = (u32) arg0;
    arg0->unk3C[temp_r28] = temp_r3;
    sp8 = arg0->unk0C;
    sp8.y += (lbl_1_rodata_48 * arg0->unk24);
    temp_r3->trans.x = sp8.x;
    temp_r3->trans.y = sp8.y;
    temp_r3->trans.z = sp8.z;
    temp_r3->scale.x = lbl_1_rodata_44;
    temp_r3->scale.y = lbl_1_rodata_44;
    temp_r3->scale.z = lbl_1_rodata_44;
    sp8.z += lbl_1_rodata_4C;
    HuAudFXPlay(0x302);
}

void fn_1_1794(unkW02Dice* arg0) {
    unkW02DiceBitfields* temp_r30;

    temp_r30 = (unkW02DiceBitfields*) arg0->unk3C[arg0->unk96]->work;
    while (temp_r30->unk3 != 1) {
        HuPrcVSleep();
    }
}

s32 fn_1_17F4(unkW02Dice* arg0) {
    unkW02DiceBitfields* temp;
    if ( arg0->unk96 < 0) {
        return 0;
    }
    temp = (unkW02DiceBitfields*) arg0->unk3C[arg0->unk96]->work;
    if (temp->unk3 != 1) {
        return 0;
    }
    return 1;
}

void fn_1_1F94(unkW02Dice* arg0, s32 arg1) {
    if (arg0->unk30[arg1] != -1) {
        BoardModelKill(arg0->unk30[arg1]);
        arg0->unk30[arg1] = -1;
    }

    if (arg0->unk48[arg1] != -1) {
        Hu3DParManKill(arg0->unk48[arg1]);
        arg0->unk48[arg1] = -1;
        
    }
}