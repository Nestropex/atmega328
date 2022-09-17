

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
uint16_t period_ticks;
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
    signal_frequency(1000u,60u);
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
uint8_t state_high;
uint8_t state_low;
uint16_t phase_ticks;
uint16_t delay_ticks;
/**
 * @brief CH1 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_a(void)
{
    uint16_t cur_ticks = timer1_get_ticks();
    uint16_t phase_1_toggle_ticks;
    switch (state_high)
    {
    case 0u:
        gpio_write(cfg_pin_output[0].port,cfg_pin_output[0].bit,1u);
        state_high = 1u;
        timer_set_compare(Timer1_Comp_A, cur_ticks + delay_ticks);
        timer_set_compare(Timer1_Comp_B, cur_ticks + (period_ticks));
        break;
    case 1u:
        gpio_write(cfg_pin_output[1].port,cfg_pin_output[1].bit,1u);
        state_high = 2u;
        timer_set_compare(Timer1_Comp_A, cur_ticks + delay_ticks);
        break;
    case 2u:
        gpio_write(cfg_pin_output[2].port,cfg_pin_output[2].bit,1u);
        state_high = 0u;
        break;
    
    default:
        break;
    }
    uart_str_transmit("isr_a ");
    
    

}

/**
 * @brief CH2 step signal pin is toggled on every interrupt.
 *        Sets also next timer interrupt event
 */
static void isr_timer_1_comp_b(void)
{
    uint16_t cur_ticks = timer1_get_ticks();
    uint16_t phase_1_toggle_ticks;
    switch (state_low)
    {
        case 0u:
            gpio_write(cfg_pin_output[0].port,cfg_pin_output[0].bit,0u);
            state_low = 1u;
            timer_set_compare(Timer1_Comp_B, cur_ticks + delay_ticks);
            timer_set_compare(Timer1_Comp_A, cur_ticks + (period_ticks));
            break;
        case 1u:
            gpio_write(cfg_pin_output[1].port,cfg_pin_output[1].bit,0u);
            state_low = 2u;
            timer_set_compare(Timer1_Comp_B, cur_ticks + delay_ticks);
            break;
        case 2u:
            gpio_write(cfg_pin_output[2].port,cfg_pin_output[2].bit,0u);
            state_low = 0u;
            break;
        
        default:
            break;
    }
    
    uart_str_transmit("isr_b ");
    
}

void signal_frequency(uint16_t frequency, uint16_t phase)
{
    if (frequency != 0u)
    {
        uint32_t timer_freq = timer_get_frequency(SYSTEM_CLK, TIMER_TIMER1_PRESCALER);
        period_ticks = timer_freq/(2u*frequency);
        uint16_t cur_ticks = timer1_get_ticks();

        // Interrupts will occure with a rate 6 times faster than frequency
        timer_set_compare(Timer1_Comp_A, cur_ticks + period_ticks);

        phase_ticks = 360u/phase;

        delay_ticks = period_ticks/(phase_ticks/2);

        uart_str_transmit("delay_ticks ");
        uart_nmb_transmit(delay_ticks,10);
    }
}