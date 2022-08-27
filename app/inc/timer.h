#ifndef TIMER_H
#define TIMER_H

#include "datatypes.h"

/**
 * @brief Resets config regs and starts the timer 
 *        by configuring the prescaler. 
 * 
 */
uint32_t timer_init(void);

/**
 * @brief Returns current timer count.
 * 
 * @return 16 bit current timer count 
 */
uint16_t timer_get_16bit_ticks(void);

/**
 * @brief Sets a compare value for all three timer 0,1 and 2
 * 
 * @param port port b,c and d correspond to 1,2 and 3
 * @param pin 0 to 7, corresponds to pin number i.e pb5: port 1, pin 5
 * @param comp_val value that is used to trigger ISR on compare match
 *                 timer 0 and 2 are 8 bit timers, value must not exceed 255
 */
void timer_set_compare(uint8_t port, uint8_t pin, uint16_t comp_val);

#endif