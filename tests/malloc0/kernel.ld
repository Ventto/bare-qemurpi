ENTRY(_Reset)
SECTIONS
{
  . = 0x8000;
  .ro : {
    startup.o (.text)
    *(.text)
    *(.rodata)
  }
  .rw : {
    *(.data)
     __bss_start__ = .;
     *(.bss COMMON)
     __bss_end__ = .;
  }
  . = ALIGN(8);
  heap_low = .;
  . = . + 0x10000;  /* 64kB of heap memory */
  heap_top = .;
  . = . + 0x10000;  /* 64kB of stack memory */
  stack_top = .;
}
