#pragma once

#include "event.h"


//these are called from loop and must be defined elsewhere
void handleAlarm(const Event* e);
void handlePinChange(const Event* e);
void handleAdc(const Event* e);
uint8_t sleepMode(void);

void loop(void) __attribute__ ((noreturn));
