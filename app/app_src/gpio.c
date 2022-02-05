#include "datatypes.h"
#include <avr/io.h>


error_t GPIO_setup(uint8_t port, uint8_t pin_config)
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


error_t GPIO_write(uint8_t port, uint8_t pin, uint8_t state)
{
    error_t ret_val = no_error;

    if (state == 0U)
    {
        switch (port)
        {
            case 0:
                ret_val = error;
                break;
            
            case 1:
                PORTB &= ~(1 << pin);
                break;
            
            case 2:
                PORTC &= ~(1 << pin);
                break;
            
            case 3:
                PORTD &= ~(1 << pin);
                break;
            
            default:
                ret_val = error;
                break;
        }
    }
    else if(state == 1U)
    {
        switch (port)
        {
            case 0:
                ret_val = error;
                break;
            
            case 1:
                PORTB |= 1 << pin;
                break;
            
            case 2:
                PORTC |= 1 << pin;
                break;
            
            case 3:
                PORTD |= 1 << pin;
                break;
            
            default:
                ret_val = error;
                break;
        }
    }
    else
    {
        ret_val = error;
    }

    return ret_val;
}

uint8_t GPIO_read(uint8_t port, uint8_t pin)
{
    uint8_t ret_state = 0xffU;


        switch (port)
        {
            case 0:
               
                break;
            
            case 1:
                PINB = ret_state;
                break;
            
            case 2:
                PINC = ret_state;
                break;
            
            case 3:
                PIND = ret_state;
                break;
            
            default:

                break;
        }
   
    ret_state &= (1 << pin);

    return ret_state >> pin;
}