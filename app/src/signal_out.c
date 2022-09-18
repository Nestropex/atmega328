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
static void signal_register(signal_t *channel);
//-------Function Definition-------

void signal_init(signal_t *channel)
{
    timer1_init(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    timer2_init(SYSTEM_CLK, TIMER_TIMER2_PRESCALER);
    isr_register(signal_timer1_comp_a_isr, Timer1_Comp_A);
    isr_register(signal_timer1_comp_b_isr, Timer1_Comp_B);
    isr_register(signal_timer2_comp_a_isr, Timer2_Comp_A);

    signal_register(channel);
}

static void signal_register(signal_t *channel)
{
    for (uint8_t i = 0; i < NMB_OF_OUTPUTS; i++)
    {
        channel_isr[i] = &channel[i];
    }
    
}

void signal_frequency(uint16_t frequency, uint16_t phase)
{
    if (frequency != 0u)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        period_ticks = timer_freq/(2u*frequency);
        
        phase_ticks = 360u/phase;

        delay_ticks = period_ticks/(phase_ticks/2u);

        if (once == 0u)
        {
            uint32_t cur_ticks = timer1_32_get_ticks();
            // Interrupts will occure with a rate 6 times faster than frequency
            timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);
            timer_set_compare(Timer1_Comp_B, cur_ticks + period_ticks + delay_ticks);
            cur_ticks = timer2_32_get_ticks();
            timer_set_compare(Timer2_Comp_A, cur_ticks + period_ticks + 2*delay_ticks);
        }
        
        once = 1u;
    }
}

void signal_rectangle(signal_t *channel)
{
    if (channel != NULL_PTR)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        channel->period_ticks = timer_freq/(2u*channel->frequency);
        
        uint16_t local_phase_ticks = 360u/channel->phase;

        channel->delay_ticks = channel->period_ticks/(local_phase_ticks/2u);

        if (once == 0u)
        {
            uint32_t cur_ticks = timer1_32_get_ticks();
            // Interrupts will occure with a rate 6 times faster than frequency
            
            timer_set_compare(Timer1_Comp_B, cur_ticks + channel->period_ticks + channel->delay_ticks);
            cur_ticks = timer2_32_get_ticks();
            timer_set_compare(Timer2_Comp_A, cur_ticks + channel->period_ticks + 2*channel->delay_ticks);
        }
        
        once = 1u;
    }
}


static uint8_t isr_state;

void signal_timer1_comp_a_isr(void)
{
    uint32_t cur_ticks = timer1_32_get_ticks();
    gpio_toggle(cfg_pin_output[0].port,cfg_pin_output[0].bit);
    timer_set_compare(Timer1_Comp_A, cur_ticks + 1000);
}

void signal_timer1_comp_b_isr(void)
{
    if (isr_state == 0u)
    {
        gpio_write(cfg_pin_output[1].port,cfg_pin_output[1].bit,1u);
    }
    else
    {
        gpio_write(cfg_pin_output[1].port,cfg_pin_output[1].bit,0u);
    }

    uint32_t cur_ticks = timer1_32_get_ticks();
}

void signal_timer2_comp_a_isr(void)
{
    if (isr_state == 0u)
    {
        gpio_write(cfg_pin_output[2].port,cfg_pin_output[2].bit,1u);
        isr_state = 1u;
    }
    else
    {
        gpio_write(cfg_pin_output[2].port,cfg_pin_output[2].bit,0u);
        isr_state = 0u;
    }

    uint32_t cur_ticks = timer2_32_get_ticks();
}