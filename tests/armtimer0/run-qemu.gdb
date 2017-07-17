file qemu-system-arm

set args  -M raspi2 -no-reboot -d guest_errors \
          -nographic -serial pty \
          -icount 1 \
          -kernel kernel7.elf

tabset

tb main

# -----------------------
#
#   BCM2835 ARM TIMER
#
# -----------------------

# Control register is written

b bcm2835_armtimer_write if offset == ARM_TIMER_CTRL

# Ack register is written

b bcm2835_armtimer_write if offset == ARM_TIMER_INTCLR

# ARM Timer callback

b bcm2835_armtimer_cb

# -----------------------
#
#        PTIMER
#
# -----------------------

# Our timer expired and triggered its callback

b ptimer_tick

# Arms our timer

b timer_mod if ts == 0x555556944b80

# Checks our timer expiration

b timer_expired_ns if timer_head == 0x555556944b80

# Runs timers from our timer's parent list

b timerlist_run_timers if timer_list == 0x555556902900

run
