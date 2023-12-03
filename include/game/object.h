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

typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_ovl_his_data {
    OverlayID overlay;
    int event;
    int stat;
} omOvlHisData;

typedef struct om_obj_data {
    u16 stat;
    s16 next_idx_alloc;
    s16 prio;
    s16 prev;
    s16 next;
    s16 next_idx;
    s16 group;
    u16 group_idx;
    int unk10;
    omObjFunc func;
    Vec trans;
    Vec rot;
    Vec scale;
    u16 mdlcnt;
    s16 *model;
    u16 mtncnt;
    s16 *motion;
    int work[4];
    void *data;
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

void omSysPauseEnable(BOOL flag);

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