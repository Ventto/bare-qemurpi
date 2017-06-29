#include <inttypes.h>
#include <stdio.h>

#include "bcm2836_control.h"
#include "generic_timers.h"
#include "irq.h"

/* ARM Controller Register bits to enable core timer IRQs */
#define CTL_CNTPNSIRQ   0x2
#define CTL_CNTPSIRQ    0x1

/* Generic timer tick */
#define NEXT_TICK               15000000

#define MASK_32BIT              0xFFFFFFFFLL

void not_main(void)
{
    uint64_t count;
    uint32_t freq, tval;

    /* Disable and mask the timer */
    gt_disable();

    freq  = gt_get_freq();
    count = gt_get_count();
    tval  = gt_get_tval();

    printf("\n[ Generic PL1 Physical Timer ]\n\n");
    printf("Register values:\n");
    printf("CNTFRQ:\t\t%" PRIu32 "\n", freq);
    printf("CNTPCT:\t\t%" PRIu64 "\n", count);
    printf("CNTP_CVAL:\t%" PRIu64 "\n", gt_get_cval());
    printf("\n=> Disable timer\n\n");
    printf("Register values:\n");
    printf("CNTKCTL:\t0x%08x\n", (unsigned int)gt_get_kctl());
    printf("CNTP_CTL:\t0x%08x\n", (unsigned int)gt_get_ctl());
    printf("\n=> Set CompareValue\n\n");
    printf("TimerValue (before):\t%" PRIu32 "\n", tval);
    printf("CompareValue:\t\t%" PRIu64 "\n", gt_get_cval());
    printf("TimerValue (after):\t%" PRIu32 "\n", gt_get_tval());

    /* Enable cores to receive IRQ */
    enable_irqs();

    /* Enable ARM controller to route IRQ to core_0 */
    bcm_enable_core_timer_irqs(0, (CTL_CNTPNSIRQ | CTL_CNTPSIRQ));

    /* Set comparevalue that causes timer value update */
    gt_set_cval(gt_get_count() + NEXT_TICK);

    /* Enable and unmask the timer */
    gt_enable();

    printf("\n=> Enable timer\n\n");
    printf("Register values:\n");
    printf("CNTKCTL:\t0x%08x\n", (unsigned int)gt_get_kctl());
    printf("CNTCTL:\t\t0x%08x\n", (unsigned int)gt_get_ctl());

    printf("\n=> Count down\n\n");
    while (1) {
        printf("CNTPCT: %" PRIu64 " ;\tCNTPTVAL: %" PRIu32
                " ;\tCNTP_CTL: 0x%08x\n",
               gt_get_count(), gt_get_tval(), (unsigned int)gt_get_ctl());
    }
}
