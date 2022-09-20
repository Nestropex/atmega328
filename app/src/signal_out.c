// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "cfg.h"
#include "isr.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "timer_32bit.h"
#include "signal_out.h"

//-------Defines-------



//-------TYPES-------



//-------Variables-------
uint8_t once;
uint32_t phase_ticks;
uint32_t delay_ticks;
uint32_t period_ticks;
static signal_t *channel_isr[NMB_OF_OUTPUTS];
//-------Static Function Declaration-------

void signal_timer1_comp_a_isr(void);
void signal_timer1_comp_b_isr(void);
void signal_timer2_comp_a_isr(void);
static void signal_register(signal_t *channel, uint8_t nmb_of_channels);
//-------Function Definition-------

void signal_init(signal_t *channel, uint8_t nmb_of_channels)
{

    isr_register(signal_timer1_comp_a_isr, Timer1_Comp_A);
    isr_register(signal_timer1_comp_b_isr, Timer1_Comp_B);

    signal_register(channel, nmb_of_channels);
}

static void signal_register(signal_t *channel, uint8_t nmb_of_channels)
{
    for (uint8_t i = 0; i < nmb_of_channels; i++)
    {
        channel_isr[i] = &channel[i];
    }
    
}

void signal_rectangle(signal_t *channel, uint8_t nmb_of_channels)
{
    if (channel != NULL_PTR)
    {
        for (uint8_t i = 0u; i < nmb_of_channels; i++)
        {
            uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
            channel[i].period_ticks = timer_freq/(2u*(*(channel[i].frequency)));
        
            uint16_t local_phase_ticks = 360u/(*(channel[i].phase));

            channel[i].delay_ticks = channel[i].period_ticks/(local_phase_ticks/2u);
        }
        


        if (once == 0u)
        {
            uint32_t cur_ticks = timer1_32_get_ticks();
            // Interrupts will occure with a rate 6 times faster than frequency
            channel[0].next_hi_event = cur_ticks + 2000u;
            timer_set_compare(Timer1_Comp_A, cur_ticks + 1000);
        }
        
        once = 1u;
    }
}

static uint8_t state[NMB_OF_OUTPUTS];
void signal_timer1_comp_a_isr(void)
{
    uint32_t cur_ticks = timer1_32_get_ticks();

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        if (((channel_isr[0]->next_hi_event + channel_isr[0]->delay_ticks * i) <= cur_ticks) && (state[i] == 0u))
        {
            gpio_write(channel_isr[i]->pin_out.port,channel_isr[i]->pin_out.bit, 1u);
            channel_isr[i]->next_low_event = cur_ticks + channel_isr[i]->period_ticks;
            state[i] = 1u;
        }
    }

    timer_set_compare(Timer1_Comp_A ,cur_ticks + 50u);
    timer_set_compare(Timer1_Comp_B, cur_ticks + 25u);

}

void signal_timer1_comp_b_isr(void)
{
    uint32_t cur_ticks = timer1_32_get_ticks();
    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        if (((channel_isr[0]->next_low_event + channel_isr[0]->delay_ticks*i) <= cur_ticks) && (state[i] == 1u))
        {
            gpio_write(channel_isr[i]->pin_out.port,channel_isr[i]->pin_out.bit, 0u);
            channel_isr[i]->next_hi_event  = cur_ticks + channel_isr[i]->period_ticks;
            state[i] = 0u;
        }
    }

}
