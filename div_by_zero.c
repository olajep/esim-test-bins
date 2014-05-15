#include <stdio.h>
#include <stdint.h>

void exception_isr() __attribute__ ((interrupt)) __attribute__ ((aligned(8)));
//void user_isr() __attribute__ ((interrupt)) __attribute__ ((aligned(8)));
void exception_isr(int n)
{
  printf("exception_isr %d\n", n);
}

//void user_isr()
//{
//  static int i = 1;
//  int k = 0;
//  printf("user_isr before div by zero\n");
//  i += (i/k);
//  printf("user_isr after div by zero\n");
//  i++;
//}



int main()
{
  register uint32_t r38 __asm__("r38"); // Tmp for enabling setting fp exceptions

  uint32_t *ivt_exception; // interrupt vector ptrs
  uint32_t addr_exception; // relative branch addr
  uint32_t br32_exception; // relative addr branch instruction

//  ivt_usr = (uint32_t *) 0x24;
//  addr_usr = (uint32_t) &user_isr;
//  addr_usr -= (uint32_t) ivt_usr; // Adjust for user interrupt branch addr
//  addr_usr = (addr_usr >> 1);     // Lowest bit is skipped (alignment)
//  br32_usr = 0xe8;
//  br32_usr |= ((addr_usr & (0x00ffffff))) << 8;
//  *ivt_usr = br32_usr;

  ivt_exception = (uint32_t *) 0x4;
  addr_exception = (uint32_t) &exception_isr;
  addr_exception -= (uint32_t) ivt_exception; // Adjust for user interrupt branch addr
  addr_exception = (addr_exception >> 1);     // Lowest bit is skipped (alignment)
  br32_exception = 0xe8;
  br32_exception |= ((addr_exception & (0x00ffffff))) << 8;
  *ivt_exception = br32_exception;

  // clear imask
  __asm__("mov r40, 0");
  __asm__("movts imask, r40");

  // enable float exceptions
  __asm__("movfs r38, config");
  r38 |= 14;
  __asm__("movts config, r38");

  volatile float a = 1e38;
  volatile float b = 1e38;
  float c;
  c = a*b;

  printf("hej\n");
  return  !(c == 0.0);
}
