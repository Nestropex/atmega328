

#include <avr/wdt.h>


void watchdog_reset(void)
{
    wdt_reset();
}

void watchdog_disable(void)
{
    wdt_disable();
}

uint8_t watchdog_enable(uint8_t timeout)
{
    uint8_t ret_val = 0u;

    switch (timeout)
    {
    case 1u:
        wdt_enable(WDTO_1S);
        break;

    case 2u:
        wdt_enable(WDTO_2S);
        break;

    case 4u:
        wdt_enable(WDTO_4S);
        break;
    
    default:
        ret_val = 0xffU;
        break;
    }

    return ret_val;
}