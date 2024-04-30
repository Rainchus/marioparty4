#define ATTRIBUTE_ALIGN(num) __attribute__((aligned(num)))
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

#define CTR     9
#define XER     1
#define LR      8

#define UPMC1   937
#define UPMC2   938
#define UPMC3   941
#define UPMC4   942

#define USIA    939

#define UMMCR0  936
#define UMMCR1  940

#define HID0    1008
#define HID1    1009

#define PVR     287

#define IBAT0U  528
#define IBAT0L  529
#define IBAT1U  530
#define IBAT1L  531
#define IBAT2U  532
#define IBAT2L  533
#define IBAT3U  534
#define IBAT3L  535

#define DBAT0U  536
#define DBAT0L  537
#define DBAT1U  538
#define DBAT1L  539
#define DBAT2U  540
#define DBAT2L  541
#define DBAT3U  542
#define DBAT3L  543

#define SDR1    25

#define SPRG0   272
#define SPRG1   273
#define SPRG2   274
#define SPRG3   275

#define DAR     19
#define DSISR   18

#define SRR0    26
#define SRR1    27

#define EAR     282

#define DABR    1013

#define TBL     284
#define TBU     285

#define L2CR    1017

#define DEC     22

#define IABR    1010

#define PMC1    953
#define PMC2    954
#define PMC3    957
#define PMC4    958

#define SIA     955

#define MMCR0   952
#define MMCR1   956

#define THRM1   1020
#define THRM2   1021
#define THRM3   1022

#define ICTC    1019

#define GQR0    912
#define GQR1    913
#define GQR2    914
#define GQR3    915
#define GQR4    916
#define GQR5    917
#define GQR6    918
#define GQR7    919

#define HID2    920

#define WPAR    921

#define DMA_U   922
#define DMA_L   923

#define MSR_POW         0x00040000  // Power Management
#define MSR_ILE         0x00010000  // Interrupt Little Endian
#define MSR_EE          0x00008000  // external interrupt
#define MSR_PR          0x00004000  // privilege level(should be 0)
#define MSR_FP          0x00002000  // floating point available
#define MSR_ME          0x00001000  // machine check enable
#define MSR_FE0         0x00000800  // floating point exception enable
#define MSR_SE          0x00000400  // single step trace enable
#define MSR_BE          0x00000200  // branch trace enable
#define MSR_FE1         0x00000100  // floating point exception enable
#define MSR_IP          0x00000040  // Exception prefix
#define MSR_IR          0x00000020  // instruction relocate
#define MSR_DR          0x00000010  // data relocate
#define MSR_PM          0x00000004  // Performance monitor marked mode
#define MSR_RI          0x00000002  // Recoverable interrupt
#define MSR_LE          0x00000001  // Little Endian

#define MSR_POW_BIT     13          // Power Management
#define MSR_ILE_BIT     15          // Interrupt Little Endian
#define MSR_EE_BIT      16          // external interrupt
#define MSR_PR_BIT      17          // privilege level (should be 0)
#define MSR_FP_BIT      18          // floating point available
#define MSR_ME_BIT      19          // machine check enable
#define MSR_FE0_BIT     20          // floating point exception enable
#define MSR_SE_BIT      21          // single step trace enable
#define MSR_BE_BIT      22          // branch trace enable
#define MSR_FE1_BIT     23          // floating point exception enable
#define MSR_IP_BIT      25          // Exception prefix
#define MSR_IR_BIT      26          // instruction relocate
#define MSR_DR_BIT      27          // data relocate
#define MSR_PM_BIT      29          // Performance monitor marked mode
#define MSR_RI_BIT      30          // Recoverable interrupt
#define MSR_LE_BIT      31          // Little Endian

/*---------------------------------------------------------------------------*
    HID0 bits
 *---------------------------------------------------------------------------*/
#define HID0_EMCP       0x80000000  // Enable MCP
#define HID0_DBP        0x40000000  // Enable 60x bus address and data parity chk
#define HID0_EBA        0x20000000  // Enable 60x address parity checking
#define HID0_EBD        0x10000000  // Enable 60x data parity checking
#define HID0_BCLK       0x08000000  // CLK_OUT output enable and clk selection
#define HID0_ECLK       0x02000000  // CLK_OUT output enable and clk selection
#define HID0_PAR        0x01000000  // Disable !ARTRY precharge
#define HID0_DOZE       0x00800000  // Doze mode enable
#define HID0_NAP        0x00400000  // Nap mode enable
#define HID0_SLEEP      0x00200000  // Sleep mode enable
#define HID0_DPM        0x00100000  // Dynamic power management enable
#define HID0_NHR        0x00010000  // Not hard reset (0 hard reset if s/w set it)
#define HID0_ICE        0x00008000  // Instruction cache enable
#define HID0_DCE        0x00004000  // Data cache enable
#define HID0_ILOCK      0x00002000  // ICache lock
#define HID0_DLOCK      0x00001000  // DCache lock
#define HID0_ICFI       0x00000800  // ICache flash invalidate
#define HID0_DCFI       0x00000400  // DCache flash invalidate
#define HID0_SPD        0x00000200  // Speculative cache access enable (0 enable)
#define HID0_IFEM       0x00000100  // Enable M bit on bus for Ifetch
#define HID0_SGE        0x00000080  // Store gathering enable
#define HID0_DCFA       0x00000040  // DCache flush assist - set before a flush
#define HID0_BTIC       0x00000020  // Branch target icache enable
#define HID0_ABE        0x00000008  // Address bcast enable
#define HID0_BHT        0x00000004  // Branch history table enable
#define HID0_NOOPTI     0x00000001  // No-op Dcache touch instructions

#define HID0_ICE_BIT    16          // Instruction cache enable
#define HID0_DCE_BIT    17          // Data cache enable
#define HID0_ILOCK_BIT  18          // ICache lock
#define HID0_DLOCK_BIT  19          // DCache lock

#define HID2_LSQE           0x80000000  // L/S quantize enable
#define HID2_WPE            0x40000000  // Write pipe enable
#define HID2_PSE            0x20000000  // Paired single enable
#define HID2_LCE            0x10000000  // Locked cache enable

#define HID2_DCHERR         0x00800000  // ERROR: dcbz_l cache hit
#define HID2_DNCERR         0x00400000  // ERROR: DMA access to normal cache
#define HID2_DCMERR         0x00200000  // ERROR: DMA cache miss error
#define HID2_DQOERR         0x00100000  // ERROR: DMA queue overflow
#define HID2_DCHEE          0x00080000  // dcbz_l cache hit error enable
#define HID2_DNCEE          0x00040000  // DMA access to normal cache error enable
#define HID2_DCMEE          0x00020000  // DMA cache miss error error enable
#define HID2_DQOEE          0x00010000  // DMA queue overflow error enable

#define HID2_DMAQL_MASK     0x0F000000  // DMA queue length mask
#define HID2_DMAQL_SHIFT    24          // DMA queue shift

#define HID2_LSQE_BIT       0
#define HID2_WPE_BIT        1
#define HID2_PSE_BIT        2
#define HID2_LCE_BIT        3

#define HID2_DCHERR_BIT     8
#define HID2_DNCERR_BIT     9
#define HID2_DCMERR_BIT     10
#define HID2_DQOERR_BIT     11
#define HID2_DCHEE_BIT      12
#define HID2_DNCEE_BIT      13
#define HID2_DCMEE_BIT      14
#define HID2_DQOEE_BIT      15

#define GQR_LOAD_SCALE_MASK         0x3F000000  // load scale field
#define GQR_LOAD_TYPE_MASK          0x00070000  // load type field
#define GQR_STORE_SCALE_MASK        0x00003F00  // store scale field
#define GQR_STORE_TYPE_MASK         0x00000007  // store type field

typedef struct
{
    u32 _pad0       :2;
    u32 loadScale   :6;
    u32 _pad1       :5;
    u32 loadType    :3;
    u32 _pad2       :2;
    u32 storeScale  :6;
    u32 _pad3       :5;
    u32 storeType   :3;
} PPC_GQR_t;

typedef union
{
    u32         val;
    PPC_GQR_t   f;
} PPC_GQR_u;


#define DMA_U_ADDR_MASK             0xFFFFFFE0  // Start addr in memory
#define DMA_U_LEN_U_MASK            0x0000001F  // lines to transfer (U)

#define DMA_L_LC_ADDR_MASK          0xFFFFFFE0  // Start addr in LC
#define DMA_L_LOAD                  0x00000010  // 0 - store, 1 - load
#define DMA_L_STORE                 0x00000000  // 0 - store, 1 - load
#define DMA_L_LEN_MASK              0x0000000C  // lines to transfer (L)
#define DMA_L_TRIGGER               0x00000002  // 0 - cmd inactive, 1 - cmd rdy
#define DMA_L_FLUSH                 0x00000001  // 1 - Flush DMA queue

typedef struct
{
    u32 memAddr     :27;
    u32 dmaLenU     :5;
} PPC_DMA_U_t;

typedef union
{
    u32             val;
    PPC_DMA_U_t     f;
} PPC_DMA_U_u;


typedef struct
{
    u32 lcAddr      :27;
    u32 dmaLd       :1;
    u32 dmaLenL     :2;
    u32 dmaTrigger  :1;
    u32 dmaFlush    :1;
} PPC_DMA_L_t;


typedef union
{
    u32             val;
    PPC_DMA_L_t     f;
} PPC_DMA_L_u;


#define WPAR_ADDR                   0xFFFFFFE0  // 32byte gather address
#define WPAR_BNE                    0x00000001  // Buffer not empty (R)

#define SRR1_DMA_BIT                0x00200000
#define SRR1_L2DP_BIT               0x00100000

#define L2CR_L2E                    0x80000000  // L2 Enable
#define L2CR_L2PE                   0x40000000  // L2 data parity generation and checking enable

#define L2CR_L2SIZ_256K             0x10000000  // L2 size 256K
#define L2CR_L2SIZ_512K             0x20000000  // L2 size 512
#define L2CR_L2SIZ_1M               0x30000000  // L2 size 1M

#define L2CR_L2CLK_1_0              0x02000000  // L2 clock ratio 1
#define L2CR_L2CLK_1_5              0x04000000  // L2 clock ratio 1.5
#define L2CR_L2CLK_2_0              0x08000000  // L2 clock ratio 2
#define L2CR_L2CLK_2_5              0x0A000000  // L2 clock ratio 2.5
#define L2CR_L2CLK_3_0              0x0C000000  // L2 clock ratio 3

#define L2CR_RAM_FLOW_THRU_BURST    0x00000000  // L2 RAM type flow-through sync. burst SRAM
#define L2CR_RAM_PIPELINE_BURST     0x01000000  // L2 RAM type pipelined sync. burst SRAM
#define L2CR_RAM_PIPELINE_LATE      0x01800000  // L2 RAM type pipelined sync. late-write SRAM

#define L2CR_L2DO                   0x00400000  // Data only
#define L2CR_L2I                    0x00200000  // Global invalidate
#define L2CR_L2CTL                  0x00100000  // ZZ enable
#define L2CR_L2WT                   0x00080000  // L2 write through
#define L2CR_L2TS                   0x00040000  // L2 test support

#define L2CR_L2OH_0_5               0x00000000  // L2 output hold 0.5 ns
#define L2CR_L2OH_1_0               0x00010000  // L2 output hold 1.0 ns

#define L2CR_L2SL                   0x00008000  // L2 DLL slow
#define L2CR_L2DF                   0x00004000  // L2 differential clock
#define L2CR_L2BYP                  0x00002000  // L2 DLL bypass
#define L2CR_L2CS                   0x00000200  // L2 clock stop
#define L2CR_L2DRO                  0x00000100  // L2 DLL rollover checkstop enable
#define L2CR_L2CTR_MASK             0x000000FE  // L2 counter value mask
#define L2CR_L2IP                   0x00000001  // L2 global invalidate in progress

#define MMCR0_DIS                   0x80000000  // Disables counting unconditionally
#define MMCR0_DP                    0x40000000  // Disables counting while in supervisor mode
#define MMCR0_DU                    0x20000000  // Disables counting while in user mode
#define MMCR0_DMS                   0x10000000  // Disables counting while MSR[PM] is set
#define MMCR0_DMR                   0x08000000  // Disables counting while MSR[PM] is zero
#define MMCR0_ENINT                 0x04000000  // Enables performance monitor interrupt signaling
#define MMCR0_DISCOUNT              0x02000000  // Disables counting of PMCn when a performance monitor interrupt is signaled or...
#define MMCR0_RTCSELECT_MASK        0x01800000  // 64-bit time base, bit selection enable
#define MMCR0_RTCSELECT_63          0x00000000  // Pick bit 63 to count
#define MMCR0_RTCSELECT_55          0x00800000  // Pick bit 55 to count
#define MMCR0_RTCSELECT_51          0x01000000  // Pick bit 51 to count
#define MMCR0_RTCSELECT_47          0x01800000  // Pick bit 47 to count
#define MMCR0_INTONBITTRANS         0x00400000  // Causes interrupt signaling on bit transition from off to on
#define MMCR0_THRESHOLD_MASK        0x003F0000  // Threshold value
#define MMCR0_THRESHOLD(n)          ((n) << 16) // Threshold value (0 - 63)
#define MMCR0_PMC1INTCONTROL        0x00008000  // Enables interrupt signaling due to PMC1 counter overflow
#define MMCR0_PMC2INTCONTROL        0x00004000  // Enables interrupt signaling due to PMC2-PMC4 counter overflow
#define MMCR0_PMCTRIGGER            0x00002000  // Can be used to trigger counting of PMC2-PMC4 after PMC1 has overflowed or...
#define MMCR0_PMC1SELECT_MASK       0x00001FC0  // PMC1 input selector
#define MMCR0_PMC2SELECT_MASK       0x0000003F  // PMC2 input selector

#define MMCR1_PMC3SELECT_MASK       0xF8000000  // PMC3 input selector
#define MMCR1_PMC4SELECT_MASK       0x07C00000  // PMC4 input selector

#define PMC1_OV                     0x80000000  // Overflow
#define PMC1_COUNTER                0x7FFFFFFF  // Counter value
#define PMC2_OV                     0x80000000  // Overflow
#define PMC2_COUNTER                0x7FFFFFFF  // Counter value
#define PMC3_OV                     0x80000000  // Overflow
#define PMC3_COUNTER                0x7FFFFFFF  // Counter value
#define PMC4_OV                     0x80000000  // Overflow
#define PMC4_COUNTER                0x7FFFFFFF  // Counter value

/*---------------------------------------------------------------------------*
    PMC1 Events
 *---------------------------------------------------------------------------*/
#define MMCR0_PMC1_HOLD             0x00000000  // Register holds current value
#define MMCR0_PMC1_CYCLE            0x00000040  // Processor cycles
#define MMCR0_PMC1_INSTRUCTION      0x00000080  // # of instructions completed.
#define MMCR0_PMC1_TRANSITION       0x000000C0  // # of transitions for 0 to 1
#define MMCR0_PMC1_DISPATCHED       0x00000100  // # of instructions dispatched
#define MMCR0_PMC1_EIEIO            0x00000140  // # of eieio instructions completed
#define MMCR0_PMC1_ITLB_CYCLE       0x00000180  // # of cycles spent performing table search op. for the ITLB
#define MMCR0_PMC1_L2_HIT           0x000001C0  // # of access that hit the L2.
#define MMCR0_PMC1_EA               0x00000200  // # of valid instruction EAs delivered to the memory subsystem
#define MMCR0_PMC1_IABR             0x00000240  // # of time the address of an instruction matches the IABR
#define MMCR0_PMC1_L1_MISS          0x00000280  // # of loads that miss the L1
#define MMCR0_PMC1_Bx_UNRESOLVED    0x000002C0  // # of branches that are unresolved when processed
#define MMCR0_PMC1_Bx_STALL_CYCLE   0x00000300  // # of cycles that dispatcher stalls due to a second
                                                //      unresolved branch in the instruction stream
#define MMCR0_PMC1_IC_FETCH_MISS    0x00000340  // # of times an instruction fetch missed the L1 Icache
#define MMCR0_PMC2_HOLD             0x00000000  // Register holds current value
#define MMCR0_PMC2_CYCLE            0x00000001  // Processor cycles
#define MMCR0_PMC2_INSTRUCTION      0x00000002  // # of instructions completed
#define MMCR0_PMC2_TRANSITION       0x00000003  // # of time-base (lower) bit transitions
#define MMCR0_PMC2_DISPATCHED       0x00000004  // # of instructions dispatched
#define MMCR0_PMC2_IC_MISS          0x00000005  // # of L1 instruction cache misses
#define MMCR0_PMC2_ITLB_MISS        0x00000006  // # of ITLB misses
#define MMCR0_PMC2_L2_I_MISS        0x00000007  // # of L2 instruction misses
#define MMCR0_PMC2_Bx_FALL_TROUGH   0x00000008  // # of fall-through branches
#define MMCR0_PMC2_PR_SWITCH        0x00000009  // # of MSR[PR] bit toggles
#define MMCR0_PMC2_RESERVED_LOAD    0x0000000A  // # of reserved loads completed
#define MMCR0_PMC2_LOAD_STORE       0x0000000B  // # of completed loads and stores
#define MMCR0_PMC2_SNOOP            0x0000000C  // # of snoops
#define MMCR0_PMC2_L1_CASTOUT       0x0000000D  // # of L1 castouts to L2
#define MMCR0_PMC2_SYSTEM           0x0000000E  // # of completed system unit instructions
#define MMCR0_PMC2_IC_FETCH_MISS    0x0000000F  // # of instruction fetch misses in the L1
#define MMCR0_PMC2_Bx_OUT_OF_ORDER  0x00000010  // # of branches allowing out-of-order execution

/*---------------------------------------------------------------------------*
    PMC3 Events
 *---------------------------------------------------------------------------*/
#define MMCR1_PMC3_HOLD             0x00000000  // Register holds current value
#define MMCR1_PMC3_CYCLE            0x08000000  // Processor cycles
#define MMCR1_PMC3_INSTRUCTION      0x10000000  // # of instructions completed
#define MMCR1_PMC3_TRANSITION       0x18000000  // # of time-base (lower) bit transitions
#define MMCR1_PMC3_DISPATCHED       0x20000000  // # of instructions dispatched
#define MMCR1_PMC3_DC_MISS          0x28000000  // # of L1 data cache misses
#define MMCR1_PMC3_DTLB_MISS        0x30000000  // # of DTLB misses
#define MMCR1_PMC3_L2_D_MISS        0x38000000  // # of L2 data misses
#define MMCR1_PMC3_Bx_TAKEN         0x40000000  // # predicted branches that were taken
#define MMCR1_PMC3_PM_SWITCH        0x48000000  // # of transitions between marked and unmarked processes
#define MMCR1_PMC3_COND_STORE       0x50000000  // # of store conditional instructions completed
#define MMCR1_PMC3_FPU              0x58000000  // # of instructions completed from the FPU
#define MMCR1_PMC3_L2_SNOOP_CASTOUT 0x60000000  // # of L2 castout caused by snoops to modified lines
#define MMCR1_PMC3_L2_HIT           0x68000000  // # of cache operations that hit in the L2 cache
#define MMCR1_PMC3_L1_MISS_CYCLE    0x78000000  // # of cycles generated by L1 load misses
#define MMCR1_PMC3_Bx_SECOND        0x80000000  // # of branches in the second speculative branch
                                                //   resolved correctly
#define MMCR1_PMC3_BPU_LR_CR        0x88000000  // # of cycles the BPU stalls due to LR or CR unresolved
                                                //   dependencies

#define MMCR1_PMC4_HOLD             0x00000000  // Register holds current value
#define MMCR1_PMC4_CYCLE            0x00400000  // Processor cycles
#define MMCR1_PMC4_INSTRUCTION      0x00800000  // # of instructions completed
#define MMCR1_PMC4_TRANSITION       0x00C00000  // # of time-base (lower) bit transitions
#define MMCR1_PMC4_DISPATCHED       0x01000000  // # of instructions dispatched
#define MMCR1_PMC4_L2_CASTOUT       0x01400000  // # of L2 castouts
#define MMCR1_PMC4_DTLB_CYCLE       0x01800000  // # of cycles spent performing table searches for DTLB accesses
#define MMCR1_PMC4_Bx_MISSED        0x02000000  // # of mispredicted branches
#define MMCR1_PMC4_COND_STORE_INT   0x02800000  // # of store conditional instructions completed
                                                //   with reservation intact
#define MMCR1_PMC4_SYNC             0x02C00000  // # of completed sync instructions
#define MMCR1_PMC4_SNOOP_RETRY      0x03000000  // # of snoop request retries
#define MMCR1_PMC4_INTEGER          0x03400000  // # of completed integer operations
#define MMCR1_PMC4_BPU_THIRD        0x03800000  // # of cycles the BPU cannot process new branches
                                                //   due to having two unresolved branches
#define MMCR1_PMC4_DC_MISS          0x07C00000  // # of L1 data cache misses

/*---------------------------------------------------------------------------*
    FPSCR bits
 *---------------------------------------------------------------------------*/
#define FPSCR_FX            0x80000000  // Exception summary
#define FPSCR_FEX           0x40000000  // Enabled exception summary
#define FPSCR_VX            0x20000000  // Invalid operation
#define FPSCR_OX            0x10000000  // Overflow exception
#define FPSCR_UX            0x08000000  // Underflow exception
#define FPSCR_ZX            0x04000000  // Zero divide exception
#define FPSCR_XX            0x02000000  // Inexact exception
#define FPSCR_VXSNAN        0x01000000  // SNaN
#define FPSCR_VXISI         0x00800000  // Infinity - Infinity
#define FPSCR_VXIDI         0x00400000  // Infinity / Infinity
#define FPSCR_VXZDZ         0x00200000  // 0 / 0
#define FPSCR_VXIMZ         0x00100000  // Infinity * 0
#define FPSCR_VXVC          0x00080000  // Invalid compare
#define FPSCR_FR            0x00040000  // Fraction rounded
#define FPSCR_FI            0x00020000  // Fraction inexact
#define FPSCR_VXSOFT        0x00000400  // Software request
#define FPSCR_VXSQRT        0x00000200  // Invalid square root
#define FPSCR_VXCVI         0x00000100  // Invalid integer convert
#define FPSCR_VE            0x00000080  // Invalid operation exception enable
#define FPSCR_OE            0x00000040  // Overflow exception enable
#define FPSCR_UE            0x00000020  // Underflow exception enable
#define FPSCR_ZE            0x00000010  // Zero divide exception enable
#define FPSCR_XE            0x00000008  // Inexact exception enable
#define FPSCR_NI            0x00000004  // Non-IEEE mode

