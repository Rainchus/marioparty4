typedef signed char s8;
typedef signed short int s16;
typedef signed long s32;
typedef signed long long int s64;
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long u32;
typedef unsigned long long int u64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;
typedef double f64;

typedef volatile f32 vf32;
typedef volatile f64 vf64;
typedef int BOOL;
#define FALSE 0
#define TRUE 1

#define NULL ((void *)0)
#define nullptr NULL

typedef enum _GXCITexFmt {
  GX_TF_C4 = 0x8,
  GX_TF_C8 = 0x9,
  GX_TF_C14X2 = 0xa,
} GXCITexFmt;

typedef enum _GXTexWrapMode {
  GX_CLAMP,
  GX_REPEAT,
  GX_MIRROR,
  GX_MAX_TEXWRAPMODE,
} GXTexWrapMode;

typedef enum _GXTexFilter {
  GX_NEAR,
  GX_LINEAR,
  GX_NEAR_MIP_NEAR,
  GX_LIN_MIP_NEAR,
  GX_NEAR_MIP_LIN,
  GX_LIN_MIP_LIN,
} GXTexFilter;

typedef enum _GXAnisotropy {
  GX_ANISO_1,
  GX_ANISO_2,
  GX_ANISO_4,
  GX_MAX_ANISOTROPY,
} GXAnisotropy;

typedef enum _GXTexMapID {
  GX_TEXMAP0,
  GX_TEXMAP1,
  GX_TEXMAP2,
  GX_TEXMAP3,
  GX_TEXMAP4,
  GX_TEXMAP5,
  GX_TEXMAP6,
  GX_TEXMAP7,
  GX_MAX_TEXMAP,
  GX_TEXMAP_NULL = 0xFF,
  GX_TEX_DISABLE = 0x100,
} GXTexMapID;

typedef enum _GXTexCoordID {
  GX_TEXCOORD0,
  GX_TEXCOORD1,
  GX_TEXCOORD2,
  GX_TEXCOORD3,
  GX_TEXCOORD4,
  GX_TEXCOORD5,
  GX_TEXCOORD6,
  GX_TEXCOORD7,
  GX_MAX_TEXCOORD,
  GX_TEXCOORD_NULL = 0xFF,
} GXTexCoordID;

typedef enum _GXTevStageID {
  GX_TEVSTAGE0,
  GX_TEVSTAGE1,
  GX_TEVSTAGE2,
  GX_TEVSTAGE3,
  GX_TEVSTAGE4,
  GX_TEVSTAGE5,
  GX_TEVSTAGE6,
  GX_TEVSTAGE7,
  GX_TEVSTAGE8,
  GX_TEVSTAGE9,
  GX_TEVSTAGE10,
  GX_TEVSTAGE11,
  GX_TEVSTAGE12,
  GX_TEVSTAGE13,
  GX_TEVSTAGE14,
  GX_TEVSTAGE15,
  GX_MAX_TEVSTAGE,
} GXTevStageID;

typedef enum _GXTevMode {
  GX_MODULATE,
  GX_DECAL,
  GX_BLEND,
  GX_REPLACE,
  GX_PASSCLR,
} GXTevMode;

typedef enum _GXTexMtxType {
  GX_MTX3x4,
  GX_MTX2x4,
} GXTexMtxType;

typedef enum _GXTexGenType {
  GX_TG_MTX3x4,
  GX_TG_MTX2x4,
  GX_TG_BUMP0,
  GX_TG_BUMP1,
  GX_TG_BUMP2,
  GX_TG_BUMP3,
  GX_TG_BUMP4,
  GX_TG_BUMP5,
  GX_TG_BUMP6,
  GX_TG_BUMP7,
  GX_TG_SRTG,
} GXTexGenType;

typedef enum _GXPosNrmMtx {
  GX_PNMTX0 = 0,
  GX_PNMTX1 = 3,
  GX_PNMTX2 = 6,
  GX_PNMTX3 = 9,
  GX_PNMTX4 = 12,
  GX_PNMTX5 = 15,
  GX_PNMTX6 = 18,
  GX_PNMTX7 = 21,
  GX_PNMTX8 = 24,
  GX_PNMTX9 = 27,
} GXPosNrmMtx;

typedef enum _GXTexMtx {
  GX_TEXMTX0 = 30,
  GX_TEXMTX1 = 33,
  GX_TEXMTX2 = 36,
  GX_TEXMTX3 = 39,
  GX_TEXMTX4 = 42,
  GX_TEXMTX5 = 45,
  GX_TEXMTX6 = 48,
  GX_TEXMTX7 = 51,
  GX_TEXMTX8 = 54,
  GX_TEXMTX9 = 57,
  GX_IDENTITY = 60,
} GXTexMtx;

typedef enum _GXChannelID {
  GX_COLOR0,
  GX_COLOR1,
  GX_ALPHA0,
  GX_ALPHA1,
  GX_COLOR0A0,
  GX_COLOR1A1,
  GX_COLOR_ZERO,
  GX_ALPHA_BUMP,
  GX_ALPHA_BUMPN,
  GX_COLOR_NULL = 0xFF,
} GXChannelID;

typedef enum _GXTexGenSrc {
  GX_TG_POS,
  GX_TG_NRM,
  GX_TG_BINRM,
  GX_TG_TANGENT,
  GX_TG_TEX0,
  GX_TG_TEX1,
  GX_TG_TEX2,
  GX_TG_TEX3,
  GX_TG_TEX4,
  GX_TG_TEX5,
  GX_TG_TEX6,
  GX_TG_TEX7,
  GX_TG_TEXCOORD0,
  GX_TG_TEXCOORD1,
  GX_TG_TEXCOORD2,
  GX_TG_TEXCOORD3,
  GX_TG_TEXCOORD4,
  GX_TG_TEXCOORD5,
  GX_TG_TEXCOORD6,
  GX_TG_COLOR0,
  GX_TG_COLOR1,
  GX_MAX_TEXGENSRC,
} GXTexGenSrc;

typedef enum _GXBlendMode {
  GX_BM_NONE,
  GX_BM_BLEND,
  GX_BM_LOGIC,
  GX_BM_SUBTRACT,
  GX_MAX_BLENDMODE,
} GXBlendMode;

typedef enum _GXBlendFactor {
  GX_BL_ZERO,
  GX_BL_ONE,
  GX_BL_SRCCLR,
  GX_BL_INVSRCCLR,
  GX_BL_SRCALPHA,
  GX_BL_INVSRCALPHA,
  GX_BL_DSTALPHA,
  GX_BL_INVDSTALPHA,
  GX_BL_DSTCLR = GX_BL_SRCCLR,
  GX_BL_INVDSTCLR = GX_BL_INVSRCCLR,
} GXBlendFactor;

#define GX_FALSE ((GXBool)0)
#define GX_TRUE ((GXBool)1)

#define GX_ENABLE ((GXBool)1)
#define GX_DISABLE ((GXBool)0)

typedef enum _GXProjectionType {
  GX_PERSPECTIVE,
  GX_ORTHOGRAPHIC,
} GXProjectionType;

typedef enum _GXCompare {
  GX_NEVER,
  GX_LESS,
  GX_EQUAL,
  GX_LEQUAL,
  GX_GREATER,
  GX_NEQUAL,
  GX_GEQUAL,
  GX_ALWAYS,
} GXCompare;

typedef enum _GXAlphaOp {
  GX_AOP_AND,
  GX_AOP_OR,
  GX_AOP_XOR,
  GX_AOP_XNOR,
  GX_MAX_ALPHAOP,
} GXAlphaOp;

typedef enum _GXZFmt16 {
  GX_ZC_LINEAR,
  GX_ZC_NEAR,
  GX_ZC_MID,
  GX_ZC_FAR,
} GXZFmt16;

typedef enum _GXGamma {
  GX_GM_1_0,
  GX_GM_1_7,
  GX_GM_2_2,
} GXGamma;

typedef enum _GXPixelFmt {
  GX_PF_RGB8_Z24,
  GX_PF_RGBA6_Z24,
  GX_PF_RGB565_Z16,
  GX_PF_Z24,
  GX_PF_Y8,
  GX_PF_U8,
  GX_PF_V8,
  GX_PF_YUV420,
} GXPixelFmt;

typedef enum _GXPrimitive {
  GX_QUADS = 0x80,
  GX_TRIANGLES = 0x90,
  GX_TRIANGLESTRIP = 0x98,
  GX_TRIANGLEFAN = 0xA0,
  GX_LINES = 0xA8,
  GX_LINESTRIP = 0xB0,
  GX_POINTS = 0xB8,
} GXPrimitive;

typedef enum _GXVtxFmt {
  GX_VTXFMT0,
  GX_VTXFMT1,
  GX_VTXFMT2,
  GX_VTXFMT3,
  GX_VTXFMT4,
  GX_VTXFMT5,
  GX_VTXFMT6,
  GX_VTXFMT7,
  GX_MAX_VTXFMT,
} GXVtxFmt;

typedef enum _GXAttr {
  GX_VA_PNMTXIDX,
  GX_VA_TEX0MTXIDX,
  GX_VA_TEX1MTXIDX,
  GX_VA_TEX2MTXIDX,
  GX_VA_TEX3MTXIDX,
  GX_VA_TEX4MTXIDX,
  GX_VA_TEX5MTXIDX,
  GX_VA_TEX6MTXIDX,
  GX_VA_TEX7MTXIDX,
  GX_VA_POS,
  GX_VA_NRM,
  GX_VA_CLR0,
  GX_VA_CLR1,
  GX_VA_TEX0,
  GX_VA_TEX1,
  GX_VA_TEX2,
  GX_VA_TEX3,
  GX_VA_TEX4,
  GX_VA_TEX5,
  GX_VA_TEX6,
  GX_VA_TEX7,
  GX_POS_MTX_ARRAY,
  GX_NRM_MTX_ARRAY,
  GX_TEX_MTX_ARRAY,
  GX_LIGHT_ARRAY,
  GX_VA_NBT,
  GX_VA_MAX_ATTR,
  GX_VA_NULL = 0xFF,
} GXAttr;

#define GX_MAX_VTXDESCLIST_SZ (GX_VA_MAX_ATTR + 1)

typedef enum _GXAttrType {
  GX_NONE,
  GX_DIRECT,
  GX_INDEX8,
  GX_INDEX16,
} GXAttrType;

#define _GX_TF_CTF 0x20
#define _GX_TF_ZTF 0x10

typedef enum _GXTexFmt {
  GX_TF_I4 = 0x0,
  GX_TF_I8 = 0x1,
  GX_TF_IA4 = 0x2,
  GX_TF_IA8 = 0x3,
  GX_TF_RGB565 = 0x4,
  GX_TF_RGB5A3 = 0x5,
  GX_TF_RGBA8 = 0x6,
  GX_TF_CMPR = 0xE,

  GX_CTF_R4 = 0x0 ,
  GX_CTF_RA4 = 0x2 ,
  GX_CTF_RA8 = 0x3 ,
  GX_CTF_YUVA8 = 0x6 ,
  GX_CTF_A8 = 0x7 ,
  GX_CTF_R8 = 0x8 ,
  GX_CTF_G8 = 0x9 ,
  GX_CTF_B8 = 0xA ,
  GX_CTF_RG8 = 0xB ,
  GX_CTF_GB8 = 0xC ,

  GX_TF_Z8 = 0x1 ,
  GX_TF_Z16 = 0x3 ,
  GX_TF_Z24X8 = 0x6 ,

  GX_CTF_Z4 = 0x0 ,
  GX_CTF_Z8M = 0x9 ,
  GX_CTF_Z8L = 0xA,
  GX_CTF_Z16L = 0xC,

  GX_TF_A8 = GX_CTF_A8,
} GXTexFmt;

