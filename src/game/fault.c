#include "game/gamework_data.h"
#include "stdarg.h"
#include "stdio.h"

typedef struct rgb_color {
    u8 r;
    u8 g;
    u8 b;
} RGBColor;

typedef struct xfb_geometry {
    void* unk0[4];
    u16 unk4;
    u16 unk5;
    u16 unk6;
    u16 unk7;
} XFBGeometry;

static RGBColor XFB_Colors[5] = {
    { 0x00, 0x80, 0x80 },
    { 0xFF, 0x80, 0x80 },
    { 0xC0, 0x80, 0x80 },
    { 0x80, 0x80, 0x80 },
    { 0x40, 0x80, 0x80 }
};

#include "Ascii8x8_1bpp.inc"

XFBGeometry XFB_Geometry;

static s32 (*XFB_putc)(u8 arg0, s32 arg1, s32 arg2);

static RGBColor Draw_Color;

static s32 x_start;
static s32 y_start;

const char* lbl_801D34A0 = "OSPanic encounterd:";

s32 XFB_putcProgressive(u8 arg0, s32 arg1, s32 arg2);
s32 XFB_putcInterlace(u8 arg0, s32 arg1, s32 arg2);
s32 XFB_puts(s8* arg0, s32 arg1, s32 arg2);
s32 XFB_putcS(u8 arg0, s32 arg1, s32 arg2);
void XFB_WriteBackCache(void);
void XFB_CR(s32 arg0, s32* arg1, s32* arg2);

