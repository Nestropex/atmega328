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
uint16_t pwm_cnt;
//-------Static Function Declaration-------

void signal_timer1_ovf_isr(void);
static void set_isr_timing(void);
//-------Function Definition-------
uint8_t once;
void signal_init(void)
{
 
    isr_register(signal_timer1_ovf_isr, Timer1_OVF);
}

static void set_isr_timing(void)
{
    timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
    isr_period = timer_freq/TIMER1_A_ISR_FREQ;

    uint32_t cur_ticks = timer1_32_get_ticks();
    timer_set_compare(Timer1_Comp_A, cur_ticks  );
}
uint16_t pwm_hi;
uint16_t pwm_lo;

#define DC_MAX 100u
void signal_pwm(uint16_t frequency, uint8_t dc)
{
    pwm_hi = timer_freq/(frequency*255u);

    if (dc> DC_MAX)
    {
        dc = DC_MAX;
    }

    pwm_lo = (pwm_hi*dc)/DC_MAX;
}



uint32_t isr_ticks;
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

        uint32_t cur_ticks = timer1_get_ticks();
        timer_set_compare(Timer1_Comp_A, cur_ticks );
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

        uint32_t cur_ticks = timer1_get_ticks();
        timer_set_compare(Timer1_Comp_A, cur_ticks );
        timer_set_compare(Timer2_Comp_B, cur_ticks );
    }
    once = 1u;
    uint32_t calc = frequency*255u;
    isr_ticks = (timer_freq/((calc*255u))) + 1u;
}

uint8_t g_cur_ticks;
uint32_t ovf_count;

void signal_timer1_ovf_isr(void)
{
    ovf_count++;
    pwm_cnt++;

    if (pwm_cnt >= pwm_hi)
    {
        PWM_PORT |= PWM_PIN;
        pwm_cnt = 0u;
    }

    if (pwm_cnt >= pwm_lo)
    {
        PWM_PORT&= (~PWM_PIN); 
    }
    
    TCNT0  = 0u;
    TCNT1L = 0u;
    TCNT1H = 0u;
    TCNT2  = 0u;

    if (ovf_count >= isr_ticks)
    {
        sine_index[0]++;
        ovf_count = 0u;
    }

    OCR0A = sine_wave[(uint8_t)(sine_index[0])];
    OCR0B = sine_wave[(uint8_t)(sine_index[0])];
    OCR1A = sine_wave[sine_index[0]];
    OCR1B = sine_wave[(uint8_t)(sine_index[0] - 42u)];
    OCR2A = sine_wave[(uint8_t)(sine_index[0] - 84u)];
    OCR2B = sine_wave[(uint8_t)(sine_index[0])];
}
