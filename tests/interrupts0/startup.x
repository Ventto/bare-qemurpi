OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY (_start)

SECTIONS
{
  . = 0x8000;
  .ro : {
    src/startup.o (.text)
    *(.text)
    *(.rodata)
  }
  .rw : {
    *(.data)
  }
  . = ALIGN(8);
  . = . + 0x1000;
  stack_top = .;
}
