#include "common.h"
#include "stdarg.h"
#include "stdio.h"

typedef struct rgb_color {
    s8 r;
    s8 g;
    s8 b;
} RGBColor;

static RGBColor XFB_Colors[5] = {
    { 0x00, 0x80, 0x80 },
    { 0xFF, 0x80, 0x80 },
    { 0xC0, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0x40, 0x80, 0x80 }
};

s16 XFB_Geometry[6][2];

static RGBColor Draw_Color;
static s32 y_start;
static s32 x_start;

const char* lbl_801D34A0 = "OSPanic encounterd:";

void OSPanic(const char* file, int line, const char* msg, ...) {
    va_list sp78;
    s32 sp74;
    s32 sp70;
    char sp84[1024];
    s32 puts;

    sp74 = x_start = 0x10;
    sp70 = y_start = 0x20;
    puts = XFB_puts(lbl_801D34A0, sp74, sp70);
    XFB_CR(puts + 1, &sp74, &sp70);
    sprintf(sp84, "%s:%d", file, line);
    puts = XFB_puts(sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    va_start(sp78, msg);
    vsnprintf(sp84, 0x400U, msg, &sp78[0]);
    puts = XFB_puts(sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    XFB_WriteBackCache();
    PPCHalt();
    va_end();
}