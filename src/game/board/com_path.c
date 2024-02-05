#include "game/board/com_path.h"
#include "game/board/space.h"

#define NODE_INDEX(x) ((x) ? ((x) - pathNodeData) : -1)

typedef struct {
    /* 0x00 */ struct {
        u8 unk00_field0 : 1;
        u8 unk00_field1 : 1;
        s8 unk00_field2 : 1;
        s8 unk00_field3 : 1;
        u8 unk00_field4 : 1;
        u8 unk00_field5 : 1;
    };
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06[2]; // array size unknown
    /* 0x0A */ char unk0A[0x3C];
    /* 0x46 */ s16 unk46[5];
} PathNode; // Size 0x50

static PathNode *SearchPathNodeSpace(s16 arg0);
static s16 InitPathNode(PathNode *arg0);
static PathNode *FindChildNode(s16 arg0, PathNode *arg1);
static s32 GetNumValidLinks(BoardSpace *arg0, PathNode *arg1);
static void AddValidLinks(BoardSpace *arg0, PathNode *arg1);
static BOOL CheckPathSpace(BoardSpace *arg0);
static s16 FindValidLink(BoardSpace *arg0);
static BOOL CheckEndSpace(BoardSpace *arg0, PathNode *arg1);
static BOOL CheckPath(PathNode *arg0);
static BOOL CheckW20Path(PathNode *arg0, u32 arg1);

static PathNode pathNodeData[16];
static PathNode *candidateNodes[16];
static s16 startPathSpaceSearch[16];
static s16 startPathSpace[16];

static s16 numCandidates;
static s16 childNodeCnt;

static PathNode *SearchPathNodeSpace(s16 arg0) {
    PathNode *var_r31;
    s32 i;

    for (var_r31 = pathNodeData, i = 0; i < 16; i++, var_r31++) {
        if (var_r31->unk04 == arg0) {
            break;
        }
    }
    if (i == 16) {
        var_r31 = NULL;
    }
    return var_r31;
}

static s16 InitPathNode(PathNode *arg0) {
    BoardSpace *temp_r30;
    PathNode *var_r23;
    s32 var_r29;
    s16 i;
    s16 var_r27;
    s16 var_r26;
    s16 var_r25;
    s16 var_r24;

    var_r24 = arg0->unk04;
    var_r29 = 0;
    arg0->unk02 = var_r25 = 0;
    do {
        var_r27 = var_r24;
        temp_r30 = BoardSpaceGet(0, var_r27);
        arg0->unk06[arg0->unk02] = var_r27;
        var_r23 = FindChildNode(var_r27, arg0);
        if (var_r23) {
            AddValidLinks(temp_r30, arg0);
            arg0->unk01 = 1;
            arg0->unk46[0] = var_r27;
            for (i = 1; i < 5; i++) {
                arg0->unk46[i] = 0;
            }
            return 0;
        }
        if (temp_r30->link_cnt == 0) {
            var_r26 = 0;
            var_r29 = 1;
        } else {
            var_r26 = GetNumValidLinks(temp_r30, arg0);
            if (var_r26 == 1) {
                var_r24 = FindValidLink(temp_r30);
            } else {
                var_r29 = 1;
            }
        }
        if (CheckEndSpace(temp_r30, arg0)) {
            var_r25++;
            if (var_r25 >= arg0->unk03) {
                var_r26 = 0;
                var_r29 = 1;
            }
        }
        arg0->unk02++;
    } while (var_r29 == 0);
    AddValidLinks(temp_r30, arg0);
    arg0->unk01 = var_r26;
    return arg0->unk03 - var_r25;
}

static PathNode *FindChildNode(s16 arg0, PathNode *arg1) {
    PathNode *temp_r31;
    s32 var_r28;
    s32 i;
    s32 j;

    var_r28 = NODE_INDEX(arg1);
    if (var_r28 == -1) {
        return NULL;
    }
    for (i = 0; i < childNodeCnt; i++) {
        temp_r31 = &pathNodeData[i];
        if (temp_r31 != arg1) {
            for (j = 0; j < temp_r31->unk02; j++) {
                if (arg0 == temp_r31->unk06[j]) {
                    return temp_r31;
                }
            }
        }
    }
    return NULL;
}

