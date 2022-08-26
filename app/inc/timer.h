#ifndef TIMER_H
#define TIMER_H

#include "datatypes.h"

/**
 * @brief Resets config regs and starts the timer 
 *        by configuring the prescaler. 
 * 
 */
void timer_init(void);

/**
 * @brief Returns current timer count.
 * 
 * @return 16 bit current timer count 
 */
uint16_t timer_get_16bit_ticks(void);


#endif