#include <inttypes.h>
#include <stdio.h>

#include "bcm2835_ic.h"
#include "bcm2835_armtimer.h"
#include "irq.h"

int wait_for_timer = 1;

void not_main(void)
{
    /* Initialize ARM Timer Control Register */
    bcm2835_armtimer_init();

    /* Enable ARM Timer IRQ. */
    bcm2835_ic_get_state()->enable_basic_irqs = BASIC_ARM_TIMER_IRQ;

    printf("[ BCM2835 Interrupt Controller ]\n\nMemory Registers:\n"
            "Enable_Basic_IRQs: 0x%08x\nDisable_Basic_IRQs: 0x%08x\n",
            (unsigned int)(bcm2835_ic_get_state()->enable_basic_irqs),
            (unsigned int)(bcm2835_ic_get_state()->disable_basic_irqs));

    /* Enable cores to receive any IRQs */
    enable_irqs();

    while (wait_for_timer) {
        /* FIXME: Prints downcount timer value. */
        printf("ARM Timer Value: %" PRIu32 "\n",
                bcm2835_armtimer_get_state()->value);
    }
}
