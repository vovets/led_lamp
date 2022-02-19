#pragma once

#include <lib/panic.h>

extern char __heap_end[4];

#define stackCheck() \
    do { if (__heap_end[0] != 0x55U) panic(); } while (0)
