#pragma once

#include <stdint.h>
#include <stdbool.h>

void pwmInit(void);

void pwmEnable(void);

void pwmDisable(void);

void pwmSet(uint8_t v);

bool pwmIsEnabled(void);

uint8_t pwmGet(void);
