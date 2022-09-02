

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
period_t loop_button2 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_button3 = {0ul,0ul,0u,0u,0u,0u,0u};
period_t loop_switch1 = {0ul,0ul,0u,0u,0u,0u,0u};
app_input_t button1;
app_input_t button2;
app_input_t button3;
app_input_t switch1;
uint16_t comp_ticks;
const uint16_t ontime_ticks = OUT_ONTIME_TICKS;

static void read_inputs(void);
static uint16_t set_step_out(uint8_t port, uint8_t pin, uint16_t offtime);
static void isr_timer_1_comp_a(void);
static void isr_timer_1_comp_b(void);
static void get_input_ONtime(app_input_t *object);



void app_init(void)
{
    button1.pin = cfg_pin_input.button1;
    button1.loop = &loop_button1;
    button2.pin = cfg_pin_input.button2;
    button2.loop = &loop_button2;
    button3.pin = cfg_pin_input.button3;
    button3.loop = &loop_button3;
    switch1.pin = cfg_pin_input.switch1;
    switch1.loop = &loop_switch1;

    isr_init();
    isr_register(isr_timer_1_comp_a, Timer1_Comp_A);
    comp_ticks = 1000u ;
    timer_set_compare(Timer1_Comp_A, comp_ticks);
    isr_register(isr_timer_1_comp_b, Timer1_Comp_B);
    timer_set_compare(Timer1_Comp_B, comp_ticks);
}

static uint8_t start_stop;
static uint8_t speed = 5u;
static uint8_t speed_dir=0u;
void app_main(void)
{
    get_input_ONtime(&button1);
    get_input_ONtime(&button2);
    get_input_ONtime(&button3);
    get_input_ONtime(&switch1);

    if ((button2.state == TOGGLE_DIR) && (button2.loop->cnt <= VALID_ONCE))
    {
        if (speed == 5u)
        {
            speed_dir = 1u;
        }
        else if (speed == 1u)
        {
            speed_dir = 0u;
        }
        else
        {
            /* code */
        }
        

        if (speed_dir == 1u)
        {
            speed--;
        }
        else
        {
            speed++;
        }
        uart_str_transmit("speed ");
        uart_nmb_transmit(speed,10);
    }

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

    if ((button3.state == TOGGLE_DIR) && (button3.loop->cnt <= VALID_ONCE))
    {
        start_stop = ~start_stop;
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

uint8_t state_comp;
static uint16_t set_step_out(uint8_t port, uint8_t pin, uint16_t offtime)
{
    if (start_stop)
    {
        uint8_t state_comp;
        state_comp = gpio_read(port,pin);
        comp_ticks = timer1_get_ticks();
        if(state_comp == 0u)
        {
            gpio_write(port, pin, 1u);
            comp_ticks = comp_ticks + ontime_ticks;
            
        }
        else
        {
            gpio_write(port, pin, 0u);
            comp_ticks = comp_ticks + offtime;
        }
        
    }
    else
    {
        comp_ticks = comp_ticks + 1000u;
    }
    
    return comp_ticks;
    
}

#define MINIMUM_TICKS_CH2 
static void isr_timer_1_comp_a(void)
{
    uint16_t comp_a;
    comp_a = set_step_out(cfg_pin_output.step1.port, cfg_pin_output.step1.bit, 300u*speed);
    timer_set_compare(Timer1_Comp_A, comp_a);
}

static void isr_timer_1_comp_b(void)
{
    uint16_t comp_b;
    comp_b = set_step_out(cfg_pin_output.step2.port, cfg_pin_output.step2.bit, 150u*speed);
    timer_set_compare(Timer1_Comp_B, comp_b);
}