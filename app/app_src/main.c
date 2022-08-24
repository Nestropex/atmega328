
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

    error |= gpio_setup(1U,(const uint8_t *)gc_portb_dir);
    error |= gpio_setup(2U,(const uint8_t *)gc_portc_dir);
    error |= gpio_setup(3U,(const uint8_t *)gc_portd_dir);

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
    pin_t dir1  = {.port = 3u, .bit = 2u,.state = 0u};
    pin_t step1 = {.port = 3u, .bit = 3u,.state = 0u};
    pin_t dir2  = {.port = 3u, .bit = 4u,.state = 0u};
    pin_t step2 = {.port = 3u, .bit = 5u,.state = 0u};

    pin_t switch1  = {.port = 1u, .bit = 1u,.state = 0u};
    pin_t switch2  = {.port = 2u, .bit = 4u,.state = 0u}; 
    pin_t button1  = {.port = 1u, .bit = 0u,.state = 0u}; 
    pin_t button2  = {.port = 2u, .bit = 5u,.state = 0u}; 
    pin_t button3  = {.port = 1u, .bit = 2u,.state = 0u};
    
    //gpio_write(dir1.port,dir1.bit,1);
    gpio_write(dir2.port,dir2.bit,1);
    
    gpio_write(step2.port,step2.bit,1);

    button1.state = gpio_read(button1.port, button1.bit);

    if(button1.state != 0u)
    {
        gpio_write(step1.port,step1.bit,1);
    }
    else
    {
        gpio_write(step1.port,step1.bit,0);
    }
    
}