#include "datatypes.h"
#include <avr/io.h>


uint8_t GPIO_setup(uint8_t port, uint8_t pin_config)
{
    error_t ret_val = no_error;

    switch (port)
    {
        case 0:
            ret_val = error;
            break;

        case 1:
            DDRB = pin_config;
            break;

        case 2:
            DDRC = pin_config;
            break;

        case 3:
            DDRD = pin_config;
            break;

        default:
            ret_val  = error;
            break;
    }

    return ret_val;
}


int pwmtest(void)
{
    int array[5000];


    for (int i = 0; i<5000;i++)
    {
        array[i] = i;
    }
}