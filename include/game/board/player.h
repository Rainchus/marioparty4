#ifndef _BOARD_PLAYER_H
#define _BOARD_PLAYER_H

#include "game/gamework_data.h"

extern s16 boardPlayerMdl[4];

static inline s16 BoardPlayerHandicapGet(s32 player)
{
	return GWPlayer[player].handicap;
}

static inline s32 BoardPlayerGetCurrIdx()
{
	return GWSystem.player_curr;
}

static inline PlayerState *BoardPlayerGet(s32 player)
{
	return &GWPlayer[player];
}

static inline PlayerState *BoardPlayerGetCurr()
{
	return &GWPlayer[BoardPlayerGetCurrIdx()];
}

static inline s16 BoardPlayerModelGet(s32 player)
{
	PlayerState *player_ptr = BoardPlayerGet(player);
	return boardPlayerMdl[player_ptr->player_idx];
}

static inline s16 BoardPlayerModelGetCurr()
{
	PlayerState *player = BoardPlayerGetCurr();
	return boardPlayerMdl[player->player_idx];
}

void BoardPlayerCoinsSet(s32 player, s32 value);
void BoardPlayerAutoSizeSet(s32 player, s32 value);

#endif