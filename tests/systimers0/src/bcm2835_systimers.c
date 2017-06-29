#include <inttypes.h>

#include "bcm2835_ic.h"
#include "bcm2835_systimers.h"

void bcm2835_st_enable_timers(int val)
{
    *ST_REG_CONTROL &= ~ (1 << val);
    *IC_REG_ENABLE_IRQS_1 |= 0xAUL;
}

void bcm2835_st_disable_timers(int val)
{
    *IC_REG_DISABLE_IRQS_1 |= 0xAUL;
}