#define FPSCR_FX_BIT        0           // Exception summary
#define FPSCR_FEX_BIT       1           // Enabled exception summary
#define FPSCR_VX_BIT        2           // Invalid operation
#define FPSCR_OX_BIT        3           // Overflow exception
#define FPSCR_UX_BIT        4           // Underflow exception
#define FPSCR_ZX_BIT        5           // Zero divide exception
#define FPSCR_XX_BIT        6           // Inexact exception
#define FPSCR_VXSNAN_BIT    7           // SNaN
#define FPSCR_VXISI_BIT     8           // Infinity - Infinity
#define FPSCR_VXIDI_BIT     9           // Infinity / Infinity
#define FPSCR_VXZDZ_BIT     10          // 0 / 0
#define FPSCR_VXIMZ_BIT     11          // Infinity * 0
#define FPSCR_VXVC_BIT      12          // Invalid compare
#define FPSCR_FR_BIT        13          // Fraction rounded
#define FPSCR_FI_BIT        14          // Fraction inexact
#define FPSCR_VXSOFT_BIT    21          // Software request
#define FPSCR_VXSQRT_BIT    22          // Invalid square root
#define FPSCR_VXCVI_BIT     23          // Invalid integer convert
#define FPSCR_VE_BIT        24          // Invalid operation exception enable
#define FPSCR_OE_BIT        25          // Overflow exception enable
#define FPSCR_UE_BIT        26          // Underflow exception enable
#define FPSCR_ZE_BIT        27          // Zero divide exception enable
#define FPSCR_XE_BIT        28          // Inexact exception enable
#define FPSCR_NI_BIT        29          // Non-IEEE mode

u32 PPCMfmsr();
void PPCMtmsr(u32 newMSR);
u32 PPCOrMsr(u32 value);
u32 PPCMfhid0();
void PPCMthid0(u32 newHID0);
u32 PPCMfl2cr();
void PPCMtl2cr(u32 newL2cr);
void PPCMtdec(u32 newDec);
void PPCSync();
void PPCHalt();
u32 PPCMffpscr();
void PPCMtfpscr(u32 newFPSCR);
u32 PPCMfhid2();
void PPCMthid2(u32 newhid2);
u32 PPCMfwpar();
void PPCMtwpar(u32 newwpar);
void PPCEnableSpeculation();
void PPCDisableSpeculation();
void PPCSetFpIEEEMode();
void PPCSetFpNonIEEEMode();

/* "include\dolphin\db.h" line 3 "types.h" */
/* end "types.h" */

#define OS_DBINTERFACE_ADDR 0x00000040

typedef struct DBInterface
{
    u32     bPresent;
    u32     exceptionMask;
    void    (*ExceptionDestination) ( void );
    void    *exceptionReturn;
} DBInterface;

extern DBInterface* __DBInterface;

void DBInit(void);
void DBInitComm(int* inputFlagPtr, int* mtrCallback);
static void __DBExceptionDestination(void);
void DBPrintf(char* format, ...);

typedef u8 GXBool;

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

#define _GX_TF_CTF 32
#define _GX_TF_ZTF 16

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

  GX_CTF_Z4 = 0x0  ,
  GX_CTF_Z8M = 0x9  ,
  GX_CTF_Z8L = 0xA  ,
  GX_CTF_Z16L = 0xC  ,

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

#define VI_INTERLACE 0
#define VI_NON_INTERLACE 1
#define VI_PROGRESSIVE 2
#define VI_3D 3

#define VI_NTSC 0
#define VI_PAL 1
#define VI_MPAL 2
#define VI_DEBUG 3
#define VI_DEBUG_PAL 4
#define VI_EURGB60 5
#define VI_GCA 6

#define VI_TVMODE(format, interlace) (((format) << 2) + (interlace))

typedef enum {
  // NTSC
  VI_TVMODE_NTSC_INT = VI_TVMODE(VI_NTSC, VI_INTERLACE),
  VI_TVMODE_NTSC_DS = VI_TVMODE(VI_NTSC, VI_NON_INTERLACE),
  VI_TVMODE_NTSC_PROG = VI_TVMODE(VI_NTSC, VI_PROGRESSIVE),
  VI_TVMODE_NTSC_3D = VI_TVMODE(VI_NTSC, VI_3D),
  // PAL
  VI_TVMODE_PAL_INT = VI_TVMODE(VI_PAL, VI_INTERLACE),
  VI_TVMODE_PAL_DS = VI_TVMODE(VI_PAL, VI_NON_INTERLACE),

  // MPAL
  VI_TVMODE_MPAL_INT = VI_TVMODE(VI_MPAL, VI_INTERLACE),
  VI_TVMODE_MPAL_DS = VI_TVMODE(VI_MPAL, VI_NON_INTERLACE),

  // Debug
  VI_TVMODE_DEBUG_INT = VI_TVMODE(VI_DEBUG, VI_INTERLACE),

  // Debug PAL
  VI_TVMODE_DEBUG_PAL_INT = VI_TVMODE(VI_DEBUG_PAL, VI_INTERLACE),
  VI_TVMODE_DEBUG_PAL_DS = VI_TVMODE(VI_DEBUG_PAL, VI_NON_INTERLACE),

  // EU RGB60
  VI_TVMODE_EURGB60_INT = VI_TVMODE(VI_EURGB60, VI_INTERLACE),
  VI_TVMODE_EURGB60_DS = VI_TVMODE(VI_EURGB60, VI_NON_INTERLACE),

  // GCA
  VI_TVMODE_GCA_INT = VI_TVMODE(VI_GCA, VI_INTERLACE),
  VI_TVMODE_GCA_DS = VI_TVMODE(VI_GCA, VI_NON_INTERLACE),
  VI_TVMODE_GCA_PROG = VI_TVMODE(VI_GCA, VI_PROGRESSIVE),
} VITVMode;

typedef enum {
  VI_XFBMODE_SF = 0,
  VI_XFBMODE_DF = 1,
} VIXFBMode;

typedef void (*VIPositionCallback)(s16 x, s16 y);
typedef void (*VIRetraceCallback)(u32 retraceCount);

// Structure to use with timing in vi.c (size 0x28).
typedef struct VITimingInfo {
  u8 equ;           // _00
  u16 acv;          // _02
  u16 prbOdd;       // _04
  u16 prbEven;      // _06
  u16 psbOdd;       // _08
  u16 psbEven;      // _0A
  u8 bs1;           // _0C
  u8 bs2;           // _0D
  u8 bs3;           // _0E
  u8 bs4;           // _0F
  u16 be1;          // _10
  u16 be2;          // _12
  u16 be3;          // _14
  u16 be4;          // _16
  u16 numHalfLines; // _18
  u16 hlw;          // _1A
  u8 hsy;           // _1C
  u8 hcs;           // _1D
  u8 hce;           // _1E
  u8 hbe640;        // _1F
  u16 hbs640;       // _20
  u8 hbeCCIR656;    // _24
  u16 hbsCCIR656;   // _26
} VITimingInfo;

// Structure to use with HorVer in vi.c (size 0x58).
typedef struct VIPositionInfo {
  u16 dispPosX;         // _00
  u16 dispPosY;         // _02
  u16 dispSizeX;        // _04
  u16 dispSizeY;        // _06
  u16 adjDispPosX;      // _08
  u16 adjDispPosY;      // _0A
  u16 adjDispSizeY;     // _0C
  u16 adjPanPosY;       // _0E
  u16 adjPanSizeY;      // _10
  u16 fbSizeX;          // _12
  u16 fbSizeY;          // _14
  u16 panPosX;          // _16
  u16 panPosY;          // _18
  u16 panSizeX;         // _1A
  u16 panSizeY;         // _1C
  VIXFBMode xfbMode;    // _20
  u32 nonInter;         // _24
  u32 tv;               // _28
  u8 wordPerLine;       // _2C
  u8 std;               // _2D
  u8 wpl;               // _2E
  u32 bufAddr;          // _30
  u32 tfbb;             // _34
  u32 bfbb;             // _38
  u8 xof;               // _3C
  BOOL isBlack;         // _40
  BOOL is3D;            // _44
  u32 rbufAddr;         // _48
  u32 rtfbb;            // _4C
  u32 rbfbb;            // _50
  VITimingInfo* timing; // _54
} VIPositionInfo;

typedef struct _GXRenderModeObj {
  /*0x00*/ VITVMode viTVmode;
  /*0x04*/ u16 fbWidth;
  /*0x06*/ u16 efbHeight;
  /*0x08*/ u16 xfbHeight;
  /*0x0A*/ u16 viXOrigin;
  /*0x0C*/ u16 viYOrigin;
  /*0x0E*/ u16 viWidth;
  /*0x10*/ u16 viHeight;
  /*0x14*/ VIXFBMode xFBmode;
  /*0x18*/ u8 field_rendering;
  u8 aa;
  u8 sample_pattern[12][2];
  u8 vfilter[7];
} GXRenderModeObj;

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

void GXSetTevDirect(GXTevStageID tev_stage);
void GXSetNumIndStages(u8 nIndStages);
void GXSetIndTexMtx(GXIndTexMtxID mtx_sel, f32 offset[2][3], s8 scale_exp);
void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map);
void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format,
                      GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s,
                      GXIndTexWrap wrap_t, GXBool add_prev, GXBool ind_lod,
                      GXIndTexAlphaSel alpha_sel);
void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXBool signed_offsets,
                     GXBool replace_mode, GXIndTexMtxID matrix_sel);
                     
void GXSetTevIndTile (GXTevStageID tev_stage, GXIndTexStageID ind_stage,
			     u16 tilesize_s, u16 tilesize_t, 
			     u16 tilespacing_s, u16 tilespacing_t, 
			     GXIndTexFormat format, GXIndTexMtxID matrix_sel,
			     GXIndTexBiasSel bias_sel, GXIndTexAlphaSel alpha_sel);
void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t);

#define GX_NOP 0x00
#define GX_DRAW_QUADS 0x80
#define GX_DRAW_TRIANGLES 0x90
#define GX_DRAW_TRIANGLE_STRIP 0x98
#define GX_DRAW_TRIANGLE_FAN 0xA0
#define GX_DRAW_LINES 0xA8
#define GX_DRAW_LINE_STRIP 0xB0
#define GX_DRAW_POINTS 0xB8

#define GX_LOAD_BP_REG 0x61
#define GX_LOAD_CP_REG 0x08
#define GX_LOAD_XF_REG 0x10
#define GX_LOAD_INDX_A 0x20
#define GX_LOAD_INDX_B 0x28
#define GX_LOAD_INDX_C 0x30
#define GX_LOAD_INDX_D 0x38

#define GX_CMD_CALL_DL 0x40
#define GX_CMD_INVL_VC 0x48

#define GX_OPCODE_MASK 0xF8
#define GX_VAT_MASK 0x07

void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht);
void GXSetCullMode(GXCullMode mode);
void GXSetCoPlanar(GXBool enable);

void GXBeginDisplayList(void* list, u32 size);
u32 GXEndDisplayList(void);
void GXCallDisplayList(const void* list, u32 nbytes);

void GXDrawSphere(u8 numMajor, u8 numMinor);

typedef struct {
  u8 pad[128];
} GXFifoObj;

typedef void (*GXBreakPtCallback)(void);

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size);
void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
void GXGetFifoPtrs(GXFifoObj* fifo, void** readPtr, void** writePtr);
GXFifoObj* GXGetCPUFifo(void);
GXFifoObj* GXGetGPFifo(void);
void GXSetCPUFifo(GXFifoObj* fifo);
void GXSetGPFifo(GXFifoObj* fifo);
void GXSaveCPUFifo(GXFifoObj* fifo);
void GXGetFifoStatus(GXFifoObj* fifo, GXBool* overhi, GXBool* underlow, u32* fifoCount,
                     GXBool* cpu_write, GXBool* gp_read, GXBool* fifowrap);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle,
                   GXBool* brkpt);
void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark, u32 loWaterMark);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
void GXEnableBreakPt(void* breakPt);
void GXDisableBreakPt(void);

extern GXRenderModeObj GXNtsc240Ds;
extern GXRenderModeObj GXNtsc240DsAa;
extern GXRenderModeObj GXNtsc240Int;
extern GXRenderModeObj GXNtsc240IntAa;
extern GXRenderModeObj GXNtsc480IntDf;
extern GXRenderModeObj GXNtsc480Int;
extern GXRenderModeObj GXNtsc480IntAa;
extern GXRenderModeObj GXNtsc480Prog;
extern GXRenderModeObj GXNtsc480ProgAa;
extern GXRenderModeObj GXMpal240Ds;
extern GXRenderModeObj GXMpal240DsAa;
extern GXRenderModeObj GXMpal240Int;
extern GXRenderModeObj GXMpal240IntAa;
extern GXRenderModeObj GXMpal480IntDf;
extern GXRenderModeObj GXMpal480Int;
extern GXRenderModeObj GXMpal480IntAa;
extern GXRenderModeObj GXPal264Ds;
extern GXRenderModeObj GXPal264DsAa;
extern GXRenderModeObj GXPal264Int;
extern GXRenderModeObj GXPal264IntAa;
extern GXRenderModeObj GXPal528IntDf;
extern GXRenderModeObj GXPal528Int;
extern GXRenderModeObj GXPal524IntAa;
extern GXRenderModeObj GXEurgb60Hz240Ds;
extern GXRenderModeObj GXEurgb60Hz240DsAa;
extern GXRenderModeObj GXEurgb60Hz240Int;
extern GXRenderModeObj GXEurgb60Hz240IntAa;
extern GXRenderModeObj GXEurgb60Hz480IntDf;
extern GXRenderModeObj GXEurgb60Hz480Int;
extern GXRenderModeObj GXEurgb60Hz480IntAa;

#define GX_MAX_Z24 0x00FFFFFF

void GXSetCopyClear(GXColor clear_clr, u32 clear_z);
void GXAdjustForOverscan(GXRenderModeObj* rmin, GXRenderModeObj* rmout, u16 hor, u16 ver);
void GXCopyDisp(void* dest, GXBool clear);
void GXSetDispCopyGamma(GXGamma gamma);
void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetDispCopyDst(u16 wd, u16 ht);
u32 GXSetDispCopyYScale(f32 vscale);
void GXSetCopyFilter(GXBool aa, u8 sample_pattern[12][2], GXBool vf, u8 vfilter[7]);
void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXCopyTex(void* dest, GXBool clear);

void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetVtxDescv(GXVtxDescList* list);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetNumTexGens(u8 nTexGens);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx,
                       GXBool normalize, u32 postmtx);
void GXSetLineWidth(u8 width, GXTexOffset texOffsets);
void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets);
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable, GXBool point_enable);
void GXSetArray(GXAttr attr, const void* data, u8 stride);
void GXInvalidateVtxCache(void);

static inline void GXSetTexCoordGen(GXTexCoordID dst_coord, GXTexGenType func,
                                    GXTexGenSrc src_param, u32 mtx) {
  GXSetTexCoordGen2(dst_coord, func, src_param, mtx, GX_FALSE, GX_PTIDENTITY);
}

GXBool GXGetTexObjMipMap(const GXTexObj* obj);
GXTexFmt GXGetTexObjFmt(const GXTexObj* obj);
u16 GXGetTexObjHeight(const GXTexObj* obj);
u16 GXGetTexObjWidth(const GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapS(const GXTexObj* obj);
GXTexWrapMode GXGetTexObjWrapT(const GXTexObj* obj);
void* GXGetTexObjData(const GXTexObj* obj);
void GXGetProjectionv(f32* p);
void GXGetLightPos(const GXLightObj* lt_obj, f32* x, f32* y, f32* z);
void GXGetLightColor(const GXLightObj* lt_obj, GXColor* color);
void GXGetVtxAttrFmt(GXVtxFmt idx, GXAttr attr, GXCompCnt* compCnt, GXCompType* compType,
                     u8* shift);

void GXSetNumChans(u8 nChans);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src,
                   u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);
void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);

void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func);
void GXInitLightDistAttn(GXLightObj* lt_obj, f32 ref_distance, f32 ref_brightness,
                         GXDistAttnFn dist_func);
void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z);
void GXInitLightDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz);
void GXInitLightColor(GXLightObj* lt_obj, GXColor color);
void GXInitLightAttn(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void GXInitLightAttnA(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2);
void GXInitLightAttnK(GXLightObj* lt_obj, f32 k0, f32 k1, f32 k2);
void GXLoadLightObjImm(GXLightObj* lt_obj, GXLightID light);

typedef void (*GXDrawDoneCallback)(void);
typedef void (*GXDrawSyncCallback)(u16 token);

GXFifoObj* GXInit(void* base, u32 size);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
void GXSetDrawSync(u16 token);
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback callback);

void GXDrawDone(void);
void GXSetDrawDone(void);
void GXFlush(void);
void GXPixModeSync(void);
void GXSetMisc(GXMiscToken token, u32 val);

extern void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1);
extern void GXClearGPMetric();
extern void GXReadXfRasMetric(u32* xfWaitIn, u32* xfWaitOut, u32* rasBusy, u32* clocks);

// Unused/inlined in P2.
extern void GXReadGPMetric(u32* count0, u32* count1);
extern u32 GXReadGP0Metric();
extern u32 GXReadGP1Metric();
extern void GXReadMemMetric(u32* cpReq, u32* tcReq, u32* cpuReadReq, u32* cpuWriteReq, u32* dspReq, u32* ioReq, u32* viReq, u32* peReq,
                            u32* rfReq, u32* fiReq);
extern void GXClearMemMetric();
extern void GXReadPixMetric(u32* topIn, u32* topOut, u32* bottomIn, u32* bottomOut, u32* clearIn, u32* copyClocks);
extern void GXClearPixMetric();
extern void GXSetVCacheMetric(GXVCachePerf attr);
extern void GXReadVCacheMetric(u32* check, u32* miss, u32* stall);
extern void GXClearVCacheMetric();
extern void GXInitXfRasMetric();
extern u32 GXReadClksPerVtx();

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetFogColor(GXColor color);
// ? GXSetFogRangeAdj();
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor,
                    GXLogicOp op);
void GXSetColorUpdate(GXBool update_enable);
void GXSetAlphaUpdate(GXBool update_enable);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void GXSetZCompLoc(GXBool before_tex);
void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
void GXSetDither(GXBool dither);
void GXSetDstAlpha(GXBool enable, u8 alpha);
// ? GXSetFieldMask();
void GXSetFieldMode(u8 field_mode, u8 half_aspect_ratio);

void GXSetTevOp(GXTevStageID id, GXTevMode mode);
void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c,
                     GXTevColorArg d);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c,
                     GXTevAlphaArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp,
                     GXTevRegID out_reg);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp,
                     GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorS10(GXTevRegID id, GXColorS10 color);
void GXSetTevKColor(GXTevKColorID id, GXColor color);
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green,
                           GXTevColorChan blue, GXTevColorChan alpha);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetNumTevStages(u8 nStages);

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* obj, GXTexMapID id);

void GXInitTexObj(GXTexObj* obj, const void* data, u16 width, u16 height, u32 format,
                  GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap);
void GXInitTexObjCI(GXTexObj* obj, const void* data, u16 width, u16 height, GXCITexFmt format,
                    GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap, u32 tlut);
void GXInitTexObjData(GXTexObj* obj, const void* data);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod,
                     f32 max_lod, f32 lod_bias, GXBool bias_clamp, GXBool do_edge_lod,
                     GXAnisotropy max_aniso);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap, u8 max_lod);
void GXInvalidateTexAll();
void GXInitTexObjWrapMode(GXTexObj* obj, GXTexWrapMode s, GXTexWrapMode t);
void GXInitTlutObj(GXTlutObj* obj, void* data, GXTlutFmt format, u16 entries);
void GXLoadTlut(const GXTlutObj* obj, GXTlut idx);
void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even,
                          GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback);
void GXInvalidateTexRegion(const GXTexRegion* region);

void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);

#define GX_PROJECTION_SZ 7


void GXSetProjection(f32 mtx[4][4], GXProjectionType type);
void GXLoadPosMtxImm(f32 mtx[3][4], u32 id);
void GXLoadNrmMtxImm(f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(f32 mtx[][4], u32 id, GXTexMtxType type);

void GXSetViewport(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz);
void GXSetCurrentMtx(u32 id);
void GXSetViewportJitter(f32 left, f32 top, f32 wd, f32 ht, f32 nearz, f32 farz, u32 field);
void GXSetScissorBoxOffset(s32 x_off, s32 y_off);
void GXSetClipMode(GXClipMode mode);

#define GXFIFO_ADDR 0xCC008000

typedef union {
  u8 u8;
  u16 u16;
  u32 u32;
  u64 u64;
  s8 s8;
  s16 s16;
  s32 s32;
  s64 s64;
  f32 f32;
  f64 f64;
} PPCWGPipe;

#define GXWGFifo (*(volatile PPCWGPipe*)GXFIFO_ADDR)

static inline void GXPosition2f32(const f32 x, const f32 y) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
}

static inline void GXPosition2u16(const u16 x, const u16 y) {
  GXWGFifo.u16 = x;
  GXWGFifo.u16 = y;
}

static inline void GXPosition2s16(const s16 x, const s16 y) {
  GXWGFifo.s16 = x;
  GXWGFifo.s16 = y;
}

static inline void GXPosition3s16(const s16 x, const s16 y, const s16 z) {
  GXWGFifo.s16 = x;
  GXWGFifo.s16 = y;
  GXWGFifo.s16 = z;
}

static inline void GXPosition3f32(const f32 x, const f32 y, const f32 z) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
  GXWGFifo.f32 = z;
}

static inline void GXNormal3f32(const f32 x, const f32 y, const f32 z) {
  GXWGFifo.f32 = x;
  GXWGFifo.f32 = y;
  GXWGFifo.f32 = z;
}

static inline void GXColor1u32(const u32 v) {
  GXWGFifo.u32 = v;
}

static inline void GXColor3u8(const u8 r, const u8 g, const u8 b) {
  GXWGFifo.u8 = r;
  GXWGFifo.u8 = g;
  GXWGFifo.u8 = b;
}

static inline void GXColor4u8(const u8 r, const u8 g, const u8 b, const u8 a) {
  GXWGFifo.u8 = r;
  GXWGFifo.u8 = g;
  GXWGFifo.u8 = b;
  GXWGFifo.u8 = a;
}

static inline void GXTexCoord2s16(const s16 u, const s16 v) {
  GXWGFifo.s16 = u;
  GXWGFifo.s16 = v;
}

static inline void GXTexCoord2f32(const f32 u, const f32 v) {
  GXWGFifo.f32 = u;
  GXWGFifo.f32 = v;
}

static inline void GXPosition1x8(u8 index) {
  GXWGFifo.u8 = index;
}

static inline void GXColor1x8(u8 index) {
  GXWGFifo.u8 = index;
}