typedef enum _GXCITexFmt {
  GX_TF_C4 = 0x8,
  GX_TF_C8 = 0x9,
  GX_TF_C14X2 = 0xa,
} GXCITexFmt;

typedef enum _GXTexWrapMode {
  GX_CLAMP,
  GX_REPEAT,
  GX_MIRROR,
  GX_MAX_TEXWRAPMODE,
} GXTexWrapMode;

typedef enum _GXTexFilter {
  GX_NEAR,
  GX_LINEAR,
  GX_NEAR_MIP_NEAR,
  GX_LIN_MIP_NEAR,
  GX_NEAR_MIP_LIN,
  GX_LIN_MIP_LIN,
} GXTexFilter;

typedef enum _GXAnisotropy {
  GX_ANISO_1,
  GX_ANISO_2,
  GX_ANISO_4,
  GX_MAX_ANISOTROPY,
} GXAnisotropy;

typedef enum _GXTexMapID {
  GX_TEXMAP0,
  GX_TEXMAP1,
  GX_TEXMAP2,
  GX_TEXMAP3,
  GX_TEXMAP4,
  GX_TEXMAP5,
  GX_TEXMAP6,
  GX_TEXMAP7,
  GX_MAX_TEXMAP,
  GX_TEXMAP_NULL = 0xFF,
  GX_TEX_DISABLE = 0x100,
} GXTexMapID;

typedef enum _GXTexCoordID {
  GX_TEXCOORD0,
  GX_TEXCOORD1,
  GX_TEXCOORD2,
  GX_TEXCOORD3,
  GX_TEXCOORD4,
  GX_TEXCOORD5,
  GX_TEXCOORD6,
  GX_TEXCOORD7,
  GX_MAX_TEXCOORD,
  GX_TEXCOORD_NULL = 0xFF,
} GXTexCoordID;

typedef enum _GXTevStageID {
  GX_TEVSTAGE0,
  GX_TEVSTAGE1,
  GX_TEVSTAGE2,
  GX_TEVSTAGE3,
  GX_TEVSTAGE4,
  GX_TEVSTAGE5,
  GX_TEVSTAGE6,
  GX_TEVSTAGE7,
  GX_TEVSTAGE8,
  GX_TEVSTAGE9,
  GX_TEVSTAGE10,
  GX_TEVSTAGE11,
  GX_TEVSTAGE12,
  GX_TEVSTAGE13,
  GX_TEVSTAGE14,
  GX_TEVSTAGE15,
  GX_MAX_TEVSTAGE,
} GXTevStageID;

typedef enum _GXTevMode {
  GX_MODULATE,
  GX_DECAL,
  GX_BLEND,
  GX_REPLACE,
  GX_PASSCLR,
} GXTevMode;

typedef enum _GXTexMtxType {
  GX_MTX3x4,
  GX_MTX2x4,
} GXTexMtxType;

typedef enum _GXTexGenType {
  GX_TG_MTX3x4,
  GX_TG_MTX2x4,
  GX_TG_BUMP0,
  GX_TG_BUMP1,
  GX_TG_BUMP2,
  GX_TG_BUMP3,
  GX_TG_BUMP4,
  GX_TG_BUMP5,
  GX_TG_BUMP6,
  GX_TG_BUMP7,
  GX_TG_SRTG,
} GXTexGenType;

typedef enum _GXPosNrmMtx {
  GX_PNMTX0 = 0,
  GX_PNMTX1 = 3,
  GX_PNMTX2 = 6,
  GX_PNMTX3 = 9,
  GX_PNMTX4 = 12,
  GX_PNMTX5 = 15,
  GX_PNMTX6 = 18,
  GX_PNMTX7 = 21,
  GX_PNMTX8 = 24,
  GX_PNMTX9 = 27,
} GXPosNrmMtx;

typedef enum _GXTexMtx {
  GX_TEXMTX0 = 30,
  GX_TEXMTX1 = 33,
  GX_TEXMTX2 = 36,
  GX_TEXMTX3 = 39,
  GX_TEXMTX4 = 42,
  GX_TEXMTX5 = 45,
  GX_TEXMTX6 = 48,
  GX_TEXMTX7 = 51,
  GX_TEXMTX8 = 54,
  GX_TEXMTX9 = 57,
  GX_IDENTITY = 60,
} GXTexMtx;

typedef enum _GXChannelID {
  GX_COLOR0,
  GX_COLOR1,
  GX_ALPHA0,
  GX_ALPHA1,
  GX_COLOR0A0,
  GX_COLOR1A1,
  GX_COLOR_ZERO,
  GX_ALPHA_BUMP,
  GX_ALPHA_BUMPN,
  GX_COLOR_NULL = 0xFF,
} GXChannelID;

typedef enum _GXTexGenSrc {
  GX_TG_POS,
  GX_TG_NRM,
  GX_TG_BINRM,
  GX_TG_TANGENT,
  GX_TG_TEX0,
  GX_TG_TEX1,
  GX_TG_TEX2,
  GX_TG_TEX3,
  GX_TG_TEX4,
  GX_TG_TEX5,
  GX_TG_TEX6,
  GX_TG_TEX7,
  GX_TG_TEXCOORD0,
  GX_TG_TEXCOORD1,
  GX_TG_TEXCOORD2,
  GX_TG_TEXCOORD3,
  GX_TG_TEXCOORD4,
  GX_TG_TEXCOORD5,
  GX_TG_TEXCOORD6,
  GX_TG_COLOR0,
  GX_TG_COLOR1,
  GX_MAX_TEXGENSRC,
} GXTexGenSrc;

typedef enum _GXBlendMode {
  GX_BM_NONE,
  GX_BM_BLEND,
  GX_BM_LOGIC,
  GX_BM_SUBTRACT,
  GX_MAX_BLENDMODE,
} GXBlendMode;

typedef enum _GXBlendFactor {
  GX_BL_ZERO,
  GX_BL_ONE,
  GX_BL_SRCCLR,
  GX_BL_INVSRCCLR,
  GX_BL_SRCALPHA,
  GX_BL_INVSRCALPHA,
  GX_BL_DSTALPHA,
  GX_BL_INVDSTALPHA,
  GX_BL_DSTCLR = GX_BL_SRCCLR,
  GX_BL_INVDSTCLR = GX_BL_INVSRCCLR,
} GXBlendFactor;

typedef enum _GXLogicOp {
  GX_LO_CLEAR,
  GX_LO_AND,
  GX_LO_REVAND,
  GX_LO_COPY,
  GX_LO_INVAND,
  GX_LO_NOOP,
  GX_LO_XOR,
  GX_LO_OR,
  GX_LO_NOR,
  GX_LO_EQUIV,
  GX_LO_INV,
  GX_LO_REVOR,
  GX_LO_INVCOPY,
  GX_LO_INVOR,
  GX_LO_NAND,
  GX_LO_SET,
} GXLogicOp;

typedef enum _GXCompCnt {
  GX_POS_XY = 0,
  GX_POS_XYZ = 1,
  GX_NRM_XYZ = 0,
  GX_NRM_NBT = 1,
  GX_NRM_NBT3 = 2,
  GX_CLR_RGB = 0,
  GX_CLR_RGBA = 1,
  GX_TEX_S = 0,
  GX_TEX_ST = 1,
} GXCompCnt;

typedef enum _GXCompType {
  GX_U8 = 0,
  GX_S8 = 1,
  GX_U16 = 2,
  GX_S16 = 3,
  GX_F32 = 4,
  GX_RGB565 = 0,
  GX_RGB8 = 1,
  GX_RGBX8 = 2,
  GX_RGBA4 = 3,
  GX_RGBA6 = 4,
  GX_RGBA8 = 5,
} GXCompType;

typedef enum _GXPTTexMtx {
  GX_PTTEXMTX0 = 64,
  GX_PTTEXMTX1 = 67,
  GX_PTTEXMTX2 = 70,
  GX_PTTEXMTX3 = 73,
  GX_PTTEXMTX4 = 76,
  GX_PTTEXMTX5 = 79,
  GX_PTTEXMTX6 = 82,
  GX_PTTEXMTX7 = 85,
  GX_PTTEXMTX8 = 88,
  GX_PTTEXMTX9 = 91,
  GX_PTTEXMTX10 = 94,
  GX_PTTEXMTX11 = 97,
  GX_PTTEXMTX12 = 100,
  GX_PTTEXMTX13 = 103,
  GX_PTTEXMTX14 = 106,
  GX_PTTEXMTX15 = 109,
  GX_PTTEXMTX16 = 112,
  GX_PTTEXMTX17 = 115,
  GX_PTTEXMTX18 = 118,
  GX_PTTEXMTX19 = 121,
  GX_PTIDENTITY = 125,
} GXPTTexMtx;

typedef enum _GXTevRegID {
  GX_TEVPREV,
  GX_TEVREG0,
  GX_TEVREG1,
  GX_TEVREG2,
  GX_MAX_TEVREG,
} GXTevRegID;

typedef enum _GXDiffuseFn {
  GX_DF_NONE,
  GX_DF_SIGN,
  GX_DF_CLAMP,
} GXDiffuseFn;

typedef enum _GXColorSrc {
  GX_SRC_REG,
  GX_SRC_VTX,
} GXColorSrc;

typedef enum _GXAttnFn {
  GX_AF_SPEC,
  GX_AF_SPOT,
  GX_AF_NONE,
} GXAttnFn;

typedef enum _GXLightID {
  GX_LIGHT0 = 0x001,
  GX_LIGHT1 = 0x002,
  GX_LIGHT2 = 0x004,
  GX_LIGHT3 = 0x008,
  GX_LIGHT4 = 0x010,
  GX_LIGHT5 = 0x020,
  GX_LIGHT6 = 0x040,
  GX_LIGHT7 = 0x080,
  GX_MAX_LIGHT = 0x100,
  GX_LIGHT_NULL = 0,
} GXLightID;

typedef enum _GXTexOffset {
  GX_TO_ZERO,
  GX_TO_SIXTEENTH,
  GX_TO_EIGHTH,
  GX_TO_FOURTH,
  GX_TO_HALF,
  GX_TO_ONE,
  GX_MAX_TEXOFFSET,
} GXTexOffset;

typedef enum _GXSpotFn {
  GX_SP_OFF,
  GX_SP_FLAT,
  GX_SP_COS,
  GX_SP_COS2,
  GX_SP_SHARP,
  GX_SP_RING1,
  GX_SP_RING2,
} GXSpotFn;

