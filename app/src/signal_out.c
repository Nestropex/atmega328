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
#include "sine.h"
#include "signal_out.h"

#include <avr/io.h>
//-------Defines-------

#define TIMER1_A_ISR_FREQ        40000u // Reocurrence of timer1_compA_isr
#define FIRST_ISR_OCURRENCE      15000u
//-------TYPES-------
uint16_t lut_period[NMB_OF_OUTPUTS];
uint16_t lut_delay[NMB_OF_OUTPUTS];
uint32_t isr_count[NMB_OF_OUTPUTS];
uint8_t sine_index[NMB_OF_OUTPUTS];

//-------Variables-------
uint8_t once;
uint32_t isr_period;
uint32_t timer_freq;
//-------Static Function Declaration-------

void signal_timer1_comp_a_isr(void);

static void set_isr_timing(void);
//-------Function Definition-------
uint8_t once;
void signal_init(void)
{

    isr_register(signal_timer1_comp_a_isr, Timer1_Comp_A);

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

void signal_sine(uint16_t frequency, uint16_t phase, uint8_t nmb_of_channels)
{
    for (uint8_t i = 0u; i < nmb_of_channels; i++)
    {
        uint16_t local_phase_ticks = (360u/phase)/2u;
        lut_period[i] = TIMER1_A_ISR_FREQ/(frequency*255u);
        lut_delay[i] = (TIMER1_A_ISR_FREQ/(local_phase_ticks*frequency))*i;
    }

    if (once == 0u)
    {
        timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        isr_period = timer_freq/TIMER1_A_ISR_FREQ;

        uint32_t cur_ticks = timer1_32_get_ticks();
        timer_set_compare(Timer1_Comp_A, cur_ticks + 15000 );
    }
    once = 1u;

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        uart_nmb_transmit(sine_index[i],10u);
    }
}

uint8_t g_cur_ticks;
void signal_timer1_comp_a_isr(void)
{
    PORTB|=0x01U;
    uint32_t cur_ticks = timer1_get_ticks();
    timer_set_compare(Timer1_Comp_A ,cur_ticks + isr_period);

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
            isr_count[i]++;
        
        if (isr_count[i] == (lut_period[i] + lut_delay[i]))
        {
            if (i== 0u)
            {
                g_cur_ticks = timer2_get_ticks();
            }
            sine_index[i]++;

            if (sine_wave[sine_index[i]] <= g_cur_ticks)
            {
                gpio_write(signal_out[i].port,signal_out[i].bit, 1u);
                isr_count[i] = lut_delay[i];
            }
            else
            {
                gpio_write(signal_out[i].port,signal_out[i].bit, 0u);
                isr_count[i] = lut_delay[i];
            }
        }
    }

PORTB&=0xfeu;
}
