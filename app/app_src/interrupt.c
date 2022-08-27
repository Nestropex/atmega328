


#include "datatypes.h"
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>

void interrupt_init(void)
{
    sei();                  // Assembler instruction to enable interrupts globally
}

ISR(TIMER1_COMPA_vect) {    
    uart_str_transmit("\n");
    uart_str_transmit("interrupt A ocurred");
    uart_str_transmit("\n");

}

ISR(TIMER1_COMPB_vect) {    
    uart_str_transmit("\n");
    uart_str_transmit("interrupt B ocurred");
    uart_str_transmit("\n");

}

ISR(TIMER1_OVF_vect) {    
    uart_str_transmit("\n");
    uart_str_transmit("interrupt OVF ocurred");
    uart_str_transmit("\n");

}

