.section .text

.global _enable_irqs
_enable_irqs:
        mrs     r0, cpsr
        bic     r0, r0, #0x80   /* Clears IRQ mask */
        msr     cpsr_c, r0
        mov     pc, lr

.global _disable_irqs
_disable_irqs:
        mrs     r0, cpsr
        orr     r0, r0, #0x80   /* Sets IRQ mask */
        mov     pc, lr

.global _restore_irqs
_restore_irqs:
        msr cpsr_c, r0
        mov pc, lr
