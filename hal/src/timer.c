


#include "datatypes.h"
#include <avr/io.h>
#include "system.h"
#include "isr.h"
#include "timer.h"


#define ENABLE_INT_T1_A_COMP 0x02u
#define ENABLE_INT_T1_B_COMP 0x04u
#define ENABLE_INT_T1_OVF    0x01u

static void set_timer_frequency(timer_t timer, uint16_t prescaler);

uint32_t timer0_init(uint32_t clk, uint16_t prescaler)
{
    TCCR0A  = REG_RESET;
    TCCR0B  = REG_RESET;
    TIMSK0  = REG_RESET;
    TIFR0   = REG_RESET;
    set_timer_frequency(Timer0, prescaler);

    return clk/prescaler; 
}

uint32_t timer1_init(uint32_t clk, uint16_t prescaler)
{
    TCCR1A  = REG_RESET;
    TCCR1B  = REG_RESET;
    TIMSK1  = REG_RESET;
    TIFR1   = REG_RESET;
    set_timer_frequency(Timer1, prescaler);
    
    return clk/prescaler; 
}

uint32_t timer2_init(uint32_t clk, uint16_t prescaler)
{
    TCCR2A  = REG_RESET;
    TCCR2B  = REG_RESET;
    TIMSK2  = REG_RESET;
    TIFR2   = REG_RESET;
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
