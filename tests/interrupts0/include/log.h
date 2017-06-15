#ifndef LOG_H
#define LOG_H

#include "bcm2835_uart.h"

#define log(s)  uart_print(s)

#endif
