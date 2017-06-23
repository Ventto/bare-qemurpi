#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <time.h>

#include "bcm2835_uart.h"

volatile uint32_t * const uart_dr = (uint32_t *)(UART_REG_DR);
volatile uint32_t * const uart_fr = (uint32_t *)(UART_REG_FR);

int _close(int file) { return -1; }

void _exit(int status) { while (1); }

int _fstat(int file, struct stat *st) { return 0; }

int _isatty(int file) { return 1; }

int _lseek(int file, int ptr, int dir) { return 0; }

int _open(const char *name, int flags, int mode) { return -1; }

int _read(int file, char *ptr, int len)
{
    if(len == 0)
        return 0;

    while(*uart_fr & UART_FR_RXFE);

    *ptr++ = *uart_dr;

    int todo;
    for(todo = 1; todo < len; todo++) {
        if(*uart_fr & UART_FR_RXFE) {
            break;
        }
        *ptr++ = *uart_dr;
    }
    return todo;
}

char *heap_end = 0;
caddr_t _sbrk(int incr) {
	extern char heap_low; /* Defined by the linker */
	extern char heap_top; /* Defined by the linker */
	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &heap_low;
	}
	prev_heap_end = heap_end;

	if (heap_end + incr > &heap_top) {
		/* Heap and stack collision */
		return (caddr_t)0;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

int _write(int file, char *ptr, int len)
{
    int todo;

    for (todo = 0; todo < len; todo++) {
        *uart_dr = *ptr;
        if (*ptr == '\n')
            *uart_dr = '\r';
        ptr++;
    }

    return len;
}
