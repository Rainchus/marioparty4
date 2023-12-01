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
    char unk_B0[0x10];
    f32 unk_C0[4];
    f32 unk_D0[4];
    f32 unk_E0[4];
    f32 unk_F0[4];
    f32 unk_100[4];
    f32 unk_110[4];
    f32 unk_120[4];
    s16 unk_130[4];
    s16 unk_138[4];
    s16 unk_140[4];
} unkSubstructBSS114;
typedef struct unkStructBSS114 {
    char unk_00[4];
    s32 unk_04;
    char unk_08[0xC];
    void *unk_14;
    Vec3f unk_18;
    char unk_24[0x1C];
    unkSubstructBSS114 *unk_40;
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
extern s16 lbl_801D3CC2;

void fn_80021228(s16, s32);
unkStructBSS114* fn_80021444(s16, s32);
void fn_800240EC(f32, f32, u8, u8, u8);
void fn_8002EF20(s16, s16);
unkStructBSS114* fn_8002F454(void*, s16, s16, s16, s16, void*);
void fn_8002F7AC(s32*, unkStructBSS114*);
void fn_8002FB10(void*, f32, f32, f32);
void fn_8002FB20(unkStructBSS114*, f32, f32, f32);
void fn_8002FB30(unkStructBSS114*, f32, f32, f32);
u8 fn_800325F4(void);
void fn_80032BC4(s32);
s32 fn_80032EAC(s32, Vec3f*);
void fn_80032F7C(void);
void fn_80033140(s32, s32);
s16 fn_80035794(s32, ...);
s16 fn_8003F958(s32, s16, s16);
void fn_8003FBA8(s16);
void fn_8003FBEC(s16);
void fn_8003FC30(s16, s16);
void fn_8003FCC0(s16, f32, f32);
void fn_8003FDA8(s16, f32);
void fn_8003FDF0(s16, s8, s8, s8);
void fn_8003FE90(s16, s16);
void fn_8003FED8(s16, s16);
void fn_800414AC(s16, s16, s16);
u8 fn_80041600(void);
s16 fn_80022ADC(Vec3f*, Vec3f*, s32*);
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

extern f32 lbl_2_data_0 = -7.1875f;
extern s16 lbl_2_data_4[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
extern Vec3f lbl_2_data_14 = { 1500.0f, 2500.0f, 1500.0f };
extern Vec3f lbl_2_data_20 = { 0.0f, -1.0f, 0.0f };
extern s32 lbl_2_data_2C = -1;
extern Vec3f lbl_2_data_30 = { 0.0f, 2500.0f, 0.0f };
extern Vec3f lbl_2_data_3C = { 0.0f, 1.0f, -1.0f };
extern Vec3f lbl_2_data_48 = { 0.0f, 0.0f, 0.0f };
extern char lbl_2_data_6F[] = "winnercnt:%d";
extern s32 lbl_2_data_80[8] = { 0x610000, 0x610001, 0x610002, 0x610003, 0x610004, 0x610005, 0x610006, 0x610007 };
extern s32 lbl_2_data_124[5];

extern f32 lbl_2_bss_10;
extern unkStruct18FC10* lbl_2_bss_1C;
extern f32 lbl_2_bss_50;
extern unkStructBSS54 lbl_2_bss_54;
extern Vec3f lbl_2_bss_60;
extern Vec3f lbl_2_bss_6C;
extern f32 lbl_2_bss_84;
extern f32 lbl_2_bss_88;
extern s32 lbl_2_bss_90;
extern s32 lbl_2_bss_A4;
extern s16 lbl_2_bss_A8;
extern s16 lbl_2_bss_AA[];
extern s16 lbl_2_bss_B2[];
extern s16 lbl_2_bss_BA;
extern s16 lbl_2_bss_BE;
extern s16 lbl_2_bss_C0;
extern void* lbl_2_bss_C8;
extern s32 lbl_2_bss_D0;
extern unkStructBSS114* lbl_2_bss_E0;
extern s32 lbl_2_bss_F4;
extern void* lbl_2_bss_F8;
extern void* lbl_2_bss_FC;
extern unkStructBSS100 lbl_2_bss_100;
extern unkStructBSS114* lbl_2_bss_108;
extern unkStructBSS114* lbl_2_bss_10C;
extern unkStructBSS114* lbl_2_bss_110;
extern unkStructBSS114* lbl_2_bss_114;
extern unkStructBSS114** lbl_2_bss_118;
extern s32 lbl_2_bss_11C;
extern s16 lbl_2_bss_120;
extern f32 lbl_2_bss_124;
extern f32 lbl_2_bss_128;
extern f32 lbl_2_bss_12C;

void fn_2_A0(void);
void fn_2_70C(unkStructBSS114*);
void fn_2_A10(void);
void fn_2_A98(void);
void fn_2_AEC(s16);
void fn_2_C1C(unkStructBSS114*);
void fn_2_11D0(unkStructBSS114*);
void fn_2_15C4(s16);
void fn_2_169C(s16);
void fn_2_1858(s16, s16);
void fn_2_1A38(unkStructBSS114*);
void fn_2_1B80(unkStructBSS114*);
void fn_2_1CF0(unkStructBSS114*);
void fn_2_2FA4(void*);
void fn_2_3B24(void*);
void fn_2_48A0(void*);
void fn_2_7CB4(void*);
void fn_2_8E74(void*);
void fn_2_95E4(void*);
void fn_2_91AC(void*, Vec3f*);
void fn_2_9D00(void*);
void fn_2_BD90(void*);
void fn_2_C6DC(void*);
void fn_2_C130(void);
void fn_2_D088(void*);
void fn_2_DBCC(s16);
void fn_2_E6BC(s32, f32, f32, f32, f32, f32);
unkStructBSS114* fn_2_FC40(s32, Vec3f*, Vec3f*, Vec3f*);
void fn_2_10240(Vec3f*, Vec3f*);
void fn_2_1041C(void);
s32 fn_2_14640(void*);
void fn_2_10710(void);
s16 fn_2_1079C(void);
s32 fn_2_10A88(Vec3f*, s16);
