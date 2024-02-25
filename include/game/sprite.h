#ifndef _GAME_SPRITE_H
#define _GAME_SPRITE_H

#include "dolphin.h"
#include "game/data.h"
#include "game/memory.h"

#define SPRITE_MAX 384
#define SPRITE_GROUP_MAX 256

#define SPRITE_INVALID -1
#define SPRITE_GROUP_INVALID -1

#define SPRITE_ATTR_PAUSED 0x1
#define SPRITE_ATTR_LOOP 0x2
#define SPRITE_ATTR_HIDDEN 0x4
#define SPRITE_ATTR_BILINEAR 0x8
#define SPRITE_ATTR_FUNC 0x10
#define SPRITE_ATTR_NOPAUSE 0x20
#define SPRITE_ATTR_REVERSE 0x40
#define SPRITE_ATTR_ADDITIVE 0x80
#define SPRITE_ATTR_INVERT 0x100

#define SPRITE_BMP_RGBA8 0
#define SPRITE_BMP_RGB5A3 1
#define SPRITE_BMP_RGB5A3_DUPE 2
#define SPRITE_BMP_C8 3
#define SPRITE_BMP_C4 4
#define SPRITE_BMP_IA8 5
#define SPRITE_BMP_IA4 6
#define SPRITE_BMP_I8 7
#define SPRITE_BMP_I4 8
#define SPRITE_BMP_A8 9
#define SPRITE_BMP_CMPR 10

#define SPRITE_BMP_FMTMASK 0xF
#define SPRITE_BMP_ALLOC 0x8000
#define SPRITE_BMP_NUM_MASK 0x7FFF

#define SPRITE_LAYER_FLIPX 0x1
#define SPRITE_LAYER_FLIPY 0x2

typedef void (*SpriteFunc)(struct sprite_data *);

typedef struct anim_frame_data {
    s16 pat;
    s16 time;
    s16 shiftX;
    s16 shiftY;
    s16 flip;
    s16 pad;
} AnimFrameData;

typedef struct anim_bank_data {
    s16 timeNum;
    s16 unk;
    AnimFrameData *frame;
} AnimBankData;

typedef struct anim_layer_data {
    u8 alpha;
    u8 flip;
    s16 bmpNo;
    s16 startX;
    s16 startY;
    s16 sizeX;
    s16 sizeY;
    s16 shiftX;
    s16 shiftY;
    s16 vtx[8];
} AnimLayerData;

typedef struct anim_pat_data {
    s16 layerNum;
    s16 centerX;
    s16 centerY;
    s16 sizeX;
    s16 sizeY;
    AnimLayerData *layer;
} AnimPatData;

typedef struct anim_bmp_data {
    u8 pixSize;
    u8 dataFmt;
    s16 palNum;
    s16 sizeX;
    s16 sizeY;
    u32 dataSize;
    void *palData;
    void *data;
} AnimBmpData;

typedef struct anim_data {
    s16 bankNum;
    s16 patNum;
    s16 bmpNum;
    s16 useNum;
    AnimBankData *bank;
    AnimPatData *pat;
    AnimBmpData *bmp;
} AnimData;

typedef struct sprite_data {
    u8 r;
    u8 g;
    u8 b;
    char draw_no;
    short frame;
    short bank;
    short attr;
    short dirty_flag;
    short prio;
    float time;
    float x;
    float y;
    float z_rot;
    float scale_x;
    float scale_y;
    float speed;
    float a;
    GXTexWrapMode wrap_s;
    GXTexWrapMode wrap_t;
    short tex_scale_x;
    short tex_scale_y;
    Mtx *group_mtx;
    union {
        AnimData *data;
        SpriteFunc func;
    };
    AnimPatData *pat_data;
    AnimFrameData *frame_data;
    short work[4];
    AnimData *bg;
    unsigned short bg_bank;
    short scissor_x;
    short scissor_y;
    short scissor_w;
    short scissor_h;
} SpriteData;

typedef struct sprite_group_data {
    short capacity;
    float x;
    float y;
    float z_rot;
    float scale_x;
    float scale_y;
    float center_x;
    float center_y;
    short *members;
    Mtx mtx;
} SpriteGroupData;

extern SpriteData HuSprData[SPRITE_MAX];
extern SpriteGroupData HuSprGrpData[SPRITE_GROUP_MAX];

#define HuSprAnimReadFile(data_id) (HuSprAnimRead(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

void HuSprInit(void);
void HuSprClose(void);
void HuSprExec(short draw_no);
void HuSprBegin(void);
SpriteData *HuSprCall(void);
void HuSprFinish(void);
void HuSprPauseSet(BOOL value);
AnimData *HuSprAnimRead(void *data);
void HuSprAnimLock(AnimData *anim);
short HuSprCreate(AnimData *anim, short prio, short bank);
short HuSprFuncCreate(SpriteFunc func, short prio);
short HuSprGrpCreate(short capacity);
short HuSprGrpCopy(short group);
void HuSprGrpMemberSet(short group, short member, short sprite);
void HuSprGrpMemberKill(short group, short member);
void HuSprGrpKill(short group);
void HuSprKill(short sprite);
void HuSprAnimKill(AnimData *anim);
void HuSprAttrSet(short group, short member, int attr);
void HuSprAttrReset(short group, short member, int attr);
void HuSprPosSet(short group, short member, float x, float y);
void HuSprZRotSet(short group, short member, float z_rot);
void HuSprScaleSet(short group, short member, float x, float y);
void HuSprTPLvlSet(short group, short member, float tp_lvl);
void HuSprColorSet(short group, short member, u8 r, u8 g, u8 b);
void HuSprSpeedSet(short group, short member, float speed);
void HuSprBankSet(short group, short member, short bank);
void HuSprGrpPosSet(short group, float x, float y);
void HuSprGrpCenterSet(short group, float x, float y);
void HuSprGrpZRotSet(short group, float z_rot);
void HuSprGrpScaleSet(short group, float x, float y);
void HuSprGrpTPLvlSet(short group, float tp_lvl);
s32 HuSprGrpDrawNoSet(short group, int draw_no);
void HuSprDrawNoSet(short group, short member, int draw_no);
void HuSprPriSet(short group, short member, short prio);
void HuSprGrpScissorSet(short group, short x, short y, short w, short h);
void HuSprScissorSet(short group, short member, short x, short y, short w, short h);
AnimData *HuSprAnimMake(short sizeX, short sizeY, short dataFmt);
void HuSprBGSet(short group, short member,  AnimData *bg, short bg_bank);
void HuSprSprBGSet(short sprite, AnimData *bg, short bg_bank);
void AnimDebug(AnimData *anim);

void HuSprDispInit(void);
void HuSprDisp(SpriteData *sprite);
void HuSprTexLoad(AnimData *anim, short bmp, short slot, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter filter);
void HuSprExecLayerSet(short draw_no, short layer);

#endif