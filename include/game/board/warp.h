#include "common.h"
#include "game/process.h"
#include "game/wipe.h"
#include "math.h"

Vec lbl_801A4AC0;

s8 lbl_801D4038;
s8 lbl_801D4037;
s8 lbl_801D4036;
s16 lbl_801D4034;
f32 lbl_801D4030;
f32 lbl_801D402C;
Process* lbl_801D4028;

s16 lbl_801D3748 = 0xFFFF;
s16 lbl_801D374A = 0xFFFF;
s8 lbl_801D374C[4] = {-1, -1, -1, -1};
char lbl_801D3750[] = "warp01";

void fn_80080D54(s32);
void fn_80080DF8(void);
void fn_80081048(void);
void fn_800810A4(s32);
void fn_800811BC(s32);
void fn_80081278(s32);
void fn_80081428(s32);
void fn_800814CC(s32);