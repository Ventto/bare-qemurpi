#ifndef BCM2836_CONTROL_H
#define BCM2836_CONTROL_H

#include <inttypes.h>

/* Quad A7 Control Documentation, Section 4.6: Core timers interrupts */

#define BCM2836_CONTROL_BASE            0x40000000

#define BCM2836_CONTROL_CORE_TIMERS     (BCM2836_CONTROL_BASE + 0x40)

void bcm_enable_core_timer_irqs(int core, uint32_t ctl);

#endif
