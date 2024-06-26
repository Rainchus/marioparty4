#include "dolphin.h"
#include "game/object.h"
#include "game/animdata.h"

// types
typedef void (*m409VoidFunc)(void);

typedef struct _unkStruct {
    f32 zoom;
    Vec center;
    Vec rot;
} unkStruct;

typedef struct _unkStruct2 {
    GXColor unk0;
    Vec unk4;
} unkStruct2; // sizeof 0x10

typedef struct _unkStruct3 {
    char unk0[0x2];
    s16 unk2;
    s16 unk4;
    char unk6[0x8];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    f32 unk14;
} unkStruct3;

// bss
extern Process* lbl_1_bss_E8;
extern s16 lbl_1_bss_E4;
extern omObjData* lbl_1_bss_E0;
extern omObjData* lbl_1_bss_DC;
extern unkStruct3 lbl_1_bss_24;
extern s16 lbl_1_bss_16;
extern s8 lbl_1_bss_14;
extern f32 lbl_1_bss_10;
extern f32 lbl_1_bss_C;
extern s8 lbl_1_bss_A;
extern s16 lbl_1_bss_8;
extern s8 lbl_1_bss_6;
extern s16 lbl_1_bss_4;
extern s16 lbl_1_bss_2;
extern s8 lbl_1_bss_0;

// data
extern Vec lbl_1_data_0;
extern Vec lbl_1_data_C;
extern unkStruct2 lbl_1_data_18;
extern Vec lbl_1_data_28;
extern Vec lbl_1_data_34;
extern Vec lbl_1_data_40;
extern unkStruct lbl_1_data_4C[4];
extern u32 lbl_1_data_BC;
extern s32 lbl_1_data_C0;

// prototypes
extern void ModuleProlog(void);
extern void fn_1_434(omObjData* object);
extern void fn_1_4DC(omObjData* object);
extern s8 fn_1_524(void);
extern s8 fn_1_B80(void);
extern void fn_1_DDC(omObjData* object);
extern void fn_1_F70(omObjData* object);
extern s8 fn_1_10E8(omObjData* object);
extern s8 fn_1_1B74(omObjData* object);
extern void fn_1_2098(omObjData* object);
extern void fn_1_2484(omObjData* object);
extern void fn_1_3840(void);
extern f32 fn_1_4120(f32, f32, f32, f32);
extern void fn_1_4FFC(s16, f32, f32, f32, u8);
extern void fn_1_5408(void);
extern void fn_1_55E0(void);
extern void fn_1_67E0(Process*);
extern void fn_1_6900(void);
// ...
extern void fn_1_2414(s32, s32);
extern u16 fn_1_2454(s32);
extern s16 fn_1_5A18(AnimData*, s32, f32, s32, s32);
extern void fn_1_5FBC(s16, m409VoidFunc);
extern void fn_1_5FF4(s16, s32);
extern void fn_1_5F5C(s16);
extern void fn_1_44F0(s16, f32, f32, f32, s32, s32);