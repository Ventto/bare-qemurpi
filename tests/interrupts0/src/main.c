#include "log.h"
#include "bcm2835_ic.h"
#include "bcm2835_systimer.h"

#define TIMER_NEXT_TICK     100000 /* us */

extern void _enable_interrupts(void);
extern void _enable_pl1_ptimer(void);
extern void _set_pl1_ptimer(void);

void kernel_main(void)
{
    /* Enable interrupt from System Timer's match 3 */
    BCM2835ICRegs *regs = bcm2835_ic_get_registers;
    regs->enable_irqs_1 = ST_TIMER_M3;

    /* Enable IRQs */
    _enable_interrupts();

    /* Arm the timer */
    *ST_REG_COMPARE(ST_DEFAULT_TIMER) = *ST_REG_COUNTER_LO + TIMER_NEXT_TICK;
    log("Timer armed.\n");

    _enable_pl1_ptimer();
    _set_pl1_ptimer();

    while (1) {
        /* Loop forever */
    }
}
