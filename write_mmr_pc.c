#define CORE_MMR_PC 0xf0408

#include <stdint.h>

volatile int trice = 0;

int main()
{
  volatile uint32_t *pc;
  trice++;
  if (trice==3) goto out;
  pc = (uint32_t*)CORE_MMR_PC;
  *pc = (uint32_t) main;

out:
  // 3
  return trice;
}
