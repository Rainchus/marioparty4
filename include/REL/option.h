#ifndef REL_OPTION_H
#define REL_OPTION_H

#include "game/object.h"

#include "dolphin/types.h"

typedef struct {
    /* 0x00 */ Process *process;
    /* 0x04 */ s16 window;
    /* 0x08 */ s32 id;
    /* 0x0C */ s32 visible;
    /* 0x10 */ BOOL messWaitSignal;
    /* 0x14 */ BOOL choiceSignal;
    /* 0x18 */ u32 messToBeSet;
    /* 0x1C */ s32 choice;
    /* 0x20 */ s32 state; // TODO add defines
} WindowWork; // Size 0x24

void fn_1_160(s16 sprite, BOOL hiddenF, s32 fadeInTime);
BOOL fn_1_550(u16 btn);
BOOL fn_1_584(u16 arg0);
BOOL fn_1_5B8(u16 arg0);

omObjData *fn_1_7F8(void);
void fn_1_A3C(omObjData *object);
void fn_1_A6C(omObjData *object, float x, float y, float z, s32 duration);
void fn_1_AF0(omObjData *object, float x, float y, float z, s32 duration);
void fn_1_B74(omObjData *object, float zoom, float rot, float y, s32 duration);
float fn_1_BF8(omObjData *object);
float fn_1_C28(omObjData *object);
void fn_1_C88(omObjData *object, float *lookingAtX, float *lookingAtY, float *lookingAtZ);
s32 fn_1_CB8(omObjData *object);

omObjData *fn_1_15A4(void);
void fn_1_1798(omObjData *object);
void fn_1_1A2C(omObjData *object, s32 mode);
s32 fn_1_1A70(omObjData *object);

omObjData *fn_1_21F8(void);
void fn_1_241C(omObjData *object);
void fn_1_2508(omObjData *object, float destPos, float distFromCam, s32 walkDuration);

omObjData *fn_1_2E04(void);
void fn_1_2F4C(omObjData *object);

omObjData *fn_1_3158(void);
void fn_1_322C(omObjData *object);
void fn_1_3290(omObjData *object, s32 mode);
s32 fn_1_39D4(omObjData *object);
void fn_1_3D54(omObjData *object);
void fn_1_3E1C(omObjData *object);
BOOL fn_1_3ED0(omObjData *object);

omObjData *fn_1_4028(void);
void fn_1_42DC(omObjData *object);
void fn_1_4388(omObjData *object, s32 arg1);
s32 fn_1_43CC(omObjData *object);

omObjData *fn_1_80E4(void);
void fn_1_825C(omObjData *object);
void fn_1_82B0(omObjData *object, s32 arg1);
s32 fn_1_82F4(omObjData *object);

WindowWork *fn_1_A44C(s32 id);
void fn_1_A6AC(WindowWork *work);
void fn_1_A6EC(WindowWork *work);
void fn_1_A704(WindowWork *work);
void fn_1_A71C(WindowWork *work, s32 mess);
void fn_1_A7B0(WindowWork *work, float x, float y);
void fn_1_A7F0(WindowWork *work);
void fn_1_A828(WindowWork *work);
void fn_1_A880(WindowWork *work, s32 choice);

extern Process *lbl_1_bss_8;
extern omObjData *lbl_1_bss_10;
extern omObjData *lbl_1_bss_18;
extern omObjData *lbl_1_bss_20;
extern omObjData *lbl_1_bss_28;
extern omObjData *lbl_1_bss_30;
extern omObjData *lbl_1_bss_38;
extern omObjData *lbl_1_bss_40;

#endif
