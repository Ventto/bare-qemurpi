#include <inttypes.h>
#include <stdio.h>

extern void _enable_interrupts(void);

extern uint32_t _gt_get_freq(void);
extern uint64_t _gt_get_count(void);
extern uint32_t _gt_get_tval(void);
extern uint32_t _gt_get_ctl(void);
extern void _gt_set_tval(uint32_t val);
extern void _gt_set_ctl(uint32_t val);
extern void _gt_start(void);
extern void _gt_stop(void);

void kernel_main(void)
{
    _gt_start();
    _gt_set_tval((_gt_get_count() >> 32) + 60000);
    _enable_interrupts();

    uint32_t freq = _gt_get_freq();

    printf("Generic Timer:\n\n");
    printf("CNTFRQ: %" PRIu32 "\n", freq);
    printf("CNTPCT: %" PRIu64 "\n", _gt_get_count());
    printf("CNTPCT_low: %" PRIu32"\n",(uint32_t)(_gt_get_count() & 0xffffffff));
    printf("CNTTVAL: %" PRIu32 "\n", _gt_get_tval());
    printf("CNTCTL: %08x\n", (unsigned int)_gt_get_ctl());

    while (1) {
        /* Loop forever */
    }
}
