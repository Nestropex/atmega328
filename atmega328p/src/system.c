


#include "datatypes.h"
#include "uart.h"
#include "gpio.h"


static uint8_t error_occurred;
static pin_t led;

void system_init(pin_t error_led)
{
    led = error_led;
}

void system_error_handler(uint8_t *error_description)
{
    uart_str_transmit(error_description);
    uart_str_transmit("\n");

    gpio_flash(led.port, led.bit);

    error_occurred = 1u;

}


void system_error_update(void)
{
    if (error_occurred != 0u)
    {
       system_error_handler("An ERROR has occurred at least once at start up");
    }
}



