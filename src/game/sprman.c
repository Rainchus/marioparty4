#include "game/sprite.h"
#include "game/memory.h"
#include "game/init.h"

#include "dolphin/mtx.h"

#define SPRITE_DIRTY_ATTR 0x1
#define SPRITE_DIRTY_XFORM 0x2
#define SPRITE_DIRTY_COLOR 0x4

typedef struct sprite_order_data {
    unsigned short group;
    unsigned short sprite;
    unsigned short prio;
    unsigned short next;
} SpriteOrderData;

SpriteData HuSprData[SPRITE_MAX];
SpriteGroupData HuSprGrpData[SPRITE_GROUP_MAX];
static SpriteOrderData HuSprOrder[SPRITE_MAX*2];

static short HuSprOrderNum;
static short HuSprOrderNo;
static BOOL HuSprPauseF;

static void HuSprOrderEntry(short group, short sprite);

void mtxTransCat(Mtx matrix, float x, float y, int z); //Last argument should be a float

void HuSprInit(void)
{
    short i;
    SpriteData *sprite;
    SpriteGroupData *group;
    for(sprite = &HuSprData[1], i=1; i<SPRITE_MAX; i++, sprite++) {
        sprite->data = NULL;
    }
    for(group = HuSprGrpData, i=0; i<SPRITE_GROUP_MAX; i++, group++) {
        group->capacity = 0;
    }
    sprite = &HuSprData[0];
    sprite->prio = 0;
    sprite->data = (void *)1;
    HuSprPauseF = FALSE;
}

void HuSprClose(void)
{
    short i;
    SpriteGroupData *group;
    SpriteData *sprite;
    
    for(group = HuSprGrpData, i=0; i<SPRITE_GROUP_MAX; i++, group++) {
        if(group->capacity != 0) {
            HuSprGrpKill(i);
        }
    }
    for(sprite = &HuSprData[1], i=1; i<SPRITE_MAX; i++, sprite++) {
        if(sprite->data) {
            HuSprKill(i);
        }
    }
    HuSprPauseF = FALSE;
}

void HuSprExec(short draw_no)
{
    SpriteData *sprite;
    while(sprite = HuSprCall()) {
        if(!(sprite->attr & SPRITE_ATTR_HIDDEN) && sprite->draw_no == draw_no) {
            HuSprDisp(sprite);
        }
    }
}

void HuSprBegin(void)
{
    Mtx temp, rot;
    short i, j;
    Vec axis = {0, 0, 1};
    SpriteGroupData *group;
    group = HuSprGrpData;
    HuSprOrderNum = 1;
    HuSprOrder[0].next = 0;
    HuSprOrder[0].prio = -1;
    for(i=0; i<SPRITE_GROUP_MAX; i++, group++) {
        if(group->capacity != 0) {
            MTXTrans(temp, group->center_x*group->scale_x, group->center_y*group->scale_y, 0.0f);
            MTXRotAxisDeg(rot, &axis, group->z_rot);
            MTXConcat(rot, temp, group->mtx);
            MTXScale(temp, group->scale_x, group->scale_y, 1.0f);
            MTXConcat(group->mtx, temp, group->mtx);
            mtxTransCat(group->mtx, group->x, group->y, 0);
            for(j=0; j<group->capacity; j++) {
                if(group->members[j] != -1) {
                    HuSprOrderEntry(i, group->members[j]);
                }
            }
        }
    }
    HuSprOrderNo = 0;
}

static void HuSprOrderEntry(short group, short sprite)
{
    SpriteOrderData *order = &HuSprOrder[HuSprOrderNum];
    short prio = HuSprData[sprite].prio;
    short prev, next;
    if(HuSprOrderNum >= SPRITE_MAX*2) {
        OSReport("Order Max Over!\n");
        return;
    }
    next = HuSprOrder[0].next;
    for(prev = 0; next != 0; prev = next, next = HuSprOrder[next].next) {
        if(HuSprOrder[next].prio < prio) {
            break;
        }
    }
    order->next = HuSprOrder[prev].next;
    HuSprOrder[prev].next = HuSprOrderNum;
    order->prio = prio;
    order->group = group;
    order->sprite = sprite;
    HuSprOrderNum++;
}

