// Short description 
// Hardware PCINT Pin Change Interrupt
//


//-------Includes-------

#include "datatypes.h"
#include "pcint.h"
#include "avr/io.h"

//-------Defines-------



//-------TYPES-------



//-------Variables-------



//-------Static Function Declaration-------



//-------Function Definition-------


void pcint_init(uint8_t index)
{
    if (index < 8u)
    {
        PCMSK0 |= 1 << index;
        PCICR  |= 0x01u;
    }
    else if (index < 15u)
    {
       PCMSK1 |= 1 << (index - 8u);
       PCICR  |= 0x02u;
    }
    else
    {
        PCMSK2 |= 1<< (index - 15u);
        PCICR  |= 0x04u;
    }
}