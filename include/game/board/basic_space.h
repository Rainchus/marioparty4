#include "common.h"
#include "math.h"
#include "game/process.h"
#include "game/audio.h"
#include "game/object.h"

extern Process *boardObjMan;


void BoardEventLandBlue(s32);
void BoardEventLandRed(s32);
s8 BoardCoinChgCreate(Vec*, s8);
s32 BoardCoinChgExist(s32);
void BoardCoinChgHide(s32);