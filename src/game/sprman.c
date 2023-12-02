#include "common.h"
#include "dolphin/mtx.h"

SpriteData HuSprData[384];
SpriteGroupData HuSprGrpData[256];
static SpriteOrderData HuSprOrder[384*2];


static s16 HuSprOrderNum;
static s16 HuSprOrderNo;
static BOOL HuSprPauseF;

void HuSprGrpKill(s16 i);
void HuSprKill(s16 i);

void HuSprDisp(SpriteData *sprite);
SpriteData *HuSprCall();

static void HuSprOrderEntry(s16 group, s16 sprite);

extern u32 minimumVcount;

void mtxTransCat(Mtx matrix, float x, float y, int z); //Last argument should be a float

void HuSprInit(void)
{
    s16 i;
    SpriteData *sprite;
    SpriteGroupData *group;
    for(sprite = &HuSprData[1], i=1; i<384; i++, sprite++) {
        sprite->data = NULL;
    }
    for(group = HuSprGrpData, i=0; i<256; i++, group++) {
        group->num_members = 0;
    }
    sprite = &HuSprData[0];
    sprite->prio = 0;
    sprite->data = (void *)1;
    HuSprPauseF = FALSE;
}

void HuSprClose(void)
{
    s16 i;
    SpriteGroupData *group;
    SpriteData *sprite;
    
    for(group = HuSprGrpData, i=0; i<256; i++, group++) {
        if(group->num_members != 0) {
            HuSprGrpKill(i);
        }
    }
    for(sprite = &HuSprData[1], i=1; i<384; i++, sprite++) {
        if(sprite->data) {
            HuSprKill(i);
        }
    }
    HuSprPauseF = FALSE;
}

void HuSprExec(s16 draw_no)
{
    SpriteData *sprite;
    while(sprite = HuSprCall()) {
        if(!(sprite->attr & 0x4) && sprite->draw_no == draw_no) {
            HuSprDisp(sprite);
        }
    }
}

void HuSprBegin(void)
{
    Mtx temp, rot;
    s16 i, j;
    Vec axis = {0, 0, 1};
    SpriteGroupData *group;
    group = HuSprGrpData;
    HuSprOrderNum = 1;
    HuSprOrder[0].next = 0;
    HuSprOrder[0].prio = -1;
    for(i=0; i<256; i++, group++) {
        if(group->num_members != 0) {
            MTXTrans(temp, group->center_x*group->scale_x, group->center_y*group->scale_y, 0.0f);
            MTXRotAxisDeg(rot, &axis, group->rot);
            MTXConcat(rot, temp, group->mtx);
            MTXScale(temp, group->scale_x, group->scale_y, 1.0f);
            MTXConcat(group->mtx, temp, group->mtx);
            mtxTransCat(group->mtx, group->x, group->y, 0);
            for(j=0; j<group->num_members; j++) {
                if(group->members[j] != -1) {
                    HuSprOrderEntry(i, group->members[j]);
                }
            }
        }
    }
    HuSprOrderNo = 0;
}

static void HuSprOrderEntry(s16 group, s16 sprite)
{
    SpriteOrderData *order = &HuSprOrder[HuSprOrderNum];
    s16 prio = HuSprData[sprite].prio;
    s16 prev, next;
    if(HuSprOrderNum >= 384*2) {
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
        if(sprite->attr & 0x10) {
            return sprite;
        }
        sprite->frame_data = &sprite->data->bank[sprite->bank].frame[sprite->frame];
        sprite->pat_data = &sprite->data->pat[sprite->frame_data->pat];
        return sprite;
    } else {
        return NULL;
    }
}

void HuSprFinish(void)
{
    AnimData *anim;
    AnimBankData *bank;
    AnimFrameData *frame;
    SpriteData *sprite;
    s16 i;
    s16 j;
    s16 wrap;
    s16 dir;
    
    
    for(sprite = &HuSprData[1], i=1; i<384; i++, sprite++) {
        if(sprite->data && !(sprite->attr & 0x10)) {
            if(!HuSprPauseF || (sprite->attr & 0x20)) {
                anim = sprite->data;
                bank = &anim->bank[sprite->bank];
                frame = &bank->frame[sprite->frame];
                wrap = (sprite->attr & 0x2) ? 0 : 1;
                if(!(sprite->attr & 0x1)) {
                    dir = (sprite->attr & 0x40) ? -1 : 1;
                    for(j=0; j<(int)sprite->speed*minimumVcount; j++) {
                        sprite->time += dir;
                        if(sprite->time >= frame->time) {
                            sprite->frame++;
                            sprite->time -= frame->time;
                            if(sprite->frame >= bank->timeNum || frame[1].time == -1) {
                                if(wrap) {
                                    sprite->frame = 0;
                                } else {
                                    sprite->frame = bank->timeNum-1;
                                }
                            }
                            frame = &bank->frame[sprite->frame];
                        } else if(sprite->time < 0) {
                            sprite->frame--;
                            if(sprite->frame < 0) {
                                if(wrap) {
                                    sprite->frame = bank->timeNum-1;
                                } else {
                                    sprite->frame = 0;
                                }
                            }
                            frame = &bank->frame[sprite->frame];
                            sprite->time += frame->time;
                        }
                    }
                    sprite->time += (sprite->speed*(float)minimumVcount)-j;
                    if(sprite->time >= frame->time) {
                        sprite->frame++;
                        sprite->time -= frame->time;
                        if(sprite->frame >= bank->timeNum || frame[1].time == -1) {
                            if(wrap) {
                                sprite->frame = 0;
                            } else {
                                sprite->frame = bank->timeNum-1;
                            }
                        }
                        frame = &bank->frame[sprite->frame];
                    } else if(sprite->time < 0) {
                        sprite->frame--;
                        if(sprite->frame < 0) {
                            if(wrap) {
                                sprite->frame = bank->timeNum-1;
                            } else {
                                sprite->frame = 0;
                            }
                        }
                        frame = &bank->frame[sprite->frame];
                        sprite->time += frame->time;
                    }
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
    s16 i;
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

static s16 bitSizeTbl[11] = { 32, 24, 16, 8, 4, 10, 8, 8, 4, 8, 4 };
