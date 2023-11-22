#define _FUNCTIONS_H_ 
#define _COMMON_H_ 
#define REL_EXECUTOR_H 
#define _TYPES_H_ 
#define F3DEX_GBI_2 1
#define M2CTX 1
#define _COMMON_STRUCTS_H 
#define _LANGUAGE_C 1
#define _MIPS_SZLONG 32
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef long long s64;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile unsigned long long vu64;
typedef volatile signed char vs8;
typedef volatile short vs16;
typedef volatile long vs32;
typedef volatile long long vs64;
typedef float f32;
typedef double f64;
typedef struct UnkOvl {
    s32 unk0;
    char unk4[4];
    s32 unk8;
} UnkOvl;
typedef struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
} Vec3f;
void OSReport(const char * format, ...);
void* HuPrcCreate(void (*), s32, s32, s32);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DCameraCreate(s16);
void Hu3DCameraPerspectiveSet(s16, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s16, f32, f32, f32, f32, f32, f32);
void omOvlHisChg(s32, s32, s32, s32);
UnkOvl* omOvlHisGet(s32);
void* omInitObjMan(s32, s32);
void fn_80044920(s16);
void fn_80045F74(s16, s32);
s32 fn_800578E4(void);
void fn_1_26C(void);
extern int _prolog();
extern void _epilog();
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];
extern void ModuleProlog(void);
extern void ModuleEpilog(void);
