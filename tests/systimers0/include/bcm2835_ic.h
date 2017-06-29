#ifndef BCM2835_IC_H
#define BCM2835_IC_H

#include "bcm2835_peripherals.h"

/* BCM2835 ARM Peripherals Documentation. Section 7. */

#define BCM2835_IC_BASE     (BCM2835_PERIPHERAL_BASE + 0xB200)

#define IRQ_ENABLE_1        0x10
#define IRQ_DISABLE_1       0x1C

#define IC_REG_ENABLE_IRQS_1    (volatile uint32_t *)(BCM2835_IC_BASE \
                                                        + IRQ_ENABLE_1)
#define IC_REG_DISABLE_IRQS_1   (volatile uint32_t *)(BCM2835_IC_BASE \
                                                        + IRQ_DISABLE_1)

#endif
