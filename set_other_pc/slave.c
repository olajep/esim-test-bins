#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t *ptr;

void fun()
{
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
  __asm__("nop");
}

void loop()
{
  for (;;) fun();
}

int main()
{
  ptr = (uint32_t *) 0x10000;
  *ptr = 0x80900000 + (uint32_t) fun;
//  printf("*ptr=%p\n", (void *) *ptr);
  loop();
  return 0;
}
