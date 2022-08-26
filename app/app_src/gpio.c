#include "datatypes.h"
#include <avr/io.h>
#include "system.h"


void gpio_init(uint8_t port, const uint8_t *pin_config)
{
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
            ERROR_HANDLER("ERROR gpio_init");
                break;
        }
    }
}


void gpio_write(uint8_t port, uint8_t pin, uint8_t state)
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
        ERROR_HANDLER("ERROR gpio_write");
            break;
    }
}

uint8_t gpio_read(uint8_t port, uint8_t pin)
{
    uint8_t ret_state = 0xffU;


        switch (port)
        {           
            case 1:
                ret_state = PINB;
                break;
            
            case 2:
                ret_state = PINC;
                break;
            
            case 3:
                ret_state = PIND;
                break;
            
            default:
            ERROR_HANDLER("ERROR gpio_read");
                break;
        }
   
    ret_state &= (1 << pin);

    return ret_state >> pin;
}

void gpio_flash(uint8_t port, uint8_t pin, uint16_t frequency)
{

}