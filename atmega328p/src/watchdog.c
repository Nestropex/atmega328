

#include <avr/wdt.h>
#include "system.h"

void watchdog_reset(void)
{
    wdt_reset();
}

void watchdog_disable(void)
{
    wdt_disable();
}

void watchdog_init(uint8_t timeout)
{
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
        ERROR_HANDLER("ERROR watchdocfg_pin_inputit");
        break;
    }


}