void OSPanic(const char* file, int line, const char* msg, ...) {
    va_list sp78;
    s32 sp74;
    s32 sp70;
    char sp84[1024];
    s32 puts;

    sp74 = x_start = 0x10;
    sp70 = y_start = 0x20;
    puts = XFB_puts((s8*)lbl_801D34A0, sp74, sp70);
    XFB_CR(puts + 1, &sp74, &sp70);
    sprintf(sp84, "%s:%d", file, line);
    puts = XFB_puts((s8*)sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    va_start(sp78, msg);
    vsnprintf(sp84, 0x400U, msg, &sp78[0]);
    puts = XFB_puts((s8*)sp84, sp74, sp70);
    XFB_CR(puts, &sp74, &sp70);
    XFB_WriteBackCache();
    PPCHalt();
    va_end(sp78);
}

void HuFaultInitXfbDirectDraw(GXRenderModeObj *mode) {
    s32 i;
    
    for (i = 0; i < 4; i++) {
        XFB_Geometry.unk0[i] = 0;
    }
    
    XFB_Geometry.unk4 = 0;
    XFB_Geometry.unk5 = 0;
    XFB_Geometry.unk6 = 0;
    
    XFB_putc = XFB_putcProgressive;
    Draw_Color = XFB_Colors[1];
    
    if (mode) {
        XFB_Geometry.unk4 = ((u16)mode->fbWidth + 0xF) & 0xFFFFFFF0;
        XFB_Geometry.unk5 = mode->xfbHeight;
        XFB_Geometry.unk6 = mode->xFBmode;
        
        if (XFB_Geometry.unk6 == 0) {
            XFB_putc = XFB_putcInterlace;
            return;
        }
        XFB_putc = XFB_putcProgressive;
    }
}

void HuFaultSetXfbAddress(s16 index, void* value) {
    if (index >= 0 && index < 4) {
        XFB_Geometry.unk0[index] = value;
    }
}

void XFB_WriteBackCache(void) {
    s32 var_r31;
    void* temp_r30;
    u32 temp_r29;

    temp_r29 = XFB_Geometry.unk4 * 2 * XFB_Geometry.unk5;
    
    if (temp_r29 != 0) {
        var_r31 = 0;
        
        while (var_r31 < 4) {
            temp_r30 = XFB_Geometry.unk0[var_r31];
            if (temp_r30) {
                DCStoreRange(temp_r30, temp_r29);
            }
            var_r31 += 1;
        }
    }
}


void XFB_CR(s32 arg0, s32* arg1, s32* arg2) {
    s32 temp_r30;
    s32 var_r31;
    s32 var_r29;

    var_r29 = *arg1;
    var_r31 = *arg2;
    
    var_r29 = x_start;
    var_r31 += 0x12;
    
    temp_r30 = arg0 & 7;
    if (temp_r30 != 0) {
        var_r31 += temp_r30 * 0x12;
    }

    *arg1 = var_r29;
    *arg2 = var_r31;
}

s32 XFB_puts(s8* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 temp_r31;
    s8 current_char;
    
    i = 0;
    
    do {
        current_char = *arg0++;
        
        if (current_char == '\n') {
            XFB_CR(0, &arg1, &arg2);
            
            i += 1;
        } else {
            temp_r31 = XFB_putcS(current_char, arg1, arg2);
            
            if (temp_r31 >= 0) {
                if (temp_r31 != 0) {
                    temp_r31 -= 1;

                    XFB_CR(temp_r31, &arg1, &arg2);
                    
                    i += temp_r31 + 1;
                }
                arg1 += 0x10;
            } else {
                break;
            }
        }
    } while(current_char != 0);
    
    return i;
}

s32 XFB_putcS(u8 arg0, s32 arg1, s32 arg2) {
    RGBColor sp8;
    s32 var_r26;
    s32 var_r25;
    s32 var_r27;
    s32 var_r29;
    RGBColor* temp_r3;
    
    var_r27 = 0;
    sp8 = Draw_Color;
    
    if (arg1 + 0x11 >= XFB_Geometry.unk4) {
        var_r26 = arg1;
        var_r29 = arg2;
        if (0 != 0) {
            var_r29 += 0 * 0x12;
        }
        var_r26 = x_start;
        var_r29 += 0x12;
        var_r25 = 0;

        if (var_r25 != 0) {
            var_r29 += var_r25 * 0x12;
        }

        arg1 = var_r26;
        arg2 = var_r29;
        var_r27++;
    }
    
    Draw_Color = *XFB_Colors;
    XFB_putc(arg0, arg1, arg2 - 2);
    XFB_putc(arg0, arg1, arg2 + 2);
    XFB_putc(arg0, arg1 - 1, arg2);
    XFB_putc(arg0, arg1 + 1, arg2);
    
    Draw_Color = sp8;
    XFB_putc(arg0, arg1, arg2);
    
    return var_r27;
}

s32 XFB_putcProgressive(u8 arg0, s32 arg1, s32 arg2) {
    s32 var_r21;
    s32 temp_r20;
    u8 spA;
    u8 sp9;
    u8 sp8;
    s32 var_r25;
    s32 var_r24;
    s32 var_r23;
    u8* var_r29;
    s32 var_r28;
    s32 var_r27;
    s32 var_r26;
    u32 temp_r31;
    u32 var_r30;
    u32 var_r22;
    u8* var_r31;
    
    var_r21 = 0;
    
    if (arg0 == 0) {
        return -1;
    }
    
    if (arg1 + 0x10 >= XFB_Geometry.unk4) {
        arg2 += 0x12;
        arg1 = x_start;
        var_r21 = 1;
    }
    
    if (arg2 + 0x10 >= XFB_Geometry.unk5) {
        return -1;
    }
    
    spA = Draw_Color.r;
    sp8 = Draw_Color.g;
    sp9 = Draw_Color.b;
    
    temp_r20 = XFB_Geometry.unk4 * 2;
    var_r23 = (arg1 & 0xFFFE) * 2 + arg2 * temp_r20;
    var_r29 = Ascii8x8_1bpp + (arg0 * 8);
    var_r25 = 8;
    
    while (var_r25 != 0) {
        var_r24 = 2;
        
        while (var_r24 != 0) {
            var_r28 = 0;
            
            while (var_r28 < 4) {
                var_r31 = XFB_Geometry.unk0[var_r28];
                
                if (var_r31 != 0) {
                    var_r31 += var_r23;
                    
                    var_r22 = *var_r29;
                    var_r30 = 0;
                    var_r26 = 0;
                    while (var_r26 < 0x10) {
                        if (var_r22 & 0xF != 0) {
                            var_r30 |= 3 << var_r26;
                        }
                        var_r26 += 2;
                        var_r22 >>= 1;
                    }
                    var_r27 = 8;
                    if ((s32) (arg1 & 1) != 0) {
                        var_r30 *= 2;
                        var_r27 = 0xA;
                    }
                    
                    while (var_r27 != 0) {
                        if ((u32) (var_r30 & 3) != 0) {
                            var_r31[1] = sp9;
                            var_r31[3] = sp8;
                            
                            if ((u32) (var_r30 & 1) != 0) {
                                var_r31[0] = spA;
                            }
                            if ((u32) (var_r30 & 2) != 0) {
                                var_r31[2] = spA;
                            }
                        }
                        var_r27 -= 1;
                        var_r31 += 4;
                        var_r30 = var_r30 >> 2;
                    }
                }
                var_r28 += 1;
            }
            var_r24 -= 1;
            var_r23 += temp_r20;
        }
        var_r25 -= 1;
        var_r29 += 1;
    }
    return var_r21;
}

s32 XFB_putcInterlace(u8 arg0, s32 arg1, s32 arg2) {
    u8 var_r24;
    u8 var_r22;
    u8 var_r21;
    s32 temp_r23;
    s32 var_r26;
    s32 var_r25;
    u8* var_r28;
    s32 var_r27;
    s16 var_r29;
    s32 var_r30;
    u8* var_r31;
    
    if (arg0 == 0) {
        return -1;
    }
    
    if (arg1 + 8 >= XFB_Geometry.unk4 || arg2 + 8 >= XFB_Geometry.unk5) {
        return -1;
    }

    var_r24 = Draw_Color.r;
    var_r21 = Draw_Color.g;
    var_r22 = Draw_Color.b;
    
    temp_r23 = XFB_Geometry.unk4 * 2;
    var_r25 = ((arg1 & 0xFFFE) * 2) + ((arg2 >> 1) * temp_r23);
    var_r28 = Ascii8x8_1bpp + arg0 * 8;
    var_r26 = 8;
    
    while (var_r26) {
        for (var_r27 = 0; var_r27 < 4; var_r27 += 2) {
            var_r30 = var_r27;
            
            if ((s32) (arg2 & 1) != 0) {
                var_r30 += 1;
            }
            
            var_r31 = XFB_Geometry.unk0[var_r30];
            
            if (var_r31) {
                var_r31 = var_r31 + var_r25;
                var_r29 = *var_r28;
                var_r30 = 4;
                
                if (arg1 & 1) {
                    var_r29 = (s16)var_r29 * 2;
                    var_r30 = 5;
                }

                while (var_r30) {
                    if (var_r29 & 3) {
                        var_r31[1] = var_r22;
                        var_r31[3] = var_r21;
                        
                        if (var_r29 & 1) {
                            var_r31[0] = var_r24;
                        }
                        if (var_r29 & 2) {
                            var_r31[2] = var_r24;
                        }
                    }
                    
                    var_r30 -= 1;
                    var_r31 += 4;
                    var_r29 >>= 2;
                }
            }
        }
        
        var_r26 -= 1;
        arg2 += 1;
        var_r28 += 1;
        var_r25 += temp_r23;
    }
    
    return 0;
}
