#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <time.h>

enum {
    UART_FR_RXFE = 0x10,
    UART_FR_TXFF = 0x20,
    UART0_ADDR = 0x3f201000,
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

clock_t _times (struct tms *buf)
{
  errno = EINVAL;
  return (-1);
}

int _write(int file, char *ptr, int len)
{
    int todo;

    for (todo = 0; todo < len; todo++) {
        UART_DR(UART0_ADDR) = *ptr++;
    }
    return len;
}
