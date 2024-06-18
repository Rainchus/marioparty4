#include "REL/option.h"
#include "ext_math.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/hsfmotion.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/process.h"
#include "game/window.h"

#include "dolphin.h"
#include "math.h"

typedef struct {
    /* 0x000 */ omObjData *objects[26];
    /* 0x068 */ WindowWork *window[13];
    /* 0x09C */ s32 mode;
    /* 0x0A0 */ s16 sprList[19];
    /* 0x0C6 */ char unkC6[2];
    /* 0x0C8 */ s32 changeTimer;
    /* 0x0CC */ s32 selectedOption;
    /* 0x0D0 */ s32 soundMode;
    /* 0x0D4 */ s32 page;
    /* 0x0D8 */ s32 lSelection; // list selection
    /* 0x0DC */ s32 prevLSelection;
    /* 0x0E0 */ s16 sndGrpSet;
    /* 0x0E2 */ char unkE2[2];
    /* 0x0E4 */ BOOL optionSelected;
    /* 0x0E8 */ BOOL unkE8;
    /* 0x0EC */ BOOL cameraDoneF;
    /* 0x0F0 */ s16 bgMusicStat;
    /* 0x0F2 */ s16 audSeqStat;
    /* 0x0F4 */ s16 audSStreamStat;
    /* 0x0F6 */ s16 audFxStat;
    /* 0x0F8 */ s32 selectionChangeTimer;
    /* 0x0FC */ s32 pageChange;
    /* 0x100 */ s32 lSelectionChange;
    /* 0x104 */ float lSelectionPos;
    /* 0x108 */ float lSelectionChangeSpeed;
    /* 0x10C */ Process *speakerNoteProcess;
} SoundWork; // Size 0x110

typedef struct {
    /* 0x00 */ BOOL enabled;
    /* 0x04 */ s32 noteType;
    /* 0x08 */ s32 speakerId;
    /* 0x0C */ float pos;
    /* 0x10 */ float speed;
} NoteWork; // Size 0x14

typedef struct {
    /* 0x00 */ BOOL enabled;
    /* 0x04 */ s32 nameMess;
    /* 0x08 */ s16 audType;
    /* 0x0A */ s16 sndGrpSet;
    /* 0x0C */ s32 fxId;
} SndSelData; // Size 0x10

#define NUM_NOTES 16

#define MODE_DISABLED 0
#define MODE_HANDLE_INITIAL_SCREEN 1
#define MODE_HANDLE_OPTION_SEL 2
#define MODE_HANDLE_SOUND 3
#define MODE_HANDLE_MUSIC 4
#define MODE_HANDLE_VOICE 5

#define SOUND_MODE_STEREO 0
#define SOUND_MODE_MONO 1

#define NUM_BOARDS 6

#define NOTE_TYPE_QUAVER 0
#define NOTE_TYPE_QUARTER 1

#define SPEAKER_LEFT 0
#define SPEAKER_RIGHT 1

static void HandleInitialScreen(omObjData *object);
static void HandleOptionSel(omObjData *object);
static void HandleSoundSettings(omObjData *object);
static void HandleMusic(omObjData *object);
static void HandleVoice(omObjData *object);
static void TurnOnIndicator(omObjData *object, s32 id);
static void TurnOffIndicators(omObjData *object);
static omObjData *CreateOptionHand(void);
static void KillOptionHand(omObjData *optionHand);
static omObjData *CreateSoundSettingsHand(void);
static void KillSoundSettingsHand(omObjData *soundSettingsHand);
static omObjData *CreateSystem(void);
static void KillSystem(omObjData *system);
static omObjData *CreateIndicator(s32 id, BOOL off);
static void KillIndicator(omObjData *indicator);
static void HideIndicator(omObjData *object);
static void ShowIndicator(omObjData *object);
static void CreateSpr(omObjData *object);
static void KillSpr(omObjData *object);
static void DisplayOptionSel(omObjData *object);
static void HideOptionSel(omObjData *object);
static void DisplaySoundSettings(omObjData *object);
static void HideSoundSettings(omObjData *object);
static void DisplayMusicTitle(omObjData *object, s32 page);
static void HideMusicTitle(omObjData *object);
static void DisplayVoice(omObjData *object, s32 character);
static void HideVoiceTitle(omObjData *object);
static omObjData *CreateNote(s32 noteType);
static void KillNote(omObjData *note);
static void HandleNote(omObjData *note);
static void SpawnNote(omObjData *object, s32 noteType, s32 speakerId, s32 color);
static void CreateNoteProcess(omObjData *object);
static void KillNoteProcess(omObjData *object);
static void HandleNoteProcess(void);
static void PlaySound(omObjData *object);
static void FadeOutCurrSound(omObjData *object);

omObjData *lbl_1_bss_38;

static const s32 musicPageNameTbl[] = {
    MAKE_MESSID(47, 70),
    MAKE_MESSID(47, 81),
    MAKE_MESSID(47, 172),
    MAKE_MESSID(47, 92),
    MAKE_MESSID(47, 101),
    MAKE_MESSID(47, 109),
    MAKE_MESSID(47, 119),
    MAKE_MESSID(47, 173),
    MAKE_MESSID(47, 174),
    MAKE_MESSID(47, 129),
    MAKE_MESSID(47, 140),
    MAKE_MESSID(47, 149),
    MAKE_MESSID(47, 156),
    MAKE_MESSID(47, 176),
};