SpriteData *HuSprCall(void)
{
    HuSprOrderNo = HuSprOrder[HuSprOrderNo].next;
    if(HuSprOrderNo != 0) {
        SpriteOrderData *order = &HuSprOrder[HuSprOrderNo];
        SpriteData *sprite = &HuSprData[order->sprite];
        sprite->group_mtx = &HuSprGrpData[order->group].mtx;
        if(sprite->attr & SPRITE_ATTR_FUNC) {
            return sprite;
        }
        sprite->frame_data = &sprite->data->bank[sprite->bank].frame[sprite->frame];
        sprite->pat_data = &sprite->data->pat[sprite->frame_data->pat];
        return sprite;
    } else {
        return NULL;
    }
}

static inline void SpriteCalcFrame(SpriteData *sprite, AnimBankData *bank, AnimFrameData **frame, short loop)
{
    if(sprite->time >= (*frame)->time) {
        sprite->frame++;
        sprite->time -= (*frame)->time;
        if(sprite->frame >= bank->timeNum || (*frame)[1].time == -1) {
            if(loop) {
                sprite->frame = 0;
            } else {
                sprite->frame = bank->timeNum-1;
            }
        }
        *frame = &bank->frame[sprite->frame];
    } else if(sprite->time < 0) {
        sprite->frame--;
        if(sprite->frame < 0) {
            if(loop) {
                sprite->frame = bank->timeNum-1;
            } else {
                sprite->frame = 0;
            }
        }
        *frame = &bank->frame[sprite->frame];
        sprite->time += (*frame)->time;
    }
}

void HuSprFinish(void)
{
    AnimData *anim;
    AnimBankData *bank;
    AnimFrameData *frame;
    SpriteData *sprite;
    short i;
    short j;
    short loop;
    short dir;
    
    for(sprite = &HuSprData[1], i=1; i<SPRITE_MAX; i++, sprite++) {
        if(sprite->data && !(sprite->attr & SPRITE_ATTR_FUNC)) {
            if(!HuSprPauseF || (sprite->attr & SPRITE_ATTR_NOPAUSE)) {
                anim = sprite->data;
                bank = &anim->bank[sprite->bank];
                frame = &bank->frame[sprite->frame];
                loop = (sprite->attr & SPRITE_ATTR_LOOP) ? 0 : 1;
                if(!(sprite->attr & SPRITE_ATTR_PAUSED)) {
                    dir = (sprite->attr & SPRITE_ATTR_REVERSE) ? -1 : 1;
                    for(j=0; j<(int)sprite->speed*minimumVcount; j++) {
                        sprite->time += dir;
                        SpriteCalcFrame(sprite, bank, &frame, loop);
                    }
                    sprite->time += (sprite->speed*(float)minimumVcount)-j;
                    SpriteCalcFrame(sprite, bank, &frame, loop);
                }
                sprite->dirty_flag = 0;
            }
        }
    }
}

void HuSprPauseSet(BOOL value)
{
    HuSprPauseF = value;
}

