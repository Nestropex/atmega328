#ifndef SIGNAL_H
#define SIGNAL_H

// Short description 
//
//


//-------Includes-------

#include "datatypes.h"



//-------Defines-------




//-------TYPES-------

typedef struct signal {
    uint8_t  state;
    uint16_t frequency;
    uint8_t  phase;
    pin_t    pin_out;
    uint32_t period_ticks;
    uint32_t delay_ticks;
    uint32_t next_event;
}signal_t;


//-------Variables-------



//-------Function Declaration-------
void signal_init(signal_t *channel);
void signal_frequency(uint16_t frequency, uint16_t phase);
void signal_rectangle(signal_t *channel);

#endif