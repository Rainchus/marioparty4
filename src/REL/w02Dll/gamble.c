#include "REL/w02Dll.h"

Process* lbl_1_bss_50;
s32 lbl_1_bss_54;

void fn_1_2D04();


void fn_1_3938(void) {
    lbl_1_bss_50 = NULL;
}


void fn_1_394C(s32 arg0) {
    s32 currPlayer;
    currPlayer = GWSystem.player_curr;

    lbl_1_bss_54 = arg0;
    lbl_1_bss_50 = HuPrcChildCreate(fn_1_2D04, 0x2003U, 0x2000U, 0, boardMainProc);
    HuPrcDestructorSet2(lbl_1_bss_50, fn_1_3938);
    while (lbl_1_bss_50) {
        HuPrcVSleep();
    }
}