#pragma once

#include "timers.h"
#include "func.h"

#include <stdint.h>

struct Blinker;

typedef void (*BlinkerFunc)(struct Blinker* blinker, void* arg);
typedef void (*BlinkerLedFunc)(bool on);

typedef enum { BlinkerModeOnThenOff, BlinkerModeOffThenOn } BlinkerMode;

typedef struct Blinker {
    Timer timer;
    BlinkerMode mode;
    uint8_t iterations;
    SysTimeDelta state_0_time;
    SysTimeDelta state_1_time;
    BlinkerLedFunc ledFunc;
    void (*state)(struct Blinker*);
    uint8_t iterationsLeft;
    BlinkerFunc finishedFunc;
    void* finishedArg;
} Blinker;

// iterations == 0 means blinker will be restarted after it has finished
void blinkerSetup(Blinker* blinker, BlinkerMode mode, uint8_t iterations, SysTimeDelta state_0_time, SysTimeDelta state_1_time, BlinkerLedFunc ledFunc);

void blinkerStart(Blinker* blinker, BlinkerFunc func, void* arg);

void blinkerStop(Blinker* blinker);

bool blinkerIsActive(Blinker* blinker);