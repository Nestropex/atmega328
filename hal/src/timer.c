


#include "datatypes.h"
#include <avr/io.h>
#include "system.h"
#include "isr.h"
#include "timer.h"


#define ENABLE_INT_T1_A_COMP 0x02u
#define ENABLE_INT_T1_B_COMP 0x04u
#define ENABLE_INT_T1_OVF    0x01u
#define SET_MODE_MASK_A      0xf3u 
#define SET_MODE_MASK_B      0x8u 
#define SET_MODE_MASK_1_B    0x18u 
static void set_timer_frequency(timer_t timer, uint16_t prescaler);

uint32_t timer_init(timer_t timer, uint8_t mode, uint32_t clk, uint16_t prescaler)
{
    switch (timer)
    {
    case Timer0:
        TCCR0A  = SET_MODE_MASK_A & mode;
        TCCR0B  = SET_MODE_MASK_B & mode;
        TIMSK0  = REG_RESET;
        TIFR0   = REG_RESET;
        break;
    case Timer1:
        TCCR1A  = SET_MODE_MASK_A & mode;
        TCCR1B  = SET_MODE_MASK_1_B & mode ;
        TIMSK1  = REG_RESET;
        TIFR1   = REG_RESET;
        break;
    case Timer2:
        TCCR2A  = SET_MODE_MASK_A & mode;
        TCCR2B  = SET_MODE_MASK_B & mode;
        TIMSK2  = REG_RESET;
        TIFR2   = REG_RESET;
        break;
    
    default:
        break;
    }

    set_timer_frequency(timer, prescaler);

    return clk/prescaler; 
}

uint32_t timer1_init(uint32_t clk, uint16_t prescaler, uint8_t mode)
{

    set_timer_frequency(Timer1, prescaler);
    
    return clk/prescaler; 
}

uint32_t timer2_init(uint32_t clk, uint16_t prescaler, uint8_t mode)
{

    set_timer_frequency(Timer2, prescaler);
    
    return clk/prescaler; 
}

static void set_timer_frequency(timer_t timer, uint16_t prescaler)
{
    switch (prescaler)
    {
    case 0u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x00u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x00u;
        }
        else
        {
            TCCR2B |= 0x00u;
        }
        break;
    case 1u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x01u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x01u;
        }
        else
        {
            TCCR2B |= 0x01u;
        }
        break;
    case 8u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x02u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x02u;
        }
        else
        {
            TCCR2B |= 0x02u;
        }
        
        break;
    case 64u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x03u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x03u;
        }
        else
        {
            TCCR2B |= 0x04u;
        }
        break;
    case 256u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x04u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x04u;
        }
        else
        {
            TCCR2B |= 0x06u;
        }

        break;
    case 1024u:
        if (timer == Timer0)
        {
            TCCR0B |= 0x05u;
        }
        else if (timer == Timer1)
        {
            TCCR1B |= 0x05u;
        }
        else
        {
            TCCR2B |= 0x07u;
        }
        break;
    
    default:
        system_error_handler("ERROR set_timer_frequency");
        break;
    }
}

uint8_t timer0_get_ticks(void)
{

return TCNT0;
}

uint16_t timer1_get_ticks(void)
{
    uint16_t low  = (uint16_t)TCNT1L; 
    uint16_t high = (uint16_t)TCNT1H;
    uint16_t count = (high << 8) | low;

    return count;

}

uint8_t timer2_get_ticks(void)
{

return TCNT2;
}

void timer_set_compare(interrupts_t nmb, uint16_t comp_val)
{

        switch (nmb)
        {
        case Timer0_Comp_A:
            OCR0A = comp_val;
            break;
        case Timer0_Comp_B:
            OCR0B = comp_val;
            break;
        case Timer1_Comp_A:
            OCR1A = comp_val;
            break;
        case Timer1_Comp_B:
            OCR1B = comp_val;
            break;
        case Timer2_Comp_A:
            OCR2A = comp_val;
            break;    
        case Timer2_Comp_B:
            OCR2B = comp_val;
            break;
        default:
            ERROR_HANDLER("ERROR timer_set_compare");
            break;
        }
}

uint32_t timer_get_frequency(uint32_t clk, uint16_t prescaler)
{
    return clk/prescaler;
}
