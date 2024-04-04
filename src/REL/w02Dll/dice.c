#include "REL/w02Dll.h"

void fn_1_13D0();

/* DATA */
extern char lbl_1_data_2A8[0x12];

/* RODATA*/
extern f32 lbl_1_rodata_38;
extern f32 lbl_1_rodata_3C;

/* STRUCTS*/
typedef struct  {
    /* 0x00 */  u8       unk00[0x0C];
    /* 0x0C */  Vec      unk0C;
    /* 0x18 */  u8       unk18[0x10];
    /* 0x28 */  s16      unk28;
    /* 0x2A */  u8       unk2A[0x2];
    /* 0x2C */  Process* unk2C;
    /* 0x30 */  s16      unk30[3];
    /* 0x36 */  u8       unk36[0x6];
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