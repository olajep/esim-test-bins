#define CORE_MMR_PC 0xf0408

#include <stdint.h>

int main()
{
  uint32_t *ptr;
  ptr = (uint32_t*)CORE_MMR_PC;
  *ptr = 0xdeadbeef;

  return 0;
}
