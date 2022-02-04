
int pwmtest(void);
int pwmmain(void)
{
    pwmtest();
    return 0;
}


int pwmtest(void)
{
    int array[5000];


    for (int i = 0; i<5000;i++)
    {
        array[i] = i;
    }
}