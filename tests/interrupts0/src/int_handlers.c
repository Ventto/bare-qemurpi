#include "bcm2835_uart.h"

#define log(s)  uart_print(s)

void __attribute__((interrupt("ABORT"))) reset_vector(void)
{
    log("interrupt: ABORT\n");
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    log("interrupt: UNDEF\n");
    while(1)
    {

    }
}

void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    log("interrupt: SWI\n");
    while(1)
    {

    }
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
    log("interrupt: ABORT\n");
}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
    log("interrupt: ABORT\n");
}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
    log("interrupt: IRQ\n");
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
    log("interrupt: FIQ\n");
}
