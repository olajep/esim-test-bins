int main()
{
  int i;
  int a=0;

  for (i=0;i < 50000000; ++i)
    {
      ++a;

    }
  return a % 9;

}
