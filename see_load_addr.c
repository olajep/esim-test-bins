#include <string.h>
#include <stdio.h>

int hello = 5;

int main()
{
  int *ptr;
  ptr = &hello;
  return *ptr;
}
