#include "REL/w02Dll.h"

/* DATA */
extern char lbl_1_data_2A8[0x12];
extern char lbl_1_data_2BA[0x0D];

/* RODATA*/
extern f32 lbl_1_rodata_38;
extern f32 lbl_1_rodata_3C;

/* STRUCTS*/
typedef struct  {
    /* 0x00 */  s16      unk00;
    /* 0x02 */  u8       unk02[0x0A];
    /* 0x0C */  Vec      unk0C;
    /* 0x18 */  u8       unk18[0xA];
    /* 0x22 */  s16      unk22;
    /* 0x24 */  u8       unk24[0x4];
    /* 0x28 */  s16      unk28;
    /* 0x2A */  u8       unk2A[0x2];
    /* 0x2C */  Process* unk2C;
    /* 0x30 */  s16      unk30[3];
    /* 0x36 */  s16      unk36[3];
    /* 0x3C */  s32      unk3C[3];
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
    /* 0x98 */  s32      unk98;
    /* 0x9C */  s16      unk9C;
} unkW02Dice;

/* EXTERN FUNCTIONS */
void fn_1_13D0(void);
void fn_1_1574(unkW02Dice*);                                 /* extern */
void fn_1_1794(unkW02Dice*);                                 /* extern */
void fn_1_2220(unkW02Dice*);                                 /* extern */
s32  fn_1_233C(unkW02Dice*);                                 /* extern */
void fn_1_23B4(unkW02Dice*, s32 i);                          /* extern */

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