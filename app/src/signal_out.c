// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "cfg.h"
#include "isr.h"
#include "timer.h"
#include "gpio.h"
#include "timer_32bit.h"
#include "signal_out.h"


//-------Defines-------



//-------TYPES-------
typedef struct signal {
    uint8_t state;
    void (* isr);
}signal_t;


//-------Variables-------
uint8_t once;
uint32_t phase_ticks;
uint32_t delay_ticks;
uint32_t period_ticks;

//-------Static Function Declaration-------

void signal_timer1_comp_a_isr(void);
void signal_timer1_comp_b_isr(void);
void signal_timer2_comp_a_isr(void);

//-------Function Definition-------

void signal_init(void)
{
    timer1_init(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    timer2_init(SYSTEM_CLK, TIMER_TIMER2_PRESCALER);
    isr_register(signal_timer1_comp_a_isr, Timer1_Comp_A);
    isr_register(signal_timer1_comp_b_isr, Timer1_Comp_B);
    isr_register(signal_timer2_comp_a_isr, Timer2_Comp_A);
}

void signal_frequency(uint16_t frequency, uint16_t phase)
{
    if (frequency != 0u)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        period_ticks = timer_freq/(2u*frequency);
        

        if (once == 0u)
        {
            uint32_t cur_ticks = timer1_32_get_ticks();
            // Interrupts will occure with a rate 6 times faster than frequency
            timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);
            timer_set_compare(Timer1_Comp_B, cur_ticks + period_ticks);
            cur_ticks = timer2_32_get_ticks();
            timer_set_compare(Timer2_Comp_A, cur_ticks + period_ticks);
        }
        
        once = 1u;


        phase_ticks = 360u/phase;

        delay_ticks = period_ticks/(phase_ticks/2);
    }
}
static uint8_t isr_state;

void signal_timer1_comp_a_isr(void)
{
    if (isr_state == 0u)
    {
        gpio_write(cfg_pin_output[0].port,cfg_pin_output[0].bit,1u);
    }
    else
    {
        gpio_write(cfg_pin_output[0].port,cfg_pin_output[0].bit,0u);
    }

    uint32_t cur_ticks = timer1_32_get_ticks();
    timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);
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
    timer_set_compare(Timer1_Comp_B, cur_ticks + period_ticks);
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
    timer_set_compare(Timer2_Comp_A, cur_ticks + period_ticks);
}