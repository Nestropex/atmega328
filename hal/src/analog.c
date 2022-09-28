// Short description 
//
//


//-------Includes-------

#include <avr/io.h>
#include "datatypes.h"
#include "analog.h"


//-------Defines-------
#define ADMUX_CONFIG 0xc3u

#define ADCSRA_CONFIG 0x87u
#define ADCSRB_CONFIG 0x04u
#define DIDR0_CONFIG  0x08u
//-------TYPES-------



//-------Variables-------



//-------Static Function Declaration-------



//-------Function Definition-------

void analog_init(void)
{
    

    ADCSRA = ADCSRA_CONFIG;
    ADCSRB = ADCSRB_CONFIG;
    DIDR0 = DIDR0_CONFIG;
    ADMUX  = ADMUX_CONFIG;
}


uint16_t analog_read(uint8_t adc_ch)
{

    ADMUX = (ADMUX & 0xF0) | (adc_ch & 0x0F);

    ADCSRA |= (1<<ADSC);

    while( ADCSRA & (1<<ADSC) );
    {

    }

    return ADC;
}