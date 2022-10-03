

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "period.h"
#include "signal_out.h"
#include "input.h"
#include "sine.h"
#include "analog.h"

typedef struct output {
    uint8_t set;
    pin_t pin;
}output_t;

uint16_t g_frequency = SIGNAL_DEFAULT_FREQ;
uint8_t g_phase = SIGNAL_DEFAULT_PHASE;
input_t gpio_in[NMB_OF_INPUTS] = {0u};
period_t loop_gpio_in[NMB_OF_INPUTS] = {0u};
output_t gpio_out[NMB_OF_OUTPUTS]={0u};
void isr_timer0_comp_a(void);
void app_init(void)
{
    for (uint8_t i = 0u; i < NMB_OF_INPUTS; i++)
    {
       gpio_in[i].pin  = cfg_pin_input[i];
       gpio_in[i].loop = &loop_gpio_in[i];
    }

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
       gpio_out[i].pin = cfg_pin_output[i];
    }

    signal_init();
    isr_register(isr_timer0_comp_a, Timer0_Comp_A);
    analog_init();
}


void app_main(void)
{
    for (uint8_t i = 0; i < NMB_OF_INPUTS; i++)
    {
        input_get(&gpio_in[i]);
    }

    if (gpio_in[0].state == 1u)
    {
        if (gpio_in[2].state == 0u)
        {
            g_frequency--;
        }
        else
        {

            g_frequency++;
        }
    }

    if (gpio_in[1].state == 1u)
    {
        if (gpio_in[3].state == 0u)
        {
            g_phase = g_phase - 1u;
        }
        else
        {
            g_phase = g_phase + 1u;
        }
        
        
    }

    if (g_phase <= 1u)
    {
        g_phase = 10u;
    }
    else if (g_phase >=180u)
    {
        g_phase = 90u;
    }
    else
    {
        /* code */
    }

    if (g_frequency <= 2u)
    {
        g_frequency = 2u;
    }
    else if (g_frequency >=100u)
    {
        g_frequency= 100u;
    }
    else
    {
        /* code */
    }

    signal_sine(g_frequency, SIGNAL_DEFAULT_PHASE, 3u);

}
double timer0_ofv_cnt;
void isr_timer0_comp_a(void)
{
    timer0_ofv_cnt++;
    double val = (analog_read(4) -512) / 512.0;

    if (timer0_ofv_cnt == 255)
    {
        timer0_ofv_cnt = 0u;
    }
    
    //uint16_t analog_ch1 = analog_read(4u);
    uart_cnt_transmit((uint8_t *)&timer0_ofv_cnt,4);
    

    //timer_set_compare(Timer0_Comp_A, timer0_get_ticks() + 10u);
}
