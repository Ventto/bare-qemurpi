file kernel7.elf
target remote localhost:1234
tbreak kernel_main
break interrupt_vector
tabset
layout regs