static const SndSelData musicTbl[14][10] = {
    {
        { TRUE, MAKE_MESSID(47, 71), 1, 0, 20 },
        { TRUE, MAKE_MESSID(47, 72), 2, 79, 43 },
        { TRUE, MAKE_MESSID(47, 73), 3, 81, 44 },
        { TRUE, MAKE_MESSID(47, 74), 29, 80, 45 },
        { TRUE, MAKE_MESSID(47, 76), 30, 82, 47 },
        { TRUE, MAKE_MESSID(47, 78), 1, 0, 12 },
        { TRUE, MAKE_MESSID(47, 77), 4, 83, 48 },
        { TRUE, MAKE_MESSID(47, 80), 11, 90, 40 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 79), 1, 0, 5 },
        { TRUE, MAKE_MESSID(47, 170), 33, 0, 12 },
        { TRUE, MAKE_MESSID(47, 82), 33, 0, 7 },
        { TRUE, MAKE_MESSID(47, 83), 33, 0, 4 },
        { TRUE, MAKE_MESSID(47, 171), 33, 0, 10 },
        { TRUE, MAKE_MESSID(47, 84), 33, 0, 9 },
        { TRUE, MAKE_MESSID(47, 85), 33, 0, 1 },
        { TRUE, MAKE_MESSID(47, 86), 33, 0, 3 },
        { TRUE, MAKE_MESSID(47, 87), 33, 0, 2 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 88), 33, 0, 5 },
        { TRUE, MAKE_MESSID(47, 89), 33, 0, 6 },
        { TRUE, MAKE_MESSID(47, 90), 33, 0, 11 },
        { TRUE, MAKE_MESSID(47, 91), 33, 0, 8 },
        { TRUE, MAKE_MESSID(47, 125), 1, 0, 2 },
        { TRUE, MAKE_MESSID(47, 126), 1, 0, 6 },
        { TRUE, MAKE_MESSID(47, 127), 1, 0, 9 },
        { TRUE, MAKE_MESSID(47, 128), 1, 0, 10 },
        { TRUE, MAKE_MESSID(47, 124), 12, 93, 49 },
        { TRUE, MAKE_MESSID(47, 123), 12, 93, 50 },
    },
    {
        { TRUE, MAKE_MESSID(47, 93), 5, 84, 13 },
        { TRUE, MAKE_MESSID(47, 94), 5, 84, 14 },
        { TRUE, MAKE_MESSID(47, 95), 5, 84, 15 },
        { TRUE, MAKE_MESSID(47, 96), 5, 84, 16 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 97), 6, 85, 17 },
        { TRUE, MAKE_MESSID(47, 98), 6, 85, 18 },
        { TRUE, MAKE_MESSID(47, 99), 6, 85, 19 },
        { TRUE, MAKE_MESSID(47, 100), 6, 85, 20 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 102), 7, 86, 21 },
        { TRUE, MAKE_MESSID(47, 103), 7, 86, 22 },
        { TRUE, MAKE_MESSID(47, 104), 7, 86, 23 },
        { TRUE, MAKE_MESSID(47, 105), 7, 86, 24 },
        { TRUE, MAKE_MESSID(47, 106), 7, 86, 25 },
        { TRUE, MAKE_MESSID(47, 107), 7, 86, 26 },
        { TRUE, MAKE_MESSID(47, 108), 7, 86, 27 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 110), 8, 87, 28 },
        { TRUE, MAKE_MESSID(47, 111), 8, 87, 30 },
        { TRUE, MAKE_MESSID(47, 112), 8, 87, 29 },
        { TRUE, MAKE_MESSID(47, 113), 8, 87, 31 },
        { TRUE, MAKE_MESSID(47, 114), 8, 87, 32 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 115), 9, 88, 33 },
        { TRUE, MAKE_MESSID(47, 116), 9, 88, 34 },
        { TRUE, MAKE_MESSID(47, 117), 9, 88, 35 },
        { TRUE, MAKE_MESSID(47, 118), 9, 88, 36 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 120), 10, 89, 37 },
        { TRUE, MAKE_MESSID(47, 121), 10, 89, 38 },
        { TRUE, MAKE_MESSID(47, 122), 10, 89, 39 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 130), 13, 94, 59 },
        { TRUE, MAKE_MESSID(47, 131), 13, 94, 57 },
        { TRUE, MAKE_MESSID(47, 132), 14, 95, 67 },
        { TRUE, MAKE_MESSID(47, 133), 15, 96, 68 },
        { TRUE, MAKE_MESSID(47, 134), 16, 97, 69 },
        { TRUE, MAKE_MESSID(47, 135), 17, 98, 70 },
        { TRUE, MAKE_MESSID(47, 136), 18, 99, 71 },
        { TRUE, MAKE_MESSID(47, 137), 19, 100, 72 },
        { TRUE, MAKE_MESSID(47, 138), 20, 101, 73 },
        { TRUE, MAKE_MESSID(47, 139), 21, 102, 74 },
    },
    {
        { TRUE, MAKE_MESSID(47, 141), 22, 103, 75 },
        { TRUE, MAKE_MESSID(47, 142), 23, 104, 76 },
        { TRUE, MAKE_MESSID(47, 143), 24, 105, 77 },
        { TRUE, MAKE_MESSID(47, 144), 13, 94, 58 },
        { TRUE, MAKE_MESSID(47, 175), 13, 94, 60 },
        { TRUE, MAKE_MESSID(47, 145), 1, 0, 1 },
        { TRUE, MAKE_MESSID(47, 146), 1, 0, 3 },
        { TRUE, MAKE_MESSID(47, 147), 1, 0, 4 },
        { TRUE, MAKE_MESSID(47, 148), 1, 0, 11 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 152), 25, 106, 61 },
        { TRUE, MAKE_MESSID(47, 150), 25, 106, 62 },
        { TRUE, MAKE_MESSID(47, 151), 25, 106, 63 },
        { TRUE, MAKE_MESSID(47, 155), 26, 107, 65 },
        { TRUE, MAKE_MESSID(47, 153), 26, 107, 64 },
        { TRUE, MAKE_MESSID(47, 154), 26, 107, 66 },
        { TRUE, MAKE_MESSID(47, 164), 1, 0, 13 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 157), 27, 108, 51 },
        { TRUE, MAKE_MESSID(47, 158), 27, 108, 53 },
        { TRUE, MAKE_MESSID(47, 159), 27, 108, 54 },
        { TRUE, MAKE_MESSID(47, 160), 27, 108, 52 },
        { TRUE, MAKE_MESSID(47, 161), 27, 108, 55 },
        { TRUE, MAKE_MESSID(47, 162), 27, 108, 56 },
        { TRUE, MAKE_MESSID(47, 163), 1, 0, 7 },
        { TRUE, MAKE_MESSID(47, 165), 1, 0, 22 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 177), 32, 92, 46 },
        { TRUE, MAKE_MESSID(47, 178), 31, 91, 41 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
        { FALSE, MAKE_MESSID(47, 69), 0, 0, 0 },
    },
};

static const s32 voiceCharNameTbl[12] = {
    MAKE_MESSID(0, 0),
    MAKE_MESSID(0, 1),
    MAKE_MESSID(0, 2),
    MAKE_MESSID(0, 3),
    MAKE_MESSID(0, 4),
    MAKE_MESSID(0, 5),
    MAKE_MESSID(0, 6),
    MAKE_MESSID(0, 7),
    MAKE_MESSID(47, 34),
    MAKE_MESSID(47, 44),
    MAKE_MESSID(47, 55),
    MAKE_MESSID(47, 62),
};

