#include "REL/w02Dll.h"


#define ROULETTE_CHOICE_YES 0
#define ROULETTE_CHOICE_NO  1
#define ROULETTE_CHOICE_MAP 2
 
#define BRIBE_CHOICE_20       0
#define BRIBE_CHOICE_10       1
#define BRIBE_CHOICE_5        2
#define BRIBE_CHOICE_NVM      3
#define BRIBE_CHOICE_INVALID -1

/* RODATA */
extern f32 lbl_1_rodata_408;
extern f32 lbl_1_rodata_40C;
extern f32 lbl_1_rodata_410;
extern f32 lbl_1_rodata_414;
extern f32 lbl_1_rodata_490;

/* BSS */
extern s32 lbl_1_bss_38C;
extern s16 lbl_1_bss_388;
extern f32 lbl_1_bss_380;

//Function Externs
extern void BoardComKeySetDown();
extern void BoardComKeySetUp();


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

s32 fn_1_BE74(void) {
    lbl_1_bss_38C = 0;
}

s32 fn_1_BE88(void) {
    s32 coinAmount;
    s32 var_r30;
    s16 playerCoinRegion;
    s32 bribeChoice;
    s32 i;
    s32 rouletteChoice;
    s32 mesg;

    var_r30 = -1;
    coinAmount = BoardPlayerCoinsGet((s32) lbl_1_bss_388);
    if (coinAmount < 5) {
        return var_r30;
    }
    fn_1_121C(0x130002);

    do {
        BoardWinCreateChoice(2, 0x13001DU, 4, 0);
        /* COM has 50% to bribe goomba */
        if (GWPlayer[lbl_1_bss_388].com) {
            if (frand() & 1) {
                BoardComKeySetRight();
            } else {
                BoardComKeySetLeft();
            }
        }
        BoardWinWait();
        BoardWinKill();
        rouletteChoice = BoardWinChoiceGet();
        // If chose to play roulette
        if (rouletteChoice == ROULETTE_CHOICE_YES) {
            BoardWinCreateChoice(1, 0x130003U, 4, 0);
            playerCoinRegion = 3;
            if (coinAmount < 0x14) {
                BoardWinChoiceDisable(0);
                playerCoinRegion--;
            }
            if (coinAmount < 0xA) {
                BoardWinChoiceDisable(1);
                playerCoinRegion--;
            }
            /* COM always bribes max unless it has 20 or
               more coins. Then 50% max, 50% 10 coin bribe. */
            if (GWPlayer[lbl_1_bss_388].com) {
                if (playerCoinRegion < 2) {
                    BoardComKeySetUp();
                } else if (frand() & 1) {
                    BoardComKeySetUp();
                } else {
                    BoardComKeySetDown();
                }
            }
            BoardWinWait();
            BoardWinKill();
            bribeChoice = BoardWinChoiceGet();
            if (bribeChoice == BRIBE_CHOICE_INVALID || 
                bribeChoice == BRIBE_CHOICE_NVM) {
                continue;
            }

            // Coin amount is now the bribe amount in coins
            switch (bribeChoice) {
            case BRIBE_CHOICE_20:
                mesg = 0x130004;
                coinAmount = 0x14;
                var_r30 = 0x5A;
                break;
            case BRIBE_CHOICE_10:
                mesg = 0x130005;
                coinAmount = 0xA;
                var_r30 = 0x3C;
                break;
            case BRIBE_CHOICE_5:
                mesg = 0x130006;
                coinAmount = 5;
                var_r30 = 0x1E;
                break;
            }
            fn_1_121C(mesg);

            
            for (i = 0; i < coinAmount; i++) {
                BoardPlayerCoinsAdd(lbl_1_bss_388, -1);
                HuAudFXPlay(0xE);
                HuPrcSleep(6);
            }
            HuAudFXPlay(0xF);
        // If chose to view map
        } else if (rouletteChoice == ROULETTE_CHOICE_MAP) {
            BoardViewMapExec(lbl_1_bss_388);
        }
    } while (rouletteChoice == ROULETTE_CHOICE_MAP); // While viewing map
    if (var_r30 == -1) {
        fn_1_121C(0x130007);
    }
    return var_r30;
}

// https://decomp.me/scratch/rctvo
// fn_1_C108 (98.34%)

/* Rotate (yaw) of model 4 */
void fn_1_E310(f32 degrees) {
    Point3d spC;
    lbl_1_bss_380 += degrees;
    if (lbl_1_bss_380 >= lbl_1_rodata_490) {
        lbl_1_bss_380 -= lbl_1_rodata_490;
    }
    if (lbl_1_bss_380 < lbl_1_rodata_410) {
        lbl_1_bss_380 += lbl_1_rodata_490;
    }
    BoardModelRotGet(lbl_1_bss_30[4], &spC);
    spC.y = lbl_1_bss_380;
    BoardModelRotSetV(lbl_1_bss_30[4], &spC);
}