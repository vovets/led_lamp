#pragma once

typedef enum DebugEventId {
    debugEvPut           = 0,
    debugEvGet           = 1,
    debugBtnToggle       = 6,
    debugBtnEvent        = 7,
    debugDbnCounter      = 8,
    debugTimerExpired    = 9,
    debugTimerSet        = 10,
    debugTimerCancel     = 11,
    debugAlarmEnabled    = 12,
    debugAlarmDisabled   = 13,
    debugEnterSleep      = 14,
    debugExitSleep       = 15,
    debugVccm            = 16,
    debugState           = 17,
    debugAdcStartConversion = 18,
    debugPwm             = 19
} DebugEventId;