static inline void GXPosition1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXColor1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXTexCoord1x16(u16 index) {
  GXWGFifo.u16 = index;
}

static inline void GXEnd(void) {}

// Upper words of the masks, since UIMM is only 16 bits
#define OS_CACHED_REGION_PREFIX 0x8000
#define OS_UNCACHED_REGION_PREFIX 0xC000
#define OS_PHYSICAL_MASK 0x3FFF

#define OS_BASE_CACHED (OS_CACHED_REGION_PREFIX << 16)
#define OS_BASE_UNCACHED (OS_UNCACHED_REGION_PREFIX << 16)

#define AT_ADDRESS

typedef s64 OSTime;
typedef u32 OSTick;
u32 __OSBusClock();  // sync with OSLoMem.h
u32 __OSCoreClock(); // sync with OSLoMem.h
#define OS_BUS_CLOCK (u32)__OSBusClock
#define OS_CORE_CLOCK __OSCoreClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#define OSPhysicalToCached(paddr) ((void*)((u32)(paddr) + OS_BASE_CACHED))
#define OSPhysicalToUncached(paddr) ((void*)((u32)(paddr) + OS_BASE_UNCACHED))
#define OSCachedToPhysical(caddr) ((u32)((u8*)(caddr)-OS_BASE_CACHED))
#define OSUncachedToPhysical(ucaddr) ((u32)((u8*)(ucaddr)-OS_BASE_UNCACHED))
#define OSCachedToUncached(caddr) ((void*)((u8*)(caddr) + (OS_BASE_UNCACHED - OS_BASE_CACHED)))
#define OSUncachedToCached(ucaddr) ((void*)((u8*)(ucaddr) - (OS_BASE_UNCACHED - OS_BASE_CACHED)))

#define OSTicksToCycles(ticks) (((ticks) * ((OS_CORE_CLOCK * 2) / OS_TIMER_CLOCK)) / 2)
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) (((ticks)*8) / (OS_TIMER_CLOCK / 125000))
#define OSTicksToNanoseconds(ticks) (((ticks)*8000) / (OS_TIMER_CLOCK / 125000))
#define OSSecondsToTicks(sec) ((sec)*OS_TIMER_CLOCK) 
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

#define OSDiffTick(tick1, tick0) ((s32)(tick1) - (s32)(tick0))

#define OSRoundUp32B(v) (((u32)(v + 31) & ~31))
#define OSRoundDown32B(x) (((u32)(x)) & ~31)

void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaHi(void* newHi);
void OSSetArenaLo(void* newLo);

void* OSAllocFromArenaLo(u32 size, u32 align);
void* OSAllocFromArenaHi(u32 size, u32 align);

void OSInit();

OSTime OSGetTime();
OSTick OSGetTick();

typedef struct OSCalendarTime {
  int sec;  // seconds after the minute [0, 61]
  int min;  // minutes after the hour [0, 59]
  int hour; // hours since midnight [0, 23]
  int mday; // day of the month [1, 31]
  int mon;  // month since January [0, 11]
  int year; // years in AD [1, ...]
  int wday; // days since Sunday [0, 6]
  int yday; // days since January 1 [0, 365]

  int msec; // milliseconds after the second [0,999]
  int usec; // microseconds after the millisecond [0,999]
} OSCalendarTime;

OSTime OSCalendarTimeToTicks(OSCalendarTime* td);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td);

typedef struct OSStopwatch {
	char* name;
	OSTime total;
	u32 hits;
	OSTime min;
	OSTime max;
	OSTime last;
	BOOL running;
} OSStopwatch;

void OSInitStopwatch(OSStopwatch* sw, char* name);
void OSStartStopwatch(OSStopwatch* sw);
void OSStopStopwatch(OSStopwatch* sw);
OSTime OSCheckStopwatch(OSStopwatch* sw);
void OSResetStopwatch(OSStopwatch* sw);
void OSDumpStopwatch(OSStopwatch* sw);

#define OS_CONSOLE_MASK 0xf0000000
#define OS_CONSOLE_RETAIL 0x00000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_TDEV 0x20000000

#define OS_CONSOLE_RETAIL4 0x00000004
#define OS_CONSOLE_RETAIL3 0x00000003
#define OS_CONSOLE_RETAIL2 0x00000002
#define OS_CONSOLE_RETAIL1 0x00000001
#define OS_CONSOLE_TDEVHW4 0x20000007
#define OS_CONSOLE_TDEVHW3 0x20000006
#define OS_CONSOLE_TDEVHW2 0x20000005
#define OS_CONSOLE_TDEVHW1 0x20000004
#define OS_CONSOLE_DEVHW4 0x10000007
#define OS_CONSOLE_DEVHW3 0x10000006
#define OS_CONSOLE_DEVHW2 0x10000005
#define OS_CONSOLE_DEVHW1 0x10000004
#define OS_CONSOLE_MINNOW 0x10000003
#define OS_CONSOLE_ARTHUR 0x10000002
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_EMULATOR 0x10000000

u32 OSGetConsoleType();

#define OS_SOUND_MODE_MONO 0u
#define OS_SOUND_MODE_STEREO 1u

u32 OSGetSoundMode(void);
void OSSetSoundMode(u32 mode);

#define OS_PROGRESSIVE_MODE_OFF 0u
#define OS_PROGRESSIVE_MODE_ON 1u

u32 OSGetProgressiveMode(void);
void OSSetProgressiveMode(u32 on);

#define OS_LANG_ENGLISH 0u
#define OS_LANG_GERMAN 1u
#define OS_LANG_FRENCH 2u
#define OS_LANG_SPANISH 3u
#define OS_LANG_ITALIAN 4u
#define OS_LANG_DUTCH 5u

u8 OSGetLanguage(void);
void OSSetLanguage(u8 language);

#define OS_EURGB60_OFF 0u
#define OS_EURGB60_ON 1u

u32 OSGetEuRgb60Mode(void);
void OSSetEuRgb60Mode(u32 on);

void OSRegisterVersion(const char* id);

BOOL OSDisableInterrupts(void);
BOOL OSEnableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL level);

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)


#define ASSERT(exp) ((void)0)

void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
void OSFatal(GXColor fg, GXColor bg, const char* msg);

u32 OSGetPhysicalMemSize(void);
u32 OSGetConsoleSimulatedMemSize(void);

#define __OS_CONTEXT_FRAME 768

#define OS_CONTEXT_R0 0
#define OS_CONTEXT_R1 4
#define OS_CONTEXT_R2 8
#define OS_CONTEXT_R3 12
#define OS_CONTEXT_R4 16
#define OS_CONTEXT_R5 20
#define OS_CONTEXT_R6 24
#define OS_CONTEXT_R7 28
#define OS_CONTEXT_R8 32
#define OS_CONTEXT_R9 36
#define OS_CONTEXT_R10 40
#define OS_CONTEXT_R11 44
#define OS_CONTEXT_R12 48
#define OS_CONTEXT_R13 52
#define OS_CONTEXT_R14 56
#define OS_CONTEXT_R15 60
#define OS_CONTEXT_R16 64
#define OS_CONTEXT_R17 68
#define OS_CONTEXT_R18 72
#define OS_CONTEXT_R19 76
#define OS_CONTEXT_R20 80
#define OS_CONTEXT_R21 84
#define OS_CONTEXT_R22 88
#define OS_CONTEXT_R23 92
#define OS_CONTEXT_R24 96
#define OS_CONTEXT_R25 100
#define OS_CONTEXT_R26 104
#define OS_CONTEXT_R27 108
#define OS_CONTEXT_R28 112
#define OS_CONTEXT_R29 116
#define OS_CONTEXT_R30 120
#define OS_CONTEXT_R31 124

#define OS_CONTEXT_CR 128
#define OS_CONTEXT_LR 132
#define OS_CONTEXT_CTR 136
#define OS_CONTEXT_XER 140

#define OS_CONTEXT_FPR0 144
#define OS_CONTEXT_FPR1 152
#define OS_CONTEXT_FPR2 160
#define OS_CONTEXT_FPR3 168
#define OS_CONTEXT_FPR4 176
#define OS_CONTEXT_FPR5 184
#define OS_CONTEXT_FPR6 192
#define OS_CONTEXT_FPR7 200
#define OS_CONTEXT_FPR8 208
#define OS_CONTEXT_FPR9 216
#define OS_CONTEXT_FPR10 224
#define OS_CONTEXT_FPR11 232
#define OS_CONTEXT_FPR12 240
#define OS_CONTEXT_FPR13 248
#define OS_CONTEXT_FPR14 256
#define OS_CONTEXT_FPR15 264
#define OS_CONTEXT_FPR16 272
#define OS_CONTEXT_FPR17 280
#define OS_CONTEXT_FPR18 288
#define OS_CONTEXT_FPR19 296
#define OS_CONTEXT_FPR20 304
#define OS_CONTEXT_FPR21 312
#define OS_CONTEXT_FPR22 320
#define OS_CONTEXT_FPR23 328
#define OS_CONTEXT_FPR24 336
#define OS_CONTEXT_FPR25 344
#define OS_CONTEXT_FPR26 352
#define OS_CONTEXT_FPR27 360
#define OS_CONTEXT_FPR28 368
#define OS_CONTEXT_FPR29 376
#define OS_CONTEXT_FPR30 384
#define OS_CONTEXT_FPR31 392

#define OS_CONTEXT_FPSCR 400

#define OS_CONTEXT_SRR0 408
#define OS_CONTEXT_SRR1 412

#define OS_CONTEXT_MODE 416
#define OS_CONTEXT_STATE 418

#define OS_CONTEXT_GQR0 420
#define OS_CONTEXT_GQR1 424
#define OS_CONTEXT_GQR2 428
#define OS_CONTEXT_GQR3 432
#define OS_CONTEXT_GQR4 436
#define OS_CONTEXT_GQR5 440
#define OS_CONTEXT_GQR6 444
#define OS_CONTEXT_GQR7 448
#define __OSCONTEXT_PADDING 452

#define OS_CONTEXT_PSF0 456
#define OS_CONTEXT_PSF1 464
#define OS_CONTEXT_PSF2 472
#define OS_CONTEXT_PSF3 480
#define OS_CONTEXT_PSF4 488
#define OS_CONTEXT_PSF5 496
#define OS_CONTEXT_PSF6 504
#define OS_CONTEXT_PSF7 512
#define OS_CONTEXT_PSF8 520
#define OS_CONTEXT_PSF9 528
#define OS_CONTEXT_PSF10 536
#define OS_CONTEXT_PSF11 544
#define OS_CONTEXT_PSF12 552
#define OS_CONTEXT_PSF13 560
#define OS_CONTEXT_PSF14 568
#define OS_CONTEXT_PSF15 576
#define OS_CONTEXT_PSF16 584
#define OS_CONTEXT_PSF17 592
#define OS_CONTEXT_PSF18 600
#define OS_CONTEXT_PSF19 608
#define OS_CONTEXT_PSF20 616
#define OS_CONTEXT_PSF21 624
#define OS_CONTEXT_PSF22 632
#define OS_CONTEXT_PSF23 640
#define OS_CONTEXT_PSF24 648
#define OS_CONTEXT_PSF25 656
#define OS_CONTEXT_PSF26 664
#define OS_CONTEXT_PSF27 672
#define OS_CONTEXT_PSF28 680
#define OS_CONTEXT_PSF29 688
#define OS_CONTEXT_PSF30 696
#define OS_CONTEXT_PSF31 704
#define OS_CONTEXT_STATE_EXC 0x02u

#define OS_CONTEXT_STATE_FPSAVED 0x01u

typedef struct OSContext {
  u32 gpr[32];
  u32 cr;
  u32 lr;
  u32 ctr;
  u32 xer;

  f64 fpr[32];

  u32 fpscr_pad;
  u32 fpscr;

  u32 srr0;
  u32 srr1;

  u16 mode;
  u16 state;

  u32 gqr[8];
  u32 psf_pad;
  f64 psf[32];

} OSContext;

u32 OSSaveContext(OSContext* context);
void OSClearContext(OSContext* context);
OSContext* OSGetCurrentContext();
void OSSetCurrentContext(OSContext* context);

typedef struct OSAlarm OSAlarm;
typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

struct OSAlarm {
  OSAlarmHandler handler;
  u32 tag;
  OSTime fire;
  OSAlarm* prev;
  OSAlarm* next;
  OSTime period;
  OSTime start;
};

void OSInitAlarm(void);
void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler);
void OSSetAlarmTag(OSAlarm* alarm, u32 tag);
void OSSetAbsAlarm(OSAlarm* alarm, OSTime time, OSAlarmHandler handler);
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler);
void OSCreateAlarm(OSAlarm* alarm);
void OSCancelAlarm(OSAlarm* alarm);
void OSCancelAlarms(u32 tag);

BOOL OSCheckAlarmQueue(void);


typedef int OSHeapHandle;
typedef void (*OSAllocVisitor)(void* obj, u32 size);
void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps);
OSHeapHandle OSCreateHeap(void* start, void* end);
void OSDestroyHeap(OSHeapHandle heap);
void OSAddToHeap(OSHeapHandle heap, void* start, void* end);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
void* OSAllocFromHeap(OSHeapHandle heap, u32 size);
void* OSAllocFixed(void** rstart, void** rend);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);
long OSCheckHeap(OSHeapHandle heap);
void OSDumpHeap(OSHeapHandle heap);
void *OSAllocFixed(void **rstart, void **rend);
u32 OSReferentSize(void* ptr);
void OSVisitAllocated(OSAllocVisitor visitor);
extern volatile OSHeapHandle __OSCurrHeap;
#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr) OSFreeToHeap(__OSCurrHeap, (ptr))


void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaHi(void* addr);
void OSSetArenaLo(void* addr);
void* OSAllocFromArenaLo(u32 size, u32 align);
void* OSAllocFromArenaLo(u32 size, u32 align);


void DCInvalidateRange(void* addr, u32 nBytes);
void DCFlushRange(void* addr, u32 nBytes);
void DCStoreRange(void* addr, u32 nBytes);
void DCFlushRangeNoSync(void* addr, u32 nBytes);
void DCStoreRangeNoSync(void* addr, u32 nBytes);
void DCZeroRange(void* addr, u32 nBytes);
void DCTouchRange(void* addr, u32 nBytes);
void ICInvalidateRange(void* addr, u32 nBytes);

#define LC_BASE_PREFIX 0xE000
#define LC_BASE (LC_BASE_PREFIX << 16)
#define LCGetBase() ((void*)LC_BASE)

void LCEnable();
void LCDisable(void);
void LCLoadBlocks(void* destTag, void* srcAddr, u32 numBlocks);
void LCStoreBlocks(void* destAddr, void* srcTag, u32 numBlocks);
u32 LCLoadData(void* destAddr, void* srcAddr, u32 nBytes);
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes);
u32 LCQueueLength(void);
void LCQueueWait(u32 len);
void LCFlushQueue(void);



#define OS_ERROR_SYSTEM_RESET 0
#define OS_ERROR_MACHINE_CHECK 1
#define OS_ERROR_DSI 2
#define OS_ERROR_ISI 3
#define OS_ERROR_EXTERNAL_INTERRUPT 4
#define OS_ERROR_ALIGNMENT 5
#define OS_ERROR_PROGRAM 6
#define OS_ERROR_FLOATING_POINT 7
#define OS_ERROR_DECREMENTER 8
#define OS_ERROR_SYSTEM_CALL 9
#define OS_ERROR_TRACE 10
#define OS_ERROR_PERFORMACE_MONITOR 11
#define OS_ERROR_BREAKPOINT 12
#define OS_ERROR_SYSTEM_INTERRUPT 13
#define OS_ERROR_THERMAL_INTERRUPT 14
#define OS_ERROR_PROTECTION 15
#define OS_ERROR_FPE 16

#define OS_ERROR_MAX (OS_ERROR_FPE + 1)

typedef u16 OSError;
typedef void (*OSErrorHandler)( OSError error, OSContext* context, ... );

OSErrorHandler OSSetErrorHandler(OSError code, OSErrorHandler handler);



/* "include\dolphin\os\OSException.h" line 4 "dolphin/os/OSContext.h" */
/* end "dolphin/os/OSContext.h" */
/* "include\dolphin\os\OSException.h" line 5 "dolphin/types.h" */
/* end "dolphin/types.h" */

#define __OS_EXCEPTION_SYSTEM_RESET         0
#define __OS_EXCEPTION_MACHINE_CHECK        1
#define __OS_EXCEPTION_DSI                  2
#define __OS_EXCEPTION_ISI                  3
#define __OS_EXCEPTION_EXTERNAL_INTERRUPT   4
#define __OS_EXCEPTION_ALIGNMENT            5
#define __OS_EXCEPTION_PROGRAM              6
#define __OS_EXCEPTION_FLOATING_POINT       7
#define __OS_EXCEPTION_DECREMENTER          8
#define __OS_EXCEPTION_SYSTEM_CALL          9
#define __OS_EXCEPTION_TRACE                10
#define __OS_EXCEPTION_PERFORMACE_MONITOR   11
#define __OS_EXCEPTION_BREAKPOINT           12
#define __OS_EXCEPTION_SYSTEM_INTERRUPT     13
#define __OS_EXCEPTION_THERMAL_INTERRUPT    14
#define __OS_EXCEPTION_MAX                  \
        (__OS_EXCEPTION_THERMAL_INTERRUPT+1)

typedef u8 __OSException;
typedef void (*__OSExceptionHandler)(__OSException exception, OSContext* context);

#define OS_EXCEPTION_SAVE_GPRS(context)                                                            \
  stw r0, OS_CONTEXT_R0(context);                                                                  \
  stw r1, OS_CONTEXT_R1(context);                                                                  \
  stw r2, OS_CONTEXT_R2(context);                                                                  \
  stmw r6, OS_CONTEXT_R6(context);                                                                 \
  mfspr r0, GQR1;                                                                                  \
  stw r0, OS_CONTEXT_GQR1(context);                                                                \
  mfspr r0, GQR2;                                                                                  \
  stw r0, OS_CONTEXT_GQR2(context);                                                                \
  mfspr r0, GQR3;                                                                                  \
  stw r0, OS_CONTEXT_GQR3(context);                                                                \
  mfspr r0, GQR4;                                                                                  \
  stw r0, OS_CONTEXT_GQR4(context);                                                                \
  mfspr r0, GQR5;                                                                                  \
  stw r0, OS_CONTEXT_GQR5(context);                                                                \
  mfspr r0, GQR6;                                                                                  \
  stw r0, OS_CONTEXT_GQR6(context);                                                                \
  mfspr r0, GQR7;                                                                                  \
  stw r0, OS_CONTEXT_GQR7(context);


#define EXI_MEMORY_CARD_59 0x00000004
#define EXI_MEMORY_CARD_123 0x00000008
#define EXI_MEMORY_CARD_251 0x00000010
#define EXI_MEMORY_CARD_507 0x00000020

#define EXI_MEMORY_CARD_1019 0x00000040
#define EXI_MEMORY_CARD_2043 0x00000080

#define EXI_MEMORY_CARD_1019A 0x00000140
#define EXI_MEMORY_CARD_1019B 0x00000240
#define EXI_MEMORY_CARD_1019C 0x00000340
#define EXI_MEMORY_CARD_1019D 0x00000440
#define EXI_MEMORY_CARD_1019E 0x00000540
#define EXI_MEMORY_CARD_1019F 0x00000640
#define EXI_MEMORY_CARD_1019G 0x00000740

#define EXI_MEMORY_CARD_2043A 0x00000180
#define EXI_MEMORY_CARD_2043B 0x00000280
#define EXI_MEMORY_CARD_2043C 0x00000380
#define EXI_MEMORY_CARD_2043D 0x00000480
#define EXI_MEMORY_CARD_2043E 0x00000580
#define EXI_MEMORY_CARD_2043F 0x00000680
#define EXI_MEMORY_CARD_2043G 0x00000780

#define EXI_USB_ADAPTER 0x01010000
#define EXI_NPDP_GDEV 0x01020000

#define EXI_MODEM 0x02020000
#define EXI_ETHER 0x04020200
#define EXI_ETHER_VIEWER 0x04220001
#define EXI_STREAM_HANGER 0x04130000

#define EXI_MARLIN 0x03010000

#define EXI_IS_VIEWER 0x05070000

#define EXI_FREQ_1M 0
#define EXI_FREQ_2M 1
#define EXI_FREQ_4M 2
#define EXI_FREQ_8M 3
#define EXI_FREQ_16M 4
#define EXI_FREQ_32M 5

#define EXI_READ 0
#define EXI_WRITE 1

#define EXI_STATE_IDLE 0x00
#define EXI_STATE_DMA 0x01
#define EXI_STATE_IMM 0x02
#define EXI_STATE_BUSY (EXI_STATE_DMA | EXI_STATE_IMM)
#define EXI_STATE_SELECTED 0x04
#define EXI_STATE_ATTACHED 0x08
#define EXI_STATE_LOCKED 0x10

BOOL EXIProbe(s32 chan);
s32 EXIProbeEx(s32 chan);

s32 EXIGetType(s32 chan, u32 dev, u32* type);
char* EXIGetTypeString(u32 type);
u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext);
s32 EXIGetID(s32 chan, u32 dev, u32* id);

typedef void (*EXICallback)(s32 chan, OSContext* context);



#define OS_GQR_F32 0x0000
#define OS_GQR_U8 0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8 0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8 2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8 4
#define OS_FASTCAST_S16 5
// clang-format off
static inline void OSInitFastCast(void) {
}
// clang-format off

static inline s16 __OSf32tos16(register f32 inF)
{
	u32 tmp;
	register u32* tmpPtr = &tmp;
	register s16 out;
	// clang-format off
  // clang-format on

  return out;
}

static inline void OSf32tos16(f32 *f, s16 *out) { *out = __OSf32tos16(*f); }

static inline u8 __OSf32tou8(register f32 inF)
{
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register u8 out;
  // clang-format off
  // clang-format on

  return out;
}

static inline void OSf32tou8(f32 *f, u8 *out) { *out = __OSf32tou8(*f); }

static inline s8 __OSf32tos8(register f32 inF)
{
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register s8 out;
  // clang-format off
  // clang-format on

  return out;
}

static inline void OSf32tos8(f32 *f, s8 *out) { *out = __OSf32tos8(*f); }

static inline u16 __OSf32tou16(register f32 inF)
{
  u32 tmp;
  register u32 *tmpPtr = &tmp;
  register u16 out;
  // clang-format off
  // clang-format on

  return out;
}

static inline void OSf32tou16(f32 *f, u16 *out) { *out = __OSf32tou16(*f); }

static inline float __OSs8tof32(register const s8* arg) {
    register float ret;


    return ret;
}

