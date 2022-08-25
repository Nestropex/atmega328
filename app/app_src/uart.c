




#include <avr/io.h>
#include "datatypes.h"


uint8_t uart_set_baudrate(uint32_t baudrate)
{
    UCSR0C = 0x80u; // Init in synchronous mode
    UCSR0C |= (1<<UCSZ00 | 1<<UCSZ01); // 8bit transmit size
    UCSR0C |= 1 << USBS0 ;  // 2 Stop bit
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //transmit enable
    UBRR0L = 103; // 9600 baud @ 16 MHz

    return 0u;
}

uint8_t uart_transmit(uint8_t *data, uint8_t count)
{

   

    for(uint8_t i = 0u; i < count; i++)
    {
        while(!(UCSR0A & (1 << UDRE0)))
        {

        }

        UDR0 = *data;
        data++;
    }
 
}