typedef enum _GXDistAttnFn {
  GX_DA_OFF,
  GX_DA_GENTLE,
  GX_DA_MEDIUM,
  GX_DA_STEEP,
} GXDistAttnFn;

typedef enum _GXCullMode {
  GX_CULL_NONE,
  GX_CULL_FRONT,
  GX_CULL_BACK,
  GX_CULL_ALL,
} GXCullMode;

typedef enum _GXTevSwapSel {
  GX_TEV_SWAP0 = 0,
  GX_TEV_SWAP1,
  GX_TEV_SWAP2,
  GX_TEV_SWAP3,
  GX_MAX_TEVSWAP,
} GXTevSwapSel;

typedef enum _GXTevColorChan {
  GX_CH_RED = 0,
  GX_CH_GREEN,
  GX_CH_BLUE,
  GX_CH_ALPHA,
} GXTevColorChan;

typedef enum _GXFogType {
  GX_FOG_NONE = 0,
  GX_FOG_PERSP_LIN = 2,
  GX_FOG_PERSP_EXP = 4,
  GX_FOG_PERSP_EXP2 = 5,
  GX_FOG_PERSP_REVEXP = 6,
  GX_FOG_PERSP_REVEXP2 = 7,
  GX_FOG_ORTHO_LIN = 10,
  GX_FOG_ORTHO_EXP = 12,
  GX_FOG_ORTHO_EXP2 = 13,
  GX_FOG_ORTHO_REVEXP = 14,
  GX_FOG_ORTHO_REVEXP2 = 15,
  GX_FOG_LIN = GX_FOG_PERSP_LIN,
  GX_FOG_EXP = GX_FOG_PERSP_EXP,
  GX_FOG_EXP2 = GX_FOG_PERSP_EXP2,
  GX_FOG_REVEXP = GX_FOG_PERSP_REVEXP,
  GX_FOG_REVEXP2 = GX_FOG_PERSP_REVEXP2,
} GXFogType;

typedef enum _GXTevColorArg {
  GX_CC_CPREV,
  GX_CC_APREV,
  GX_CC_C0,
  GX_CC_A0,
  GX_CC_C1,
  GX_CC_A1,
  GX_CC_C2,
  GX_CC_A2,
  GX_CC_TEXC,
  GX_CC_TEXA,
  GX_CC_RASC,
  GX_CC_RASA,
  GX_CC_ONE,
  GX_CC_HALF,
  GX_CC_KONST,
  GX_CC_ZERO,
} GXTevColorArg;

typedef enum _GXTevAlphaArg {
  GX_CA_APREV,
  GX_CA_A0,
  GX_CA_A1,
  GX_CA_A2,
  GX_CA_TEXA,
  GX_CA_RASA,
  GX_CA_KONST,
  GX_CA_ZERO,
} GXTevAlphaArg;

typedef enum _GXTevOp {
  GX_TEV_ADD = 0,
  GX_TEV_SUB = 1,
  GX_TEV_COMP_R8_GT = 8,
  GX_TEV_COMP_R8_EQ = 9,
  GX_TEV_COMP_GR16_GT = 10,
  GX_TEV_COMP_GR16_EQ = 11,
  GX_TEV_COMP_BGR24_GT = 12,
  GX_TEV_COMP_BGR24_EQ = 13,
  GX_TEV_COMP_RGB8_GT = 14,
  GX_TEV_COMP_RGB8_EQ = 15,
  GX_TEV_COMP_A8_GT = GX_TEV_COMP_RGB8_GT,
  GX_TEV_COMP_A8_EQ = GX_TEV_COMP_RGB8_EQ,
} GXTevOp;

typedef enum _GXTevBias {
  GX_TB_ZERO,
  GX_TB_ADDHALF,
  GX_TB_SUBHALF,
  GX_MAX_TEVBIAS,
} GXTevBias;

typedef enum _GXTevScale {
  GX_CS_SCALE_1,
  GX_CS_SCALE_2,
  GX_CS_SCALE_4,
  GX_CS_DIVIDE_2,
  GX_MAX_TEVSCALE,
} GXTevScale;

typedef enum _GXTevKColorSel {
  GX_TEV_KCSEL_8_8 = 0x00,
  GX_TEV_KCSEL_7_8 = 0x01,
  GX_TEV_KCSEL_6_8 = 0x02,
  GX_TEV_KCSEL_5_8 = 0x03,
  GX_TEV_KCSEL_4_8 = 0x04,
  GX_TEV_KCSEL_3_8 = 0x05,
  GX_TEV_KCSEL_2_8 = 0x06,
  GX_TEV_KCSEL_1_8 = 0x07,
  GX_TEV_KCSEL_1 = GX_TEV_KCSEL_8_8,
  GX_TEV_KCSEL_3_4 = GX_TEV_KCSEL_6_8,
  GX_TEV_KCSEL_1_2 = GX_TEV_KCSEL_4_8,
  GX_TEV_KCSEL_1_4 = GX_TEV_KCSEL_2_8,
  GX_TEV_KCSEL_K0 = 0x0C,
  GX_TEV_KCSEL_K1 = 0x0D,
  GX_TEV_KCSEL_K2 = 0x0E,
  GX_TEV_KCSEL_K3 = 0x0F,
  GX_TEV_KCSEL_K0_R = 0x10,
  GX_TEV_KCSEL_K1_R = 0x11,
  GX_TEV_KCSEL_K2_R = 0x12,
  GX_TEV_KCSEL_K3_R = 0x13,
  GX_TEV_KCSEL_K0_G = 0x14,
  GX_TEV_KCSEL_K1_G = 0x15,
  GX_TEV_KCSEL_K2_G = 0x16,
  GX_TEV_KCSEL_K3_G = 0x17,
  GX_TEV_KCSEL_K0_B = 0x18,
  GX_TEV_KCSEL_K1_B = 0x19,
  GX_TEV_KCSEL_K2_B = 0x1A,
  GX_TEV_KCSEL_K3_B = 0x1B,
  GX_TEV_KCSEL_K0_A = 0x1C,
  GX_TEV_KCSEL_K1_A = 0x1D,
  GX_TEV_KCSEL_K2_A = 0x1E,
  GX_TEV_KCSEL_K3_A = 0x1F,
} GXTevKColorSel;

typedef enum _GXTevKAlphaSel {
  GX_TEV_KASEL_8_8 = 0x00,
  GX_TEV_KASEL_7_8 = 0x01,
  GX_TEV_KASEL_6_8 = 0x02,
  GX_TEV_KASEL_5_8 = 0x03,
  GX_TEV_KASEL_4_8 = 0x04,
  GX_TEV_KASEL_3_8 = 0x05,
  GX_TEV_KASEL_2_8 = 0x06,
  GX_TEV_KASEL_1_8 = 0x07,
  GX_TEV_KASEL_1 = GX_TEV_KASEL_8_8,
  GX_TEV_KASEL_3_4 = GX_TEV_KASEL_6_8,
  GX_TEV_KASEL_1_2 = GX_TEV_KASEL_4_8,
  GX_TEV_KASEL_1_4 = GX_TEV_KASEL_2_8,
  GX_TEV_KASEL_K0_R = 0x10,
  GX_TEV_KASEL_K1_R = 0x11,
  GX_TEV_KASEL_K2_R = 0x12,
  GX_TEV_KASEL_K3_R = 0x13,
  GX_TEV_KASEL_K0_G = 0x14,
  GX_TEV_KASEL_K1_G = 0x15,
  GX_TEV_KASEL_K2_G = 0x16,
  GX_TEV_KASEL_K3_G = 0x17,
  GX_TEV_KASEL_K0_B = 0x18,
  GX_TEV_KASEL_K1_B = 0x19,
  GX_TEV_KASEL_K2_B = 0x1A,
  GX_TEV_KASEL_K3_B = 0x1B,
  GX_TEV_KASEL_K0_A = 0x1C,
  GX_TEV_KASEL_K1_A = 0x1D,
  GX_TEV_KASEL_K2_A = 0x1E,
  GX_TEV_KASEL_K3_A = 0x1F,
} GXTevKAlphaSel;

typedef enum _GXTevKColorID {
  GX_KCOLOR0 = 0,
  GX_KCOLOR1,
  GX_KCOLOR2,
  GX_KCOLOR3,
  GX_MAX_KCOLOR,
} GXTevKColorID;

typedef enum _GXZTexOp {
  GX_ZT_DISABLE,
  GX_ZT_ADD,
  GX_ZT_REPLACE,
  GX_MAX_ZTEXOP,
} GXZTexOp;

typedef enum _GXIndTexFormat {
  GX_ITF_8,
  GX_ITF_5,
  GX_ITF_4,
  GX_ITF_3,
  GX_MAX_ITFORMAT,
} GXIndTexFormat;

typedef enum _GXIndTexBiasSel {
  GX_ITB_NONE,
  GX_ITB_S,
  GX_ITB_T,
  GX_ITB_ST,
  GX_ITB_U,
  GX_ITB_SU,
  GX_ITB_TU,
  GX_ITB_STU,
  GX_MAX_ITBIAS,
} GXIndTexBiasSel;

typedef enum _GXIndTexAlphaSel {
  GX_ITBA_OFF,
  GX_ITBA_S,
  GX_ITBA_T,
  GX_ITBA_U,
  GX_MAX_ITBALPHA,
} GXIndTexAlphaSel;

typedef enum _GXIndTexMtxID {
  GX_ITM_OFF,
  GX_ITM_0,
  GX_ITM_1,
  GX_ITM_2,
  GX_ITM_S0 = 5,
  GX_ITM_S1,
  GX_ITM_S2,
  GX_ITM_T0 = 9,
  GX_ITM_T1,
  GX_ITM_T2,
} GXIndTexMtxID;

typedef enum _GXIndTexWrap {
  GX_ITW_OFF,
  GX_ITW_256,
  GX_ITW_128,
  GX_ITW_64,
  GX_ITW_32,
  GX_ITW_16,
  GX_ITW_0,
  GX_MAX_ITWRAP,
} GXIndTexWrap;

typedef enum _GXIndTexStageID {
  GX_INDTEXSTAGE0,
  GX_INDTEXSTAGE1,
  GX_INDTEXSTAGE2,
  GX_INDTEXSTAGE3,
  GX_MAX_INDTEXSTAGE,
} GXIndTexStageID;

typedef enum _GXIndTexScale {
  GX_ITS_1,
  GX_ITS_2,
  GX_ITS_4,
  GX_ITS_8,
  GX_ITS_16,
  GX_ITS_32,
  GX_ITS_64,
  GX_ITS_128,
  GX_ITS_256,
  GX_MAX_ITSCALE,
} GXIndTexScale;

typedef enum _GXClipMode {
  GX_CLIP_ENABLE = 0,
  GX_CLIP_DISABLE = 1,
} GXClipMode;

