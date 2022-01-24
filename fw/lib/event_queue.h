#pragma once

#include "event.h"

#include <stdbool.h>


void eqPutI(const Event* event);
void eqGet(Event* event);
bool eqEmpty(void);
bool eqFull(void);
