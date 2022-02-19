#pragma once

#include <stdint.h>
#include <stdbool.h>

#define SLEEP_MODE_NONE 0xFFU

//this is called from loop and must be defined in app
uint8_t sleepMode(void);

void loop(void) __attribute__ ((noreturn));
bool processOneEvent(void);
void tryToSleep(void);
