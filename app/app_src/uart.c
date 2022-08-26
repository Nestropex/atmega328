




#include <avr/io.h>
#include "datatypes.h"


#define INIT_IN_SYNCH_MODE 0x80u
#define BAUDRATE           103u
#define ENABLE_TRANSMIT    (1 << TXEN0 | 1 << RXEN0)
#define STOP_BITS_2        (1 << USBS0) 
#define FRAME_SIZE_8BIT    (1<<UCSZ00 | 1<<UCSZ01)

void uart_init(void)
{
    UCSR0C  = INIT_IN_SYNCH_MODE;
    UCSR0C |= FRAME_SIZE_8BIT; 
    UCSR0C |= STOP_BITS_2;              
    UCSR0B |= ENABLE_TRANSMIT;
    UBRR0L  = BAUDRATE;              

}

uint8_t uart_str_transmit(uint8_t *str)
{
    uint8_t count = 0u;  

    if (str != NULL_PTR)
    {
        

        do
        {
            while(!(UCSR0A & (1 << UDRE0)))
            {

            }

            UDR0 = *str;
            str++;
            count++;

        }while(*str != '\0');
    }

    return count;
}

// This function is taken and modified from printNumber()
// to find in Arduino\hardware\arduino\avr\cores\arduino\print.ccp
void uart_nmb_transmit(unsigned long n, uint8_t base)
{
  uint8_t buf[8 * sizeof(long) + 1]; 
  uint8_t *str = &buf[sizeof(buf) - 1];
  uint8_t count = 0u;

  *str = '\0';

  if (base > 1u)
  {
    do {
        char c = n % base;
        n /= base;

        *--str = c < 10 ? c + '0' : c + 'A' - 10; // else means hex numbers are required
        count++;
       } while(n);

    uart_str_transmit(str);
    uart_str_transmit("\n");
  }
 
}