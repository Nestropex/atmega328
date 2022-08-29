
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
static void app_isr_timer_0_ovf(void);

loop_t main_loop;
loop_t period_1_loop;
loop_t period_2_loop;
uint8_t state;
// Main function must be the first one in the file 
int main(void)
{
    init();
    app_init();
    main_loop.time_config = LOOP_MAIN_TIME;
    period_1_loop.time_config = LOOP_1_TIME;
    period_2_loop.time_config = LOOP_2_TIME;


    while(1)
    {  
        watchdog_reset();
        loop_control(&main_loop);
        if(main_loop.execute_flag == 1u)
        {   

            loop_control(&period_1_loop);
            if(period_1_loop.execute_flag == 1u)
            {                
                read_inputs();
                app_main();

            } 

            loop_control(&period_2_loop);
            if(period_2_loop.execute_flag == 1u)
            {
                system_error_update();

                if(state == 0u)
                {
                    state = 1u;
                }
                else
                {
                    state = 0u;
                }
                
                uart_str_transmit("Heartbeat\n");
                gpio_write(1,4,state);
            }

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
