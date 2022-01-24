#pragma once

extern char __heap_end;

#define stackCheck() \
    do { if (__heap_end != 0x55U) abort(); } while (0)
