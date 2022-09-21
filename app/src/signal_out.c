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



//-------TYPES-------
uint16_t lut_period[NMB_OF_OUTPUTS];
uint16_t lut_delay[NMB_OF_OUTPUTS];


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
uint32_t timer_freq;
uint32_t isr_period;
void signal_rectangle(signal_t *channel, uint8_t nmb_of_channels)
{

    
    if (channel != NULL_PTR)
    {
        for (uint8_t i = 0u; i < nmb_of_channels; i++)
        {
             timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
            channel[i].period_ticks = timer_freq/(2u*(*(channel[i].frequency)));
        
            uint16_t local_phase_ticks = 360u/(*(channel[i].phase));

            channel[i].delay_ticks = channel[i].period_ticks/(local_phase_ticks/2u);

            lut_period[i] = TIMER_TIMER1_A_ISR_FREQ/(*(channel[i].frequency));
            lut_delay[i] = (lut_period[i]/(local_phase_ticks/2u))*i;
        }
        


        if (once == 0u)
        {
            uint32_t cur_ticks = timer1_32_get_ticks();
            isr_period = timer_freq/TIMER_TIMER1_A_ISR_FREQ;
            // Interrupts will occure with a rate 6 times faster than frequency
            channel[0].next_hi_event = cur_ticks + 2000u;
            timer_set_compare(Timer1_Comp_A, cur_ticks + isr_period );
        }
        
        once = 1u;
    }
}

uint8_t signal_state[NMB_OF_OUTPUTS];
uint32_t isr_count[NMB_OF_OUTPUTS];


void signal_timer1_comp_a_isr(void)
{
    PORTB|=0x01U;
    uint32_t cur_ticks = timer1_get_ticks();
    uint8_t shoot[NMB_OF_OUTPUTS] = {0u};


    for (uint8_t i = 0u; i < 3; i++)
    {
        if (signal_state[i] == 0)
        {
            isr_count[i]++;
        }
        
        
        if (isr_count[0] == 125u)
        {
            shoot[0] = 1u;

        }

        if (isr_count[1] == (lut_delay[1] + lut_period[1]))
        {
            shoot[1] = 1u;

        }

        if (isr_count[2] == 207u)
        {
            shoot[2] = 1u;

        }

        
        if (shoot[i] == 1u)
        {
            gpio_write(channel_isr[i]->pin_out.port,channel_isr[i]->pin_out.bit, 1u);
            signal_state[i]= 1u;
        }
    }

    timer_set_compare(Timer1_Comp_A ,cur_ticks + isr_period);
    timer_set_compare(Timer1_Comp_B, cur_ticks + isr_period/2u );
PORTB&=0xfeu;
}

void signal_timer1_comp_b_isr(void)
{
    uint32_t cur_ticks = timer1_get_ticks();
    uint8_t shoot[NMB_OF_OUTPUTS] = {0u};

    for (uint8_t i = 0u; i < 3; i++)
    {
        if (signal_state[i] == 1)
        {
            isr_count[i]--;
        }

        if (isr_count[0] == 0u)
        {
            shoot[0] = 1u;
     

        }

        if (isr_count[1] == 41u)
        {
            shoot[1] = 1u;

        }

        if (isr_count[2] == 82u)
        {
            shoot[2] = 1u;

        }

        if (shoot[i] == 1u)
        {
           gpio_write(channel_isr[i]->pin_out.port,channel_isr[i]->pin_out.bit, 0u);

            signal_state[i]= 0u;
        }


    }

}
