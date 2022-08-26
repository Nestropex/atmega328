




#include <avr/io.h>
#include "datatypes.h"





void uart_init(void)
{
    UCSR0C = 0x80u; // Init in synchronous mode
    UCSR0C |= (1<<UCSZ00 | 1<<UCSZ01); // 8bit transmit size
    UCSR0C |= 1 << USBS0 ;  // 2 Stop bit
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0); //transmit enable
    UBRR0L = 103; // 9600 baud @ 16 MHz

}

uint8_t uart_str_transmit(uint8_t *str)
{
    do
    {
        while(!(UCSR0A & (1 << UDRE0)))
        {

        }

        UDR0 = *str;
        str++;
    }while(*str != '\0');

    return 0;
}

void uart_nmb_transmit(unsigned long n, uint8_t base)
{
  uint8_t buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  uint8_t *str = &buf[sizeof(buf) - 1];
  uint8_t count = 0u;

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
    count++;
  } while(n);

  uart_str_transmit(str);
  uart_str_transmit("\n");
  
}