#include <inttypes.h>

#include "bcm2835_armtimer.h"

static BCM2835ARMTimerState *bcm2835_armtimer_state =
        (BCM2835ARMTimerState *)BCM2835_ARMTIMER_BASE;

BCM2835ARMTimerState *bcm2835_armtimer_get_state(void)
{
    return bcm2835_armtimer_state;
}

void bcm2835_armtimer_init(void)
{
    bcm2835_armtimer_state->ctrl |= ARMTIMER_CTRL_TIMER_ENABLE
                                       | ARMTIMER_CTRL_INT_ENABLE;
    //bcm2835_armtimer_state->load = 0;
}

void bcm2835_armtimer_ack(void)
{
    /* Write anything to ack interrupt. */
    bcm2835_armtimer_state->int_clr = 1;
}
