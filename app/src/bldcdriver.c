

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "period.h"
#include "input.h"

extern period_t period_1_loop;
app_input_t button1;
app_input_t button2;
app_input_t switch1;
app_input_t switch2;

period_t loop_button1 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_button2 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_switch1 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_switch2 = {0ul,0ul,0u,0u,0u,0u,0u};
static void isr_timer_1_comp_a(void);
static void isr_timer_1_comp_b(void);




void app_init(void)
{
    button1.pin = cfg_pin_input.button1;
    button1.loop = &loop_button1;
    button2.pin = cfg_pin_input.button2;
    button2.loop = &loop_button2;
    switch1.pin = cfg_pin_input.switch1;
    switch1.loop = &loop_switch1;
    switch2.pin = cfg_pin_input.switch2;
    switch2.loop = &loop_switch2;

    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    isr_register(isr_timer_1_comp_b, Timer1_Comp_B);

}


void app_main(void)
{
    input_get(&button1);
    input_get(&button2);
    input_get(&switch1);
    input_get(&switch2);

    gpio_toggle(cfg_pin_output.phase1.port,cfg_pin_output.phase1.bit);
    gpio_toggle(cfg_pin_output.phase2.port,cfg_pin_output.phase2.bit);
    gpio_toggle(cfg_pin_output.phase3.port,cfg_pin_output.phase3.bit);

    if ((period_1_loop.cnt % 2u)== 0u)
    {
        uart_str_transmit("button1: ");
        uart_nmb_transmit(button1.ONtime,10u);
        uart_str_transmit("button2: ");
        uart_nmb_transmit(button2.ONtime,10u);

        uart_str_transmit("switch1: ");
        uart_nmb_transmit(switch1.ONtime,10u);
        uart_str_transmit("switch2: ");
        uart_nmb_transmit(switch2.ONtime,10u);
        uart_str_transmit("period_1_loop: ");
        uart_nmb_transmit(period_1_loop.cnt,10u);
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