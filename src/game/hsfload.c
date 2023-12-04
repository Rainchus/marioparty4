#include "game/hsfformat.h"
#include "string.h"

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
HsfBuffer *vtxtop;
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

static HsfBuffer *SearchVertexPtr(s32 id);
static HsfBuffer *SearchNormalPtr(s32 id);
static HsfBuffer *SearchStPtr(s32 id);
static HsfBuffer *SearchColorPtr(s32 id);
static HsfBuffer *SearchFacePtr(s32 id);
static HsfCenv *SearchCenvPtr(s32 id);
static HsfPart *SearchPartPtr(s32 id);
static HsfPalette *SearchPalettePtr(s32 id);

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
    HsfBuffer *file_color;
    HsfBuffer *new_color;
    void *data;
    void *color_data;
    HsfBuffer *temp_color;
    
    if(head.color.count) {
        temp_color = file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, file_color++);
        new_color = temp_color;
        Model.color = new_color;
        Model.colorCnt = head.color.count;
        file_color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
        data = &file_color[head.color.count];
        for(i=0; i<head.color.count; i++, new_color++, file_color++) {
            color_data = file_color->data;
            new_color->name = SetName((u32 *)&file_color->name);
            new_color->data = (void *)((u32)data+(u32)color_data);
        }
    }
}

static void VertexLoad(void)
{
    s32 i, j;
    HsfBuffer *file_vertex;
    HsfBuffer *new_vertex;
    void *data;
    HsfVector3f *data_elem;
    void *temp_data;
    
    if(head.vertex.count) {
        vtxtop = file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, file_vertex++) {
            for(j=0; j<(u32)file_vertex->count; j++) {
                data_elem = (HsfVector3f *)(((u32)data)+((u32)file_vertex->data)+(j*sizeof(HsfVector3f)));
            }
        }
        new_vertex = vtxtop;
        Model.vertex = new_vertex;
        Model.vertexCnt = head.vertex.count;
        file_vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
        VertexDataTop = data = (void *)&file_vertex[head.vertex.count];
        for(i=0; i<head.vertex.count; i++, new_vertex++, file_vertex++) {
            temp_data = file_vertex->data;
            new_vertex->count = file_vertex->count;
            new_vertex->name = SetName((u32 *)&file_vertex->name);
            new_vertex->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_vertex->count; j++) {
                data_elem = (HsfVector3f *)(((u32)data)+((u32)temp_data)+(j*sizeof(HsfVector3f)));
                ((HsfVector3f *)new_vertex->data)[j].x = data_elem->x;
                ((HsfVector3f *)new_vertex->data)[j].y = data_elem->y;
                ((HsfVector3f *)new_vertex->data)[j].z = data_elem->z;
            }
        }
    }
}

static void NormalLoad(void)
{
    s32 i, j;
    void *temp_data;
    HsfBuffer *file_normal;
    HsfBuffer *new_normal;
    HsfBuffer *temp_normal;
    void *data;
    
    
    if(head.normal.count) {
        s32 cenv_count = head.cenv.count;
        temp_normal = file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        data = (void *)&file_normal[head.normal.count];
        new_normal = temp_normal;
        Model.normal = new_normal;
        Model.normalCnt = head.normal.count;
        file_normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
        NormalDataTop = data = (void *)&file_normal[head.normal.count];
        for(i=0; i<head.normal.count; i++, new_normal++, file_normal++) {
            temp_data = file_normal->data;
            new_normal->count = file_normal->count;
            new_normal->name = SetName((u32 *)&file_normal->name);
            new_normal->data = (void *)((u32)data+(u32)temp_data);
        }
    }
}

static void STLoad(void)
{
    s32 i, j;
    HsfBuffer *file_st;
    HsfBuffer *temp_st;
    HsfBuffer *new_st;
    void *data;
    HsfVector2f *data_elem;
    void *temp_data;
    
    if(head.st.count) {
        temp_st = file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, file_st++) {
            for(j=0; j<(u32)file_st->count; j++) {
                data_elem = (HsfVector2f *)(((u32)data)+((u32)file_st->data)+(j*sizeof(HsfVector2f)));
            }
        }
        new_st = temp_st;
        Model.st = new_st;
        Model.stCnt = head.st.count;
        file_st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
        data = (void *)&file_st[head.st.count];
        for(i=0; i<head.st.count; i++, new_st++, file_st++) {
            temp_data = file_st->data;
            new_st->count = file_st->count;
            new_st->name = SetName((u32 *)&file_st->name);
            new_st->data = (void *)((u32)data+(u32)temp_data);
            for(j=0; j<new_st->count; j++) {
                data_elem = (HsfVector2f *)(((u32)data)+((u32)temp_data)+(j*sizeof(HsfVector2f)));
                ((HsfVector2f *)new_st->data)[j].x = data_elem->x;
                ((HsfVector2f *)new_st->data)[j].y = data_elem->y;
            }
        }
    }
}

