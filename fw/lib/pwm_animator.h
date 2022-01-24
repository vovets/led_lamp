#pragma once

#include <stdint.h>

typedef void (*PwmaFunc)(void);

void pwmaStart(uint8_t target, PwmaFunc completion);

void pwmaStop(void);
