#include <stdio.h>

void __attribute__((interrupt("ABORT"))) reset_vector(void)
{
    printf("interrupt: ABORT\n");
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    printf("interrupt: UNDEF\n");
    while(1)
    {

    }
}

void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    printf("interrupt: SWI\n");
    while(1)
    {

    }
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
    printf("interrupt: ABORT\n");
}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
    printf("interrupt: ABORT\n");
}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
    printf("interrupt: IRQ\n");
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
    printf("interrupt: FIQ\n");
}
