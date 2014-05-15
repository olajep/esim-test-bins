// core 0x808
int main()
{
    int i;
    int *p;
    p = (int *) 0x80880000;
    *p = 0;
    for (i = 0; i < 100000; i++);
    *p = 5;
    for (i = 0; i < 10000000; i++);
    return 0;
}