static inline void OSs8tof32(const s8* in, float* out) { *out = __OSs8tof32(in); }

static inline float __OSs16tof32(register const s16* arg) {
    register float ret;


    return ret;
}

static inline void OSs16tof32(const s16* in, float* out) { *out = __OSs16tof32(in); }

static inline float __OSu8tof32(register const u8* arg) {
    register float ret;

    return ret;
}

static inline void OSu8tof32(const u8* in, float* out) { *out = __OSu8tof32(in); }

static inline float __OSu16tof32(register const u16* arg) {
    register float ret;

    return ret;
}

static inline void OSu16tof32(const u16* in, float* out) { *out = __OSu16tof32(in); }

#define OS_FONT_ENCODE_ANSI 0u
#define OS_FONT_ENCODE_SJIS 1u
#define OS_FONT_ENCODE_UTF8 3u  // UTF-8 [RFC 3629]
#define OS_FONT_ENCODE_UTF16 4u // UTF-16BE [RFC 2781]
#define OS_FONT_ENCODE_UTF32 5u // UTF-32
#define OS_FONT_ENCODE_MAX 5u
#define OS_FONT_ENCODE_VOID 0xffffu

#define OS_FONT_PROPORTIONAL FALSE
#define OS_FONT_FIXED TRUE

u16 OSGetFontEncode(void);
u16 OSSetFontEncode(u16 encode);

#define __OS_INTERRUPT_MEM_0 0
#define __OS_INTERRUPT_MEM_1 1
#define __OS_INTERRUPT_MEM_2 2
#define __OS_INTERRUPT_MEM_3 3
#define __OS_INTERRUPT_MEM_ADDRESS 4
#define __OS_INTERRUPT_DSP_AI 5
#define __OS_INTERRUPT_DSP_ARAM 6
#define __OS_INTERRUPT_DSP_DSP 7
#define __OS_INTERRUPT_AI_AI 8
#define __OS_INTERRUPT_EXI_0_EXI 9
#define __OS_INTERRUPT_EXI_0_TC 10
#define __OS_INTERRUPT_EXI_0_EXT 11
#define __OS_INTERRUPT_EXI_1_EXI 12
#define __OS_INTERRUPT_EXI_1_TC 13
#define __OS_INTERRUPT_EXI_1_EXT 14
#define __OS_INTERRUPT_EXI_2_EXI 15
#define __OS_INTERRUPT_EXI_2_TC 16
#define __OS_INTERRUPT_PI_CP 17
#define __OS_INTERRUPT_PI_PE_TOKEN 18
#define __OS_INTERRUPT_PI_PE_FINISH 19
#define __OS_INTERRUPT_PI_SI 20
#define __OS_INTERRUPT_PI_DI 21
#define __OS_INTERRUPT_PI_RSW 22
#define __OS_INTERRUPT_PI_ERROR 23
#define __OS_INTERRUPT_PI_VI 24
#define __OS_INTERRUPT_PI_DEBUG 25
#define __OS_INTERRUPT_PI_HSP 26
#define __OS_INTERRUPT_MAX 32

#define OS_INTERRUPTMASK(interrupt) (0x80000000u >> (interrupt))

#define OS_INTERRUPTMASK_MEM_0 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_0)
#define OS_INTERRUPTMASK_MEM_1 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_1)
#define OS_INTERRUPTMASK_MEM_2 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_2)
#define OS_INTERRUPTMASK_MEM_3 OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_3)
#define OS_INTERRUPTMASK_MEM_ADDRESS OS_INTERRUPTMASK(__OS_INTERRUPT_MEM_ADDRESS)
#define OS_INTERRUPTMASK_MEM                                                                       \
  (OS_INTERRUPTMASK_MEM_0 | OS_INTERRUPTMASK_MEM_1 | OS_INTERRUPTMASK_MEM_2 |                      \
   OS_INTERRUPTMASK_MEM_3 | OS_INTERRUPTMASK_MEM_ADDRESS)
#define OS_INTERRUPTMASK_DSP_AI OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_AI)
#define OS_INTERRUPTMASK_DSP_ARAM OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_ARAM)
#define OS_INTERRUPTMASK_DSP_DSP OS_INTERRUPTMASK(__OS_INTERRUPT_DSP_DSP)
#define OS_INTERRUPTMASK_DSP                                                                       \
  (OS_INTERRUPTMASK_DSP_AI | OS_INTERRUPTMASK_DSP_ARAM | OS_INTERRUPTMASK_DSP_DSP)
#define OS_INTERRUPTMASK_AI_AI OS_INTERRUPTMASK(__OS_INTERRUPT_AI_AI)
#define OS_INTERRUPTMASK_AI (OS_INTERRUPTMASK_AI_AI)
#define OS_INTERRUPTMASK_EXI_0_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_EXI)
#define OS_INTERRUPTMASK_EXI_0_TC OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_TC)
#define OS_INTERRUPTMASK_EXI_0_EXT OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_0_EXT)
#define OS_INTERRUPTMASK_EXI_0                                                                     \
  (OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC | OS_INTERRUPTMASK_EXI_0_EXT)
#define OS_INTERRUPTMASK_EXI_1_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_EXI)
#define OS_INTERRUPTMASK_EXI_1_TC OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_TC)
#define OS_INTERRUPTMASK_EXI_1_EXT OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_1_EXT)
#define OS_INTERRUPTMASK_EXI_1                                                                     \
  (OS_INTERRUPTMASK_EXI_1_EXI | OS_INTERRUPTMASK_EXI_1_TC | OS_INTERRUPTMASK_EXI_1_EXT)
#define OS_INTERRUPTMASK_EXI_2_EXI OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_2_EXI)
#define OS_INTERRUPTMASK_EXI_2_TC OS_INTERRUPTMASK(__OS_INTERRUPT_EXI_2_TC)
#define OS_INTERRUPTMASK_EXI_2 (OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC)
#define OS_INTERRUPTMASK_EXI                                                                       \
  (OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC | OS_INTERRUPTMASK_EXI_0_EXT |           \
   OS_INTERRUPTMASK_EXI_1_EXI | OS_INTERRUPTMASK_EXI_1_TC | OS_INTERRUPTMASK_EXI_1_EXT |           \
   OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC)
#define OS_INTERRUPTMASK_PI_PE_TOKEN OS_INTERRUPTMASK(__OS_INTERRUPT_PI_PE_TOKEN)
#define OS_INTERRUPTMASK_PI_PE_FINISH OS_INTERRUPTMASK(__OS_INTERRUPT_PI_PE_FINISH)
#define OS_INTERRUPTMASK_PI_PE (OS_INTERRUPTMASK_PI_PE_TOKEN | OS_INTERRUPTMASK_PI_PE_FINISH)
#define OS_INTERRUPTMASK_PI_CP OS_INTERRUPTMASK(__OS_INTERRUPT_PI_CP)
#define OS_INTERRUPTMASK_PI_SI OS_INTERRUPTMASK(__OS_INTERRUPT_PI_SI)
#define OS_INTERRUPTMASK_PI_DI OS_INTERRUPTMASK(__OS_INTERRUPT_PI_DI)
#define OS_INTERRUPTMASK_PI_RSW OS_INTERRUPTMASK(__OS_INTERRUPT_PI_RSW)
#define OS_INTERRUPTMASK_PI_ERROR OS_INTERRUPTMASK(__OS_INTERRUPT_PI_ERROR)
#define OS_INTERRUPTMASK_PI_VI OS_INTERRUPTMASK(__OS_INTERRUPT_PI_VI)
#define OS_INTERRUPTMASK_PI_DEBUG OS_INTERRUPTMASK(__OS_INTERRUPT_PI_DEBUG)
#define OS_INTERRUPTMASK_PI_HSP OS_INTERRUPTMASK(__OS_INTERRUPT_PI_HSP)
#define OS_INTERRUPTMASK_PI                                                                        \
  (OS_INTERRUPTMASK_PI_CP | OS_INTERRUPTMASK_PI_SI | OS_INTERRUPTMASK_PI_DI |                      \
   OS_INTERRUPTMASK_PI_RSW | OS_INTERRUPTMASK_PI_ERROR | OS_INTERRUPTMASK_PI_VI |                  \
   OS_INTERRUPTMASK_PI_PE_TOKEN | OS_INTERRUPTMASK_PI_PE_FINISH | OS_INTERRUPTMASK_PI_DEBUG |      \
   OS_INTERRUPTMASK_PI_HSP)

typedef s16 __OSInterrupt;
typedef void (*__OSInterruptHandler)(__OSInterrupt interrupt, OSContext* context);

typedef u32 OSInterruptMask;

extern volatile __OSInterrupt __OSLastInterrupt;
extern volatile u32 __OSLastInterruptSrr0;
extern volatile OSTime __OSLastInterruptTime;

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt interrupt, __OSInterruptHandler handler);

__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt interrupt);

void __OSDispatchInterrupt(__OSException exception, OSContext* context);

OSInterruptMask OSGetInterruptMask(void);
OSInterruptMask OSSetInterruptMask(OSInterruptMask mask);
OSInterruptMask __OSMaskInterrupts(OSInterruptMask mask);
OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask mask);


#define OS_PROTECT_CHAN0 0
#define OS_PROTECT_CHAN1 1
#define OS_PROTECT_CHAN2 2
#define OS_PROTECT_CHAN3 3

#define OS_PROTECT_CONTROL_NONE 0x00
#define OS_PROTECT_CONTROL_READ 0x01
#define OS_PROTECT_CONTROL_WRITE 0x02
#define OS_PROTECT_CONTROL_RDWR (OS_PROTECT_CONTROL_READ | OS_PROTECT_CONTROL_WRITE)

void OSProtectRange(u32 chan, void* addr, u32 nBytes, u32 control);


typedef struct OSThread OSThread;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSThreadLink OSThreadLink;
typedef s32 OSPriority; //  0 highest, 31 lowest

typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSMutexLink OSMutexLink;
typedef struct OSCond OSCond;

typedef void (*OSIdleFunction)(void* param);
typedef void (*OSSwitchThreadCallback)(OSThread* from, OSThread* to);

struct OSThreadQueue {
  OSThread* head;
  OSThread* tail;
};

struct OSThreadLink {
  OSThread* next;
  OSThread* prev;
};

struct OSMutexQueue {
  OSMutex* head;
  OSMutex* tail;
};

struct OSMutexLink {
  OSMutex* next;
  OSMutex* prev;
};

struct OSThread {
  OSContext context;
  u16 state;
  u16 attr;
  s32 suspend;
  OSPriority priority;
  OSPriority base;
  void* val;
  OSThreadQueue* queue;
  OSThreadLink link;
  OSThreadQueue queueJoin;
  OSMutex* mutex;
  OSMutexQueue queueMutex;
  OSThreadLink linkActive;
  u8* stackBase;
  u32* stackEnd;
};

enum OS_THREAD_STATE {
  OS_THREAD_STATE_READY = 1,
  OS_THREAD_STATE_RUNNING = 2,
  OS_THREAD_STATE_WAITING = 4,
  OS_THREAD_STATE_MORIBUND = 8
};

#define OS_THREAD_ATTR_DETACH 0x0001u

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

#define OS_PRIORITY_MIN 0  // highest
#define OS_PRIORITY_MAX 31 // lowest
#define OS_PRIORITY_IDLE OS_PRIORITY_MAX


void OSInitThreadQueue(OSThreadQueue* queue);
OSThread* OSGetCurrentThread(void);
BOOL OSIsThreadSuspended(OSThread* thread);
BOOL OSIsThreadTerminated(OSThread* thread);
s32 OSDisableScheduler(void);
s32 OSEnableScheduler(void);
void OSYieldThread(void);
BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize,
                    OSPriority priority, u16 attr);
void OSExitThread(void* val);
void OSCancelThread(OSThread* thread);
BOOL OSJoinThread(OSThread* thread, void** val);
void OSDetachThread(OSThread* thread);
s32 OSResumeThread(OSThread* thread);
s32 OSSuspendThread(OSThread* thread);
BOOL OSSetThreadPriority(OSThread* thread, OSPriority priority);
OSPriority OSGetThreadPriority(OSThread* thread);
void OSSleepThread(OSThreadQueue* queue);
void OSWakeupThread(OSThreadQueue* queue);

OSThread* OSSetIdleFunction(OSIdleFunction idleFunction, void* param, void* stack, u32 stackSize);
OSThread* OSGetIdleFunction(void);
void OSClearStack(u8 val);
long OSCheckActiveThreads(void);

/* end "dolphin/os/OSThread.h" */
typedef struct OSMessageQueue OSMessageQueue;
typedef void* OSMessage;

struct OSMessageQueue {
  OSThreadQueue queueSend;
  OSThreadQueue queueReceive;
  OSMessage* msgArray;
  s32 msgCount;
  s32 firstIndex;
  s32 usedCount;
};

// Flags to turn blocking on/off when sending/receiving message
#define OS_MESSAGE_NOBLOCK 0
#define OS_MESSAGE_BLOCK 1

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount);
BOOL OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags);
BOOL OSJamMessage(OSMessageQueue* mq, OSMessage msg, s32 flags);
BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags);


#define OS_MODULE_VERSION 2
typedef struct OSModuleHeader OSModuleHeader;

typedef u32 OSModuleID;
typedef struct OSModuleQueue OSModuleQueue;
typedef struct OSModuleLink OSModuleLink;
typedef struct OSModuleInfo OSModuleInfo;
typedef struct OSSectionInfo OSSectionInfo;
typedef struct OSImportInfo OSImportInfo;
typedef struct OSRel OSRel;

struct OSModuleQueue {
  OSModuleInfo* head;
  OSModuleInfo* tail;
};

struct OSModuleLink {
  OSModuleInfo* next;
  OSModuleInfo* prev;
};

struct OSModuleInfo {
  OSModuleID id;         // unique identifier for the module
  OSModuleLink link;     // doubly linked list of modules
  u32 numSections;       // # of sections
  u32 sectionInfoOffset; // offset to section info table
  u32 nameOffset;        // offset to module name
  u32 nameSize;          // size of module name
  u32 version;           // version number
};

struct OSModuleHeader {
  // CAUTION: info must be the 1st member
  OSModuleInfo info;

  // OS_MODULE_VERSION == 1
  u32 bssSize; // total size of bss sections in bytes
  u32 relOffset;
  u32 impOffset;
  u32 impSize;          // size in bytes
  u8 prologSection;     // section # for prolog function
  u8 epilogSection;     // section # for epilog function
  u8 unresolvedSection; // section # for unresolved function
  u8 bssSection;        // section # for bss section (set at run-time)
  u32 prolog;           // prolog function offset
  u32 epilog;           // epilog function offset
  u32 unresolved;       // unresolved function offset

  // OS_MODULE_VERSION == 2
  u32 align;    // module alignment constraint
  u32 bssAlign; // bss alignment constraint

  // OS_MODULE_VERSION == 3
};

#define OSGetSectionInfo(module) ((OSSectionInfo*)(((OSModuleInfo*)(module))->sectionInfoOffset))

struct OSSectionInfo {
  u32 offset;
  u32 size;
};

// OSSectionInfo.offset bit
#define OS_SECTIONINFO_EXEC 0x1
#define OS_SECTIONINFO_OFFSET(offset) ((offset) & ~0x1)

struct OSImportInfo {
  OSModuleID id; // external module id
  u32 offset;    // offset to OSRel instructions
};

struct OSRel {
  u16 offset; // byte offset from the previous entry
  u8 type;
  u8 section;
  u32 addend;
};

#define R_DOLPHIN_NOP 201     //  C9h current offset += OSRel.offset
#define R_DOLPHIN_SECTION 202 //  CAh current section = OSRel.section
#define R_DOLPHIN_END 203     //  CBh
#define R_DOLPHIN_MRKREF 204  //  CCh

void OSSetStringTable(const void* stringTable);
BOOL OSLink(OSModuleInfo* newModule, void* bss);
BOOL OSUnlink(OSModuleInfo* oldModule);

OSModuleInfo* OSSearchModule(void* ptr, u32* section, u32* offset);

// debugger notification
void OSNotifyLink(OSModuleInfo* module);
void OSNotifyUnlink(OSModuleInfo* module);

struct OSMutex {
  OSThreadQueue queue;
  OSThread* thread; // the current owner
  s32 count;        // lock count
  OSMutexLink link; // for OSThread.queueMutex
};

struct OSCond {
  OSThreadQueue queue;
};

void OSInitMutex(OSMutex* mutex);
void OSLockMutex(OSMutex* mutex);
void OSUnlockMutex(OSMutex* mutex);
BOOL OSTryLockMutex(OSMutex* mutex);
void OSInitCond(OSCond* cond);
void OSWaitCond(OSCond* cond, OSMutex* mutex);
void OSSignalCond(OSCond* cond);

#define OS_RESETCODE_RESTART 0x80000000
#define OS_RESETCODE_SYSTEM 0x40000000

#define OS_RESETCODE_EXEC 0xC0000000
#define OS_RESETCODE_NETCONFIG 0xC0010000

#define OS_RESET_TIMEOUT OSMillisecondsToTicks(1000)

#define OS_RESET_RESTART 0
#define OS_RESET_HOTRESET 1
#define OS_RESET_SHUTDOWN 2

#define OS_RESET_PRIO_SO 110
#define OS_RESET_PRIO_IP 111
#define OS_RESET_PRIO_CARD 127
#define OS_RESET_PRIO_PAD 127
#define OS_RESET_PRIO_GX 127
#define OS_RESET_PRIO_ALARM 4294967295

typedef BOOL (*OSResetFunction)(BOOL final);
typedef struct OSResetFunctionInfo OSResetFunctionInfo;

struct OSResetFunctionInfo {
  // public
  OSResetFunction func;
  u32 priority;

  // private
  OSResetFunctionInfo* next;
  OSResetFunctionInfo* prev;
};

u32 OSGetResetCode(void);

typedef void (*OSResetCallback)(void);

BOOL OSGetResetButtonState(void);

BOOL OSGetResetSwitchState(void);
OSResetCallback OSSetResetCallback(OSResetCallback callback);

#define SI_MAX_CHAN 4
#define SI_MAX_COMCSR_INLNGTH 128
#define SI_MAX_COMCSR_OUTLNGTH 128
#define SI_ERROR_UNDER_RUN 0x0001
#define SI_ERROR_OVER_RUN 0x0002
#define SI_ERROR_COLLISION 0x0004
#define SI_ERROR_NO_RESPONSE 0x0008
#define SI_ERROR_WRST 0x0010
#define SI_ERROR_RDST 0x0020
#define SI_ERROR_UNKNOWN 0x0040
#define SI_ERROR_BUSY 0x0080
#define SI_CHAN0 0
#define SI_CHAN1 1
#define SI_CHAN2 2
#define SI_CHAN3 3
#define SI_CHAN0_BIT 0x80000000
#define SI_CHAN1_BIT 0x40000000
#define SI_CHAN2_BIT 0x20000000
#define SI_CHAN3_BIT 0x10000000
#define SI_CHAN_BIT(chan) (SI_CHAN0_BIT >> (chan))
#define SI_TYPE_MASK 0x18000000u
#define SI_TYPE_N64 0x00000000u
#define SI_TYPE_DOLPHIN 0x08000000u
#define SI_TYPE_GC SI_TYPE_DOLPHIN
#define SI_GC_WIRELESS 0x80000000
#define SI_GC_NOMOTOR 0x20000000
#define SI_GC_STANDARD 0x01000000
#define SI_WIRELESS_RECEIVED 0x40000000
#define SI_WIRELESS_IR 0x04000000
#define SI_WIRELESS_STATE 0x02000000
#define SI_WIRELESS_ORIGIN 0x00200000
#define SI_WIRELESS_FIX_ID 0x00100000
#define SI_WIRELESS_TYPE 0x000f0000
#define SI_WIRELESS_LITE_MASK 0x000c0000
#define SI_WIRELESS_LITE 0x00040000
#define SI_WIRELESS_CONT_MASK 0x00080000
#define SI_WIRELESS_CONT 0x00000000
#define SI_WIRELESS_ID 0x00c0ff00
#define SI_WIRELESS_TYPE_ID (SI_WIRELESS_TYPE | SI_WIRELESS_ID)
#define SI_N64_CONTROLLER (SI_TYPE_N64 | 0x05000000)
#define SI_N64_MIC (SI_TYPE_N64 | 0x00010000)
#define SI_N64_KEYBOARD (SI_TYPE_N64 | 0x00020000)
#define SI_N64_MOUSE (SI_TYPE_N64 | 0x02000000)
#define SI_GBA (SI_TYPE_N64 | 0x00040000)
#define SI_GC_CONTROLLER (SI_TYPE_GC | SI_GC_STANDARD)
#define SI_GC_RECEIVER (SI_TYPE_GC | SI_GC_WIRELESS)
#define SI_GC_WAVEBIRD                                                                             \
  (SI_TYPE_GC | SI_GC_WIRELESS | SI_GC_STANDARD | SI_WIRELESS_STATE | SI_WIRELESS_FIX_ID)
#define SI_GC_KEYBOARD (SI_TYPE_GC | 0x00200000)
#define SI_GC_STEERING (SI_TYPE_GC | 0x00000000)

u32 SIProbe(s32 chan);
char* SIGetTypeString(u32 type);
void SIRefreshSamplingRate(void);
void SISetSamplingRate(u32 msec);

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

typedef void (*DVDCBCallback)(s32 result, DVDCommandBlock* block);

struct DVDCommandBlock {
  DVDCommandBlock* next;
  DVDCommandBlock* prev;
  u32 command;
  s32 state;
  u32 offset;
  u32 length;
  void* addr;
  u32 currTransferSize;
  u32 transferredSize;
  DVDDiskID* id;
  DVDCBCallback callback;
  void* userData;
};

typedef struct DVDFileInfo DVDFileInfo;

typedef void (*DVDCallback)(s32 result, DVDFileInfo* fileInfo);

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
  char* name;
} DVDDirEntry;

void DVDInit();
BOOL DVDClose(DVDFileInfo* f);
BOOL DVDSetAutoFatalMessaging(BOOL);
void DVDReset();
s32 DVDCancel(DVDCommandBlock* block);
BOOL DVDOpen(char* fileName, DVDFileInfo* fileInfo);
BOOL DVDFastOpen(s32 entrynum, DVDFileInfo* fileInfo);
s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block);
BOOL DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDCancel(DVDCommandBlock* block);
BOOL DVDCancelAllAsync(DVDCBCallback callback);
s32 DVDCancelAll(void);
BOOL DVDPrepareStreamAsync(DVDFileInfo* fInfo, u32 length, u32 offset, DVDCallback callback);
s32 DVDPrepareStream(DVDFileInfo* fInfo, u32 length, u32 offset);

