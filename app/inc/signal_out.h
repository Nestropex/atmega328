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
    uint16_t *frequency;
    uint8_t  *phase;
    pin_t    pin_out;
    uint32_t period_ticks;
    uint32_t delay_ticks;
    uint32_t next_hi_event;
    uint32_t next_low_event;
}signal_t;


//-------Variables-------



//-------Function Declaration-------

/**
 * @brief Registeres timer 1 interrupts and initializes handles for isr's
 *        and sets periodical occurrence of isr as base to compute signals
 *        rather than timer ticks
 */
void signal_init(void);
void signal_frequency(uint16_t frequency, uint16_t phase);
void signal_rectangle(uint16_t frequency, uint16_t phase, uint8_t nmb_of_channels);

#endif