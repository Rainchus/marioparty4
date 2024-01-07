#include "game/gamework_data.h"
#include "game/flag.h"
#include "math.h"

extern s16 fn_80083F84(void);
extern void BoardModelPosSetV(s16 model, Vec *pos);

typedef s32 (*BoardSpaceEventFunc)(void);

typedef struct board_space {
	Vec pos;
	u32 flag;
	Vec scale;
	Vec rot;
	u16 type;
	u16 link_cnt;
	u16 link[5];
} BoardSpace;

static GXTexObj spaceHiliteTex;
static GXTexObj spaceTex;
s16 boardSpaceStarTbl[8];
static BoardSpace spaceData[2][256];

static s16 spaceCnt[2];
static u32 spaceAttr[2];
static void *spaceTexData;
static void *spaceHiliteTexData;
static GXTexFmt spaceTexFmt;
static GXTexFmt spaceHiliteTexFmt;
s16 lbl_801D3FC4[4];
static BoardSpaceEventFunc landEventFunc;
static BoardSpaceEventFunc walkMiniEventFunc;
static BoardSpaceEventFunc walkEventFunc;
static s32 spaceDrawCnt;
static s16 spaceDrawF;

static s16 spaceDrawMdl = -1;
static s16 starMdl = -1;

s32 BoardSpaceRotGet(s32 layer, s32 index, Vec *rot);

void BoardSpaceWalkEventFuncSet(BoardSpaceEventFunc func)
{
	walkEventFunc = func;
}

void BoardSpaceWalkMiniEventFuncSet(BoardSpaceEventFunc func)
{
	walkMiniEventFunc = func;
}

void BoardSpaceLandEventFuncSet(BoardSpaceEventFunc func)
{
	landEventFunc = func;
}

s32 BoardSpaceWalkEventExec(void)
{
	s32 ret = -1;
	if(walkEventFunc) {
		ret = walkEventFunc();
	}
	return ret;
}

s32 BoardSpaceWalkMiniEventExec(void)
{
	s32 ret = -1;
	if(walkMiniEventFunc) {
		_SetFlag(FLAG_ID_MAKE(1, 8));
		ret = walkMiniEventFunc();
		_ClearFlag(FLAG_ID_MAKE(1, 8));
	}
	return ret;
}

s16 BoardSpaceCountGet(s32 layer)
{
	return spaceCnt[layer];
}

BoardSpace *BoardSpaceGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return NULL;
	} else {
		return &spaceData[layer][index-1];
	}
}

void BoardSpaceAttrSet(s32 layer, u32 attr)
{
	spaceAttr[layer] |= attr;
}

void BoardSpaceAttrReset(s32 layer, u32 attr)
{
	spaceAttr[layer] &= ~attr;
}

u32 BoardSpaceFlagGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return 0;
	} else {
		return spaceData[layer][index-1].flag;
	}
}

u16 BoardSpaceTypeGet(s32 layer, s32 index)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return 0;
	} else {
		return spaceData[layer][index-1].type;
	}
}

void BoardSpaceTypeSet(s32 layer, s32 index, int type)
{
	if(index <= 0 || index > spaceCnt[layer]) {
		return;
	} else {
		spaceData[layer][index-1].type = type;
	}
}

s32 BoardSpacePosGet(s32 layer, s32 index, Vec *pos)
{
	BoardSpace *space = BoardSpaceGet(layer, index);
	if(!space) {
		return -1;
	} else {
		*pos = space->pos;
		return 0;
	}
}

void BoardSpaceCornerPosGet(s32 index, s32 corner, Vec *pos)
{
	Vec corner_ofs;
	Vec rot;
	s8 corner_pos[4][2] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
	BoardSpaceRotGet(0, index, &rot);
	BoardSpacePosGet(0, index, pos);
	corner_ofs.x = corner_pos[corner][0]*80.0f;
	corner_ofs.y = 0;
	corner_ofs.z = corner_pos[corner][1]*80.0f;
	corner_ofs.x = (cos((M_PI*rot.z)/180)*corner_ofs.x)+(sin((M_PI*rot.z)/180)*corner_ofs.y);
	corner_ofs.y = (cos((M_PI*rot.x)/180)*cos((M_PI*rot.z)/180)*corner_ofs.y)
		+(sin((M_PI*rot.z)/180)*corner_ofs.x)
		+(sin((M_PI*-rot.x)/180)*corner_ofs.z);
	corner_ofs.z = (sin((M_PI*rot.x)/180)*corner_ofs.y)+(cos((M_PI*rot.x)/180)*corner_ofs.z);
	pos->x += corner_ofs.x;
	pos->y += corner_ofs.y;
	pos->z += corner_ofs.z;
}

