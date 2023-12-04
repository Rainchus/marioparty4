#ifndef _HSF_FORMAT_H
#define _HSF_FORMAT_H

#include "dolphin.h"

#define HSF_OBJTYPE_NULL1 0
#define HSF_OBJTYPE_REPLICA 1
#define HSF_OBJTYPE_MESH 2
#define HSF_OBJTYPE_ROOT 3
#define HSF_OBJTYPE_JOINT 4
#define HSF_OBJTYPE_NULL2 5
#define HSF_OBJTYPE_NULL3 6
#define HSF_OBJTYPE_NONE1 7
#define HSF_OBJTYPE_NONE2 8
#define HSF_OBJTYPE_MAP 9

typedef struct hsf_vector3f {
    float x;
    float y;
    float z;
} HsfVector3f;

typedef struct hsf_vector2f {
    float x;
    float y;
} HsfVector2f;

typedef struct hsf_section {
    s32 ofs;
    s32 count;
} HsfSection;

typedef struct hsf_header {
    char magic[8];
    HsfSection scene;
    HsfSection color;
    HsfSection material;
    HsfSection attribute;
    HsfSection vertex;
    HsfSection normal;
    HsfSection st;
    HsfSection face;
    HsfSection object;
    HsfSection bitmap;
    HsfSection palette;
    HsfSection motion;
    HsfSection cenv;
    HsfSection skeleton;
    HsfSection part;
    HsfSection cluster;
    HsfSection shape;
    HsfSection mapAttr;
    HsfSection matrix;
    HsfSection symbol;
    HsfSection string;
} HsfHeader;

typedef struct hsf_scene {
    GXColor unk0;
    f32 unk4;
    f32 unk8;
    u32 unkC;
} HsfScene;

typedef struct hsf_bitmap {
    char *name;
    s32 maxLod;
    u8 dataFmt;
    u8 pixSize;
    s16 sizeX;
    s16 sizeY;
    s16 palSize;
    GXColor tint;
    void *palData;
    u32 unk;
    void *data;
} HsfBitmap;

typedef struct hsf_palette {
    char *name;
    s32 unk;
    u32 palSize;
    u16 *data;
} HsfPalette;

typedef struct hsf_attribute {
    char *name;
    u8 unk4[96];
    u32 wrap_s;
    u32 wrap_t;
    u8 unk6C[16];
    u32 flag;
    HsfBitmap *bitmap;
} HsfAttribute;

typedef struct hsf_material {
    char *name;
    u8 unk4[4];
    u16 pass;
    u8 vtxMode;
    u8 litColor[3];
    u8 color[3];
    u8 shadowColor[3];
    float hilite_scale;
    float unk18;
    float invAlpha;
    float unk20[2];
    float refAlpha;
    float unk2C;
    u32 flags;
    u32 numAttrs;
    HsfAttribute **attrs;
} HsfMaterial;

typedef struct hsf_vertex_buf {
    char *name;
    s32 count;
    void *data;
} HsfBuffer;

typedef struct hsf_tristrip {
    u16 data[4];
} HsfTristrip;

typedef struct hsf_face {
    u16 type;
    u16 mat;
    u16 indices[12];
    union {
        struct {
            u32 count;
            HsfTristrip *data;
        } strip;
        u16 ext_indices[4];
    };
    float nbt[3];
} HsfFace;

typedef struct hsf_const_data {
    u32 flags;
    u8 unk4[64];
} HsfConstData;

typedef struct hsf_transform {
    HsfVector3f pos;
    HsfVector3f rot;
    HsfVector3f scale;
} HsfTransform;

typedef struct hsf_cenv_single {
    u32 target;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
} HsfCenvSingle;

typedef struct hsf_cenv_dual_weight {
    float weight;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
} HsfCenvDualWeight;

typedef struct hsf_cenv_dual {
    u32 target1;
    u32 target2;
    u32 weightCnt;
    HsfCenvDualWeight *weight;
} HsfCenvDual;

typedef struct hsf_cenv_multi_weight {
    u32 target;
    float value;
} HsfCenvMultiWeight;

