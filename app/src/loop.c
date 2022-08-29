
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "loop.h"


void loop_update(loop_t  *period)
{
    if (period != NULL_PTR)
    {
        period->cnt++;
        period->cur_ticks = timer1_get_ticks();
        period->diff = period->cur_ticks - period->last_ticks;
        period->last_ticks = period->cur_ticks;
        
        period->time = (uint32_t)((period->diff*TIMER_TIMER1_PRESCALER * 1000u)/SYSTEM_CLK);
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
    uart_str_transmit(str);
    uart_str_transmit("cnt: ");
    uart_nmb_transmit(period->cnt, 10u);
    uart_str_transmit("\n");
}

void loop_time_elapsed(loop_t *period)
{
  
    period->cur_ticks = timer1_get_ticks();
    period->diff = period->cur_ticks - period->last_ticks;

    uint32_t clk_scaled = SYSTEM_CLK/1000ul;
    uint32_t ticks_config = (period->time_config*clk_scaled)/TIMER_TIMER1_PRESCALER;
    
    if (period != NULL_PTR)
    {
        if (period->diff >= ticks_config)
        {
            period->execute_flag = 1u;
        }
        else
        {
            period->execute_flag = 0u;
        }
    }
    else
    {
        ERROR_HANDLER("ERROR loop_time_elapsed");
    }
    
    
}