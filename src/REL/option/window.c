#include "game/window.h"
#include "REL/option.h"
#include "game/esprite.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"

static void HandleWindow(void);

WindowWork *fn_1_A44C(s32 id)
{
    WindowWork *work;

    work = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(WindowWork), MEMORY_DEFAULT_NUM);
    work->messToBeSet = 0;
    work->messWaitSignal = 0;
    work->choiceSignal = 0;
    work->state = 0;
    work->process = HuPrcChildCreate(HandleWindow, 0x2000, 0x2000, 0, lbl_1_bss_8);
    work->process->user_data = work;
    work->id = id;
    switch (work->id) {
        case 0:
            work->window = HuWinExCreateStyled(-10000.0f, 360.0f, 480, 80, -1, 1);
            HuWinBGTPLvlSet(work->window, 0.8f);
            HuWinMesSpeedSet(work->window, 0);
            HuWinMesPalSet(work->window, 7, 0, 0, 0);
            break;
        case 1:
            work->window = HuWinExCreateStyled(-10000.0f, 326.0f, 480, 40, -1, 0);
            HuWinAttrSet(work->window, 0x800);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
        case 2:
            work->window = HuWinExCreateStyled(-10000.0f, 88.0f, 224, 34, -1, 0);
            HuWinAttrSet(work->window, 0x800);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
        case 3:
            work->window = HuWinExCreateStyled(175.0f, 100.0f, 300, 34, -1, 0);
            HuWinBGTPLvlSet(work->window, 0.0f);
            HuWinMesSpeedSet(work->window, 0);
            break;
    }
    HuWinDrawNoSet(work->window, 0x3F);
    fn_1_A828(work);
    HuSprExecLayerSet(0x3F, 2);
    return work;
}

void fn_1_A6AC(WindowWork *work)
{
    HuWinExCleanup(work->window);
    HuPrcKill(work->process);
    HuMemDirectFree(work);
}

void fn_1_A6EC(WindowWork *work)
{
    if (!work->visible) {
        work->state = 1;
    }
}

void fn_1_A704(WindowWork *work)
{
    if (work->visible) {
        work->state = 2;
    }
}

void fn_1_A71C(WindowWork *work, s32 mess)
{
    if (work->state == 0) {
        HuWinMesSet(work->window, mess);
    }
    else {
        work->messToBeSet = mess;
    }
}

static void fn_1_A770(WindowWork *work, s32 mess, s16 index)
{
    HuWinInsertMesSet(work->window, mess, index);
}

// SetWindowPosition
void fn_1_A7B0(WindowWork *work, float x, float y)
{
    HuWinPosSet(work->window, x, y);
}

// DisplayWindow
void fn_1_A7F0(WindowWork *work)
{
    HuWinDispOn(work->window);
    work->visible = TRUE;
}

// HideWindow
void fn_1_A828(WindowWork *work)
{
    HuWinDispOff(work->window);
    work->visible = FALSE;
}

static void fn_1_A860(WindowWork *work)
{
    if (work->state == 0) {
        work->state = 3;
    }
    work->messWaitSignal = TRUE;
}

void fn_1_A880(WindowWork *work, s32 choice)
{
    if (work->state == 0) {
        work->state = 4;
    }
    work->choiceSignal = TRUE;
    work->choice = choice;
}

static void HandleWindow(void)
{
    WindowWork *work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        switch (work->state) {
            case 1:
                fn_1_A7F0(work);
                HuWinExAnimIn(work->window);
                break;
            case 2:
                HuWinExAnimOut(work->window);
                fn_1_A828(work);
                break;
            case 3:
                HuWinMesWait(work->window);
                work->messWaitSignal = FALSE;
                break;
            case 4:
                work->choice = HuWinChoiceGet(work->window, work->choice);
                work->choiceSignal = FALSE;
                break;
        }
        if (work->messToBeSet != 0) {
            HuWinMesSet(work->window, work->messToBeSet);
            work->messToBeSet = 0;
        }
        work->state = 0;
        if (work->messWaitSignal) {
            work->state = 3;
        }
        if (work->choiceSignal) {
            work->state = 4;
        }
        HuPrcVSleep();
    }
}