static const SndSelData voiceTbl[12][10] = {
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2217 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2219 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2216 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2223 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2220 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2221 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2222 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2218 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2208 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2210 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2207 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2214 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2211 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2212 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2213 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2209 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2226 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2228 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2225 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2232 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2229 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2230 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2231 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2227 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2253 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2255 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2252 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2259 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2256 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2257 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2258 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2254 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2244 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2246 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2243 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2250 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2247 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2248 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2249 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2245 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2199 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2201 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2198 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2205 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2202 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2203 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2204 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2200 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2190 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2192 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2189 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2196 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2193 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2194 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2195 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2191 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 26), 28, 109, 2235 },
        { TRUE, MAKE_MESSID(47, 27), 28, 109, 2237 },
        { TRUE, MAKE_MESSID(47, 28), 28, 109, 2234 },
        { TRUE, MAKE_MESSID(47, 29), 28, 109, 2241 },
        { TRUE, MAKE_MESSID(47, 30), 28, 109, 2238 },
        { TRUE, MAKE_MESSID(47, 31), 28, 109, 2239 },
        { TRUE, MAKE_MESSID(47, 32), 28, 109, 2240 },
        { TRUE, MAKE_MESSID(47, 33), 28, 109, 2236 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 35), 28, 109, 54 },
        { TRUE, MAKE_MESSID(47, 36), 28, 109, 55 },
        { TRUE, MAKE_MESSID(47, 37), 28, 109, 56 },
        { TRUE, MAKE_MESSID(47, 38), 28, 109, 67 },
        { TRUE, MAKE_MESSID(47, 39), 28, 109, 68 },
        { TRUE, MAKE_MESSID(47, 40), 28, 109, 69 },
        { TRUE, MAKE_MESSID(47, 41), 28, 109, 64 },
        { TRUE, MAKE_MESSID(47, 42), 28, 109, 65 },
        { TRUE, MAKE_MESSID(47, 43), 28, 109, 66 },
        { FALSE, MAKE_MESSID(47, 24), 0, 0, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 45), 28, 109, 75 },
        { TRUE, MAKE_MESSID(47, 46), 28, 109, 76 },
        { TRUE, MAKE_MESSID(47, 47), 28, 109, 77 },
        { TRUE, MAKE_MESSID(47, 48), 28, 109, 70 },
        { TRUE, MAKE_MESSID(47, 49), 28, 109, 71 },
        { TRUE, MAKE_MESSID(47, 50), 28, 109, 72 },
        { TRUE, MAKE_MESSID(47, 51), 28, 109, 58 },
        { TRUE, MAKE_MESSID(47, 52), 28, 109, 59 },
        { TRUE, MAKE_MESSID(47, 53), 28, 109, 60 },
        { TRUE, MAKE_MESSID(47, 54), 28, 109, 61 },
    },
    {
        { TRUE, MAKE_MESSID(47, 56), 28, 109, 62 },
        { TRUE, MAKE_MESSID(47, 57), 28, 109, 63 },
        { TRUE, MAKE_MESSID(47, 58), 28, 109, 79 },
        { TRUE, MAKE_MESSID(47, 59), 28, 109, 80 },
        { TRUE, MAKE_MESSID(47, 60), 28, 109, 73 },
        { TRUE, MAKE_MESSID(47, 61), 28, 109, 74 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
    {
        { TRUE, MAKE_MESSID(47, 63), 28, 109, 36 },
        { TRUE, MAKE_MESSID(47, 64), 28, 109, 37 },
        { TRUE, MAKE_MESSID(47, 65), 28, 109, 38 },
        { TRUE, MAKE_MESSID(47, 67), 28, 109, 40 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
        { FALSE, MAKE_MESSID(47, 24), 28, 109, 0 },
    },
};

static BOOL musicPageEnabledTbl[14] = { TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE };

static omObjFunc modes[] = { NULL, HandleInitialScreen, HandleOptionSel, HandleSoundSettings, HandleMusic, HandleVoice };

static s32 optionTextTbl[] = { MAKE_MESSID(47, 8), MAKE_MESSID(47, 10), MAKE_MESSID(47, 9) };

omObjData *fn_1_4028(void)
{
    omObjData *object;
    SoundWork *work;
    s32 i;

    object = omAddObjEx(lbl_1_bss_8, 1003, 0, 0, 1, NULL);
    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(SoundWork), MEMORY_DEFAULT_NUM);
    object->data = work;
    work->selectedOption = 0;
    work->unkE8 = FALSE;
    work->optionSelected = FALSE;
    work->bgMusicStat = -2;
    work->audSeqStat = -1;
    work->audSStreamStat = -1;
    work->audFxStat = -1;
    work->speakerNoteProcess = NULL;
    switch (GWGameStat.sound_mode) {
        case 0:
            work->soundMode = SOUND_MODE_MONO;
            break;
        case 2:
        default:
            work->soundMode = SOUND_MODE_STEREO;
            break;
    }

    work->objects[0] = CreateSystem();
    for (i = 0; i < 6; i++) {
        work->objects[i + 1] = CreateIndicator(i % 3, (i / 3) > 0);
    }
    TurnOffIndicators(object);
    work->objects[7] = CreateOptionHand();
    work->objects[8] = CreateSoundSettingsHand();
    for (i = 0; i < NUM_NOTES; i++) {
        work->objects[i + 10] = CreateNote((i / 8) == 0 ? NOTE_TYPE_QUAVER : NOTE_TYPE_QUARTER);
    }
    CreateSpr(object);
    fn_1_4388(object, MODE_DISABLED);
    for (i = 0; i < NUM_BOARDS; i++) {
        musicPageEnabledTbl[i + 3] = (GWGameStat.board_play_count[i] != 0) ? TRUE : FALSE;
    }
    musicPageEnabledTbl[11] = (GWGameStat.field10E_bit6 != 0) ? TRUE : FALSE;
    musicPageEnabledTbl[12] = (GWGameStat.field10E_bit6 != 0) ? TRUE : FALSE;
    musicPageEnabledTbl[13] = (GWGameStat.field10E_bit6 != 0) ? TRUE : FALSE;
    return object;
}

void fn_1_42DC(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    KillOptionHand(work->objects[7]);
    KillSoundSettingsHand(work->objects[8]);
    KillSystem(work->objects[0]);
    for (i = 0; i < 6; i++) {
        KillIndicator(work->objects[i + 1]);
    }
    for (i = 0; i < 16; i++) {
        KillNote(work->objects[i + 10]);
    }
    KillSpr(object);
    HuMemDirectFree(work);
}

void fn_1_4388(omObjData *object, s32 mode)
{
    SoundWork *work = object->data;

    work->mode = mode;
    object->func = modes[mode];
    object->unk10 = 0;
    object->unk10 = 0;
}

s32 fn_1_43CC(omObjData *object)
{
    SoundWork *work = object->data;

    return work->mode;
}

static void HandleInitialScreen(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    switch (object->unk10) {
        case 0:
            if (!work->unkE8) {
                work->window[0] = fn_1_A44C(0);
                work->window[1] = fn_1_A44C(1);
                work->window[2] = fn_1_A44C(2);
                for (i = 0; i < 10; i++) {
                    work->window[i + 3] = fn_1_A44C(3);
                }
                fn_1_AF0(lbl_1_bss_10, 0.0f, 120.0f, -600.0f, 0x28);
                fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, -350.0f, 0x28);
                work->unkE8 = TRUE;
                work->selectedOption = 0;
                work->optionSelected = FALSE;
                object->unk10 = 1;
            }
            else {
                object->unk10 = 2;
            }
            break;
        case 1:
            if (fn_1_CB8(lbl_1_bss_10) == 0) {
                fn_1_4388(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
        case 2:
            for (i = 0; i < 13; i++) {
                fn_1_A6AC(work->window[i]);
            }
            fn_1_AF0(lbl_1_bss_10, 0.0f, 120.0f, -600.0f, 0x28);
            fn_1_A6C(lbl_1_bss_10, 0.0f, 120.0f, 0.0f, 0x28);
            work->unkE8 = FALSE;
            work->optionSelected = FALSE;
            fn_1_4388(object, MODE_DISABLED);
            break;
    }
}

static void HandleOptionSel(omObjData *object)
{
    SoundWork *work = object->data;

    switch (object->unk10) {
        case 0:
            TurnOffIndicators(object);
            work->lSelection = work->selectedOption;
            if (!work->optionSelected) {
                fn_1_3D54(lbl_1_bss_30);
            }
            else {
                HideSoundSettings(object);
                HideMusicTitle(object);
                HideVoiceTitle(object);
            }
            work->optionSelected = FALSE;
            work->cameraDoneF = FALSE;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            DisplayOptionSel(object);
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 168));
            fn_1_A6EC(work->window[0]);
            fn_1_A71C(work->window[0], optionTextTbl[work->lSelection]);
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->objects[7]->model[0], 1);
                work->cameraDoneF = TRUE;
            }
            omSetTra(work->objects[7], -34.0f + 40.0f * work->lSelection, 120.0f, -500.0f);
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (fn_1_550(PAD_BUTTON_A)) {
                    work->selectedOption = work->lSelection;
                    work->optionSelected = TRUE;
                    TurnOnIndicator(object, work->selectedOption);
                    HuAudFXPlay(2);
                    object->unk10 = 3;
                }
                else if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 3;
                }
                else if (fn_1_584(1) && work->lSelection > 0) {
                    work->lSelection--;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (fn_1_584(2) && work->lSelection < 2) {
                    work->lSelection++;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
            }
            break;
        case 3:
            fn_1_A704(work->window[1]);
            fn_1_A704(work->window[0]);
            if (!work->optionSelected) {
                fn_1_3E1C(lbl_1_bss_30);
            }
            Hu3DModelAttrSet(work->objects[7]->model[0], 1);
            object->unk10 = 4;
            /* fallthrough */
        case 4:
            if ((work->optionSelected || !fn_1_3ED0(lbl_1_bss_30)) && work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (work->optionSelected) {
                    switch (work->selectedOption) {
                        case 0:
                            fn_1_4388(object, MODE_HANDLE_SOUND);
                            break;
                        case 1:
                            fn_1_4388(object, MODE_HANDLE_MUSIC);
                            break;
                        case 2:
                            fn_1_4388(object, MODE_HANDLE_VOICE);
                            break;
                    }
                }
                else {
                    HideOptionSel(object);
                    fn_1_4388(object, MODE_HANDLE_INITIAL_SCREEN);
                }
            }
            break;
    }
}

