#ifndef _GAME_GAMEWORK_H
#define _GAME_GAMEWORK_H

#include "dolphin.h"

void GWInit(void);
void GWGameStatReset(void);
s16 GWMessSpeedGet(void);
void GWMGRecordSet(int index, s32 value);
s32 GWMGRecordGet(int index);
void GWCharColorGet(int character, GXColor *color);
void GWBoardPlayCountSet(int board, u8 value);
void GWBoardPlayCountAdd(int board, u8 value);
u8 GWBoardPlayCountGet(int board);
void GWBoardMaxStarsSet(int board, int value);
u16 GWBoardMaxStarsGet(int board);
void GWBoardMaxCoinsSet(int board, int value);
u16 GWBoardMaxCoinsGet(int board);
int GWBoardWinCountInc(int character, int board);
int GWBoardWinCountGet(int character, int board);
void GWBoardWinCountSet(int character, int board, int value);
int GWMGAvailGet(int id);
int GWMGAvailSet(int id);
int GWMGCustomGet(int id);
int GWMGCustomSet(int id);
int GWMGCustomReset(int id);
s16 GWCoinsGet(int player);
void GWCoinsSet(int player, s16 value);
void GWCoinsAdd(int player, s16 amount);
void GWStarsSet(int player, s16 value);
void GWStarsAdd(int player, s16 amount);
s16 GWStarsGet(int player);
void GWTotalStarsSet(s16 value);
void GWTotalStarsAdd(s16 amount);
u16 GWTotalStarsGet(void);

#endif