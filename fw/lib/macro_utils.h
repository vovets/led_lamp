#pragma once

#define LL_CAT_(A1, A2) A1##A2
#define LL_CAT(A1, A2) LL_CAT_(A1, A2)
#define MAX(A1, A2) ((A1) > (A2) ? (A1) : (A2))

#define BREAK() asm volatile ("break"::)

#define ARR_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(ARRAY[0]))

/* 210 us
#define advance(counter, mod) \
do { counter = (counter + 1) % mod; } while (false)
*/

/* 10 us
*/
#define advance(counter, mod) \
do { ++counter; if (counter == mod) { counter = 0; } } while (false)

#define ATOMIC() ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
