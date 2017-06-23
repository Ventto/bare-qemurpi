#ifndef GIC_H
#define GIC_H

#define GIC_BASE        0x003F0000UL
#define GICD_BASE       (GIC_BASE + 0x1000UL)
#define GICC_BASE       (GIC_BASE + 0x2000UL)

#define GICD_CTLR       0x000
#define GICD_TYPER      0x004
#define GICD_PPISR      0xD00

uint32_t gic_get_addr(void);
uint32_t gicd_get_reg(long reg);
uint32_t gicd_ptimer_status(void);

#endif
