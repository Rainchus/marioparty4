#include "common.h"
#include "REL/executor.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);

typedef struct unkw10Dll {
    Vec3f unk0;
    Vec3f unk0C;
    Vec3f unk18;
    s32 unk24;
} unkw10Dll; //sizeof 0x28

typedef struct w10DllUnk01 {
    u8 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} w10DllUnk01; //sizeof ?

typedef struct w10DllUnk02 {
    char unk00[0x5C];
    w10DllUnk01* unk5C;
} w10DllUnk02; //sizeof ?

typedef struct w10DllUnk03 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} w10DllUnk03;

typedef struct w10DllUnk04 {
    s16 unk0;
    s16 unk2;
    void (*unk4)();
} w10DllUnk04;

//this belongs to m456Dll
w10DllUnk02** fn_8002FAC0(Process*, s32);
u8 fn_80041600(void);
s16 HuPadStatGet(s16);
void espDispOn(s16);
void espPosSet(s16, f32, f32);
void espScaleSet(s16, f32, f32);
void fn_1_C10(s16);
void fn_8005D8E8(void); 
void fn_8005DB6C(s16, Vec3f*, s32, f32, f32, s32); 
void fn_8005E0C0(void);
void fn_80074210(s32, s32, Vec3f*);
void fn_8007A360(s32);
void fn_8007F894(void);
void fn_80083F84(void);
void fn_800884F4(s32);
void fn_800A4C88(void);
void fn_800A6B10(void);
extern s16 lbl_1_bss_20;
extern s16 lbl_1_bss_22[];
void espScaleSet(s16, f32, f32);
extern s16 lbl_1_bss_20;
s16 espEntry(s32, s32, s32);
void espDispOff(s16);
void fn_8008853C(s32);
extern s32 lbl_801A52E8;
void fn_800B42B4(s32);
void fn_80082AAC(s32);
void fn_800B4264(s32, s32, s32);
void fn_1_1FB0(void);
void fn_1_1E3C(s16, s16, s16);
void fn_8007500C(s32);
void fn_1_BA0(s32);
void fn_8006F0D4(s32, f32);
f32 fn_8006F128(s32);
f64 fmod(f32, f64);
void fn_1_C20(void);
void fn_8006F61C(s16, s32);
void fn_800B42BC(s16);
void Hu3DModelLightInfoSet(s32, s32);
s32 fn_8006DBD4(s16);
void fn_8005B150(void*, void*);
void fn_1_6D8(void);
void fn_1_E0(void);
void fn_8006F2E8(s32, Vec3f*);
void HuWinMesSet(s16, s32);
void fn_1_1D68(void);
void fn_1_1DEC(void);
void fn_1_AEC(void);
void HuWinKill(s16);
void HuWinPriSet(s16, s32);
void HuWinMesPalSet(s16, s32, s32, s32, s32);
void HuWinMesSpeedSet(s16, s32);
void HuWinMesMaxSizeGet(s32, f32*, ...);
void fn_8005D10C(void*, void*);
s16 fn_8006D9A4(s32, void*, s32);
void fn_8006DB90(s16);
void fn_8006DDE8(s16, f32);
void fn_8006E2B8(s16, s32, s32);
void fn_8006E878(s16, f32);
void fn_8006F158(s16, void*);
void fn_8006F1A8(s16, f32, f32, f32);
s32 fn_8006F220(s16 arg0, Vec3f* arg1);
void fn_8006F50C(s16, s32);
void fn_80073FF4(void*);
void fn_80073FFC(void*);
void fn_80074004(void*);
s32 fn_800745F0(s32, s32);
void fn_800772EC(s32);
void fn_80077A3C(void);
void fn_80077AAC(s16);
void fn_8007A83C(s16);
void fn_80083EDC(s16);
void fn_800A4F6C(s16);
void fn_800B3FD8(void*);
void fn_800B4274(s32, s32);
int fn_1_1AAC(s16, s32);
void fn_1_8C0(void);
void fn_1_904(void);
void fn_1_908(void);
s32 fn_1_90C(void);
void fn_1_91C(void);
void Hu3D2Dto3D(Vec3f*, s32, Vec3f*);
void fn_8005D5C0(Vec3f*);
void fn_8006F338(s16, f32, f32, f32);
s32 fn_8005B6A8(void);
void fn_8006EFBC(s16, Mtx);
void fn_8006F270(s16, f32, f32, f32);
void espKill(s16);
void fn_1_13A4(void);
void fn_1_176C(void);
void fn_1_179C(void);
void fn_1_17F4(void);
void fn_1_1834(void);
void fn_1_18BC(void);
void fn_1_1908(void);
void fn_1_1930(void);
void fn_1_1958(void);
void fn_1_D2C(void);
void fn_1_D54(void);
void fn_1_D7C(void);
void fn_1_DA4(void);
void fn_1_DCC(void);
void fn_1_DF4(void);
void fn_1_E1C(void);
void fn_1_E44(void);
void fn_1_E94(void);
void fn_1_EBC(void);
void fn_1_EE4(void);
void fn_1_EE8(void);
void fn_1_F30(void);
void fn_1_F6C(void);
void fn_1_FB8(void);
void fn_1_1010(void);
void fn_1_105C(void);
void fn_1_1098(void);
void fn_1_10C0(void);
void fn_1_10F8(void);
void fn_1_1134(void);
void fn_1_1178(void);
void fn_1_11A0(void);
void fn_1_11EC(void);
void fn_1_1240(void);
void fn_1_1278(void);
void fn_1_12A0(void);
void fn_1_12DC(void);
void fn_1_1304(void);
void fn_1_132C(void);
void fn_1_1354(void);
void fn_1_137C(void);

extern w10DllUnk04 lbl_1_data_108[42];
extern w10DllUnk03 lbl_1_data_C6[];
extern Vec3f lbl_1_data_80[];
extern Process* lbl_1_bss_18;
extern s16 lbl_1_bss_1C;
extern s16 lbl_1_bss_1E;
extern s32 lbl_1_data_78[2];
extern BoardStateSubStruct* lbl_1_bss_0;
extern s16 lbl_1_bss_10[4]; //could be incorrect size
extern void* lbl_1_bss_8; //unknown type
extern s16 lbl_1_bss_C;
extern s16 lbl_1_bss_E;
extern unkw10Dll lbl_1_data_0[1];
extern s16 lbl_1_bss_22[11];
extern s32 lbl_1_data_2A8[11];
extern s16 lbl_1_data_28;
extern s16 lbl_1_data_2A;
extern s16 lbl_1_data_2C;
extern s16 lbl_1_data_2E;
extern s16 lbl_1_data_30;
extern s16 lbl_1_data_32;
extern s32 lbl_1_data_54[2];
extern s32 lbl_1_data_5C[2];
extern s32 lbl_1_data_64[2];
extern s32 lbl_1_data_6C[3]; //HACK: should be 2
extern BoardState lbl_8018FCF8;