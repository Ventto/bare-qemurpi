file qemu-system-arm

set args  -M raspi2 -no-reboot -d guest_errors \
          -nographic -serial pty \
          -icount 1 \
          -kernel kernel.elf

tabset

winheight src 30

tb main

# -----------------------
#
#       PARSING
#
# -----------------------

b vl.c:4426

# -----------------------
#
#        LOADING
#
# -----------------------

b setup_boot

b arm_load_kernel

b arm_load_kernel_notify if kernel_size == -1
commands
disp kernel_size
end

b arm_load_elf

run
