
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "loop.h"


void loop_control(loop_t  *period)
{
    if (period != NULL_PTR)
    {
        period->cnt++;
        period->cur_ticks = timer1_get_ticks();
        period->diff = period->cur_ticks - period->last_ticks;
  

        uint32_t clk_scaled = SYSTEM_CLK/1000ul;
        uint32_t ticks_config = (period->time_config*clk_scaled)/TIMER_TIMER1_PRESCALER;

        if (period->diff >= ticks_config)
        {
            period->execute_flag = 1u;
            period->time = (uint32_t)((period->diff*TIMER_TIMER1_PRESCALER * 1000u)/SYSTEM_CLK);
            period->last_ticks = period->cur_ticks;

 
        }
        else
        {
            period->execute_flag = 0u;
        }
        
        
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

