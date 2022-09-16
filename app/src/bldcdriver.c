

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "period.h"
#include "input.h"


typedef struct output {
    uint8_t set;
    pin_t pin;
}output_t;

extern period_t period_1_loop;
uint16_t next_event;
input_t gpio_in[NMB_OF_INPUTS] = {0u};
period_t loop_gpio_in[NMB_OF_INPUTS] = {0u};
output_t gpio_out[NMB_OF_OUTPUTS]={0u};

static void isr_timer_1_comp_a(void);
static void isr_timer_1_comp_b(void);
void signal_frequency(uint16_t frequency, uint16_t phase);
void app_init(void)
{
    for (uint8_t i = 0u; i < NMB_OF_INPUTS; i++)
    {
       gpio_in[i].pin  = cfg_pin_input[i];
       gpio_in[i].loop = &loop_gpio_in[i];
    }

    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
       gpio_out[i].pin = cfg_pin_input[i];
    }

    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    isr_register(isr_timer_1_comp_b, Timer1_Comp_B);
    signal_frequency(200u, 0u);
}


void app_main(void)
{
    

    for (uint8_t i = 0; i < NMB_OF_INPUTS; i++)
    {
        input_get(&gpio_in[i]);
    }
    
    if ((period_1_loop.cnt % 2u)== 0u)
    {
        for (uint8_t i = 0u; i < NMB_OF_INPUTS; i++)
        {
          /*  uart_str_transmit("input: ");
            uart_nmb_transmit(i,10u);
            uart_str_transmit("\n");
            uart_nmb_transmit(gpio_in[i].ONtime,10u); */
        }
    }
}

/**
 * @brief CH1 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_a(void)
{
    
    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        gpio_toggle(cfg_pin_output[i].port,cfg_pin_output[i].bit);
    }
    uint16_t cur_ticks = timer1_get_ticks();
    timer_set_compare(Timer1_Comp_A, cur_ticks + next_event);

}

/**
 * @brief CH2 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_b(void)
{

}

void signal_frequency(uint16_t frequency, uint16_t phase)
{
    if (frequency != 0u)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
         next_event = timer_freq/frequency;
        uint16_t cur_ticks = timer1_get_ticks();
        timer_set_compare(Timer1_Comp_A, cur_ticks + next_event);

        uart_str_transmit("timer_freq");
        uart_nmb_transmit(timer_freq,10u);

        uart_str_transmit("next_event");
        uart_nmb_transmit(next_event,10u);

        uart_str_transmit("cur_ticks");
        uart_nmb_transmit(cur_ticks,10u);

        


    }
}