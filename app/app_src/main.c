
int test(void);
int main(void)
{
    test();
    return 0;
}


int test(void)
{
    int array[5000];


    for (int i = 0; i<5000;i++)
    {
        array[i] = i;
    }
}