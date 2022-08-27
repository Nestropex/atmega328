


#include "datatypes.h"
#include <avr/io.h>
#include "cfg.h"
#include "system.h"
#include "timer.h"


#define REG_RESET 0u
#define ENABLE_INT_T1_A_COMP 0x02u
#define ENABLE_INT_T1_B_COMP 0x04u
#define ENABLE_INT_T1_OVF     0x01u
static void set_timer_frequency(void);

uint32_t timer_init(void)
{
    TCCR1A = REG_RESET; 
    TCCR1B = REG_RESET;
    TIMSK1 = REG_RESET;
    TIMSK1 = ENABLE_INT_T1_A_COMP | ENABLE_INT_T1_B_COMP | ENABLE_INT_T1_OVF; 
    TIFR1  = REG_RESET;
    TIFR1  = ENABLE_INT_T1_A_COMP | ENABLE_INT_T1_B_COMP | ENABLE_INT_T1_OVF; 
    set_timer_frequency();

    return SYSTEM_CLK/TIMER_16BIT_PRESCALER;
}

static void set_timer_frequency(void)
{
    switch (TIMER_16BIT_PRESCALER)
    {
    case 1u:
        TCCR1B |= 0x01u;
        break;
    case 8u:
        TCCR1B |= 0x02u;
        break;
    case 64u:
        TCCR1B |= 0x03u;
        break;
    case 256u:
        TCCR1B |= 0x04u;
        break;
    case 1024u:
        TCCR1B |= 0x05u;
        break;
    
    default:
        system_error_handler("ERROR set_timer_frequency");
        break;
    }
}

uint16_t timer_get_16bit_ticks(void)
{

return TCNT1L | TCNT1H << 8;
}


void timer_set_compare(uint8_t port, uint8_t pin, uint16_t comp_val)
{
    if (port = 2u)
    {
        switch (pin)
        {
        case 1u:
            OCR1A = comp_val;
            break;
        case 2u:
            OCR1B = comp_val;
            break;
        case 3u:
            OCR2A = comp_val;
            break;
        default:
            ERROR_HANDLER("timer_set_compare");
            break;
        }
    }
    else if (port = 3u)
    {
        switch (pin)
        {
        case 3u:
            OCR2B = comp_val;
            break;
        case 5u:
            OCR0B = comp_val;
            break;
        case 6u:
            OCR0A = comp_val;
            break;
        
        default:
            ERROR_HANDLER("timer_set_compare");
            break;
        }
    }
    else
    {
        ERROR_HANDLER("timer_set_compare");
    }
}