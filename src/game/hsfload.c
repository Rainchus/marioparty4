#include "game/hsfformat.h"

GXColor rgba[100];
HsfHeader head;
HsfData Model;

static BOOL MotionOnly;
static HsfData *MotionModel;
static void *VertexDataTop;
static void *NormalDataTop;
void *fileptr;
char *StringTable;
char *DicStringTable;
void **NSymIndex;
HsfObject *objtop;
HsfVertexBuf *vtxtop;
HsfCluster *ClusterTop;
HsfAttribute *AttributeTop;
HsfMaterial *MaterialTop;

static void FileLoad(void *data);
static HsfData *SetHsfModel(void);
static void MaterialLoad(void);
static void AttributeLoad(void);
static void SceneLoad(void);
static void ColorLoad(void);
static void VertexLoad(void);
static void NormalLoad(void);
static void STLoad(void);
static void FaceLoad(void);
static void ObjectLoad(void);
static void CenvLoad(void);
static void SkeletonLoad(void);
static void PartLoad(void);
static void ClusterLoad(void);
static void ShapeLoad(void);
static void MapAttrLoad(void);
static void PaletteLoad(void);
static void BitmapLoad(void);
static void MotionLoad(void);
static void MatrixLoad(void);

static HsfBitmap *SearchBitmapPtr(s32 id);
static char *GetString(u32 *str_ofs);

HsfData *LoadHSF(void *data)
{
    HsfData *hsf;
    Model.root = NULL;
    objtop = NULL;
    FileLoad(data);
    SceneLoad();
    ColorLoad();
    PaletteLoad();
    BitmapLoad();
    MaterialLoad();
    AttributeLoad();
    VertexLoad();
    NormalLoad();
    STLoad();
    FaceLoad();
    ObjectLoad();
    CenvLoad();
    SkeletonLoad();
    PartLoad();
    ClusterLoad();
    ShapeLoad();
    MapAttrLoad();
    MotionLoad();
    MatrixLoad();
    hsf = SetHsfModel();
    InitEnvelope(hsf);
    objtop = NULL;
    return hsf;
    
}

static void FileLoad(void *data)
{
    fileptr = data;
    memcpy(&head, fileptr, sizeof(HsfHeader));
    memset(&Model, 0, sizeof(HsfData));
    NSymIndex = (void **)((u32)fileptr+head.symbol.ofs);
    StringTable = (char *)((u32)fileptr+head.string.ofs);
    ClusterTop = (HsfCluster *)((u32)fileptr+head.cluster.ofs);
    AttributeTop = (HsfAttribute *)((u32)fileptr+head.attribute.ofs);
    MaterialTop = (HsfMaterial *)((u32)fileptr+head.material.ofs);
}

static HsfData *SetHsfModel(void)
{
    HsfData *data = fileptr;
    data->scene = Model.scene;
    data->sceneCnt = Model.sceneCnt;
    data->attribute = Model.attribute;
    data->attributeCnt = Model.attributeCnt;
    data->bitmap = Model.bitmap;
    data->bitmapCnt = Model.bitmapCnt;
    data->cenv = Model.cenv;
    data->cenvCnt = Model.cenvCnt;
    data->skeleton = Model.skeleton;
    data->skeletonCnt = Model.skeletonCnt;
    data->face = Model.face;
    data->faceCnt = Model.faceCnt;
    data->material = Model.material;
    data->materialCnt = Model.materialCnt;
    data->motion = Model.motion;
    data->motionCnt = Model.motionCnt;
    data->normal = Model.normal;
    data->normalCnt = Model.normalCnt;
    data->root = Model.root;
    data->objectCnt = Model.objectCnt;
    data->object = objtop;
    data->matrix = Model.matrix;
    data->matrixCnt = Model.matrixCnt;
    data->palette = Model.palette;
    data->paletteCnt = Model.paletteCnt;
    data->st = Model.st;
    data->stCnt = Model.stCnt;
    data->vertex = Model.vertex;
    data->vertexCnt = Model.vertexCnt;
    data->cenv = Model.cenv;
    data->cenvCnt = Model.cenvCnt;
    data->cluster = Model.cluster;
    data->clusterCnt = Model.clusterCnt;
    data->part = Model.part;
    data->partCnt = Model.partCnt;
    data->shape = Model.shape;
    data->shapeCnt = Model.shapeCnt;
    data->mapAttr = Model.mapAttr;
    data->mapAttrCnt = Model.mapAttrCnt;
    return data;
}

char *SetName(u32 *str_ofs)
{
    char *ret = GetString(str_ofs);
    return ret;
}

