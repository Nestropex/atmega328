
#include "datatypes.h"
#include "cfg.h"
#include "system.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "period.h"
#include "input.h"


void input_get(app_input_t *object)
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
   


