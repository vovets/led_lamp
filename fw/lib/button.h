#pragma once

#include <lib/timers.h>

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BtnShortPress,
    BtnLongPress
} BtnEvent;

typedef void (*BtnFunc)(BtnEvent e);

void btnInit(uint8_t pin, BtnFunc func);

// returns ture if button is pressed down
bool btnRead();

void btnToggle(bool stateNow);