static const s32 outputModeTbl[] = { 2, 0 };
static const s32 soundModeTbl[] = { 1, 0 };

static const s32 soundModeNameTbl[] = { MAKE_MESSID(47, 11), MAKE_MESSID(47, 12) };

static void HandleSoundSettings(omObjData *object)
{
    SoundWork *work = object->data;
    Vec sp8;

    switch (object->unk10) {
        case 0:
            HideOptionSel(object);
            work->optionSelected = FALSE;
            work->lSelection = work->soundMode;
            work->cameraDoneF = FALSE;
            work->optionSelected = FALSE;
            CreateNoteProcess(object);
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            DisplaySoundSettings(object);
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 168));
            fn_1_A6EC(work->window[0]);
            fn_1_A71C(work->window[0], soundModeNameTbl[work->soundMode]);
            if (!work->cameraDoneF) {
                Hu3DModelAttrReset(work->objects[8]->model[0], 1);
                work->cameraDoneF = TRUE;
            }
            sp8.x = -38.0f;
            sp8.y = 140.0f - 15.0f * work->lSelection;
            sp8.z = -500.0f;
            omSetTra(work->objects[8], sp8.x, sp8.y, sp8.z);
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (fn_1_550(PAD_BUTTON_A)) {
                    work->soundMode = work->lSelection;
                    if (work->soundMode == SOUND_MODE_STEREO) {
                        HuAudFXPlay(0x841);
                    }
                    else {
                        HuAudFXPlay(0x842);
                    }
                    GWGameStat.sound_mode = outputModeTbl[work->lSelection];
                    msmSysSetOutputMode(outputModeTbl[work->lSelection]);
                    OSSetSoundMode(soundModeTbl[work->lSelection]);
                    work->optionSelected = TRUE;
                    DisplaySoundSettings(object);
                    work->changeTimer = 0;
                    object->unk10 = 3;
                }
                else if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    object->unk10 = 4;
                }
                else if (fn_1_584(8) != 0 && work->lSelection > 0) {
                    work->lSelection--;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
                else if (fn_1_584(4) != 0 && work->lSelection < 1) {
                    work->lSelection++;
                    HuAudFXPlay(0);
                    object->unk10 = 1;
                }
            }
            break;
        case 3:
            if (work->changeTimer++ >= 60) {
                object->unk10 = 4;
                return;
            }
            break;
        case 4:
            KillNoteProcess(object);
            fn_1_A704(work->window[1]);
            fn_1_A704(work->window[0]);
            Hu3DModelAttrSet(work->objects[8]->model[0], 1);
            object->unk10 = 5;
            /* fallthrough */
        case 5:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                work->optionSelected = FALSE;
                DisplaySoundSettings(object);
                work->optionSelected = TRUE;
                fn_1_4388(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void HandleMusic(omObjData *object)
{
    SoundWork *work = object->data;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    s32 i;
    s32 newSelection;
    s32 sp8;

    sp8 = work->lSelection;
    switch (object->unk10) {
        case 0:
            HideOptionSel(object);
            work->page = 0;
            work->lSelectionChange = 0;
            work->pageChange = 0;
            espBankSet(work->sprList[14], 0);
            espBankSet(work->sprList[15], 2);
            espPosSet(work->sprList[14], 36.0f, 222.0f);
            espPosSet(work->sprList[15], 544.0f, 222.0f);
            fn_1_160(work->sprList[14], 1, 5);
            fn_1_160(work->sprList[15], 1, 5);
            work->selectionChangeTimer = 0;
            object->unk10 = 1;
            /* fallthrough */
        case 1:
            work->lSelection = 0;
            work->prevLSelection = 0;
            if (work->pageChange != 0) {
                do {
                    work->page += work->pageChange;
                    if (work->page >= 14) {
                        work->page = 0;
                    }
                    else if (work->page < 0) {
                        work->page = 13;
                    }
                } while (!musicPageEnabledTbl[work->page]);
                HuAudFXPlay(0x840);
                if (work->pageChange > 0) {
                    espBankSet(work->sprList[15], 3);
                }
                else {
                    espBankSet(work->sprList[14], 1);
                }
                work->selectionChangeTimer = 5;
                work->pageChange = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->lSelectionChange != 0) {
                newSelection = work->lSelection + work->lSelectionChange;
                if (newSelection > 9) {
                    newSelection = 9;
                }
                else if (newSelection < 0) {
                    newSelection = 0;
                }
                if (!musicTbl[work->page][newSelection].enabled) {
                    if (work->lSelection < 5) {
                        for (i = newSelection; i >= 5; i--) {
                            if (musicTbl[work->page][i].enabled) {
                                newSelection = i;
                                break;
                            }
                        }
                        if (i < 5) {
                            newSelection = work->lSelection;
                        }
                    }
                    else {
                        newSelection = work->lSelection;
                    }
                }
                work->prevLSelection = work->lSelection;
                if (work->lSelection != newSelection) {
                    work->lSelection = newSelection;
                    HuAudFXPlay(0x840);
                }
                work->lSelectionChange = 0;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            DisplayMusicTitle(object, work->page);
            fn_1_A6EC(work->window[0]);
            fn_1_A71C(work->window[0], MAKE_MESSID(47, 10));
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 18));
            espDispOn(work->sprList[18]);
            work->lSelectionPos = 0.0f;
            work->lSelectionChangeSpeed = 0.0625f;
            if (work->selectionChangeTimer > 0) {
                object->unk10 = 5;
            }
            else {
                object->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            temp_f31 = 166.0f + 244.0f * (work->prevLSelection / 5);
            temp_f30 = 144.0f + 29.0f * (work->prevLSelection % 5);
            temp_f27 = 166.0f + 244.0f * (work->lSelection / 5);
            temp_f26 = 144.0f + 29.0f * (work->lSelection % 5);
            temp_f29 = temp_f31 + work->lSelectionPos * (temp_f27 - temp_f31);
            temp_f28 = temp_f30 + work->lSelectionPos * (temp_f26 - temp_f30);
            espPosSet(work->sprList[18], temp_f29, temp_f28);
            if ((work->lSelectionPos += work->lSelectionChangeSpeed) < 1.0f) {
                break;
            }
            espPosSet(work->sprList[18], 166.0f + 244.0f * (work->lSelection / 5), 144.0f + 29.0f * (work->lSelection % 5));
            object->unk10 = 6;
            break;
        case 5:
            if (work->selectionChangeTimer > 0) {
                work->selectionChangeTimer--;
                break;
            }
            espBankSet(work->sprList[14], 0);
            espBankSet(work->sprList[15], 2);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (fn_1_550(PAD_BUTTON_A)) {
                    if (work->bgMusicStat == -2) {
                        HuAudFadeOut(0x64);
                        work->bgMusicStat = -1;
                    }
                    else if (work->bgMusicStat != -1) {
                        HuAudSeqFadeOut(work->bgMusicStat, 0x64);
                        work->bgMusicStat = -1;
                    }
                    PlaySound(object);
                }
                else if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    work->changeTimer = 0;
                    object->unk10 = 7;
                }
                else {
                    if (fn_1_5B8(1) != 0 && work->lSelection >= 5) {
                        work->lSelectionChange -= 5;
                    }
                    else if (fn_1_5B8(2) != 0 && work->lSelection < 5) {
                        work->lSelectionChange += 5;
                    }
                    if (fn_1_5B8(8) != 0 && work->lSelection % 5 > 0) {
                        work->lSelectionChange--;
                    }
                    else if (fn_1_5B8(4) != 0 && work->lSelection % 5 < 4) {
                        work->lSelectionChange++;
                    }
                    if (work->lSelectionChange != 0) {
                        object->unk10 = 2;
                    }
                    else if (fn_1_550(PAD_TRIGGER_L)) {
                        work->pageChange = -1;
                    }
                    else if (fn_1_550(PAD_TRIGGER_R)) {
                        work->pageChange = 1;
                    }
                    if (work->pageChange != 0) {
                        object->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            fn_1_A704(work->window[1]);
            fn_1_A704(work->window[0]);
            FadeOutCurrSound(object);
            fn_1_160(work->sprList[14], 0, 5);
            fn_1_160(work->sprList[15], 0, 5);
            object->unk10 = 8;
            /* fallthrough */
        case 8:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                espDispOff(work->sprList[18]);
                if (work->bgMusicStat == -1) {
                    work->bgMusicStat = HuAudSeqPlay(0x2D);
                }
                fn_1_4388(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void HandleVoice(omObjData *object)
{
    SoundWork *work = object->data;
    float temp_f31;
    float temp_f30;
    float temp_f29;
    float temp_f28;
    float temp_f27;
    float temp_f26;
    s32 var_r28;
    s32 newSelection;

    switch (object->unk10) {
        case 0:
            HideOptionSel(object);
            work->page = 0;
            work->lSelectionChange = 0;
            work->pageChange = 0;
            espBankSet(work->sprList[14], 0);
            espBankSet(work->sprList[15], 2);
            espPosSet(work->sprList[14], 36.0f, 222.0f);
            espPosSet(work->sprList[15], 544.0f, 222.0f);
            fn_1_160(work->sprList[14], 1, 5);
            fn_1_160(work->sprList[15], 1, 5);
            work->selectionChangeTimer = 0;
            object->unk10 = 3;
            /* fallthrough */
        case 1:
            work->lSelection = 0;
            work->prevLSelection = 0;
            if (work->pageChange != 0) {
                work->page += work->pageChange;
                if (work->page > 11) {
                    work->page = 0;
                }
                else if (work->page < 0) {
                    work->page = 11;
                }
                HuAudFXPlay(0x840);
                if (work->pageChange > 0) {
                    espBankSet(work->sprList[15], 3);
                }
                else {
                    espBankSet(work->sprList[14], 1);
                }
                work->selectionChangeTimer = 5;
                work->pageChange = 0;
            }
            object->unk10 = 2;
            /* fallthrough */
        case 2:
            if (work->lSelectionChange != 0) {
                newSelection = work->lSelection + work->lSelectionChange;
                if (newSelection > 9) {
                    newSelection = 9;
                }
                else if (newSelection < 0) {
                    newSelection = 0;
                }
                if (!voiceTbl[work->page][newSelection].enabled) {
                    if (work->lSelection < 5) {
                        for (var_r28 = newSelection; var_r28 >= 5; var_r28--) {
                            if (voiceTbl[work->page][var_r28].enabled) {
                                newSelection = var_r28;
                                break;
                            }
                        }
                        if (var_r28 < 5) {
                            newSelection = work->lSelection;
                        }
                    }
                    else {
                        newSelection = work->lSelection;
                    }
                }
                work->prevLSelection = work->lSelection;
                if (work->lSelection != newSelection) {
                    work->lSelection = newSelection;
                    HuAudFXPlay(0x840);
                }
                work->lSelectionChange = 0;
            }
            object->unk10 = 3;
            /* fallthrough */
        case 3:
            DisplayVoice(object, work->page);
            fn_1_A6EC(work->window[0]);
            fn_1_A71C(work->window[0], MAKE_MESSID(47, 9));
            fn_1_A6EC(work->window[1]);
            fn_1_A71C(work->window[1], MAKE_MESSID(47, 18));
            espDispOn(work->sprList[18]);
            work->lSelectionPos = 0.0f;
            work->lSelectionChangeSpeed = 0.0625f;
            if (work->selectionChangeTimer > 0) {
                object->unk10 = 5;
            }
            else {
                object->unk10 = 4;
            }
            /* fallthrough */
        case 4:
            temp_f31 = 166.0f + 244.0f * (work->prevLSelection / 5);
            temp_f30 = 144.0f + 29.0f * (work->prevLSelection % 5);
            temp_f27 = 166.0f + 244.0f * (work->lSelection / 5);
            temp_f26 = 144.0f + 29.0f * (work->lSelection % 5);
            temp_f29 = temp_f31 + work->lSelectionPos * (temp_f27 - temp_f31);
            temp_f28 = temp_f30 + work->lSelectionPos * (temp_f26 - temp_f30);
            espPosSet(work->sprList[18], temp_f29, temp_f28);
            if ((work->lSelectionPos += work->lSelectionChangeSpeed) < 1.0f) {
                break;
            }
            espPosSet(work->sprList[18], 166.0f + 244.0f * (work->lSelection / 5), 144.0f + 29.0f * (work->lSelection % 5));
            object->unk10 = 6;
            break;
        case 5:
            if (work->selectionChangeTimer > 0) {
                work->selectionChangeTimer--;
                break;
            }
            espBankSet(work->sprList[14], 0);
            espBankSet(work->sprList[15], 2);
            object->unk10 = 6;
            /* fallthrough */
        case 6:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                if (fn_1_550(PAD_BUTTON_A)) {
                    PlaySound(object);
                }
                else if (fn_1_550(PAD_BUTTON_B)) {
                    HuAudFXPlay(3);
                    work->changeTimer = 0;
                    object->unk10 = 7;
                }
                else {
                    if (fn_1_5B8(1) != 0 && work->lSelection >= 5) {
                        work->lSelectionChange -= 5;
                    }
                    else if (fn_1_5B8(2) != 0 && work->lSelection < 5) {
                        work->lSelectionChange += 5;
                    }
                    if (fn_1_5B8(8) != 0 && work->lSelection % 5 > 0) {
                        work->lSelectionChange--;
                    }
                    else if (fn_1_5B8(4) != 0 && work->lSelection % 5 < 4) {
                        work->lSelectionChange++;
                    }
                    if (work->lSelectionChange != 0) {
                        object->unk10 = 2;
                    }
                    else if (fn_1_550(PAD_TRIGGER_L)) {
                        work->pageChange = -1;
                    }
                    else if (fn_1_550(PAD_TRIGGER_R)) {
                        work->pageChange = 1;
                    }
                    if (work->pageChange != 0) {
                        object->unk10 = 1;
                    }
                }
            }
            break;
        case 7:
            fn_1_A704(work->window[1]);
            fn_1_A704(work->window[0]);
            FadeOutCurrSound(object);
            fn_1_160(work->sprList[14], 0, 5);
            fn_1_160(work->sprList[15], 0, 5);
            object->unk10 = 8;
            /* fallthrough */
        case 8:
            if (work->window[0]->state == 0 && work->window[1]->state == 0) {
                espDispOff(work->sprList[18]);
                fn_1_4388(object, MODE_HANDLE_OPTION_SEL);
            }
            break;
    }
}

static void TurnOnIndicator(omObjData *object, s32 id)
{
    SoundWork *work = object->data;

    switch (id) {
        case 0:
            HideIndicator(work->objects[1]);
            HideIndicator(work->objects[5]);
            HideIndicator(work->objects[6]);
            ShowIndicator(work->objects[4]);
            ShowIndicator(work->objects[2]);
            ShowIndicator(work->objects[3]);
            break;
        case 1:
            HideIndicator(work->objects[4]);
            HideIndicator(work->objects[2]);
            HideIndicator(work->objects[6]);
            ShowIndicator(work->objects[1]);
            ShowIndicator(work->objects[5]);
            ShowIndicator(work->objects[3]);
            break;
        case 2:
            HideIndicator(work->objects[4]);
            HideIndicator(work->objects[5]);
            HideIndicator(work->objects[3]);
            ShowIndicator(work->objects[1]);
            ShowIndicator(work->objects[2]);
            ShowIndicator(work->objects[6]);
            break;
    }
}

static void TurnOffIndicators(omObjData *object)
{
    SoundWork *work = object->data;

    HideIndicator(work->objects[4]);
    HideIndicator(work->objects[5]);
    HideIndicator(work->objects[6]);
    ShowIndicator(work->objects[1]);
    ShowIndicator(work->objects[2]);
    ShowIndicator(work->objects[3]);
}

static omObjData *CreateOptionHand(void)
{
    omObjData *optionHand;

    optionHand = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    optionHand->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 13));
    Hu3DModelLayerSet(optionHand->model[0], 2);
    Hu3DModelAttrSet(optionHand->model[0], 0x40000001);
    omSetRot(optionHand, -80.0f, 45.0f, 0.0f);
    omSetSca(optionHand, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(optionHand->model[0], 1);
    return optionHand;
}

static void KillOptionHand(omObjData *optionHand)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(optionHand->model[i]);
    }
}

static omObjData *CreateSoundSettingsHand(void)
{
    omObjData *soundSettingsHand;

    soundSettingsHand = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    soundSettingsHand->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 14));
    Hu3DModelLayerSet(soundSettingsHand->model[0], 2);
    Hu3DModelAttrSet(soundSettingsHand->model[0], 0x40000001);
    omSetRot(soundSettingsHand, 0.0f, -90.0f, 0.0f);
    omSetSca(soundSettingsHand, 0.6f, 0.6f, 0.6f);
    Hu3DModelAttrSet(soundSettingsHand->model[0], 1);
    return soundSettingsHand;
}

