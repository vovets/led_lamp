#pragma once

typedef enum DebugEventId {
    debugEvPut = 0,
    debugEvGet = 1,
    debugAlarmEnabled    = 12,
    debugAlarmDisabled   = 13,
    debugEnterSleep      = 14,
    debugExitSleep       = 15,
    debugTime            = 31
} DebugEventId;
