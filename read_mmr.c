#define CORE_MMR_BASE 0xf0000

#include <stdint.h>

/* Return 0 on success */

int main()
{
  register uint32_t r40 asm ("r40");
  uint32_t *ptr;
  r40 = 40;
  ptr = (uint32_t*)(CORE_MMR_BASE);
  ptr += 40;
  return (*ptr == 40 ? 0 : 1);
}
