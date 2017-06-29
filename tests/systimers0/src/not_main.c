#include <inttypes.h>
#include <stdio.h>

#include "bcm2835_ic.h"
#include "bcm2835_systimers.h"
#include "bcm2836_control.h"
#include "irq.h"

/* ARM Controller Register bits to enable core timer IRQs */
#define CTL_CNTPNSIRQ   0x2
#define CTL_CNTPSIRQ    0x1

/* BCM2835 System Timer registers */
#define ST_REG_COUNTER_LO  (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x04)
#define ST_REG_COUNTER_HI  (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x08)
#define ST_REG_COMPARE(n)  (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x0C + (n) * 4)

#define NEXT_TICK       150000

#define MASK_32BIT      0xFFFFFFFFLL

void not_main(void)
{
    volatile uint32_t *timer = ST_REG_COMPARE(ST_DEFAULT_OS_TIMER);

    /* Enable cores to receive IRQ */
    enable_irqs();

    printf("\n[ BCM2835 Interrupt Controller ]\n\n");
    printf("Register values:\n");
    printf("ENABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_ENABLE_IRQS_1));
    printf("DISABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_DISABLE_IRQS_1));

    bcm2835_st_enable_timers(ST_DEFAULT_OS_TIMER);

    printf("\n=> Enable timer IRQ\n\n");
    printf("Register values:\n");
    printf("ENABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_ENABLE_IRQS_1));
    printf("DISABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_DISABLE_IRQS_1));

    /* Set the compare value */
    *timer = *ST_REG_COUNTER_LO + NEXT_TICK;

    volatile int match = 0;

    while (!match) {
        match = *ST_REG_CONTROL & (1 << ST_DEFAULT_OS_TIMER);

        printf("COUNTER_LO: %" PRIu32 ";\tTIMER_3: %" PRIu32 ";\tMATCH: %s\n",
                *ST_REG_COUNTER_LO, *timer, (match ? "YES" : "NO"));
    }
}