static void FaceLoad(void)
{
    HsfBuffer *file_face;
    HsfBuffer *new_face;
    HsfBuffer *temp_face;
    HsfFace *temp_data;
    HsfFace *data;
    HsfFace *file_face_strip;
    HsfFace *new_face_strip;
    HsfTristrip *strip;
    s32 i;
    s32 j;
    
    if(head.face.count) {
        temp_face = file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
        new_face = temp_face;
        Model.face = new_face;
        Model.faceCnt = head.face.count;
        file_face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
        data = (HsfFace *)&file_face[head.face.count];
        for(i=0; i<head.face.count; i++, new_face++, file_face++) {
            temp_data = file_face->data;
            new_face->name = SetName((u32 *)&file_face->name);
            new_face->count = file_face->count;
            new_face->data = (void *)((u32)data+(u32)temp_data);
            strip = (HsfTristrip *)(&((HsfFace *)new_face->data)[new_face->count]);
        }
        new_face = temp_face;
        for(i=0; i<head.face.count; i++, new_face++) {
            file_face_strip = new_face_strip = new_face->data;
            for(j=0; j<new_face->count; j++, new_face_strip++, file_face_strip++) {
                if(file_face_strip->type == 4) {
                    new_face_strip->strip.data = &strip[(u32)file_face_strip->strip.data];
                }
            }
        }
    }
}

static void DispObject(HsfObject *parent, HsfObject *object)
{
    u32 i;
    HsfObject *child_obj;
    HsfObject *temp_object;
    struct {
        HsfObject *parent;
        HsfBuffer *shape;
        HsfCluster *cluster;
    } temp;
    
    temp.parent = parent;
    object->type = object->type;
    switch(object->type) {
        case 2:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            new_object->data.parent = parent;
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->type = 2;
            new_object->data.vertex = SearchVertexPtr((s32)data->vertex);
            new_object->data.normal = SearchNormalPtr((s32)data->normal);
            new_object->data.st = SearchStPtr((s32)data->st);
            new_object->data.color = SearchColorPtr((s32)data->color);
            new_object->data.face = SearchFacePtr((s32)data->face);
            new_object->data.vertexShape = (HsfBuffer **)&NSymIndex[(u32)data->vertexShape];
            for(i=0; i<new_object->data.vertexShapeCnt; i++) {
                temp.shape = &vtxtop[(u32)new_object->data.vertexShape[i]];
                new_object->data.vertexShape[i] = temp.shape;
            }
            new_object->data.cluster = (HsfCluster **)&NSymIndex[(u32)data->cluster];
            for(i=0; i<new_object->data.clusterCnt; i++) {
                temp.cluster = &ClusterTop[(u32)new_object->data.cluster[i]];
                new_object->data.cluster[i] = temp.cluster;
            }
            new_object->data.cenv = SearchCenvPtr((s32)data->cenv);
            new_object->data.material = Model.material;
            if((s32)data->attribute >= 0) {
                new_object->data.attribute = Model.attribute;
            } else {
                new_object->data.attribute = NULL;
            }
            new_object->data.file[0] = (void *)((u32)fileptr+(u32)data->file[0]);
            new_object->data.file[1] = (void *)((u32)fileptr+(u32)data->file[1]);
            new_object->data.base.pos.x = data->base.pos.x;
            new_object->data.base.pos.y = data->base.pos.y;
            new_object->data.base.pos.z = data->base.pos.z;
            new_object->data.base.rot.x = data->base.rot.x;
            new_object->data.base.rot.y = data->base.rot.y;
            new_object->data.base.rot.z = data->base.rot.z;
            new_object->data.base.scale.x = data->base.scale.x;
            new_object->data.base.scale.y = data->base.scale.y;
            new_object->data.base.scale.z = data->base.scale.z;
            new_object->data.mesh.min.x = data->mesh.min.x;
            new_object->data.mesh.min.y = data->mesh.min.y;
            new_object->data.mesh.min.z = data->mesh.min.z;
            new_object->data.mesh.max.x = data->mesh.max.x;
            new_object->data.mesh.max.y = data->mesh.max.y;
            new_object->data.mesh.max.z = data->mesh.max.z;
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
            
        case 0:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case 1:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            new_object->data.unk64 = &objtop[(u32)new_object->data.unk64];
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;

        case 3:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case 4:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case 5:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        case 9:
        {
            HsfObjectData *data;
            HsfObject *new_object;
            data = &object->data;
            new_object = temp_object = object;
            new_object->data.parent = parent;
            new_object->data.childrenCount = data->childrenCount;
            new_object->data.children = (HsfObject **)&NSymIndex[(u32)data->children];
            for(i=0; i<new_object->data.childrenCount; i++) {
                child_obj = &objtop[(u32)new_object->data.children[i]];
                new_object->data.children[i] = child_obj;
            }
            if(Model.root == NULL) {
                Model.root = temp_object;
            }
            for(i=0; i<data->childrenCount; i++) {
                DispObject(new_object, new_object->data.children[i]);
            }
        }
        break;
        
        default:
            break;
    }
}