typedef struct hsf_cenv_multi {
    u32 weightCnt;
    u16 pos;
    u16 posCnt;
    u16 normal;
    u16 normalCnt;
    HsfCenvMultiWeight *weight;
} HsfCenvMulti;

typedef struct hsf_cenv {
    char *name;
    HsfCenvSingle *singleData;
    HsfCenvDual *dualData;
    HsfCenvMulti *multiData;
    u32 singleCount;
    u32 dualCount;
    u32 multiCount;
    u32 vtxCount;
    u32 copyCount;
} HsfCenv;

typedef struct hsf_part {
    char *name;
    u32 count;
    u16 *vertex;
} HsfPart;

typedef struct hsf_cluster {
    char *name[2];
    union {
        char *targetName;
        u32 target;
    };
    HsfPart *part;
    u8 unk10[132];
    u8 adjusted;
    u8 unk95;
    u16 type;
    u32 vertexCnt;
    HsfBuffer **vertex;
} HsfCluster;

typedef struct hsf_shape {
    char *name;
    union {
        u16 count16[2];
        u32 vertexCnt;
    };
    HsfBuffer **vertex;
} HsfShape;

typedef struct hsf_object_data {
    struct hsf_object *parent;
    u32 childrenCount;
    struct hsf_object **children;
    HsfTransform base;
    HsfTransform curr;
    union {
        struct {
            HsfVector3f min;
            HsfVector3f max;
            float baseMorph;
            float *morphWeight[33];
        } mesh;
        struct hsf_object *replica;
    };
    
    HsfBuffer *face;
    HsfBuffer *vertex;
    HsfBuffer *normal;
    HsfBuffer *color;
    HsfBuffer *st;
    HsfMaterial *material;
    HsfAttribute *attribute;
    u8 unk120[2];
    u8 shapeType;
    u32 vertexShapeCnt;
    HsfBuffer **vertexShape;
    u32 clusterCnt;
    HsfCluster **cluster;
    u32 hook;
    HsfCenv *cenv;
    void *file[2];
} HsfObjectData;

typedef struct hsf_object {
    char *name;
    s32 type;
    HsfConstData *constData;
    u32 flags;
    HsfObjectData data;
} HsfObject;

typedef struct hsf_skeleton {
    char *name;
    HsfTransform transform;
} HsfSkeleton;

typedef struct hsf_track {
    u8 mode;
    u8 value;
    s16 idx;
    s16 type;
    s16 effect;
    s16 curveType;
    s16 numKeyframes;
    void *data;
} HsfTrack;

typedef struct hsf_motion {
    char *name;
    u32 numTracks;
    HsfTrack *track;
    float len;
} HsfMotion;

typedef struct hsf_map_attr {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    s16 *data;
    u32 dataLen;
} HsfMapAttr;

typedef struct hsf_matrix {
    u32 base_idx;
    u32 count;
    Mtx *data;
} HsfMatrix;

typedef struct hsf_data {
    u8 magic[8];
    HsfScene *scene;
    HsfAttribute *attribute;
    HsfMaterial *material;
    HsfBuffer *vertex;
    HsfBuffer *normal;
    HsfBuffer *st;
    HsfBuffer *color;
    HsfBuffer *face;
    HsfBitmap *bitmap;
    HsfPalette *palette;
    HsfObject *root;
    HsfCenv *cenv;
    HsfSkeleton *skeleton;
    HsfCluster *cluster;
    HsfPart *part;
    HsfShape *shape;
    HsfMotion *motion;
    HsfObject *object;
    HsfMapAttr *mapAttr;
    HsfMatrix *matrix;
    s16 sceneCnt;
    s16 attributeCnt;
    s16 materialCnt;
    s16 vertexCnt;
    s16 normalCnt;
    s16 stCnt;
    s16 colorCnt;
    s16 faceCnt;
    s16 bitmapCnt;
    s16 paletteCnt;
    s16 objectCnt;
    s16 cenvCnt;
    s16 skeletonCnt;
    s16 clusterCnt;
    s16 partCnt;
    s16 shapeCnt;
    s16 mapAttrCnt;
    s16 motionCnt;
    s16 matrixCnt;
} HsfData;

#endif