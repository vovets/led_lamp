#pragma once

#include <stdint.h>



typedef void (*VccmFunc)(uint16_t mv); 

void vccmInit(void);

void vccmEnable(void);

void vccmStart(VccmFunc func);

void vccmContinue(VccmFunc func);

void vccmDisable(void);
