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
#define ST_REG_CONTROL      (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x00)
#define ST_REG_COUNTER_LO   (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x04)
#define ST_REG_COUNTER_HI   (volatile uint32_t *)(BCM2835_SYSTIMER_BASE + 0x08)
#define ST_REG_COMPARE(n)   (volatile uint32_t *)(BCM2835_SYSTIMER_BASE \
                                                  + 0x0C + (n) * 4)
#define TIMER_MATCH(n)  (1 << n)

#define DEFAULT_TIMER   3

#define NEXT_TICK       100000
#define MASK_32BIT      0xFFFFFFFFLL

int wait_for_timer = 1;

void not_main(void)
{
    /* Enable cores to receive IRQ */
    enable_irqs();

    printf("\n[ BCM2835 Interrupt Controller ]\n\n");
    printf("Register values:\n");
    printf("ENABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_ENABLE_IRQS_1));
    printf("DISABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_DISABLE_IRQS_1));

    /* Enable system timer n°3 */
    bcm2835_st_enable_timer(DEFAULT_TIMER);

    printf("\n=> Enable system timer IRQ\n\n");
    printf("Register values:\n");
    printf("ENABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_ENABLE_IRQS_1));
    printf("DISABLE_IRQS_1:\t%08x\n", (unsigned int)(*IC_REG_DISABLE_IRQS_1));

    volatile uint32_t *cmp_r = ST_REG_COMPARE(DEFAULT_TIMER);

    /* Set corresponding compare value */
    *cmp_r = *ST_REG_COUNTER_LO + NEXT_TICK;

    while (wait_for_timer) {
        printf("COUNTER_LO: %" PRIu32 ";\tTIMER_%u: %" PRIu32 "\n",
                *ST_REG_COUNTER_LO, DEFAULT_TIMER, *cmp_r);
    }
}
