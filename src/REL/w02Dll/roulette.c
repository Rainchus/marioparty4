#include "REL/w02Dll.h"
#include "game/audio.h"

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
extern f32 lbl_1_rodata_418;
extern f32 lbl_1_rodata_41C;
extern f32 lbl_1_rodata_420;
extern f32 lbl_1_rodata_424;
extern f32 lbl_1_rodata_428;
extern f32 lbl_1_rodata_42C;
extern f32 lbl_1_rodata_430;
extern f32 lbl_1_rodata_434;
extern f32 lbl_1_rodata_438;
extern f32 lbl_1_rodata_43C;
extern f32 lbl_1_rodata_440;
extern f32 lbl_1_rodata_444;
extern f32 lbl_1_rodata_448;
extern f64 lbl_1_rodata_450;
extern f64 lbl_1_rodata_458;
extern f32 lbl_1_rodata_460;
extern f32 lbl_1_rodata_464;
extern f32 lbl_1_rodata_468;
extern f32 lbl_1_rodata_46C;
extern f32 lbl_1_rodata_470;
extern f32 lbl_1_rodata_474;
extern f32 lbl_1_rodata_478;
extern f32 lbl_1_rodata_47C;
extern f64 lbl_1_rodata_480;
extern f64 lbl_1_rodata_488;
extern f32 lbl_1_rodata_490;
extern f32 lbl_1_rodata_494;
extern f64 lbl_1_rodata_498;
extern f64 lbl_1_rodata_4A0;
extern f32 lbl_1_rodata_4A8;
extern f32 lbl_1_rodata_4AC;
extern f32 lbl_1_rodata_4B0;
extern f32 lbl_1_rodata_4B8;
extern f32 lbl_1_rodata_4C0;
extern f32 lbl_1_rodata_4C4;
extern f32 lbl_1_rodata_4C8;
extern f32 lbl_1_rodata_4CC;
extern f64 lbl_1_rodata_4D0;
extern f32 lbl_1_rodata_4D8;
extern f32 lbl_1_rodata_4DC;

/* DATA */
extern s32 lbl_1_data_4D0[];

/* BSS */
extern s32 lbl_1_bss_38C;
extern s16 lbl_1_bss_388;
extern s32 lbl_1_bss_384;
extern f32 lbl_1_bss_380;

//Function Externs
extern s16 BoardBowserSuitModelGet();
extern s16 BoardBowserSuitPlayerModelGet();
extern void BoardComKeySetDown();
extern void BoardComKeySetUp();
extern void omVibrate(s16 player, s16 duration, s16 off, s16 on);
extern u32 frand();

//Local Functions
s32 fn_1_E2AC(void);
void fn_1_E310(f32);

