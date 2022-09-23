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

#include <avr/io.h>
//-------Defines-------

#define TIMER1_A_ISR_FREQ  2500u // Reocurrence of timer1_compA_isr
#define FIRST_ISR_OCURRENCE      15000u
//-------TYPES-------
uint16_t lut_period[NMB_OF_OUTPUTS];
uint16_t lut_delay[NMB_OF_OUTPUTS];


//-------Variables-------
uint8_t once;
uint32_t isr_period;
uint32_t timer_freq;
//-------Static Function Declaration-------

void signal_timer1_comp_a_isr(void);
void signal_timer1_comp_b_isr(void);
void signal_timer2_comp_a_isr(void);

static void set_isr_timing(void);
//-------Function Definition-------
uint8_t once;
void signal_init(void)
{

    isr_register(signal_timer1_comp_a_isr, Timer1_Comp_A);
    isr_register(signal_timer1_comp_b_isr, Timer1_Comp_B);
    //set_isr_timing();

}

static void set_isr_timing(void)
{
    timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    isr_period = timer_freq/TIMER1_A_ISR_FREQ;

    uint32_t cur_ticks = timer1_32_get_ticks();
    timer_set_compare(Timer1_Comp_A, cur_ticks + 15000 );
}


void signal_rectangle(uint16_t frequency, uint16_t phase, uint8_t nmb_of_channels)
{
    for (uint8_t i = 0u; i < nmb_of_channels; i++)
    {
        uint16_t local_phase_ticks = 360u/phase;
        lut_period[i] = TIMER1_A_ISR_FREQ/frequency;
        lut_delay[i] = (lut_period[i]/(local_phase_ticks/2u))*i;
    }

    if (once == 0u)
    {
        timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        isr_period = timer_freq/TIMER1_A_ISR_FREQ;

        uint32_t cur_ticks = timer1_32_get_ticks();
        timer_set_compare(Timer1_Comp_A, cur_ticks + 15000 );
    }
    once = 1u;
}

uint8_t signal_state[NMB_OF_OUTPUTS];
uint32_t isr_count[NMB_OF_OUTPUTS];

void signal_timer1_comp_a_isr(void)
{
    PORTB|=0x01U;
    uint32_t cur_ticks = timer1_get_ticks();
    uint8_t shoot[NMB_OF_OUTPUTS] = {0u};

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        if (signal_state[i] == 0)
        {
            isr_count[i]++;
        }
        
        if (isr_count[i] == (lut_delay[i] + lut_period[i]))
        {
            shoot[i] = 1u;

        }

        if (shoot[i] == 1u)
        {
            gpio_write(signal_out[i].port,signal_out[i].bit, 1u);
            signal_state[i]= 1u;
        }
    }

    timer_set_compare(Timer1_Comp_A ,cur_ticks + isr_period);
    timer_set_compare(Timer1_Comp_B, cur_ticks + isr_period/2u );
PORTB&=0xfeu;
}

void signal_timer1_comp_b_isr(void)
{
    uint8_t shoot[NMB_OF_OUTPUTS] = {0u};

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        if (signal_state[i] == 1)
        {
            isr_count[i]--;
        }

        if (isr_count[i] == lut_delay[i])
        {
            shoot[i] = 1u;
        }

        if (shoot[i] == 1u)
        {
           gpio_write(signal_out[i].port,signal_out[i].bit, 0u);

            signal_state[i]= 0u;
        }
    }
}