static s32 GetNumValidLinks(BoardSpace *arg0, PathNode *arg1) {
    BoardSpace *var_r28;
    s16 i;
    s16 var_r29;

    for (var_r29 = i = 0; i < arg0->link_cnt; i++) {
        var_r28 = BoardSpaceGet(0, arg0->link[i]);
        if (!CheckPathSpace(var_r28)) {
            var_r29++;
        }
    }
    if (var_r29 >= arg0->link_cnt) {
        return 0;
    }
    return arg0->link_cnt - var_r29;
}

static void AddValidLinks(BoardSpace *arg0, PathNode *arg1) {
    BoardSpace *var_r27;
    s16 var_r30;
    s16 var_r31;

    for (var_r31 = var_r30 = 0; var_r30 < arg0->link_cnt; var_r30++) {
        var_r27 = BoardSpaceGet(0, arg0->link[var_r30]);
        if (CheckPathSpace(var_r27)) {
            arg1->unk46[var_r31] = arg0->link[var_r30];
            var_r31++;
        }
    }
    for (; var_r31 < 5; var_r31++) {
        arg1->unk46[var_r31] = 0;
    }
}

static BOOL CheckPathSpace(BoardSpace *arg0) {
    if ((arg0->flag & 0x02000000) || (arg0->flag & 0x04000000)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static s16 FindValidLink(BoardSpace *arg0) {
    s16 var_r29;
    s16 i;
    BoardSpace *temp_r30;

    for (var_r29 = i = 0; i < arg0->link_cnt; i++) {
        var_r29 = arg0->link[i];
        temp_r30 = BoardSpaceGet(0, var_r29);
        if (CheckPathSpace(temp_r30)) {
            break;
        }
    }
    return var_r29;
}

static BOOL CheckEndSpace(BoardSpace *arg0, PathNode *arg1) {
    if (arg0->flag & 0x80000000) {
    }
    if (arg0->flag & 0x4000000) {
    }
    if (arg0->flag & 0x2000000) {
    }
    if (arg0->flag & 0x180000) {
        arg1->unk00_field3 = 1;
    }
    if (arg0->flag & 0x48000000) {
        arg1->unk00_field4 = 1;
    }
    if (arg0->flag & 0x20000000) {
        arg1->unk00_field2 = 1;
    }
    if (arg0->flag & 0x10000000) {
        arg1->unk00_field5 = 1;
    }
    switch (arg0->type) {
        case 8:
            arg1->unk00_field1 = 1;
            return FALSE;
        case 10:
            return FALSE;
        case 0:
            return FALSE;
    }
    return TRUE;
}

static inline void ComPathInlineFunc02(PathNode *arg0) {
    if (numCandidates < 16) {
        candidateNodes[numCandidates] = arg0;
        numCandidates++;
    }
}

static inline PathNode *ComPathInlineFunc03(void) {
    PathNode *ret;

    numCandidates--;
    if (numCandidates < 0) {
        return NULL;
    } else {
        ret = candidateNodes[numCandidates];
        candidateNodes[numCandidates] = NULL;
        return ret;
    }
}

static inline PathNode *ComPathInlineFunc04(s16 arg0, s16 arg1) {
    PathNode *var_r26;
    s32 i;

    var_r26 = pathNodeData;
    for (i = 0; i < 16; i++, var_r26++) {
        if (var_r26->unk00_field0 == 0) {
            break;
        }
    }
    if (i == 16) {
        return NULL;
    } else {
        var_r26->unk00_field0 = 1;
        var_r26->unk04 = arg0;
        var_r26->unk03 = arg1;
        childNodeCnt++;
        return var_r26;
    }
}

static inline void ComPathInlineFunc05(s16 arg0, s16 arg1) {
    PathNode *var_r28;
    s32 var_r24;
    s32 temp_r17;
    s32 i;
    PathNode *var_r23;

    memset(pathNodeData, 0, sizeof(pathNodeData));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    childNodeCnt = 0;
    var_r23 = ComPathInlineFunc04(arg0, arg1);
    ComPathInlineFunc02(var_r23);
    var_r24 = 1;
    temp_r17 = arg1;
    while (1) {
        if (var_r24 <= 0) {
            break;
        }
        var_r28 = ComPathInlineFunc03();
        if (!var_r28) {
            break;
        }
        var_r24--;
        temp_r17 = InitPathNode(var_r28);
        if (temp_r17 != 0) {
            if (var_r28->unk01 <= 1) {
                break;
            }
            for (i = 0; i < var_r28->unk01; var_r24++, i++) {
                var_r23 = ComPathInlineFunc04(var_r28->unk46[i], temp_r17);
                if (!var_r23) {
                    break;
                }
                ComPathInlineFunc02(var_r23);
            }
        }
    }
}

s16 BoardComPathReachCheck(s16 arg0, u32 arg1, s32 arg2) {
    s16 sp80[10];
    s16 sp6C[10];
    PathNode *sp68;
    PathNode *var_r29;
    s16 sp1C;
    s16 sp1A;
    s16 temp_r20;
    s16 var_r22;
    s16 var_r28;
    s16 i;
    s32 var_r19;

    if (_CheckFlag(0x1000B)) {
        return 0;
    }
    ComPathInlineFunc05(arg0, 0x1E);
    memset(startPathSpaceSearch, 0, sizeof(startPathSpaceSearch));
    memset(sp80, 0, sizeof(sp80));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    var_r29 = SearchPathNodeSpace(arg0);
    sp1A = NODE_INDEX(var_r29);
    ComPathInlineFunc02(var_r29);
    var_r28 = 0;
    var_r22 = 0;
    startPathSpaceSearch[sp1A] = var_r28;
    var_r19 = 0;
    while (1) {
        var_r29 = ComPathInlineFunc03();
        sp1C = NODE_INDEX(var_r29);
        if (sp1C == -1) {
            if (var_r22 != 0) {
                break;
            }
        } else {
            var_r19 = 0;
            var_r28 = startPathSpaceSearch[sp1C];
            for (i = 0; i < var_r29->unk02; i++) {
                if (arg2 == 0 && (BoardSpaceFlagGet(0, var_r29->unk06[i]) & 0x20000000)) {
                    break;
                }
                if (arg1 == BoardSpaceTypeGet(0, var_r29->unk06[i])) {
                    sp80[var_r22] = var_r28;
                    sp6C[var_r22] = sp1C;
                    if (++var_r22 < 0xA) {
                        var_r19 = 1;
                        break;
                    } else {
                        goto return_r28;
                    }
                }
                if (var_r28++ >= 0x1E) {
                    var_r19 = 1;
                    break;
                }
            }
            if (var_r19 == 0) {
                for (i = 0; i < var_r29->unk01; i++) {
                    sp68 = SearchPathNodeSpace(var_r29->unk46[i]);
                    temp_r20 = NODE_INDEX(sp68);
                    if (temp_r20 != -1 && temp_r20 >= 0 && temp_r20 < 16) {
                        startPathSpaceSearch[temp_r20] = var_r28;
                        ComPathInlineFunc02(sp68);
                    }
                }
            }
            continue;
        }
        return 0;
    }
return_r28:
    var_r28 = 10000;
    for (i = 0; i < 10; i++) {
        if (var_r28 > sp80[i] && sp80[i] != 0) {
            var_r28 = sp80[i];
        }
    }
    return var_r28;
}

s16 BoardComPathBestGet(s16 arg0) {
    PathNode *sp30;
    PathNode *sp2C;
    s32 i;

    ComPathInlineFunc05(arg0, 0x1E);
    sp2C = SearchPathNodeSpace(arg0);
    if (sp2C->unk00_field1 != 0) {
        return -1;
    }
    if (sp2C->unk01 <= 1) {
        return -1;
    }
    for (i = 0; i < sp2C->unk01; i++) {
        sp30 = SearchPathNodeSpace(sp2C->unk46[i]);
        if (sp30 && CheckPath(sp30)) {
            return sp2C->unk46[i];
        }
    }
    return -1;
}

s16 BoardComPathLenGet(s16 arg0, s16 arg1) {
    PathNode *var_r30;
    s16 temp_r21;
    s16 var_r25;
    s16 sp16;
    s16 sp14;
    s16 sp12;
    s16 i;
    s32 sp5C;
    PathNode *sp58;

    ComPathInlineFunc05(arg0, 0x1E);
    memset(startPathSpace, 0, sizeof(startPathSpace));
    memset(candidateNodes, 0, sizeof(candidateNodes));
    numCandidates = 0;
    var_r30 = SearchPathNodeSpace(arg0);
    sp12 = NODE_INDEX(var_r30);
    ComPathInlineFunc02(var_r30);
    var_r25 = 0;
    sp16 = 0;
    startPathSpace[sp12] = var_r25;
    sp5C = 0;
    while (1) {
        var_r30 = ComPathInlineFunc03();
        sp14 = NODE_INDEX(var_r30);
        if (sp14 == -1) {
            if (sp16 != 0) {
                break;
            }
        } else {
            sp5C = 0;
            var_r25 = startPathSpace[sp14];
            for (i = 0; i < var_r30->unk02; i++) {
                if (BoardSpaceFlagGet(0, var_r30->unk06[i]) & 0x20000000) {
                    break;
                }
                if (var_r30->unk06[i] == arg1) {
                    goto return_r25;
                }
                if (var_r25++ >= 0x1E) {
                    sp5C = 1;
                    break;
                }
            }
            if (sp5C == 0) {
                for (i = 0; i < var_r30->unk01; i++) {
                    sp58 = SearchPathNodeSpace(var_r30->unk46[i]);
                    temp_r21 = NODE_INDEX(sp58);
                    if (temp_r21 != -1 && temp_r21 >= 0 && temp_r21 < 16) {
                        startPathSpace[temp_r21] = var_r25;
                        ComPathInlineFunc02(sp58);
                    }
                }
            }
            continue;
        }
        return 0;
    }
return_r25:
    return var_r25;
}

static BOOL CheckPath(PathNode *arg0) {
    s32 i;
    PathNode *sp1C;

    if (arg0->unk00_field1 != 0) {
        return TRUE;
    }
    if (arg0->unk01 <= 1) {
        return FALSE;
    }
    for (i = 0; i < arg0->unk01; i++) {
        sp1C = SearchPathNodeSpace(arg0->unk46[i]);
        if (sp1C && CheckPath(sp1C)) {
            return TRUE;
        }
    }
    return FALSE;
}

s16 BoardComPathW20BestGet(s16 arg0, u32 arg1, s16 arg2) {
    PathNode *var_r31;
    PathNode *sp38;
    s32 i;

    ComPathInlineFunc05(arg0, arg2);
    var_r31 = SearchPathNodeSpace(arg0);
    if (arg1 & 0x180000) {
        if (var_r31->unk00_field1 != 0) {
            return -1;
        }
    } else if (arg1 & 0x08000000) {
        if (var_r31->unk00_field4 != 0) {
            return -1;
        }
    } else if (arg1 & 0x10000000) {
        if (var_r31->unk00_field5 != 0) {
            return -1;
        }
    }
    if (var_r31->unk01 <= 1) {
        return -1;
    }
    for (i = 0; i < var_r31->unk01; i++) {
        sp38 = SearchPathNodeSpace(var_r31->unk46[i]);
        if (sp38 && CheckW20Path(sp38, arg1)) {
            return var_r31->unk46[i];
        }
    }
    return -1;
}

static BOOL CheckW20Path(PathNode *arg0, u32 arg1) {
    s32 i;
    PathNode *sp1C;

    if (arg1 & 0x180000) {
        if (arg0->unk00_field1 != 0) {
            return TRUE;
        }
    } else if (arg1 & 0x08000000) {
        if (arg0->unk00_field4 != 0) {
            return TRUE;
        }
    } else if (arg1 & 0x10000000) {
        if (arg0->unk00_field5 != 0) {
            return TRUE;
        }
    }
    if (arg0->unk01 <= 1) {
        return FALSE;
    }
    for (i = 0; i < arg0->unk01; i++) {
        sp1C = SearchPathNodeSpace(arg0->unk46[i]);
        if (sp1C && CheckW20Path(sp1C, arg1)) {
            return TRUE;
        }
    }
    return FALSE;
}
