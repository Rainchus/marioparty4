#include "dolphin.h"
#include "game/process.h"
#include "game/gamework_data.h"
#include "game/board/model.h"
#include "game/board/space.h"
#include "game/board/main.h"
#include "game/board/window.h"

// Temporary defines
#define MINI_MUSHROOM         0x0
#define MEGA_MUSHROOM         0x1
#define SUPER_MINI_MUSHROOM   0x2
#define SUPER_MEGA_MUSHROOM   0x3
#define MINI_MEGA_HAMMER      0x4
#define WARP_PIPE             0x5
#define SWAP_CARD             0x6
#define SPARKY_STICKER        0x7 
#define GADDLIGHT             0x8  
#define CHOMP_CALL            0x9
#define BOWSER_SUIT           0xA
#define BOOS_CRYSTAL_BALL     0xB
#define MAGIC_LAMP            0xC
#define ITEM_BAG              0xD
#define TOTAL_ITEMS           0xE
#define NO_ITEM               -1

/* BSS */
s16 lbl_1_bss_8[3]; // Item List
s16 lbl_1_bss_30[0x10]; // Model List

/* DATA */
// Special Models
s16 lbl_1_data_280;
s16 lbl_1_data_282;
s16 lbl_1_data_284;
s16 lbl_1_data_286;

/* RODATA */
f32 lbl_1_rodata_14;
f32 lbl_1_rodata_1C;
f32 lbl_1_rodata_20;
f32 lbl_1_rodata_24;
f32 lbl_1_rodata_28;
f32 lbl_1_rodata_2C;
f32 lbl_1_rodata_30;


/* Functions */
//Actual externs
extern void BoardMusStart(s32, s32, s32, s32);
extern void BoardAudSeqPause(s32, s32, s32);
s8 BoardComPreferItemCheck(s32, s8, s8, s8);
extern void BoardComKeySetLeft();
extern void BoardComKeySetRight();
extern u32 frand();
extern u32 frandmod(u32);

// Local incomplete functions
void fn_1_394C(s32);
void fn_1_3BF4();
void fn_1_39F4();
void fn_1_5CF8();
void fn_1_5D28();
void fn_1_5F90(); 
void fn_1_79BC(s16* itemList);
void fn_1_8244(s32);
void fn_1_93C8(s32 spaceFlag);
void fn_1_E41C();

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