BOOL DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDCancelStream(DVDCommandBlock* block);

BOOL DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDStopStreamAtEnd(DVDCommandBlock* block);

BOOL DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDGetStreamErrorStatus(DVDCommandBlock* block);

BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback);
s32 DVDGetStreamPlayAddr(DVDCommandBlock* block);

s32 DVDGetDriveStatus();

s32 DVDConvertPathToEntrynum(char* pathPtr);

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                      DVDCallback callback, s32 prio);
               
BOOL DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio);

			   
#define DVDReadAsync(fileInfo, addr, length, offset, callback)                                     \
  DVDReadAsyncPrio((fileInfo), (addr), (length), (offset), (callback), 2)
#define DVDRead(fileInfo, addr, length, offset)                 \
                         DVDReadPrio((fileInfo), (addr), (length), (offset), 2)
                         
#define DVDSeekAsync(fileInfo, offset, callback)                                                   \
  DVDSeekAsyncPrio((fileInfo), (offset), (callback), 2)

extern u32 __PADFixBits;

#define PAD_SPEC_0 0
#define PAD_SPEC_1 1
#define PAD_SPEC_2 2
#define PAD_SPEC_3 3
#define PAD_SPEC_4 4
#define PAD_SPEC_5 5

#define PAD_CHAN0 0
#define PAD_CHAN1 1
#define PAD_CHAN2 2
#define PAD_CHAN3 3
#define PAD_CHANMAX 4

#define PAD_MOTOR_STOP 0
#define PAD_MOTOR_RUMBLE 1
#define PAD_MOTOR_STOP_HARD 2

#define PAD_ERR_NONE 0
#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NOT_READY -2
#define PAD_ERR_TRANSFER -3

#define PAD_BUTTON_LEFT 0x0001
#define PAD_BUTTON_RIGHT 0x0002
#define PAD_BUTTON_DOWN 0x0004
#define PAD_BUTTON_UP 0x0008
#define PAD_TRIGGER_Z 0x0010
#define PAD_TRIGGER_R 0x0020
#define PAD_TRIGGER_L 0x0040
#define PAD_BUTTON_A 0x0100
#define PAD_BUTTON_B 0x0200
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800
#define PAD_BUTTON_MENU 0x1000
#define PAD_BUTTON_START 0x1000

#define PAD_CHAN0_BIT 0x80000000
#define PAD_CHAN1_BIT 0x40000000
#define PAD_CHAN2_BIT 0x20000000
#define PAD_CHAN3_BIT 0x10000000

#define PADButtonDown(buttonLast, button) ((((buttonLast) ^ (button)) & (button)))

#define PADButtonUp(buttonLast, button) ((((buttonLast) ^ (button)) & (buttonLast)))


typedef void (*PADSamplingCallback)(void);

typedef struct PADStatus {
  u16 button;
  s8 stickX;
  s8 stickY;
  s8 substickX;
  s8 substickY;
  u8 triggerL;
  u8 triggerR;
  u8 analogA;
  u8 analogB;
  s8 err;
} PADStatus;

BOOL PADInit();
u32 PADRead(PADStatus* status);
BOOL PADReset(u32 mask);
BOOL PADRecalibrate(u32 mask);
void PADClamp(PADStatus* status);
void PADClampCircle(PADStatus* status);
void PADControlMotor(s32 chan, u32 cmd);
void PADSetSpec(u32 spec);
void PADControlAllMotors(const u32* cmdArr);
void PADSetAnalogMode(u32 mode);
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback);


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




#define GEKKO

#define MTX_USE_PS

#define MTX_PTR_OFFSET 3

#define MTX44_PTR_OFFSET 4

typedef struct {

  u32 numMtx;
  MtxPtr stackBase;
  MtxPtr stackPtr;

} MtxStack, *MtxStackPtr;

#define MTXDegToRad(a) ((a)*0.01745329252f)
#define MTXRadToDeg(a) ((a)*57.29577951f)
#define MTXRowCol(m, r, c) ((m)[(r)][(c)])

void C_MTXIdentity(Mtx m);
void C_MTXCopy(const Mtx src, Mtx dst);
void C_MTXConcat(const Mtx a, const Mtx b, Mtx ab);
void C_MTXConcatArray(const Mtx a, const Mtx* srcBase, Mtx* dstBase, u32 count);
void C_MTXTranspose(const Mtx src, Mtx xPose);
u32 C_MTXInverse(const Mtx src, Mtx inv);
u32 C_MTXInvXpose(const Mtx src, Mtx invX);

void PSMTXIdentity(Mtx m);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXConcatArray(const Mtx a, const Mtx* srcBase, Mtx* dstBase, u32 count);
void PSMTXTranspose(const Mtx src, Mtx xPose);
u32 PSMTXInverse(const Mtx src, Mtx inv);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);

#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXConcatArray PSMTXConcatArray
#define MTXTranspose PSMTXTranspose
#define MTXInverse PSMTXInverse
#define MTXInvXpose PSMTXInvXpose


void C_MTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void C_MTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void C_MTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void C_MTXMultVecArraySR(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);


void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecArraySR(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);


#define MTXMultVec PSMTXMultVec
#define MTXMultVecArray PSMTXMultVecArray
#define MTXMultVecSR PSMTXMultVecSR
#define MTXMultVecArraySR PSMTXMultVecArraySR


void C_MTXQuat(Mtx m, const Quaternion* q);
void C_MTXReflect(Mtx m, const Vec* p, const Vec* n);

void C_MTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void C_MTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void C_MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void C_MTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);

void C_MTXRotRad(Mtx m, char axis, f32 rad);
void C_MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void C_MTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);


void PSMTXQuat(Mtx m, const Quaternion* q);
void PSMTXReflect(Mtx m, const Vec* p, const Vec* n);

void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);

void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);



#define MTXQuat PSMTXQuat
#define MTXReflect PSMTXReflect
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotAxisRad

#define MTXRotDeg(m, axis, deg) PSMTXRotRad(m, axis, MTXDegToRad(deg))
#define MTXRotAxisDeg(m, axis, deg) PSMTXRotAxisRad(m, axis, MTXDegToRad(deg))

void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target);

#define MTXLookAt C_MTXLookAt

void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#define MTXFrustum C_MTXFrustum
#define MTXPerspective C_MTXPerspective
#define MTXOrtho C_MTXOrtho

void C_MTXLightFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 scaleS, f32 scaleT, f32 transS,
                       f32 transT);

void C_MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scaleS, f32 scaleT, f32 transS,
                           f32 transT);

void C_MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 scaleS, f32 scaleT, f32 transS,
                     f32 transT);

#define MTXLightFrustum C_MTXLightFrustum
#define MTXLightPerspective C_MTXLightPerspective
#define MTXLightOrtho C_MTXLightOrtho

void C_VECAdd(const Vec* a, const Vec* b, Vec* ab);
void C_VECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void C_VECScale(const Vec* src, Vec* dst, f32 scale);
void C_VECNormalize(const Vec* src, Vec* unit);
f32 C_VECSquareMag(const Vec* v);
f32 C_VECMag(const Vec* v);
f32 C_VECDotProduct(const Vec* a, const Vec* b);
void C_VECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 C_VECSquareDistance(const Vec* a, const Vec* b);
f32 C_VECDistance(const Vec* a, const Vec* b);
void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);
void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);

void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECNormalize(const Vec* src, Vec* unit);
f32 PSVECSquareMag(const Vec* v);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);


// TODO

#define VECAdd PSVECAdd
#define VECSubtract PSVECSubtract
#define VECScale PSVECScale
#define VECNormalize PSVECNormalize
#define VECSquareMag PSVECSquareMag
#define VECMag PSVECMag
#define VECDotProduct PSVECDotProduct
#define VECCrossProduct PSVECCrossProduct
#define VECSquareDistance PSVECSquareDistance
#define VECDistance PSVECDistance


#define VECReflect C_VECReflect
#define VECHalfAngle C_VECHalfAngle

void C_QUATAdd(const Quaternion* p, const Quaternion* q, Quaternion* r);
void C_QUATSubtract(const Quaternion* p, const Quaternion* q, Quaternion* r);
void C_QUATMultiply(const Quaternion* p, const Quaternion* q, Quaternion* pq);
void C_QUATDivide(const Quaternion* p, const Quaternion* q, Quaternion* r);
void C_QUATScale(const Quaternion* q, Quaternion* r, f32 scale);
f32 C_QUATDotProduct(const Quaternion* p, const Quaternion* q);
void C_QUATNormalize(const Quaternion* src, Quaternion* unit);
void C_QUATInverse(const Quaternion* src, Quaternion* inv);
void C_QUATExp(const Quaternion* q, Quaternion* r);
void C_QUATLogN(const Quaternion* q, Quaternion* r);

void C_QUATMakeClosest(const Quaternion* q, const Quaternion* qto, Quaternion* r);
void C_QUATRotAxisRad(Quaternion* r, const Vec* axis, f32 rad);
void C_QUATMtx(Quaternion* r, const Mtx m);

void C_QUATLerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);
void C_QUATSlerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);
void C_QUATSquad(const Quaternion* p, const Quaternion* a, const Quaternion* b, const Quaternion* q,
                 Quaternion* r, f32 t);
void C_QUATCompA(const Quaternion* qprev, const Quaternion* q, const Quaternion* qnext,
                 Quaternion* a);


void PSQUATAdd(const Quaternion* p, const Quaternion* q, Quaternion* r);
void PSQUATSubtract(const Quaternion* p, const Quaternion* q, Quaternion* r);
void PSQUATMultiply(const Quaternion* p, const Quaternion* q, Quaternion* pq);
void PSQUATDivide(const Quaternion* p, const Quaternion* q, Quaternion* r);
void PSQUATScale(const Quaternion* q, Quaternion* r, f32 scale);
f32 PSQUATDotProduct(const Quaternion* p, const Quaternion* q);
void PSQUATNormalize(const Quaternion* src, Quaternion* unit);
void PSQUATInverse(const Quaternion* src, Quaternion* inv);



#define QUATAdd PSQUATAdd
#define QUATSubtract PSQUATSubtract
#define QUATMultiply PSQUATMultiply
#define QUATDivide PSQUATDivide
#define QUATScale PSQUATScale
#define QUATDotProduct PSQUATDotProduct
#define QUATNormalize PSQUATNormalize
#define QUATInverse PSQUATInverse

#define QUATExp C_QUATExp
#define QUATLogN C_QUATLogN
#define QUATMakeClosest C_QUATMakeClosest
#define QUATRotAxisRad C_QUATRotAxisRad
#define QUATMtx C_QUATMtx
#define QUATLerp C_QUATLerp
#define QUATSlerp C_QUATSlerp
#define QUATSquad C_QUATSquad
#define QUATCompA C_QUATCompA

void PSMTXReorder(const Mtx src, ROMtx dest);
void PSMTXROMultVecArray(const ROMtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXROSkin2VecArray(const ROMtx m0, const ROMtx m1, const f32* wtBase, const Vec* srcBase,
                          Vec* dstBase, u32 count);
void PSMTXMultS16VecArray(const Mtx m, const S16Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXROMultS16VecArray(const ROMtx m, const S16Vec* srcBase, Vec* dstBase, u32 count);

void MTXInitStack(MtxStack* sPtr, u32 numMtx);
MtxPtr MTXPush(MtxStack* sPtr, const Mtx m);
MtxPtr MTXPushFwd(MtxStack* sPtr, const Mtx m);
MtxPtr MTXPushInv(MtxStack* sPtr, const Mtx m);
MtxPtr MTXPushInvXpose(MtxStack* sPtr, const Mtx m);
MtxPtr MTXPop(MtxStack* sPtr);
MtxPtr MTXGetStackPtr(const MtxStack* sPtr);

#define MTXAllocStack(sPtr, numMtx)                                                                \
  (((MtxStackPtr)(sPtr))->stackBase = (MtxPtr)OSAlloc(((numMtx) * sizeof(Mtx))))

#define MTXFreeStack(sPtr) (OSFree((void*)(((MtxStackPtr)(sPtr))->stackBase)))




/* end "dolphin/mtx.h" */
/* "include\dolphin.h" line 10 "dolphin/gx.h" */
/* end "dolphin/gx.h" */
/* "include\dolphin.h" line 11 "dolphin/vi.h" */

#define _DOLPHIN_VI

/* "include\dolphin\vi.h" line 3 "dolphin/gx/GXStruct.h" */
/* end "dolphin/gx/GXStruct.h" */
/* "include\dolphin\vi.h" line 4 "dolphin/vifuncs.h" */

#define _DOLPHIN_VIFUNCS

/* "include\dolphin\vifuncs.h" line 3 "dolphin/types.h" */
/* end "dolphin/types.h" */

/* "include\dolphin\vifuncs.h" line 5 "dolphin/vitypes.h" */
/* end "dolphin/vitypes.h" */


u32 VIGetNextField(void);
u32 VIGetRetraceCount();
VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback);
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback);
void __VIGetCurrentPosition(s16* x, s16* y);
u32 VIGetDTVStatus(void);


void VIInit(void);
void VIConfigure(const GXRenderModeObj* rm);
void VIFlush(void);
u32 VIGetTvFormat(void);
void VISetNextFrameBuffer(void* fb);
void VIWaitForRetrace(void);
void VISetBlack(BOOL black);




/* end "dolphin/vi.h" */
/* "include\dolphin.h" line 12 "dolphin/ai.h" */

#define _DOLPHIN_AI

/* "include\dolphin\ai.h" line 3 "types.h" */
/* end "types.h" */


typedef void (*AISCallback)(u32 count);
typedef void (*AIDCallback)();

AIDCallback AIRegisterDMACallback(AIDCallback callback);
void AIInitDMA(u32 start_addr, u32 length);
BOOL AIGetDMAEnableFlag();
void AIStartDMA();
void AIStopDMA();
u32 AIGetDMABytesLeft();
u32 AIGetDMAStartAddr();
u32 AIGetDMALength();
u32 AIGetDSPSampleRate();
void AISetDSPSampleRate(u32 rate);
AISCallback AIRegisterStreamCallback(AISCallback callback);
u32 AIGetStreamSampleCount();
void AIResetStreamSampleCount();
void AISetStreamTrigger(u32 trigger);
u32 AIGetStreamTrigger();
void AISetStreamPlayState(u32 state);
u32 AIGetStreamPlayState();
void AISetStreamSampleRate(u32 rate);
u32 AIGetStreamSampleRate();
void AISetStreamVolLeft(u8 vol);
void AISetStreamVolRight(u8 vol);
u8 AIGetStreamVolLeft();
u8 AIGetStreamVolRight();
void AIInit(u8* stack);
BOOL AICheckInit();
void AIReset();


/* end "dolphin/ai.h" */
/* "include\dolphin.h" line 13 "dolphin/ar.h" */

#define _DOLPHIN_AR

/* "include\dolphin\ar.h" line 3 "types.h" */
/* end "types.h" */


#define AR_STACK_INDEX_ENTRY_SIZE sizeof(u32)

#define ARAM_DIR_MRAM_TO_ARAM 0x00
#define ARAM_DIR_ARAM_TO_MRAM 0x01

#define AR_CLEAR_INTERNAL_ALL 0x00
#define AR_CLEAR_INTERNAL_USER 0x01
#define AR_CLEAR_EXPANSION 0x02

typedef void (*ARCallback)(void);

ARCallback ARRegisterDMACallback(ARCallback callback);
u32 ARGetDMAStatus(void);
void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);
u32 ARInit(u32* stack_index_addr, u32 num_entries);
u32 ARGetBaseAddress(void);
BOOL ARCheckInit(void);
void ARReset(void);
u32 ARAlloc(u32 length);
u32 ARFree(u32* length);
u32 ARGetSize(void);
u32 ARGetInternalSize(void);
void ARSetSize(void);
void ARClear(u32 flag);

void __ARClearInterrupt(void);
u16 __ARGetInterruptStatus(void);

#define ARStartDMARead(mmem, aram, len) ARStartDMA(ARAM_DIR_ARAM_TO_MRAM, mmem, aram, len)
#define ARStartDMAWrite(mmem, aram, len) ARStartDMA(ARAM_DIR_MRAM_TO_ARAM, mmem, aram, len)



/* end "dolphin/ar.h" */
/* "include\dolphin.h" line 14 "dolphin/arq.h" */

#define _DOLPHIN_ARQ

/* "include\dolphin\arq.h" line 3 "types.h" */
/* end "types.h" */

/* "include\dolphin\arq.h" line 5 "dolphin/ar.h" */
/* end "dolphin/ar.h" */



/* "include\dolphin\arq.h" line 11 "dolphin/ar.h" */
/* end "dolphin/ar.h" */

#define ARQ_DMA_ALIGNMENT 32
#define ARQ_CHUNK_SIZE_DEFAULT 4096

#define ARQ_TYPE_MRAM_TO_ARAM ARAM_DIR_MRAM_TO_ARAM
#define ARQ_TYPE_ARAM_TO_MRAM ARAM_DIR_ARAM_TO_MRAM

#define ARQ_PRIORITY_LOW 0
#define ARQ_PRIORITY_HIGH 1

typedef void (*ARQCallback)(u32 pointerToARQRequest);

typedef struct ARQRequest {

  struct ARQRequest* next;
  u32 owner;
  u32 type;
  u32 priority;
  u32 source;
  u32 dest;
  u32 length;
  ARQCallback callback;

} ARQRequest;

void ARQInit(void);
void ARQReset(void);
void ARQPostRequest(ARQRequest* task, u32 owner, u32 type, u32 priority, u32 source, u32 dest,
                    u32 length, ARQCallback callback);
void ARQRemoveRequest(ARQRequest* task);
void ARQRemoveOwnerRequest(u32 owner);
void ARQFlushQueue(void);
void ARQSetChunkSize(u32 size);
u32 ARQGetChunkSize(void);
BOOL ARQCheckInit(void);



/* end "dolphin/arq.h" */
/* "include\dolphin.h" line 15 "dolphin/dsp.h" */

#define _DOLPHIN_DSP

/* "include\dolphin\dsp.h" line 3 "types.h" */
/* end "types.h" */
/* "include\dolphin\dsp.h" line 4 "dolphin/os.h" */
/* end "dolphin/os.h" */


#define DSP_TASK_FLAG_CLEARALL 0x00000000
#define DSP_TASK_FLAG_ATTACHED 0x00000001
#define DSP_TASK_FLAG_CANCEL 0x00000002

#define DSP_TASK_STATE_INIT 0
#define DSP_TASK_STATE_RUN 1
#define DSP_TASK_STATE_YIELD 2
#define DSP_TASK_STATE_DONE 3

typedef void (*DSPCallback)(void* task);

typedef struct STRUCT_DSP_TASK {
  vu32 state;
  vu32 priority;
  vu32 flags;
  u16* iram_mmem_addr;
  u32 iram_length;
  u32 iram_addr;

  u16* dram_mmem_addr;
  u32 dram_length;
  u32 dram_addr;

  u16 dsp_init_vector;
  u16 dsp_resume_vector;

  DSPCallback init_cb;
  DSPCallback res_cb;
  DSPCallback done_cb;
  DSPCallback req_cb;

  struct STRUCT_DSP_TASK* next;
  struct STRUCT_DSP_TASK* prev;

  OSTime t_context;
  OSTime t_task;

} DSPTaskInfo;

void DSPInit();
void DSPReset();
void DSPHalt();
void DSPSendMailToDSP(u32 mail);
u32 DSPCheckMailToDSP();
u32 DSPCheckMailFromDSP();
u32 DSPGetDMAStatus();

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
void __DSP_boot_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);


#define CARD_ENCODE_ANSI 0u
#define CARD_ENCODE_SJIS 1u

/* Sizes */
#define CARD_WORKAREA_SIZE (5 * 8 * 1024)
#define CARD_READ_SIZE 512
#define CARD_MAX_FILE 127
#define CARD_COMMENT_SIZE 64
#define CARD_FILENAME_MAX 32
#define CARD_ICON_MAX 8
#define CARD_ICON_WIDTH 32
#define CARD_ICON_HEIGHT 32
#define CARD_BANNER_WIDTH 96
#define CARD_BANNER_HEIGHT 32

/* Icon animation */
#define CARD_MODE_NORMAL 0
#define CARD_MODE_FAST 1

#define CARDGetBannerFormat(stat) (((stat)->bannerFormat) & CARD_STAT_BANNER_MASK)
#define CARDGetIconAnim(stat) (((stat)->bannerFormat) & CARD_STAT_ANIM_MASK)
#define CARDGetIconFormat(stat, n) (((stat)->iconFormat >> (2 * (n))) & CARD_STAT_ICON_MASK)
#define CARDGetIconSpeed(stat, n) (((stat)->iconSpeed >> (2 * (n))) & CARD_STAT_SPEED_MASK)
#define CARDSetBannerFormat(stat, f)                                                               \
  ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_BANNER_MASK) | (f)))
#define CARDSetIconAnim(stat, f)                                                                   \
  ((stat)->bannerFormat = (u8)(((stat)->bannerFormat & ~CARD_STAT_ANIM_MASK) | (f)))
