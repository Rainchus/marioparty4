#include "dolphin.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/board/model.h"
#include "game/board/space.h"

/* Data */
s16 lbl_1_bss_30[0x10]; // Model List

// Special Models
s16 lbl_1_data_280;
s16 lbl_1_data_282;
s16 lbl_1_data_284;
s16 lbl_1_data_286;

/* Functions */
//Actual externs
extern void BoardMusStart(s32, s32, s32, s32);

// Local functions
extern void fn_1_394C(s32);
extern void fn_1_39F4();
extern void fn_1_5CF8();
extern void fn_1_93C8(s32);
extern void fn_1_E41C();

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

void fn_1_770(void) {

}

/* Decrement current space's [UNKNOWN] flag */
void fn_1_774(void) {
    u32 unkFlag;
    u32 currPlayer;
    u32 currSpace;
    u32 spaceFlags;
    currPlayer = GWSystem.player_curr;
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceFlags = BoardSpaceFlagGet(0, currSpace);
    //temp_r31 = (temp_r)
    unkFlag = (spaceFlags & 0x1C0) >> 6;
    if (unkFlag != 0) {
        unkFlag--;
        fn_1_93C8(unkFlag);
    }
}

/* Check if can iteract with board object? */
s32 fn_1_800(void) {
    BoardSpace* currSpace;
    s32 currPlayer;
    s32 var_r29;

    currPlayer = GWSystem.player_curr;
    currSpace = BoardSpaceGet(0, GWPlayer[currPlayer].space_curr);
    if ((currSpace->flag & 0x30) != 0) {


        // If mega mushroom state return
        if (BoardPlayerSizeGet(currPlayer) == 2) {
            return 0;
        }
        // If using the bowser suit return
        if (GWPlayer[currPlayer].bowser_suit) {
            return 0;
        }

        if ((currSpace->flag & 0x20) != 0 && (currSpace->flag & 0x10) != 0) {
            var_r29 = 2;
        } else if ((currSpace->flag & 0x20) != 0) {
            var_r29 = 1;
        } else {
            var_r29 = 0;
        }
        fn_1_394C(var_r29);
        return 1;
    }
    if ((currSpace->flag & 1) != 0) {
        fn_1_E41C();
        return 1;
    }
    return 0;
}

void fn_1_92C(void) {
    fn_1_39F4();
    fn_1_5CF8();
}

void fn_1_950(void) {

}

void fn_1_954(void) {
    HuPrcSleep(0x3C);
    BoardMusStart(1, 0x12, 0x7F, 0);
    HuPrcEnd();
}