#include <string.h>
#include <stdint.h>
#define CORE_MMR_BASE 0xf0000


int main()
{
  register uint32_t r40 asm ("r40");
  register uint32_t r41 asm ("r41");
  register uint32_t r42 asm ("r42");
  register uint32_t r43 asm ("r43");
  register uint32_t r44 asm ("r44");
  register uint32_t r45 asm ("r45");
  uint32_t buf[] = { 0, 1, 2, 3, 4, 5 };
  uint32_t *ptr;
  ptr = (uint32_t*)CORE_MMR_BASE;
  ptr += 40;
  memcpy((void *) ptr, (void *) buf, sizeof(buf));

  // 15
  return r40+r41+r42+r43+r44+r45;
}
