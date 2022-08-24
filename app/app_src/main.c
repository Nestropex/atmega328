
#include "datatypes.h"
#include <avr/io.h>
#include "watchdog.h"
#include "gpio.h"
#include "cfg.h"

#define SET_WDT_CHANGE_ENABLE 0x10u
#define DISABLE_WDT 0xf7u;

static void init(void);
static void read_inputs(void);
static void write_outputs(void);

static void init(void)
{
    watchdog_reset();
    watchdog_disable();

    GPIO_setup(1U,gc_portb_cfg);
}

static void read_inputs(void)
{

}

static void write_outputs(void)
{
    GPIO_write(1,5,1);
}

int main(void)
{
    init();
 
    while(1)
    {  
        read_inputs();
        write_outputs();
    }

    return 0;
}
