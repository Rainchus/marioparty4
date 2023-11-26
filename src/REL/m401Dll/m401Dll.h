#include "common.h"
#include "REL/executor.h"

// global data //
typedef struct unkStruct18FC10 {
    s16  unk_00;
    char unk_02[8];
} unkStruct18FC10;
typedef struct unkSubstructBSS114 {
    s16 unk_00[4];
    s16 unk_08[4][3];
    char unk_20[0x30];
    s16 unk_50[4][3];
    s16 unk_68[4][3];
    s16 unk_80[4];
    s16 unk_88[4];
    f32 unk_90[4];
    f32 unk_A0[4];
    char unk_B0[0x80];
    s16 unk_130[4];
    s16 unk_138[4];
} unkSubstructBSS114;
typedef struct unkStructBSS114 {
    char unk_00[0x14];
    void *unk_14;
    char unk_18[0x28];
    s16 *unk_40;
    char unk_44[0x8];
    s32 unk_4C;
    u32 unk_50;
    char unk_54[0x8];
    unkSubstructBSS114 *unk_5C;
} unkStructBSS114;
typedef struct unkStruct18BFC0 {
    char unk_00[0x14];
    Vec3f  unk_14;
} unkStruct18BFC0;
typedef struct unkStruct18C8FC {
    s16  unk_00;
    char unk_02[0x42];
} unkStruct18C8FC;

extern unkStruct18FC10 lbl_8018FC10[];
extern unkStruct18BFC0 lbl_8018BFC0;
extern unkStruct18C8FC lbl_8018C8FC[];

void fn_800240EC(f32, f32, u8, u8, u8);
void fn_8002EF20(s16, s16);
void fn_80032F7C(void);
u8 fn_80041600(void);
void fn_80021228(s16, s32);
void fn_8002F7AC(s32*, unkStructBSS114*);
void fn_8002FB10(void*, f32, f32, f32);
s16 fn_8003F958(s32, s16, s16);
void fn_8003FBA8(s16);
void fn_8003FBEC(s16);
void fn_8003FC30(s16, s16);
void fn_8003FCC0(s16, f32, f32);
void fn_8003FDA8(s16, f32);
void fn_8003FDF0(s16, s8, s8, s8);
void fn_8003FE90(s16, s16);
void fn_8003FED8(s16, s16);
s16 fn_80022ADC(s32*, s32*, s32*);
void fn_80022EB4(s16);
void fn_800240E4(s16);
void fn_800241C0(f32, f32, f32);
void fn_80024348(Vec3f*, Vec3f*, Vec3f*);
void fn_800243AC(f32);
unkStructBSS114* fn_8002F454(void*, s16, s16, s16, s16, void*);
void fn_8002F9C4(void*, s16, s16);
unkStructBSS114* fn_8002FAC0(void*, s16);
s32 fn_80032A94(s32);
void fn_80057E80(unkStruct18FC10*);

// local data //
typedef struct unkStructBSS54 {
    Vec3f unk_00;
} unkStructBSS54;
typedef struct unkStructBSS100 {
    void *unk_00;
    void *unk_04;
} unkStructBSS100;

s16 lbl_2_data_4[8];
s32 lbl_2_data_14;
s32 lbl_2_data_20;
s32 lbl_2_data_2C;
Vec3f lbl_2_data_30;
Vec3f lbl_2_data_3C;
Vec3f lbl_2_data_48;
s32 lbl_2_data_80[8];

unkStruct18FC10* lbl_2_bss_1C;
f32 lbl_2_bss_50;
unkStructBSS54 lbl_2_bss_54;
Vec3f lbl_2_bss_60;
Vec3f lbl_2_bss_6C;
f32 lbl_2_bss_84;
f32 lbl_2_bss_88;
s16 lbl_2_bss_A8;
s16 lbl_2_bss_BA;
s16 lbl_2_bss_BE;
void* lbl_2_bss_C8;
unkStructBSS114* lbl_2_bss_E0;
s32 lbl_2_bss_F4;
void* lbl_2_bss_F8;
void* lbl_2_bss_FC;
unkStructBSS100 lbl_2_bss_100;
unkStructBSS114* lbl_2_bss_108;
unkStructBSS114* lbl_2_bss_10C;
unkStructBSS114* lbl_2_bss_110;
unkStructBSS114* lbl_2_bss_114;
unkStructBSS114* lbl_2_bss_118[];
s32 lbl_2_bss_11C;
s16 lbl_2_bss_120;
f32 lbl_2_bss_124;
f32 lbl_2_bss_128;
f32 lbl_2_bss_12C;

void fn_2_A0(void);
void fn_2_70C(void*);
void fn_2_A10(void);
void fn_2_A98(void);
void fn_2_AEC(s16);
void fn_2_C1C(unkStructBSS114*);
void fn_2_11D0(void*);
void fn_2_2FA4(void*);
void fn_2_3B24(void*);
void fn_2_7CB4(void*);
void fn_2_8E74(void*);
void fn_2_95E4(void*);
void fn_2_9D00(void*);
void fn_2_BD90(void*);
void fn_2_C6DC(void*);
void fn_2_D088(void*);
void fn_2_DBCC(s16);
void fn_2_10710(void);
void fn_2_1041C(void);
s16 fn_2_1079C(void);
s32 fn_2_14640(void*);
