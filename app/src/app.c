

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"

void app_isr_timer_1_comp_a(void);

void app_init(void)
{
    timer1_init(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    timer2_init(SYSTEM_CLK, TIMER_TIMER2_PRESCALER);

    isr_register(&app_isr_timer_1_comp_a, Timer1_Comp_A);
    timer_set_compare(Timer1_Comp_A, 10000);

}
uint8_t state3;
uint16_t dummy_val = 0u;
void app_main(void)
{
    uint8_t var2 = 10;

    uint8_t data[] = "Hello World\n";
    uint16_t dummy = (uint16_t)timer1_get_ticks();
    uint8_t size = sizeof(data)/sizeof(uint8_t);
    dummy_val++;
    //uart_str_transmit("app_timer1 \n");
    //uart_nmb_transmit((uint32_t)dummy, 10u);

    if(dummy_val == 20000u)
    {
        
        gpio_write(g_out.step1.port, g_out.step1.bit,1);
     /* uart_str_transmit("\n");
    uart_str_transmit("main: ");
    uart_nmb_transmit(&app_isr_timer_0,10);
    uart_str_transmit("\n");*/

   
    }

    if(dummy_val == 20500)
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


void app_isr_timer_1_comp_a(void)
{
    //uart_str_transmit("\n");
}