typedef enum _GXTlut {
  GX_TLUT0 = 0,
  GX_TLUT1 = 1,
  GX_TLUT2 = 2,
  GX_TLUT3 = 3,
  GX_TLUT4 = 4,
  GX_TLUT5 = 5,
  GX_TLUT6 = 6,
  GX_TLUT7 = 7,
  GX_TLUT8 = 8,
  GX_TLUT9 = 9,
  GX_TLUT10 = 10,
  GX_TLUT11 = 11,
  GX_TLUT12 = 12,
  GX_TLUT13 = 13,
  GX_TLUT14 = 14,
  GX_TLUT15 = 15,
  GX_BIGTLUT0 = 16,
  GX_BIGTLUT1 = 17,
  GX_BIGTLUT2 = 18,
  GX_BIGTLUT3 = 19,
} GXTlut;

typedef enum _GXTlutFmt {
  GX_TL_IA8,
  GX_TL_RGB565,
  GX_TL_RGB5A3,
  GX_MAX_TLUTFMT,
} GXTlutFmt;

typedef enum _GXMiscToken {
  GX_MT_NULL = 0,
  GX_MT_XF_FLUSH = 1,
  GX_MT_DL_SAVE_CONTEXT = 2,
  GX_MT_ABORT_WAIT_COPYOUT = 3,
} GXMiscToken;

typedef enum _GXTexCacheSize {
  GX_TEXCACHE_32K,
  GX_TEXCACHE_128K,
  GX_TEXCACHE_512K,
  GX_TEXCACHE_NONE
} GXTexCacheSize;

typedef enum _GXPerf0 {
  GX_PERF0_VERTICES,
  GX_PERF0_CLIP_VTX,
  GX_PERF0_CLIP_CLKS,
  GX_PERF0_XF_WAIT_IN,
  GX_PERF0_XF_WAIT_OUT,
  GX_PERF0_XF_XFRM_CLKS,
  GX_PERF0_XF_LIT_CLKS,
  GX_PERF0_XF_BOT_CLKS,
  GX_PERF0_XF_REGLD_CLKS,
  GX_PERF0_XF_REGRD_CLKS,
  GX_PERF0_CLIP_RATIO,

  GX_PERF0_TRIANGLES,
  GX_PERF0_TRIANGLES_CULLED,
  GX_PERF0_TRIANGLES_PASSED,
  GX_PERF0_TRIANGLES_SCISSORED,
  GX_PERF0_TRIANGLES_0TEX,
  GX_PERF0_TRIANGLES_1TEX,
  GX_PERF0_TRIANGLES_2TEX,
  GX_PERF0_TRIANGLES_3TEX,
  GX_PERF0_TRIANGLES_4TEX,
  GX_PERF0_TRIANGLES_5TEX,
  GX_PERF0_TRIANGLES_6TEX,
  GX_PERF0_TRIANGLES_7TEX,
  GX_PERF0_TRIANGLES_8TEX,
  GX_PERF0_TRIANGLES_0CLR,
  GX_PERF0_TRIANGLES_1CLR,
  GX_PERF0_TRIANGLES_2CLR,

  GX_PERF0_QUAD_0CVG,
  GX_PERF0_QUAD_NON0CVG,
  GX_PERF0_QUAD_1CVG,
  GX_PERF0_QUAD_2CVG,
  GX_PERF0_QUAD_3CVG,
  GX_PERF0_QUAD_4CVG,
  GX_PERF0_AVG_QUAD_CNT,

  GX_PERF0_CLOCKS,
  GX_PERF0_NONE

} GXPerf0;

typedef enum _GXPerf1 {
  GX_PERF1_TEXELS,
  GX_PERF1_TX_IDLE,
  GX_PERF1_TX_REGS,
  GX_PERF1_TX_MEMSTALL,
  GX_PERF1_TC_CHECK1_2,
  GX_PERF1_TC_CHECK3_4,
  GX_PERF1_TC_CHECK5_6,
  GX_PERF1_TC_CHECK7_8,
  GX_PERF1_TC_MISS,

  GX_PERF1_VC_ELEMQ_FULL,
  GX_PERF1_VC_MISSQ_FULL,
  GX_PERF1_VC_MEMREQ_FULL,
  GX_PERF1_VC_STATUS7,
  GX_PERF1_VC_MISSREP_FULL,
  GX_PERF1_VC_STREAMBUF_LOW,
  GX_PERF1_VC_ALL_STALLS,
  GX_PERF1_VERTICES,

  GX_PERF1_FIFO_REQ,
  GX_PERF1_CALL_REQ,
  GX_PERF1_VC_MISS_REQ,
  GX_PERF1_CP_ALL_REQ,

  GX_PERF1_CLOCKS,
  GX_PERF1_NONE

} GXPerf1;

typedef enum _GXVCachePerf {
  GX_VC_POS,
  GX_VC_NRM,
  GX_VC_CLR0,
  GX_VC_CLR1,
  GX_VC_TEX0,
  GX_VC_TEX1,
  GX_VC_TEX2,
  GX_VC_TEX3,
  GX_VC_TEX4,
  GX_VC_TEX5,
  GX_VC_TEX6,
  GX_VC_TEX7,
  GX_VC_ALL = 0xf

} GXVCachePerf;

typedef enum _GXFBClamp {
  GX_CLAMP_NONE = 0,
  GX_CLAMP_TOP = 1,
  GX_CLAMP_BOTTOM = 2,
} GXFBClamp;

typedef enum _GXCopyMode {
  GX_COPY_PROGRESSIVE = 0,
  GX_COPY_INTLC_EVEN = 2,
  GX_COPY_INTLC_ODD = 3,
} GXCopyMode;

typedef enum _GXAlphaReadMode {
  GX_READ_00 = 0,
  GX_READ_FF = 1,
  GX_READ_NONE = 2,

} _GXAlphaReadMode;

typedef enum _GXLogicOp {
  GX_LO_CLEAR,
  GX_LO_AND,
  GX_LO_REVAND,
  GX_LO_COPY,
  GX_LO_INVAND,
  GX_LO_NOOP,
  GX_LO_XOR,
  GX_LO_OR,
  GX_LO_NOR,
  GX_LO_EQUIV,
  GX_LO_INV,
  GX_LO_REVOR,
  GX_LO_INVCOPY,
  GX_LO_INVOR,
  GX_LO_NAND,
  GX_LO_SET,
} GXLogicOp;

typedef enum _GXCompCnt {
  GX_POS_XY = 0,
  GX_POS_XYZ = 1,
  GX_NRM_XYZ = 0,
  GX_NRM_NBT = 1,
  GX_NRM_NBT3 = 2,
  GX_CLR_RGB = 0,
  GX_CLR_RGBA = 1,
  GX_TEX_S = 0,
  GX_TEX_ST = 1,
} GXCompCnt;

typedef enum _GXCompType {
  GX_U8 = 0,
  GX_S8 = 1,
  GX_U16 = 2,
  GX_S16 = 3,
  GX_F32 = 4,
  GX_RGB565 = 0,
  GX_RGB8 = 1,
  GX_RGBX8 = 2,
  GX_RGBA4 = 3,
  GX_RGBA6 = 4,
  GX_RGBA8 = 5,
} GXCompType;

typedef enum _GXPTTexMtx {
  GX_PTTEXMTX0 = 64,
  GX_PTTEXMTX1 = 67,
  GX_PTTEXMTX2 = 70,
  GX_PTTEXMTX3 = 73,
  GX_PTTEXMTX4 = 76,
  GX_PTTEXMTX5 = 79,
  GX_PTTEXMTX6 = 82,
  GX_PTTEXMTX7 = 85,
  GX_PTTEXMTX8 = 88,
  GX_PTTEXMTX9 = 91,
  GX_PTTEXMTX10 = 94,
  GX_PTTEXMTX11 = 97,
  GX_PTTEXMTX12 = 100,
  GX_PTTEXMTX13 = 103,
  GX_PTTEXMTX14 = 106,
  GX_PTTEXMTX15 = 109,
  GX_PTTEXMTX16 = 112,
  GX_PTTEXMTX17 = 115,
  GX_PTTEXMTX18 = 118,
  GX_PTTEXMTX19 = 121,
  GX_PTIDENTITY = 125,
} GXPTTexMtx;

typedef struct _GXColor {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} GXColor;

typedef struct _GXTexObj {
  u32 dummy[8];
} GXTexObj;

typedef struct _GXTlutObj {
  u32 dummy[3];
} GXTlutObj;

typedef struct _GXLightObj {
  u32 dummy[16];
} GXLightObj;

typedef struct _GXVtxDescList {
  GXAttr attr;
  GXAttrType type;
} GXVtxDescList;

typedef struct _GXColorS10 {
  s16 r;
  s16 g;
  s16 b;
  s16 a;
} GXColorS10;

typedef struct _GXTexRegion {
  u32 dummy[4];
} GXTexRegion;

typedef struct _GXTlutRegion {
  u32 dummy[4];
} GXTlutRegion;

typedef struct _GXVtxAttrFmtList {
  // total size: 0x10
  GXAttr attr;     // offset 0x0, size 0x4
  GXCompCnt cnt;   // offset 0x4, size 0x4
  GXCompType type; // offset 0x8, size 0x4
  u8 frac;         // offset 0xC, size 0x1
} GXVtxAttrFmtList;

typedef enum _GXTevRegID {
  GX_TEVPREV,
  GX_TEVREG0,
  GX_TEVREG1,
  GX_TEVREG2,
  GX_MAX_TEVREG,
} GXTevRegID;

typedef enum _GXDiffuseFn {
  GX_DF_NONE,
  GX_DF_SIGN,
  GX_DF_CLAMP,
} GXDiffuseFn;

typedef enum _GXColorSrc {
  GX_SRC_REG,
  GX_SRC_VTX,
} GXColorSrc;

typedef enum _GXAttnFn {
  GX_AF_SPEC,
  GX_AF_SPOT,
  GX_AF_NONE,
} GXAttnFn;

typedef enum _GXLightID {
  GX_LIGHT0 = 0x001,
  GX_LIGHT1 = 0x002,
  GX_LIGHT2 = 0x004,
  GX_LIGHT3 = 0x008,
  GX_LIGHT4 = 0x010,
  GX_LIGHT5 = 0x020,
  GX_LIGHT6 = 0x040,
  GX_LIGHT7 = 0x080,
  GX_MAX_LIGHT = 0x100,
  GX_LIGHT_NULL = 0,
} GXLightID;

typedef enum _GXTexOffset {
  GX_TO_ZERO,
  GX_TO_SIXTEENTH,
  GX_TO_EIGHTH,
  GX_TO_FOURTH,
  GX_TO_HALF,
  GX_TO_ONE,
  GX_MAX_TEXOFFSET,
} GXTexOffset;

typedef enum _GXSpotFn {
  GX_SP_OFF,
  GX_SP_FLAT,
  GX_SP_COS,
  GX_SP_COS2,
  GX_SP_SHARP,
  GX_SP_RING1,
  GX_SP_RING2,
} GXSpotFn;

typedef enum _GXDistAttnFn {
  GX_DA_OFF,
  GX_DA_GENTLE,
  GX_DA_MEDIUM,
  GX_DA_STEEP,
} GXDistAttnFn;

typedef enum _GXCullMode {
  GX_CULL_NONE,
  GX_CULL_FRONT,
  GX_CULL_BACK,
  GX_CULL_ALL,
} GXCullMode;

