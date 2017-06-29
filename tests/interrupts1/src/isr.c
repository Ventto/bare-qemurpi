#include <inttypes.h>
#include <stdio.h>

#include "generic_timers.h"
#include "irq.h"

void __attribute__((isr("ABORT"))) reset_vector(void)
{
    printf("\ninterrupt: ABORT\n");
}

void __attribute__((isr("UNDEF"))) undefined_instruction_vector(void)
{
    printf("interrupt: UNDEF\n");
    while(1)
    {

    }
}

void __attribute__((isr("SWI"))) software_interrupt_vector(void)
{
    printf("interrupt: SWI\n");
    while(1)
    {

    }
}

void __attribute__((isr("ABORT"))) prefetch_abort_vector(void)
{
    printf("\ninterrupt: ABORT\n");
}

void __attribute__((isr("ABORT"))) data_abort_vector(void)
{
    printf("\ninterrupt: ABORT\n");
}

void __attribute__((isr("IRQ"))) interrupt_vector(void)
{
    uint32_t cpsr = disable_irqs();

    gt_disable();

    printf("\ninterrupt: IRQ\n");

    restore_irqs(cpsr);
}

void __attribute__((isr("FIQ"))) fast_interrupt_vector(void)
{
    printf("\ninterrupt: FIQ\n");
}
