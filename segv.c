/* Segfault in a nice way */
/* If run from gdb we should be able to get a backtrace etc. */

void increment(unsigned *ptr)
{
  (*ptr)++;
}

int main()
{
  unsigned *segv;
  segv = (unsigned *) 0xfffff000;
  increment(segv);
  return 0;
}
