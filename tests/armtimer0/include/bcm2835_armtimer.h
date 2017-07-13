#ifndef BCM2835_ARMTIMER_H
#define BCM2835_ARMTIMER_H

#include <inttypes.h>

#include "bcm2835_peripherals.h"

/* BCM2835 ARM Peripherals Documentation. Section 14. */

#define BCM2835_ARMTIMER_BASE   (BCM2835_PERIPHERAL_BASE + 0xB400)

/* BCM2835 ARM Peripherals Documentation. Section 14.2. */

/* Control register masks */
#define ARMTIMER_CTRL_CNT_ENABLE         (1 << 9)
#define ARMTIMER_CTRL_TIMER_ENABLE       (1 << 7)
#define ARMTIMER_CTRL_INT_ENABLE         (1 << 5)
#define ARMTIMER_CTRL_TIMER_PRESCALE     (3 << 2)
#define ARMTIMER_CTRL_TIMER_SIZE_32BIT   (1 << 1)

typedef struct {
    volatile uint32_t load;
    volatile uint32_t value;
    volatile uint32_t ctrl;
    volatile uint32_t int_clr;
    volatile uint32_t raw_irq;
    volatile uint32_t msk_irq;
    volatile uint32_t reload;
    volatile uint32_t prediv;
    volatile uint32_t counter;
} BCM2835ARMTimerState;

BCM2835ARMTimerState *bcm2835_armtimer_get_state(void);
void bcm2835_armtimer_init(void);
void bcm2835_armtimer_ack(void);

#endif