typedef enum _GXTevSwapSel {
  GX_TEV_SWAP0 = 0,
  GX_TEV_SWAP1,
  GX_TEV_SWAP2,
  GX_TEV_SWAP3,
  GX_MAX_TEVSWAP,
} GXTevSwapSel;

typedef enum _GXTevColorChan {
  GX_CH_RED = 0,
  GX_CH_GREEN,
  GX_CH_BLUE,
  GX_CH_ALPHA,
} GXTevColorChan;

typedef enum _GXFogType {
  GX_FOG_NONE = 0,
  GX_FOG_PERSP_LIN = 2,
  GX_FOG_PERSP_EXP = 4,
  GX_FOG_PERSP_EXP2 = 5,
  GX_FOG_PERSP_REVEXP = 6,
  GX_FOG_PERSP_REVEXP2 = 7,
  GX_FOG_ORTHO_LIN = 10,
  GX_FOG_ORTHO_EXP = 12,
  GX_FOG_ORTHO_EXP2 = 13,
  GX_FOG_ORTHO_REVEXP = 14,
  GX_FOG_ORTHO_REVEXP2 = 15,
  GX_FOG_LIN = GX_FOG_PERSP_LIN,
  GX_FOG_EXP = GX_FOG_PERSP_EXP,
  GX_FOG_EXP2 = GX_FOG_PERSP_EXP2,
  GX_FOG_REVEXP = GX_FOG_PERSP_REVEXP,
  GX_FOG_REVEXP2 = GX_FOG_PERSP_REVEXP2,
} GXFogType;

typedef enum _GXTevColorArg {
  GX_CC_CPREV,
  GX_CC_APREV,
  GX_CC_C0,
  GX_CC_A0,
  GX_CC_C1,
  GX_CC_A1,
  GX_CC_C2,
  GX_CC_A2,
  GX_CC_TEXC,
  GX_CC_TEXA,
  GX_CC_RASC,
  GX_CC_RASA,
  GX_CC_ONE,
  GX_CC_HALF,
  GX_CC_KONST,
  GX_CC_ZERO,
} GXTevColorArg;

typedef enum _GXTevAlphaArg {
  GX_CA_APREV,
  GX_CA_A0,
  GX_CA_A1,
  GX_CA_A2,
  GX_CA_TEXA,
  GX_CA_RASA,
  GX_CA_KONST,
  GX_CA_ZERO,
} GXTevAlphaArg;

typedef enum _GXTevOp {
  GX_TEV_ADD = 0,
  GX_TEV_SUB = 1,
  GX_TEV_COMP_R8_GT = 8,
  GX_TEV_COMP_R8_EQ = 9,
  GX_TEV_COMP_GR16_GT = 10,
  GX_TEV_COMP_GR16_EQ = 11,
  GX_TEV_COMP_BGR24_GT = 12,
  GX_TEV_COMP_BGR24_EQ = 13,
  GX_TEV_COMP_RGB8_GT = 14,
  GX_TEV_COMP_RGB8_EQ = 15,
  GX_TEV_COMP_A8_GT = GX_TEV_COMP_RGB8_GT,
  GX_TEV_COMP_A8_EQ = GX_TEV_COMP_RGB8_EQ,
} GXTevOp;

typedef enum _GXTevBias {
  GX_TB_ZERO,
  GX_TB_ADDHALF,
  GX_TB_SUBHALF,
  GX_MAX_TEVBIAS,
} GXTevBias;

typedef enum _GXTevScale {
  GX_CS_SCALE_1,
  GX_CS_SCALE_2,
  GX_CS_SCALE_4,
  GX_CS_DIVIDE_2,
  GX_MAX_TEVSCALE,
} GXTevScale;

typedef enum _GXTevKColorSel {
  GX_TEV_KCSEL_8_8 = 0x00,
  GX_TEV_KCSEL_7_8 = 0x01,
  GX_TEV_KCSEL_6_8 = 0x02,
  GX_TEV_KCSEL_5_8 = 0x03,
  GX_TEV_KCSEL_4_8 = 0x04,
  GX_TEV_KCSEL_3_8 = 0x05,
  GX_TEV_KCSEL_2_8 = 0x06,
  GX_TEV_KCSEL_1_8 = 0x07,
  GX_TEV_KCSEL_1 = GX_TEV_KCSEL_8_8,
  GX_TEV_KCSEL_3_4 = GX_TEV_KCSEL_6_8,
  GX_TEV_KCSEL_1_2 = GX_TEV_KCSEL_4_8,
  GX_TEV_KCSEL_1_4 = GX_TEV_KCSEL_2_8,
  GX_TEV_KCSEL_K0 = 0x0C,
  GX_TEV_KCSEL_K1 = 0x0D,
  GX_TEV_KCSEL_K2 = 0x0E,
  GX_TEV_KCSEL_K3 = 0x0F,
  GX_TEV_KCSEL_K0_R = 0x10,
  GX_TEV_KCSEL_K1_R = 0x11,
  GX_TEV_KCSEL_K2_R = 0x12,
  GX_TEV_KCSEL_K3_R = 0x13,
  GX_TEV_KCSEL_K0_G = 0x14,
  GX_TEV_KCSEL_K1_G = 0x15,
  GX_TEV_KCSEL_K2_G = 0x16,
  GX_TEV_KCSEL_K3_G = 0x17,
  GX_TEV_KCSEL_K0_B = 0x18,
  GX_TEV_KCSEL_K1_B = 0x19,
  GX_TEV_KCSEL_K2_B = 0x1A,
  GX_TEV_KCSEL_K3_B = 0x1B,
  GX_TEV_KCSEL_K0_A = 0x1C,
  GX_TEV_KCSEL_K1_A = 0x1D,
  GX_TEV_KCSEL_K2_A = 0x1E,
  GX_TEV_KCSEL_K3_A = 0x1F,
} GXTevKColorSel;

typedef enum _GXTevKAlphaSel {
  GX_TEV_KASEL_8_8 = 0x00,
  GX_TEV_KASEL_7_8 = 0x01,
  GX_TEV_KASEL_6_8 = 0x02,
  GX_TEV_KASEL_5_8 = 0x03,
  GX_TEV_KASEL_4_8 = 0x04,
  GX_TEV_KASEL_3_8 = 0x05,
  GX_TEV_KASEL_2_8 = 0x06,
  GX_TEV_KASEL_1_8 = 0x07,
  GX_TEV_KASEL_1 = GX_TEV_KASEL_8_8,
  GX_TEV_KASEL_3_4 = GX_TEV_KASEL_6_8,
  GX_TEV_KASEL_1_2 = GX_TEV_KASEL_4_8,
  GX_TEV_KASEL_1_4 = GX_TEV_KASEL_2_8,
  GX_TEV_KASEL_K0_R = 0x10,
  GX_TEV_KASEL_K1_R = 0x11,
  GX_TEV_KASEL_K2_R = 0x12,
  GX_TEV_KASEL_K3_R = 0x13,
  GX_TEV_KASEL_K0_G = 0x14,
  GX_TEV_KASEL_K1_G = 0x15,
  GX_TEV_KASEL_K2_G = 0x16,
  GX_TEV_KASEL_K3_G = 0x17,
  GX_TEV_KASEL_K0_B = 0x18,
  GX_TEV_KASEL_K1_B = 0x19,
  GX_TEV_KASEL_K2_B = 0x1A,
  GX_TEV_KASEL_K3_B = 0x1B,
  GX_TEV_KASEL_K0_A = 0x1C,
  GX_TEV_KASEL_K1_A = 0x1D,
  GX_TEV_KASEL_K2_A = 0x1E,
  GX_TEV_KASEL_K3_A = 0x1F,
} GXTevKAlphaSel;

typedef enum _GXTevKColorID {
  GX_KCOLOR0 = 0,
  GX_KCOLOR1,
  GX_KCOLOR2,
  GX_KCOLOR3,
  GX_MAX_KCOLOR,
} GXTevKColorID;

typedef enum _GXZTexOp {
  GX_ZT_DISABLE,
  GX_ZT_ADD,
  GX_ZT_REPLACE,
  GX_MAX_ZTEXOP,
} GXZTexOp;

typedef enum _GXIndTexFormat {
  GX_ITF_8,
  GX_ITF_5,
  GX_ITF_4,
  GX_ITF_3,
  GX_MAX_ITFORMAT,
} GXIndTexFormat;

typedef enum _GXIndTexBiasSel {
  GX_ITB_NONE,
  GX_ITB_S,
  GX_ITB_T,
  GX_ITB_ST,
  GX_ITB_U,
  GX_ITB_SU,
  GX_ITB_TU,
  GX_ITB_STU,
  GX_MAX_ITBIAS,
} GXIndTexBiasSel;

typedef enum _GXIndTexAlphaSel {
  GX_ITBA_OFF,
  GX_ITBA_S,
  GX_ITBA_T,
  GX_ITBA_U,
  GX_MAX_ITBALPHA,
} GXIndTexAlphaSel;

typedef enum _GXIndTexMtxID {
  GX_ITM_OFF,
  GX_ITM_0,
  GX_ITM_1,
  GX_ITM_2,
  GX_ITM_S0 = 5,
  GX_ITM_S1,
  GX_ITM_S2,
  GX_ITM_T0 = 9,
  GX_ITM_T1,
  GX_ITM_T2,
} GXIndTexMtxID;

typedef enum _GXIndTexWrap {
  GX_ITW_OFF,
  GX_ITW_256,
  GX_ITW_128,
  GX_ITW_64,
  GX_ITW_32,
  GX_ITW_16,
  GX_ITW_0,
  GX_MAX_ITWRAP,
} GXIndTexWrap;

typedef enum _GXIndTexStageID {
  GX_INDTEXSTAGE0,
  GX_INDTEXSTAGE1,
  GX_INDTEXSTAGE2,
  GX_INDTEXSTAGE3,
  GX_MAX_INDTEXSTAGE,
} GXIndTexStageID;

typedef enum _GXIndTexScale {
  GX_ITS_1,
  GX_ITS_2,
  GX_ITS_4,
  GX_ITS_8,
  GX_ITS_16,
  GX_ITS_32,
  GX_ITS_64,
  GX_ITS_128,
  GX_ITS_256,
  GX_MAX_ITSCALE,
} GXIndTexScale;

typedef enum _GXClipMode {
  GX_CLIP_ENABLE = 0,
  GX_CLIP_DISABLE = 1,
} GXClipMode;

typedef enum _GXTlut {
  GX_TLUT0 = 0,
  GX_TLUT1 = 1,
  GX_TLUT2 = 2,
  GX_TLUT3 = 3,
  GX_TLUT4 = 4,
  GX_TLUT5 = 5,
  GX_TLUT6 = 6,
  GX_TLUT7 = 7,
  GX_TLUT8 = 8,
  GX_TLUT9 = 9,
  GX_TLUT10 = 10,
  GX_TLUT11 = 11,
  GX_TLUT12 = 12,
  GX_TLUT13 = 13,
  GX_TLUT14 = 14,
  GX_TLUT15 = 15,
  GX_BIGTLUT0 = 16,
  GX_BIGTLUT1 = 17,
  GX_BIGTLUT2 = 18,
  GX_BIGTLUT3 = 19,
} GXTlut;

