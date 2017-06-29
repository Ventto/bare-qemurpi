#ifndef BCM2835_SYSTIMERS_H
#define BCM2835_SYSTIMERS_H

#include "bcm2835_peripherals.h"

/* BCM2835 ARM Peripherals Documentation. Section 12. */

#define BCM2835_SYSTIMER_BASE   (BCM2835_PERIPHERAL_BASE + 0x3000)

/* OSs use the timer 3. GPU uses timers 0 & 2 and timer 1 is available. */
#define ST_REG_CONTROL      (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x00)

#define ST_DEFAULT_OS_TIMER     3

void bcm2835_st_enable_timers(int val);
void bcm2835_st_disable_timers(int val);

#endif
