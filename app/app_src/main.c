
#include "datatypes.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include "watchdog.h"
#include "gpio.h"
#include "uart.h"
#include "cfg.h"
#include "system.h"
#include "timer.h"
#include "isr.h"
static void init(void);
static void read_inputs(void);
static void app_out(void);

void app_isr_timer_0(void);

// Main function must be the first one in the file 
int main(void)
{
    init();


    while(1)
    {  
        watchdog_reset();
        system_error_update();
        read_inputs();
        app_out();
        
    }

    return 0;
}

static void init(void)
{
    uart_str_transmit("start init");
    watchdog_init(1u);

    gpio_init(1U,(const uint8_t *)gc_portb_dir);
    gpio_init(2U,(const uint8_t *)gc_portc_dir);
    gpio_init(3U,(const uint8_t *)gc_portd_dir);
    isr_init();
    isr_register(&app_isr_timer_0, Timer1_Comp_A);
    uart_init();
    timer_init();

    
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
    uint16_t dummy = timer_get_16bit_ticks();
    uint8_t size = sizeof(data)/sizeof(uint8_t);
    dummy_val++;


    if(dummy_val == 200000u)
    {
        
        gpio_write(g_out.step1.port, g_out.step1.bit,1);
      uart_str_transmit("\n");
    uart_str_transmit("main: ");
    uart_nmb_transmit(&app_isr_timer_0,2);
    uart_str_transmit("\n");

   
    }

    if(dummy_val == 205000)
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

    state = gpio_read(g_in.switch1.port, g_in.switch1.bit);

    if(state != 0u)
    {
        //gpio_write(g_out.step1.port, g_out.step1.bit,1);
    }
    else
    {
      //  gpio_write(g_out.step1.port, g_out.step1.bit,0);
    }
    
}


void app_isr_timer_0(void)
{
    uart_str_transmit("function pointer executed\n");
}