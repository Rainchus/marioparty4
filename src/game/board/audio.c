#include "game/board/audio.h"
#include "game/audio.h"
#include "game/gamework_data.h"
#include "game/msm.h"
#include "game/board/main.h"

static s16 boardSeq[2][2];

static s32 boardFX = -1;

static s16 boardMusTbl[] = {
    0x000D, 0x0011, 0x0015,
    0x001C, 0x0021, 0x0025,
    0x0028, 0x0029, 0x002A
};

void BoardMusStartBoard(void) {
    s16 temp_r31 = boardMusTbl[GWBoardGet()];

    BoardMusStart(0, temp_r31, 0x7F, 0);
    BoardAudFXPlay();
}

void BoardMusStart(s32 arg0, s32 arg1, s8 arg2, u16 arg3) {
    s16 *temp_r31 = boardSeq[arg0];
    MSM_MUSPARAM param;

    if (arg1 == temp_r31[1]) {
        return;
    }
    if (temp_r31[0] != -1) {
        BoardAudSeqFadeOutFast(temp_r31[0]);
    }
    param.flag = MSM_MUSPARAM_CHAN;
    if (arg3 != 0) {
        param.flag |= MSM_MUSPARAM_FADESPEED;
    }
    if (arg2 < 0) {
        param.flag |= MSM_MUSPARAM_VOL;
        arg2 = 0x7F;
    }
    param.fadeSpeed = arg3;
    param.vol = arg2;
    param.chan = arg0;
    temp_r31[0] = msmMusPlay(arg1, &param);
    temp_r31[1] = arg1;
}

void BoardAudSeqFadeOutFast(s32 arg0) {
    BoardAudSeqFadeOut(arg0, 0x64);
}

void BoardAudSeqFadeOut(s32 arg0, u16 arg1) {
    s16 *temp_r31 = boardSeq[arg0];

    if (temp_r31[0] == -1) {
        return;
    }
    HuAudSeqFadeOut(temp_r31[0], arg1);
    temp_r31[1] = temp_r31[0] = -1;
}

void BoardMusLoudSet(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        BoardMusVolPanSet(arg0, 0x60, 0x1F4);
    } else {
        BoardMusVolPanSet(arg0, 0x7F, 0x1F4);
    }
}

void BoardMusVolPanSet(s32 arg0, s8 vol, u16 fadeSpeed) {
    s16 *temp_r31 = boardSeq[arg0];
    MSM_MUSPARAM param;

    if (temp_r31[0] == -1) {
        return;
    }
    param.flag = MSM_MUSPARAM_CHAN;
    param.flag |= MSM_MUSPARAM_VOL;
    if (vol < 0) {
        vol = 0x7F;
    }
    param.fadeSpeed = fadeSpeed;
    param.vol = vol;
    msmMusSetParam(temp_r31[0], &param);
}

void BoardAudSeqPause(s32 arg0, s32 arg1, u16 arg2) {
    s16 *temp_r31 = boardSeq[arg0];

    if (temp_r31[0] == -1) {
        return;
    }
    if (arg1 != 0) {
        if (BoardMusStatusGet(arg0) == 3) {
            return;
        }
    } else if (BoardMusStatusGet(arg0) != 3) {
        return;
    }
    HuAudSeqPause(temp_r31[0], arg1, arg2);
}

s32 BoardMusStatusGet(s32 arg0) {
    s16 *temp_r31 = boardSeq[arg0];

    if (temp_r31[0] == -1) {
        return 0;
    }
    return msmMusGetStatus(temp_r31[0]);
}

void BoardAudSeqClear(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        boardSeq[i][0] = boardSeq[i][1] = -1;
    }
    boardFX = -1;
}

void BoardAudSeqFadeOutAll(void) {
    s16 *temp_r31;
    s32 i;

    for (i = 0; i < 2; i++) {
        temp_r31 = boardSeq[i];
        if (temp_r31[0] != -1) {
            HuAudSeqFadeOut(temp_r31[0], 0x64);
            temp_r31[1] = temp_r31[0] = -1;
        }
    }
    BoardAudFXStop();
}

void BoardAudFXPlay(void) {
    s32 var_r31;

    switch (GWBoardGet()) {
        case BOARD_ID_MAIN5:
            var_r31 = 0x48D;
            break;
        case BOARD_ID_MAIN6:
            var_r31 = 0x4A2;
            break;
        default:
            return;
    }
    if (boardFX == -1) {
        boardFX = HuAudFXPlay(var_r31);
    }
}

void BoardAudFXStop(void) {
    if (boardFX != -1) {
        HuAudFXStop(boardFX);
        boardFX = -1;
    }
}
