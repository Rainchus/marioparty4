#include "game/object.h"
#include "game/objsub.h"
#include "game/wipe.h"
#include "game/chrman.h"
#include "game/minigame_seq.h"
#include "game/pad.h"

#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/hsfanim.h"
#include "game/hsfdraw.h"
#include "game/sprite.h"

#include "game/audio.h"
#include "game/gamework_data.h"

#include "REL/m408Dll.h"

#include "math.h"
#include "ext_math.h"

s32 lbl_1_bss_160[2];
AnimData *lbl_1_bss_14C[5];
s16 lbl_1_bss_148;
s32 lbl_1_bss_144;
u32 lbl_1_bss_140;
omObjData *lbl_1_bss_13C;
s32 lbl_1_bss_138;
s32 lbl_1_bss_134;
s32 lbl_1_bss_130;
HsfConstData *lbl_1_bss_128[2];
void *lbl_1_bss_120[2];
HsfDrawData *lbl_1_bss_11C;
s16 lbl_1_bss_118;
