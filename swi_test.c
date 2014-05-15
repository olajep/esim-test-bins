#include <stdio.h>
#include <stdint.h>

void interrupt_handler() __attribute__ ((interrupt)) __attribute__ ((aligned(8)));
void interrupt_handler()
{
  static int i = 0;
  switch (i)
    {
    case 0: printf("Hello\n"); break;
    case 1: printf("World\n"); break;
    case 2: printf("Goodbye\n"); break;
    case 3: printf("World\n"); break;
    default: printf("Here we go again\n"); break;
    }
  i++;
}



int main()
{
  uint32_t *ivt; // user interrupt vector ptr
  uint32_t addr; // relative branch addr
  uint32_t br32; // relative addr branch instruction

  ivt = (uint32_t *) 0x24;

  addr = (uint32_t) &interrupt_handler;
  addr -= (uint32_t) ivt; // Adjust for user interrupt branch addr
  addr = (addr >> 1);     // Lowest bit is skipped (alignment)

  br32 = 0xe8;
  br32 |= ((addr & (0x00ffffff))) << 8;

  *ivt = br32;

  /* Loop on exception interrupt */
  ivt = (uint32_t *) 4;
  *ivt = 0x000000e8;

  // clear imask
  __asm__("mov r40, 0");
  __asm__("movts imask, r40");

  /* SWI is software interrupt, but we want user interrupt so write to
   * ILATST instead */
  //__asm__("swi");
  __asm__("mov r40, 0x200");
  __asm__("movts ilatst, r40");
  __asm__("movts ilatst, r40");
  __asm__("movts ilatst, r40");
  __asm__("movts ilatst, r40");
  __asm__("movts ilatst, r40");

  return 0;
}
