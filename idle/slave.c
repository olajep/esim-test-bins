#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

asm(".global __CORE_ROW_;");
asm(".set __CORE_ROW_,0x20;");
asm(".global __CORE_COL_;");
asm(".set __CORE_COL_,0x9;");


volatile static unsigned quit = 0;

void interrupt_handler() __attribute__ ((interrupt )) __attribute__ ((aligned(8)));
void interrupt_handler()
{
  // TODO: Should just return if IRET is not overwritten (see main TODO)
  printf("User interrupt handler, exiting\n");
  exit(0);
}

void stop()
{
  printf("Exiting\n");
  exit(0);
}

int main()
{
  register uint32_t addr __asm__("r41");
  uint32_t *ivt;
  static int times = 0;

  if (times)
    {
      printf("Got synced\n");
      return 0;
    }

  times++;

  addr = (uint32_t) stop;

  /* IVT user interrupt branch instruction */
  ivt = (uint32_t *) 0x24;
  *ivt = (uint32_t) 0xe8 | ((((uint32_t) interrupt_handler) - 0x24) << 7);

  // set iret to stop
  // won't work will be overwritten in simulator
  // TODO: check if hardware does the same
  __asm__("movts iret, r41");

  // clear imask
  __asm__("gie");
  __asm__("movt r40, 0"); //
  __asm__("mov r40, 0");  // Mask nothing ...
  __asm__("movts imask, r40");

  __asm__("idle");


  return 0;
}
