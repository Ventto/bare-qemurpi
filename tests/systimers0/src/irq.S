.section .text

.global enable_irqs
enable_irqs:
        mrs     r0, cpsr
        bic     r0, r0, #0x80   /* Clears IRQ mask */
        msr     cpsr_c, r0
        mov     pc, lr

.global disable_irqs
disable_irqs:
        mrs     r0, cpsr
        orr     r0, r0, #0x80   /* Sets IRQ mask */
        mov     pc, lr

.global restore_irqs
restore_irqs:
        msr cpsr_c, r0
        mov pc, lr
