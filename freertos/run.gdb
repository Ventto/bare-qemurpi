file kernel.elf
target remote localhost:1234

tabset
#winheight src 30
#layout regs

set print thread-events

tb main
commands
info thread
end

b vTickISR
b xPortStartScheduler

b task1
b task2
b vTaskDelay
