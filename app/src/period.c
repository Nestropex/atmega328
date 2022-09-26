
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "timer_32bit.h"
#include "period.h"

void period_init(void)
{
    timer_init(Timer0,0x0u, SYSTEM_CLK, TIMER_TIMER0_PRESCALER);
    timer_init(Timer1,TIMER_1_MODE, SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    timer_init(Timer2,TIMER_2_MODE, SYSTEM_CLK, TIMER_TIMER2_PRESCALER);
    timer_32bit_init();
}

void period_control(period_t  *loop)
{
    if (loop != NULL_PTR)
    {
        period_t *temp_loop = loop;
        temp_loop->cur_ticks = timer0_32_get_ticks();
        temp_loop->diff = temp_loop->cur_ticks - temp_loop->last_ticks;
  

        uint32_t clk_scaled = SYSTEM_CLK/1000ul;
        uint32_t ticks_config = (temp_loop->time_config*clk_scaled)/TIMER_TIMER0_PRESCALER;

    	uint32_t compute = loop->diff;
        compute = compute * TIMER_TIMER0_PRESCALER;

        if (temp_loop->diff >= ticks_config)
        {
            temp_loop->cnt++;
            temp_loop->execute_flag = 1u;
            temp_loop->time = (uint32_t)((compute)/clk_scaled);
            temp_loop->last_ticks = temp_loop->cur_ticks;
        }
        else
        {
            temp_loop->execute_flag = 0u;
        }
        
        *loop = *temp_loop;
    }
    else
    {
        ERROR_HANDLER("ERROR period_control");
    }
}

void period_print(period_t *loop, uint8_t *str)
{
    if ((loop != NULL_PTR)&&(str != NULL_PTR))
    {
        uart_str_transmit(str);
        uart_str_transmit("time: ");
        uart_nmb_transmit(loop->time, 10u);
        uart_str_transmit("cnt: ");
        uart_nmb_transmit(loop->cnt, 10u);
        uart_str_transmit("diff ");
        uart_nmb_transmit(loop->diff,10u);
        uart_str_transmit("cur ");
        uart_nmb_transmit(loop->cur_ticks,10u);
        uart_str_transmit("last2 ");
        uart_nmb_transmit(loop->last_ticks,10u);
    }

}



