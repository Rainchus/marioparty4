#ifndef _GAME_OBJSUB_H
#define _GAME_OBJSUB_H

#include "dolphin.h"
#include "game/process.h"

typedef struct mg_info {
    u16 ovl;
    u8 type;
    u8 flag;
    u16 unk_4;
    u16 unk_6;
    u32 name_mess;
    u32 data_dir;
    u32 inst_pic;
    u32 unk_14;
    u32 unk_18;
    u32 mg_pic;
    u32 unk_20;
    u32 unk_24;
    u32 rules_mess;
    u32 control_mess[2];
    u32 advice_mess;
} MgInfo;

s16 omGetMGIndex(s16 overlay);
void omGameSysInit(Process* process);
void omVibrate(s16 player_cfg_index, s16 duration, s16 off, s16 on);

#endif
