



#include <avr/io.h>
#include <avr/interrupt.h>
#include "datatypes.h"
#include "system.h"
#include "uart.h"
#include "isr.h"

#define ENABLE_INT_COMP_A 0x02u
#define ENABLE_INT_COMP_B 0x04u
#define ENABLE_INT_OVF    0x01u

static void (* function_timer0_comp_a)();
static void (* function_timer0_comp_b)();
static void (* function_timer0_ovf)();
static void (* function_timer1_comp_a)();
static void (* function_timer1_comp_b)();
static void (* function_timer1_ovf)();
static void (* function_timer2_comp_a)();
static void (* function_timer2_comp_b)();
static void (* function_timer2_ovf)();
static void (* function_uart_tx)();

void isr_init(void)
{
    sei();
}

void isr_register(void (*isr), interrupts_t nmb)
{
    if (isr != NULL_PTR)
    {
        switch (nmb)
        {
        case Timer0_Comp_A:
            function_timer0_comp_a = isr;
            TIFR0  |= ENABLE_INT_COMP_A;
            TIMSK0 |= ENABLE_INT_COMP_A;
            break;
        case Timer0_Comp_B:
            function_timer0_comp_b = isr;
            TIFR0  |= ENABLE_INT_COMP_B;
            TIMSK0 |= ENABLE_INT_COMP_B;
            break;
        case Timer0_OVF:
            function_timer0_ovf = isr;
            TIFR0  |= ENABLE_INT_OVF;
            TIMSK0 |= ENABLE_INT_OVF;
            break;
        case Timer1_Comp_A:
            function_timer1_comp_a = isr;
            TIFR1  |= ENABLE_INT_COMP_A;
            TIMSK1 |= ENABLE_INT_COMP_A;
            break;
        case Timer1_Comp_B:
            function_timer1_comp_b = isr;
            TIFR1  |= ENABLE_INT_COMP_B;
            TIMSK1 |= ENABLE_INT_COMP_B;
            break;
        case Timer1_OVF:
            function_timer1_ovf = isr;
            TIFR1  |= ENABLE_INT_OVF;
            TIMSK1 |= ENABLE_INT_OVF;
            break;
        case Timer2_Comp_A:
            function_timer2_comp_a = isr;
            TIFR2  |= ENABLE_INT_COMP_A;
            TIMSK2 |= ENABLE_INT_COMP_A;
            break;
        case Timer2_Comp_B:
            function_timer2_comp_b = isr;
            TIFR2  |= ENABLE_INT_COMP_B;
            TIMSK2 |= ENABLE_INT_COMP_B;
            break;
        case Timer2_OVF:
            function_timer2_ovf = isr;
            TIFR2  |= ENABLE_INT_OVF;
            TIMSK2 |= ENABLE_INT_OVF;
            break;
        case Uart_tx:
            function_uart_tx = isr;
            UCSR0B  |= 1u << TXCIE0;
            break;
        
        default:
            ERROR_HANDLER("ERROR isr_register");
            break;
        }
        
    }
    else
    {
        ERROR_HANDLER("ERROR isr_register");
    }
}

ISR(TIMER0_COMPA_vect) {   

    if (function_timer0_comp_a != NULL_PTR)
    {
        (*function_timer0_comp_a)(); 
    }
}

ISR(TIMER0_COMPB_vect) {    
    
    if (function_timer0_comp_b != NULL_PTR)
    {
        (*function_timer0_comp_b)(); 
    }
}

ISR(TIMER0_OVF_vect) {    
    
    if (function_timer0_ovf != NULL_PTR)
    {
        (*function_timer0_ovf)(); 
    }
}

ISR(TIMER1_COMPA_vect) {   

    if (function_timer1_comp_a != NULL_PTR)
    {
        (*function_timer1_comp_a)(); 
    }
}

ISR(TIMER1_COMPB_vect) {    
    
    if (function_timer1_comp_b != NULL_PTR)
    {
        (*function_timer1_comp_b)(); 
    }
}

ISR(TIMER1_OVF_vect) {    
    
    if (function_timer1_ovf != NULL_PTR)
    {
        (*function_timer1_ovf)(); 
    }
}

ISR(TIMER2_COMPA_vect) {   

    if (function_timer2_comp_a != NULL_PTR)
    {
        (*function_timer2_comp_a)(); 
    }
}

ISR(TIMER2_COMPB_vect) {    
    
    if (function_timer2_comp_b != NULL_PTR)
    {
        (*function_timer2_comp_b)(); 
    }
}

ISR(TIMER2_OVF_vect) {    
    
    if (function_timer2_ovf != NULL_PTR)
    {
        (*function_timer2_ovf)(); 
    }
}

ISR(USART_TX_vect) {    
    
    if (function_uart_tx != NULL_PTR)
    {
        (*function_uart_tx)(); 
    }
}