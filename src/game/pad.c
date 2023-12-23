#include "common.h"
#include "dolphin.h"
#include "game/msm.h"

typedef struct pad_rumble {
    s16 duration;
    s16 stop;
    s16 rumble;
    s16 time;
} padRumble;

void HuPadRead(void);
static void PadReadVSync(u32 retraceCount);
static void PadADConv(s16 pad, PADStatus *status);

static int padStatErrOld[4];
static padRumble rumbleData[4];

u16 HuPadBtnRep[4];
u16 _PadBtnDown[4];
u16 _PadBtn[4];
static u16 _PadRepCnt[4];
static s8 _PadStkX[4];
static s8 _PadStkY[4];
static s8 _PadSubStkX[4];
static s8 _PadSubStkY[4];
static u8 _PadTrigL[4];
static u8 _PadTrigR[4];
static u8 _PadDStk[4];
static u8 _PadDStkRep[4];
static u8 _PadDStkRepCnt[4];
static u8 _PadDStkRepOld[4];
static s8 _PadErr[4];
static u32 RumbleBit;
u32 VCounter;

u32 chanTbl[4] = { PAD_CHAN0_BIT, PAD_CHAN1_BIT, PAD_CHAN2_BIT, PAD_CHAN3_BIT };

extern int HuDvdErrWait;

void HuPadInit(void)
{
    int i;
    BOOL int_level;
    PADSetSpec(PAD_SPEC_5);
    PADInit();
    SISetSamplingRate(0);
    int_level = OSDisableInterrupts();
    VISetPostRetraceCallback(PadReadVSync);
    OSRestoreInterrupts(int_level);
    for(i=0; i<4; i++) {
        padStatErrOld[i] = PAD_ERR_NOT_READY;
    }
    VIWaitForRetrace();
    VIWaitForRetrace();
    HuPadRead();
    for(i=0; i<4; i++) {
        if(_PadErr[i] == PAD_ERR_NONE) {
            PADControlMotor(i, PAD_MOTOR_STOP_HARD);
        }
        rumbleData[i].duration = 0;
        _PadRepCnt[i] = 0;
    }
}

void HuPadRead(void)
{
    
}

static void PadReadVSync(u32 retraceCount)
{
    u32 chan;
    s16 i;
    PADStatus status[4];
    if(!HuDvdErrWait) {
        RumbleBit = PADRead(status);
        PADClamp(status);
        chan = 0;
        for(i=0; i<4; i++) {
            PADStatus *curr_status = &status[i];
            padRumble *rumble = &rumbleData[i];
            if(padStatErrOld[i] && curr_status->err == PAD_ERR_NONE) {
                PADControlMotor(i, PAD_MOTOR_STOP_HARD);
                rumble->duration = 0;
            }
            padStatErrOld[i] = curr_status->err;
            if(curr_status->err != PAD_ERR_NONE) {
                _PadErr[i] = curr_status->err;
                if(curr_status->err != PAD_ERR_TRANSFER && curr_status->err != PAD_ERR_NOT_READY) {
                    chan |= chanTbl[i];
                }
                _PadBtnDown[i] = _PadBtn[i] = _PadStkX[i] = _PadStkY[i] = _PadSubStkX[i] = _PadSubStkY[i] = _PadTrigL[i] = _PadTrigR[i] =  _PadDStkRep[i] = _PadDStk[i] =  HuPadBtnRep[i] = 0;
            } else {
                u16 button = curr_status->button;
                if(curr_status->triggerL & 0xC0) {
                    button |= 0x4000;
                }
                if(curr_status->triggerR & 0xC0) {
                    button |= 0x2000;
                }
                if(button && _PadBtn[i] == button) {
                    if(_PadRepCnt[i] > 20) {
                        HuPadBtnRep[i] = button;
                    } else {
                        HuPadBtnRep[i] = 0;
                        _PadRepCnt[i]++;
                    }
                } else {
                    _PadRepCnt[i] = 0;
                    HuPadBtnRep[i] = button;
                }
                PadADConv(i, curr_status);
                _PadBtnDown[i] |= PADButtonDown(_PadBtn[i], button);
                _PadBtn[i] = button;
                _PadStkX[i] = curr_status->stickX;
                _PadStkY[i] = curr_status->stickY;
                _PadSubStkX[i] = curr_status->substickX;
                _PadSubStkY[i] = curr_status->substickY;
                _PadTrigL[i] = curr_status->triggerL;
                _PadTrigR[i] = curr_status->triggerR;
                _PadErr[i] = curr_status->err;
                if(rumble->duration) {
                    s16 time = rumble->time%(rumble->stop+rumble->rumble);
                    if(time == 0) {
                        PADControlMotor(i, PAD_MOTOR_RUMBLE);
                    } else {
                        if(time == rumble->stop) {
                            PADControlMotor(i, PAD_MOTOR_STOP);
                        }
                    }
                    rumble->time++;
                    if(rumble->time > rumble->duration) {
                        PADControlMotor(i, PAD_MOTOR_STOP_HARD);
                        rumble->duration = 0;
                    }
                }
            }
        }
        if(chan) {
            PADReset(chan);
        }
    }
    msmSysRegularProc();
    VCounter++;
}

static void PadADConv(s16 player, PADStatus *status)
{
    
    
}