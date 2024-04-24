#ifndef M401DLL_H
#define M401DLL_H

#include "game/object.h"
#include "dolphin.h"

extern float lbl_2_bss_12C;
extern float lbl_2_bss_128;
extern float lbl_2_bss_124;
extern s16 lbl_2_bss_120;

void fn_2_10240(Vec *arg0, Vec *arg1);
void fn_2_1041C(void);
void fn_2_10710(void);

void fn_2_1079C(void);
omObjData *fn_2_14640(Process *objman);

#endif