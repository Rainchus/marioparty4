#include "common.h"
#include "math.h"
#include "game/process.h"
#include "game/audio.h"
#include "game/object.h"

extern Process *boardObjMan;

typedef struct bit_copy {
    struct {
        u8 hide : 1;
        u8 field08_bit1 : 1;
        u8 field08_bit2 : 1;
        u8 field08_bit3 : 3;
        u8 field08_bit6 : 1;
        u8 field08_bit7 : 1;
    };
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    u16 unk_04;
    u16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} bitcopy;

void BoardEventLandBlue(s32);
void BoardEventLandRed(s32);
s8 fn_8007FE70(Point3d*, s8);
s32 fn_80080058(s32);
void fn_800800C4(s32);
void fn_80080124(bitcopy*, Vec*);
void fn_80080360(omObjData*);
void fn_800804F8(omObjData*, bitcopy*);
void fn_800806B0(omObjData*, bitcopy*);
void fn_8008094C(omObjData*, bitcopy*);
void fn_80080AF4(omObjData*, bitcopy*);