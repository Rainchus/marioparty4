#ifndef _BOARD_START_H
#define _BOARD_START_H

#include "game/board/space.h"

#include "dolphin.h"

void BoardStarHostSet(s16 arg0);
s16 BoardStarHostMdlGet(void);
void BoardStarExec(s32 arg0, BoardSpace *arg1);
void BoardStarGive(s32 arg0, Vec *arg1);
void BoardStarShowNext(s32 arg0);

#endif
