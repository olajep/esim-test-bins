#include <stdint.h>

#define SLAVE_COREID 0x809
#define ILAT_REGNO
int main()
{
  unsigned i,j;
  volatile uint32_t *slave_ilat, *slave_ilatst, *slave_ipend;
  slave_ilat   = (uint32_t *) ( (0x809 << 20) + 0xF0428 );
  slave_ilatst = (uint32_t *) ( (0x809 << 20) + 0xF042C );
  slave_ipend  = (uint32_t *) ( (0x809 << 20) + 0xF0434 );

  // Might need to wait on real hardware
  for (i=0; i < 10000000; ++i) ;

  for (i=0; i < 5; ++i) {
    *slave_ilatst = (1 << 9);
    while (*slave_ilat) ;
  }

  return 0;

}
