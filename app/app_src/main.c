
#define __AVR_ATmega324A__
#include <avr/io.h>

void delay(int delay);
int main(void)
{
int i = 0;
    int mydelay = 500;
    while(1)
    {    
    if (i < mydelay)
    {
        DDRB |= 1 << PB5;
        PORTB |= 1 << PB5;
    }
    else
    {
        DDRB = 0 ;
        PORTB = 0 ;
    }
    i++;
    
    }

    return 0;
}


void delay(int delay)
{
    


    for (int i = 0; i<delay;i++)
    {
        
    }
}