static void KillSoundSettingsHand(omObjData *settingsHand)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(settingsHand->model[i]);
    }
}

static omObjData *CreateSystem(void)
{
    omObjData *system;

    system = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    system->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 3));
    Hu3DModelAttrSet(system->model[0], 0x40000001);
    Hu3DModelLayerSet(system->model[0], 0);
    return system;
}

static void KillSystem(omObjData *system)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(system->model[i]);
    }
}

static const Vec indicatorPosTbl[3] = { { -40.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 40.0f, 0.0f, 0.0f } };

static omObjData *CreateIndicator(s32 id, BOOL off)
{
    omObjData *indicator;

    indicator = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    if (off) {
        indicator->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 5));
    }
    else {
        indicator->model[0] = Hu3DModelCreateFile(DATA_MAKE_NUM(DATADIR_OPTION, 4));
    }
    Hu3DModelAttrSet(indicator->model[0], 0x40000001);
    Hu3DModelLayerSet(indicator->model[0], 0);
    omSetTra(indicator, indicatorPosTbl[id].x, indicatorPosTbl[id].y, indicatorPosTbl[id].z);
    return indicator;
}

static void KillIndicator(omObjData *indicator)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(indicator->model[i]);
    }
}

static void HideIndicator(omObjData *indicator)
{
    Hu3DModelAttrReset(indicator->model[0], 1);
}