#define CARDSetIconFormat(stat, n, f)                                                              \
  ((stat)->iconFormat =                                                                            \
       (u16)(((stat)->iconFormat & ~(CARD_STAT_ICON_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconSpeed(stat, n, f)                                                               \
  ((stat)->iconSpeed =                                                                             \
       (u16)(((stat)->iconSpeed & ~(CARD_STAT_SPEED_MASK << (2 * (n)))) | ((f) << (2 * (n)))))
#define CARDSetIconAddress(stat, addr) ((stat)->iconAddr = (u32)(addr))
#define CARDSetCommentAddress(stat, addr) ((stat)->commentAddr = (u32)(addr))
#define CARDGetFileNo(fileInfo) ((fileInfo)->fileNo)

#define CARD_RESULT_UNLOCKED 1
#define CARD_RESULT_READY 0
#define CARD_RESULT_BUSY -1
#define CARD_RESULT_WRONGDEVICE -2
#define CARD_RESULT_NOCARD -3
#define CARD_RESULT_NOFILE -4
#define CARD_RESULT_IOERROR -5
#define CARD_RESULT_BROKEN -6
#define CARD_RESULT_EXIST -7
#define CARD_RESULT_NOENT -8
#define CARD_RESULT_INSSPACE -9
#define CARD_RESULT_NOPERM -10
#define CARD_RESULT_LIMIT -11
#define CARD_RESULT_NAMETOOLONG -12
#define CARD_RESULT_ENCODING -13
#define CARD_RESULT_CANCELED -14
#define CARD_RESULT_FATAL_ERROR -128

#define CARD_STAT_ICON_NONE 0
#define CARD_STAT_ICON_C8 1
#define CARD_STAT_ICON_RGB5A3 2
#define CARD_STAT_ICON_MASK 3

#define CARD_STAT_BANNER_NONE 0
#define CARD_STAT_BANNER_C8 1
#define CARD_STAT_BANNER_RGB5A3 2
#define CARD_STAT_BANNER_MASK 3

#define CARD_STAT_ANIM_LOOP 0x00
#define CARD_STAT_ANIM_BOUNCE 0x04
#define CARD_STAT_ANIM_MASK 0x04

#define CARD_STAT_SPEED_END 0
#define CARD_STAT_SPEED_FAST 1
#define CARD_STAT_SPEED_MIDDLE 2
#define CARD_STAT_SPEED_SLOW 3
#define CARD_STAT_SPEED_MASK 3

#define CARD_ATTR_PUBLIC 0x04u
#define CARD_ATTR_NO_COPY 0x08u
#define CARD_ATTR_NO_MOVE 0x10u
#define CARD_ATTR_GLOBAL 0x20u
#define CARD_ATTR_COMPANY 0x40u

typedef struct CARDFileInfo {
  s32 chan;
  s32 fileNo;

  s32 offset;
  s32 length;
  u16 iBlock;
  u16 __padding;
} CARDFileInfo;

typedef struct CARDStat {
  char fileName[CARD_FILENAME_MAX];
  u32 length;
  u32 time; // seconds since 01/01/2000 midnight
  u8 gameName[4];
  u8 company[2];

  u8 bannerFormat;
  u8 __padding;
  u32 iconAddr; // offset to the banner, bannerTlut, icon, iconTlut data set.
  u16 iconFormat;
  u16 iconSpeed;
  u32 commentAddr; // offset to the pair of 32 byte character strings.

  u32 offsetBanner;
  u32 offsetBannerTlut;
  u32 offsetIcon[CARD_ICON_MAX];
  u32 offsetIconTlut;
  u32 offsetData;
} CARDStat;

typedef void (*CARDCallback)(s32 chan, s32 result);

void CARDInit(void);
BOOL CARDGetFastMode(void);
BOOL CARDSetFastMode(BOOL enable);

s32 CARDCheck(s32 chan);
s32 CARDCheckAsync(s32 chan, CARDCallback callback);
s32 CARDCheckEx(s32 chan, s32* xferBytes);
s32 CARDCheckExAsync(s32 chan, s32* xferBytes, CARDCallback callback);
s32 CARDCreate(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo);
s32 CARDCreateAsync(s32 chan, const char* fileName, u32 size, CARDFileInfo* fileInfo,
                    CARDCallback callback);
s32 CARDDelete(s32 chan, const char* fileName);
s32 CARDDeleteAsync(s32 chan, const char* fileName, CARDCallback callback);
s32 CARDFastDelete(s32 chan, s32 fileNo);
s32 CARDFastDeleteAsync(s32 chan, s32 fileNo, CARDCallback callback);
s32 CARDFastOpen(s32 chan, s32 fileNo, CARDFileInfo* fileInfo);
s32 CARDFormat(s32 chan);
s32 CARDFormatAsync(s32 chan, CARDCallback callback);
s32 CARDFreeBlocks(s32 chan, s32* byteNotUsed, s32* filesNotUsed);
s32 CARDGetAttributes(s32 chan, s32 fileNo, u8* attr);
s32 CARDGetEncoding(s32 chan, u16* encode);
s32 CARDGetMemSize(s32 chan, u16* size);
s32 CARDGetResultCode(s32 chan);
s32 CARDGetSectorSize(s32 chan, u32* size);
s32 CARDGetSerialNo(s32 chan, u64* serialNo);
s32 CARDGetStatus(s32 chan, s32 fileNo, CARDStat* stat);
s32 CARDGetXferredBytes(s32 chan);
s32 CARDMount(s32 chan, void* workArea, CARDCallback detachCallback);
s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback,
                   CARDCallback attachCallback);
s32 CARDOpen(s32 chan, const char* fileName, CARDFileInfo* fileInfo);
BOOL CARDProbe(s32 chan);
s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize);
s32 CARDRename(s32 chan, const char* oldName, const char* newName);
s32 CARDRenameAsync(s32 chan, const char* oldName, const char* newName, CARDCallback callback);
s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback);
s32 CARDSetAttributes(s32 chan, s32 fileNo, u8 attr);
s32 CARDSetStatus(s32 chan, s32 fileNo, CARDStat* stat);
s32 CARDSetStatusAsync(s32 chan, s32 fileNo, CARDStat* stat, CARDCallback callback);
s32 CARDUnmount(s32 chan);
s32 CARDGetCurrentMode(s32 chan, u32* mode);
s32 CARDCancel(CARDFileInfo* fileInfo);
s32 CARDClose(CARDFileInfo* fileInfo);
s32 CARDRead(CARDFileInfo* fileInfo, void* addr, s32 length, s32 offset);
s32 CARDReadAsync(CARDFileInfo* fileInfo, void* addr, s32 length, s32 offset,
                  CARDCallback callback);
s32 CARDWrite(CARDFileInfo* fileInfo, const void* addr, s32 length, s32 offset);
s32 CARDWriteAsync(CARDFileInfo* fileInfo, const void* addr, s32 length, s32 offset,
                   CARDCallback callback);


typedef struct jump_buf {
    u32 lr;
    u32 cr;
    u32 sp;
    u32 r2;
    u32 pad;
    u32 regs[19];
    double flt_regs[19];
} jmp_buf;

int gcsetjmp(jmp_buf *jump);
int gclongjmp(jmp_buf *jump, int status);


/* end "game/jmp.h" */
/* "include\game\process.h" line 4 "dolphin/types.h" */
/* end "dolphin/types.h" */

#define PROCESS_STAT_PAUSE 0x1
#define PROCESS_STAT_UPAUSE 0x2
#define PROCESS_STAT_PAUSE_EN 0x4
#define PROCESS_STAT_UPAUSE_EN 0x8

typedef struct process {
    struct process *next;
    struct process *prev;
    struct process *child;
    struct process *parent;
    struct process *next_child;
    struct process *first_child;
    void *heap;
    u16 exec;
    u16 stat;
    u16 prio;
    int sleep_time;
    u32 base_sp;
    jmp_buf jump;
    void (*dtor)(void);
    void *user_data;
} Process;

void HuPrcInit(void);
void HuPrcEnd(void);
Process *HuPrcCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size);
void HuPrcChildLink(Process *parent, Process *child);
void HuPrcChildUnlink(Process *process);
Process *HuPrcChildCreate(void (*func)(void), u16 prio, u32 stack_size, s32 extra_size, Process *parent);
void HuPrcChildWatch(void);
Process *HuPrcCurrentGet(void);
int HuPrcKill(Process *process);
void HuPrcChildKill(Process *process);
void HuPrcSleep(int time);
void HuPrcVSleep();
void HuPrcWakeup(Process *process);
void HuPrcDestructorSet2(Process *process, void (*func)(void));
void HuPrcDestructorSet(void (*func)(void));
void HuPrcCall(int tick);
void *HuPrcMemAlloc(s32 size);
void HuPrcMemFree(void *ptr);
void HuPrcSetStat(Process *process, u16 value);
void HuPrcResetStat(Process *process, u16 value);
void HuPrcAllPause(int flag);
void HuPrcAllUPause(int flag);



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



typedef struct data_read_stat DataReadStat;

typedef struct file_list_entry {
    char *name;
    s32 file_id;
} FileListEntry;

void *HuDvdDataRead(char *path);
void **HuDvdDataReadMulti(char **paths);
void *HuDvdDataReadDirect(char *path, HeapID heap);
void *HuDvdDataFastRead(s32 entrynum);
void *HuDvdDataFastReadNum(s32 entrynum, s32 num);
void *HuDvdDataFastReadAsync(s32 entrynum, DataReadStat *stat);
void HuDvdDataClose(void *ptr);
void HuDvdErrorWatch();




#define OM_DLL_MAX 20

typedef enum {
    OVL_INVALID = -1,
/* "include\game\object.h" line 13 "ovl_table.h" */
OVL__MINI,
OVL_BOOT,
OVL_E3SETUP,
OVL_INST,
OVL_M300,
OVL_M302,
OVL_M303,
OVL_M330,
OVL_M333,
OVL_M401,
OVL_M402,
OVL_M403,
OVL_M404,
OVL_M405,
OVL_M406,
OVL_M407,
OVL_M408,
OVL_M409,
OVL_M410,
OVL_M411,
OVL_M412,
OVL_M413,
OVL_M414,
OVL_M415,
OVL_M416,
OVL_M417,
OVL_M418,
OVL_M419,
OVL_M420,
OVL_M421,
OVL_M422,
OVL_M423,
OVL_M424,
OVL_M425,
OVL_M426,
OVL_M427,
OVL_M428,
OVL_M429,
OVL_M430,
OVL_M431,
OVL_M432,
OVL_M433,
OVL_M434,
OVL_M435,
OVL_M436,
OVL_M437,
OVL_M438,
OVL_M439,
OVL_M440,
OVL_M441,
OVL_M442,
OVL_M443,
OVL_M444,
OVL_M445,
OVL_M446,
OVL_M447,
OVL_M448,
OVL_M449,
OVL_M450,
OVL_M451,
OVL_M453,
OVL_M455,
OVL_M456,
OVL_M457,
OVL_M458,
OVL_M459,
OVL_M460,
OVL_M461,
OVL_M462,
OVL_M463,
OVL_MENT,
OVL_MESS,
OVL_MGMODE,
OVL_MODELTEST,
OVL_MODESEL, 
OVL_MPEX, 
OVL_MSETUP, 
OVL_MSTORY2, 
OVL_MSTORY3, 
OVL_MSTORY4, 
OVL_MSTORY, 
OVL_NIS, 
OVL_OPTION, 
OVL_PRESENT, 
OVL_RESULT, 
OVL_SAF, 
OVL_SELMENU, 
OVL_STAFF, 
OVL_SUBCHRSEL,
OVL_W01, 
OVL_W02, 
OVL_W03, 
OVL_W04, 
OVL_W05, 
OVL_W06, 
OVL_W10, 
OVL_W20, 
OVL_W21, 
OVL_ZTAR, 
    OVL_COUNT
} OverlayID;

#define OM_STAT_DELETED 0x1
#define OM_STAT_DISABLED 0x2
#define OM_STAT_ACTIVE 0x4
#define OM_STAT_PAUSED 0x10
#define OM_STAT_NOPAUSE 0x20
#define OM_STAT_MODEL_PAUSED 0x100


#define OM_GET_WORK_PTR(object, type) ((type *)(&((object)->work[0])))
#define OM_GET_DATA_PTR(object, type) ((type *)(((object)->data)))

typedef void (*omObjFunc)(struct om_obj_data *);

typedef struct om_ovl_his_data {
    OverlayID overlay;
    int event;
    int stat;
} omOvlHisData;

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

typedef struct om_dll_data {
	char *name;
	OSModuleHeader *module;
	void *bss;
	s32 ret;
} omDllData;

void omMasterInit(int prio, FileListEntry *ovl_list, int ovl_count, OverlayID start_ovl);
void omOvlCallEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlGotoEx(OverlayID overlay, s16 arg2, int event, int stat);
void omOvlReturnEx(s16 level, s16 arg2);
void omOvlKill(s16 arg);
void omOvlHisChg(s32 level, OverlayID overlay, int event, int stat);
omOvlHisData *omOvlHisGet(s32 level);
Process *omInitObjMan(s16 max_objs, int prio);
void omDestroyObjMan(void);
omObjData *omAddObjEx(Process *objman_process, s16 prio, u16 mdlcnt, u16 mtncnt, s16 group, omObjFunc func);
void omAddMember(Process *objman_process, u16 group, omObjData *object);
void omDelObjEx(Process *objman_process, omObjData *object);
void omDelMember(Process *objman_process, omObjData *object);
void omMakeGroupEx(Process *objman_process, u16 group, u16 max_objs);
omObjData **omGetGroupMemberListEx(Process *objman_process, s16 group);
void omSetStatBit(omObjData *obj, u16 stat);
void omResetStatBit(omObjData *obj, u16 stat);
void omSetTra(omObjData *obj, float x, float y, float z);
void omSetRot(omObjData *obj, float x, float y, float z);
void omSetSca(omObjData *obj, float x, float y, float z);
void omMain(void);
void omAllPause(BOOL pause);
char omPauseChk(void);
OverlayID omCurrentOvlGet(void);


void omDLLDBGOut(void);
void omDLLInit(FileListEntry *ovl_list);
int omDLLStart(s16 overlay, s16 flag);
void omDLLNumEnd(s16 overlay, s16 flag);
void omDLLEnd(s16 dllno, s16 flag);
omDllData *omDLLLink(omDllData **dll_ptr, s16 overlay, s16 flag);
void omDLLUnlink(omDllData *dll_ptr, s16 flag);
s32 omDLLSearch(s16 overlay);
void omDLLInfoDump(OSModuleInfo *module);
void omDLLHeaderDump(OSModuleHeader *module);

void omOutView(omObjData *object);
void omOutViewMulti(omObjData *object);
void omSystemKeyCheckSetup(Process *objman);
void omSystemKeyCheck(omObjData *object);
void omSysPauseEnable(u8 flag);
void omSysPauseCtrl(s16 flag);

extern omObjData *omDBGSysKeyObj;
extern Process *omwatchproc;
extern OverlayID omnextovl;
extern OverlayID omcurovl;
extern int omcurdll;
extern int omovlhisidx;
extern int omovlevtno;
extern int omnextovlevtno;
extern int omovlstat;
extern char omUPauseFlag;
extern s16 omSysExitReq;
extern s16 omdispinfo;
extern u8 omSysPauseEnableFlag;
extern OverlayID omprevovl;

extern omDllData *omDLLinfoTbl[OM_DLL_MAX];

extern Vec CRot;
extern Vec Center;
extern float CZoom;
extern Vec CRotM[16];
extern Vec CenterM[16];
extern float CZoomM[16];
extern s16 omDBGMenuButton;



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


/* "include\game\flag.h" line 3 "dolphin/types.h" */
/* end "dolphin/types.h" */

#define FLAG_ID_MAKE(group, index) (((group) << 16)|(index))

s32 _CheckFlag(u32 flag);
void _SetFlag(u32 flag);
void _ClearFlag(u32 flag);
void _InitFlag(void);


//HACK: to prevent prototype errors
extern void HuPadRumbleAllStop(void);

typedef struct player_config {
    s16 character;
    s16 pad_idx;
    s16 diff;
    s16 group;
    s16 iscom;
} PlayerConfig;

typedef struct system_state {
/* 0x00 */ struct {
        u8 party : 1;
        u8 team : 1;
    };
/* 0x01 */ u8 diff_story;
/* 0x02 */ struct {
        u16 bonus_star : 1;
        u16 explain_mg : 1;
        u16 show_com_mg : 1;
        u16 mg_list : 2;
        u16 mess_speed : 2;
        u16 save_mode : 2;
    };
/* 0x04 */ u8 turn;
/* 0x05 */ u8 max_turn;
/* 0x06 */ u8 star_flag;
/* 0x07 */ u8 star_total;
/* 0x08 */ struct {
    u8 star_pos : 3;
    u8 board : 5;
};
/* 0x09 */ s8 last5_effect;
/* 0x0A */ s8 player_curr;
/* 0x0B */ s8 unk0B[3];
/* 0x0E */ s16 block_pos;
/* 0x10 */ u8 board_data[32];
/* 0x30 */ u8 mess_delay;
/* 0x31 */ struct {
        u8 bowser_loss : 4;
        u8 bowser_event : 4;
    };
/* 0x32 */ s8 lucky_value;
/* 0x34 */ u16 mg_next;
/* 0x36 */ s16 mg_type;
/* 0x38 */ u16 unk_38;
/* 0x3A */ u8 flag[3][16];
/* 0x6A */ u8 unk_6A[0x72];
} SystemState; //8018fcf8, sizeof 0xDC

typedef struct player_state {
/* 0x00 */ struct {
        u16 diff : 2;
        u16 com : 1;
        u16 character : 4;
        u16 auto_size : 2;
        u16 draw_ticket : 1;
        u16 ticket_player : 6;
    };
/* 0x02 */ struct {
        u8 team : 1;
        u8 spark : 1;
        u8 player_idx : 2;
    };
/* 0x03 */ s8 handicap;
/* 0x04 */ s8 port;
/* 0x05 */ s8 items[3];
/* 0x08 */ struct {
        u16 color : 2;
        u16 moving : 1;
        u16 jump : 1;
        u16 show_next : 1;
        u16 size : 2;
        u16 num_dice : 2;
        u16 rank : 2;
        u16 bowser_suit : 1;
        u16 team_backup : 1;
    };
/* 0x0A */ s8 roll;
/* 0x0C */ s16 space_curr;
/* 0x0E */ s16 space_prev;
/* 0x10 */ s16 space_next;
/* 0x12 */ s16 space_shock;
/* 0x14 */ s8 blue_count;
/* 0x15 */ s8 red_count;
/* 0x16 */ s8 question_count;
/* 0x17 */ s8 fortune_count;
/* 0x18 */ s8 bowser_count;
/* 0x19 */ s8 battle_count;
/* 0x1A */ s8 mushroom_count;
/* 0x1B */ s8 warp_count;
/* 0x1C */ s16 coins;
/* 0x1E */ s16 coins_mg;
/* 0x20 */ s16 coins_total;
/* 0x22 */ s16 coins_max;
/* 0x24 */ s16 coins_battle;
/* 0x26 */ s16 coin_collect;
/* 0x28 */ s16 coin_win;
/* 0x2A */ s16 stars;
/* 0x2C */ s16 stars_max;
/* 0x2E */ char unk_2E[2];
} PlayerState; //size of 0x30

typedef struct pause_backup_config {
	u8 explain_mg : 1;
	u8 show_com_mg : 1;
	u8 mg_list : 2;
	u8 mess_speed : 2;
	u8 save_mode : 2;
} PauseBackupConfig;

typedef struct game_stat {
/* 0x0 */ s16 unk_00;
/* 0x2 */ u8 language;
/* 0x3 */ u8 sound_mode;
/* 0x4 */ s8 rumble;
/* 0x6 */ u16 total_stars;
/* 0x8 */ OSTime create_time;
/* 0x10 */ u32 mg_custom[2];
/* 0x18 */ u32 mg_avail[2];
/* 0x20 */ u32 mg_record[15];
/* 0x5C */ u8 board_win_count[9][8];
/* 0xA4 */ u8 board_play_count[9];
/* 0xAE */ u16 board_max_stars[9];
/* 0xC0 */ u16 board_max_coins[9];
/* 0xD2 */ u8 present[60];
/* 0x10E */ struct {
        u8 story_continue : 1;
        u8 party_continue : 1;
        u8 open_w06 : 1;
        u8 field10E_bit4 : 1;
        u8 field10E_bit5 : 1;
        u8 field10E_bit6 : 1;
    };
/* 0x10F */ PauseBackupConfig story_pause; 
/* 0x110 */ PauseBackupConfig party_pause; 
} GameStat;

extern PlayerConfig GWPlayerCfg[4];
extern PlayerState GWPlayer[4];
extern SystemState GWSystem;
extern GameStat GWGameStat;

static inline s32 GWTeamGet(void)
{
    return GWSystem.team;
}

static inline s32 GWMGTypeGet(void)
{
	return GWSystem.mg_type;
}

static inline void GWMGTypeSet(s32 type)
{
	GWSystem.mg_type = type;
}

static inline s32 GWPartyGet(void)
{
    return GWSystem.party;
}

static inline s32 GWLanguageGet(void)
{
    return GWGameStat.language;
}

static inline s32 GWRumbleGet(void)
{
    return GWGameStat.rumble;
}

static inline void GWRumbleSet(s32 value)
{
    GWGameStat.rumble = value;
	if(value == 0) {
		HuPadRumbleAllStop();
	}
}

static inline s32 GWMGExplainGet(void)
{
    return GWSystem.explain_mg;
}

static inline void GWMGExplainSet(s32 value)
{
    GWSystem.explain_mg = value;
}

static inline s32 GWMGShowComGet(void)
{
    return GWSystem.show_com_mg;
}

static inline void GWMGShowComSet(s32 value)
{
    GWSystem.show_com_mg = value;
}

static inline s32 GWMGListGet(void)
{
    if (GWSystem.mg_list == 3) {
        GWSystem.mg_list = 0;
    }
    return GWSystem.mg_list;
}

static inline void GWMGListSet(s32 value)
{
    GWSystem.mg_list = value;
}

static inline s32 GWMessSpeedGet(void)
{
    if (GWSystem.mess_speed == 3) {
        GWSystem.mess_speed = 1;
    }
    return GWSystem.mess_speed;
}

static inline void GWMessSpeedSet(s32 value)
{
	GWSystem.mess_speed = value;
	switch(value) {
		case 0:
			GWSystem.mess_delay = 16;
			break;
			
		case 2:
			GWSystem.mess_delay = 48;
			break;
			
		default:
			GWSystem.mess_delay = 32;
			break;
	}
}

static inline void GWSaveModeSet(s32 value)
{
    GWSystem.save_mode = value;
}

static inline s32 GWSaveModeGet(void)
{
    if (GWSystem.save_mode == 3) {
		GWSaveModeSet(1);
    }
    return GWSystem.save_mode;
}

static inline s32 GWTurnGet(void)
{
    return GWSystem.turn;
}

static inline s32 GWBoardGet(void)
{
    return GWSystem.board;
}

static inline s32 GWPlayerTeamGet(s32 player)
{
    return GWPlayer[player].team;
}

static inline s32 GWLuckyValueGet(void)
{
    return GWSystem.lucky_value;
}

static inline void GWLuckyValueSet(s32 value)
{
    GWSystem.lucky_value = value;
}

static inline s16 GWPlayerCoinBattleGet(s32 player)
{
	return GWPlayer[player].coins_battle;
}

static inline s16 GWPlayerCoinCollectGet(s32 player)
{
	return GWPlayer[player].coin_collect;
}

static inline void GWPlayerCoinCollectSet(s32 player, s16 value)
{
	GWPlayer[player].coin_collect = value;
}

static inline s16 GWPlayerCoinWinGet(s32 player)
{
	return GWPlayer[player].coin_win;
}

static inline void GWPlayerCoinWinSet(s32 player, s16 value)
{
	if (_CheckFlag(0x1000C) == 0) {
		GWPlayer[player].coin_win = value;
	}
}

#define GWPlayerCoinWinAdd(player, value) GWPlayerCoinWinSet((player), GWPlayerCoinWinGet((player))+(value))
#define GWPlayerCoinCollectAdd(player, value) GWPlayerCoinCollectSet((player), GWPlayerCoinCollectGet((player))+(value))