typedef enum _GXTlutFmt {
  GX_TL_IA8,
  GX_TL_RGB565,
  GX_TL_RGB5A3,
  GX_MAX_TLUTFMT,
} GXTlutFmt;

typedef enum _GXMiscToken {
  GX_MT_NULL = 0,
  GX_MT_XF_FLUSH = 1,
  GX_MT_DL_SAVE_CONTEXT = 2,
  GX_MT_ABORT_WAIT_COPYOUT = 3,
} GXMiscToken;

typedef enum _GXTexCacheSize {
  GX_TEXCACHE_32K,
  GX_TEXCACHE_128K,
  GX_TEXCACHE_512K,
  GX_TEXCACHE_NONE
} GXTexCacheSize;

typedef enum _GXPerf0 {
  GX_PERF0_VERTICES,
  GX_PERF0_CLIP_VTX,
  GX_PERF0_CLIP_CLKS,
  GX_PERF0_XF_WAIT_IN,
  GX_PERF0_XF_WAIT_OUT,
  GX_PERF0_XF_XFRM_CLKS,
  GX_PERF0_XF_LIT_CLKS,
  GX_PERF0_XF_BOT_CLKS,
  GX_PERF0_XF_REGLD_CLKS,
  GX_PERF0_XF_REGRD_CLKS,
  GX_PERF0_CLIP_RATIO,

  GX_PERF0_TRIANGLES,
  GX_PERF0_TRIANGLES_CULLED,
  GX_PERF0_TRIANGLES_PASSED,
  GX_PERF0_TRIANGLES_SCISSORED,
  GX_PERF0_TRIANGLES_0TEX,
  GX_PERF0_TRIANGLES_1TEX,
  GX_PERF0_TRIANGLES_2TEX,
  GX_PERF0_TRIANGLES_3TEX,
  GX_PERF0_TRIANGLES_4TEX,
  GX_PERF0_TRIANGLES_5TEX,
  GX_PERF0_TRIANGLES_6TEX,
  GX_PERF0_TRIANGLES_7TEX,
  GX_PERF0_TRIANGLES_8TEX,
  GX_PERF0_TRIANGLES_0CLR,
  GX_PERF0_TRIANGLES_1CLR,
  GX_PERF0_TRIANGLES_2CLR,

  GX_PERF0_QUAD_0CVG,
  GX_PERF0_QUAD_NON0CVG,
  GX_PERF0_QUAD_1CVG,
  GX_PERF0_QUAD_2CVG,
  GX_PERF0_QUAD_3CVG,
  GX_PERF0_QUAD_4CVG,
  GX_PERF0_AVG_QUAD_CNT,

  GX_PERF0_CLOCKS,
  GX_PERF0_NONE

} GXPerf0;

typedef enum _GXPerf1 {
  GX_PERF1_TEXELS,
  GX_PERF1_TX_IDLE,
  GX_PERF1_TX_REGS,
  GX_PERF1_TX_MEMSTALL,
  GX_PERF1_TC_CHECK1_2,
  GX_PERF1_TC_CHECK3_4,
  GX_PERF1_TC_CHECK5_6,
  GX_PERF1_TC_CHECK7_8,
  GX_PERF1_TC_MISS,

  GX_PERF1_VC_ELEMQ_FULL,
  GX_PERF1_VC_MISSQ_FULL,
  GX_PERF1_VC_MEMREQ_FULL,
  GX_PERF1_VC_STATUS7,
  GX_PERF1_VC_MISSREP_FULL,
  GX_PERF1_VC_STREAMBUF_LOW,
  GX_PERF1_VC_ALL_STALLS,
  GX_PERF1_VERTICES,

  GX_PERF1_FIFO_REQ,
  GX_PERF1_CALL_REQ,
  GX_PERF1_VC_MISS_REQ,
  GX_PERF1_CP_ALL_REQ,

  GX_PERF1_CLOCKS,
  GX_PERF1_NONE

} GXPerf1;

typedef enum _GXVCachePerf {
  GX_VC_POS,
  GX_VC_NRM,
  GX_VC_CLR0,
  GX_VC_CLR1,
  GX_VC_TEX0,
  GX_VC_TEX1,
  GX_VC_TEX2,
  GX_VC_TEX3,
  GX_VC_TEX4,
  GX_VC_TEX5,
  GX_VC_TEX6,
  GX_VC_TEX7,
  GX_VC_ALL = 0xf

} GXVCachePerf;

typedef enum _GXFBClamp {
  GX_CLAMP_NONE = 0,
  GX_CLAMP_TOP = 1,
  GX_CLAMP_BOTTOM = 2,
} GXFBClamp;

typedef enum _GXCopyMode {
  GX_COPY_PROGRESSIVE = 0,
  GX_COPY_INTLC_EVEN = 2,
  GX_COPY_INTLC_ODD = 3,
} GXCopyMode;

typedef enum _GXAlphaReadMode {
  GX_READ_00 = 0,
  GX_READ_FF = 1,
  GX_READ_NONE = 2,

} _GXAlphaReadMode;

#define ANIM_BMP_RGBA8 0
#define ANIM_BMP_RGB5A3 1
#define ANIM_BMP_RGB5A3_DUPE 2
#define ANIM_BMP_C8 3
#define ANIM_BMP_C4 4
#define ANIM_BMP_IA8 5
#define ANIM_BMP_IA4 6
#define ANIM_BMP_I8 7
#define ANIM_BMP_I4 8
#define ANIM_BMP_A8 9
#define ANIM_BMP_CMPR 10

#define ANIM_BMP_FMTMASK 0xF
#define ANIM_BMP_ALLOC 0x8000
#define ANIM_BMP_NUM_MASK 0x7FFF

#define ANIM_LAYER_FLIPX 0x1
#define ANIM_LAYER_FLIPY 0x2

typedef struct anim_frame_data {
  s16 pat;
  s16 time;
  s16 shiftX;
  s16 shiftY;
  s16 flip;
  s16 pad;
} AnimFrameData;

typedef struct anim_bank_data {
  s16 timeNum;
  s16 unk;
  AnimFrameData *frame;
} AnimBankData;

typedef struct anim_layer_data {
  u8 alpha;
  u8 flip;
  s16 bmpNo;
  s16 startX;
  s16 startY;
  s16 sizeX;
  s16 sizeY;
  s16 shiftX;
  s16 shiftY;
  s16 vtx[8];
} AnimLayerData;

typedef struct anim_pat_data {
  s16 layerNum;
  s16 centerX;
  s16 centerY;
  s16 sizeX;
  s16 sizeY;
  AnimLayerData *layer;
} AnimPatData;

typedef struct anim_bmp_data {
  u8 pixSize;
  u8 dataFmt;
  s16 palNum;
  s16 sizeX;
  s16 sizeY;
  u32 dataSize;
  void *palData;
  void *data;
} AnimBmpData;

typedef struct anim_data {
  s16 bankNum;
  s16 patNum;
  s16 bmpNum;
  s16 useNum;
  AnimBankData *bank;
  AnimPatData *pat;
  AnimBmpData *bmp;
} AnimData;

typedef struct {
  f32 x, y, z;
} Vec, *VecPtr, Point3d, *Point3dPtr;

typedef struct {
  s16 x;
  s16 y;
  s16 z;
} S16Vec, *S16VecPtr;

typedef struct {
  f32 x, y, z, w;
} Quaternion, *QuaternionPtr, Qtrn, *QtrnPtr;

typedef f32 Mtx[3][4];

typedef f32 (*MtxPtr)[4];

typedef f32 ROMtx[4][3];

typedef f32 (*ROMtxPtr)[3];

typedef f32 Mtx44[4][4];

typedef f32 (*Mtx44Ptr)[4];

#define HUSPR_MAX 384
#define HUSPR_GRP_MAX 256

#define HUSPR_NONE -1
#define HUSPR_GRP_NONE -1

#define HUSPR_ATTR_NOANIM 0x1
#define HUSPR_ATTR_LOOP 0x2
#define HUSPR_ATTR_DISPOFF 0x4
#define HUSPR_ATTR_LINEAR 0x8
#define HUSPR_ATTR_FUNC 0x10
#define HUSPR_ATTR_NOPAUSE 0x20
#define HUSPR_ATTR_REVERSE 0x40
#define HUSPR_ATTR_ADDCOL 0x80
#define HUSPR_ATTR_INVCOL 0x100

typedef void (*HuSprFunc)(struct hu_sprite *);

typedef struct hu_sprite {
  u8 r;
  u8 g;
  u8 b;
  u8 draw_no;
  s16 frame;
  s16 bank;
  s16 attr;
  s16 dirty_flag;
  s16 prio;
  float time;
  float x;
  float y;
  float z_rot;
  float scale_x;
  float scale_y;
  float speed;
  float a;
  GXTexWrapMode wrap_s;
  GXTexWrapMode wrap_t;
  s16 tex_scale_x;
  s16 tex_scale_y;
  Mtx *group_mtx;
  union {
    AnimData *data;
    HuSprFunc func;
  };
  AnimPatData *pat_data;
  AnimFrameData *frame_data;
  s16 work[4];
  AnimData *bg;
  u16 bg_bank;
  s16 scissor_x;
  s16 scissor_y;
  s16 scissor_w;
  s16 scissor_h;
} HuSprite;

typedef struct hu_spr_grp {
  s16 capacity;
  float x;
  float y;
  float z_rot;
  float scale_x;
  float scale_y;
  float center_x;
  float center_y;
  s16 *members;
  Mtx mtx;
} HuSprGrp;

extern HuSprite HuSprData[HUSPR_MAX];
extern HuSprGrp HuSprGrpData[HUSPR_GRP_MAX];

