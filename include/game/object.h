#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "dolphin.h"
#include "game/process.h"
#include "game/dvd.h"

#define OVL_DEFINE(name, path) name,

typedef enum {
    OVL_INVALID = -1,
    #include "ovl_table.h"
    OVL_COUNT
} OverlayID;

#undef OVL_DEFINE

#define OM_STAT_DELETED 0x1
#define OM_STAT_DISABLED 0x2
#define OM_STAT_ACTIVE 0x4
#define OM_STAT_PAUSED 0x10
#define OM_STAT_NOPAUSE 0x20
#define OM_STAT_MODEL_PAUSED 0x100


#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))

typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_ovl_his_data {
    OverlayID overlay;
    int event;
    int stat;
} omOvlHisData;

typedef struct om_obj_data {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 next_idx_alloc;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 next_idx;
/* 0x0C */ s16 group;
/* 0x0E */ u16 group_idx;
/* 0x10 */ int unk10;
/* 0x14 */ omObjFunc func;
/* 0x18 */ Vec trans;
/* 0x24 */ Vec rot;
/* 0x30 */ Vec scale;
/* 0x3C */ u16 mdlcnt;
/* 0x40 */ s16 *model;
/* 0x44 */ u16 mtncnt;
/* 0x48 */ s16 *motion;
/* 0x4C */ u32 work[4];
/* 0x5C */ void *data;
} omObjData;

void omMasterInit(int prio, FileListEntry *ovl_list, int ovl_count, OverlayID start_ovl);
void omOvlCallEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlGotoEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlReturnEx(s16 level, s16 arg2);
void omOvlKill(s16 arg);
void omOvlHisChg(s32 level, OverlayID overlay, int event, int stat);
omOvlHisData *omOvlHisGet(s32 level);
Process *omInitObjMan(s16 max_objs, int prio);
void omDestroyObjMan(void);
omObjData *omAddObjEx(Process *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func);
void omAddMember(Process *objman_process, u16 group, omObjData *object);
void omDelObjEx(Process *objman_process, omObjData *object);
void omDelMember(Process *objman_process, omObjData *object);
void omMakeGroupEx(Process *objman_process, u16 group, u16 max_objs);
omObjData **omGetGroupMemberListEx(Process *objman_process, s16 group);
void omSetStatBit(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omSetTra(omObjData *obj, float x, float y, float z);
void omSetRot(omObjData *obj, float x, float y, float z);
void omSetSca(omObjData *obj, float x, float y, float z);
void omMain(void);
void omAllPause(BOOL pause);
char omPauseChk(void);
OverlayID omCurrentOvlGet(void);


void omDLLDBGOut(void);
void omDLLInit(FileListEntry *ovl_list);
int omDLLStart(s16 ovl, s16 dll);
void omDLLNumEnd(s16 ovl, s16 arg2);

void omSysPauseEnable(u8 flag);

void omSystemKeyCheckSetup(Process *objman_process);

extern omObjData *omDBGSysKeyObj;
extern Process *omwatchproc;
extern OverlayID omnextovl;
extern OverlayID omcurovl;
extern int omcurdll;
extern int omovlhisidx;
extern int omovlevtno;
extern int omnextovlevtno;
extern int omovlstat;
extern char omUPauseFlag;
extern s16 omSysExitReq;
extern s16 omdispinfo;
extern char omSysPauseEnableFlag;
extern OverlayID omprevovl;

#endif