#pragma once

#include "timers.h"

#include <stdint.h>
#include <stdbool.h>

#define BTN_LONG_PRESS_TICKS ST_MS2TICKS(1000)
#define BTN_DOWN_IS_PIN_LOW 1

typedef enum {
    BtnShortPress,
    BtnLongPress
} BtnEvent;

typedef void (*BtnFunc)(BtnEvent e);

void btnInit(uint8_t pin, BtnFunc func);

// returns ture if button is pressed down
bool btnRead();

void btnToggle(bool stateNow);
