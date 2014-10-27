#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <e_lib.h>

int foo() { return 0; }
int bar() { return 1; }

int main()
{
    if (e_get_coreid() % 2)
        return foo();
    else
        return bar();

    return 0;
}

