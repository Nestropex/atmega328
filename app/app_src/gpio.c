#include "datatypes.h"
#include <avr/io.h>


uint8_t GPIO_setup(uint8_t port, const uint8_t *pin_config)
{
    uint8_t ret_val = 0u;
    for(uint8_t i = 0u; i < 8; i++)
    {
        switch (port)
        {
            case 1U:
                DDRB |= *(pin_config + i) << i;
                break;

            case 2U:
                DDRC = *(pin_config + i) << i;
                break;

            case 3U:
                DDRD = *(pin_config + i) << i;
                break;

            default:
                ret_val = 0xffu; 
                break;
        }
    }

    return ret_val;

}


void GPIO_write(uint8_t port, uint8_t pin, uint8_t state)
{

    switch (port)
    {
        case 1U:
            if (state == 0U)
            {
                PORTB &= ~(1 << pin);
            }else
            {
                PORTB |= 1 << pin;
            }             
            break;
        
        case 2U:
            if (state == 0U)
            {
                PORTC &= ~(1 << pin);
            }else
            {
                PORTC |= 1 << pin;
            }
            break;
        
        case 3U:
            if (state == 0U)
            {
                PORTD &= ~(1 << pin);
            }else
            {
                PORTD |= 1 << pin;
            }
            break;
        
        default:
            break;
    }
}

uint8_t GPIO_read(uint8_t port, uint8_t pin)
{
    uint8_t ret_state = 0xffU;


        switch (port)
        {           
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