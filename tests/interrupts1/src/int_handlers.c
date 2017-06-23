#include <stdio.h>

void __attribute__((isr("ABORT"))) reset_vector(void)
{
    printf("interrupt: ABORT\n");
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
    printf("interrupt: ABORT\n");
}

void __attribute__((isr("ABORT"))) data_abort_vector(void)
{
    printf("interrupt: ABORT\n");
}

void __attribute__((isr("IRQ"))) interrupt_vector(void)
{
    printf("interrupt: IRQ\n");
}

void __attribute__((isr("FIQ"))) fast_interrupt_vector(void)
{
    printf("interrupt: FIQ\n");
}
