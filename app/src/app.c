

#include "datatypes.h"
#include "cfg.h"
#include "timer.h"
#include "gpio.h"
#include "isr.h"
#include "uart.h"
#include "loop.h"


typedef struct app_input{
        uint16_t on_time;
        uint8_t  state;
        pin_t pin;
        loop_t *period;
}app_input_t;

loop_t loop_button1 = {0ul,0ul,0u,0u,0u,0u,0u};


static void read_inputs(void);
static void isr_timer_1_comp_a(void);
static void button_update(app_input_t *object);


void app_init(void)
{
    
}


void app_main(void)
{
    const cfg_output_pin_t app_out = cfg_pin_output;
    app_input_t button1;
    button1.pin = cfg_pin_input.button1;
    button1.period = &loop_button1;
 
    button_update(&button1);

    gpio_write(app_out.dir1.port, app_out.dir1.bit,1);
    
}
/**
 * @brief Updates input object with button state and the time it is on
 * 
 * @param object pointer to input object as switch or button
 */
static void button_update(app_input_t *object)
{
    if (object != NULL_PTR)
    {
        app_input_t temp_obj = *object;

        temp_obj.state = gpio_read(temp_obj.pin.port,temp_obj.pin.bit);

        if (temp_obj.state == 1u)
        {
            
            loop_control(temp_obj.period);
        }
        else 
        {
            temp_obj.period->time = 0u;
            temp_obj.period->cnt = 0u;
            
        }
        temp_obj.on_time =(uint16_t) temp_obj.period->time * temp_obj.period->cnt;
        *object = temp_obj;
    }
    

}
static void isr_timer_1_comp_a(void)
{
    //uart_str_transmit("\n");
}