/* Test: BCM2835 System Timer.
 * Goal: Raising the timer_3's IRQ.
 */

#include <stdio.h>
#include <inttypes.h>

#define BASE_ADDR       0x3F003000

#define REG_CONTROL     (uint32_t *)(BASE_ADDR + 0x00)
#define REG_COUNTER_LO  (uint32_t *)(BASE_ADDR + 0x04)
#define REG_COUNTER_HI  (uint32_t *)(BASE_ADDR + 0x08)
#define REG_COMPARE(n)  (uint32_t *)(BASE_ADDR + 0x0C + (n) * 4)

/* Default one used by the Linux Kernel */
#define DEFAULT_TIMER   3
#define NEXT_TICK       100000 /* us */


int main(void)
{
    uint64_t counter;

    *REG_COMPARE(DEFAULT_TIMER) = *REG_COUNTER_LO + NEXT_TICK;

    for (;;) {
        printf("VIRTUAL:\t" "%" PRIu32 " us\n\r", *REG_COUNTER_LO);
    }

    return 0;
}
