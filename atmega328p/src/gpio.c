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
static uint8_t state;

void gpio_flash(uint8_t port, uint8_t pin)
{
    if (state == 0u)
    {
        gpio_write(port, pin, 1u);
        state = 1u;
    }
    else
    {
        gpio_write(port, pin, 0u);
        state = 0u;
    }
    
    
}

void gpio_toggle(uint8_t port, uint8_t pin)
{
    switch (port)
    {
    case 1u:
        //Assembler necessary to toggle one pin at a time. See manual
        

        switch (pin)
        {
            case 0u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB0));
                break;
            case 1u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB1));
                break;
            case 2u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB2));
                break;
            case 3u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB3));
                break;
            case 4u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB4));
                break;
            case 5u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB5));
                break;
            case 6u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB6));
                break;
            case 7u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PINB7));
                break;
            
            default:
                ERROR_HANDLER("ERROR gpio_toggle port b");
                break;
        }
        break;
    case 2u:
        switch (pin)
        {
            case 0u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC0));
                break;
            case 1u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC1));
                break;
            case 2u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC2));
                break;
            case 3u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC3));
                break;
            case 4u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC4));
                break;
            case 5u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC5));
                break;
            case 6u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINC)), "I" (PINC6));
                break;
            
            default:
                ERROR_HANDLER("ERROR gpio_toggle port c");
                break;
        }

        break;
    case 3u:
        switch (pin)
        {
            case 0u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PINB)), "I" (PIND0));
                break;
            case 1u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND1));
                break;
            case 2u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND2));
                break;
            case 3u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND3));
                break;
            case 4u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND4));
                break;
            case 5u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND5));
                break;
            case 6u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND6));
                break;
            case 7u:
                asm ("sbi %0, %1 \n": : "I" (_SFR_IO_ADDR(PIND)), "I" (PIND7));
                break;
            
            default:
                ERROR_HANDLER("ERROR gpio_toggle port d");
                break;
        break;
        }
    
    default:
        ERROR_HANDLER("ERROR gpio_toggle");
        break;
    }
}