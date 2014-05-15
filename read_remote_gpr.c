#define CORE_MMR_BASE 0xf0000

#include <stdint.h>

/* Reading remote gpr */

int main()
{
  uint32_t read;
  uint32_t *remote_r40;
  remote_r40 = (uint32_t *) (0x808f0000 + (40<<2));
  /* Should fail here if remote core is active */
  read = *remote_r40;
  return read;
}
