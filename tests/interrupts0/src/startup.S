.section .text
.global _start
.extern print_uart

/** From ARM Architecture Reference Manual: ARMv7-A and ARMv7-R edition
    B1.8.1 Exception vectors and exception base address
    Interrupt Vector Table */
_start:
        ldr pc, _reset_h
        ldr pc, _undef_h
        ldr pc, _swi_h       /* A8.8.228: Previously called SWI, now SVC */
        ldr pc, _prefetch_h
        ldr pc, _data_h
        ldr pc, _unused_h
        ldr pc, _irq_h
        ldr pc, _fiq_h

/* Constants that hold interrupt service routine's addresses. */
 _reset_h     : .word   _reset_
 _undef_h     : .word   undefined_instruction_vector
 _swi_h       : .word   software_interrupt_vector
 _prefetch_h  : .word   prefetch_abort_vector
_data_h       : .word   data_abort_vector
 _unused_h    : .word   _reset_
 _irq_h       : .word   interrupt_vector
 _fiq_h       : .word   fast_interrupt_vector

_reset_:
        ldr sp, =stack_top

        /* Copy the vector table at 0x8000 to the active table at 0x0000 */
        mov     r0, #0x8000
        mov     r1, #0x0000

        /* -- Loads vector table (8*32bits) and increments */
        ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
        stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

        /* -- Loads constants (8*32bits) and increments */
        ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
        stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

        bl      kernel_main

        /* If main returns for some reason than loop forever */
        b .

.global _enable_interrupts
_enable_interrupts:
        /* B1.3.3: CPSR holds interrupt disable bits */

        mrs     r0, cpsr        /* Stores CPSR into r0 */
        bic     r0, r0, #0x80   /* r0 = r0 & !op2 : Sets IRQ mask bit */

        /** CPSR_c is used instead of CPSR in the MSR instruction,
            to avoid altering the condition code flags. */

        msr     cpsr_c, r0      /* Write back CPSR from r0 */

        mov     pc, lr

output_str:    .ascii "CNTK_CTL:\n\0"

.align 4

.global _enable_pl1_ptimer
_enable_pl1_ptimer:

        /** B8.1: Operation of the timer output sinal

            Condition to assert a timer:
                - timer enabled
                - timer output signal not masked

            B8.2 Generic Timer registers summary

            |Name,VMSA  | coproc|<CRn>  |<opc1> |<CRm>  |<opc2> |
            |-----------|-------|-------|-------|-------|-------|
            |CNTP_CTRL  | p15   |c14    |0      |c2     |   1   |

            B4.1.27: CNTP_CTL, PL1 Physical Timer Control register

            Interesting bits:
                - bit[0]: ENABLE    1: timer enabled
                - bit[1]: IMASK     0: timer not masked
            Accessing CNTP_CTL:
            MRC op1{cond} coproc, #opc1, Rt, CRn, CRm{, #opc2} ; Read 32-bit
            MCR -                                              ; Write 32-bit*/

        mov     r0, #1                  /* IMASK = 0, ENABLE = 1 */
        mcr     p15, 0, r0, c14, c2, 1  /* Set CNTP_CTL */

        mov     pc, lr

.global _set_pl1_ptimer
_set_pl1_ptimer:
        /**
            B8.1.5 Timers: Operation of the CompareValue views of the timers

            CompareValue condition to assert a timer:
                - EventTriggered = ( (CNTPCT - CNT_CVAL) >= 0 )

            B8.2 Generic Timer registers summary

            |Name,VMSA  | coproc|<CRn>  |<opc1> |<CRm>  |<opc2> |
            |-----------|-------|-------|-------|-------|-------|
            |CNTP_CVAL  | p15   |-      |2      |c14    |   -   |
            |CNTPCT     | p15   |-      |2      |c14    |   -   |

            B4.1.28: CNTP_CVAL, PL1 Physical Timer Compare Value register

            Accessing CNTP_CVAL:
            MRRC op1{cond} coproc, #opc1, Rt, Rt2, CRm  ; Read 64-bit
            MCRR -                                      ; Write 64-bit
            [Rt]    : low word
            [Rt2]   : high word
            */

        mrrc    p15, 0, r0, r1, c14 /* Read CNTPCT */
        add     r0, r0, #2000
        add     r0, r0, #2000
        add     r0, r0, #2000
        //mcrr    p15, 2, r0, r1, c14 /* Write CNTP_CVAL */
        mcr     p15, 0, r0, c14, c2, 0  /* Set CNTP_TVAL */

        mov     pc, lr

