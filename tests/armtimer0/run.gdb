file kernel7.elf
target remote localhost:1234

tabset
layout regs

tb not_main
b interrupt_vector
