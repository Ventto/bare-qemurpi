#ifndef BCM2835_UART_H
#define BCM2835_UART_H

#include <stdint.h>
#include "bcm2835_peripherals.h"

#define UART_BASE           (PERIPHERAL_BASE + 0x201000)

void uart_print(const char *s);

#endif
