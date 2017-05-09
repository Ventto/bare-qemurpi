#define BASE_ADDR   0x3f000000
#define UART_DR     0x201000

volatile unsigned int * const UARTDR = (unsigned int *)(BASE_ADDR + UART_DR);

void printf(const char *s) {
 	while(*s != '\0') {
        /* Transmit char */
		*UARTDR = (unsigned int)(*s);
		/* Next char */
        s++;
	}
}

void main(void) {
	printf("Hello world!\n");
}