static void ShowIndicator(omObjData *indicator)
{
    Hu3DModelAttrSet(indicator->model[0], 1);
}

static s32 sprTbl[] = {
    DATA_MAKE_NUM(DATADIR_OPTION, 38),
    DATA_MAKE_NUM(DATADIR_OPTION, 39),
    DATA_MAKE_NUM(DATADIR_OPTION, 40),
    DATA_MAKE_NUM(DATADIR_OPTION, 35),
    DATA_MAKE_NUM(DATADIR_OPTION, 36),
    DATA_MAKE_NUM(DATADIR_OPTION, 37),
    DATA_MAKE_NUM(DATADIR_OPTION, 41),
    DATA_MAKE_NUM(DATADIR_OPTION, 43),
    DATA_MAKE_NUM(DATADIR_OPTION, 42),
    DATA_MAKE_NUM(DATADIR_OPTION, 44),
    DATA_MAKE_NUM(DATADIR_OPTION, 45),
    DATA_MAKE_NUM(DATADIR_OPTION, 46),
    DATA_MAKE_NUM(DATADIR_OPTION, 47),
    DATA_MAKE_NUM(DATADIR_OPTION, 48),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 49),
    DATA_MAKE_NUM(DATADIR_OPTION, 63),
    DATA_MAKE_NUM(DATADIR_OPTION, 64),
    DATA_MAKE_NUM(DATADIR_OPTION, 65),
};

