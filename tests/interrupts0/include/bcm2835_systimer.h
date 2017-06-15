#ifndef BCM2835_SYSTIMER_H
#define BCM2835_SYSTIMER_H

#include <stdint.h>
#include "bcm2835_peripherals.h"

#define ST_BASE             (PERIPHERAL_BASE + 0x3000)

#define ST_REG_CONTROL      (uint32_t *)(ST_BASE + 0x00)
#define ST_REG_COUNTER_LO   (uint32_t *)(ST_BASE + 0x04)
#define ST_REG_COUNTER_HI   (uint32_t *)(ST_BASE + 0x08)
#define ST_REG_COMPARE(n)   (uint32_t *)(ST_BASE + 0x0C + (n) * 4)
#define ST_TIMER_M0         (1 << 0)
#define ST_TIMER_M1         (1 << 1)
#define ST_TIMER_M2         (1 << 2)
#define ST_TIMER_M3         (1 << 3)

#define ST_DEFAULT_TIMER    3

#endif
