#include "game/ShapeExec.h"
#include "game/EnvelopeExec.h"

static void SetShapeMain(HsfObject *arg0) {
    HsfBuffer *temp_r28;
    HsfBuffer *temp_r30;
    float var_f30;
    float var_f31;
    s32 temp_r27;
    s32 var_r29;
    s32 var_r26;
    s32 i;

    if (arg0->data.shapeType == 2) {
        var_f30 = 0.0f;
        for (i = 0; i < arg0->data.vertexShapeCnt; i++) {
            var_f30 += arg0->data.mesh.morphWeight[i];
        }
        temp_r30 = *arg0->data.vertexShape;
        for (i = 0; i < temp_r30->count; i++) {
            Vertextop[i].x = ((Vec*) temp_r30->data)[i].x;
            Vertextop[i].y = ((Vec*) temp_r30->data)[i].y;
            Vertextop[i].z = ((Vec*) temp_r30->data)[i].z;
        }
        for (i = 0; i < arg0->data.vertexShapeCnt; i++) {
            temp_r30 = arg0->data.vertexShape[i];
            var_f31 = arg0->data.mesh.morphWeight[i];
            if (var_f31 < 0.0f) {
                var_f31 = 0.0f;
            } else if (var_f30 > 1.0f) {
                var_f31 /= var_f30;
            }
            for (var_r29 = 0; var_r29 < temp_r30->count; var_r29++) {
                Vertextop[var_r29].x += var_f31 * (((Vec*) temp_r30->data)[var_r29].x - Vertextop[var_r29].x);
                Vertextop[var_r29].y += var_f31 * (((Vec*) temp_r30->data)[var_r29].y - Vertextop[var_r29].y);
                Vertextop[var_r29].z += var_f31 * (((Vec*) temp_r30->data)[var_r29].z - Vertextop[var_r29].z);
            }
        }
    } else {
        temp_r27 = arg0->data.mesh.baseMorph;
        var_r26 = temp_r27 + 1;
        if (var_r26 >= arg0->data.vertexShapeCnt) {
            var_r26 = temp_r27;
        }
        var_f31 = arg0->data.mesh.baseMorph - temp_r27;
        temp_r30 = arg0->data.vertexShape[temp_r27];
        temp_r28 = arg0->data.vertexShape[var_r26];
        for (i = 0; i < temp_r30->count; i++) {
            Vertextop[i].x = ((Vec*) temp_r30->data)[i].x + var_f31 * (((Vec*) temp_r28->data)[i].x - ((Vec*) temp_r30->data)[i].x);
            Vertextop[i].y = ((Vec*) temp_r30->data)[i].y + var_f31 * (((Vec*) temp_r28->data)[i].y - ((Vec*) temp_r30->data)[i].y);
            Vertextop[i].z = ((Vec*) temp_r30->data)[i].z + var_f31 * (((Vec*) temp_r28->data)[i].z - ((Vec*) temp_r30->data)[i].z);
        }
    }
}

void ShapeProc(HsfData *arg0) {
    HsfObject *var_r31;
    s32 i;

    var_r31 = arg0->object;
    for (i = 0; i < arg0->objectCnt; i++, var_r31++) {
        if (var_r31->type == 2 && var_r31->data.vertexShapeCnt != 0) {
            Vertextop = var_r31->data.vertex->data;
            SetShapeMain(var_r31);
            DCStoreRange(Vertextop, var_r31->data.vertex->count * sizeof(Vec));
            var_r31->data.unk120[0]++;
        }
    }
}