static void CreateSpr(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        work->sprList[i] = espEntry(sprTbl[i], 0, 0);
        espDrawNoSet(work->sprList[i], 0x40);
        espDispOff(work->sprList[i]);
    }
    espBankSet(work->sprList[14], 0);
    espBankSet(work->sprList[15], 2);
    HuSprExecLayerSet(0x40, 1);
}

static void KillSpr(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 19; i++) {
        espKill(work->sprList[i]);
    }
}

static void DisplayOptionSel(omObjData *object)
{
    SoundWork *work = object->data;
    float temp_f31 = 288.0f;
    float temp_f30 = 188.0f;

    espPosSet(work->sprList[12], 288.0f, 72.0f);
    espPosSet(work->sprList[0], temp_f31 + -112.0f, temp_f30);
    espPosSet(work->sprList[3], temp_f31 + -112.0f, temp_f30);
    espPosSet(work->sprList[1], temp_f31, temp_f30);
    espPosSet(work->sprList[4], temp_f31, temp_f30);
    espPosSet(work->sprList[2], temp_f31 + 112.0f, temp_f30);
    espPosSet(work->sprList[5], temp_f31 + 112.0f, temp_f30);
    espDispOn(work->sprList[12]);
    switch (work->lSelection) {
        case 0:
            espDispOn(work->sprList[3]);
            espDispOn(work->sprList[1]);
            espDispOn(work->sprList[2]);
            espDispOff(work->sprList[0]);
            espDispOff(work->sprList[4]);
            espDispOff(work->sprList[5]);
            break;
        case 1:
            espDispOn(work->sprList[0]);
            espDispOn(work->sprList[4]);
            espDispOn(work->sprList[2]);
            espDispOff(work->sprList[3]);
            espDispOff(work->sprList[1]);
            espDispOff(work->sprList[5]);
            break;
        case 2:
            espDispOn(work->sprList[0]);
            espDispOn(work->sprList[1]);
            espDispOn(work->sprList[5]);
            espDispOff(work->sprList[3]);
            espDispOff(work->sprList[4]);
            espDispOff(work->sprList[2]);
            break;
    }
}

static const s32 optionSelSprIdxTbl[] = { 12, 0, 1, 2, 3, 4, 5 };

static void HideOptionSel(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(work->sprList[optionSelSprIdxTbl[i]]);
    }
}

static void DisplaySoundSettings(omObjData *object)
{
    SoundWork *work = object->data;
    float temp_f31 = 290.0f;
    float temp_f30 = 192.0f;

    espPosSet(work->sprList[13], 288.0f, 72.0f);
    espPosSet(work->sprList[6], temp_f31, temp_f30 - 32.0f);
    espPosSet(work->sprList[7], temp_f31, temp_f30 - 32.0f);
    espPosSet(work->sprList[8], temp_f31, temp_f30 + 32.0f);
    espPosSet(work->sprList[9], temp_f31, temp_f30 + 32.0f);
    switch (work->lSelection) {
        case 0:
            espPosSet(work->sprList[17], temp_f31, temp_f30 - 32.0f);
            break;
        case 1:
            espPosSet(work->sprList[17], temp_f31, temp_f30 + 32.0f);
            break;
    }
    espDispOn(work->sprList[13]);
    switch (work->lSelection) {
        case 0:
            espDispOn(work->sprList[6]);
            espDispOn(work->sprList[9]);
            espDispOff(work->sprList[7]);
            espDispOff(work->sprList[8]);
            break;
        case 1:
            espDispOn(work->sprList[7]);
            espDispOn(work->sprList[8]);
            espDispOff(work->sprList[6]);
            espDispOff(work->sprList[9]);
            break;
    }
    if (work->optionSelected) {
        espDispOn(work->sprList[17]);
    }
    else {
        espDispOff(work->sprList[17]);
    }
}

static const s32 soundSettingsSprTbl[] = { 13, 6, 7, 8, 9 };

static void HideSoundSettings(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 5; i++) {
        espDispOff(work->sprList[soundSettingsSprTbl[i]]);
    }
}

