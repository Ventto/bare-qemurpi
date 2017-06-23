#include <inttypes.h>

#include "gic.h"

/* DDI0438 Cortex A15 Reference Manual */

/** 8.2.2: GIC memory-map

    The GIC registers are memory-mapped, with a physical base address specified
    by PERIPHBASE[39:15] into the Configuration Base Address Register (CBAR).

    4.3.63: Configuration Base Address Register

    To access the CBAR, read the CP15 register with:
    MRC p15, 4, <Rt>, c15, c0, 0                     */

uint32_t gic_get_addr(void)
{
    uint32_t cbar; //, addr;

    __asm__ volatile ("mrc p15, 4, %0, c15, c0, 0" : "=r" (cbar));

    return cbar;
}

uint32_t gicd_get_reg(long reg)
{
    return *((uint32_t *)(GICD_BASE + reg));
}

uint32_t gicd_ptimer_status(void)
{
    return *((uint32_t *)(GICD_BASE + GICD_PPISR)) & 0x6000;
}
