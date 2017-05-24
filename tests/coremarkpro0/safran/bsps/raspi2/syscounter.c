#include <inttypes.h>

uint64_t get_cntpct(void)
{
     uint64_t val;

	__asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r" (val));

    return val;
}
