#include "common.h"
#include "dolphin/gx.h"

struct strline_data {
    u16 type;
    u16 last_idx;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 empty_line;
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

void pfClsScr(void);

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
        strline[i].empty_line = i+1;
        strline[i].type = 0;
        if (strline[i].str[0] != 0) {
            strline[i].str[0] = 0;
        }
    }
}