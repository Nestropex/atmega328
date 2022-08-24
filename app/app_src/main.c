
#include "datatypes.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "watchdog.h"
#include "gpio.h"
#include "cfg.h"


static void init(void);
static void read_inputs(void);
static void write_outputs(void);


// main function must be the first one in the file 
int main(void)
{
    init();
 
    while(1)
    {  
        watchdog_reset();
        read_inputs();
        write_outputs();
    }

    return 0;
}

static void init(void)
{
    uint8_t error = 0u;

    error |= watchdog_enable(1u);

    GPIO_setup(1U,gc_portb_cfg);

    if(error != 0u)
    {
        // error_handler
    }

}

static void read_inputs(void)
{

}

static void write_outputs(void)
{
    GPIO_write(1,5,1);
}