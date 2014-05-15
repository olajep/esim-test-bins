#include <stdio.h>
#include <stdint.h>

volatile static unsigned quit = 0;

void interrupt_handler() __attribute__ ((interrupt)) __attribute__ ((aligned(8)));
void interrupt_handler()
{
  //__asm__("gid");
  static int i = 0;
  int j;
  switch (i)
    {
    case 0: printf("Hello\n"); break;
    case 1: printf("World\n"); break;
    case 2: printf("Goodbye\n"); break;
    case 3: printf("World\n"); break;
    default: printf("Enough, I want out\n"); quit = 1; break;
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

  // clear imask
  __asm__("mov r40, 0");
  __asm__("movts imask, r40");

  //__asm__("swi");
  //__asm__("swi");
  //__asm__("swi");
  //__asm__("swi");
  //__asm__("swi");

  while (!quit) ;

  return 0;
}
