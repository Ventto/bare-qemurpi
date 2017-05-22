#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <inttypes.h>

static uint32_t get_freq(void)
{
    uint32_t val;

    __asm volatile("mrc p15, 0, %0, c14, c0, 0" : "=r" (val));

    return val;
}

static uint64_t get_cntpct(void)
{
    uint64_t val;

	__asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r" (val));

    return val;
}

int main(void) {
	do {
		printf("CNTPCT=" "%" PRIu64 " , CNTFRK=" "%" PRIu32 ", _times()=%lu\n",
                get_cntpct(), get_freq(), times(NULL));

	} while (1);
}
