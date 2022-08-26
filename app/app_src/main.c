
#include "datatypes.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "watchdog.h"
#include "gpio.h"
#include "uart.h"
#include "cfg.h"


static void init(void);
static void read_inputs(void);
static void app_out(void);


// Main function must be the first one in the file 
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
    watchdog_init(1u);

    gpio_init(1U,(const uint8_t *)gc_portb_dir);
    gpio_init(2U,(const uint8_t *)gc_portc_dir);
    gpio_init(3U,(const uint8_t *)gc_portd_dir);

    uart_init();
}

static void read_inputs(void)
{

}
uint8_t state3;
uint16_t dummy_val = 0u;
static void app_out(void)
{
    uint8_t var2 = 10;

    uint8_t data[] = "Hello World\n";
    uint16_t *dummy = &dummy_val;
    uint8_t size = sizeof(data)/sizeof(uint8_t);
    dummy_val++;
    if(dummy_val == 40000u)
    {
        
        gpio_write(g_out.step1.port, g_out.step1.bit,1);
        //uart_str_transmit(data);

        //uart_nmb_transmit(var2, 16);
    }

    if(dummy_val == 40500)
    {
        gpio_write(g_out.step1.port, g_out.step1.bit,0);
        dummy_val = 0u;
    }
    
    const pin_t *switch1 = &g_in.switch1;
    const output_t *out = &g_out;
    int state = 0u;

    //gpio_write(dir1.port,dir1.bit,1);
    gpio_write(g_out.dir1.port, g_out.dir2.bit,1);
    
    //gpio_write(g_out.step1.port, g_out.step1.bit,1);

    state = gpio_read(g_in.switch1.port +10, g_in.switch1.bit);

    if(state != 0u)
    {
        //gpio_write(g_out.step1.port, g_out.step1.bit,1);
    }
    else
    {
      //  gpio_write(g_out.step1.port, g_out.step1.bit,0);
    }
    
}