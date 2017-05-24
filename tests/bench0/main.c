#include <stdio.h>
#include <inttypes.h>

#define HZ_PER_MHZ      1000000     /* Hz */
#define FRQ_DEFAULT     62500000    /* Hz */
#define PRD_DEFAULT     16          /* ns */

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

    int sample = 3;
    uint32_t freq = get_freq();
    uint64_t start, end;

    for (int i = 0; i < sample;) {

        start = get_cntpct();

        /* FIXME: BEGIN */

        /* FIXME: END */

        end = get_cntpct();

        printf("FRQ: %.1f MHz\tPERIOD: %d ns\tElapsed time: " "%" PRIu64 " ns\n",
                (float)freq / HZ_PER_MHZ, PRD_DEFAULT >> i,
                (end - start) * (PRD_DEFAULT >> i));

        freq = FRQ_DEFAULT << ++i;
        set_freq(freq);
    }
}