/* end "game/gamework_data.h" */
/* "src\REL\E3setupDLL\main.c" line 3 "game/hsfman.h" */

#define _GAME_HSFMAN_H

/* "include\game\hsfman.h" line 3 "game/hsfanim.h" */

#define GAME_HSFANIM_H

/* "include\game\hsfanim.h" line 3 "game/hsfformat.h" */

#define _GAME_HSFFORMAT_H

/* "include\game\hsfformat.h" line 3 "dolphin.h" */
/* end "dolphin.h" */
/* "include\game\hsfformat.h" line 4 "game/animdata.h" */

#define _GAME_ANIMDATA_H

/* "include\game\animdata.h" line 3 "dolphin.h" */
/* end "dolphin.h" */

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


#define HSF_OBJ_NULL1 0
#define HSF_OBJ_REPLICA 1
#define HSF_OBJ_MESH 2
#define HSF_OBJ_ROOT 3
#define HSF_OBJ_JOINT 4
#define HSF_OBJ_NULL2 5
#define HSF_OBJ_NULL3 6
#define HSF_OBJ_NONE1 7
#define HSF_OBJ_NONE2 8
#define HSF_OBJ_MAP 9

#define HSF_TRACK_TRANSFORM 2
#define HSF_TRACK_MORPH 3
#define HSF_TRACK_CLUSTER 5
#define HSF_TRACK_CLUSTER_WEIGHT 6
#define HSF_TRACK_MATERIAL 9
#define HSF_TRACK_ATTRIBUTE 10

#define HSF_CURVE_STEP 0
#define HSF_CURVE_LINEAR 1
#define HSF_CURVE_BEZIER 2
#define HSF_CURVE_BITMAP 3
#define HSF_CURVE_CONST 4

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
    GXFogType fogType;
    f32 start;
    f32 end;
    GXColor color;
} HsfScene;

typedef struct hsf_bitmap {
    char *name;
    u32 maxLod;
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
    void *unk04;
    u8 unk8[4];
    float unk0C;
    u8 unk10[4];
    float unk14;
    u8 unk18[8];
    float unk20;
    u8 unk24[4];
    float unk28;
    float unk2C;
    float unk30;
    float unk34;
    u8 unk38[44];
    u32 wrap_s;
    u32 wrap_t;
    u8 unk6C[12];
    u32 unk78;
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
    s32 *attrs;
} HsfMaterial;

typedef struct hsf_vertex_buf {
    char *name;
    s32 count;
    void *data;
} HsfBuffer;

typedef struct hsf_face {
    s16 type;
    s16 mat;
    union {
        struct {
			s16 indices[3][4];
            u32 count;
            s16 *data;
        } strip;
        s16 indices[4][4];
    };
    float nbt[3];
} HsfFace;

typedef struct hsf_const_data {
    u32 flags;
    s16 hook;
    u8 unk6[2];
    void *unk08;
    void *unk0C;
    Mtx unk10;
    AnimData *hilite_map;
} HsfConstData;

typedef struct hsf_transform {
    Vec pos;
    Vec rot;
    Vec scale;
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
        s32 target;
    };
    HsfPart *part;
    float unk10;
    float unk14[1]; // unknown array size
    u8 unk18[124];
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
            float morphWeight[33];
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
    u8 unk123;
    u32 vertexShapeCnt;
    HsfBuffer **vertexShape;
    u32 clusterCnt;
    HsfCluster **cluster;
    u32 cenvCnt;
    HsfCenv *cenv;
    void *file[2];
} HsfObjectData;

typedef struct hsf_camera {
    HsfVector3f target;
    HsfVector3f pos;
    float aspect_dupe;
    float fov;
    float near;
    float far;
} HsfCamera;

typedef struct hsf_light {
    HsfVector3f pos;
    HsfVector3f target;
    u8 type;
    u8 r;
    u8 g;
    u8 b;
    float unk2C;
    float ref_distance;
    float ref_brightness;
    float cutoff;
} HsfLight;
typedef struct hsf_object {
    char *name;
    u32 type;
    HsfConstData *constData;
    u32 flags;
    union {
        HsfObjectData data;
        HsfCamera camera;
        HsfLight light;
    };
} HsfObject;

typedef struct hsf_skeleton {
    char *name;
    HsfTransform transform;
} HsfSkeleton;

typedef struct hsf_bitmap_keyframe {
    float time;
    HsfBitmap *data;
} HsfBitmapKey;

typedef struct hsf_track {
    u8 type;
    u8 start;
    union {
        u16 target;
        s16 target_s16;
    };
    union {
        s32 unk04;
        struct {
            union {
                s16 param;
                u16 param_u16;
            };
            union {
                u16 channel;
                s16 channel_s16;
            };
        };
    };
    u16 curveType;
    u16 numKeyframes;
    union {
        float value;
        void *data;
    };
} HsfTrack;

typedef struct hsf_motion {
    char *name;
    s32 numTracks;
    HsfTrack *track;
    float len;
} HsfMotion;

typedef struct hsf_map_attr {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    u16 *data;
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

/* end "game/hsfformat.h" */
/* "include\game\hsfanim.h" line 4 "game/hsfman.h" */
/* end "game/hsfman.h" */
/* "include\game\hsfanim.h" line 5 "game/animdata.h" */
/* end "game/animdata.h" */

typedef struct model_data ModelData;
typedef struct particle_data ParticleData;

typedef void (*ParticleHook)(ModelData *model, ParticleData *particle, Mtx matrix);

typedef struct {
    /* 0x00 */ union {
        u16 unk00;
        s16 unk00_s16;
    };
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ Vec unk08;
    /* 0x14 */ Vec unk14;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float unk30;
    /* 0x34 */ Vec unk34;
    /* 0x40 */ GXColor unk40;
} HsfanimStruct01; // Size 0x44

typedef struct particle_data {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ float unk_04;
    /* 0x08 */ char unk_08[0x14];
    /* 0x1C */ void *unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ float unk_24;
    /* 0x28 */ float unk_28;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ char unk_2E[2];
    /* 0x30 */ s16 unk_30;
    /* 0x32 */ char unk_32[2];
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ u32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ AnimData *unk_44;
    /* 0x48 */ HsfanimStruct01 *unk_48;
    /* 0x4C */ Vec *unk_4C;
    /* 0x50 */ void *unk_50;
    /* 0x54 */ ParticleHook unk_54;
} ParticleData; // Size 0x58

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ char unk02[2];
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ Vec unk10;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ GXColor unk2E[4];
    /* 0x3E */ GXColor unk3E[4];
} HsfanimStruct00; // Size unknown

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ AnimData *unk10;
} Hu3DTexAnimDataStruct; // Size 0x14

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ Vec unk04;
    /* 0x10 */ char unk10[0xC];
    /* 0x1C */ Vec unk1C;
    /* 0x28 */ char unk28[0xC];
    /* 0x34 */ float unk34;
    /* 0x38 */ float unk38;
    /* 0x3C */ Mtx unk3C;
} Hu3DTexScrDataStruct; // Size 0x6C

void Hu3DAnimInit(void);
s16 Hu3DAnimCreate(void *arg0, s16 arg1, char *arg2);
s16 Hu3DAnimLink(s16 arg0, s16 arg1, char *arg2);
void Hu3DAnimKill(s16 arg0);
void Hu3DAnimModelKill(s16 arg0);
void Hu3DAnimAllKill(void);
void Hu3DAnimAttrSet(s16 arg0, u16 arg1);
void Hu3DAnimAttrReset(s16 arg0, s32 arg1);
void Hu3DAnimSpeedSet(s16 arg0, float arg1);
void Hu3DAnimBankSet(s16 arg0, s32 arg1);
void Hu3DAnmNoSet(s16 arg0, u16 arg1);
s32 Hu3DAnimSet(ModelData *arg0, HsfAttribute *arg1, s16 arg2);
void Hu3DAnimExec(void);
s16 Hu3DTexScrollCreate(s16 arg0, char *arg1);
void Hu3DTexScrollKill(s16 arg0);
void Hu3DTexScrollAllKill(void);
void Hu3DTexScrollPosSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DTexScrollPosMoveSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DTexScrollRotSet(s16 arg0, float arg1);
void Hu3DTexScrollRotMoveSet(s16 arg0, float arg1);
void Hu3DTexScrollPauseDisableSet(s16 arg0, s32 arg1);
s16 Hu3DParticleCreate(AnimData *arg0, s16 arg1);
void Hu3DParticleScaleSet(s16 arg0, float arg1);
void Hu3DParticleZRotSet(s16 arg0, float arg1);
void Hu3DParticleColSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void Hu3DParticleTPLvlSet(s16 arg0, float arg1);
void Hu3DParticleBlendModeSet(s16 arg0, u8 arg1);
void Hu3DParticleHookSet(s16 arg0, ParticleHook arg1);
void Hu3DParticleAttrSet(s16 arg0, u8 arg1);
void Hu3DParticleAttrReset(s16 arg0, u8 arg1);
void Hu3DParticleAnimModeSet(s16 arg0, s16 arg1);
void Hu3DParManInit(void);
s16 Hu3DParManCreate(AnimData *arg0, s16 arg1, HsfanimStruct00 *arg2);
s16 Hu3DParManLink(s16 arg0, HsfanimStruct00 *arg1);
void Hu3DParManKill(s16 arg0);
void Hu3DParManAllKill(void);
void *Hu3DParManPtrGet(s16 arg0);
void Hu3DParManPosSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManVecSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManRotSet(s16 arg0, float arg1, float arg2, float arg3);
void Hu3DParManAttrSet(s16 arg0, s32 arg1);
void Hu3DParManAttrReset(s16 arg0, s32 arg1);
s16 Hu3DParManModelIDGet(s16 arg0);
void Hu3DParManTimeLimitSet(s16 arg0, s32 arg1);
void Hu3DParManVacumeSet(s16 arg0, float arg1, float arg2, float arg3, float arg4);
void Hu3DParManColorSet(s16 arg0, s16 arg1);

extern Hu3DTexAnimDataStruct Hu3DTexAnimData[256];
extern Hu3DTexScrDataStruct Hu3DTexScrData[16];

/* end "game/hsfanim.h" */
/* "include\game\hsfman.h" line 4 "game/hsfformat.h" */
/* end "game/hsfformat.h" */
/* "include\game\hsfman.h" line 5 "game/memory.h" */
/* end "game/memory.h" */
/* "include\game\hsfman.h" line 6 "game/data.h" */

#define _GAME_DATA_H

/* "include\game\data.h" line 3 "game/dvd.h" */
/* end "game/dvd.h" */

/* "include\game\data.h" line 5 "datadir_enum.h" */

#define DATADIR_ENUM


enum {
/* "include\datadir_enum.h" line 6 "datadir_table.h" */
DATADIR_ID_E3SETUP,
DATADIR_ID_BBATTLE, 
DATADIR_ID_BGUEST, 
DATADIR_ID_BKOOPA, 
DATADIR_ID_BKOOPASUIT, 
DATADIR_ID_BKUJIYA, 
DATADIR_ID_BLAST5, 
DATADIR_ID_BOARD, 
DATADIR_ID_BPAUSE, 
DATADIR_ID_BYOKODORI,
DATADIR_ID_DAISY, 
DATADIR_ID_DAISYMDL0,
DATADIR_ID_DAISYMDL1, 
DATADIR_ID_DAISYMOT, 
DATADIR_ID_DONKEY, 
DATADIR_ID_DONKEYMDL0, 
DATADIR_ID_DONKEYMDL1, 
DATADIR_ID_DONKEYMOT, 
DATADIR_ID_EFFECT, 
DATADIR_ID_GAMEMES, 
DATADIR_ID_INST, 
DATADIR_ID_INSTFONT, 
DATADIR_ID_INSTPIC, 
DATADIR_ID_LUIGI, 
DATADIR_ID_LUIGIMDL0, 
DATADIR_ID_LUIGIMDL1, 
DATADIR_ID_LUIGIMOT, 
DATADIR_ID_M300, 
DATADIR_ID_M302, 
DATADIR_ID_M303, 
DATADIR_ID_M330, 
DATADIR_ID_M333, 
DATADIR_ID_M401, 
DATADIR_ID_M402, 
DATADIR_ID_M403, 
DATADIR_ID_M404, 
DATADIR_ID_M405, 
DATADIR_ID_M406, 
DATADIR_ID_M407, 
DATADIR_ID_M408, 
DATADIR_ID_M409, 
DATADIR_ID_M410, 
DATADIR_ID_M411, 
DATADIR_ID_M412, 
DATADIR_ID_M413, 
DATADIR_ID_M414, 
DATADIR_ID_M415, 
DATADIR_ID_M416, 
DATADIR_ID_M417, 
DATADIR_ID_M418, 
DATADIR_ID_M419, 
DATADIR_ID_M420, 
DATADIR_ID_M421, 
DATADIR_ID_M422, 
DATADIR_ID_M423, 
DATADIR_ID_M424, 
DATADIR_ID_M425, 
DATADIR_ID_M426, 
DATADIR_ID_M427, 
DATADIR_ID_M428, 
DATADIR_ID_M429, 
DATADIR_ID_M430, 
DATADIR_ID_M431, 
DATADIR_ID_M432, 
DATADIR_ID_M433, 
DATADIR_ID_M434, 
DATADIR_ID_M435, 
DATADIR_ID_M436, 
DATADIR_ID_M437, 
DATADIR_ID_M438, 
DATADIR_ID_M439, 
DATADIR_ID_M440, 
DATADIR_ID_M441, 
DATADIR_ID_M442, 
DATADIR_ID_M443, 
DATADIR_ID_M444, 
DATADIR_ID_M445, 
DATADIR_ID_M446, 
DATADIR_ID_M447, 
DATADIR_ID_M448, 
DATADIR_ID_M449, 
DATADIR_ID_M450, 
DATADIR_ID_M451, 
DATADIR_ID_M453, 
DATADIR_ID_M455, 
DATADIR_ID_M456, 
DATADIR_ID_M457, 
DATADIR_ID_M458, 
DATADIR_ID_M459, 
DATADIR_ID_M460, 
DATADIR_ID_M461, 
DATADIR_ID_M462, 
DATADIR_ID_MARIO,
DATADIR_ID_MARIOMDL0, 
DATADIR_ID_MARIOMDL1, 
DATADIR_ID_MARIOMOT, 
DATADIR_ID_MENT, 
DATADIR_ID_MGCONST, 
DATADIR_ID_MGMODE,
DATADIR_ID_MODESEL,
DATADIR_ID_MPEX, 
DATADIR_ID_MSTORY, 
DATADIR_ID_MSTORY2, 
DATADIR_ID_MSTORY3, 
DATADIR_ID_MSTORY4, 
DATADIR_ID_OPTION, 
DATADIR_ID_PEACH, 
DATADIR_ID_PEACHMDL0,
DATADIR_ID_PEACHMDL1,
DATADIR_ID_PEACHMOT, 
DATADIR_ID_PRESENT, 
DATADIR_ID_RESULT, 
DATADIR_ID_SAF, 
DATADIR_ID_SELMENU, 
DATADIR_ID_SETUP, 
DATADIR_ID_STAFF, 
DATADIR_ID_TITLE, 
DATADIR_ID_W01, 
DATADIR_ID_W02, 
DATADIR_ID_W03, 
DATADIR_ID_W04, 
DATADIR_ID_W05, 
DATADIR_ID_W06, 
DATADIR_ID_W10, 
DATADIR_ID_W20, 
DATADIR_ID_W21, 
DATADIR_ID_WALUIGI, 
DATADIR_ID_WALUIGIMDL0,
DATADIR_ID_WALUIGIMDL1,
DATADIR_ID_WALUIGIMOT, 
DATADIR_ID_WARIO, 
DATADIR_ID_WARIOMDL0,
DATADIR_ID_WARIOMDL1, 
DATADIR_ID_WARIOMOT, 
DATADIR_ID_WIN, 
DATADIR_ID_YOSHI, 
DATADIR_ID_YOSHIMDL0, 
DATADIR_ID_YOSHIMDL1, 
DATADIR_ID_YOSHIMOT, 
DATADIR_ID_ZTAR,
    DATADIR_ID_MAX
};


#define DATADIR_DEFINE(name, path) DATADIR_##name = (DATADIR_ID_##name) << 16,


#define DATA_MAKE_NUM(dir, file) ((dir)+(file))

#define DATA_DECODE_NONE 0
#define DATA_DECODE_LZ 1
#define DATA_DECODE_SLIDE 2
#define DATA_DECODE_FSLIDE_ALT 3
#define DATA_DECODE_FSLIDE 4
#define DATA_DECODE_RLE 5

#define DATA_NUM_LISTEND -1

/* "include\game\data.h" line 16 "dolphin/types.h" */
/* end "dolphin/types.h" */


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
void HuDataDirReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo);
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


#define Hu3DModelCreateFile(data_id) (Hu3DModelCreate(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

typedef struct particle_data ParticleData;

typedef void (*ModelHookFunc)(struct model_data *, Mtx);

