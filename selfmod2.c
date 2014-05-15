#include <string.h>
#include <stdio.h>

int hello = 0;

void foo()
{
    if (!hello) {
	hello = 1;
	printf("Hello\n");
    }
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
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
}

void bar()
{
    printf("World\n");
}

void baz()
{
}

int main()
{
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    foo();
    memcpy(foo,bar, baz-bar);
    foo();
    return 0;
}
