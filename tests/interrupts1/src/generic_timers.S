.section .text

/** From ARM Architecture Reference Manual: ARMv7-A and ARMv7-R edition
    B8: The Generic Timer */

.equ    GT_CTRL_ENABLE,     0x01
.equ    GT_CTRL_INT_MASK,   0x02
.equ    GT_CTRL_INT_STATUS, 0x03

/**
    B8.2 Generic Timer registers summary

    |Name,VMSA  | coproc|<CRn>  |<opc1> |<CRm>  |<opc2> | size   |
    |-----------|-------|-------|-------|-------|-------|--------|
    |CNTFRQ     | p15   |c14    |0      |c0     |   0   | 32-bit |
    |CNTPCT     | p15   |c14    |0      |c14    |   0   | 64-bit |
    |CNTP_TVAL  | p15   |c14    |0      |c2     |   0   | 32-bit |
    |CNTP_CTL   | p15   |c14    |0      |c2     |   1   | 32-bit |

    Accessing 32-bit:

    MRC op1{cond} coproc, #opc1, Rt, CRn, CRm{, #opc2}  ; Read
    MCR -                                               ; Write

    Accessing 64-bit:

    MRRC{cond} coproc, #opcode, Rt, Rt2, CRm            ; Read
    MCRR -                                              ; Write */

.global _gt_get_freq
_gt_get_freq:
        mrc     p15, 0, r0, c14, c0, 0
        mov     pc, lr

.global _gt_get_count
_gt_get_count:
        mrrc p15, 0, r1, r0, c14
        mov     pc, lr

.global _gt_get_tval
_gt_get_tval:
        mrc     p15, 0, r0, c14, c2, 0
        mov     pc, lr

.global _gt_get_ctl
_gt_get_ctl:
        mrc     p15, 0, r0, c14, c2, 1
        mov     pc, lr

.global _gt_set_cval
_gt_set_tval:
        mcr     p15, 0, r0, c14, c2, 0
        mov     pc, lr

.global _gt_set_tval
_gt_set_ctl:
        mcr     p15, 0, r0, c14, c2, 1
        mov     pc, lr

.global _gt_start
_gt_start:
        /** B8.1: Operation of the timer output sinal

            Condition to assert a timer:
                - timer enabled
                - timer output signal not masked

            B4.1.27: CNTP_CTL, PL1 Physical Timer Control register

                * bit[0]: ENABLE    timer enabled if set
                * bit[1]: IMASK     timer signal not masked if not set */
        mrc     p15, 0, r0, c14, c2, 1
        orr     r1, r0, #0x1
        mcr     p15, 0, r1, c14, c2, 1
        mov     pc, lr

.global _gt_stop
_gt_stop:
        mrc     p15, 0, r0, c14, c2, 1
        bic     r1, r0, #0x2
        mcr     p15, 0, r1, c14, c2, 1
        mov     pc, lr

