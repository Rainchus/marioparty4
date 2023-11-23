#include "common.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "stdio.h"
#include "stdarg.h"

extern u8 ank8x8_4b[];

struct strline_data {
    u16 type;
    u16 color_idx;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 empstrline_next;
    float scale;
    char str[80];
    GXColor color;
};

static struct strline_data strline[256];
static char pfStrBuf[256];

BOOL saftyFrameF;
u16 strlinecnt;
u16 empstrline;
int fontcolor;

static void WireDraw(void);

static GXColor ATTRIBUTE_ALIGN(32) fcoltbl[16] = {
    { 0, 0, 0, 255 },
    { 0, 0, 128, 255 },
    { 128, 0, 0, 255 },
    { 128, 0, 128, 255 },
    { 0, 128, 0, 255 },
    { 0, 128, 128, 255 },
    { 128, 128, 0, 255 }, 
    { 128, 128, 128, 255 },
    { 128, 128, 128, 128 },
    { 0, 0, 255, 255 },
    { 255, 0, 0, 255 },
    { 255, 0, 255, 255 },
    { 0, 255, 0, 255 },
    { 0, 255, 255, 255 },
    { 255, 255, 0, 255 }, 
    { 255, 255, 255, 255 }
};

void pfInit(void)
{
    int i;
    fontcolor = 15;
    empstrline = 0;
    
    for (i = 0; i < 256; i++) {
        strline[i].str[0] = 0;
    }
    pfClsScr();
}

void pfClsScr(void)
{
    int i;
    empstrline = 0;
    strlinecnt = 0;
    for (i = 0; i < 256; i++) {
        strline[i].empstrline_next = i+1;
        strline[i].type = 0;
        if (strline[i].str[0] != 0) {
            strline[i].str[0] = 0;
        }
    }
}

s16 print8(s16 x, s16 y, float scale, char *str, ...)
{
    struct strline_data *strline_curr;
    char *src = pfStrBuf;
    char *dst;
    s16 ret;
    va_list list;
    strline_curr = &strline[empstrline];
    if(strlinecnt >= 256) {
        return -1;
    }
    va_start(list, str);
    vsprintf(pfStrBuf, str, list);
    strlinecnt++;
    ret = empstrline;
    empstrline = strline_curr->empstrline_next;
    strline_curr->type = 0;
    strline_curr->color_idx = fontcolor;
    strline_curr->x = x;
    strline_curr->y = y;
    strline_curr->scale = scale;
    dst = strline_curr->str;
    while(*src) {
        *dst++ = *src++;
    }
    *dst = 0;
    va_end(list);
    return ret;
}

s16 printWin(s16 x, s16 y, s16 w, s16 h, GXColor *color)
{
    struct strline_data *strline_curr;
    s16 ret;
    char *src = pfStrBuf;
    strline_curr = &strline[empstrline];
    if(strlinecnt >= 256) {
        return -1;
    }
    strlinecnt++;
    ret = empstrline;
    empstrline = strline_curr->empstrline_next;
    strline_curr->type = 1;
    strline_curr->color.r = color->r;
    strline_curr->color.g = color->g;
    strline_curr->color.b = color->b;
    strline_curr->color.a = color->a;
    strline_curr->x = x;
    strline_curr->y = y;
    strline_curr->w = w;
    strline_curr->h = h;
    return ret;
}

void pfDrawFonts(void)
{
    GXTexObj font_tex;
    Mtx modelview;
    Mtx44 proj;
    u16 strline_count = strlinecnt;
    if(saftyFrameF) {
        WireDraw();
    }
    MTXOrtho(proj, 0, 480, 0, 640, 0, 10);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(modelview);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    GXSetCurrentMatrix(GX_PNMTX0);
    GXSetViewport(0, 0, RenderMode->fbWidth, RenderMode->efbHeight, 0, 1);
    GXSetScissor(0, 0, RenderMode->fbWidth, RenderMode->efbHeight);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_CLR0, fcoltbl, sizeof(GXColor));
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXInitTexObj(&font_tex, ank8x8_4b, 128, 128, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&font_tex, GX_NEAR, GX_NEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&font_tex, GX_TEXMAP0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}