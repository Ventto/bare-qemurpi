#ifndef BCM2835_UART_H
#define BCM2835_UART_H

#include <stdint.h>
#include "bcm2835_peripherals.h"

#define UART_BASE       (BCM2835_PERIPHERAL_BASE + 0x201000)
#define UART_REG_DR     UART_BASE
#define UART_REG_FR     (UART_BASE + 0x18)
#define UART_FR_RXFE    0x10
#define UART_FR_TXFF    0x20
#endif
