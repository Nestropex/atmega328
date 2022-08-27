



#include <avr/io.h>
#include <avr/interrupt.h>
#include "datatypes.h"
#include "system.h"
#include "uart.h"
#include "isr.h"

static void (* function_timer0_comp_a)();
static void (* function_timer0_comp_b)();
static void (* function_timer0_ovf)();
static void (* function_timer1_comp_a)();
static void (* function_timer1_comp_b)();
static void (* function_timer1_ovf)();
static void (* function_timer2_comp_a)();
static void (* function_timer2_comp_b)();
static void (* function_timer2_ovf)();

void isr_init(void)
{
    sei();                  // Assembler instruction to enable interrupts globally
}

ISR(TIMER1_COMPA_vect) {   

    if (function_timer1_comp_a != NULL_PTR)
    {
        (*function_timer1_comp_a)(); 
    }
    
    uart_str_transmit("isr t1 a executed\n");

}

ISR(TIMER1_COMPB_vect) {    
    
    if (function_timer1_comp_b != NULL_PTR)
    {
        (*function_timer1_comp_b)(); 
    }
    uart_str_transmit("isr t1 b executed\n");
}

ISR(TIMER1_OVF_vect) {    
    
    if (function_timer1_ovf != NULL_PTR)
    {
        (*function_timer1_ovf)(); 
    }
    uart_str_transmit("isr t1 ovf executed\n");

}

void isr_register(void (*isr), interrupts_t nmb)
{
    
    if (isr != NULL_PTR)
    {
        switch (nmb)
        {
        case Timer0_Comp_A:
            function_timer0_comp_a = isr;
            break;
        case Timer0_Comp_B:
            function_timer0_comp_b = isr;
            break;
        case Timer0_OVF:
            function_timer0_ovf = isr;
            break;
        case Timer1_Comp_A:
            function_timer1_comp_a = isr;
            break;
        case Timer1_Comp_B:
            function_timer1_comp_b = isr;
            break;
        case Timer1_OVF:
            function_timer1_ovf = isr;
            break;
        case Timer2_Comp_A:
            function_timer2_comp_a = isr;
            break;
        case Timer2_Comp_B:
            function_timer2_comp_b = isr;
            break;
        case Timer2_OVF:
            function_timer2_ovf = isr;
            break;
        
        default:
            ERROR_HANDLER("ERROR isr_register");
            break;
        }
        
    }
    else
    {
        
    }
}
