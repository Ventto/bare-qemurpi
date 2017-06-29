#ifndef IRQ_H
#define IRQ_H

extern void enable_irqs(void);
extern uint32_t disable_irqs(void);
extern void restore_irqs(uint32_t cpsr);

#endif
