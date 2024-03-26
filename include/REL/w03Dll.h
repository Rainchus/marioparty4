#include "game/gamework_data.h"
#include "dolphin.h"
#include "REL/executor.h"
#include "game/process.h"
#include "game/window.h"
#include "game/object.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

typedef struct w03StructUnk0 {
/* 0x00 */ Vec unk_00;
/* 0x0C */ Vec unk_0C;
/* 0x18 */ Vec unk_18;
/* 0x24 */ s32 datanum;
} w03StructUnk0;

typedef struct w03UnkStruct2{
    u8 unk0 : 1;
} w03UnkStruct2;

typedef struct w03State {
           s8 unk0;
           u8 unk1;
           u8 unk2;
           s8 unk3;
           u16 unk4;
           u16 unk6;
           s16 unk8;
} w03State;

extern w03State* lbl_1_bss_0;
extern s16 lbl_1_bss_C[14];
