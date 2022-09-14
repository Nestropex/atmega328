
#include "datatypes.h"
#include "system.h"
#include "cfg.h"
#include "watchdog.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "gpio.h"
#include "period.h"
#include "app.h"

static void init(void);
static void read_inputs(void);
static void app_out(void);
static void app_isr_timer_0_ovf(void);

period_t main_loop;
period_t period_1_loop;
period_t period_2_loop;
uint8_t heartbeat;
// Main function must be the first one in the file 
int main(void)
{
    init();
    app_init();
    main_loop.time_config = LOOP_MAIN_TIME_MILLIS;
    period_1_loop.time_config = LOOP_1_TIME_MILLIS;
    period_2_loop.time_config = LOOP_2_TIME_MILLIS;


    while(1)
    {  
        watchdog_reset();
        period_control(&main_loop);
        if(main_loop.execute_flag == 1u)
        {   

            period_control(&period_1_loop);
            if(period_1_loop.execute_flag == 1u)
            {                
                app_main();
            } 

            period_control(&period_2_loop);
            if(period_2_loop.execute_flag == 1u)
            {
                system_error_update();

                if(heartbeat == 0u)
                {
                    heartbeat = 1u;
                }
                else
                {
                    heartbeat = 0u;
                }
                uart_str_transmit("heartbeat \n");
                uart_nmb_transmit(heartbeat,10);
                gpio_write(1,5,heartbeat);
            }

        }
    }

    return 0;
}

static void init(void)
{  
    uart_init(SYSTEM_CLK,UART_BAUDRATE);
    watchdog_init(1u);
    gpio_init(1U,cfg_port_b);
    gpio_init(2U,cfg_port_c);
    gpio_init(3U,cfg_port_d);
    system_init(cfg_error_pin);
    timer1_init(SYSTEM_CLK, TIMER_TIMER0_PRESCALER);
    isr_init();
}

