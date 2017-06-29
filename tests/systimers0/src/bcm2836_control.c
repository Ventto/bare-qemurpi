#include <inttypes.h>

#include "bcm2836_control.h"

inline void bcm_enable_core_timer_irqs(int core, uint32_t ctl)
{
    *(uint32_t *)(BCM2836_CONTROL_CORE_TIMERS + (0x4 * core)) |= ctl;
}
