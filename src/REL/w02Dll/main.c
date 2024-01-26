#include "dolphin.h"
#include "game/board/model.h"

s16 lbl_1_bss_30[0x10]; // Model List

/* Special Models */
s16 lbl_1_data_280;
s16 lbl_1_data_282;
s16 lbl_1_data_284;
s16 lbl_1_data_286;


void BoardDestroy(void) {
    /* Kill Model List */
    s32 i;
    for (i = 0; i < 0x10; i++) {
        if (lbl_1_bss_30[i] != 0) {
            BoardModelKill(lbl_1_bss_30[i]);
            lbl_1_bss_30[i] = 0;
        }
    }

    /* Kill Special Models */
    if (lbl_1_data_286 != -1) {
        BoardModelKill(lbl_1_data_286);
        lbl_1_data_286 = -1;
    }
    if (lbl_1_data_284 != -1) {
        BoardModelKill(lbl_1_data_284);
        lbl_1_data_284 = -1;
    }
    if (lbl_1_data_280 != -1) {
        BoardModelKill(lbl_1_data_280);
        lbl_1_data_280 = -1;
    }
    if (lbl_1_data_282 != -1) {
        BoardModelKill(lbl_1_data_282);
        lbl_1_data_282 = -1;
    }
    BoardSpaceDestroy();
}

void fn_1_72C(void) {
    s16 var = BoardModelIDGet(lbl_1_data_280);
    Hu3DModelLightInfoSet(var, 1);
}