
#include "datatypes.h"
#include <avr/io.h>
#include "gpio.h"
#include "cfg.h"

int main(void)
{
    GPIO_setup(1U,gc_portb_cfg);
    GPIO_setup(2U,gc_portc_cfg);
    GPIO_setup(3U,gc_portd_cfg);

    while(1)
    {    

 
    
    }

    return 0;
}


void delay(int delay)
{
    


    for (int i = 0; i<delay;i++)
    {
        
    }
}