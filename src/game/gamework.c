#include "common.h"
#include "string.h"
#include "game/gamework.h"
#include "game/flag.h"

GameStat GWGameStatDefault;
GameStat GWGameStat;
SystemState GWSystem;
PlayerState GWPlayer[4];
PlayerConfig GWPlayerCfg[4];

static inline void GWErase(void)
{
    memset(GWPlayerCfg, 0, sizeof(GWPlayerCfg));
    memset(GWPlayer, 0, sizeof(GWPlayer));
    memset(&GWSystem, 0, sizeof(GWSystem));
}

static inline void InitPlayerConfig(void)
{
    PlayerConfig *config;
    s32 i;
    for(i=0; i<4; i++) {
        config = &GWPlayerCfg[i];
        config->character = i;
        config->pad_idx = i;
        config->diff = 0;
        config->group = i;
        if(!HuPadStatGet(i)) {
            config->iscom = 0;
        } else {
            config->iscom = 1;
        }
    }
}

static inline void ResetBoardSettings(void)
{
    GWGameStat.rumble = 1;
    GWSystem.explain_mg = 1;
    GWSystem.show_com_mg = 1;
    GWSystem.mess_speed = 1;
    GWSystem.mess_delay = 32;
    GWSystem.save_mode = 0;
}

void GWInit(void)
{
    GWGameStatReset();
    _InitFlag();
    GWErase();
    InitPlayerConfig();
    GWGameStat.language = 1;
    ResetBoardSettings();
}

static inline void ResetMGRecord(GameStat *game_stat)
{
    game_stat->mg_record[0] = 18000;
    game_stat->mg_record[1] = 80;
    game_stat->mg_record[2] = 3600;
    game_stat->mg_record[3] = 7200;
    game_stat->mg_record[4] = 0;
    game_stat->mg_record[5] = 3600;
    game_stat->mg_record[6] = 18000;
    game_stat->mg_record[7] = 18000;
    game_stat->mg_record[8] = 18000;
    game_stat->mg_record[9] = 0;
    game_stat->mg_record[10] = 300;
    game_stat->mg_record[11] = 0;
    game_stat->mg_record[12] = 0;
    game_stat->mg_record[13] = 0;
    game_stat->mg_record[14] = 0;
}

static inline void ResetBoardRecord(GameStat *game_stat)
{
    s32 i;
    s32 j;
    
    for(i=0; i<9; i++) {
        for(j=0; j<8; j++) {
            game_stat->board_win_count[i][j] = 0;
        }
        game_stat->board_play_count[i] = 0;
        game_stat->board_max_stars[i] = 0;
        game_stat->board_max_coins[i] = 0;
    }
}

static inline void ResetPresent(GameStat *game_stat)
{
    s32 i;
    for(i=0; i<60; i++) {
        game_stat->present[i] = 0;
    }
    (void)i; //HACK to match GWResetGameStat
}

static inline void ResetFlag(GameStat *game_stat)
{
    game_stat->story_continue = 0;
    game_stat->party_continue = 0;
    game_stat->open_w06 = 0;
    game_stat->field10E_bit4 = 0;
    game_stat->field10E_bit5 = 0;
    game_stat->field10E_bit6 = 0;
    game_stat->field10F_bit0 = game_stat->field110_bit0 = 1;
    game_stat->field10F_bit1 = game_stat->field110_bit1 = 1;
    game_stat->field10F_bit2 = game_stat->field110_bit2 = 0;
    game_stat->field10F_bit4 = game_stat->field110_bit4 = 1;
    game_stat->field10F_bit6 = game_stat->field110_bit6 = 0;
}

void GWGameStatReset(void)
{
    GameStat *game_stat = &GWGameStatDefault;
    memset(game_stat, 0, sizeof(GameStat));
    game_stat->unk_00 = 0;
    game_stat->language = 1;
    game_stat->sound_mode = 1;
    game_stat->rumble = 1;
    game_stat->total_stars = 0;
    game_stat->create_time = 0;
    game_stat->mg_custom[0] = 0;
    game_stat->mg_custom[1] = 0;
    game_stat->mg_avail[0] = 0;
    game_stat->mg_avail[1] = 0;
    ResetMGRecord(game_stat);
    ResetBoardRecord(game_stat);
    ResetPresent(game_stat);
    ResetFlag(game_stat);
    memcpy(&GWGameStat, &GWGameStatDefault, sizeof(GameStat));
    ResetBoardSettings();
}

s32 GWMessSpeedGet(void)
{
    if(GWSystem.mess_delay > 48) {
        GWSystem.mess_speed = 1;
        GWSystem.mess_delay = 32;
    }
    return GWSystem.mess_delay;
}

void GWMGRecordSet(int index, s32 value)
{
    if(!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        GWGameStat.mg_record[index] = value;
    }
}

