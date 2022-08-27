


#include "datatypes.h"
#include <avr/io.h>
#include "system.h"
#include <avr/interrupt.h>

void interrupt_init(void)
{


    
    sei();                  // C6:: Enable interrupts

}

ISR(TIMER1_COMPA_vect) {    

    ERROR_HANDLER("interrupt A ocurred");

}

ISR(TIMER1_COMPB_vect) {    

    ERROR_HANDLER("interrupt B ocurred");

}

ISR(TIMER1_OVF_vect) {    

    ERROR_HANDLER("interrupt OVF ocurred");

}

