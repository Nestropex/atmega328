#ifndef SIGNAL_H
#define SIGNAL_H

// Short description 
//
//


//-------Includes-------

#include "datatypes.h"



//-------Defines-------




//-------TYPES-------



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
void signal_sine(uint16_t frequency, uint16_t phase, uint8_t nmb_of_channels);
#endif