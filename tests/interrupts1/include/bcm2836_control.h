#ifndef BCM2836_CONTROL_H
#define BCM2836_CONTROL_H

#include <inttypes.h>

/* "QA7" (Pi2) interrupt controller, ARM timer, mailboxes */
#define BCM2836_CONTROL_BASE            0x40000000

#define BCM2836_CONTROL_CORE_TIMERS     (BCM2836_CONTROL_BASE + 0x40)

#define CTL_CNTPNSIRQ_ENABLED   0x2
#define CTL_CNTPSIRQ_ENABLED    0x1

void bcm_enable_timer_irqs(int core, uint32_t ctl);

#endif
