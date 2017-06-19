#include <stdint.h>
#include "bcm2835_uart.h"

volatile unsigned int * const uart_dr = (unsigned int *)(UART_BASE);

void uart_print(const char *s)
{
    while(*s != '\0') {
		*uart_dr = (unsigned int)(*s++);
	}
    /* Force newline for serial display */
	*uart_dr = (unsigned int)('\r');
}
