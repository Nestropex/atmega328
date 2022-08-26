


#include "datatypes.h"
#include <avr/io.h>
#include "cfg.h"
#include "system.h"

#define REG_RESET 0u

static void set_timer_frequency(void);

uint32_t timer_init(void)
{
    TCCR1A = REG_RESET; 

    TCCR1B = REG_RESET;

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