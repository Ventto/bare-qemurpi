#ifndef BCM2835_IC_H
#define BCM2835_IC_H

#include <inttypes.h>

#include "bcm2835_peripherals.h"

/* BCM2835 ARM Peripherals Documentation. Section 7. */

#define BCM2835_IC_BASE     (BCM2835_PERIPHERAL_BASE + 0xB200)

/* BCM2835 ARM Peripherals Documentation. Section 7.5. */

#define BASIC_ARM_TIMER_IRQ         (1 << 0)
#define BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)

typedef struct {
    volatile uint32_t irq_basic_pending;
    volatile uint32_t irq_pending_1;
    volatile uint32_t irq_pending_2;
    volatile uint32_t fiq_control;
    volatile uint32_t enable_irqs_1;
    volatile uint32_t enable_irqs_2;
    volatile uint32_t enable_basic_irqs;
    volatile uint32_t disable_irqs_1;
    volatile uint32_t disable_irqs_2;
    volatile uint32_t disable_basic_irqs;
} BCM2835ICState;

static BCM2835ICState *bcm2835_ic_state = (BCM2835ICState *)BCM2835_IC_BASE;

BCM2835ICState *bcm2835_ic_get_state(void)
{
    return bcm2835_ic_state;
}

#endif
