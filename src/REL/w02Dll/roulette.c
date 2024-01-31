#include "REL/w02Dll.h"


/* RODATA */
extern f32 lbl_1_rodata_408;
extern f32 lbl_1_rodata_40C;
extern f32 lbl_1_rodata_410;
extern f32 lbl_1_rodata_414;

/* BSS */
extern s16 lbl_1_bss_388;


/* FUNCTIONS */
void fn_1_BC1C(void) {
    Point3d sp8;

    BoardModelPosGet(lbl_1_bss_30[15], &sp8);
    sp8.z -= lbl_1_rodata_408;
    sp8.y += lbl_1_rodata_40C;
    BoardModelPosSetV(lbl_1_bss_30[6], &sp8);
    BoardModelAttrSet(lbl_1_bss_30[5], 0x40000002);
    BoardModelMotionTimeSet(lbl_1_bss_30[5], lbl_1_rodata_410);
    BoardModelRotGet(lbl_1_bss_30[15], &sp8);
    sp8.y = lbl_1_rodata_410;
    BoardModelRotSetV(lbl_1_bss_30[15], &sp8);
}

void fn_1_BCFC(void) {
    s32 spaceLinkFlags;
    s32 temp_r30;
    s32 temp_r29;
    
    BoardDiceDigit2DShowSet(0);
    spaceLinkFlags = BoardSpaceLinkFlagSearch(0, (s32) GWPlayer[lbl_1_bss_388].space_curr, 2U);
    BoardPlayerMoveToAsync(lbl_1_bss_388, spaceLinkFlags);
    while (GWPlayer[lbl_1_bss_388].moving) {
        HuPrcVSleep();
    }
    BoardRotateDiceNumbers((s32) lbl_1_bss_388);
    BoardCameraViewSet(2);
    BoardCameraMotionWait();
    BoardPlayerMotBlendSet((s32) lbl_1_bss_388, 0x5A, 0xF);
    while (BoardPlayerMotBlendCheck((s32) lbl_1_bss_388) == 0) {
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[15], lbl_1_rodata_414);
    fn_1_121C(0x130000);
    HuAudFXPlay(0x44);
    temp_r29 = fn_1_BE88();
    BoardStatusShowSetAll(0);
    fn_1_121C(0x130001);
    temp_r30 = fn_1_C108(temp_r29);
    fn_1_CD04(temp_r30);
    BoardCameraViewSet(1);
    BoardStatusShowSetAll(1);
    BoardCameraMotionWait();
    BoardDiceDigit2DShowSet(1);
    HuPrcKill(NULL);
    while(TRUE) {
      HuPrcVSleep();  
    }
}