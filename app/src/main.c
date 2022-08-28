
#include "datatypes.h"
#include "system.h"
#include "cfg.h"
#include "watchdog.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "gpio.h"
#include "app.h"

static void init(void);
static void read_inputs(void);
static void app_out(void);

static uint16_t timer0_ovf_cnt;
static void app_isr_timer_0_ovf(void);

uint8_t state0;
uint8_t state1;
uint16_t cnt_last_0;
uint16_t cnt_last_1;
uint16_t cnt_last_2;
// Main function must be the first one in the file 
int main(void)
{
    uint8_t flag;
    uint16_t ovf_cnt = 0u;
    init();
    app_init();

    while(1)
    {  
        watchdog_reset();
        if ((timer0_get_ticks() == 0u) && (flag == 1u))
        {
            ovf_cnt++;
            flag = 0u; // Avoid multiple executions while timer is 0

        if((ovf_cnt > cnt_last_0) && ((ovf_cnt % 30u) == 0u))
        {
            cnt_last_0 = ovf_cnt;
            
            read_inputs();
            app_main();

            if (state0 == 1u)
            {
                state0 = 0u;
            }
            else
            {
                state0 = 1;
            }

           gpio_write(1,4,state0);
        } 
 

        if((ovf_cnt > cnt_last_1) && ((ovf_cnt % 125u) == 0u))
        {
            system_error_update();
            cnt_last_1 = ovf_cnt;
   
            if (state1 == 1u)
            {
                state1 = 0u;
            }
            else
            {
                state1 = 1;
            }

            gpio_write(1,3,state1);
            
        }

        }

        if(timer0_get_ticks() == 255u)
        {
            flag = 1u;
        }
    }

    return 0;
}

static void init(void)
{  
    watchdog_init(1u);
    gpio_init(1U,(const uint8_t *)gc_portb_dir);
    gpio_init(2U,(const uint8_t *)gc_portc_dir);
    gpio_init(3U,(const uint8_t *)gc_portd_dir);
    system_init(g_error_out);
    uart_init();
    timer0_init(SYSTEM_CLK, TIMER_TIMER0_PRESCALER);
    isr_init();
    isr_register(&app_isr_timer_0_ovf, Timer0_OVF);

}

static void read_inputs(void)
{

}

static void app_isr_timer_0_ovf(void)
{

}