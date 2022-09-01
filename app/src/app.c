

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

typedef struct app_input{
        uint16_t  ONtime;
        uint8_t   state;
        pin_t     pin;
        period_t *loop;
}app_input_t;

period_t loop_button1 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_switch1 = {0ul,0ul,0u,0u,0u,0u,0u};


static void read_inputs(void);
static void isr_timer_1_comp_a(void);
static void get_input_ONtime(app_input_t *object);

app_input_t button1;
app_input_t switch1;
uint16_t comp_a;
void app_init(void)
{
    button1.pin = cfg_pin_input.button1;
    button1.loop = &loop_button1;
    switch1.pin = cfg_pin_input.switch1;
    switch1.loop = &loop_switch1;

    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    comp_a = 1000u ;
    timer_set_compare(Timer1_Comp_A, comp_a);
}


void app_main(void)
{
    get_input_ONtime(&button1);
    get_input_ONtime(&switch1);

    
    if ((button1.state == TOGGLE_DIR) && (button1.loop->cnt <= VALID_ONCE))
    {
        if (switch1.state == CHANNEL_1)
        {
            gpio_toggle(cfg_pin_output.dir1.port, cfg_pin_output.dir1.bit);
        }
        else
        {
            gpio_toggle(cfg_pin_output.dir2.port, cfg_pin_output.dir2.bit);
        }
    }
}

/**
 * @brief Updates input object with input state and the time it has been on
 * 
 * @param object pointer to input object as switch or button
 */
static void get_input_ONtime(app_input_t *object)
{
    if (object != NULL_PTR)
    {
        app_input_t temp_obj = *object;

        temp_obj.state = gpio_read(temp_obj.pin.port,temp_obj.pin.bit);

        if (temp_obj.state == 1u)
        {
            period_control(temp_obj.loop);
        }
        else 
        {
            temp_obj.loop->time = 0u;
            temp_obj.loop->cnt = 0u; 
        }

        temp_obj.ONtime =(uint16_t) temp_obj.loop->time * temp_obj.loop->cnt;
        *object = temp_obj;
    }
    

}
uint8_t state_comp_a;
static void isr_timer_1_comp_a(void)
{
    if(state_comp_a == 0u)
    {
        gpio_write(cfg_pin_output.step1.port, cfg_pin_output.step1.bit, 1u);
        state_comp_a = 1u;
        comp_a = comp_a + 3u;
        
    }
    else
    {
        gpio_write(cfg_pin_output.step1.port, cfg_pin_output.step1.bit, 0u);
        state_comp_a = 0u;
        comp_a = comp_a + 80u;
    }
    

    timer_set_compare(Timer1_Comp_A, comp_a);
}