typedef struct model_data {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s8 unk_04;
    s8 unk_05;
    s16 layer;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10[4];
    s16 cluster_attr[4];
    s16 unk_20;
    u16 camera;
    s16 unk_24;
    u16 unk_26;
    u16 unk_28[8];
    s16 unk_38[8];
    HsfData *unk_48;
    HsfData *unk_4C;
    u32 attr;
    u32 motion_attr;
    Point3d unk_58;
    f32 unk_64;
	f32 unk_68;
	f32 unk_6C;
	f32 unk_70;
    f32 unk_74;
    f32 unk_78;
    f32 unk_7C;
    f32 unk_80;
    f32 unk_84;
    f32 unk_88;
    f32 unk_8C;
    f32 unk_90;
    f32 unk_94;
    f32 unk_98;
    f32 unk_9C;
    f32 unk_A0;
    f32 unk_A4[4];
    f32 unk_B4[4];
	union {
		HsfData *hsfData;
		ModelHookFunc hook;
	};
    HsfData *unk_C8;
    Vec pos;
    Vec rot;
    Vec scale;
    Mtx unk_F0;
    ParticleData *unk_120;
} ModelData; // sizeof 0x124
typedef struct camera_data {
    f32 fov;
    f32 near;
    f32 far;
    f32 aspect;
    f32 aspect_dupe;
    Vec pos;
    Vec up;
    Vec target;
    s16 scissor_x;
    s16 scissor_y;
    s16 scissor_w;
    s16 scissor_h;
    f32 viewport_x;
    f32 viewport_y;
    f32 viewport_w;
    f32 viewport_h;
    f32 near_z;
    f32 far_z;
} CameraData; // sizeof 0x58
typedef struct ThreeDProjectionStruct {
    u8 unk_00;
    char unk_01[0x3];
    void *unk_04;
    Vec unk_08;
    Point3d unk_14;
    Point3d unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ThreeDProjectionStruct; // sizeof 0x98
typedef struct shadow_data {
    u8 unk_00;
    u8 unk_01;
    u16 unk_02;
    void* unk_04;
    Vec unk_08;
    Vec unk_14;
    Vec unk_20;
    Vec unk_2C;
    Mtx unk_38;
    Mtx unk_68;
} ShadowData; // sizeof 0x98
typedef struct light_data {
    s16 unk_00;
    s16 unk_02;
    f32 unk_04;
    f32 unk_08;
    char unk_0C[0x10];
    Vec unk_1C;
    Vec unk_28;
    Vec unk_34;
    GXColor color;
} LightData;

extern void GXWaitDrawDone();                                 /* extern */
extern void GXInitSpecularDir(GXLightObj*, f32, f32, f32);

void Hu3DInit(void);
void Hu3DPreProc(void);
void Hu3DExec(void);
void Hu3DAllKill(void);
void Hu3DBGColorSet(u8, u8, u8);
void Hu3DLayerHookSet(s16, void (*)(s16));
void Hu3DPauseSet(s32);
void Hu3DNoSyncSet(s32);
s16 Hu3DModelCreate(void *);
s16 Hu3DModelLink(s16);
s16 Hu3DHookFuncCreate(ModelHookFunc);
void Hu3DModelKill(s16);
void Hu3DModelAllKill(void);
void Hu3DModelPosSet(s16, f32, f32, f32);
void Hu3DModelPosSetV(s16, Vec *);
void Hu3DModelRotSet(s16, f32, f32, f32);
void Hu3DModelRotSetV(s16, Vec *);
void Hu3DModelScaleSet(s16, f32, f32, f32);
void Hu3DModelScaleSetV(s16, Vec *);
void Hu3DModelAttrSet(s16, u32);
void Hu3DModelAttrReset(s16, u32);
u32 Hu3DModelAttrGet(s16);
u32 Hu3DModelMotionAttrGet(s16);
void Hu3DModelClusterAttrSet(s16, s16, s32);
void Hu3DModelClusterAttrReset(s16, s16, s32);
void Hu3DModelCameraSet(s16, u16);
void Hu3DModelLayerSet(s16, s16);
HsfObject* Hu3DModelObjPtrGet(s16, char *);
void Hu3DModelTPLvlSet(s16, f32);
void Hu3DModelHiliteMapSet(s16, AnimData*);
void Hu3DModelShadowSet(s16);
void Hu3DModelShadowReset(s16);
void Hu3DModelShadowDispOn(s16);
void Hu3DModelShadowDispOff(s16);
void Hu3DModelShadowMapSet(s16);
void Hu3DModelShadowMapObjSet(s16, char *);
void Hu3DModelAmbSet(s16, f32, f32, f32);
void Hu3DModelHookSet(s16, char *, s16);
void Hu3DModelHookReset(s16);
void Hu3DModelHookObjReset(s16, char *);
void Hu3DModelProjectionSet(s16, s16);
void Hu3DModelProjectionReset(s16, s16);
void Hu3DModelHiliteTypeSet(s16, s16);
void Hu3DModelReflectTypeSet(s16, s16);
void Hu3DCameraCreate(s32);
void Hu3DCameraPerspectiveSet(s32, f32, f32, f32, f32);
void Hu3DCameraViewportSet(s32, f32, f32, f32, f32, f32, f32);
void Hu3DCameraScissorSet(s32, u32, u32, u32, u32);
void Hu3DCameraPosSet(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Hu3DCameraPosSetV(s32 cam, Vec *pos, Vec *up, Vec *target);
void Hu3DCameraKill(s32);
void Hu3DCameraAllKill(void);
void Hu3DCameraSet(s32, Mtx);
BOOL Hu3DModelCameraInfoSet(s16, u16);
s16 Hu3DModelCameraCreate(s16, u16);
void Hu3DCameraMotionOn(s16, s8);
void Hu3DCameraMotionStart(s16, u16);
void Hu3DCameraMotionOff(s16);
void Hu3DLighInit(void);
s16 Hu3DGLightCreate(f32, f32, f32, f32, f32, f32, u8, u8, u8);
s16 Hu3DGLightCreateV(Vec*, Vec*, GXColor*);
s16 Hu3DLLightCreate(s16, f32, f32, f32, f32, f32, f32, u8, u8, u8);
s16 Hu3DLLightCreateV(s16, Vec*, Vec*, GXColor*);
void Hu3DGLightSpotSet(s16, u16, f32);
void Hu3DLLightSpotSet(s16, s16, u16, f32);
void Hu3DGLightInfinitytSet(s16);
void Hu3DLLightInfinitytSet(s16, s16);
void Hu3DGLightPointSet(s16, u16, f32, f32);
void Hu3DLLightPointSet(s16, s16, u16, f32, f32);
void Hu3DGLightKill(s16);
void Hu3DLLightKill(s16, s16);
void Hu3DLightAllKill(void);
void Hu3DGLightColorSet(s16, u8, u8, u8, u8);
void Hu3DLLightColorSet(s16, s16, u8, u8, u8, u8);
void Hu3DGLightPosSetV(s16, Vec*, Point3d*);
void Hu3DLLightPosSetV(s16, s16, Vec*, Point3d*);
void Hu3DGLightPosSet(s16, f32, f32, f32, f32, f32, f32);
void Hu3DLLightPosSet(s16, s16, f32, f32, f32, f32, f32, f32);
void Hu3DGLightPosAimSetV(s16, Point3d*, Point3d*);
void Hu3DLLightPosAimSetV(s16, s16, Point3d*, Point3d*);
void Hu3DGLightPosAimSet(s16, f32, f32, f32, f32, f32, f32);
void Hu3DLLightPosAimSet(s16, s16, f32, f32, f32, f32, f32, f32);
void Hu3DGLightStaticSet(s16, s32);
void Hu3DLLightStaticSet(s16, s16, s32);
s32 Hu3DModelLightInfoSet(s16, s16);
s16 Hu3DLightSet(ModelData*, Mtx*, Mtx*, f32);
void lightSet(LightData* arg0, s16 arg1, Mtx *arg2, Mtx *arg3, f32 arg8);
void Hu3DReflectMapSet(AnimData* arg0);
void Hu3DReflectNoSet(s16 arg0);
void Hu3DFogSet(f32, f32, u8, u8, u8);
void Hu3DFogClear(void);
void Hu3DShadowCreate(f32, f32, f32);
void Hu3DShadowPosSet(Vec*, Vec*, Vec*);
void Hu3DShadowTPLvlSet(f32);
void Hu3DShadowSizeSet(u16);
void Hu3DShadowExec(void);
s16 Hu3DProjectionCreate(void*, f32, f32, f32);
void Hu3DProjectionKill(s16);
void Hu3DProjectionPosSet(s16, Vec*, Vec*, Vec*);
void Hu3DProjectionTPLvlSet(s16, f32);
void Hu3DMipMapSet(char*, s16, s32, f32);

extern ModelData Hu3DData[0x200];
extern CameraData Hu3DCamera[0x10];
extern AnimData *reflectAnim[5];
extern AnimData *hiliteAnim[4];
extern ThreeDProjectionStruct Hu3DProjection[4];
extern ShadowData Hu3DShadowData;
extern Mtx Hu3DCameraMtx;
extern Mtx Hu3DCameraMtxXPose;
extern LightData Hu3DGlobalLight[0x8];
extern s16 reflectMapNo;
extern AnimData *toonAnim;
extern s16 Hu3DShadowCamBit;
extern s32 Hu3DShadowF;
extern s32 shadowModelDrawF;
extern s16 Hu3DCameraNo;
extern s16 Hu3DCameraBit;
extern s16 Hu3DPauseF;


/* end "game/hsfman.h" */
/* "src\REL\E3setupDLL\main.c" line 4 "game/wipe.h" */

#define _GAME_WIPE_H

/* "include\game\wipe.h" line 3 "dolphin.h" */
/* end "dolphin.h" */

#define WIPE_TYPE_NORMAL 0
#define WIPE_TYPE_CROSS 1
#define WIPE_TYPE_DUMMY 2
#define WIPE_MODE_IN 1
#define WIPE_MODE_OUT 2
#define WIPE_MODE_BLANK 3

typedef struct wipe_state {
	u32 unk00;
	u32 unk04;
	void *copy_data;
	u32 unk0C;
	void *unk10[8];
    float time;
    float duration;
    u32 unk38;
	u16 w;
	u16 h;
	u16 x;
	u16 y;
	GXColor color;
	volatile u8 type;
    u8 mode;
	u8 stat;
	u8 keep_copy;
} WipeState;

void WipeInit(GXRenderModeObj *rmode);
void WipeExecAlways(void);
void WipeCreate(s16 mode, s16 type, s16 duration);
void WipeColorSet(u8 r, u8 g, u8 b);
u8 WipeStatGet(void);

extern WipeState wipeData;
extern BOOL wipeFadeInF;


/* "src\REL\E3setupDLL\main.c" line 5 "game/pad.h" */

#define _GAME_PAD_H

/* "include\game\pad.h" line 3 "dolphin.h" */
/* end "dolphin.h" */

#define PAD_BUTTON_DIR (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_UP | PAD_BUTTON_DOWN)

#define PAD_BUTTON_TRIGGER_L 0x4000
#define PAD_BUTTON_TRIGGER_R 0x2000

extern u16 HuPadBtn[4];
extern u16 HuPadBtnDown[4];
extern u16 HuPadBtnRep[4];
extern s8 HuPadStkX[4];
extern s8 HuPadStkY[4];
extern s8 HuPadSubStkX[4];
extern s8 HuPadSubStkY[4];
extern u8 HuPadTrigL[4];
extern u8 HuPadTrigR[4];
extern u8 HuPadDStk[4];
extern u8 HuPadDStkRep[4];
extern s8 HuPadErr[4];
extern u16 _PadBtn[4];
extern u16 _PadBtnDown[4];
extern s32 VCounter;

void HuPadInit(void);
void HuPadRead(void);
void HuPadRumbleSet(s16 pad, s16 duration, s16 off, s16 on);
void HuPadRumbleStop(s16 pad);
void HuPadRumbleAllStop(void);
s16 HuPadStatGet(s16 pad);
u32 HuPadRumbleGet(void);


/* "src\REL\E3setupDLL\main.c" line 6 "game/hsfmotion.h" */

#define _GAME_HSFMOTION_H

/* "include\game\hsfmotion.h" line 3 "dolphin.h" */
/* end "dolphin.h" */
/* "include\game\hsfmotion.h" line 4 "game/hsfformat.h" */
/* end "game/hsfformat.h" */

#define Hu3DJointMotionFile(model, data_id) (Hu3DJointMotion((model), HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))


typedef struct motion_data {
    s16 unk_00;
    s16 unk_02;
    HsfData *unk_04;
} MotionData;

typedef struct {
    /* 0x00 */ float unk00;
    /* 0x04 */ HsfBitmap *unk04;
} UnknownHsfMotionStruct01; // Size 8

void Hu3DMotionInit(void);
s16 Hu3DMotionCreate(void *arg0);
s16 Hu3DMotionModelCreate(s16 arg0);
s32 Hu3DMotionKill(s16 arg0);
void Hu3DMotionAllKill(void);
void Hu3DMotionSet(s16 arg0, s16 arg1);
void Hu3DMotionOverlaySet(s16 arg0, s16 arg1);
void Hu3DMotionOverlayReset(s16 arg0);
float Hu3DMotionOverlayTimeGet(s16 arg0);
void Hu3DMotionOverlayTimeSet(s16 arg0, float arg1);
void Hu3DMotionOverlaySpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSet(s16 arg0, s16 arg1, float arg2, float arg3, u32 arg4);
void Hu3DMotionShapeSet(s16 arg0, s16 arg1);
s16 Hu3DMotionShapeIDGet(s16 arg0);
void Hu3DMotionShapeSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShapeTimeSet(s16 arg0, float arg1);
float Hu3DMotionShapeMaxTimeGet(s16 arg0);
void Hu3DMotionShapeStartEndSet(s16 arg0, float arg1, float arg2);
s16 Hu3DMotionClusterSet(s16 arg0, s16 arg1);
s16 Hu3DMotionClusterNoSet(s16 arg0, s16 arg1, s16 arg2);
void Hu3DMotionShapeReset(s16 arg0);
void Hu3DMotionClusterReset(s16 arg0, s16 arg1);
s16 Hu3DMotionIDGet(s16 arg0);
s16 Hu3DMotionShiftIDGet(s16 arg0);
void Hu3DMotionTimeSet(s16 arg0, float arg1);
float Hu3DMotionTimeGet(s16 arg0);
float Hu3DMotionShiftTimeGet(s16 arg0);
float Hu3DMotionMaxTimeGet(s16 arg0);
float Hu3DMotionShiftMaxTimeGet(s16 arg0);
void Hu3DMotionShiftStartEndSet(s16 arg0, float arg1, float arg2);
float Hu3DMotionMotionMaxTimeGet(s16 arg0);
void Hu3DMotionStartEndSet(s16 arg0, float arg1, float arg2);
s32 Hu3DMotionEndCheck(s16 arg0);
void Hu3DMotionSpeedSet(s16 arg0, float arg1);
void Hu3DMotionShiftSpeedSet(s16 arg0, float arg1);
void Hu3DMotionNoMotSet(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionNoMotReset(s16 arg0, char *arg1, u32 arg2);
void Hu3DMotionForceSet(s16 arg0, char *arg1, u32 arg2, float arg3);
void Hu3DMotionNext(s16 arg0);
void Hu3DMotionExec(s16 arg0, s16 arg1, float arg2, s32 arg3);
void Hu3DCameraMotionExec(s16 arg0);
void Hu3DSubMotionExec(s16 arg0);
float *GetObjTRXPtr(HsfObject *arg0, u16 arg1);
void SetObjMatMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjAttrMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjCameraMotion(s16 arg0, HsfTrack *arg1, float arg2);
void SetObjLightMotion(s16 arg0, HsfTrack *arg1, float arg2);
float GetCurve(HsfTrack *arg0, float arg1);
float GetConstant(s32 arg0, float *arg1, float arg2);
float GetLinear(s32 arg0, float arg1[][2], float arg2);
float GetBezier(s32 arg0, HsfTrack *arg1, float arg2);
HsfBitmap *GetBitMap(s32 arg0, UnknownHsfMotionStruct01 *arg1, float arg2);
s16 Hu3DJointMotion(s16 arg0, void *arg1);
void JointModel_Motion(s16 arg0, s16 arg1);
void Hu3DMotionCalc(s16 arg0);

extern MotionData Hu3DMotion[256];


/* end "game/hsfmotion.h" */
/* "src\REL\E3setupDLL\main.c" line 7 "game/init.h" */

#define _GAME_INIT_H

/* "include\game\init.h" line 3 "dolphin.h" */
/* end "dolphin.h" */

extern GXRenderModeObj *RenderMode;
extern OSHeapHandle currentHeapHandle;

extern void *DemoFrameBuffer1;
extern void *DemoFrameBuffer2;
extern void *DemoCurrentBuffer;
extern u32 minimumVcount;
extern float minimumVcountf;
extern u32 worstVcount;

void HuSysInit(GXRenderModeObj *mode);
void HuSysBeforeRender();
void HuSysDoneRender(s32 retrace_count);


/* "src\REL\E3setupDLL\main.c" line 8 "game/minigame_seq.h" */

#define _GAME_MINIGAME_SEQ_H

/* "include\game\minigame_seq.h" line 3 "game/object.h" */
/* end "game/object.h" */
/* "include\game\minigame_seq.h" line 4 "stdarg.h" */

#define STDARG_H

typedef struct {
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} __va_list[1];
typedef __va_list va_list;

void* __va_arg(va_list v_list, unsigned char type);

#define va_start(ap, fmt) ((void) fmt, __builtin_va_info(&ap))
#define va_arg(ap, t) (*((t*) __va_arg(ap, _var_arg_typeof(t))))
#define va_end(ap) (void) 0



#define MG_SEQ_TYPE_TIMER 1
#define MG_SEQ_TYPE_AUTO 3
#define MG_SEQ_TYPE_1VS3 4
#define MG_SEQ_TYPE_WIN 5
#define MG_SEQ_TYPE_BATTLE 6
#define MG_SEQ_TYPE_STORY 7
#define MG_SEQ_TYPE_4P 8
#define MG_SEQ_TYPE_2VS2 9
#define MG_SEQ_TYPE_PINBALL 10
#define MG_SEQ_TYPE_BOWSER 11
#define MG_SEQ_TYPE_ALTWIN 12
#define MG_SEQ_TYPE_DRAW 13
#define MG_SEQ_TYPE_RECORD 14

#define MG_SEQ_WIN_TYPE_WIN 3
#define MG_SEQ_WIN_TYPE_LOSE 4
#define MG_SEQ_WIN_TYPE_CHAMPION 5

#define MG_SEQ_WORD_START 0
#define MG_SEQ_WORD_FINISH 1
#define MG_SEQ_WORD_DRAW 2

#define MGSeqTimerCreate(value) MGSeqCreate(MG_SEQ_TYPE_TIMER, (value), -1, -1)
#define MGSeqTimerCreateXY(value, x, y) MGSeqCreate(MG_SEQ_TYPE_TIMER, (value), (int)(x), (int)(y))
#define MGSeqStartCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_START)
#define MGSeqFinishCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_FINISH)
#define MGSeqDrawCreate() MGSeqCreate(MG_SEQ_TYPE_AUTO, MG_SEQ_WORD_DRAW)
#define MGSeqStartCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_START)
#define MGSeqFinishCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_FINISH)
#define MGSeqDrawCreateType(type) MGSeqCreate((type), MG_SEQ_WORD_DRAW)
#define MGSeqWinCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_WIN, MG_SEQ_WIN_TYPE_WIN, (player_1), (player_2), (player_3), (player_4))
#define MGSeqLoseCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_WIN, MG_SEQ_WIN_TYPE_LOSE, (player_1), (player_2), (player_3), (player_4))
#define MGSeqChampionCreate(player_1, player_2, player_3, player_4) MGSeqCreate(MG_SEQ_TYPE_ALTWIN, MG_SEQ_WIN_TYPE_CHAMPION, (player_1), (player_2), (player_3), (player_4))
#define MGSeqRecordCreate(value) MGSeqCreate(MG_SEQ_TYPE_RECORD, (value))



typedef struct seq_work SeqWork;

typedef int (*SeqUpdateFunc)(SeqWork *work);
typedef int (*SeqInitFunc)(SeqWork *work, va_list params);

typedef struct seq_work {
	SeqUpdateFunc update;
	char *data;
	float x;
	float y;
	float scale_x;
	float scale_y;
	float unk_18;
	float angle;
	float win_scale;
	float unk_24;
	s16 time;
	s16 time_max;
	s16 timer_val;
	s16 state;
	s16 alt_word_len;
	s16 word_len;
	s16 param[2];
	s16 type;
	s16 spr_grp[16];
	s16 sprite[16];
	u8 seq_no;
	u8 stat;
	u8 unk_7C;
	u8 unk_7D;
} SeqWork;

void MGSeqInit(void);
void MGSeqMain(void);
s16 MGSeqCreate(s16 type, ...);
u8 MGSeqStatGet(s16 id);
void MGSeqPosSet(s16 id, float x, float y);
void MGSeqParamSet(s16 id, s16 param1, s16 param2);
void MGSeqSprKill(SeqWork *work);
void MGSeqKill(s16 id);
void MGSeqKillAll(void);
s32 MGSeqDoneCheck(void);
void MGSeqStub(void);
void MGSeqPauseInit(void);
void MGSeqPauseEnableCtrl(s32 flag);
void MGSeqPracticeInit(void);
void MGSeqPracticeExitCheck(omObjData *object);

extern OverlayID mgSeqOvlPrev;


/* end "game/minigame_seq.h" */
/* "src\REL\E3setupDLL\main.c" line 9 "game/chrman.h" */

#define _GAME_CHRMAN_H

/* "include\game\chrman.h" line 3 "dolphin.h" */
/* end "dolphin.h" */

void CharManInit(void);
void *CharAMemPtrGet(s16 character);
void CharARAMOpen(s16 character);
void CharARAMClose(s16 character);
void CharKill(s16 arg0);
void CharKillAll(void);
s16 CharModelCreate(s16 character, s16 lod);
s16 CharModelMotionCreate(s16 character, s32 arg1);
void CharModelMotionIndexSet(s16 character, s16 arg1, s32 arg2);
void CharModelMotionKill(s16 character, u32 motion);
void CharModelMotionDataClose(s16 character);
void CharModelDataClose(s16 arg0);
void CharModelKill(s16 character);
void CharModelMotionSet(s16 character, s16 motion);
void CharModelTexAnimSet(s16 character);
char **CharModelTexNameGet(s16 arg0, s16 arg1);
char *CharModelHookNameGet(s16 arg0, s16 arg1, s16 arg2);
void CharModelMotionTimeSet(s16 character, float time);
float CharModelMotionTimeGet(s16 character);
float CharModelMotionMaxTimeGet(s16 character);
s32 CharModelMotionEndCheck(s16 character);
s16 CharModelMotionShiftIDGet(s16 character);
void CharModelMotionShiftSet(s16 character, s16 motion, float time, float shift_time, u32 attr);
float CharModelMotionShiftTimeGet(s16 character);
void CharModelMotionSpeedSet(s16 character, float speed);
void CharModelLayerSetAll(s16 arg0);
void CharModelItemHookCreate(s16 character, char *arg1);
void CharModelEffectCreate(s16 arg0, Vec *arg1);
void CharModelCoinEffectCreate(s16 arg0, Vec *arg1);
void fn_8004EC74(s16 character);
void fn_8004EDA4(s16 arg0, Vec *arg1, Vec *arg2);
void fn_8004F058(s16 character);
void fn_8004F13C(s16 arg0, Vec *arg1, Vec *arg2);
void CharModelLayerSetAll2(s16 arg0);
void CharModelVoiceEnableSet(s16 character, s16 motion, s32 flag);
void fn_8004F52C(s16 character, s32 arg1);
void CharModelEffectEnableSet(s16 character, s32 arg1);
s32 CharModelEffectNpcInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
s32 CharModelEffectNpcInitSilent(s16 arg0, s16 arg1, s16 arg2);
s32 CharModelStepTypeSet(s16 character, s32 arg1);


/* end "game/chrman.h" */
/* "src\REL\E3setupDLL\main.c" line 10 "game/sprite.h" */

#define _GAME_SPRITE_H

/* "include\game\sprite.h" line 3 "dolphin.h" */
/* end "dolphin.h" */
/* "include\game\sprite.h" line 4 "game/data.h" */
/* end "game/data.h" */
/* "include\game\sprite.h" line 5 "game/memory.h" */
/* end "game/memory.h" */

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

/* "include\game\sprite.h" line 23 "game/animdata.h" */
/* end "game/animdata.h" */

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

#define HuSprAnimReadFile(data_id) (HuSprAnimRead(HuDataSelHeapReadNum((data_id), MEMORY_DEFAULT_NUM, HEAP_DATA)))

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
void HuSprBGSet(s16 group, s16 member,  AnimData *bg, s16 bg_bank);
void HuSprSprBGSet(s16 sprite, AnimData *bg, s16 bg_bank);
void AnimDebug(AnimData *anim);

void HuSprDispInit(void);
void HuSprDisp(HuSprite *sprite);
void HuSprTexLoad(AnimData *anim, s16 bmp, s16 slot, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter filter);
void HuSprExecLayerSet(s16 draw_no, s16 layer);


/* "src\REL\E3setupDLL\main.c" line 11 "game/window.h" */

#define _GAME_WINDOW_H

/* "include\game\window.h" line 3 "game/animdata.h" */
/* end "game/animdata.h" */
/* "include\game\window.h" line 4 "dolphin.h" */
/* end "dolphin.h" */

#define MAKE_MESSID(bank, mess) (((bank) << 16)+(mess))
#define MAKE_MESSID_PTR(ptr) ((u32)(ptr))

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
void HuWinComKeyWait(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay);
void HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4);
void _HuWinComKeySet(s32 player_1, s32 player_2, s32 player_3, s32 player_4, s16 delay);
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
s16 HuWinExCreateStyled(float x, float y, s16 w, s16 h, s16 portrait, s16 frame);
void HuWinExAnimIn(s16 window);
void HuWinExAnimOut(s16 window);
void HuWinExCleanup(s16 window);
void HuWinExAnimPopIn(s16 window, s16 portrait);
void *MessData_MesPtrGet(void *data, u32 index);

extern void *messDataPtr;


/* end "game/window.h" */
/* "src\REL\E3setupDLL\main.c" line 12 "ext_math.h" */

#define _EXT_MATH_H

/* "include\ext_math.h" line 3 "math.h" */

#define _MATH_H

#define M_PI 3.141592653589793


#define _MATH_INLINE static inline


extern inline float sqrtf(float x)
{
	volatile float y;
	if(x > 0.0f)
	{
		double guess = __frsqrte((double)x);   // returns an approximation to
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 12 sig bits
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 24 sig bits
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 32 sig bits
		y=(float)(x*guess);
		return y;
	}
	return x;
}

double atan(double x);
double copysign(double x, double y);
double cos(double x);
double floor(double x);
double frexp(double x, int *exp);
double ldexp(double x, int exp);
double modf(double x, double *intpart);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan2(double y, double x);
double fmod(double x, double y);
double log(double x);
double pow(double x, double y);
float tanf(float x);
float sinf(float x);
float cosf(float x);
float atan2f(float y, float x);
float acosf(float x);

extern inline double fabs(double x)
{
   return __fabs(x);
}


/* end "math.h" */
/* "include\ext_math.h" line 4 "dolphin/mtx.h" */
/* end "dolphin/mtx.h" */

typedef struct vec2f {
	float x;
	float y;
} Vec2f;

#define ABS(x) (((x) < 0) ? -(x) : (x))

#define VECDistanceXZ(a, b) sqrtf((((a)->x-(b)->x)*((a)->x-(b)->x))+(((a)->z-(b)->z)*((a)->z-(b)->z)))
#define VECDistanceAlt(a, b) sqrtf((((a)->x-(b)->x)*((a)->x-(b)->x))+(((a)->y-(b)->y)*((a)->y-(b)->y))+(((a)->z-(b)->z)*((a)->z-(b)->z)))

#define VECMagXZ(a) sqrtf(((a)->x*(a)->x)+((a)->z*(a)->z))

#define sind(x) sin(M_PI*(x)/180.0)
#define cosd(x) cos(M_PI*(x)/180.0)
#define atan2d(y, x) (180.0*(atan2((y), (x)) / M_PI))
