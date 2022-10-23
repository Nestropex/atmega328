




#include <avr/io.h>
#include "datatypes.h"
#include "system.h"
#include "isr.h"
#include "fifo.h"
#include "stream.h"

#define INIT_IN_SYNCH_MODE 0x80u
#define ENABLE_TRANSMIT    (1 << TXEN0 | 1 << RXEN0)
#define STOP_BITS_2        (1 << USBS0) 
#define FRAME_SIZE_8BIT    (1<<UCSZ00 | 1<<UCSZ01)

extern list_t stream;
void uart_isr_tx(void);

void uart_init(uint32_t clk, uint32_t baudrate)
{
    uint8_t reg_val;
    if (baudrate >= 4800)
    {
        if(baudrate != 115200)
        {
            reg_val = (uint8_t)((clk/(16*baudrate)) - 1u);
        }
        else
        {
            // According to manual reg_val should be 8 but it is 7.
            // Equation is not correct for 115200
            reg_val = (uint8_t)(clk/(16*baudrate)) ;
        }
        

        UCSR0C  = INIT_IN_SYNCH_MODE;
        UCSR0C |= FRAME_SIZE_8BIT; 
        UCSR0C |= STOP_BITS_2;              
        UCSR0B |= ENABLE_TRANSMIT;
        UBRR0L  = reg_val;  
    }
    

    isr_register(uart_isr_tx, Uart_tx);

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
    else
    {
        ERROR_HANDLER("ERROR uart_str_transmit");
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
  else
  {
      ERROR_HANDLER("ERROR uart_nmb_transmit");
  }
  
 
}

void uart_cnt_transmit(uint8_t *str, uint8_t cnt)
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

        }while(count < cnt);
    }
    else
    {
        ERROR_HANDLER("ERROR uart_cnt_transmit");
    }
}

void uart_fast_byte_transmit(uint8_t *str)
{
    uint8_t count = 0u;  

    if (str != NULL_PTR)
    {
        uart_nmb_transmit(*str, 10u);
  
    }
    else
    {
        ERROR_HANDLER("ERROR uart_cnt_transmit");
    }
}

void uart_isr_tx(void)
{
    if(stream.head != stream.tail)
    {
        uint8_t data = fifo_read(&stream);
        uart_nmb_transmit(data, 10u);
    }
}
