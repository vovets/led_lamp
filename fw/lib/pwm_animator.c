#include <lib/parameters.h>
#include <lib/pwm_animator.h>
#include <lib/timers.h>
#include <lib/pwm.h>

#include <stdlib.h>


#define PWMA_TOTAL_DSTEPS 2560U
#define PWMA_TOTAL_TICKS (PWMA_FULL_TRANSITION_TIME_MS / PWMA_TICK_TIME_MS)
#define PWMA_DSTEPS_PER_TICK (PWMA_TOTAL_DSTEPS / PWMA_TOTAL_TICKS)


typedef struct Animator {
    uint16_t target;
    uint16_t current;
    Timer timer;
    PwmaFunc completion;
} Animator;

static Animator animator;

static void timerExpired(void* arg);

static void setTimer(void) {
    tmSetTimer(&animator.timer, ST_MS2TICKS(PWMA_TICK_TIME_MS), timerExpired, 0);
}    

static void timerExpired(void* arg) {
    int diff = animator.target - animator.current;
    if (!diff) {
        if (animator.completion) { animator.completion(); }
        return;
    }
    
    int sign = diff > 0 ? 1 : -1;
    int delta = abs(diff);
    if (delta > PWMA_DSTEPS_PER_TICK) { delta = PWMA_DSTEPS_PER_TICK; }
    animator.current += delta * sign;
    pwmSet(animator.current / 10);
    setTimer();
}

void pwmaStart(uint8_t target, PwmaFunc completion) {
    pwmaStop();
    animator.target = target * 10;
    animator.current = pwmGet() * 10;
    animator.completion = completion;
    setTimer();
}

void pwmaStop(void) {
    if (tmIsTimerSet(&animator.timer)) {
        tmCancelTimer(&animator.timer);
    }
}