AnimData *HuSprAnimRead(void *data)
{
    short i;
    AnimBmpData *bmp;
    AnimBankData *bank;
    AnimPatData *pat;
    
    AnimData *anim = (AnimData *)data;
    if((u32)anim->bank & 0xFFFF0000) {
        anim->useNum++;
        return anim;
    }
    bank = (AnimBankData *)((u32)anim->bank+(u32)data);
    anim->bank = bank;
    pat = (AnimPatData *)((u32)anim->pat+(u32)data);
    anim->pat = pat;
    bmp = (AnimBmpData *)((u32)anim->bmp+(u32)data);
    anim->bmp = bmp;
    for(i=0; i<anim->bankNum; i++, bank++) {
        bank->frame = (AnimFrameData *)((u32)bank->frame+(u32)data);
    }
    for(i=0; i<anim->patNum; i++, pat++) {
        pat->layer = (AnimLayerData *)((u32)pat->layer+(u32)data);
    }
    for(i=0; i<anim->bmpNum; i++, bmp++) {
        bmp->palData = (void *)((u32)bmp->palData+(u32)data);
        bmp->data = (void *)((u32)bmp->data+(u32)data);
    }
    anim->useNum = 0;
    return anim;
}

void HuSprAnimLock(AnimData *anim)
{
    anim->useNum++;
}

short HuSprCreate(AnimData *anim, short prio, short bank)
{
    SpriteData *sprite;
    short i;
    for(sprite = &HuSprData[1], i=1; i<SPRITE_MAX; i++, sprite++) {
        if(!sprite->data) {
            break;
        }
    }
    if(i == SPRITE_MAX) {
        return SPRITE_INVALID;
    }
    sprite->data = anim;
    sprite->speed = 1.0f;
    sprite->frame = 0;
    sprite->bank = bank;
    sprite->time = 0.0f;
    sprite->attr = 0;
    sprite->draw_no = 0;
    sprite->r = sprite->g = sprite->b = sprite->a = 255;
    sprite->x = sprite->y = sprite->z_rot = 0.0f;
    sprite->prio = prio;
    sprite->scale_x = sprite->scale_y = 1.0f;
    sprite->wrap_s = sprite->wrap_t = GX_CLAMP;
    sprite->tex_scale_x = sprite->tex_scale_y = 1;
    sprite->bg = NULL;
    sprite->scissor_x = sprite->scissor_y = 0;
    sprite->scissor_w = 640;
    sprite->scissor_h = 480;
    if(anim) {
        HuSprAnimLock(anim);
    }
    return i;
}

short HuSprFuncCreate(void (*func)(SpriteData *sprite), short prio)
{
    SpriteData *sprite;
    short index = HuSprCreate(NULL, prio, 0);
    if(index == SPRITE_INVALID) {
        return SPRITE_INVALID;
    }
    sprite = &HuSprData[index];
    sprite->func = func;
    sprite->attr |= SPRITE_ATTR_FUNC;
    return index;
}

short HuSprGrpCreate(short capacity)
{
    SpriteGroupData *group;
    short i, j;
    for(group = HuSprGrpData, i=0; i<SPRITE_GROUP_MAX; i++, group++) {
        if(group->capacity == 0) {
            break;
        }
    }
    if(i == SPRITE_GROUP_MAX) {
        return SPRITE_GROUP_INVALID;
    }
    group->members = HuMemDirectMalloc(HEAP_SYSTEM, sizeof(short)*capacity);
    for(j=0; j<capacity; j++) {
        group->members[j] = SPRITE_INVALID;
    }
    group->capacity = capacity;
    group->x = group->y = group->z_rot = group->center_x = group->center_y = 0.0f;
    group->scale_x = group->scale_y = 1.0f;
    return i;
}

short HuSprGrpCopy(short group)
{
    SpriteGroupData *new_group_ptr;
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short new_group = HuSprGrpCreate(group_ptr->capacity);
    short i;
    if(new_group == SPRITE_GROUP_INVALID) {
        return SPRITE_GROUP_INVALID;
    }
    new_group_ptr = &HuSprGrpData[new_group];
    new_group_ptr->x = group_ptr->x;
    new_group_ptr->y = group_ptr->y;
    new_group_ptr->z_rot = group_ptr->z_rot;
    new_group_ptr->scale_x = group_ptr->scale_x;
    new_group_ptr->scale_y = group_ptr->scale_y;
    new_group_ptr->center_x = group_ptr->center_x;
    new_group_ptr->center_y = group_ptr->center_y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            SpriteData *old_sprite = &HuSprData[group_ptr->members[i]];
            short new_sprite = HuSprCreate(old_sprite->data, old_sprite->prio, old_sprite->bank);
            HuSprData[new_sprite] = *old_sprite;
            HuSprGrpMemberSet(new_group, i, new_sprite);
        }
    }
    return new_group;
}

