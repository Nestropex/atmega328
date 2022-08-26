


#include "datatypes.h"
#include "uart.h"
#include "gpio.h"
#include "cfg.h"

#define ERROR_FREQUENCY 10u

void system_error_handler(uint8_t *error_description)
{
    uart_str_transmit(error_description);
    uart_str_transmit("\n");

    gpio_flash(g_error_out.port, g_error_out.bit, ERROR_FREQUENCY);


}