void fn_1_990(void) {
    Vec rotation;
    Vec offset;
    Vec boardSpacePos;

    s32 textChoice;
    s32 currPlayer;
    s32 currSpace;
    s32 spaceLinkFlag;


    currPlayer = GWSystem.player_curr;
    BoardWinCreateChoice(2, 0x130011U, 4, 0);
    if (GWPlayer[currPlayer].com) {
        if ((s32) (frand() & 1) != 0) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    textChoice = BoardWinChoiceGet();
    if ((textChoice == 1) || (textChoice == -1)) {
        BoardWinCreate(2, 0x130012U, 4);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        return;
    }
    BoardAudSeqPause(0, 1, 0x3E8);
    HuPrcChildCreate(fn_1_954, 0x2003U, 0x1000U, 0, boardMainProc);
    rotation.x = lbl_1_rodata_14;
    rotation.y = rotation.z = lbl_1_rodata_14;
    offset.y = lbl_1_rodata_1C;
    offset.x = offset.z = lbl_1_rodata_14;
    BoardCameraMotionStartEx(lbl_1_bss_30[8], &rotation, &offset, lbl_1_rodata_20, lbl_1_rodata_24, 0x15);
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceLinkFlag = BoardSpaceLinkFlagSearch(0, currSpace, 0x02000000U);
    BoardSpacePosGet(0, spaceLinkFlag, &boardSpacePos);
    BoardPlayerMoveBetween(currPlayer, currSpace, spaceLinkFlag);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(currPlayer, 1, 0x40000001);
    fn_1_3BF4();

    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart(currPlayer, 1, 0x40000001);
}

void fn_1_C50(void) {
    Vec rotation;
    Vec offset;
    s32 currSpace;
    s32 spaceLinkFlags;
    s32 textChoice;
    s32 currPlayer;
    s32 i, j;

    currPlayer = GWSystem.player_curr;
    if (BoardPlayerItemCount((s32) currPlayer) == 3) {
        BoardWinCreate(2, 0x13001A, 4);
        BoardWinWait();
        BoardWinKill();
        HuPrcEnd();
    }
    BoardCameraTargetModelSet(lbl_1_bss_30[10]);
    BoardCameraMotionWait();

    /* Generate three random unique items where
       the first item is MINI_MUSHROOM and the
       other two are not BOWSER_SUIT or ITEM_BAG.
    */
    lbl_1_bss_8[0] = MINI_MUSHROOM;
    for (i = 1; i < 3;) {
        lbl_1_bss_8[i] = frandmod(TOTAL_ITEMS);
        if (lbl_1_bss_8[i] != BOWSER_SUIT && lbl_1_bss_8[i] != ITEM_BAG) {
            for (j = 0; j < i; j++) {
                if (lbl_1_bss_8[i] == lbl_1_bss_8[j]) {
                    lbl_1_bss_8[i] = NO_ITEM;
                }
            }
            if (lbl_1_bss_8[i] != NO_ITEM) {
                i++;
            } 
        }
    }
    fn_1_79BC(lbl_1_bss_8);

    HuAudFXPlay(0x43);
    BoardWinCreateChoice(2, 0x130016, 4, 0);
    if (GWPlayer[currPlayer].com) {
        if (BoardComPreferItemCheck(currPlayer, lbl_1_bss_8[0], lbl_1_bss_8[1], lbl_1_bss_8[2]) != -1) {
            BoardComKeySetLeft();
        } else {
            BoardComKeySetRight();
        }
    }
    BoardWinWait();
    BoardWinKill();
    textChoice = BoardWinChoiceGet();
    if ((textChoice == 1) || (textChoice == -1)) {
        HuAudFXPlay(0x44);
        BoardWinCreate(2, 0x130017, 4);
        BoardWinWait();
        BoardWinKill();
        BoardMGExit();
        fn_1_8244(1);
        while (BoardMGDoneFlagGet() != 1) {
            HuPrcVSleep();
        }
        BoardMGDoneFlagSet(0);
        fn_1_5F90();
        HuPrcEnd();
    }
    rotation.x = lbl_1_rodata_28;
    rotation.y = rotation.z = lbl_1_rodata_14;
    offset.x = lbl_1_rodata_14;
    offset.y = lbl_1_rodata_14;
    offset.z = lbl_1_rodata_2C;
    BoardCameraMotionStartEx(lbl_1_bss_30[10], (Point3d* ) &rotation, (Point3d* ) &offset, lbl_1_rodata_30, lbl_1_rodata_24, 0x15);
    currSpace = GWPlayer[currPlayer].space_curr;
    spaceLinkFlags = BoardSpaceLinkFlagSearch(0, currSpace, 0x02000000U);
    BoardPlayerMoveBetween(currPlayer, currSpace, spaceLinkFlags);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    BoardPlayerMotionStart((s32) currPlayer, 1, 0x40000001);
    BoardPlayerMotBlendSet(currPlayer, 0xB4, 0xF);
    while (BoardPlayerMotBlendCheck(currPlayer) == 0) {
        HuPrcVSleep();
    }
    BoardCameraMotionWait();
    fn_1_5D28();
    while (BoardEventFlagGet() != 0) {
        HuPrcVSleep();
    }
    fn_1_8244(0);
    while (GWPlayer[currPlayer].moving) {
        HuPrcVSleep();
    }
    fn_1_5F90();
    BoardPlayerMotionStart((s32) currPlayer, 1, 0x40000001);
    HuPrcEnd();
}