#define HuSprAnimReadFile(data_id)                                             \
  (HuSprAnimRead(                                                              \
      HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

void HuSprInit(void);
void HuSprClose(void);
void HuSprExec(s16 draw_no);
void HuSprBegin(void);
HuSprite *HuSprCall(void);
void HuSprFinish(void);
void HuSprPauseSet(BOOL value);
AnimData *HuSprAnimRead(void *data);
void HuSprAnimLock(AnimData *anim);
s16 HuSprCreate(AnimData *anim, s16 prio, s16 bank);
s16 HuSprFuncCreate(HuSprFunc func, s16 prio);
s16 HuSprGrpCreate(s16 capacity);
s16 HuSprGrpCopy(s16 group);
void HuSprGrpMemberSet(s16 group, s16 member, s16 sprite);
void HuSprGrpMemberKill(s16 group, s16 member);
void HuSprGrpKill(s16 group);
void HuSprKill(s16 sprite);
void HuSprAnimKill(AnimData *anim);
void HuSprAttrSet(s16 group, s16 member, s32 attr);
void HuSprAttrReset(s16 group, s16 member, s32 attr);
void HuSprPosSet(s16 group, s16 member, float x, float y);
void HuSprZRotSet(s16 group, s16 member, float z_rot);
void HuSprScaleSet(s16 group, s16 member, float x, float y);
void HuSprTPLvlSet(s16 group, s16 member, float tp_lvl);
void HuSprColorSet(s16 group, s16 member, u8 r, u8 g, u8 b);
void HuSprSpeedSet(s16 group, s16 member, float speed);
void HuSprBankSet(s16 group, s16 member, s16 bank);
void HuSprGrpPosSet(s16 group, float x, float y);
void HuSprGrpCenterSet(s16 group, float x, float y);
void HuSprGrpZRotSet(s16 group, float z_rot);
void HuSprGrpScaleSet(s16 group, float x, float y);
void HuSprGrpTPLvlSet(s16 group, float tp_lvl);
void HuSprGrpDrawNoSet(s16 group, s32 draw_no);
void HuSprDrawNoSet(s16 group, s16 member, s32 draw_no);
void HuSprPriSet(s16 group, s16 member, s16 prio);
void HuSprGrpScissorSet(s16 group, s16 x, s16 y, s16 w, s16 h);
void HuSprScissorSet(s16 group, s16 member, s16 x, s16 y, s16 w, s16 h);
AnimData *HuSprAnimMake(s16 sizeX, s16 sizeY, s16 dataFmt);
void HuSprBGSet(s16 group, s16 member, AnimData *bg, s16 bg_bank);
void HuSprSprBGSet(s16 sprite, AnimData *bg, s16 bg_bank);
void AnimDebug(AnimData *anim);

void HuSprDispInit(void);
void HuSprDisp(HuSprite *sprite);
void HuSprTexLoad(AnimData *anim, s16 bmp, s16 slot, GXTexWrapMode wrap_s,
                  GXTexWrapMode wrap_t, GXTexFilter filter);
void HuSprExecLayerSet(s16 draw_no, s16 layer);

#define MEMORY_DEFAULT_NUM 0x10000000

typedef enum {
  HEAP_SYSTEM,
  HEAP_MUSIC,
  HEAP_DATA,
  HEAP_DVD,
  HEAP_MISC,
  HEAP_MAX
} HeapID;

void HuMemInitAll(void);
void *HuMemInit(void *ptr, s32 size);
void HuMemDCFlushAll();
void HuMemDCFlush(HeapID heap);
void *HuMemDirectMalloc(HeapID heap, s32 size);
void *HuMemDirectMallocNum(HeapID heap, s32 size, u32 num);
void HuMemDirectFree(void *ptr);
void HuMemDirectFreeNum(HeapID heap, u32 num);
s32 HuMemUsedMallocSizeGet(HeapID heap);
s32 HuMemUsedMallocBlockGet(HeapID heap);
u32 HuMemHeapSizeGet(HeapID heap);
void *HuMemHeapPtrGet(HeapID heap);

void *HuMemHeapInit(void *ptr, s32 size);
void *HuMemMemoryAlloc(void *heap_ptr, s32 size, u32 retaddr);
void *HuMemMemoryAllocNum(void *heap_ptr, s32 size, u32 num, u32 retaddr);
void HuMemMemoryFree(void *ptr, u32 retaddr);
void HuMemMemoryFreeNum(void *heap_ptr, u32 num, u32 retaddr);
s32 HuMemUsedMemorySizeGet(void *heap_ptr);
s32 HuMemUsedMemoryBlockGet(void *heap_ptr);
s32 HuMemMemorySizeGet(void *ptr);
s32 HuMemMemoryAllocSizeGet(s32 size);
void HuMemHeapDump(void *heap_ptr, s16 status);

#define DVD_MIN_TRANSFER_SIZE 32

#define DVD_STATE_FATAL_ERROR -1
#define DVD_STATE_END 0
#define DVD_STATE_BUSY 1
#define DVD_STATE_WAITING 2
#define DVD_STATE_COVER_CLOSED 3
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_MOTOR_STOPPED 7
#define DVD_STATE_PAUSING 8
#define DVD_STATE_IGNORED 9
#define DVD_STATE_CANCELED 10
#define DVD_STATE_RETRY 11

#define DVD_FILEINFO_READY 0
#define DVD_FILEINFO_BUSY 1

#define DVD_RESULT_GOOD 0
#define DVD_RESULT_FATAL_ERROR -1
#define DVD_RESULT_IGNORED -2
#define DVD_RESULT_CANCELED -3

#define DVD_AIS_SUCCESS 0x0

typedef struct DVDDiskID {
  char gameName[4];
  char company[2];
  u8 diskNumber;
  u8 gameVersion;
  u8 streaming;
  u8 streamingBufSize; // 0 = default
  u8 padding[22];      // 0's are stored
} DVDDiskID;

typedef struct DVDCommandBlock DVDCommandBlock;

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock *block);

struct DVDCommandBlock {
  DVDCommandBlock *next;
  DVDCommandBlock *prev;
  u32 command;
  s32 state;
  u32 offset;
  u32 length;
  void *addr;
  u32 currTransferSize;
  u32 transferredSize;
  DVDDiskID *id;
  DVDCBCallback callback;
  void *userData;
};

typedef struct DVDFileInfo DVDFileInfo;

typedef void (*DVDCallback)(s32 result, DVDFileInfo *fileInfo);

struct DVDFileInfo {
  DVDCommandBlock cb;
  u32 startAddr;
  u32 length;
  DVDCallback callback;
};

typedef struct {
  u32 entryNum;
  u32 location;
  u32 next;
} DVDDir;

typedef struct {
  u32 entryNum;
  BOOL isDir;
  char *name;
} DVDDirEntry;

void DVDInit();
BOOL DVDClose(DVDFileInfo *f);
BOOL DVDSetAutoFatalMessaging(BOOL);
void DVDReset();
s32 DVDCancel(DVDCommandBlock *block);
BOOL DVDOpen(char *fileName, DVDFileInfo *fileInfo);
BOOL DVDFastOpen(s32 entrynum, DVDFileInfo *fileInfo);
s32 DVDGetCommandBlockStatus(const DVDCommandBlock *block);
BOOL DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback callback);
s32 DVDCancel(DVDCommandBlock *block);
BOOL DVDCancelAllAsync(DVDCBCallback callback);
s32 DVDCancelAll(void);
BOOL DVDPrepareStreamAsync(DVDFileInfo *fInfo, u32 length, u32 offset,
                           DVDCallback callback);
s32 DVDPrepareStream(DVDFileInfo *fInfo, u32 length, u32 offset);

BOOL DVDCancelStreamAsync(DVDCommandBlock *block, DVDCBCallback callback);
s32 DVDCancelStream(DVDCommandBlock *block);

BOOL DVDStopStreamAtEndAsync(DVDCommandBlock *block, DVDCBCallback callback);
s32 DVDStopStreamAtEnd(DVDCommandBlock *block);

BOOL DVDGetStreamErrorStatusAsync(DVDCommandBlock *block,
                                  DVDCBCallback callback);
s32 DVDGetStreamErrorStatus(DVDCommandBlock *block);

BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock *block, DVDCBCallback callback);
s32 DVDGetStreamPlayAddr(DVDCommandBlock *block);

s32 DVDGetDriveStatus();

s32 DVDConvertPathToEntrynum(char *pathPtr);

BOOL DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio);

BOOL DVDReadPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset,
                 s32 prio);

#define DVDReadAsync(fileInfo, addr, length, offset, callback)                 \
  DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)
#define DVDRead(fileInfo, addr, length, offset)                                \
  DVDReadPrio((fileInfo), (addr), (length), (offset), 2)

#define DVDSeekAsync(fileInfo, offset, callback)                               \
  DVDSeekAsyncPrio((fileInfo), (offset), (callback), 2)

#define DATA_DECODE_NONE 0
#define DATA_DECODE_LZ 1
#define DATA_DECODE_SLIDE 2
#define DATA_DECODE_FSLIDE_ALT 3
#define DATA_DECODE_FSLIDE 4
#define DATA_DECODE_RLE 5

#define DATA_NUM_LISTEND -1

typedef struct data_read_stat {
  s32 dir_id;
  void *dir;
  void *file;
  u32 raw_len;
  u32 comp_type;
  BOOL used;
  s32 num;
  u32 status;
  DVDFileInfo file_info;
} DataReadStat;

void HuDataInit(void);
int HuDataReadChk(s32 data_num);
DataReadStat *HuDataGetStatus(void *dir_ptr);
void *HuDataGetDirPtr(s32 data_num);
DataReadStat *HuDataDirRead(s32 data_num);
DataReadStat *HuDataDirReadNum(s32 data_num, s32 num);
DataReadStat *HuDataDirSet(void *dir_ptr, s32 data_num);
void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo *fileInfo);
s32 HuDataDirReadAsync(s32 data_num);
s32 HuDataDirReadNumAsync(s32 data_num, s32 num);
BOOL HuDataGetAsyncStat(s32 status);
void *HuDataRead(s32 data_num);
void *HuDataReadNum(s32 data_num, s32 num);
void *HuDataSelHeapRead(s32 data_num, HeapID heap);
void *HuDataSelHeapReadNum(s32 data_num, s32 num, HeapID heap);
void **HuDataReadMulti(s32 *data_ids);
s32 HuDataGetSize(s32 data_num);
void HuDataClose(void *ptr);
void HuDataCloseMulti(void **ptrs);
void HuDataDirClose(s32 data_id);
void HuDataDirCloseNum(s32 num);
void *HuDataReadNumHeapShortForce(s32 data_id, s32 num, HeapID heap);

void HuDecodeData(void *src, void *dst, u32 size, int decode_type);

extern u32 DirDataSize;

typedef struct {
  /* 0x00 */ u8 color;
  /* 0x01 */ u8 fade;
  /* 0x02 */ s16 x;
  /* 0x04 */ s16 y;
  /* 0x06 */ s16 character;
} WinChar; // Size 8

typedef struct {
  /* 0x00 */ u8 stat;
  /* 0x02 */ s16 x;
  /* 0x04 */ s16 y;
} WinChoice; // Size 6

typedef struct {
  /* 0x000 */ u8 stat;
  /* 0x001 */ u8 active_pad;
  /* 0x002 */ u8 player_disable;
  /* 0x003 */ u8 color_key;
  /* 0x004 */ s16 group;
  /* 0x006 */ s16 sprite_id[30];
  /* 0x042 */ s16 speed;
  /* 0x044 */ s16 mess_time;
  /* 0x046 */ s16 advance_sprite;
  /* 0x048 */ s16 prio;
  /* 0x04C */ u32 attr;
  /* 0x050 */ AnimData *frame;
  /* 0x054 */ s16 mess_rect_x;
  /* 0x056 */ s16 mess_rect_w;
  /* 0x058 */ s16 mess_rect_y;
  /* 0x05A */ s16 mess_rect_h;
  /* 0x05C */ s16 mess_x;
  /* 0x05E */ s16 mess_y;
  /* 0x060 */ s16 mess_color;
  /* 0x062 */ s16 mess_shadow_color;
  /* 0x064 */ s16 spacing_x;
  /* 0x066 */ s16 spacing_y;
  /* 0x068 */ s16 w;
  /* 0x06A */ s16 h;
  /* 0x06C */ float pos_x;
  /* 0x070 */ float pos_y;
  /* 0x074 */ float scale_x;
  /* 0x078 */ float scale_y;
  /* 0x07C */ float z_rot;
  /* 0x080 */ s16 num_chars;
  /* 0x082 */ s16 max_chars;
  /* 0x084 */ WinChar *char_data;
  /* 0x088 */ s16 mess_stackptr;
  /* 0x08C */ s32 unk8C;
  /* 0x090 */ u8 *mess;
  /* 0x094 */ u8 *mess_stack[8];
  /* 0x0B4 */ u8 *insert_mess[8];
  /* 0x0D4 */ s16 num_choices;
  /* 0x0D6 */ s16 choice;
  /* 0x0D8 */ s16 cursor_sprite;
  /* 0x0DA */ u8 choice_disable[16];
  /* 0x0EA */ WinChoice choice_data[16];
  /* 0x14A */ s16 scissor_x;
  /* 0x14C */ s16 scissor_y;
  /* 0x14E */ s16 scissor_w;
  /* 0x150 */ s16 scissor_h;
  /* 0x152 */ s16 tab_w;
  /* 0x154 */ s16 push_key;
  /* 0x156 */ s16 key_down;
  /* 0x158 */ s16 key_auto;
  /* 0x160 */ u8 mess_pal[10][3];
} WindowData; // Size 0x180

