
#include "datatypes.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "watchdog.h"
#include "gpio.h"
#include "cfg.h"


static void init(void);
static void read_inputs(void);
static void app_out(void);


// main function must be the first one in the file 
int main(void)
{
    init();
    
    while(1)
    {  
        watchdog_reset();
        read_inputs();
        app_out();
    }

    return 0;
}

static void init(void)
{
    uint8_t error = 0u;

    error |= watchdog_enable(1u);

    error |= GPIO_setup(1U,(const uint8_t *)gc_portb_dir);
    error |= GPIO_setup(2U,(const uint8_t *)gc_portc_dir);
    error |= GPIO_setup(3U,(const uint8_t *)gc_portd_dir);

    if(error != 0u)
    {
        // error_handler
    }

}

static void read_inputs(void)
{

}

static void app_out(void)
{
    pin_t dir1  = {.port = 3u, .bit = 2u,.dir = 1u};
    pin_t step1 = {.port = 3u, .bit = 3u,.dir = 1u};
    pin_t dir2  = {.port = 3u, .bit = 4u,.dir = 1u};
    pin_t step2 = {.port = 3u, .bit = 5u,.dir = 1u};
    
    GPIO_write(dir1.port,dir1.bit,1);
    GPIO_write(dir2.port,dir2.bit,1);
    GPIO_write(step1.port,step1.bit,1);
    GPIO_write(step2.port,step2.bit,1);
}