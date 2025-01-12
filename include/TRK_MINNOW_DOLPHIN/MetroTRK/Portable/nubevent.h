#ifndef METROTRK_PORTABLE_NUBEVENT_H
#define METROTRK_PORTABLE_NUBEVENT_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u32 NubEventID;

typedef struct TRKEvent {
	NubEventType eventType;
	NubEventID eventID;
	MessageBufferID msgBufID;
} TRKEvent;

typedef struct TRKEventQueue {
	int _00;
	int count;
	int next;
	TRKEvent events[2];
	NubEventID eventID;
} TRKEventQueue;
extern TRKEventQueue gTRKEventQueue;

BOOL TRKGetNextEvent(TRKEvent* event);
void TRKDestructEvent(TRKEvent*);
void TRKConstructEvent(TRKEvent*, NubEventType);
DSError TRKPostEvent(TRKEvent*);
DSError TRKInitializeEventQueue();

#ifdef __cplusplus
}
#endif

#endif /* METROTRK_PORTABLE_NUBEVENT_H */
