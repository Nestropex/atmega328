
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "timer.h"
#include "isr.h"
#include "period.h"

uint32_t timer0_32 = 0x0ul;
void isr_timer_0_ovf(void);

void period_init(void)
{
    isr_register(isr_timer_0_ovf, Timer0_OVF);
}

void period_control(period_t  *loop)
{
    if (loop != NULL_PTR)
    {
        period_t *temp_loop = loop;
        temp_loop->cur_ticks = timer0_get_ticks_32();
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

void isr_timer_0_ovf(void)
{
    timer0_32 = timer0_32 + 0x00000100ul;
}

uint32_t timer0_get_ticks_32(void)
{
    return  (timer0_32 | timer0_get_ticks());
}