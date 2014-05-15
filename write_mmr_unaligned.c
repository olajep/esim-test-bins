#define CORE_MMR_BASE 0xf0000

#include <stdint.h>

int main()
{
  register uint32_t r40 asm ("r40");
  uint32_t *ptr;
  ptr = (uint32_t*)(CORE_MMR_BASE+1);
  ptr += 40;
  *ptr = 0x13;

  return r40;
}