void HuSprGrpMemberSet(short group, short member, short sprite)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    SpriteData *sprite_ptr = &HuSprData[sprite];
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] != SPRITE_INVALID) {
        return;
    }
    group_ptr->members[member] = sprite;
}

void HuSprGrpMemberKill(short group, short member)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == SPRITE_INVALID) {
        return;
    }
    HuSprKill(group_ptr->members[member]);
    group_ptr->members[member] = SPRITE_INVALID;
}

void HuSprGrpKill(short group)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprKill(group_ptr->members[i]);
        }
    }
    group_ptr->capacity = 0;
    HuMemDirectFree(group_ptr->members);
}

void HuSprKill(short sprite)
{
    SpriteData *sprite_ptr = &HuSprData[sprite];
    if(!sprite_ptr->data) {
        return;
    }
    if(!(sprite_ptr->attr & SPRITE_ATTR_FUNC)) {
        HuSprAnimKill(sprite_ptr->data);
        if(sprite_ptr->bg) {
            HuSprAnimKill(sprite_ptr->bg);
            sprite_ptr->bg = NULL;
        }
    }
    sprite_ptr->data = NULL;
}

void HuSprAnimKill(AnimData *anim)
{
    if(--anim->useNum <= 0) {
        if(anim->bmpNum & SPRITE_BMP_ALLOC) {
            if(anim->bmp->data) {
                HuMemDirectFree(anim->bmp->data);
            }
            if(anim->bmp->palData) {
                HuMemDirectFree(anim->bmp->palData);
            }
        }
        HuMemDirectFree(anim);
    }
}

void HuSprAttrSet(short group, short member, int attr)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    SpriteData *sprite_ptr;
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == SPRITE_INVALID) {
        return;
    }
    sprite_ptr = &HuSprData[group_ptr->members[member]];
    sprite_ptr->attr |= attr;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_ATTR;
}

void HuSprAttrReset(short group, short member, int attr)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    SpriteData *sprite_ptr;
    if(group_ptr->capacity == 0 || group_ptr->capacity <= member || group_ptr->members[member] == SPRITE_INVALID) {
        return;
    }
    sprite_ptr = &HuSprData[group_ptr->members[member]];
    sprite_ptr->attr &= ~attr;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_ATTR;
}

void HuSprPosSet(short group, short member, float x, float y)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->x = x;
    sprite_ptr->y = y;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprZRotSet(short group, short member, float z_rot)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->z_rot = z_rot;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprScaleSet(short group, short member, float x, float y)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->scale_x = x;
    sprite_ptr->scale_y = y;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_XFORM;
}

void HuSprTPLvlSet(short group, short member, float tp_lvl)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->a = tp_lvl*255;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_COLOR;
}

void HuSprColorSet(short group, short member, u8 r, u8 g, u8 b)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->r = r;
    sprite_ptr->g = g;
    sprite_ptr->b = b;
    sprite_ptr->dirty_flag |= SPRITE_DIRTY_COLOR;
}

void HuSprSpeedSet(short group, short member, float speed)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    HuSprData[group_ptr->members[member]].speed = speed;
}