static inline void FixupObject(HsfObject *object)
{
    HsfObjectData *objdata_8;
    HsfObjectData *objdata_7;
    
    s32 obj_type = object->type;
    switch(obj_type) {
        case 8:
        {
            objdata_8 = &object->data;
            object->type = 8;
        }
        break;
        
        case 7:
        {
            objdata_7 = &object->data;
            object->type = 7;
        }
        break;
        
        default:
            break;
            
    }
}

static void ObjectLoad(void)
{
    s32 i;
    HsfObject *object;
    HsfObject *new_object;
    
    
    s32 obj_type;
    
    
    
    if(head.object.count) {
        objtop = object = (HsfObject *)((u32)fileptr+head.object.ofs);
        for(i=0; i<head.object.count; i++, object++) {
            new_object = object;
            new_object->name = SetName((u32 *)&object->name);
        }
        object = objtop;
        for(i=0; i<head.object.count; i++, object++) {
            if((s32)object->data.parent == -1) {
                break;
            }
        }
        DispObject(NULL, object);
        Model.objectCnt = head.object.count;
        object = objtop;
        for(i=0; i<head.object.count; i++, object++) {
            FixupObject(object);
        }
    }
}

static s32 SearchObjectSetName(HsfData *data, char *name)
{
    HsfObject *object = data->object;
    s32 i;
    for(i=0; i<data->objectCnt; i++, object++) {
        char *other_name = object->name;
        int unk8 = 0;
        if(!strcmp(other_name, name)) {
            return i;
        }
    }
    OSReport("Search Object Error %s\n", name);
    return -1;
}

static HsfBuffer *SearchVertexPtr(s32 id)
{
    HsfBuffer *vertex; 
    if(id == -1) {
        return NULL;
    }
    vertex = (HsfBuffer *)((u32)fileptr+head.vertex.ofs);
    vertex += id;
    return vertex;
}

static HsfBuffer *SearchNormalPtr(s32 id)
{
    HsfBuffer *normal; 
    if(id == -1) {
        return NULL;
    }
    normal = (HsfBuffer *)((u32)fileptr+head.normal.ofs);
    normal += id;
    return normal;
}

static HsfBuffer *SearchStPtr(s32 id)
{
    HsfBuffer *st; 
    if(id == -1) {
        return NULL;
    }
    st = (HsfBuffer *)((u32)fileptr+head.st.ofs);
    st += id;
    return st;
}

static HsfBuffer *SearchColorPtr(s32 id)
{
    HsfBuffer *color; 
    if(id == -1) {
        return NULL;
    }
    color = (HsfBuffer *)((u32)fileptr+head.color.ofs);
    color += id;
    return color;
}

static HsfBuffer *SearchFacePtr(s32 id)
{
    HsfBuffer *face; 
    if(id == -1) {
        return NULL;
    }
    face = (HsfBuffer *)((u32)fileptr+head.face.ofs);
    face += id;
    return face;
}

static HsfCenv *SearchCenvPtr(s32 id)
{
    HsfCenv *cenv; 
    if(id == -1) {
        return NULL;
    }
    cenv = (HsfCenv *)((u32)fileptr+head.cenv.ofs);
    cenv += id;
    return cenv;
}

static HsfPart *SearchPartPtr(s32 id)
{
    HsfPart *part; 
    if(id == -1) {
        return NULL;
    }
    part = (HsfPart *)((u32)fileptr+head.part.ofs);
    part += id;
    return part;
}

static HsfPalette *SearchPalettePtr(s32 id)
{
    HsfPalette *palette; 
    if(id == -1) {
        return NULL;
    }
    palette = Model.palette;
    palette += id;
    return palette;
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