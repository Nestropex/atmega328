
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "loop.h"


void loop_control(loop_t  *period)
{
    if (period != NULL_PTR)
    {
        loop_t *temp_period = period;
        temp_period->cnt++;
        temp_period->cur_ticks = timer1_get_ticks();
        temp_period->diff = temp_period->cur_ticks - temp_period->last_ticks;
  

        uint32_t clk_scaled = SYSTEM_CLK/1000ul;
        uint32_t ticks_config = (temp_period->time_config*clk_scaled)/TIMER_TIMER1_PRESCALER;

    	uint32_t compute = period->diff;
        compute = compute *TIMER_TIMER1_PRESCALER;
        if (temp_period->diff >= ticks_config)
        {
            temp_period->execute_flag = 1u;
            temp_period->time = (uint32_t)((compute)/clk_scaled);
            temp_period->last_ticks = temp_period->cur_ticks;
        }
        else
        {
            temp_period->execute_flag = 0u;
        }
        
        *period = *temp_period;
    }
    else
    {
        ERROR_HANDLER("loop_time_update");
    }
}

void loop_print(loop_t *period, uint8_t *str)
{
    uart_str_transmit(str);
    uart_str_transmit("time: ");
    uart_nmb_transmit(period->time, 10u);
    uart_str_transmit("cnt: ");
    uart_nmb_transmit(period->cnt, 10u);
    uart_str_transmit("diff ");
    uart_nmb_transmit(period->diff,10u);
    uart_str_transmit("cur ");
    uart_nmb_transmit(period->cur_ticks,10u);
    uart_str_transmit("last ");
    uart_nmb_transmit(period->last_ticks,10u);
}

