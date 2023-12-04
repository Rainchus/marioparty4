#include "common.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef struct unkw10Dll {
    Vec unk0;
    Vec unk0C;
    Vec unk18;
    s32 unk24;
} unkw10Dll; //sizeof 0x28

typedef struct w10DllUnk01 {
    u8 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} w10DllUnk01; //sizeof ?

typedef struct m456DllUnk02 {
    char unk00[0x5C];
    w10DllUnk01* unk5C;
} m456DllUnk02; //sizeof ?

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

extern s16 lbl_1_bss_20;
extern s16 lbl_1_bss_22[];
extern s16 lbl_1_bss_20;
extern s32 lbl_801A52E8;

void fn_1_C10(s16);
void fn_1_1FB0(void);
void fn_1_1E3C(s16, s16, s16);
void fn_1_BA0(s32);
void fn_1_C20(void);
void fn_1_6D8(void);
void fn_1_E0(void);
void fn_1_1D68(void);
void fn_1_1DEC(void);
void fn_1_AEC(void);
int fn_1_1AAC(s16, s32);
void fn_1_8C0(void);
void fn_1_904(void);
void fn_1_908(void);
s32 fn_1_90C(void);
void fn_1_91C(void);
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
extern Vec lbl_1_data_80[];
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
extern s32 lbl_1_data_6C[2];