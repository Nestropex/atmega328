// Short description 
//
//


//-------Includes-------

#include "datatypes.h"
#include "isr.h"
#include "timer.h"
#include "uart.h"
#include "timer_32bit.h"


//-------Defines-------

#define FIRST_BIT_AFTER_8BIT_OVF 0x00000100ul
#define FIRST_BIT_AFTER_16BIT_OVF 0x00010000ul

//-------TYPES-------



//-------Variables-------

uint32_t timer0_32 = 0x0ul;
uint32_t timer1_32 = 0x0ul;
uint32_t timer2_32 = 0x0ul;

//-------Static Function Declaration-------

void period_timer_0_ovf_isr(void); // Do not make static as it serves as isr
void period_timer_1_ovf_isr(void); // Do not make static as it serves as isr
void period_timer_2_ovf_isr(void); // Do not make static as it serves as isr


//-------Function Definition-------

void timer_32bit_init(void)
{
    isr_register(period_timer_0_ovf_isr, Timer0_OVF);
    isr_register(period_timer_1_ovf_isr, Timer1_OVF);
    isr_register(period_timer_2_ovf_isr, Timer2_OVF);
}

uint32_t timer0_32_get_ticks(void)
{
    return  (timer0_32 | timer0_get_ticks());
}

uint32_t timer1_32_get_ticks(void)
{
    return  (timer1_32 | timer1_get_ticks());
}


uint32_t timer2_32_get_ticks(void)
{
    return  (timer2_32 | timer2_get_ticks());
}


void period_timer_0_ovf_isr(void)
{
    timer0_32 = timer0_32 + FIRST_BIT_AFTER_8BIT_OVF;
    //uart_str_transmit("ovf 0  ");
}

void period_timer_1_ovf_isr(void)
{
    timer1_32 = timer1_32 + FIRST_BIT_AFTER_16BIT_OVF;
}

void period_timer_2_ovf_isr(void)
{
    timer2_32 = timer2_32 + FIRST_BIT_AFTER_8BIT_OVF;
    
}