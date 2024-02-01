#ifndef _GAMEWORK_DATA_H
#define _GAMEWORK_DATA_H

#include "dolphin.h"

typedef struct player_config {
    s16 character;
    s16 pad_idx;
    s16 diff;
    s16 group;
    s16 iscom;
} PlayerConfig;

typedef struct system_state {
/* 0x00 */ struct {
        u8 party : 1;
        u8 team : 1;
    };
/* 0x01 */ u8 diff_story;
/* 0x02 */ struct {
        u16 bonus_star : 1;
        u16 explain_mg : 1;
        u16 show_com_mg : 1;
        u16 mg_type : 2;
        u16 mess_speed : 2;
        u16 save_mode : 2;
    };
/* 0x04 */ u8 turn;
/* 0x05 */ u8 max_turn;
/* 0x06 */ u8 star_flag;
/* 0x07 */ u8 star_total;
/* 0x08 */ struct {
    u8 star_pos : 3;
    u8 board : 5;
};
/* 0x09 */ s8 last5_effect;
/* 0x0A */ s8 player_curr;
/* 0x0B */ char unk0B[3];
/* 0x0E */ s16 block_pos;
/* 0x10 */ u8 ATTRIBUTE_ALIGN(4) board_data[32];
/* 0x30 */ u8 mess_delay;
/* 0x31 */ struct {
        u8 field31_bit0 : 4;
        u8 field31_bit4 : 4;
    };
/* 0x32 */ s8 unk_32;
/* 0x34 */ u16 mg_next;
/* 0x36 */ s16 mg_next_extra;
/* 0x38 */ u16 unk_38;
/* 0x3A */ u8 flag[3][16];
/* 0x6A */ u8 unk_6A[0x72];
} SystemState; //8018fcf8, sizeof 0xDC

typedef struct player_state {
/* 0x00 */ struct {
        u16 diff : 2;
        u16 com : 1;
        u16 character : 4;
        u16 auto_size : 2;
        u16 field00_bit9 : 1;
    };
/* 0x02 */ struct {
        u8 team : 1;
        u8 field02_bit1 : 1;
        u8 player_idx : 2;
    };
/* 0x03 */ s8 handicap;
/* 0x04 */ s8 port;
/* 0x05 */ s8 items[3];
/* 0x08 */ struct {
        u16 color : 2;
        u16 moving : 1;
        u16 field08_bit3 : 1;
        u16 show_next : 1;
        u16 size : 2;
        u16 field08_bit7 : 2;
        u16 rank : 2;
        u16 bowser_suit : 1;
        u16 field08_bit11 : 1;
    };
/* 0x0A */ s8 roll;
/* 0x0C */ s16 space_curr;
/* 0x0E */ s16 space_prev;
/* 0x10 */ s16 space_next;
/* 0x12 */ s16 space_shock;
/* 0x14 */ s8 blue_count;
/* 0x15 */ s8 red_count;
/* 0x16 */ s8 question_count;
/* 0x17 */ s8 fortune_count;
/* 0x18 */ s8 bowser_count;
/* 0x19 */ s8 battle_count;
/* 0x1A */ s8 mushroom_count;
/* 0x1B */ s8 warp_count;
/* 0x1C */ s16 coins;
/* 0x1E */ s16 coins_mg;
/* 0x20 */ s16 coins_total;
/* 0x22 */ s16 coins_max;
/* 0x24 */ s16 coins_battle;
/* 0x26 */ s16 unk_26;
/* 0x28 */ s16 coins_mg_gain;
/* 0x2A */ s16 stars;
/* 0x2C */ s16 stars_max;
/* 0x2E */ char unk_2E[2];
} PlayerState; //size of 0x30

typedef struct game_stat {
/* 0x0 */ s16 unk_00;
/* 0x2 */ u8 language;
/* 0x3 */ u8 sound_mode;
/* 0x4 */ s8 rumble;
/* 0x6 */ u16 total_stars;
/* 0x8 */ OSTime create_time;
/* 0x10 */ u32 mg_custom[2];
/* 0x18 */ u32 mg_avail[2];
/* 0x20 */ u32 mg_record[15];
/* 0x5C */ u8 board_win_count[9][8];
/* 0xA4 */ u8 board_play_count[9];
/* 0xAE */ u16 board_max_stars[9];
/* 0xC0 */ u16 board_max_coins[9];
/* 0xD2 */ u8 present[60];
/* 0x10E */ struct {
        u8 story_continue : 1;
        u8 party_continue : 1;
        u8 open_w06 : 1;
        u8 field10E_bit4 : 1;
        u8 field10E_bit5 : 1;
        u8 field10E_bit6 : 1;
    };
/* 0x10F */ struct {
        u8 field10F_bit0 : 1;
        u8 field10F_bit1 : 1;
        u8 field10F_bit2 : 2;
        u8 field10F_bit4 : 2;
        u8 field10F_bit6 : 2;
    };
/* 0x110 */ struct {
        u8 field110_bit0 : 1;
        u8 field110_bit1 : 1;
        u8 field110_bit2 : 2;
        u8 field110_bit4 : 2;
        u8 field110_bit6 : 2;
    };
} GameStat;

extern PlayerConfig GWPlayerCfg[4];
extern PlayerState GWPlayer[4];
extern SystemState GWSystem;
extern GameStat GWGameStat;

static inline s32 GWTeamGet(void)
{
    return GWSystem.team;
}

static inline s32 GWLanguageGet(void)
{
    return GWGameStat.language;
}

static inline s32 GWMGTypeGet(void)
{
    return GWSystem.mg_type;
}

static inline s32 GWMessSpeedGet(void)
{
    return GWSystem.mess_speed;
}

static inline s32 GWBoardGet(void)
{
    return GWSystem.board;
}

static inline s32 GWPlayerTeamGet(s32 player)
{
    return GWPlayer[player].team;
}

static inline s32 GWPlayerSpaceCurrGet(s32 player)
{
    return GWPlayer[player].space_curr;
}

#endif
