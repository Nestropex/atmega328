

#include <avr/wdt.h>


void watchdog_reset(void)
{
    wdt_reset();
}

void watchdog_disable(void)
{
    wdt_disable();
}