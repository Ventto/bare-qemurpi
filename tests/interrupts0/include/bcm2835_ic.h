#ifndef BCM2835_IC_H
#define BCM2835_IC_H

#include <stdint.h>
#include "bcm2835_peripherals.h"

#define INTERRUPT_CONTROLLER_BASE   (PERIPHERAL_BASE + 0xB200)

/*
 * From BCM2835 ARM Peripherals Manual:Section 7.5
 * Bits of Enable_Basic_IRQs register
 */
#define IRQ_ARM_TIMER         (1 << 0)
#define IRQ_ARM_MAILBOX       (1 << 1)
#define IRQ_ARM_DOORBELL_0    (1 << 2)
#define IRQ_ARM_DOORBELL_1    (1 << 3)
#define IRQ_GPU_0_HALTED      (1 << 4)
#define IRQ_GPU_1_HALTED      (1 << 5)
#define IRQ_ACCESS_ERROR_1    (1 << 6)
#define IRQ_ACCESS_ERROR_0    (1 << 7)

#define bcm2835_ic_get_registers (BCM2835ICRegs *)(INTERRUPT_CONTROLLER_BASE)

/* The interrupt controller memory mapped register set */
typedef struct BCM2835ICRegs {
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
} BCM2835ICRegs;

#endif