s32 BoardSpaceRotGet(s32 layer, s32 index, Vec *rot)
{
	BoardSpace *space = BoardSpaceGet(layer, index);
	if(!space) {
		return -1;
	} else {
		*rot = space->rot;
		return 0;
	}
}

s32 BoardSpaceFlagSearch(s32 layer, u32 flag)
{
	s32 i;
	for(i=0; i<spaceCnt[layer]; i++) {
		BoardSpace *space = &spaceData[layer][i];
		if((space->flag & flag) == flag) {
			return space-(&spaceData[layer][0])+1;
		}
	}
	return -1;
}

s32 BoardSpaceFlagPosGet(s32 layer, u32 flag, Vec *pos)
{
	s32 space = BoardSpaceFlagSearch(layer, flag);
	if(space == -1) {
		return -1;
	}
	if(pos) {
		BoardSpacePosGet(layer, space, pos);
	}
	return space;
}

s32 BoardSpaceLinkFlagSearch(s32 layer, s32 index, u32 flag)
{
	BoardSpace *space = BoardSpaceGet(layer, index);
	s32 i;
	if(!space) {
		return -1;
	}
	for(i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->flag & flag) {
			return link_space-&spaceData[layer][0]+1;
		}
	}
	return -1;
}

s32 BoardSpaceLinkTypeListGet(s32 layer, s32 index, int type, s16 *list)
{
	s32 count;
	BoardSpace *space = BoardSpaceGet(layer, index);
	s32 i;
	if(!space) {
		return -1;
	}
	for(count=i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->type == type && count < 4) {
			list[count] = link_space-&spaceData[layer][0]+1;
			count++;
		}
	}
	return count;
}

s32 BoardSpaceLinkTargetListGet(s32 layer, s32 target, s16 *list)
{
	s32 i, j;
	s32 count;
	BoardSpace *space;
	memset(list, 0, 4*sizeof(s16));
	space = &spaceData[layer][0];
	for(count=i=0; i<spaceCnt[layer]; i++, space++) {
		for(j=0; j<space->link_cnt; j++) {
			if(space->link[j] == target && count < 4) {
				list[count++] = space-&spaceData[layer][0]+1;
			}
		}
	}
	return count;
}

s32 BoardSpaceLinkTypeSearch(s32 layer, s32 target, u16 type)
{
	s32 i;
	BoardSpace *space = BoardSpaceGet(layer, target);
	if(!space) {
		return -1;
	}
	for(i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(layer, space->link[i]);
		if(link_space->type == type) {
			return space->link[i];
		}
	}
	return -1;
}

s32 BoardSpaceLinkTransformGet(s32 flag, Vec *pos, Vec *rot, Vec *scale)
{
	s32 i;
	s32 space_flag = BoardSpaceFlagSearch(0, flag);
	BoardSpace *space = BoardSpaceGet(0, space_flag);
	
	for(i=0; i<space->link_cnt; i++) {
		BoardSpace *link_space = BoardSpaceGet(0, space->link[i]);
		BoardSpace *src_space;
		if(!(link_space->flag & 0x2000000)) {
			continue;
		}
		src_space = BoardSpaceGet(0, link_space->link[0]);
		if(pos) {
			*pos = src_space->pos;
		}
		if(rot) {
			*rot = src_space->rot;
		}
		if(scale) {
			*scale = src_space->scale;
		}
		return 0;
	}
	return -1;
}

void BoardSpaceStarSet(s32 space)
{
	s16 space_platid;
	BoardSpace *space_plat;
	Vec pos;
	BoardSpaceTypeSet(0, space, 8);
	space_platid = BoardSpaceLinkFlagSearch(0, space, 0x04000000);
	space_plat = BoardSpaceGet(0, space_platid);
	if(space_plat) {
		pos = space_plat->pos;
	}
	BoardModelPosSetV(fn_80083F84(), &pos);
}