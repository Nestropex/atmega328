
#include "datatypes.h"
#include "system.h"
#include "cfg.h"
#include "watchdog.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "gpio.h"
#include "loop.h"
#include "app.h"

static void init(void);
static void read_inputs(void);
static void app_out(void);

static uint16_t timer0_ovf_cnt;
static void app_isr_timer_0_ovf(void);




loop_t main_loop;
loop_t period_1_loop;
loop_t period_2_loop;


    uint8_t state0;
    uint8_t state1;
    uint16_t cnt_last_0;
    uint16_t cnt_last_1;
    uint16_t cnt_last_2;
    uint16_t last_timer1;
    
// Main function must be the first one in the file 
int main(void)
{
    uint8_t flag;
    uint16_t ovf_cnt = 0u;
    uint16_t cur_timer1;
    init();
    app_init();
    period_1_loop.time_config = 1000u;
    uint32_t diff;

    while(1)
    {  
        watchdog_reset();
        if ((timer0_get_ticks() == 0u) && (flag == 1u))
        {   
            //loop_control(&main_loop);


            flag = 0u; // Avoid multiple executions while timer is 0

        loop_control(&period_1_loop);

        if(period_1_loop.execute_flag == 1u)
        {
   

            cnt_last_0 = main_loop.cnt;
            
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

           //loop_print(&main_loop, "main.");
           //loop_print(&period_1_loop, "period_1.");
           //loop_print(&period_2_loop, "period_2.");
        } 

        //loop_control(&period_2_loop);
        if((main_loop.cnt > period_2_loop.cnt) && ((main_loop.cnt % 60u) == 0u))
        {
            cnt_last_2 = main_loop.cnt;

            system_error_update();
  
   
            if (state1 == 1u)
            {
                state1 = 0u;
            }
            else
            {
                state1 = 1;
            }
            gpio_write(2,2,state1);
            
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
    uart_init(SYSTEM_CLK, UART_BAUDRATE);
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
