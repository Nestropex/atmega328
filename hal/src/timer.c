


#include "datatypes.h"
#include <avr/io.h>
#include "system.h"
#include "isr.h"
#include "timer.h"


#define TCCR0A_CFG 0x0u
#define TCCR0B_CFG 0x0u
#define TCCR1A_CFG 0x1au
#define TCCR1B_CFG 0x09u
#define TCCR2A_CFG 0xf3u
#define TCCR2B_CFG 0x1u

static void set_timer_frequency(timer_t timer, uint16_t prescaler);

void timer_init(timer_t timer, uint32_t clk, uint16_t prescaler)
{
    switch (timer)
    {
    case Timer0:
        TCCR0A  = TCCR0A_CFG;
        TCCR0B  = TCCR0B_CFG;
        TIMSK0  = REG_RESET;
        TIFR0   = REG_RESET;
        break;
    case Timer1:
        TCCR1A  = TCCR1A_CFG;
        TCCR1B  = TCCR1B_CFG;
        TIMSK1  = REG_RESET;
        TIFR1   = REG_RESET;
        break;
    case Timer2:
        TCCR2A  = TCCR2A_CFG;
        TCCR2B  = TCCR2B_CFG;
        TIMSK2  = REG_RESET;
        TIFR2   = REG_RESET;
        break;
    
    default:
        break;
    }

    set_timer_frequency(timer, prescaler);

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
