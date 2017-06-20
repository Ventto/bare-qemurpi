.section .text
.global _start

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
        /* ldr sp, =stack_top */

        /* Copy the vector table at 0x8000 to the active table at 0x0000 */
        mov     r0, #0x8000
        mov     r1, #0x0000

        /* -- Loads vector table (8*32bits) and increments */
        ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
        stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

        /* -- Loads constants (8*32bits) and increments */
        ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
        stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}

        /** B1.3.1: Processor Modes

            | Proc. mode | Encoding     | Privilege Level |
            | IRQ        | 10010 - 0x12 | PL1             |
            | SVC        | 10011 - 0x13 | PL1             |

            B1.3.3: Program status registers (PSR)

                * Mask bits [8:6]:
                    - IRQ: bit[7] - 010
                    - FIQ: bit[6] - 001

                * Mode field [0:4]:
                    (see the table above)

                Ex:
                    0xD2:   [011]           [0]     [10010]
                            ^---(irq+fiq)   ^---(T) ^---(IRQ mode)
                    0xD3:   [011]           [0]     [10010]
                                                    ^---(SVC mode)
            */
        /*  Interrupt stack initialization */
        mov r0,#0xD2
        msr cpsr_c,r0
        mov sp,#0x7000

        /*  Applicative stack initialization */
        mov r0,#0xD3
        msr cpsr_c,r0
        mov sp,#0x8000

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
