#ifndef IRQ_H
#define IRQ_H

extern void _enable_irqs(void);
extern uint32_t _disable_irqs(void);
extern void _restore_irqs(uint32_t cpsr);

#endif
