// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "cfg.h"
#include "isr.h"
#include "timer.h"
#include "gpio.h"
#include "signal_out.h"


//-------Defines-------



//-------TYPES-------
typedef struct signal {
    uint8_t state;
    void (* isr);
}signal_t;


//-------Variables-------
uint8_t once;
uint8_t state_high;
uint8_t state_low;
uint16_t phase_ticks;
uint16_t delay_ticks;
uint16_t period_ticks;

//-------Static Function Declaration-------

void period_timer_1_comp_a_isr(void);

//-------Function Definition-------

void signal_init(void)
{
    timer1_init(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    isr_register(period_timer_1_comp_a_isr, Timer1_Comp_A);
}

void signal_frequency(uint16_t frequency, uint16_t phase)
{
    if (frequency != 0u)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        period_ticks = timer_freq/(2u*frequency);
        uint16_t cur_ticks = timer1_get_ticks();

        if (once == 0u)
        {
            // Interrupts will occure with a rate 6 times faster than frequency
            timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);
        }
        
        once = 1u;


        phase_ticks = 360u/phase;

        delay_ticks = period_ticks/(phase_ticks/2);
    }
}

void period_timer_1_comp_a_isr(void)
{
    gpio_toggle(cfg_pin_output[0].port,cfg_pin_output[0].bit);
    uint16_t cur_ticks = timer1_get_ticks();
    timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);
}