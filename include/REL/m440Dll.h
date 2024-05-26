#include "dolphin/types.h"

#include "game/object.h"

////// TYPES //////
typedef struct _unkStruct {
    f32 zoom;
    Vec center;
    Vec rot;
} unkStruct;

typedef struct _unkStruct2 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
} unkStruct2;

////// BSS //////
// object.c
extern omObjData* lbl_1_bss_C0[4];
// main.c
extern omObjData* lbl_1_bss_6C;
extern omObjData* lbl_1_bss_68;
extern void* lbl_1_bss_64;
extern s16 lbl_1_bss_10[10];
extern s16 lbl_1_bss_E;
extern u8 lbl_1_bss_B;
extern u8 lbl_1_bss_A;
extern s16 lbl_1_bss_8;
extern s16 lbl_1_bss_6;
extern s16 lbl_1_bss_4;
extern s8 lbl_1_bss_2;
extern s8 lbl_1_bss_0;

////// DATA //////
// main.c
extern Vec lbl_1_data_2C;
extern Vec lbl_1_data_38;
extern GXColor lbl_1_data_44;
extern Vec lbl_1_data_54;
extern Vec lbl_1_data_60;
extern Vec lbl_1_data_6C;
extern unkStruct lbl_1_data_78[3];

////// FUNCTIONS //////
// main.c
extern void ModuleProlog(void);
extern void fn_1_3C4(omObjData* object);
extern void fn_1_434(omObjData* object);
extern s32 fn_1_4A4(void);
extern s32 fn_1_6C8(void);
extern void fn_1_8F0(omObjData* object);
extern void fn_1_AE0(omObjData* object);
extern s32 fn_1_E14(omObjData* object);
// ...
extern f32 fn_1_93C0(f32, f32, f32);