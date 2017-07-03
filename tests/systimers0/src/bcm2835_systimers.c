#include <inttypes.h>

#include "bcm2835_ic.h"
#include "bcm2835_systimers.h"

#define ST_REG_CONTROL      (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x00)

void bcm2835_st_enable_timer(int timer)
{
    *IC_REG_ENABLE_IRQS_1 |= (1 << timer);
}

void bcm2835_st_ack_timer(int timer)
{
    *ST_REG_CONTROL |= (1 << timer);
}
