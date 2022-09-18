

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "period.h"
#include "signal_out.h"
#include "input.h"

typedef struct output {
    uint8_t set;
    pin_t pin;
}output_t;

signal_t phase[NMB_OF_OUTPUTS];
uint16_t g_frequency = 1000u;
uint16_t g_phase = 60u;
input_t gpio_in[NMB_OF_INPUTS] = {0u};
period_t loop_gpio_in[NMB_OF_INPUTS] = {0u};
output_t gpio_out[NMB_OF_OUTPUTS]={0u};

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

    phase[0u].frequency = SIGNAL_DEFAULT_FREQ;
    phase[0u].phase = 60u;
    phase[0u].pin_out = cfg_pin_output[0u];

    phase[1u].frequency = SIGNAL_DEFAULT_FREQ;
    phase[1u].phase = 60u;
    phase[1u].pin_out = cfg_pin_output[1u];

    phase[2u].frequency = SIGNAL_DEFAULT_FREQ;
    phase[2u].phase = 60u;
    phase[2u].pin_out = cfg_pin_output[2u];


    signal_init(&phase[0u]);
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
            g_frequency = g_frequency - 10u;
        }
        else
        {
            g_frequency = g_frequency + 10u;
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

    if (g_phase <= 10u)
    {
        g_phase = 10u;
    }
    else if (g_phase >=90u)
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
    else if (g_frequency >=1200u)
    {
        g_frequency= 1200u;
    }
    else
    {
        /* code */
    }

    signal_rectangle(&phase[0u]);
    signal_rectangle(&phase[1u]);
    signal_rectangle(&phase[2u]);
    
}


