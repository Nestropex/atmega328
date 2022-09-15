

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "period.h"

#define CHANNEL_1 0u
#define VALID_ONCE 1u
#define TOGGLE_DIR 1u


#define MINIMUM_TICKS_CH2 
#define NMB_REVOLUTION_CH2 300u
#define STEP_MODE     8u // Driver in Full Step = 1, 1/2=2, 1/8=8
#define STEPS_PER_REV 200ul*STEP_MODE

#define SYSTEM_CLK_SCALED_MICRO SYSTEM_CLK/1000000ul
#define OUT_ONTIME_TICKS        ((OUT_ONTIME_MICROS*SYSTEM_CLK_SCALED_MICRO)/TIMER_TIMER1_PRESCALER)



typedef struct app_input{
        uint16_t  ONtime;
        uint8_t   state;
        pin_t     pin;
        period_t *loop;
}app_input_t;


static void isr_timer_1_comp_a(void);
static void isr_timer_1_comp_b(void);




void app_init(void)
{
    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    isr_register(isr_timer_1_comp_b, Timer1_Comp_B);

}


void app_main(void)
{
    //gpio_toggle(1,0);

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