#include <stdint.h>

asm(".global __core_row__;");
asm(".set __core_row__,0x20;");
asm(".global __core_col__;");
asm(".set __core_col__,0x8;");


#define SLAVE_COREID 0x809
#define ILAT_REGNO
int main()
{
  unsigned i,j;
  volatile uint32_t *slave_ilat, *slave_ilatst, *slave_ipend;
  slave_ilat   = (uint32_t *) ( (0x809 << 20) + 0xF0428 );
  slave_ilatst = (uint32_t *) ( (0x809 << 20) + 0xF042C );
  slave_ipend  = (uint32_t *) ( (0x809 << 20) + 0xF0434 );

  for (i=0; i < 10000000; ++i) ;

  // Trigger sync interrupt on remote

  *slave_ilatst = (1 << 9);

  return 0;

}
