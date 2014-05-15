// core 0x809
#include <stdio.h>
int main()
{
    int a;
    volatile int *p;
    p = (int *) 0x80880000;
    a = *p;
    while (! *p)
      {
        /* NOP */
        //printf("%d\n", *p);
      }
    return a;
}

