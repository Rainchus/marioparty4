#include "common.h"

//HACK: Force 0.5 and 3.0 double constants to appear in REL
const double _half = 0.5;
const double _three = 3.0;

static void SubchrMain(void);

static u8 cur_direction[4];

static char *player_numstr[4] = {
    "PLAYER1",
    "PLAYER2",
    "PLAYER3",
    "PLAYER4"
};

static char *character_str[8] = {
    "MARIO",
    "LUIGI",
    "PEACH",
    "YOSHI",
    "WARIO",
    "DONKEY",
    "DAISY",
    "WALUIGI"
};

static char *ext_character_str[7] = {
    "",
    "KOOPA",
    "KINOPIO",
    "HEIHOH",
    "TERESA",
    "NOKO2",
    "MKOOPA"
};

void ModuleProlog(void)
{
    void* sp8 = omInitObjMan(0x32, 0x2000);
    Hu3DBGColorSet(0, 0, 0);
    HuPrcChildCreate(SubchrMain, 4096, 12288, 0, HuPrcCurrentGet());
    WipeCreate(1, 0, -1);
}

static u16 GetBtns(void)
{
    u16 btns;

    btns = HuPadBtnDown[0];
    if (cur_direction[0] != HuPadDStk[0]) {
        btns |= HuPadDStk[0];
    }
    return btns;
}

static void SubchrMain()
{
    int character[4];
    int ext_character[4];
    int i, cursor_pos;
    for(i=0; i<4; i++) {
        character[i] = gPlayerConfig[i].character;
        ext_character[i] = 0;
        cur_direction[i] = 0;
    }
    cursor_pos = 0;
    while(1) {
        int y, x;
        u16 btns;
        fontcolor = 14;
        print8(150, 64, 2.0f, "Sub Character Select");
        x = 170;
        y = 120;
        for(i=0; i<4; i++, y += 16) {
            fontcolor = 12;
            print8(x, y, 2.0f, player_numstr[i]);
            if(i == cursor_pos) {
                fontcolor = 13;
            } else {
                fontcolor = 12;
            }
            if(ext_character[i] != 0) {
                print8(x+200, y, 2.0f, ext_character_str[ext_character[i]]);
            } else {
                print8(x+200, y, 2.0f, character_str[character[i]]);
            }
        }
        if(GetBtns() & 0x1000) {
            for(i=0; i<4; i++) {
                if(ext_character[i] != 0) {
                    gPlayerConfig[i]. character = ext_character[i]+7;
                }
            }
            fn_80032A58(30);
            WipeCreate(2, 0, -1);
            HuPrcSleep(wipeData.duration+1.0f);
            fn_80035A0C();
            omOvlGotoEx(OVL_M433, 1, 0, 0);
            do {
                HuPrcVSleep();
            } while(1);
        } else {
            if(GetBtns() & 0x1) {
                do {
                    ext_character[cursor_pos]--;
                    if(ext_character[cursor_pos] < 0) {
                        ext_character[cursor_pos] = 6;
                    }
                    for(i=0; i<4; i++) {
                        if(cursor_pos != i) {
                            if(ext_character[cursor_pos] == ext_character[i] && ext_character[cursor_pos] != 0) {
                                break;
                            }
                        }
                    }
                } while(i < 4);
            }
            if(GetBtns() & 0x2) {
                do {
                    ext_character[cursor_pos]++;
                    if(ext_character[cursor_pos] > 6) {
                        ext_character[cursor_pos] = 0;
                    }
                    for(i=0; i<4; i++) {
                        if(cursor_pos != i) {
                            if(ext_character[cursor_pos] == ext_character[i] && ext_character[cursor_pos] != 0) {
                                break;
                            }
                        }
                    }
                } while(i < 4);
            }
            if(GetBtns() & 0x4) {
                cursor_pos++;
            }
            if(GetBtns() & 0x8) {
                cursor_pos--;
            }
            if(cursor_pos < 0) {
                cursor_pos = 3;
            }
            if(cursor_pos > 3) {
                cursor_pos = 0;
            }
            if(GetBtns() & 0x200) {
                fn_80032A58(30);
                WipeCreate(2, 0, -1);
                HuPrcSleep(wipeData.duration+1.0f);
                fn_80035A0C();
                omOvlReturnEx(1, 1);
                do {
                    HuPrcVSleep();
                } while(1);
            } else {
                if(cur_direction[0] != HuPadDStk[0]) {
                    cur_direction[0] = HuPadDStk[0];
                }
            }
        }
        HuPrcVSleep();
    }
}