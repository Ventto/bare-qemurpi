#include <inttypes.h>

#include "bcm2836_control.h"

void bcm_enable_timer_irqs(int core, uint32_t val)
{
    volatile uint32_t *reg = (uint32_t *)(BCM2836_CONTROL_CORE_TIMERS
                                          + (0x4 * core));

    *reg |= val;
}
