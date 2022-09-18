
#include "datatypes.h"
#include "system.h"
#include "cfg.h"
#include "watchdog.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "gpio.h"
#include "period.h"
#include "timer_32bit.h"
#include "app.h"



period_t loop_main;
period_t loop_1;
period_t loop_2;

static void init(void);

// Main function must be the first one in the file 
int main(void)
{
    init();
    app_init();
    loop_main.time_config = LOOP_MAIN_TIME_MILLIS;
    loop_1.time_config = LOOP_1_TIME_MILLIS;
    loop_2.time_config = LOOP_2_TIME_MILLIS;



    while(1)
    {  
        watchdog_reset();
        period_control(&loop_main);
 
        if(loop_main.execute_flag == 1u)
        {   
            period_control(&loop_1);
            if(loop_1.execute_flag == 1u)
            {                
                app_main();          
            } 

            period_control(&loop_2);
            if(loop_2.execute_flag == 1u)
            {
                system_error_update();
                uart_str_transmit("heartbeat \n");
            }

        }
    }

    return 0;
}

static void init(void)
{  
    system_init(cfg_error_pin);
    uart_init(SYSTEM_CLK,UART_BAUDRATE);
    watchdog_init(1u);
    gpio_init(1U,cfg_port_b);
    gpio_init(2U,cfg_port_c);
    gpio_init(3U,cfg_port_d);
    period_init();
    isr_init();
}

