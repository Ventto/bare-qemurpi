#include <stdio.h>
#include <inttypes.h>

#define FRQ_DEFAULT     62500000    /* Hz */
#define HZ_PER_MHZ       1000000

static inline void set_freq(uint32_t val)
{
    __asm volatile("mcr p15, 0, %0, c14, c0, 0" :: "r" (val));
}

static inline uint32_t get_freq(void)
{
    uint32_t val;

    __asm volatile("mrc p15, 0, %0, c14, c0, 0" : "=r" (val));

    return val;
}

static inline uint64_t get_cntpct(void)
{
    uint64_t val;

    __asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r" (val));

    return val;
}

int main(void) {
    set_freq(FRQ_DEFAULT);

    uint32_t freq = get_freq();
    uint64_t start, end;

    printf("\nARM System Counter Frequency:\n%.1f MHz\n\n",
            (float)freq / HZ_PER_MHZ);

    start = get_cntpct();

    /* FIXME: BEGIN */

    /* FIXME: END */

    end = get_cntpct();

    printf("Results:\n");
    printf("--Total (ticks): %" PRIu64 "\n", end - start);
    printf("--Total (secs): %.5f\n\n", (float)(end - start) / (float)freq);
}
