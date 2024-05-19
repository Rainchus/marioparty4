#include "dolphin/types.h"

#include "game/process.h"
#include "game/object.h"

typedef struct _unkSubStruct {
    s32 unk0;
    char unk4[0x20];
    s32 unk24;
    char unk28[0x3C];
    u8 unk64;
    u8 unk65;
    u8 unk66;
    s32 unk68;
    char unk6C[0x4];
} unkSubStruct;

typedef struct _unkSubStruct2 {
    s32 unk0;
    s32 unk4;
    char unk8[0x68];
    s32 unk70;
    s32 unk74;
    s32 unk78;
} unkSubStruct2;

typedef struct _unkStruct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    char unk8[0x4];
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    unkSubStruct *unk20;
    s32 unk24;
    s32 unk28;
    unkSubStruct *unk2C[2];
    unkSubStruct2 *unk34;
    s32 unk38[23];
    s32 unk94;
    Process *unk98;
} unkStruct;

typedef struct _unkStruct2 {
    s32 *unk0;
    s32 unk4;
    s32 unk8;
} unkStruct2;

typedef struct _unkStruct3 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} unkStruct3;

typedef void (*m446Func)(unkStruct *);

// prototypes
extern void ModuleProlog(void);
extern void fn_1_13C(omObjData*);
extern unkStruct* m446FlowCreate(void);
extern void fn_1_3FC(unkStruct*);
extern void fn_1_4B4(unkStruct*);
extern void fn_1_53C(unkStruct*);
extern void fn_1_958(unkStruct*);
extern void fn_1_B78(unkStruct*);
extern void fn_1_C0C(unkStruct*);
extern void fn_1_CA0(unkStruct*);
extern s32 fn_1_17FC(unkStruct*);
extern void fn_1_183C(unkStruct*);
extern void fn_1_1874(unkStruct*);
extern void fn_1_18B0(unkStruct*);
extern void fn_1_19D4(void);