#include <inttypes.h>
#include <stdio.h>

#include "gic.h"

#define MASK_32BIT  0xFFFFFFFFLL

extern uint32_t _gt_get_freq(void);
extern uint64_t _gt_get_count(void);
extern uint32_t _gt_get_kctl(void);
extern uint32_t _gt_get_tval(void);
extern uint32_t _gt_get_ctl(void);
extern uint64_t _gt_get_cval(void);
extern void _gt_set_tval(uint32_t val);
extern void _gt_set_ctl(uint32_t val);
extern void _gt_set_cval(uint64_t val);
extern void _gt_start(void);
extern void _gt_stop(void);
extern void _enable_interrupts(void);

void kernel_main(void)
{
    uint64_t count, cval;
    uint32_t freq, tval1, tval2;

    freq = _gt_get_freq();

    printf("\n[ Generic Interrupt Controller ]\n\n");
    printf("Map:\t\t0x%08x\n", (unsigned int)gic_get_addr());
    printf("GICD_TYPER:\t0x%08x\n", (unsigned int)gicd_get_reg(GICD_TYPER));
    printf("GICD_PPISR:\t0x%08x\n", (unsigned int)gicd_get_reg(GICD_PPISR));

    printf("\n[ Generic Timer ]\n\n");

    _gt_stop();

    printf("=> stop\n");
    printf("CNTFRQ:\t\t%" PRIu32 "\n", freq);

    count = _gt_get_count();

    printf("CNTPCT:\t\t%" PRIu64 "\n", count);
    printf("CNTPCT_LOW:\t%" PRIu32"\n",(uint32_t)(count & MASK_32BIT));
    printf("CNTP_CVAL:\t%" PRIu64 "\n", _gt_get_cval());
    printf("CNTKCTL:\t0x%08x\n", (unsigned int)_gt_get_kctl());
    printf("CNTP_CTL:\t0x%08x\n", (unsigned int)_gt_get_ctl());

    printf("\n=> setting\n");

    cval = _gt_get_count() + 20000000;
    tval1 = _gt_get_tval();
    _gt_set_cval(cval);
    tval2 = _gt_get_tval();

    printf("CompareValue:\t\t%" PRIu64 "\n", cval);
    printf("TimerValue (before):\t%" PRIu32 "\n", tval1);
    printf("TimerValue (after):\t%" PRIu32 "\n", tval2);

    printf("\n=> start\n");

    _enable_interrupts();
    _gt_start();

    printf("CNTKCTL:\t0x%08x\n", (unsigned int)_gt_get_kctl());
    printf("CNTCTL:\t\t0x%08x\n", (unsigned int)_gt_get_ctl());

    while (1) {
        /* Loop forever */
        printf("CNTPCT: %" PRIu64 " ; CNTP_CVAL: %" PRIu64
               " ; CNTPTVAL: %" PRIu32 " ; CNTP_CTL: 0x%08x\n",
               _gt_get_count(), cval, _gt_get_tval(),
               (unsigned int)_gt_get_ctl());
    }
}