s32 GWMGRecordGet(int index)
{
    return GWGameStat.mg_record[index];
}

void GWCharColorGet(int character, GXColor *color)
{
    GXColor char_color[] = {
        { 227, 67, 67, 255 },
        { 68, 67, 227, 255 },
        { 241, 158, 220, 255 },
        { 67, 228, 68, 255 },
        { 138, 60, 180, 255 },
        { 146, 85, 55, 255 },
        { 227, 228, 68, 255 },
        { 40, 40, 40, 255 }
    };
    *color = char_color[character];
}

void GWBoardPlayCountSet(int board, u8 value)
{
    if(value > 99) {
        value = 99;
    }
    GWGameStat.board_play_count[board] = value;
}

void GWBoardPlayCountAdd(int board, u8 value)
{
    value += GWGameStat.board_play_count[board];
    if(value > 99) {
        value = 99;
    }
    GWGameStat.board_play_count[board] = value;
}


u8 GWBoardPlayCountGet(int board)
{
    return GWGameStat.board_play_count[board];
}

void GWBoardMaxStarsSet(int board, int value)
{
    GWGameStat.board_max_stars[board] = value;
}

u16 GWBoardMaxStarsGet(int board)
{
    return GWGameStat.board_max_stars[board];
}

void GWBoardMaxCoinsSet(int board, int value)
{
    GWGameStat.board_max_coins[board] = value;
}

u16 GWBoardMaxCoinsGet(int board)
{
    return GWGameStat.board_max_coins[board];
}

int GWBoardWinCountInc(int character, int board)
{
    int win_count = GWGameStat.board_win_count[board][character]+1;
    if(win_count > 99) {
        win_count = 99;
    }
    GWGameStat.board_win_count[board][character] = win_count;
    return win_count;
}

int GWBoardWinCountGet(int character, int board)
{
    return GWGameStat.board_win_count[board][character];
}

void GWBoardWinCountSet(int character, int board, int value)
{
    GWGameStat.board_win_count[board][character] = value;
}

int GWMGAvailGet(int id)
{
    int word;
    int bit;
    id -= 401;
    word = id >> 5;
    bit = id % 32;
    if(GWGameStat.mg_avail[word] & (1 << bit)) {
        return 1;
    } else {
        return 0;
    }
}

int GWMGAvailSet(int id)
{
    int word;
    int bit;
    id -= 401;
    word = id >> 5;
    bit = id % 32;
    GWGameStat.mg_avail[word] |= (1 << bit);
}

int GWMGCustomGet(int id)
{
    int word;
    int bit;
    id -= 401;
    word = id >> 5;
    bit = id % 32;
    if(GWGameStat.mg_custom[word] & (1 << bit)) {
        return 1;
    } else {
        return 0;
    }
}

int GWMGCustomSet(int id)
{
    int word;
    int bit;
    id -= 401;
    word = id >> 5;
    bit = id % 32;
    GWGameStat.mg_custom[word] |= (1 << bit);
}

int GWMGCustomReset(int id)
{
    int word;
    int bit;
    id -= 401;
    word = id >> 5;
    bit = id % 32;
    GWGameStat.mg_custom[word] &= ~(1 << bit);
}

s16 GWCoinsGet(int player)
{
    return GWPlayer[player].coins;
}

void GWCoinsSet(int player, s16 value)
{
    if(!_CheckFlag(FLAG_ID_MAKE(1, 12))) {
        if(value < 0) {
            value = 0;
        }
        if(value > 999) {
            value = 999;
        }
        if(value > GWPlayer[player].coins_max) {
            GWPlayer[player].coins_max = value;
        }
        GWPlayer[player].coins = value;
    }
}

void GWCoinsAdd(int player, s16 amount)
{
    GWCoinsSet(player, GWPlayer[player].coins+amount);
}

void GWStarsSet(int player, s16 value)
{
    if(value < 0) {
        value = 0;
    }
    if(value > 999) {
        value = 999;
    }
    if(value > GWPlayer[player].stars_max) {
        GWPlayer[player].stars_max = value;
    }
    GWPlayer[player].stars = value;
}

void GWStarsAdd(int player, s16 amount)
{
    GWStarsSet(player, GWPlayer[player].stars+amount);
}

s16 GWStarsGet(int player)
{
    return GWPlayer[player].stars;
}

void GWTotalStarsSet(s16 value)
{
    if(value < 0) {
        value = 0;
    }
    if(value > 10000) {
        value = 10000;
    }
    GWGameStat.total_stars = value;
}

void GWTotalStarsAdd(s16 amount)
{
    GWTotalStarsSet(GWGameStat.total_stars+amount);
}

u16 GWTotalStarsGet(void)
{
    return GWGameStat.total_stars;
}