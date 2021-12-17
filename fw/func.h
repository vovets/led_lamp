#pragma once

typedef void (*Func)(void* arg);

typedef struct Closure {
    Func func;
    void* arg;
} Closure;
