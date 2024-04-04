#ifndef REL_W06_H
#define REL_W06_H

#include "dolphin/types.h"

enum {
    MAPOBJ_MAX = 6
};

extern void fn_1_D70(void);
extern void fn_1_F6C(void);
extern void fn_1_1054(void); // return s32?

extern void fn_1_4878(void);
extern void fn_1_4A10(void);
extern void fn_1_4A60(void); // return s32?

extern void fn_1_6EF0(void); // return s32?

extern void fn_1_7BB0(void);
extern void fn_1_7F3C(void);
extern void fn_1_8264(s32 arg0, s16 arg1);

extern void fn_1_8F20(void);
extern void fn_1_91D8(void);
extern void fn_1_9294(s32 arg0, s32 arg1);
extern s32 fn_1_92D8(s32 arg0, s32 arg1);
extern void fn_1_C108(s32 arg0);
extern void fn_1_C2B4(void);
extern void fn_1_CC90(void);
extern void fn_1_CD0C(void);

extern s16 lbl_1_bss_C[MAPOBJ_MAX];
extern void *lbl_1_bss_0;

#endif