extern WindowData winData[32];
extern void *messDataPtr;

void HuWindowInit(void);
void HuWinInit(s32 mess_data_no);
s16 HuWinCreate(float x, float y, s16 w, s16 h, s16 frame);
void HuWinKill(s16 window);
void HuWinAllKill(void);
void HuWinHomeClear(s16 window);
void HuWinKeyWaitEntry(s16 window);
u32 HuWinActivePadGet(WindowData *window);
u32 HuWinActiveKeyGetX(WindowData *window);
void HuWinPosSet(s16 window, float x, float y);
void HuWinScaleSet(s16 window, float x, float y);
void HuWinZRotSet(s16 window, float z_rot);
void HuWinCenterPosSet(s16 window, float x, float y);
void HuWinDrawNoSet(s16 window, s16 draw_no);
void HuWinScissorSet(s16 window, s16 x, s16 y, s16 w, s16 h);
void HuWinPriSet(s16 window, s16 prio);
void HuWinAttrSet(s16 window, u32 attr);
void HuWinAttrReset(s16 window, u32 attr);
s16 HuWinStatGet(s16 window);
void HuWinMesColSet(s16 window, u8 color);
void HuWinMesPalSet(s16 window, u8 index, u8 r, u8 g, u8 b);
void HuWinBGTPLvlSet(s16 window, float tp_level);
void HuWinBGColSet(s16 window, GXColor *bg_color);
void HuWinMesSpeedSet(s16 window, s16 speed);
void HuWinMesRead(s32 mess_data_no);
void HuWinMesSet(s16 window, u32 mess);
void HuWinInsertMesSet(s16 window, u32 mess, s16 index);
s16 HuWinChoiceGet(s16 window, s16 start_choice);
s16 HuWinChoiceNumGet(s16 window);
void HuWinChoiceDisable(s16 window, s16 choice);
s16 HuWinChoiceNowGet(s16 window);
void HuWinMesWait(s16 window);
s16 HuWinAnimSet(s16 window, AnimData *anim, s16 bank, float x, float y);
s16 HuWinSprSet(s16 window, s16 sprite, float x, float y);
void HuWinSprPosSet(s16 window, s16 index, float x, float y);
void HuWinSprPriSet(s16 window, s16 index, s16 prio);
s16 HuWinSprIDGet(s16 window, s16 index);
void HuWinSprKill(s16 window, s16 index);
void HuWinDispOff(s16 window);
void HuWinDispOn(s16 window);
void HuWinComKeyWait(s32 player_1, s32 player_2, s32 player_3, s32 player_4,
                     s16 delay);
void HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4);
void _HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4,
                     s16 delay);
void HuWinComKeyGet(s16 window, u32 *data);
void HuWinComKeyReset(void);
void HuWinMesMaxSizeGet(s16 mess_num, float *size, ...);
void HuWinInsertMesSizeGet(u32 mess, s16 index);
void HuWinMesSizeCancelCRSet(s32 cancel_cr);
void HuWinMesMaxSizeBetGet(float *size, u32 start, u32 end);
s16 HuWinKeyWaitNumGet(u32 mess);
void HuWinPushKeySet(s16 window, s16 push_key);
void HuWinDisablePlayerSet(s16 window, u8 player);
void HuWinDisablePlayerReset(s16 window, u8 player);
s16 HuWinExCreate(float x, float y, s16 w, s16 h, s16 portrait);
s16 HuWinExCreateStyled(float x, float y, s16 w, s16 h, s16 portrait,
                        s16 frame);
void HuWinExAnimIn(s16 window);
void HuWinExAnimOut(s16 window);
void HuWinExCleanup(s16 window);
void HuWinExAnimPopIn(s16 window, s16 portrait);
void *MessData_MesPtrGet(void *data, u32 index);

extern void *messDataPtr;

typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_obj_data {
  /* 0x00 */ u16 stat;
  /* 0x02 */ s16 next_idx_alloc;
  /* 0x04 */ s16 prio;
  /* 0x06 */ s16 prev;
  /* 0x08 */ s16 next;
  /* 0x0A */ s16 next_idx;
  /* 0x0C */ s16 group;
  /* 0x0E */ u16 group_idx;
  /* 0x10 */ u32 unk10;
  /* 0x14 */ omObjFunc func;
  /* 0x18 */ Vec trans;
  /* 0x24 */ Vec rot;
  /* 0x30 */ Vec scale;
  /* 0x3C */ u16 mdlcnt;
  /* 0x40 */ s16 *model;
  /* 0x44 */ u16 mtncnt;
  /* 0x48 */ s16 *motion;
  /* 0x4C */ u32 work[4];
  /* 0x5C */ void *data;
} omObjData;


typedef struct hu_snd_grp_data {
    /* 0x00 */ s16 ovl;
    /* 0x02 */ s16 grpset;
    /* 0x04 */ s32 auxANo;
    /* 0x08 */ s32 auxBNo;
    /* 0x0C */ s8 auxAVol;
    /* 0x0D */ s8 auxBVol;
} HuSndGrpData;

void HuAudInit(void);
s32 HuAudStreamPlay(void);
void HuAudStreamVolSet(s16 vol);
void HuAudStreamPauseOn(void);
void HuAudStreamPauseOff(void);
void HuAudStreamFadeOut(void);
void HuAudAllStop(void);
void HuAudFadeOut(s32 arg0);
s32 HuAudFXPlay(s32 arg0);
s32 HuAudFXPlayVol(s32 arg0, s16 arg1);
s32 HuAudFXPlayVolPan(s32 arg0, s16 arg1, s16 arg2);
void HuAudFXStop(s32 arg0);
void HuAudFXAllStop(void);
void HuAudFXFadeOut(s32 arg0, s32 arg1);
void HuAudFXPanning(s32 arg0, s16 arg1);
void HuAudFXListnerSet(Vec* arg0, Vec* arg1, float arg2, float arg3);
void HuAudFXListnerSetEX(Vec* arg0, Vec* arg1, float sndDist, float sndSpeed, float arg4, float arg5, float arg6);
void HuAudFXListnerUpdate(Vec *arg0, Vec *arg1);
s32 HuAudFXEmiterPlay(s32 arg0, Vec *arg1);
void HuAudFXEmiterUpDate(s32 arg0, Vec *arg1);
void HuAudFXListnerKill(void);
void HuAudFXPauseAll(s32 arg0);
s32 HuAudFXStatusGet(s32 arg0);
s32 HuAudFXPitchSet(s32 arg0, s16 arg1);
s32 HuAudFXVolSet(s32 arg0, s16 arg1);
s32 HuAudSeqPlay(s16 arg0);
void HuAudSeqStop(s32 arg0);
void HuAudSeqFadeOut(s32 arg0, s32 arg1);
void HuAudSeqAllFadeOut(s32 arg0);
void HuAudSeqAllStop(void);
void HuAudSeqPauseAll(s32 arg0);
void HuAudSeqPause(s32 arg0, s32 arg1, s32 arg2);
s32 HuAudSeqMidiCtrlGet(s32 arg0, s8 arg1, s8 arg2);
s32 HuAudSStreamPlay(s16 arg0);
void HuAudSStreamStop(s32 arg0);
void HuAudSStreamFadeOut(s32 arg0, s32 arg1);
void HuAudSStreamAllFadeOut(s32 arg0);
void HuAudSStreamAllStop(void);
s32 HuAudSStreamStatGet(s32 arg0);
void HuAudDllSndGrpSet(u16 ovl);
void HuAudSndGrpSetSet(s16 arg0);
void HuAudSndGrpSet(s16 arg0);
void HuAudSndCommonGrpSet(s16 arg0, s32 arg1);
void HuAudAUXSet(s32 arg0, s32 arg1);
void HuAudAUXVolSet(s8 arg0, s8 arg1);
void HuAudVoiceInit(s16 ovl);
s32 HuAudPlayerVoicePlay(s16 arg0, s16 arg1);
s32 HuAudPlayerVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2);
void HuAudPlayerVoicePlayEntry(s16 arg0, s16 arg1);
s32 HuAudCharVoicePlay(s16 arg0, s16 arg1);
s32 HuAudCharVoicePlayPos(s16 arg0, s16 arg1, Vec *arg2);
void HuAudCharVoicePlayEntry(s16 arg0, s16 arg1);

extern float Snd3DBackSurDisOffset;
extern float Snd3DFrontSurDisOffset;
extern float Snd3DStartDisOffset;
extern float Snd3DSpeedOffset;
extern float Snd3DDistOffset;
extern s32 musicOffF;
extern u8 fadeStat;

extern HuSndGrpData HuSndGrpTbl[];

void GWInit(void);
void GWGameStatReset(void);
s32 GWMessSpeedGet(void);
s32 GWMessDelayGet(void);
void GWMGRecordSet(int index, s32 value);
s32 GWMGRecordGet(int index);
void GWCharColorGet(int character, GXColor *color);
void GWBoardPlayCountSet(int board, u8 value);
void GWBoardPlayCountAdd(int board, u8 value);
u8 GWBoardPlayCountGet(int board);
void GWBoardMaxStarsSet(int board, int value);
u16 GWBoardMaxStarsGet(int board);
void GWBoardMaxCoinsSet(int board, int value);
u16 GWBoardMaxCoinsGet(int board);
int GWBoardWinCountInc(int character, int board);
int GWBoardWinCountGet(int character, int board);
void GWBoardWinCountSet(int character, int board, int value);
int GWMGAvailGet(int id);
int GWMGAvailSet(int id);
int GWMGCustomGet(int id);
int GWMGCustomSet(int id);
int GWMGCustomReset(int id);
s16 GWCoinsGet(int player);
void GWCoinsSet(int player, s16 value);
void GWCoinsAdd(int player, s16 amount);
void GWStarsSet(int player, s16 value);
void GWStarsAdd(int player, s16 amount);
s32 GWStarsGet(int player);
void GWTotalStarsSet(s16 value);
void GWTotalStarsAdd(s16 amount);
u16 GWTotalStarsGet(void);
