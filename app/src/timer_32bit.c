// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "isr.h"
#include "timer.h"
#include "timer_32bit.h"


//-------Defines-------

#define FIRST_BIT_AFTER_8BIT_OVF 0x00000100ul

//-------TYPES-------



//-------Variables-------

uint32_t timer0_32 = 0x0ul;

//-------Static Function Declaration-------

void period_timer_0_ovf(void); // Do not make static as it serves as isr


//-------Function Definition-------

void timer0_32bit_init(void)
{
    isr_register(period_timer_0_ovf, Timer0_OVF);
}

uint32_t timer0_32_get_ticks(void)
{
    return  (timer0_32 | timer0_get_ticks());
}

void period_timer_0_ovf(void)
{
    timer0_32 = timer0_32 + FIRST_BIT_AFTER_8BIT_OVF;
}