static void DisplayMusicTitle(omObjData *object, s32 page)
{
    SoundWork *work = object->data;
    s32 i;

    espPosSet(work->sprList[10], 288.0f, 72.0f);
    espDispOn(work->sprList[10]);
    fn_1_A7F0(work->window[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A7F0(work->window[i + 3]);
        fn_1_A7B0(work->window[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    fn_1_A71C(work->window[2], musicPageNameTbl[page]);
    for (i = 0; i < 10; i++) {
        fn_1_A71C(work->window[i + 3], musicTbl[page][i].nameMess);
    }
}

static const s32 musicTitleSprIdxTbl[] = { 10 };

static void HideMusicTitle(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(work->sprList[musicTitleSprIdxTbl[i]]);
    }
    fn_1_A828(work->window[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A828(work->window[i + 3]);
    }
}

static void DisplayVoice(omObjData *object, s32 character)
{
    SoundWork *work = object->data;
    s32 i;

    espPosSet(work->sprList[11], 288.0f, 72.0f);
    espDispOn(work->sprList[11]);
    fn_1_A7F0(work->window[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A7F0(work->window[i + 3]);
        fn_1_A7B0(work->window[i + 3], 52.0f + 244.0f * (i / 5), 124.0f + 29.0f * (i % 5));
    }
    fn_1_A71C(work->window[2], voiceCharNameTbl[character]);
    for (i = 0; i < 10; i++) {
        fn_1_A71C(work->window[i + 3], voiceTbl[character][i].nameMess);
    }
}

static const s32 voiceTitleSprIdxTbl[] = { 11, 0 };

static void HideVoiceTitle(omObjData *object)
{
    SoundWork *work = object->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        espDispOff(work->sprList[voiceTitleSprIdxTbl[i]]);
    }
    fn_1_A828(work->window[2]);
    for (i = 0; i < 10; i++) {
        fn_1_A828(work->window[i + 3]);
    }
}

static s32 noteSprTbl[] = { DATA_MAKE_NUM(DATADIR_OPTION, 7), DATA_MAKE_NUM(DATADIR_OPTION, 8) };

static omObjData *CreateNote(s32 noteType)
{
    omObjData *note;
    NoteWork *noteWork;

    note = omAddObjEx(lbl_1_bss_8, 1003, 1, 0, 1, NULL);
    noteWork = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(NoteWork), MEMORY_DEFAULT_NUM);
    note->data = noteWork;
    noteWork->enabled = FALSE;
    noteWork->noteType = noteType;
    note->model[0] = Hu3DModelCreateFile(noteSprTbl[noteType]);
    Hu3DModelAttrSet(note->model[0], 0x40000001);
    Hu3DModelLayerSet(note->model[0], 2);
    Hu3DModelAttrReset(note->model[0], 2);
    return note;
}

static void KillNote(omObjData *note)
{
    NoteWork *noteWork = note->data;
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DModelKill(note->model[i]);
    }
    HuMemDirectFree(noteWork);
}

static void HandleNote(omObjData *note)
{
    NoteWork *noteWork = note->data;
    float temp_f31;
    float scale;
    float var_f29;
    float rot;
    float temp_f27;
    float x;
    float z;
    float y;
    float temp_f23;

    Hu3DModelAttrReset(note->model[0], 1);
    temp_f31 = sind(45.0f * noteWork->pos);
    temp_f31 = temp_f31 * temp_f31;
    switch (noteWork->speakerId) {
        case SPEAKER_LEFT:
            var_f29 = 174.5f + 7.0f * temp_f31;
            rot = -15.0 + 30.0 * sind(1440.0f * temp_f31);
            break;
        case SPEAKER_RIGHT:
            var_f29 = 185.5f - (7.0f * temp_f31);
            rot = 15.0 - 30.0 * sind(1440.0f * temp_f31);
            break;
    }
    temp_f23 = sind(180.0f * noteWork->pos);
    temp_f27 = 500.0f - 25.0f * temp_f31;
    x = temp_f27 * -sind(var_f29);
    z = temp_f27 * cosd(var_f29);
    y = 160.0f - 15.0f * noteWork->pos;
    scale = 0.5 + 2.0 * sind(90.0f * temp_f31);
    omSetTra(note, x, y, z);
    Hu3DModelTPLvlSet(note->model[0], temp_f23);
    omSetSca(note, scale, scale, scale);
    omSetRot(note, 0.0f, 0.0f, rot);
    if ((noteWork->pos += noteWork->speed) < 1.0f) {
        return;
    }
    noteWork->enabled = FALSE;
    Hu3DModelAttrSet(note->model[0], 1);
    note->func = NULL;
    note->unk10 = 0;
}

static void SpawnNote(omObjData *object, s32 noteType, s32 speakerId, s32 color)
{
    omObjData *note;
    NoteWork *var_r31;
    s32 i;

    for (i = 0; i < NUM_NOTES; i++) {
        note = ((SoundWork *)object->data)->objects[i + 10];
        var_r31 = note->data;
        if (!var_r31->enabled && var_r31->noteType == noteType) {
            break;
        }
    }
    if (i != NUM_NOTES) {
        Hu3DMotionTimeSet(note->model[0], 2.0f * color);
        Hu3DMotionStartEndSet(note->model[0], 2.0f * color, 2.0f * color + 1.0f);
        var_r31->enabled = TRUE;
        var_r31->speakerId = speakerId;
        var_r31->pos = 0.0f;
        var_r31->speed = 0.011111111f;
        note->func = HandleNote;
        note->unk10 = 0;
    }
}

static void CreateNoteProcess(omObjData *object)
{
    SoundWork *work = object->data;

    work->speakerNoteProcess = HuPrcChildCreate(HandleNoteProcess, 0x64, 0x2000, 0, HuPrcCurrentGet());
    work->speakerNoteProcess->user_data = object;
}

static void KillNoteProcess(omObjData *object)
{
    SoundWork *work = object->data;

    HuPrcKill(work->speakerNoteProcess);
}

static void HandleNoteProcess(void)
{
    omObjData *object;
    SoundWork *work;
    s32 noteType;
    s32 color;

    object = HuPrcCurrentGet()->user_data;
    work = object->data;
    while (TRUE) {
        switch (work->lSelection) {
            case 0:
                noteType = NOTE_TYPE_QUARTER;
                color = frandmod(7);
                SpawnNote(object, noteType, SPEAKER_LEFT, color);
                noteType = NOTE_TYPE_QUAVER;
                color = frandmod(7);
                SpawnNote(object, noteType, SPEAKER_RIGHT, color);
                break;
            case 1:
                noteType = NOTE_TYPE_QUAVER;
                color = frandmod(7);
                SpawnNote(object, noteType, SPEAKER_LEFT, color);
                SpawnNote(object, noteType, SPEAKER_RIGHT, color);
                break;
        }
        HuPrcSleep(24);
    }
}

static void PlaySound(omObjData *object)
{
    SoundWork *work = object->data;
    SndSelData *sndSelData;

    if (work->selectedOption == 1) {
        sndSelData = (SndSelData *)&musicTbl[work->page][work->lSelection];
    }
    else {
        sndSelData = (SndSelData *)&voiceTbl[work->page][work->lSelection];
    }
    if (sndSelData->enabled) {
        FadeOutCurrSound(object);
        switch (sndSelData->audType) {
            case 1:
                work->audSStreamStat = HuAudSStreamPlay(sndSelData->fxId);
                break;
            case 28:
                if (sndSelData->sndGrpSet != work->sndGrpSet) {
                    HuAudSndGrpSetSet(sndSelData->sndGrpSet);
                }
                work->audFxStat = HuAudFXPlay(sndSelData->fxId);
                break;
            default:
                if (sndSelData->sndGrpSet != work->sndGrpSet && sndSelData->sndGrpSet != 2) {
                    HuAudSndGrpSetSet(sndSelData->sndGrpSet);
                }
                work->audSeqStat = HuAudSeqPlay(sndSelData->fxId);
                break;
        }
        work->sndGrpSet = sndSelData->sndGrpSet;
        HuPrcSleep(40);
    }
}

static void FadeOutCurrSound(omObjData *object)
{
    SoundWork *work = object->data;

    if (work->audSeqStat != -1) {
        HuAudSeqFadeOut(work->audSeqStat, 0x64);
        work->audSeqStat = -1;
    }
    if (work->audSStreamStat != -1) {
        HuAudSStreamFadeOut(work->audSStreamStat, 0x64);
        work->audSStreamStat = -1;
    }
    if (work->audFxStat != -1) {
        HuAudFXFadeOut(work->audFxStat, 0x64);
        work->audFxStat = -1;
    }
    HuPrcSleep(20);
}