// Unknown Structures
typedef struct UnkPoint {
    f32 unk00;
    Vec point;
} UnkPoint;


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
    
    BoardRollDispSet(0);
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
    BoardRollDispSet(1);
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
                var_r30 = 0x5A; // 90%
                break;
            case BRIBE_CHOICE_10:
                mesg = 0x130005;
                coinAmount = 0xA;
                var_r30 = 0x3C; // 60%
                break;
            case BRIBE_CHOICE_5:
                mesg = 0x130006;
                coinAmount = 5;
                var_r30 = 0x1E; // 30%
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
s32 fn_1_C108(s32 arg0) {
    Vec sp34;
    Vec sp28;
    Vec sp1C;
    UnkPoint spC;


    f32 var_f27;
    f32 var_f26;
    f32 var_f25;
    f32 var_f28;
    f32 var_f29;
    f64 var_f30;
    f32 var_f31;

    s32 var_r26;
    s32 var_r27;
    s16 var_r28;
    s32 var_r30;
    s32 var_r29;
    s32 i;

    if ((s32) frandmod(0x64U) < arg0) {
        s32 temp_r25 = fn_1_E2AC();
        var_r27 = 4;
        var_r29 = frandmod(3U);
        if ((s32) frandmod(0x64U) < 0x14) {
            var_r29 += 1;
        }
        var_r29 = var_r29 + (3 - temp_r25) * 4;
    } else {
        var_r29 = frandmod(0x10U);
        var_r27 = frandmod(4U);
    }
    BoardModelPosGet(lbl_1_bss_30[4], &spC.point);
    BoardCameraViewSet(1);
    BoardCameraMotionWait();
    var_r26 = BoardSpaceFlagSearch(0, 0x800U);
    BoardCameraTargetSpaceSet(var_r26);
    BoardPlayerMotBlendSet(lbl_1_bss_388, 0xB4, 0xF);
    BoardModelRotGet(lbl_1_bss_30[15], &sp34);

    for (i = 0; i < 0xF; i++) {
        sp34.y -= lbl_1_rodata_418;
        BoardModelRotSetV(lbl_1_bss_30[15], &sp34);
        HuPrcVSleep();
    }

    sp34.y = lbl_1_rodata_41C;
    BoardModelRotSetV(lbl_1_bss_30[15], &sp34);
    BoardCameraMotionWait();
    lbl_1_bss_384 = HuAudFXPlay(0x41D);
    var_r28 = -0x1FFF;
    var_f29 = lbl_1_rodata_410;
    for (i = 0; i < 0x3C; i++) {
        var_f29 -= lbl_1_rodata_420;
        fn_1_E310(var_f29);
        var_r28 = (s16) ((f32) (s16) var_r28 + lbl_1_rodata_424);
        HuAudFXPitchSet(lbl_1_bss_384, var_r28);
        HuPrcVSleep();
    }
    
    var_f29 = lbl_1_rodata_428;
    HuAudFXPitchSet(lbl_1_bss_384, 0);
    BoardModelMotionStart(lbl_1_bss_30[15], 2, 0x40000001);
    BoardModelPosGet(lbl_1_bss_30[15], &sp34);

    for (i = 0; i < 0x1E; i++) {
        sp34.z += lbl_1_rodata_42C;
        BoardModelPosSetV(lbl_1_bss_30[15], &sp34);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 1, 0x40000001);
    while (var_r29) {
        fn_1_E310(var_f29);
        HuPrcVSleep();
        var_r29 -= 1;
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 3, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_30[15], lbl_1_rodata_430);
    
    for (i = 0; i < 0xA; i++) {
        sp34.z -= lbl_1_rodata_434;
        BoardModelPosSetV(lbl_1_bss_30[15], &sp34);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }
    BoardModelMotionStart(lbl_1_bss_30[15], 1, 0x40000001);
    BoardModelMotionSpeedSet(lbl_1_bss_30[15], lbl_1_rodata_438);
    HuAudFXPlay(0x41F);
    HuAudFXPlay(0x42D);
    omVibrate(lbl_1_bss_388, 0xC, 6, 6);
    var_f31 = lbl_1_rodata_410;
    var_f27 = lbl_1_rodata_43C;
    sp1C.x = lbl_1_rodata_410;
    sp1C.z = lbl_1_rodata_440;

    // Roulette motion and ball ?
    while(TRUE) {
        sp1C.y = var_f27 - (lbl_1_rodata_444 * (lbl_1_rodata_448 * (var_f31 * var_f31)));
        var_f31 += lbl_1_rodata_438;
        BoardModelPosGet(lbl_1_bss_30[6], &sp28);
        PSVECAdd(&sp28, &sp1C, &sp28);
        var_f28 = (sp28.x - spC.point.x) * (sp28.x - spC.point.x) + ((sp28.z - spC.point.z) * (sp28.z - spC.point.z));
        if (var_f28 > lbl_1_rodata_410) {
            var_f30 = __frsqrte(var_f28);
            var_f30 = lbl_1_rodata_450 * var_f30 * (lbl_1_rodata_458 - ((f64) var_f28 * (var_f30 * var_f30)));
            var_f30 = lbl_1_rodata_450 * var_f30 * (lbl_1_rodata_458 - ((f64) var_f28 * (var_f30 * var_f30)));
            var_f30 = (lbl_1_rodata_450 * var_f30 * (lbl_1_rodata_458 - (var_f28 * (var_f30 * var_f30))));
            spC.unk00 = (var_f28 * var_f30);
            var_f26 = spC.unk00;
        } else {
            var_f26 = var_f28;
        }

        var_f25 = var_f26;
        if (var_f25 >= lbl_1_rodata_460) {
            if (sp28.y <= (lbl_1_rodata_464 + spC.point.y)) {
                PSVECSubtract(&sp28, &spC.point, (Vec* ) &sp1C);
                PSVECNormalize((Vec* ) &sp1C, (Vec* ) &sp1C);
                sp1C.y = lbl_1_rodata_410;
                PSVECScale((Vec* ) &sp1C, (Vec* ) &sp1C, lbl_1_rodata_468);
                PSVECAdd((Vec* ) &sp1C, &spC.point, (Vec* ) &sp1C);
                sp28.x = sp1C.x;
                sp28.z = sp1C.z;
                sp1C.x = lbl_1_rodata_46C;
                sp1C.z = lbl_1_rodata_470;
            }
        }

        if (sp28.y < spC.point.y) {
            sp28.y = spC.point.y;
            if (var_r27 >=  3) {
                break;
            }
            //var_f31 = (lbl_1_rodata_474 * (lbl_1_rodata_418 * (s32) (u8) frand()));
            var_f27 = lbl_1_rodata_418 + (lbl_1_rodata_474 * (lbl_1_rodata_418 * (s32) (u8) frand()));
            var_f31 = lbl_1_rodata_438;
            var_r27 += 1;
            //var_f31 = (lbl_1_rodata_474 * (lbl_1_rodata_47C * (s32) (u8) frand()));
            sp1C.x = lbl_1_rodata_478 + (lbl_1_rodata_474 * (lbl_1_rodata_47C * (s32) (u8) frand()));
            sp1C.z = lbl_1_rodata_478 + (lbl_1_rodata_474 * (lbl_1_rodata_47C * (s32) (u8) frand()));
            HuAudFXPlay(0x41E);
        }
        
        BoardModelPosSetV(lbl_1_bss_30[6], (Vec* ) &sp28);
        fn_1_E310(var_f29);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x41E);
    PSVECSubtract(&sp28, &spC.point, (Vec* ) &sp1C);
    PSVECNormalize((Vec* ) &sp1C, (Vec* ) &sp1C);
    var_f31 = (f32) (lbl_1_rodata_480 * (atan2((f64) -sp1C.z, (f64) sp1C.x) / lbl_1_rodata_488));
    BoardModelRotGet(lbl_1_bss_30[4], &sp34);
    var_f31 = var_f31 - sp34.y;
    if (var_f31 < lbl_1_rodata_410) {
        var_f31 += lbl_1_rodata_490;
    }
    var_r30 = (s32) (var_f31 / lbl_1_rodata_494);
    if (fmod(var_f31, lbl_1_rodata_498) > lbl_1_rodata_4A0) {
        var_r30 += 1;
    }
    if (var_r30 >= 0x10) {
        var_r30 -= 0x10;
    }
    sp1C.y = lbl_1_rodata_410;

    while(TRUE) {
        fn_1_E310(var_f29);
        BoardModelRotGet(lbl_1_bss_30[4], &sp34);
        var_f31 = (lbl_1_rodata_494 * var_r30) + sp34.y; // TODO: Update rodata for asm change
        sp1C.x= cos((lbl_1_rodata_488 * var_f31) / lbl_1_rodata_480);
        sp1C.z = -sin((lbl_1_rodata_488 * var_f31) / lbl_1_rodata_480);
        PSVECScale(&sp1C, &sp1C, lbl_1_rodata_468);
        PSVECAdd(&sp1C, &spC.point, &sp1C);
        sp28.x = sp1C.x;
        sp28.z = sp1C.z;
        BoardModelPosSetV(lbl_1_bss_30[6], &sp28);
        if (sp34.y >= lbl_1_rodata_4A8 &&
            sp34.y < lbl_1_rodata_4AC) {
            break;
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 0x3C; i++) {
        var_f29 += lbl_1_rodata_420;
        fn_1_E310(var_f29);
        BoardModelRotGet(lbl_1_bss_30[4], &sp34);
        var_f31 = (lbl_1_rodata_494 * (f32) var_r30) + sp34.y; // TODO: Update rodata for asm change
        sp1C.x = (f32) cos((lbl_1_rodata_488 * (f64) var_f31) / lbl_1_rodata_480);
        sp1C.z = (f32) -sin((lbl_1_rodata_488 * (f64) var_f31) / lbl_1_rodata_480);
        PSVECScale(&sp1C, &sp1C, lbl_1_rodata_468);
        PSVECAdd((Vec* ) &sp1C, &spC.point, (Vec* ) &sp1C);
        sp28.x = sp1C.x;
        sp28.z = sp1C.z;
        BoardModelPosSetV(lbl_1_bss_30[6], (Vec* ) &sp28);
        var_r28 = var_r28 + lbl_1_rodata_4B0; // TODO: Weird extra rodata
        HuAudFXPitchSet(lbl_1_bss_384, var_r28);
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[4], lbl_1_rodata_410);
    HuAudFXStop(lbl_1_bss_384);
    return lbl_1_data_4D0[var_r30];
}

// Place player on space post roulette?
void fn_1_CD04(s32 arg0) {
    Vec sp24;
    Vec sp18;
    Vec spC;

    f32 temp_f30;
    f32 temp_f29;
    f32 var_f31;
    
    s16 var_r25;
    u32 var_r26;
    s32 var_r27;
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;
    BoardSpace* temp_r31;

    if (arg0 < 0) {
        fn_1_D3AC();
        arg0 = fn_1_D8C4();
    }
    temp_r31 = BoardSpaceGet(0, BoardSpaceFlagSearch(0, 0x800));
    
    for (var_r28 = 0; var_r28 < temp_r31->link_cnt; var_r28++) {
        var_r29 = temp_r31->link[var_r28];
        var_r26 = ( (BoardSpaceFlagGet(0, var_r29) & 0xE) >> 1U);
        if ( var_r26 == (arg0 + 2)) {
            break;
        }
    }
    BoardSpacePosGet(0, var_r29, &sp24);
    BoardModelAttrReset(lbl_1_bss_30[5], 0x40000002);
    HuAudFXPlay(0x420);
    if (BoardPlayerSizeGet(lbl_1_bss_388) == 2) {
        while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < lbl_1_rodata_4C0) {
            HuPrcVSleep();
        }
        BoardPlayerScaleGet(lbl_1_bss_388, &spC);

        while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < lbl_1_rodata_4C4) {
            spC.x -= lbl_1_rodata_448;
            spC.y -= lbl_1_rodata_448;
            //temp_f1 = spC.z;
            spC.z = spC.z - lbl_1_rodata_448;
            BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
            HuPrcVSleep();
        }

        spC.x = spC.y = spC.z = lbl_1_rodata_4C8;
        BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
    }

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < lbl_1_rodata_4C4) {
        HuPrcVSleep();
    }
    if (GWPlayer[lbl_1_bss_388].bowser_suit) {
        BoardModelVisibilitySet(BoardBowserSuitModelGet(), 0);
        BoardModelVisibilitySet(BoardBowserSuitPlayerModelGet(), 0);
    } else {
        BoardModelVisibilitySet(BoardPlayerModelGet(lbl_1_bss_388), 0);
    }
    HuAudFXPlay(0x421);
    omVibrate(lbl_1_bss_388, 0xC, 4, 2);

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < lbl_1_rodata_4CC) {
        HuPrcVSleep();
    }

    BoardModelPosGet(lbl_1_bss_30[5], &sp18);
    temp_f30 = (f32) ((lbl_1_rodata_480 * (atan2(sp24.x - sp18.x, sp24.z - sp18.z) / lbl_1_rodata_488)) / lbl_1_rodata_4D0);

    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < lbl_1_rodata_408) {
        BoardModelRotYSet(lbl_1_bss_30[5], temp_f30 + BoardModelRotYGet(lbl_1_bss_30[5]));
        HuPrcVSleep();
    }
    BoardModelRotYSet(lbl_1_bss_30[5], (f32) (lbl_1_rodata_480 * (atan2(sp24.x - sp18.x, sp24.z - sp18.z) / lbl_1_rodata_488)));
    omVibrate(lbl_1_bss_388, 0xC, 4, 2);
    if (GWPlayer[lbl_1_bss_388].bowser_suit) {

        BoardModelVisibilitySet(BoardBowserSuitModelGet(),1);
        BoardModelVisibilitySet(BoardBowserSuitPlayerModelGet(),1);
    } else {
        BoardModelVisibilitySet(BoardPlayerModelGet(lbl_1_bss_388), 1);
    }
    GWPlayer[lbl_1_bss_388].space_curr =(s16) var_r29;
    BoardPlayerPosSetV(lbl_1_bss_388, &sp24);
    temp_r31 = BoardSpaceGet(0, var_r29);
    
    for ( var_r30 = 0; var_r30 < (s32) temp_r31->link_cnt; var_r30++) {
        if (BoardSpaceTypeGet(0, temp_r31->link[var_r30])) {
            break;
        }
    }

    if (var_r30 != (s32) temp_r31->link_cnt) {
        BoardSpacePosGet(0, temp_r31->link[var_r30], &sp18);
        BoardPlayerRotYSet(lbl_1_bss_388, (f32) (lbl_1_rodata_480 * (atan2(sp18.x - sp24.x, sp18.z - sp24.z) / lbl_1_rodata_488)));
    }
    if (BoardPlayerSizeGet(lbl_1_bss_388) == 2) {
        var_f31 = spC.x;

        while (var_f31 < lbl_1_rodata_4DC) {
            var_f31 += lbl_1_rodata_4D8;
            if (var_f31 > lbl_1_rodata_4DC) {
                var_f31 = lbl_1_rodata_4DC;
            }
            spC.z = var_f31;
            spC.y = var_f31;
            spC.x = var_f31;
            BoardPlayerScaleSetV(lbl_1_bss_388, &spC);
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x42A);
    while (BoardModelMotionTimeGet(lbl_1_bss_30[5]) < BoardModelMotionMaxTimeGet(lbl_1_bss_30[5])) {
        HuPrcVSleep();
    }
    HuPrcCreate(&fn_1_DF48, 0x2004, 0x1000, 0);
}

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