static void MaterialLoad(void)
{
    s32 i;
    s32 j;
    if(head.material.count) {
        HsfMaterial *file_mat = (HsfMaterial *)((u32)fileptr+head.material.ofs);
        HsfMaterial *curr_mat;
        HsfMaterial *new_mat;
        for(i=0; i<head.material.count; i++) {
            curr_mat = &file_mat[i];
        }
        new_mat = file_mat;
        Model.material = new_mat;
        Model.materialCnt = head.material.count;
        file_mat = (HsfMaterial *)((u32)fileptr+head.material.ofs);
        for(i=0; i<head.material.count; i++, new_mat++) {
            curr_mat = &file_mat[i];
            new_mat->name = SetName((u32 *)&curr_mat->name);
            new_mat->pass = curr_mat->pass;
            new_mat->vtxMode = curr_mat->vtxMode;
            new_mat->litColor[0] = curr_mat->litColor[0];
            new_mat->litColor[1] = curr_mat->litColor[1];
            new_mat->litColor[2] = curr_mat->litColor[2];
            new_mat->color[0] = curr_mat->color[0];
            new_mat->color[1] = curr_mat->color[1];
            new_mat->color[2] = curr_mat->color[2];
            new_mat->shadowColor[0] = curr_mat->shadowColor[0];
            new_mat->shadowColor[1] = curr_mat->shadowColor[1];
            new_mat->shadowColor[2] = curr_mat->shadowColor[2];
            new_mat->hilite_scale = curr_mat->hilite_scale;
            new_mat->unk18 = curr_mat->unk18;
            new_mat->invAlpha = curr_mat->invAlpha;
            new_mat->unk20[0] = curr_mat->unk20[0];
            new_mat->unk20[1] = curr_mat->unk20[1];
            new_mat->refAlpha = curr_mat->refAlpha;
            new_mat->unk2C = curr_mat->unk2C;
            new_mat->numAttrs = curr_mat->numAttrs;
            new_mat->attrs = (HsfAttribute **)(NSymIndex+((u32)curr_mat->attrs));
            rgba[i].r = new_mat->litColor[0];
            rgba[i].g = new_mat->litColor[1];
            rgba[i].b = new_mat->litColor[2];
            rgba[i].a = 255;
            for(j=0; j<new_mat->numAttrs; j++) {
                new_mat->attrs[j] = new_mat->attrs[j];
            }
        }
    }
}

static void AttributeLoad(void)
{
    HsfAttribute *file_attr;
    HsfAttribute *new_attr;
    HsfAttribute *temp_attr;
    s32 i;
    if(head.attribute.count) {
        temp_attr = file_attr = (HsfAttribute *)((u32)fileptr+head.attribute.ofs);
        new_attr = temp_attr;
        Model.attribute = new_attr;
        Model.attributeCnt = head.attribute.count;
        for(i=0; i<head.attribute.count; i++, new_attr++) {
            if((u32)file_attr[i].name != -1) {
                new_attr->name = SetName((u32 *)&file_attr[i].name);
            } else {
                new_attr->name = NULL;
            }
            new_attr->bitmap = SearchBitmapPtr((s32)file_attr[i].bitmap);
        }
    }
}

static void SceneLoad(void)
{
    HsfScene *file_scene;
    HsfScene *new_scene;
    if(head.scene.count) {
        file_scene = (HsfScene *)((u32)fileptr+head.scene.ofs);
        new_scene = file_scene;
        new_scene->unk8 = file_scene->unk8;
        new_scene->unk4 = file_scene->unk4;
        Model.scene = new_scene;
        Model.sceneCnt = head.scene.count;
    }
}


static void ColorLoad(void)
{
    s32 i;
    HsfVertexBuf *file_color;
    HsfVertexBuf *new_color;
    void *data;
    void *color_data;
    HsfVertexBuf *temp_color;
    
    if(head.color.count) {
        temp_color = file_color = (HsfVertexBuf *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, file_color++);
        new_color = temp_color;
        Model.color = new_color;
        Model.colorCnt = head.color.count;
        file_color = (HsfVertexBuf *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, new_color++, file_color++) {
            color_data = file_color->data;
            new_color->name = SetName((u32 *)&file_color->name);
            new_color->data = (void *)((u32)data+(u32)color_data);
        }
    }
}

static HsfBitmap *SearchBitmapPtr(s32 id)
{
    HsfBitmap *bitmap; 
    if(id == -1) {
        return NULL;
    }
    bitmap = (HsfBitmap *)((u32)fileptr+head.bitmap.ofs);
    bitmap += id;
    return bitmap;
}

static char *GetString(u32 *str_ofs)
{
    char *ret = &StringTable[*str_ofs];
    return ret;
}

static char *GetMotionString(u16 *str_ofs)
{
    char *ret = &StringTable[*str_ofs];
    return ret;
}