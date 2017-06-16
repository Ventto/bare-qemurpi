#include <stdint.h>
#include "bcm2835_uart.h"

volatile unsigned int * const UART_IN = (unsigned int *)(UART_BASE);

void uart_print(const char *s)
{
    while(*s != '\0') {
		*UART_IN = (unsigned int)(*s++);
	}
	*UART_IN = (unsigned int)('\r');
}
