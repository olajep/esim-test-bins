#define SLAVE_COREID 0x809
#define SLAVE_FUN_PTR_OFFSET 0x10000
#define PC_OFFSET 0xF0408

#include <stdint.h>
#include <string.h>

void exit5()
{
  __asm__("mov r0, 5");
  __asm__("trap 3");
}
void exit5_end()
{
}

int main()
{
  volatile uint32_t *slave_fun;

  int i;
  slave_fun = (uint32_t *) ((SLAVE_COREID << 20) + SLAVE_FUN_PTR_OFFSET);
//  ack = exit_fun+1;
  for (i = 0; i < 10000; ++i) ;
//  printf("%p\n", (void *) *slave_fun);
  memcpy((void *) *slave_fun, (void *) exit5, exit5_end-exit5);
//  *ack = 0;
//  while (!*ack)
//    *slave_pc = *exit_fun;

#if 0
  printf("exit_fun=%p slave_pc=%p\n", exit_fun, slave_pc);
#endif
  return 0;
}
