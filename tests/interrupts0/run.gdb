file kernel7.elf
target remote localhost:1234
tbreak kernel_main
tabset
layout regs
