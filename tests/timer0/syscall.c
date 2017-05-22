#include <stdlib.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>


#define PHYS_BASE   0x3F000000
#define UART_ADDR   (PHYS_BASE + 0x201000)

enum {
    UART_FR_RXFE = 0x10,
    UART_FR_TXFF = 0x20,
    UART0_ADDR = UART_ADDR,
};

#define UART_DR(baseaddr) (*(unsigned int *)(baseaddr))
#define UART_FR(baseaddr) (*(((unsigned int *)(baseaddr)) + 0x18))

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

    while(UART_FR(UART0_ADDR) & UART_FR_RXFE);

    *ptr++ = UART_DR(UART0_ADDR);

    int todo;
    for(todo = 1; todo < len; todo++) {
        if(UART_FR(UART0_ADDR) & UART_FR_RXFE) {
            break;
        }
        *ptr++ = UART_DR(UART0_ADDR);
    }
    return todo;
}

caddr_t _sbrk(int incr) { return (caddr_t) 0; }

clock_t _times (struct tms *tp)
{
    clock_t timeval = 40;

	if (tp)
	{
		tp->tms_utime  = timeval;   /* user time */
		tp->tms_stime  = 0;         /* system time */
		tp->tms_cutime = 0;         /* user time, children */
		tp->tms_cstime = 0;         /* system time, children */
    }
    return timeval;
}

int _write(int file, char *ptr, int len)
{
    int todo;

    for (todo = 0; todo < len; todo++) {
        UART_DR(UART0_ADDR) = *ptr++;
    }
    return len;
}