void HuSprBankSet(short group, short member, short bank)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    AnimData *anim = sprite_ptr->data;
    AnimBankData *bank_ptr = &anim->bank[sprite_ptr->bank];
    AnimFrameData *frame_ptr = &bank_ptr->frame[sprite_ptr->frame];
    sprite_ptr->bank = bank;
    if(sprite_ptr->attr & SPRITE_ATTR_REVERSE) {
        sprite_ptr->frame = bank_ptr->timeNum-1;
        frame_ptr = &bank_ptr->frame[sprite_ptr->frame];
        sprite_ptr->time = frame_ptr->time;
    } else {
        sprite_ptr->time = 0;
        sprite_ptr->frame = 0;
    }
}

void HuSprGrpPosSet(short group, float x, float y)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    group_ptr->x = x;
    group_ptr->y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != -1) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpCenterSet(short group, float x, float y)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    group_ptr->center_x = x;
    group_ptr->center_y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpZRotSet(short group, float z_rot)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    group_ptr->z_rot = z_rot;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpScaleSet(short group, float x, float y)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    group_ptr->scale_x = x;
    group_ptr->scale_y = y;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_XFORM;
        }
    }
}

void HuSprGrpTPLvlSet(short group, float tp_lvl)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprData[group_ptr->members[i]].a = tp_lvl*255;
            HuSprData[group_ptr->members[i]].dirty_flag |= SPRITE_DIRTY_COLOR;
        }
    }
}

s32 HuSprGrpDrawNoSet(short group, int draw_no)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprData[group_ptr->members[i]].draw_no = draw_no;
        }
    }
}

void HuSprDrawNoSet(short group, short member, int draw_no)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->draw_no = draw_no;
}

void HuSprPriSet(short group, short member, short prio)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->prio = prio;
}

void HuSprGrpScissorSet(short group, short x, short y, short w, short h)
{
    SpriteGroupData *group_ptr = &HuSprGrpData[group];
    short i;
    for(i=0; i<group_ptr->capacity; i++) {
        if(group_ptr->members[i] != SPRITE_INVALID) {
            HuSprScissorSet(group, i, x, y, w, h);
        }
    }
}

void HuSprScissorSet(short group, short member, short x, short y, short w, short h)
{
    SpriteData *sprite_ptr = &HuSprData[HuSprGrpData[group].members[member]];
    sprite_ptr->scissor_x = x;
    sprite_ptr->scissor_y = y;
    sprite_ptr->scissor_w = w;
    sprite_ptr->scissor_h = h;
}

static short bitSizeTbl[11] = { 32, 24, 16, 8, 4, 16, 8, 8, 4, 8, 4 };

AnimData *HuSprAnimMake(short sizeX, short sizeY, short dataFmt)
{
    AnimLayerData *layer;
    AnimBmpData *bmp;
    AnimData *anim;
    AnimPatData *pat;
    AnimFrameData *frame;
    void *temp;
    AnimBankData *bank;
    AnimData *new_anim;

    anim = new_anim = HuMemDirectMalloc(HEAP_DATA, sizeof(AnimData)+sizeof(AnimBankData)+sizeof(AnimFrameData)
                                            +sizeof(AnimPatData)+sizeof(AnimLayerData)+sizeof(AnimBmpData));

    bank = temp = &new_anim[1];
    anim->bank = bank;
    frame = temp = ((char *)temp+sizeof(AnimBankData));
    bank->frame = frame;
    pat = temp = ((char *)temp+sizeof(AnimFrameData));
    anim->pat = pat;
    layer = temp = ((char *)temp+sizeof(AnimPatData));
    pat->layer = layer;
    bmp = temp = ((char *)temp+sizeof(AnimLayerData));
    anim->bmp = bmp;
    anim->useNum = 0;
    anim->bankNum = 1;
    anim->patNum = 1;
    anim->bmpNum = (1|SPRITE_BMP_ALLOC);
    bank->timeNum = 1;
    bank->unk = 10;
    frame->pat = 0;
    frame->time = 10;
    frame->shiftX = frame->shiftY = frame->flip = 0;
    pat->layerNum = 1;
    pat->centerX = sizeX/2;
    pat->centerY = sizeY/2;
    pat->sizeX = sizeX;
    pat->sizeY = sizeY;
    layer->alpha = 255;
    layer->flip = 0;
    layer->bmpNo = 0;
    layer->startX = layer->startY = 0;
    layer->sizeX = sizeX;
    layer->sizeY = sizeY;
    layer->shiftX = layer->shiftY = 0;
    layer->vtx[0] = layer->vtx[1] = 0;
    layer->vtx[2] = sizeX;
    layer->vtx[3] = 0;
    layer->vtx[4] = sizeX;
    layer->vtx[5] = sizeY;
    layer->vtx[6] = 0;
    layer->vtx[7] = sizeY;
    bmp->pixSize = bitSizeTbl[dataFmt];
    bmp->dataFmt = dataFmt;
    bmp->palNum = 0;
    bmp->sizeX = sizeX;
    bmp->sizeY = sizeY;
    bmp->dataSize = sizeX*sizeY*bitSizeTbl[dataFmt]/8;
    bmp->palData = NULL;
    bmp->data = NULL;
    return anim;
}

