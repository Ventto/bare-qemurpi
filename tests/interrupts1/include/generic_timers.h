#ifndef GENERIC_TIMERS_H
#define GENERIC_TIMERS_H

extern uint32_t _gt_get_freq(void);
extern uint64_t _gt_get_count(void);
extern uint32_t _gt_get_kctl(void);
extern uint32_t _gt_get_tval(void);
extern uint32_t _gt_get_ctl(void);
extern uint64_t _gt_get_cval(void);
extern void _gt_set_tval(uint32_t val);
extern void _gt_set_ctl(uint32_t val);
extern void _gt_set_cval(uint64_t val);
extern void _gt_enable(void);
extern void _gt_disable(void);

#endif
