#ifndef _GAME_GAMEWORK_H
#define _GAME_GAMEWORK_H

#include "dolphin.h"

void GWInit(void);
void GWResetGameStat(void);
s16 GWGetMessSpeed(void);
void GWSetMGRecord(int index, s32 value);
s32 GWGetMGRecord(int index);
void GWGetCharColor(int character, GXColor *color);
void GWSetBoardPlayCount(int board, u8 value);
void GWAddBoardPlayCount(int board, u8 value);
u8 GWGetBoardPlayCount(int board);
void GWSetBoardMaxStars(int board, int value);
u16 GWGetBoardMaxStars(int board);
void GWSetBoardMaxCoins(int board, int value);
u16 GWGetBoardMaxCoins(int board);
int GWIncBoardWinCount(int character, int board);
int GWGetBoardWinCount(int character, int board);
void GWSetBoardWinCount(int character, int board, int value);
int GWGetMGAvail(int id);
int GWSetMGAvail(int id);
int GWGetMGCustom(int id);
int GWSetMGCustom(int id);
int GWResetMGCustom(int id);
s16 GWGetCoins(int player);
void GWSetCoins(int player, s16 value);
void GWAddCoins(int player, s16 amount);
void GWSetStars(int player, s16 value);
void GWAddStars(int player, s16 amount);
s16 GWGetStars(int player);
void GWSetTotalStars(s16 value);
void GWAddTotalStars(s16 amount);
u16 GWGetTotalStars(void);

#endif