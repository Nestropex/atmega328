

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

input_t gpio_in[NMB_OF_INPUTS] = {0u};
period_t loop_gpio_in[NMB_OF_INPUTS] = {0u};
output_t gpio_out[NMB_OF_OUTPUTS]={0u};

static void isr_timer_1_comp_a(void);
static void isr_timer_1_comp_b(void);

void app_init(void)
{
    for (uint8_t i = 0u; i < NMB_OF_INPUTS; i++)
    {
       gpio_in[i].pin  = cfg_pin_input[i];
       gpio_in[i].loop = &loop_gpio_in[i];
       gpio_out[i].pin = cfg_pin_input[i];
    }

    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    isr_register(isr_timer_1_comp_b, Timer1_Comp_B);
}


void app_main(void)
{
    for (uint8_t i = 0u; i < NMB_OF_OUTPUTS; i++)
    {
        input_get(&gpio_in[i]);
        gpio_toggle(cfg_pin_output[i].port,cfg_pin_output[i].bit);
    }


    if ((period_1_loop.cnt % 2u)== 0u)
    {
        for (uint8_t i = 0; i < NMB_OF_INPUTS; i++)
        {
            uart_str_transmit("input: ");
            uart_nmb_transmit(i,10u);
            uart_str_transmit("\n");
            uart_nmb_transmit(gpio_in[i].ONtime,10u);
        }
    }
}



 



/**
 * @brief CH1 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_a(void)
{


}

/**
 * @brief CH2 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_b(void)
{

}