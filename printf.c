#include <stdio.h>

#include <e_lib.h>

int main()
{
    //register unsigned coreid asm("r40");
    //coreid=0x808;
    //__asm__("movfs r40, coreid");
    //printf("%d Hello World\n", e_get_coreid());
    int apa = e_get_coreid();
    return apa;
}
