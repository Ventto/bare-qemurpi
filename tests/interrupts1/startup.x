OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY (_start)

SECTIONS
{
  . = 0x8000;
  .ro               : {
    src/vectors.o (.text)
    *(.text)
    *(.rodata)
  }
  .rw               : {
    *(.data)
     __bss_start__ = .;
     *(.bss COMMON)
     __bss_end__ = .;
  }
  . = ALIGN(4);
  heap_low = .;
  . = . + 0x10000;  /* 64kB of heap memory */
  heap_top = .;
  . = . + 0x10000;  /* 64kB of stack memory */
  .stack            : {
    _stack = .;
    *(.stack)
  }
}
