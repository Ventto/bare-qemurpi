#ifndef BCM2835_SYSTIMERS_H
#define BCM2835_SYSTIMERS_H

#include "bcm2835_peripherals.h"

/* BCM2835 ARM Peripherals Documentation. Section 12. */

#define BCM2835_SYSTIMER_BASE   (BCM2835_PERIPHERAL_BASE + 0x3000)

void bcm2835_st_enable_timer(int timer);
void bcm2835_st_ack_timer(int timer);

#endif
