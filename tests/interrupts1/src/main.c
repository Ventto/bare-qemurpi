#include <inttypes.h>
#include <stdio.h>

#include "bcm2836_control.h"
#include "generic_timers.h"
#include "irq.h"

#define MASK_32BIT  0xFFFFFFFFLL

void kernel_main(void)
{
    uint64_t count, cval;
    uint32_t freq, tval1, tval2;

    freq = _gt_get_freq();

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

    cval = _gt_get_count() + 15000000;
    tval1 = _gt_get_tval();
    _gt_set_cval(cval);
    tval2 = _gt_get_tval();

    printf("CompareValue:\t\t%" PRIu64 "\n", cval);
    printf("TimerValue (before):\t%" PRIu32 "\n", tval1);
    printf("TimerValue (after):\t%" PRIu32 "\n", tval2);

    printf("\n=> start\n");

    _enable_irqs();
    bcm_enable_timer_irqs(0, (CTL_CNTPNSIRQ_ENABLED | CTL_CNTPSIRQ_ENABLED));
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