void HuSprBGSet(short group, short member,  AnimData *bg, short bg_bank)
{
    short sprite = HuSprGrpData[group].members[member];
    HuSprSprBGSet(sprite, bg, bg_bank);
}

void HuSprSprBGSet(short sprite, AnimData *bg, short bg_bank)
{
    SpriteData *sprite_ptr = &HuSprData[sprite];
    sprite_ptr->bg = bg;
    sprite_ptr->bg_bank = bg_bank;
    sprite_ptr->wrap_t = sprite_ptr->wrap_s = GX_REPEAT;
    sprite_ptr->attr &= ~SPRITE_ATTR_BILINEAR;
}

void AnimDebug(AnimData *anim)
{
    AnimPatData *pat;
    AnimLayerData *layer;
    s16 i;
    s16 j;
    AnimFrameData *frame;
    AnimBankData *bank;
    AnimBmpData *bmp;
    
    OSReport("patNum %d,bankNum %d,bmpNum %d\n", anim->patNum, anim->bankNum, anim->bmpNum & SPRITE_BMP_NUM_MASK);
    pat = anim->pat;
    for(i=0; i<anim->patNum; i++) {
        OSReport("PATTERN%d:\n", i);
        OSReport("\tlayerNum %d,center (%d,%d),size (%d,%d)\n", pat->layerNum, pat->centerX, pat->centerX, pat->sizeX, pat->sizeY);
        layer = pat->layer;
        for(j=0; j<pat->layerNum; j++) {
            OSReport("\t\tfileNo %d,flip %x\n", layer->bmpNo, layer->flip);
            OSReport("\t\tstart (%d,%d),size (%d,%d),shift (%d,%d)\n", layer->startX, layer->startY, layer->sizeX, layer->sizeY, layer->shiftX, layer->shiftY);
            if(j != pat->layerNum-1) {
                OSReport("\n");
            }
            layer++;
        }
        pat++;
    }
    bank = anim->bank;
    for(i=0; i<anim->bankNum; i++) {
        OSReport("BANK%d:\n", i);
        OSReport("\ttimeNum %d\n", bank->timeNum);
        frame = bank->frame;
        for(j=0; j<bank->timeNum; j++) {
            OSReport("\t\tpat %d,time %d,shift(%d,%d),flip %x\n", frame->pat, frame->time, frame->shiftX, frame->shiftY, frame->flip);
            frame++;
        }
        bank++;
    }
    bmp = anim->bmp;
    for(i=0; i<anim->bmpNum & SPRITE_BMP_NUM_MASK; i++) {
        OSReport("BMP%d:\n", i);
        OSReport("\tpixSize %d,palNum %d,size (%d,%d)\n", bmp->pixSize, bmp->palNum, bmp->sizeX, bmp->sizeY);
        bmp++;
    }
}