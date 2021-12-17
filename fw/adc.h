#pragma once

#include <stdint.h>
#include <stdbool.h>


typedef void (*AdcConversionFinished)(void* arg, uint16_t result);

void adcEnable(uint8_t admuxValue);

void adcDisable(void);

void adcStartConversion(AdcConversionFinished func, void* arg);
