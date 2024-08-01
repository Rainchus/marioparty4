#include "dolphin.h"

#include "game/object.h"
#include "game/hsfman.h"

// types
typedef struct _unkStruct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    Vec unk10;
    HsfVector2f unk1C;
    Vec unk24;
    f32 unk30;
    f32 unk34;
} unkStruct;

typedef struct _unkStruct2 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC[5];
    s16 unk16[5];
    s16 unk20;
    s32 unk24;
    s32 unk28;
    Vec unk2C;
    Vec unk38;
} unkStruct2; // sizeof 0x44

typedef struct _unkStruct3 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC[6];
    s16 unk18[6];
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    char unk34[0x8];
    s32 unk3C;
    Vec unk40;
    char unk4C[0x8];
    Vec unk54;
    Vec unk60;
    f32 unk6C;
    char unk70[0xC];
    Vec unk7C;
    s8 unk88;
    s8 unk89;
    s8 unk8A;
    s8 unk8B;
    u16 unk8C;
    u16 unk8E;
    char unk90[0x14];
    s32 unkA4;
} unkStruct3; // sizeof 0xA8

typedef struct _unkStruct4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Vec unkC;
} unkStruct4;

// prototypes
void ObjectSetup(void);
void fn_1_6EC(f32, f32, f32, s32);
void fn_1_73C(void);
void fn_1_7BC(void);
void fn_1_894(omObjData* object);
void fn_1_898(omObjData* object);
void fn_1_8BC(void);
f32 fn_1_1D08(f32);
void fn_1_1D88(void);
void fn_1_1DBC(void);
void fn_1_2014(void);
void fn_1_2064(void);
s32 fn_1_2708(void);
f32 fn_1_27C4(s32, f32, f32);
void fn_1_2A1C(void);
void fn_1_3950(void);
s8 fn_1_4BE4(s32, s32);
void fn_1_4C9C(Vec*, f32, f32);
s8 fn_1_4E58(s32, s32);
u8 fn_1_525C(s32, s32);
u16 fn_1_531C(s32);
u16 fn_1_5388(s32);
s32 fn_1_53F4(unkStruct3*, f32, f32, f32);
s32 fn_1_561C(unkStruct3*, s32*);
//...
void fn_1_7C60(void); // *
void fn_1_A01C(ModelData* model, ParticleData* particle, Mtx matrix); // *
void fn_1_A618(ModelData* model, ParticleData* particle, Mtx matrix); // *
void fn_1_AA88(ModelData* model, ParticleData* particle, Mtx matrix); // *
void fn_1_B160(void); // *
void fn_1_B1C0(void); // *